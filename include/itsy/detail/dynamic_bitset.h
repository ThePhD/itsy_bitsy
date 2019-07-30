#ifndef ITSY_BITSY_DETAIL_DYNAMIC_BITSET_H
#define ITSY_BITSY_DETAIL_DYNAMIC_BITSET_H 1

#if defined(_MSC_VER) || (defined(__cplusplus) && __cplusplus >= 201703L)

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
#else
#include <itsy/detail/bit_iterator.h>
#include <itsy/detail/bit_view.h>
#endif

#include <cstddef>
#include <type_traits>
#include <algorithm>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{

	template<typename __C>
	class __basic_dynamic_bitset : private __bit_view<__C, __word_bit_extents<__C>>
	{
	private:
		template<typename, typename>
		friend class __bit_view;

		using __base_t           = __bit_view<__C>;
		using __word_type        = typename __base_t::__word_type;
		using __base_reference   = typename __base_t::__base_reference;
		using __base_c_reference = typename __base_t::__base_c_reference;
		using __base_iterator    = typename __base_t::__base_iterator;
		using __base_c_iterator  = typename __base_t::__base_c_iterator;
		using __storage_type     = typename __base_t::__storage_type;

	public:
		using difference_type   = typename __base_t::difference_type;
		using size_type         = typename __base_t::size_type;
		using value_type        = typename __base_t::value_type;
		using reference         = typename __base_t::reference;
		using const_reference   = typename __base_t::const_reference;
		using iterator_category = typename __base_t::iterator_category;
		using iterator_concept  = typename __base_t::iterator_category;
		using pointer           = typename __base_t::pointer;
		using iterator          = typename __base_t::iterator;
		using sentinel          = typename __base_t::sentinel;
		using const_iterator    = typename __base_t::const_iterator;
		using const_sentinel    = typename __base_t::const_sentinel;
		using range_type        = typename __base_t::range_type;
		using container_type    = __C;

		// constructors
		__basic_dynamic_bitset() noexcept(noexcept(__base_t()))
		: __base_t(), _M_bit_pos(__binary_digits_v<__word_type>)
		{
		}

		template<typename... __Args>
		__basic_dynamic_bitset(::std::in_place_t, __Args&&... __args) noexcept(
		  noexcept(__base_t(::std::forward<__Args>(__args)...)))
		: __base_t(::std::forward<__Args>(__args)...), _M_bit_pos(__binary_digits_v<__word_type>)
		{
		}

		__basic_dynamic_bitset(const __basic_dynamic_bitset& __right) = default;

		__basic_dynamic_bitset(__basic_dynamic_bitset&& __right) = default;

		__basic_dynamic_bitset&
		operator=(__basic_dynamic_bitset&& __right) = default;

		__basic_dynamic_bitset&
		operator=(const __basic_dynamic_bitset& __right) = default;

		// modifiers
		using __base_t::flip;
		using __base_t::set;

		iterator
		insert(const_iterator __pos, std::initializer_list<bool> __il)
		{
			return insert(std::move(__pos), __il.begin(), __il.end());
		}

		iterator
		insert(const_iterator __pos, size_type __n, bool __val)
		{
			iterator __current_pos = std::move(__pos);
			for (size_type __ni = __n; __ni > 0; --__ni)
				{
					__current_pos = insert(std::move(__current_pos), __val);
				}
			return __current_pos;
		}

		template<typename __Iterator>
		iterator
		insert(const_iterator __pos, __Iterator __first, __Iterator __last)
		{
			if (__first == __last)
				{
					return this->end();
				}
			if constexpr (false)
				{
					// TODO: range bit insertion,
					// range bit shifting
				}
			else
				{
					iterator __current_pos = insert(std::move(__pos), *__first);
					++__first;
					for (; __first != __last; ++__first)
						{
							__current_pos = insert(std::move(__current_pos), *__first);
						}
					return __current_pos;
				}
		}

		void
		push_back(bool __val)
		{
			using __bit_ref = reference;
			__base_iterator __storage_it;
			if (_M_bit_pos == __binary_digits_v<__word_type>)
				{
					__storage_it =
					  this->_M_storage.insert(::std::cend(this->_M_storage), static_cast<__word_type>(0));
					_M_bit_pos = 0;
				}
			else
				{
					__storage_it = ::std::end(this->_M_storage);
					--__storage_it;
				}

			__bit_ref __ref(*__storage_it, _M_bit_pos);
			__ref = __val;

			++_M_bit_pos;
		}

		void
		push_front(bool __val)
		{
			using __bit_ref = reference;
			if (_M_bit_pos == __binary_digits_v<__word_type>)
				{
					this->_M_storage.insert(::std::cend(this->_M_storage), static_cast<__word_type>(0));
					_M_bit_pos = 0;
				}
			++_M_bit_pos;

			auto __storage_first = ::std::begin(this->_M_storage);
			auto __storage_last  = ::std::end(this->_M_storage);
			bool __old_val       = __val;
			for (; __storage_first != __storage_last; ++__storage_first)
				{
					__base_reference __ref = *__storage_first;
					__bit_ref __front(__ref, 0);
					__bit_ref __back(__ref, __max_binary_index_v<__word_type>);
					__old_val = __back;
					__ref <<= 1;
					__front = __val;
					__val   = __old_val;
				}
		}

		iterator
		insert(const_iterator __pos, bool __val)
		{
			// if this container is at its end,
			// then we need to push back another word of storage
			if (this->empty())
				{
					push_back(__val);
					return --this->end();
				}
			auto __pos_base_it  = std::move(__pos).base();
			auto __pos_position = std::move(__pos).position();
			auto __storage_last = ::std::cend(this->_M_storage);
			if (__pos.base() == __storage_last)
				{
					push_back(__val);
					return --this->end();
				}
			--__storage_last;
			if (__storage_last == __pos_base_it && __pos_position >= this->_M_bit_pos)
				{
					push_back(__val);
					return --this->end();
				}
			if (__pos_base_it == ::std::cbegin(this->_M_storage) && __pos_position == 0)
				{
					push_front(__val);
					return this->begin();
				}

			using __mutator                 = __bit_reference<__base_reference, __word_type>;
			__base_iterator __storage_first = ::std::begin(this->base());
			__base_iterator __it =
			  std::next(__storage_first, std::distance(__base_c_iterator(__storage_first), __pos.base()));
			iterator __insertion_return(__it, __pos.position());
			__mutator __insert_target(*__it, __pos.position());
			bool __old_val  = __insert_target;
			__insert_target = __val;

			// now, shift literally everything
			for (size_type __shift_bit_pos = __pos.position() + 1;
			     __shift_bit_pos < __binary_digits_v<__word_type>; ++__shift_bit_pos)
				{
					__mutator __target_bit(*__it, __shift_bit_pos);
					bool __saved = __target_bit;
					__target_bit = __old_val;
					__old_val    = __saved;
				}
			for (; __it != __storage_last; ++__it)
				{
					bool __saved = __mutator(*__it, __max_binary_index_v<__word_type>);
					*__it >>= 1;
					__mutator(*__it, 0) = __old_val;
					__old_val           = __saved;
				}

			return __insertion_return;
		}

		iterator
		erase(const_iterator __pos)
		{
			auto __storage_last      = ::std::cend(this->_M_storage);
			auto __pos_it            = __pos.base();
			size_type __pos_position = __pos.position();
			if (__pos_it == __storage_last ||
			    (__pos_position >= _M_bit_pos && --__storage_last == __pos_it))
				{
					// can't erase the literal end:
					return __pos;
				}

			// okay, we actually have to remove old bits now...
			// save old bits that will be affected by left shift
			__base_reference __storage_ref = *__pos_it;
			if (__pos_position == 0)
				{
					__storage_ref <<= 1;
				}
			else
				{
					__word_type __preservation      = __storage_ref;
					__word_type __preservation_mask = __pos_to_all_1_mask<__word_type>(__pos.position());
					__preservation                  = __preservation & __preservation_mask;
					__storage_ref <<= 1;
					__storage_ref = (__storage_ref & (~__preservation_mask)) | (__preservation);
				}
			bool __old_val;
			auto __old_pos_it = __pos_it;
			++__pos_it;
			for (auto __curr_pos_it = __pos_it; __curr_pos_it != __storage_last; ++__curr_pos_it)
				{
					// get current iterator's position
					__base_reference __curr_pos_ref = *__curr_pos_it;
					// give last position's most significant bit
					// our last signficant bit
					reference(*__old_pos_it, __max_binary_index_v<__word_type>) =
					  __bit_value(__curr_pos_ref, 0);
					++__old_pos_it;
					// shift over
					__curr_pos_ref <<= 1;
					// continue
				}
			if (_M_bit_pos == 0)
				{
					auto __removed_storage_it = this->_M_storage.erase(--__storage_last);
					if (__removed_storage_it == ::std::cbegin(this->_M_storage))
						{
							// we have no more storage left, stay at 0
							return iterator(::std::move(__removed_storage_it), 0);
						}
					_M_bit_pos = __max_binary_index_v<__word_type>;
					return iterator(--__removed_storage_it, __pos_position);
				}
			return iterator(__pos_it, __pos_position);
		}

		iterator
		erase(const_iterator __first, const_iterator __last)
		{
			if constexpr (false)
				{
					// TODO: bulk, sized removal
				}
			else
				{
					--__last;
					for (; __last != __first; --__last)
						{
							erase(__last);
						}
				}
		}

		void
		clear()
		{
			this->_M_storage.clear();
		}

		void
		swap(__basic_dynamic_bitset& __right) noexcept(::std::is_nothrow_swappable_v<__storage_type>)
		{
			::std::swap(this->_M_storage, __right._M_storage);
			::std::swap(this->_M_bit_pos, __right._M_bit_pos);
		}

		// observers
		using __base_t::all;
		using __base_t::any;
		using __base_t::count;
		using __base_t::none;
		using __base_t::population_count;
		using __base_t::test;

		using __base_t::operator[];

		bool
		empty() const
		{
			return this->_M_storage.empty();
		}

		reference
		back() noexcept
		{
			auto __back_it = this->end();
			--__back_it;
			return *(__back_it);
		}

		const_reference
		back() const noexcept
		{
			auto __back_it = this->cend();
			--__back_it;
			return *(__back_it);
		}

		reference
		front() noexcept
		{
			__base_reference __storage_ref = *::std::begin(this->_M_storage);
			return reference(__storage_ref, 0);
		}

		const_reference
		front() const noexcept
		{
			__base_c_reference __storage_ref = *::std::cbegin(this->_M_storage);
			return const_reference(__storage_ref, 0);
		}

		std::add_lvalue_reference_t<__C>
		base() noexcept
		{
			return this->_M_storage;
		}

		std::add_const_t<std::add_lvalue_reference_t<__C>>
		base() const noexcept
		{
			return this->_M_storage;
		}

		constexpr size_type
		size() const noexcept
		{
			size_type __word_size = ::std::size(this->_M_storage);
			if (__word_size == 0)
				{
					return 0;
				}
			return (__word_size - 1) * __binary_digits_v<__word_type> + this->_M_bit_pos;
		}

		constexpr iterator
		begin() noexcept
		{
			return iterator(::std::begin(this->_M_storage));
		}

		constexpr sentinel
		end() noexcept
		{
			auto __storage_last = ::std::end(this->_M_storage);
			if (_M_bit_pos < __binary_digits_v<__word_type>)
				{
					--__storage_last;
					return sentinel(::std::move(__storage_last), _M_bit_pos);
				}
			return sentinel(::std::move(__storage_last), 0);
		}

		constexpr const_iterator
		begin() const noexcept
		{
			return cbegin();
		}

		constexpr const_sentinel
		end() const noexcept
		{
			return cend();
		}

		constexpr const_iterator
		cbegin() const noexcept
		{
			return const_iterator(::std::cbegin(this->_M_storage));
		}

		constexpr const_sentinel
		cend() const noexcept
		{
			auto __storage_last = ::std::cend(this->_M_storage);
			if (_M_bit_pos < __binary_digits_v<__word_type>)
				{
					--__storage_last;
					return const_sentinel(::std::move(__storage_last), _M_bit_pos);
				}
			return const_sentinel(::std::move(__storage_last), 0);
		}

		template<typename __RightC>
		friend constexpr bool
		operator==(
		  const __basic_dynamic_bitset& __left, const __basic_dynamic_bitset<__RightC>& __right)
		{
			using __Left  = __basic_dynamic_bitset;
			using __Right = __basic_dynamic_bitset<__RightC>;

			if (__left._M_bit_pos == __binary_digits_v<typename __Left::__word_type> &&
			    __right._M_bit_pos == __binary_digits_v<typename __Right::__word_type>)
				{
					return static_cast<const typename __Left::__base_t&>(__left) ==
					       static_cast<const typename __Right::__base_t&>(__right);
				}
			auto __left_size  = __left.size();
			auto __right_size = __right.size();
			if (__left_size != __right_size)
				{
					return false;
				}
			else
				{
					return ::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(),
					  std::equal_to<bool>());
				}
		}

		template<typename __RightC>
		friend constexpr bool
		operator!=(
		  const __basic_dynamic_bitset& __left, const __basic_dynamic_bitset<__RightC>& __right)
		{
			using __Left  = __basic_dynamic_bitset;
			using __Right = __basic_dynamic_bitset<__RightC>;

			if (__left._M_bit_pos == __binary_digits_v<typename __Left::__word_type> &&
			    __right._M_bit_pos == __binary_digits_v<typename __Right::__word_type>)
				{
					return static_cast<const typename __Left::__base_t&>(__left) !=
					       static_cast<const typename __Right::__base_t&>(__right);
				}
			auto __left_size  = __left.size();
			auto __right_size = __right.size();
			if (__left_size != __right_size)
				{
					return true;
				}
			else
				{
					return !::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(),
					  std::equal_to<bool>());
				}
		}

		template<typename __RightC>
		friend constexpr bool
		operator<(const __basic_dynamic_bitset& __left, const __basic_dynamic_bitset<__RightC>& __right)
		{
			using __Left  = __basic_dynamic_bitset;
			using __Right = __basic_dynamic_bitset<__RightC>;

			if (__left._M_bit_pos == __binary_digits_v<typename __Left::__word_type> &&
			    __right._M_bit_pos == __binary_digits_v<typename __Right::__word_type>)
				{
					return static_cast<const typename __Left::__base_t&>(__left) <
					       static_cast<const typename __Right::__base_t&>(__right);
				}
			return ::std::lexicographical_compare(
			  __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), std::less<bool>());
		}

		template<typename __RightC>
		friend constexpr bool
		operator<=(
		  const __basic_dynamic_bitset& __left, const __basic_dynamic_bitset<__RightC>& __right)
		{
			using __Left  = __basic_dynamic_bitset;
			using __Right = __basic_dynamic_bitset<__RightC>;

			if (__left._M_bit_pos == __binary_digits_v<typename __Left::__word_type> &&
			    __right._M_bit_pos == __binary_digits_v<typename __Right::__word_type>)
				{
					return static_cast<const typename __Left::__base_t&>(__left) <=
					       static_cast<const typename __Right::__base_t&>(__right);
				}

			return !::std::lexicographical_compare(
			  __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), std::greater<bool>());
		}

		template<typename __RightC>
		friend constexpr bool
		operator>(const __basic_dynamic_bitset& __left, const __basic_dynamic_bitset<__RightC>& __right)
		{
			using __Left  = __basic_dynamic_bitset;
			using __Right = __basic_dynamic_bitset<__RightC>;

			if (__left._M_bit_pos == __binary_digits_v<typename __Left::__word_type> &&
			    __right._M_bit_pos == __binary_digits_v<typename __Right::__word_type>)
				{
					return static_cast<const typename __Left::__base_t&>(__left) >
					       static_cast<const typename __Right::__base_t&>(__right);
				}
			return ::std::lexicographical_compare(
			  __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), std::greater<bool>());
		}

		template<typename __RightC>
		friend constexpr bool
		operator>=(
		  const __basic_dynamic_bitset& __left, const __basic_dynamic_bitset<__RightC>& __right)
		{
			using __Left  = __basic_dynamic_bitset;
			using __Right = __basic_dynamic_bitset<__RightC>;

			if (__left._M_bit_pos == __binary_digits_v<typename __Left::__word_type> &&
			    __right._M_bit_pos == __binary_digits_v<typename __Right::__word_type>)
				{
					return static_cast<const typename __Left::__base_t&>(__left) >=
					       static_cast<const typename __Right::__base_t&>(__right);
				}

			return !::std::lexicographical_compare(
			  __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), std::less<bool>());
		}

	private:
		size_type _M_bit_pos = 0;

		void
		_M_ensure_enough_size()
		{
			if (_M_bit_pos == __max_binary_index_v<__word_type>)
				{
					this->_M_storage.insert(::std::cend(this->_M_storage), static_cast<__word_type>(0));
				}
		}

		void
		_M_ensure_enough_size(size_type __more)
		{
			size_type __ew, __eb;
			_M_ensure_enough_size(__more, __ew, __eb);
		}

		void
		_M_ensure_enough_size(size_type __more, size_type& __extra_words, size_type& __extra_bits)
		{
			size_type __extra_values = __more / __binary_digits_v<__word_type>;
			__extra_words            = __extra_values;
			__extra_bits             = __more % __binary_digits_v<__word_type>;
			if ((_M_bit_pos + __extra_bits) >= __binary_digits_v<__word_type>)
				{
					++__extra_values;
				}
			this->_M_storage.insert(
			  ::std::cend(this->_M_storage), __extra_values, static_cast<__word_type>(0));
		}

		void
		__add_to_bit_pos()
		{
			if (_M_bit_pos == __max_binary_index_v<__word_type>)
				{
					_M_bit_pos = 0;
				}
			else
				{
					++_M_bit_pos;
				}
		}

		void
		__add_to_bit_pos(size_type __more)
		{
			_M_bit_pos = (_M_bit_pos + __more) % __binary_digits_v<__word_type>;
		}
	};

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_DYNAMIC_BITSET_H
