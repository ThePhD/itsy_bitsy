// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#ifndef ITSY_BITSY_DETAIL_BIT_SEQUENCE_HPP
#define ITSY_BITSY_DETAIL_BIT_SEQUENCE_HPP 1

#include <itsy/detail/bit_iterator.hpp>
#include <itsy/detail/bit_view.hpp>
#include <itsy/detail/bit_detail.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>
#include <initializer_list>
#include <algorithm>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	template<typename _Container>
	class __bit_sequence : private __bit_view<_Container, __word_bit_bounds<_Container>>
	{
	private:
		template<typename, typename>
		friend class __bit_view;

		using __base_t                   = __bit_view<_Container, __word_bit_bounds<_Container>>;
		using __base_value_type          = typename __base_t::__base_value_type;
		using __integral_base_value_type = typename __base_t::__integral_base_value_type;
		using __base_reference           = typename __base_t::__base_reference;
		using __base_c_reference         = typename __base_t::__base_c_reference;
		using __base_iterator            = typename __base_t::__base_iterator;
		using __base_c_iterator          = typename __base_t::__base_c_iterator;
		using __base_iterator_category   = typename __base_t::__base_iterator_category;
		using __base_c_iterator_category = typename __base_t::__base_c_iterator_category;
		using __range_ref                = typename __base_t::__range_ref;

	public:
		using difference_type = typename __base_t::difference_type;
		using size_type       = typename __base_t::size_type;
		using value_type      = typename __base_t::value_type;
		using reference       = typename __base_t::reference;
		using const_reference = typename __base_t::const_reference;
		using iterator_category = typename __base_t::iterator_category;
		using iterator_concept = __iterator_concept_t<__base_iterator>;
		using pointer           = typename __base_t::pointer;
		using iterator          = typename __base_t::iterator;
		using sentinel          = typename __base_t::sentinel;
		using const_iterator    = typename __base_t::const_iterator;
		using const_sentinel    = typename __base_t::const_sentinel;
		using container_type    = typename __base_t::container_type;

		// constructors
		__bit_sequence() noexcept(noexcept(__base_t())) : __base_t(), _M_bit_pos(__binary_digits_v<__base_value_type>)
		{
		}

		template<typename... _Args>
		__bit_sequence(::std::in_place_t, _Args&&... __args) noexcept(
		     noexcept(__base_t(::std::forward<_Args>(__args)...)))
		: __base_t(::std::forward<_Args>(__args)...), _M_bit_pos(__binary_digits_v<__base_value_type>)
		{
		}

		template<typename _Iterator, typename _Sentinel,
		     std::enable_if_t<!::std::is_arithmetic_v<_Iterator> &&
		                      !::std::is_same_v<_Iterator, ::std::in_place_t>>* = nullptr>
		__bit_sequence(_Iterator __first, _Sentinel __last) noexcept(noexcept(__bit_sequence(
		     __dummy_tag{}, __bit_sequence::_S_efficient_empty_create(::std::move(__first), ::std::move(__last)))))
		: __bit_sequence(
		       __dummy_tag{}, __bit_sequence::_S_efficient_empty_create(::std::move(__first), ::std::move(__last)))
		{
		}

		__bit_sequence(size_type __desired_count) noexcept(
		     noexcept(__bit_sequence(__desired_count, static_cast<value_type>(false))))
		: __bit_sequence(__desired_count, static_cast<value_type>(false))
		{
		}

		__bit_sequence(size_type __desired_count, value_type __val) noexcept(noexcept(
		     __bit_sequence(__dummy_tag{}, __bit_sequence::_S_efficient_empty_create_sized(__desired_count, __val))))
		: __bit_sequence(__dummy_tag{}, __bit_sequence::_S_efficient_empty_create_sized(__desired_count, __val))
		{
		}

		__bit_sequence(::std::initializer_list<value_type> __il) noexcept(
		     noexcept(__bit_sequence(__il.begin(), __il.end())))
		: __bit_sequence(__il.begin(), __il.end())
		{
		}

		__bit_sequence(const __bit_sequence& __right) = default;

		__bit_sequence(__bit_sequence&& __right) = default;

		// assignment
		__bit_sequence&
		operator=(const __bit_sequence& __right) = default;

		__bit_sequence&
		operator=(__bit_sequence&& __right) = default;

		// modifiers
		void
		reserve(size_type __desired_capacity)
		{
			this->_M_storage_unwrapped().reserve(__desired_capacity);
		}

		__bit_sequence&
		assign(const __bit_sequence& __right)
		{
			return this->operator=(__right);
		}

		__bit_sequence&
		assign(__bit_sequence&& __right)
		{
			return this->operator=(::std::move(__right));
		}

		__bit_sequence&
		assign(::std::initializer_list<value_type> __il)
		{
			clear();
			if (__il.size() == 0)
				{
					return *this;
				}
			this->_M_empty_assign(__il.begin(), __il.end());
			return *this;
		}

		template<typename _Iterator, typename _Sentinel,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_Iterator>>* = nullptr>
		__bit_sequence&
		assign(_Iterator __first, _Sentinel __last)
		{
			clear();
			if (__first == __last)
				{
					return *this;
				}
			this->_M_empty_assign(::std::move(__first), ::std::move(__last));
			return *this;
		}

		__bit_sequence&
		assign(size_type __desired_count, value_type __val)
		{
			clear();
			if (__desired_count == static_cast<size_type>(0))
				{
					return *this;
				}

			this->_M_empty_assign_sized(__desired_count, __val);
			return *this;
		}

		using __base_t::flip;
		using __base_t::reset;
		using __base_t::set;

		void
		push_back(value_type __val)
		{
			using __bit_ref = reference;
			__base_iterator __storage_it;
			if (_M_bit_pos == __binary_digits_v<__base_value_type>)
				{
					// FIXME: use optimized push_front of container,
					// if possible!
					__storage_it = this->_M_storage_unwrapped().insert(
					     this->_M_storage_cend(), static_cast<__base_value_type>(0));
					_M_bit_pos = 0;
				}
			else
				{
					__storage_it = this->_M_storage_end();
					--__storage_it;
				}

			__bit_ref __ref(*__storage_it, _M_bit_pos);
			__ref = __val;

			++_M_bit_pos;
		}

		void
		push_front(value_type __val)
		{
			using __bit_ref = reference;
			if (_M_bit_pos == __binary_digits_v<__base_value_type>)
				{
					// FIXME: use optimized push_front of container,
					// if possible!
					this->_M_storage_unwrapped().insert(
					     this->_M_storage_cend(), static_cast<__base_value_type>(0));
					_M_bit_pos = 0;
				}
			++_M_bit_pos;

			auto __storage_first = this->_M_storage_begin();
			auto __storage_last  = this->_M_storage_end();
			value_type __old_val = __val;
			for (; __storage_first != __storage_last; ++__storage_first)
				{
					__base_reference __ref = *__storage_first;
					__bit_ref __front(__ref, 0);
					__bit_ref __back(__ref, __max_binary_index_v<__base_value_type>);
					__old_val = __back;
					__ref <<= 1;
					__front = __val;
					__val   = __old_val;
				}
		}

		iterator
		insert(const_iterator __where, ::std::initializer_list<value_type> __il)
		{
			return this->insert(::std::move(__where), __il.begin(), __il.end());
		}

		iterator
		insert(const_iterator __where, size_type __desired_count, value_type __val)
		{
			if (__desired_count < static_cast<size_type>(1))
				{
					__base_iterator __nowhere =
					     this->_M_storage_unwrapped().insert(__where.base(), __where.base());
					return iterator(::std::move(__nowhere), __where.position());
				}
			iterator __current_pos = this->insert(::std::move(__where), __val);
			for (size_type __index = 1; __index < __desired_count; ++__index)
				{
					__current_pos = this->insert(::std::move(__current_pos), __val);
				}
			return __current_pos;
		}

		template<typename _Iterator, typename _Sentinel>
		iterator
		insert(const_iterator __where, _Iterator __first, _Sentinel __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_Iterator>::iterator_category;

			if (__first == __last)
				{
					__base_c_iterator __where_base = ::std::move(__where).base();
					__base_iterator __nowhere =
					     __iter_as_mutable_from_begin(__where_base, this->_M_storage_unwrapped());
					return iterator(::std::move(__nowhere), __where.position());
				}

			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag, _ItCategory>)
				{
					return this->_M_source_random_access_insert(
					     ::std::move(__where), ::std::move(__first), ::std::move(__last));
				}
			else
				{
					return this->_M_basic_insert(::std::move(__where), ::std::move(__first), ::std::move(__last));
				}
		}

		iterator
		insert(const_iterator __where, value_type __val)
		{
			if (this->empty())
				{
					push_back(__val);
					return --this->end();
				}
			auto __where_base   = ::std::move(__where).base();
			auto __where_pos    = ::std::move(__where).position();
			auto __storage_last = this->_M_storage_cend();
			if (__where.base() == __storage_last)
				{
					push_back(__val);
					return --this->end();
				}
			auto __storage_before_last = __storage_last;
			--__storage_before_last;
			if (__storage_before_last == __where_base && __where_pos >= this->_M_bit_pos)
				{
					push_back(__val);
					return --this->end();
				}
			if (__where_base == this->_M_storage_cbegin() && __where_pos == 0)
				{
					push_front(__val);
					return this->begin();
				}

			// okay, we are inserting somewhere in the
			// middle of the words ...
			// do we have enough space?
			if (this->_M_bit_pos == __binary_digits_v<__base_value_type>)
				{
					// we need more space for this
					// this may also invalidates old iterators,
					// so we need to re-establish
					// the position iterator we had...
					difference_type __saved_dist = ::std::distance(this->_M_storage_cbegin(), __where_base);
					this->_M_storage_unwrapped().insert(
					     this->_M_storage_cend(), static_cast<__base_value_type>(0));
					this->_M_bit_pos = 0;
					__where_base     = this->_M_storage_cbegin();
					::std::advance(__where_base, __saved_dist);
					__storage_last = this->_M_storage_cend();
				}
			__base_iterator __storage_first = this->_M_storage_begin();
			difference_type __storage_dist  = ::std::distance(__base_c_iterator(__storage_first), __where_base);
			__base_iterator __storage_it    = ::std::next(__storage_first, __storage_dist);
			iterator __insertion_return(__storage_it, __where_pos);

			__base_reference __first_ref = *__storage_it;
			++__storage_it;
			reference __first_insert_target(__first_ref, __where_pos);
			// save potential off-the-edge value
			value_type __old_val = reference(__first_ref, __max_binary_index_v<__base_value_type>);

			// are we not at the MSB edge of a word?
			if (__where_pos != __max_binary_index_v<__base_value_type>)
				{
					// we are not at the edge of a word
					// need to shift pertinent values
					if (__where_pos != 0)
						{
							// we are not at the LSB, shift bits
							__shift_left_preserve_right<__base_value_type>(__first_ref, __where_pos, 1);
						}
					else
						{
							__first_ref <<= 1;
						}
				}
			// write new value
			__first_insert_target = __val;

			for (; __storage_it != __storage_last; ++__storage_it)
				{
					__base_reference __storage_current_ref = *__storage_it;
					value_type __saved = reference(__storage_current_ref, __max_binary_index_v<__base_value_type>);
					__storage_current_ref <<= 1;
					reference(__storage_current_ref, 0) = __old_val;
					__old_val                           = __saved;
				}

			++_M_bit_pos;

			return __insertion_return;
		}

		void
		pop_back()
		{
			if (this->empty())
				{
					return;
				}
			--this->_M_bit_pos;
			if (this->_M_bit_pos == 0)
				{
					this->_M_bit_pos = __binary_digits_v<__base_value_type>;
					// FIXME: use optimized pop_back of container,
					// if possible!
					this->_M_storage_unwrapped().erase(--this->_M_storage_cend());
				}
		}

		void
		pop_front()
		{
			if (this->empty())
				{
					return;
				}
			__base_iterator __storage_first  = this->_M_storage_begin();
			__base_iterator __storage_last   = this->_M_storage_end();
			__base_iterator __old_storage_it = __storage_first;
			(*__old_storage_it) >>= 1;
			++__storage_first;
			for (; __storage_first != __storage_last; ++__storage_first, (void)++__old_storage_it)
				{
					__base_reference __storage_ref = *__storage_first;
					value_type __old_val           = reference(__storage_ref, 0);
					__storage_ref >>= 1;
					reference __old_bit_ref(*__old_storage_it, __max_binary_index_v<__base_value_type>);
					__old_bit_ref = __old_val;
				}
			if (this->_M_bit_pos == 0)
				{
					this->_M_bit_pos = __binary_digits_v<__base_value_type>;
					// FIXME: use optimized pop_front of container,
					// if possible!
					this->_M_storage_unwrapped().erase(--this->_M_storage_cend());
				}
			--this->_M_bit_pos;
		}

		constexpr iterator
		erase(const_iterator __first, const_sentinel __last) noexcept
		{
			if (__first == __last)
				{
					__base_iterator __nowhere = this->_M_storage_unwrapped().erase(__first.base(), __first.base());
					return iterator(::std::move(__nowhere), __first.position());
				}
			if (this->empty())
				{
					return this->end();
				}
			if (__first == this->cbegin() && __last == this->cend())
				{
					clear();
					return this->end();
				}
			// if this is a random access iterator,
			// then size computation is cheap
			// and so is bulk, sized removal
			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag, iterator_category>)
				{
					return this->_M_this_random_access_erase(::std::move(__first), ::std::move(__last));
				}
			else
				{
					return this->_M_basic_erase(::std::move(__first), ::std::move(__last));
				}
		}

		constexpr iterator
		erase(const_iterator __where) noexcept
		{
			if (this->empty())
				{
					return this->end();
				}
			auto __where_base   = ::std::move(__where).base();
			auto __where_pos    = ::std::move(__where).position();
			auto __storage_last = this->_M_storage_cend();
			if (__where_base == __storage_last)
				{
					return this->end();
				}
			--__storage_last;
			if (__storage_last == __where_base)
				{
					if (__where_pos >= this->_M_bit_pos)
						{
							pop_back();
							return this->end();
						}
					else if (this->_M_bit_pos - 1 == __where_pos)
						{
							this->pop_back();
							return this->end();
						}
				}
			if (__where_base == this->_M_storage_cbegin() && __where_pos == 0)
				{
					this->pop_front();
					return this->begin();
				}
			// okay, we actually have to remove old bits now...
			__base_iterator __storage_first = this->_M_storage_begin();
			difference_type __storage_dist  = ::std::distance(__base_c_iterator(__storage_first), __where_base);
			__base_iterator __storage_it    = ::std::next(__storage_first, __storage_dist);

			// put __storage_last back to
			// the end iterator
			++__storage_last;

			// save old bits that will be affected by left shift
			__base_reference __storage_ref = *__storage_it;
			if (__where_pos == 0)
				{
					// no old bits matter: just truncate at the desired position
					__storage_ref >>= 1;
				}
			else
				{
					// sigh... old bits do matter, save, truncate, then restore old bits
					__shift_right_preserve_right<__base_value_type>(__storage_ref, __where_pos - 1, 1);
				}

			// great, now shift literally everything else indiscriminately
			auto __old_storage_it  = __storage_it;
			auto __curr_storage_it = __storage_it;
			++__curr_storage_it;
			for (; __curr_storage_it != __storage_last; ++__curr_storage_it, (void)++__old_storage_it)
				{
					// get current iterator's position
					__base_reference __curr_pos_ref = *__curr_storage_it;
					// get least significant bit that is going to
					// be shift-truncated
					value_type __old_val = reference(__curr_pos_ref, 0);
					// assign it to the MSB of the old word
					reference(*__old_storage_it, __max_binary_index_v<__base_value_type>) = __old_val;
					// shift over
					__curr_pos_ref >>= 1;
				}

			// did we chop off an old word?
			if (_M_bit_pos == 0)
				{
					this->_M_bit_pos = __binary_digits_v<__base_value_type> - 1;
					// destroy it
					--__storage_last;
					bool __storage_last_is_current = __storage_it == __storage_last;
					auto __removed_storage_it      = this->_M_storage_unwrapped().erase(__storage_last);
					if (__storage_last_is_current)
						{
							// the storage we had was removed, we need to return
							// that iterator itself
							// otherwise we have invalidation issues!
							return iterator(::std::move(--__removed_storage_it), __where_pos);
						}
				}
			else
				{
					// no, so just decrement and
					// pretend higher bits don't exist
					--this->_M_bit_pos;
				}
			return iterator(::std::move(__storage_it), __where_pos);
		}

		constexpr void
		clear() noexcept
		{
			this->_M_bit_pos = __binary_digits_v<__base_value_type>;
			this->_M_storage_unwrapped().clear();
		}

		constexpr void
		swap(__bit_sequence& __right) noexcept(::std::is_nothrow_swappable_v<container_type>)
		{
			__adl_swap(this->_M_storage_unwrapped(), __right._M_storage);
			__adl_swap(this->_M_bit_pos, __right._M_bit_pos);
		}

		// observers
		using __base_t::all;
		using __base_t::any;
		using __base_t::count;
		using __base_t::none;
		using __base_t::one_count;
		using __base_t::popcount;
		using __base_t::test;
		using __base_t::zero_count;

		using __base_t::operator[];

		bool
		empty() const
		{
			return __adl_empty(this->_M_storage_unwrapped());
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
			__base_reference __storage_ref = *this->_M_storage_begin();
			return reference(__storage_ref, 0);
		}

		const_reference
		front() const noexcept
		{
			__base_c_reference __storage_ref = *this->_M_storage_cbegin();
			return const_reference(__storage_ref, 0);
		}

		std::add_lvalue_reference_t<_Container>
		base() noexcept
		{
			return this->_M_storage_unwrapped();
		}

		std::add_const_t<std::add_lvalue_reference_t<_Container>>
		base() const noexcept
		{
			return this->_M_storage_unwrapped();
		}

		constexpr size_type
		size() const noexcept
		{
			size_type __word_size = __adl_size(this->_M_storage_unwrapped());
			if (__word_size == 0)
				{
					return 0;
				}
			return (__word_size - 1) * __binary_digits_v<__base_value_type> + this->_M_bit_pos;
		}

		constexpr iterator
		begin() noexcept
		{
			return iterator(this->_M_storage_begin(), 0);
		}

		constexpr sentinel
		end() noexcept
		{
			auto __storage_last = this->_M_storage_end();
			if (this->_M_bit_pos < __binary_digits_v<__base_value_type>)
				{
					--__storage_last;
					return sentinel(::std::move(__storage_last), this->_M_bit_pos);
				}
			return sentinel(::std::move(__storage_last), 0);
		}

		constexpr const_iterator
		begin() const noexcept
		{
			return this->cbegin();
		}

		constexpr const_sentinel
		end() const noexcept
		{
			return this->cend();
		}

		constexpr const_iterator
		cbegin() const noexcept
		{
			return const_iterator(this->_M_storage_begin(), 0);
		}

		constexpr const_sentinel
		cend() const noexcept
		{
			auto __storage_last = this->_M_storage_cend();
			if (this->_M_bit_pos < __binary_digits_v<__base_value_type>)
				{
					--__storage_last;
					return const_sentinel(::std::move(__storage_last), this->_M_bit_pos);
				}
			return const_sentinel(::std::move(__storage_last), 0);
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator==(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) ==
					       static_cast<const typename _Right::__base_t&>(__right);
				}
			return ::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator!=(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) !=
					       static_cast<const typename _Right::__base_t&>(__right);
				}
			return !::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator<(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) <
					       static_cast<const typename _Right::__base_t&>(__right);
				}
			return ::std::lexicographical_compare(
			     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::less<bool>());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator<=(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) <=
					       static_cast<const typename _Right::__base_t&>(__right);
				}

			return !::std::lexicographical_compare(
			     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::greater<bool>());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator>(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) >
					       static_cast<const typename _Right::__base_t&>(__right);
				}
			return ::std::lexicographical_compare(
			     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::greater<bool>());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator>=(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) >=
					       static_cast<const typename _Right::__base_t&>(__right);
				}

			return !::std::lexicographical_compare(
			     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::less<bool>());
		}

	private:
		size_type _M_bit_pos = 0;

		__bit_sequence(__dummy_tag, ::std::pair<container_type, size_type> __container_position) noexcept(
		     noexcept(__base_t(::std::move(__container_position.first))))
		: __base_t(::std::move(__container_position.first)), _M_bit_pos(__container_position.second)
		{
			// avoids inefficiencies by using a static method to create needed data and
			// delegating to some internal constructor which can properly
			// init the data
			// C++ needs a better constructor story, or we'll keep
			// having spammy constructor delegation
			// like this for all eternity...
			// but what do I know? I'm just a GSoCer. c:
		}

		template<typename _Iterator, typename _Sentinel>
		static constexpr void
		_S_efficient_empty_assign_into(
		     _Iterator __first, _Sentinel __last, __range_ref& __storage, size_type& __bit_pos)
		{
			// welp...
			// it's bulk, so only medium slow
			// instead of slow-slow?
			size_type __bit_counter        = 0;
			size_type __modulo_bit_counter = 0;
			__base_iterator __storage_it =
			     __storage.insert(__adl_cend(__storage), static_cast<__base_value_type>(0));
			iterator __it(::std::move(__storage_it), 0);
			for (; __first != __last; ++__first, (void)++__bit_counter, (void)++__modulo_bit_counter, (void)++__it)
				{
					if (__modulo_bit_counter == __binary_digits_v<__base_value_type>)
						{
							__base_iterator __storage_it =
							     __storage.insert(__adl_cend(__storage), static_cast<__base_value_type>(0));
							__it                 = iterator(::std::move(__storage_it), 0);
							__modulo_bit_counter = 0;
						}
					*__it = *__first;
				}
			__bit_pos = __modulo_bit_counter;
		}

		static constexpr void
		_S_efficient_empty_assign_into_sized(
		     size_type __desired_count, value_type __val, __range_ref& __storage, size_type& __bit_pos)
		{
			size_type __word_insertion = (__desired_count / __binary_digits_v<__base_value_type>);
			__bit_pos                  = (__desired_count % __binary_digits_v<__base_value_type>);
			if (__bit_pos == 0)
				{
					__bit_pos = __binary_digits_v<__base_value_type>;
				}
			else
				{
					++__word_insertion;
				}

			__storage.assign(__word_insertion,
			     __val ? static_cast<__base_value_type>(::std::numeric_limits<__integral_base_value_type>::max())
			           : static_cast<__base_value_type>(0));
		}

		template<typename _Iterator, typename _Sentinel>
		constexpr void
		_M_empty_assign(_Iterator __first, _Sentinel __last)
		{
			decltype(auto) __storage = this->_M_storage_unwrapped();
			_S_efficient_empty_assign_into(::std::move(__first), ::std::move(__last), __storage, this->_M_bit_pos);
		}

		constexpr void
		_M_empty_assign_sized(size_type __desired_count, value_type __val)
		{
			decltype(auto) __storage = this->_M_storage_unwrapped();
			_S_efficient_empty_assign_into_sized(__desired_count, __val, __storage, this->_M_bit_pos);
		}

		template<typename _Iterator, typename _Sentinel>
		static constexpr ::std::pair<container_type, size_type>
		_S_efficient_empty_create(_Iterator __first, _Sentinel __last)
		{
			if (__first == __last)
				{
					return { container_type(), static_cast<size_type>(__binary_digits_v<__base_value_type>) };
				}

			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag,
			                   typename ::std::iterator_traits<_Iterator>::iterator_category>)
				{
					size_type __desired_count  = ::std::distance(__first, __last);
					size_type __word_insertion = (__desired_count / __binary_digits_v<__base_value_type>);
					size_type __bit_pos        = (__desired_count % __binary_digits_v<__base_value_type>);
					if (__bit_pos == 0)
						{
							__bit_pos = __binary_digits_v<__base_value_type>;
						}
					else
						{
							++__word_insertion;
						}


					container_type __storage(__word_insertion, static_cast<__base_value_type>(0));
					__base_iterator __storage_it = __storage.begin();
					iterator __copy_it(::std::move(__storage_it), 0);
					::std::copy_n(__first, __desired_count, __copy_it);
					return { ::std::move(__storage), __bit_pos };
				}
			else
				{
					container_type __storage;
					size_type __bit_pos;
					_S_efficient_empty_assign_into(
					     ::std::move(__first), ::std::move(__last), __storage, __bit_pos);
					return { ::std::move(__storage), __bit_pos };
				}
		}

		static constexpr ::std::pair<container_type, size_type>
		_S_efficient_empty_create_sized(size_type __desired_count, value_type __val)
		{
			if (__desired_count < 1)
				{
					return { container_type(), static_cast<size_type>(__binary_digits_v<__base_value_type>) };
				}
			size_type __word_insertion = (__desired_count / __binary_digits_v<__base_value_type>);
			size_type __bit_pos        = (__desired_count % __binary_digits_v<__base_value_type>);
			if (__bit_pos == 0)
				{
					__bit_pos = __binary_digits_v<__base_value_type>;
				}
			else
				{
					++__word_insertion;
				}


			container_type __storage(__word_insertion,
			     __val ? static_cast<__base_value_type>(::std::numeric_limits<__integral_base_value_type>::max())
			           : static_cast<__base_value_type>(0));
			return { ::std::move(__storage), __bit_pos };
		}

		template<typename _Iterator, typename _Sentinel>
		constexpr iterator
		_M_source_random_access_insert(const_iterator __where, _Iterator __first, _Sentinel __last)
		{
			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag, iterator_category>)
				{
					difference_type __insert_bit_count = ::std::distance(__first, __last);
					return this->_M_this_and_source_random_access_insert(
					     __insert_bit_count, ::std::move(__where), ::std::move(__first), ::std::move(__last));
				}
			else
				{
					return this->_M_basic_insert(::std::move(__where), ::std::move(__first), ::std::move(__last));
				}
		}

		template<typename _Iterator, typename _Sentinel>
		constexpr iterator
		_M_this_and_source_random_access_insert(
		     difference_type __insert_bit_count, const_iterator __where, _Iterator __first, _Sentinel __last)
		{
			size_type __where_pos        = __where.position();
			difference_type __where_dist = __where - this->cbegin();
			if (__where_pos == 0)
				{
					// we can copy literally everything
					// without individual bit management
					__base_c_iterator __where_base = ::std::move(__where).base();
					difference_type __insert_word_count =
					     __insert_bit_count / __binary_digits_v<__base_value_type>;
					difference_type __insert_bit_shift = __insert_bit_count % __binary_digits_v<__base_value_type>;
					iterator __shift_insertion_target  = this->_M_copy_words_if_necessary(
                              __insert_word_count, __where_dist, __where_base, __first);
					if (__insert_bit_shift > 0)
						{
							this->_M_basic_insert(__shift_insertion_target, __first, __last);
						}
					iterator __ret = this->begin();
					__ret += __where_dist;
					return __ret;
				}
			// okay now we're back to the boring implementation...
			// first, shove in as many bits until we get to
			// a word boundary using basic insert

			// FIXME: optimize basic less-than-word bulk insertions
			difference_type __bits_to_boundary = __binary_digits_v<__base_value_type> - __where_pos;
			if (__bits_to_boundary >= __insert_bit_count)
				{
					_Iterator __boundary_last = __first;
					__boundary_last += __insert_bit_count;
					return this->_M_basic_insert(
					     ::std::move(__where), ::std::move(__first), ::std::move(__boundary_last));
				}
			iterator __boundary_it =
			     this->_M_basic_insert(::std::move(__where), __first, __first + __bits_to_boundary);
			__base_iterator __boundary_base_it = ::std::move(__boundary_it).base();
			++__boundary_base_it;

			// now insert and copy words, which require no shifts at all
			difference_type __leftover_bits       = __insert_bit_count - __bits_to_boundary;
			difference_type __leftover_words      = __leftover_bits / __binary_digits_v<__base_value_type>;
			difference_type __leftover_words_bits = __leftover_words * __binary_digits_v<__base_value_type>;
			__base_iterator __insertion_point = this->_M_storage_unwrapped().insert(::std::move(__boundary_base_it),
			     static_cast<size_type>(__leftover_words), static_cast<__base_value_type>(0));
			__first += __bits_to_boundary;
			iterator __wheret_word_it =
			     ::std::copy_n(__first, __leftover_words_bits, iterator(__insertion_point, 0));

			// finally, handle the last bits...
			// FIXME: handle bulk less-than-word insertions
			__leftover_bits -= __leftover_words_bits;
			if (__leftover_bits > 0)
				{
					__first += __leftover_words_bits;
					this->_M_basic_insert(__wheret_word_it, __first, __last);
				}
			iterator __ret = this->begin();
			__ret += __where_dist;
			return __ret;
		}

		template<typename _Iterator>
		constexpr iterator
		_M_copy_words_if_necessary(difference_type __insert_word_count, difference_type __where_dist,
		     __base_c_iterator __where_base, _Iterator& __first)
		{
			if (__insert_word_count > 0)
				{
					difference_type __where_base_dist = __where_dist / __binary_digits_v<__base_value_type>;
					difference_type __insert_word_bit_count =
					     __insert_word_count * __binary_digits_v<__base_value_type>;
					__base_iterator __storage_it = this->_M_storage_unwrapped().insert(::std::move(__where_base),
					     static_cast<size_type>(__insert_word_count), static_cast<__base_value_type>(0));
					::std::advance(__storage_it, __where_base_dist);
					iterator __insertion_point = iterator(__storage_it, 0);
					iterator __wheret_copy_it = ::std::copy_n(__first, __insert_word_bit_count, __insertion_point);
					__first += __insert_word_bit_count;
					return __wheret_copy_it;
				}
			return iterator(__iter_as_mutable_from_begin(__where_base, this->_M_storage_unwrapped()), 0);
		}

		template<typename _Iterator, typename _Sentinel>
		constexpr iterator
		_M_basic_insert(const_iterator __where, _Iterator __first, _Sentinel __last)
		{
			bool __is_storage_empty = this->empty();
			if (__is_storage_empty)
				{
					for (; __first != __last; ++__first)
						{
							this->push_back(*__first);
						}
					return this->begin();
				}
			// we can only check cbegin, because
			// we can't save an iterator for
			// wherever "end" is before we start
			// shoveling things in (yay, iterator invalidation...)
			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag, iterator_category>)
				{
					// if we're inserting at the end,
					// and we are random access,
					// we can get a distance
					// and then use it later on to return the
					// insertion point properly from this method
					if (__where == this->cend())
						{
							difference_type __insertion_point_at = static_cast<difference_type>(this->size());
							for (; __first != __last; ++__first)
								{
									this->push_back(*__first);
								}
							return ::std::next(this->begin(), __insertion_point_at);
						}
				}
			if (__where == this->cbegin())
				{
					for (; __first != __last; ++__first)
						{
							this->push_front(*__first);
						}
					return this->begin();
				}
			if constexpr (__is_iterator_category_or_better_v<::std::bidirectional_iterator_tag, iterator_category> &&
			              __weakly_decrementable_v<_Sentinel>)
				{
					--__last;
					bool __the_last_time   = __last == __first;
					iterator __current_pos = this->insert(::std::move(__where), *__last);
					for (; !__the_last_time;)
						{
							--__last;
							__the_last_time = __last == __first;
							__current_pos   = this->insert(::std::move(__current_pos), *__last);
						}
					return __current_pos;
				}
			else
				{
					iterator __current_pos = this->insert(::std::move(__where), *__first);
					++__first;
					for (; __first != __last; ++__first)
						{
							++__current_pos;
							__current_pos = this->insert(::std::move(__current_pos), *__first);
						}
					return __current_pos;
				}
		}

		constexpr __base_iterator
		_M_maybe_storage_bulk_erase(
		     __base_c_iterator& __first_base_it, size_type __first_position, difference_type __erase_word_count)
		{
			if (__erase_word_count > static_cast<difference_type>(0))
				{
					return this->_M_storage_bulk_erase(__first_base_it, __first_position, __erase_word_count);
				}
			else
				{
					return __iter_as_mutable_from_begin(__first_base_it, this->_M_storage_unwrapped());
				}
		}

		constexpr __base_iterator
		_M_storage_bulk_erase(__base_c_iterator& __first_base_it, size_type __first_position,
		     difference_type __erase_word_count) noexcept
		{
			// are we on a boundary?
			if (__first_position == 0)
				{
					// perfectly aligned on word boundary,
					// no half-word to shift:
					// remove indiscriminately
					auto __storage_it =
					     this->_M_storage_unwrapped().erase(__first_base_it, __first_base_it + __erase_word_count);
					return __storage_it;
				}

			// Not perfectly aligned...
			// attempt to preserve bits on boundaries of removal
			__base_c_iterator __last_base_it = __first_base_it + (__erase_word_count);
			// if the last is equal to end, we're just removing everything aren't we?
			if (__last_base_it == this->_M_storage_cend())
				{
					return this->_M_storage_unwrapped().erase(__first_base_it, __last_base_it);
				}

			// bulk-remove the parts we do not care about
			// and merge tips into a single word that
			// we can perform shifts on later
			// save msb word for later merging into non-removed part, for when the shift happens
			__base_value_type __lsb_word_chunk = *__first_base_it;
			__base_iterator __storage_it       = this->_M_storage_unwrapped().erase(__first_base_it, __last_base_it);
			__base_reference __msb_word_chunk_ref = *__storage_it;
			__base_value_type __msb_word_chunk    = __msb_word_chunk_ref;
			__msb_word_chunk_ref = __merge_bits_at(__lsb_word_chunk, __msb_word_chunk, __first_position);
			return __storage_it;
		}

		constexpr iterator
		_M_this_random_access_erase(const_iterator __first, const_sentinel __last) noexcept
		{
			// early check: are we deleting
			// everything?
			if (__first == this->begin() && __last == this->cend())
				{
					clear();
					return this->end();
				}
			difference_type __erase_bit_count  = ::std::distance(__first, __last);
			difference_type __erase_word_count = __erase_bit_count / __binary_digits_v<__base_value_type>;
			difference_type __erase_bit_shift  = __erase_bit_count % __binary_digits_v<__base_value_type>;
			__base_c_iterator __first_base_it  = __first.base();
			size_type __first_position         = __first.position();
			__base_iterator __first_storage_it =
			     _M_maybe_storage_bulk_erase(__first_base_it, __first_position, __erase_word_count);
			// are we out of bits?
			if (__erase_bit_shift == 0)
				{
					// then we're already done
					return iterator(::std::move(__first_storage_it), __first_position);
				}
			// we are not out of bits:
			// shift down the first, then do the rest
			__base_reference __first_storage_ref = *__first_storage_it;
			if (__first_position == 0)
				{
					__first_storage_ref >>= __erase_bit_shift;
				}
			else
				{
					// bit preserver is inclusive: subtract 1
					size_type __bit_pivot = __first_position - 1;
					__shift_right_preserve_right<__base_value_type>(
					     __first_storage_ref, __bit_pivot, __erase_bit_shift);
				}
			// shift down all other bits now
			__base_iterator __storage_last   = this->_M_storage_end();
			__base_iterator __storage_it     = __first_storage_it;
			__base_iterator __old_storage_it = __first_storage_it;

			++__storage_it;
			for (; __storage_it != __storage_last; ++__storage_it, (void)++__old_storage_it)
				{
					__base_reference __storage_ref     = *__storage_it;     // msb
					__base_reference __old_storage_ref = *__old_storage_it; // lsb
					__old_storage_ref                  = __replace_most_significant_bits_from<__base_value_type>(
                              __old_storage_ref, __storage_ref, __erase_bit_shift);
					__storage_ref >>= __erase_bit_shift;
				}
			// update bit count
			if (this->_M_bit_pos > static_cast<size_type>(__erase_bit_shift))
				{
					// simple rollback
					this->_M_bit_pos -= static_cast<size_type>(__erase_bit_shift);
				}
			else
				{
					// we're going back over a word,
					// so we need to remove the old word
					auto __erase_target = this->_M_storage_unwrapped().cend();
					--__erase_target;
					this->_M_storage_unwrapped().erase(__erase_target);
					// then adjust the bit position
					this->_M_bit_pos =
					     __binary_digits_v<__base_value_type> - (__erase_bit_shift - this->_M_bit_pos);
				}
			return iterator(::std::move(__first_storage_it), __first_position);
		}

		constexpr iterator
		_M_basic_erase(const_iterator __first, const_sentinel __last) noexcept
		{
			// we already checked if we were empty
			--__last;
			// is this the first iterator?
			// if so, this is our last iteration
			bool __the_last_time   = __last == __first;
			iterator __current_pos = this->erase(__last);
			for (; !__the_last_time;)
				{
					// __last is currently invalid
					// because we just killed it...
					__last = ::std::move(__current_pos);
					--__last;
					__the_last_time = __last == __first;
					__current_pos   = this->erase(__last);
				}
			return __current_pos;
		}
	};

} // namespace ITSY_BITSY_SOURCE_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef ITSY_BITSY_SOURCE_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // ITSY_BITSY_DETAIL_BIT_SEQUENCE_HPP
