#ifndef ITSY_BITSY_DETAIL_BIT_VIEW_H
#define ITSY_BITSY_DETAIL_BIT_VIEW_H 1

#if (defined(_MSC_VER)) || (defined(__cplusplus) && __cplusplus >= 201703L)

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
#else
#include <itsy/detail/bit_iterator.h>
#include <itsy/detail/is_detected.h>
#endif

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <utility>
#include <algorithm>


#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{
	template<typename __Type>
	using __has_size_function = decltype(::std::declval<__Type>().size());

	template<typename __R>
	class __word_bit_extents
	{
	private:
		using __R_ref           = std::add_lvalue_reference_t<__R>;
		using __base_iterator   = decltype(::std::begin(::std::declval<__R_ref>()));
		using __word_type       = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;

	public:
		static constexpr __size_type
		begin_position(const __R&) noexcept
		{
			return 0;
		}

		static constexpr __size_type
		end_position(const __R& __container) noexcept
		{
			if constexpr (::std::is_array_v<__R>)
				{
					return static_cast<__size_type>(
					  ::std::size(__container) * __binary_digits_v<__word_type>);
				}
			else if constexpr (__is_detected_v<__has_size_function, const __R&>)
				{
					return static_cast<__size_type>(__container.size() * __binary_digits_v<__word_type>);
				}
			else
				{
					return static_cast<__size_type>(
					  ::std::distance(::std::cbegin(__container), ::std::cend(__container)) *
					  __binary_digits_v<__word_type>);
				}
		}
	};

	template<::std::size_t __begin_bit, ::std::size_t __end_bit>
	class __static_bit_extents
	{
	public:
		template<typename __Range>
		static constexpr ::std::size_t
		begin_position(const __Range&) noexcept
		{
			return __begin_bit;
		}

		template<typename __Range>
		static constexpr ::std::size_t
		end_position(const __Range&) noexcept
		{
			return __end_bit;
		}
	};

	template<typename __R>
	class __dynamic_bit_extents_for
	{
	private:
		using __R_ref           = std::add_lvalue_reference_t<__R>;
		using __base_iterator   = decltype(::std::begin(::std::declval<__R_ref>()));
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __value_type      = typename ::std::iterator_traits<__base_iterator>::value_type;

	public:
		__size_type first;
		__size_type last;

		__dynamic_bit_extents_for(const __R_ref __range) noexcept
		: first(0), last(::std::size(__range) * __binary_digits_v<__value_type>)
		{
		}

		__dynamic_bit_extents_for(__size_type __first, __size_type __last) noexcept
		: first(__first), last(__last)
		{
		}

		constexpr __size_type
		begin_position(const __R&) const noexcept
		{
			return first;
		}

		constexpr __size_type
		end_position(const __R&) const noexcept
		{
			return last;
		}
	};

	class __dynamic_bit_extents
	{
	public:
		::std::size_t first;
		::std::size_t last;

		template<typename __Range>
		__dynamic_bit_extents(const __Range& __range) noexcept
		: first(0)
		, last(::std::size(__range) *
		       __binary_digits_v<
		         typename ::std::iterator_traits<decltype(::std::begin(__range))>::value_type>)
		{
		}

		__dynamic_bit_extents(::std::size_t __first, ::std::size_t __last) noexcept
		: first(__first), last(__last)
		{
		}

		template<typename __Range>
		constexpr ::std::size_t
		begin_position(const __Range&) const noexcept
		{
			return first;
		}

		template<typename __Range>
		constexpr ::std::size_t
		end_position(const __Range&) const noexcept
		{
			return last;
		}
	};

	template<typename>
	struct __is_word_bit_extents : ::std::false_type
	{
	};

	template<typename __Range>
	struct __is_word_bit_extents<__word_bit_extents<__Range>> : ::std::true_type
	{
	};

	template<typename __Type>
	inline constexpr bool __is_word_bit_extents_v = __is_word_bit_extents<__Type>::value;

	template<typename __Type>
	struct __is_word_or_static_bit_extents : __is_word_bit_extents<__Type>
	{
	};

	template<::std::size_t __First, ::std::size_t __Last>
	struct __is_word_or_static_bit_extents<__static_bit_extents<__First, __Last>> : ::std::true_type
	{
	};

	template<typename __Type>
	inline constexpr bool __is_word_or_static_bit_extents_v =
	  __is_word_or_static_bit_extents<__Type>::value;

	template<typename __R, typename __Extents = __word_bit_extents<__R>>
	class __bit_view
	{
	private:
		template<typename, typename>
		friend class __bit_view;
		template<typename>
		friend class __basic_dynamic_bitset;

		using __R_ref = std::add_lvalue_reference_t<__R>;

		using __base_iterator    = decltype(::std::begin(::std::declval<__R_ref>()));
		using __base_sentinel    = decltype(::std::end(::std::declval<__R_ref>()));
		using __base_c_iterator  = decltype(::std::cbegin(::std::declval<__R_ref>()));
		using __base_c_sentinel  = decltype(::std::cend(::std::declval<__R_ref>()));
		using __base_pointer     = typename ::std::iterator_traits<__base_iterator>::pointer;
		using __base_reference   = typename ::std::iterator_traits<__base_iterator>::reference;
		using __base_c_pointer   = typename ::std::iterator_traits<__base_c_iterator>::pointer;
		using __base_c_reference = typename ::std::iterator_traits<__base_c_iterator>::reference;
		using __iterator         = __bit_iterator<__base_iterator>;
		using __sentinel         = __bit_iterator<__base_sentinel>;
		using __c_iterator       = __bit_iterator<__base_c_iterator>;
		using __c_sentinel       = __bit_iterator<__base_c_sentinel>;
		using __word_type        = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __non_enum_word_type = __any_to_underlying_t<__word_type>;
		using __storage_type     = __R;
		using __reference        = __bit_reference<__base_reference, __word_type>;
		using __const_reference  = __bit_reference<__base_c_reference, __word_type>;

		__Extents _M_extents;
		__storage_type _M_storage;

	public:
		using difference_type   = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using size_type         = ::std::make_unsigned_t<difference_type>;
		using value_type        = bool;
		using reference         = __reference;
		using const_reference   = __const_reference;
		using pointer           = __bit_pointer<__base_pointer>;
		using const_pointer     = __bit_pointer<__base_c_pointer>;
		using iterator_category = typename ::std::iterator_traits<__base_iterator>::iterator_category;
		// TODO: strengthen guarantees by checking for `iterator_concept`
		// on iterator_traits
		using iterator_concept = iterator_category;
		using iterator         = __iterator;
		using sentinel         = __sentinel;
		using const_iterator   = __c_iterator;
		using const_sentinel   = __c_sentinel;
		using range_type       = __R;
		using extents          = __Extents;

	private:
		template<typename __Right>
		inline static constexpr bool __is_directly_comparable =
		  ::std::is_unsigned_v<__non_enum_word_type>&& ::std::is_unsigned_v<
		    typename __Right::__non_enum_word_type>&& ::std::is_same_v<range_type,
		    typename __Right::range_type>&& ::std::is_same_v<extents, typename __Right::extents>&&
		    __is_word_bit_extents_v<extents>&& __is_word_bit_extents_v<typename __Right::extents>;

	public:
		template<typename __Arg, typename... __Args,
		  ::std::enable_if_t<
		    !__is_same_no_cvref_v<__bit_view, __Arg> && !__is_same_no_cvref_v<extents, __Arg>, void*> =
		    nullptr>
		__bit_view(__Arg&& __arg, __Args&&... __args) noexcept(
		  ::std::is_nothrow_constructible_v<range_type, __Arg,
		    __Args...>&& ::std::is_nothrow_default_constructible_v<extents>)
		: _M_extents(), _M_storage(::std::forward<__Arg>(__arg), ::std::forward<__Args>(__args)...)
		{
		}

		template<typename... __Args>
		__bit_view(extents __extents, __Args&&... __args) noexcept(
		  ::std::is_nothrow_constructible_v<range_type,
		    __Args...>&& ::std::is_nothrow_move_constructible_v<extents>)
		: _M_extents(std::move(__extents)), _M_storage(::std::forward<__Args>(__args)...)
		{
		}

		__bit_view(const __bit_view& __right) = default;
		__bit_view(__bit_view&& __right)      = default;

		__bit_view&
		operator=(const __bit_view& __right) = default;
		__bit_view&
		operator=(__bit_view&& __right) = default;

		// modifiers
		constexpr reference operator[](difference_type __n) noexcept
		{
			auto __it = this->begin();
			__it += __n;
			return *__it;
		}

		constexpr __const_reference operator[](difference_type __n) const noexcept
		{
			auto __it = this->cbegin();
			__it += __n;
			return *__it;
		}

		constexpr void
		set(size_type __pos = 0, bool __val = true) noexcept
		{
			auto it = begin();
			::std::advance(it, __pos);
			*it = __val;
		}

		constexpr void
		set(size_type __pos, size_type __len, bool __val = true) noexcept
		{
			auto it = begin();
			for (; __len-- > 0; ++it)
				{
					*it = __val;
				}
		}

		constexpr void
		flip(size_type __pos = 0) noexcept
		{
			auto it = begin();
			::std::advance(it, __pos);
			auto ref = *it;
			ref      = !static_cast<bool>(ref);
		}

		constexpr void
		flip(size_type __pos, size_type __len) noexcept
		{
			auto it = begin();
			for (; __len-- > 0; ++it)
				{
					auto ref = *it;
					ref      = !static_cast<bool>(ref);
				}
		}

		constexpr iterator
		begin() noexcept
		{
			if constexpr (__is_word_bit_extents_v<extents>)
				{
					return iterator(::std::begin(this->_M_storage), 0);
				}
			else
				{
					auto __bit_distance = this->_M_extents.begin_position(this->_M_storage);
					auto __first        = iterator(::std::begin(this->_M_storage));
					__first += __bit_distance;
					return __first;
				}
		}

		constexpr sentinel
		end() noexcept
		{
			if constexpr (__is_word_bit_extents_v<extents>)
				{
					return const_sentinel(::std::end(this->_M_storage), 0);
				}
			else
				{
					auto __bit_distance = this->_M_extents.end_position(this->_M_storage);
					auto __last         = const_iterator(::std::begin(this->_M_storage));
					__last += __bit_distance;
					return __last;
				}
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

			if constexpr (__is_word_bit_extents_v<extents>)
				{
					return const_iterator(::std::cbegin(this->_M_storage), 0);
				}
			else
				{
					auto __bit_distance = this->_M_extents.begin_position(this->_M_storage);
					auto __first        = const_iterator(::std::cbegin(this->_M_storage));
					__first += __bit_distance;
					return __first;
				}
		}

		constexpr const_sentinel
		cend() const noexcept
		{
			if constexpr (__is_word_bit_extents_v<extents>)
				{
					return const_sentinel(::std::cend(this->_M_storage), 0);
				}
			else
				{
					auto __bit_distance = this->_M_extents.end_position(this->_M_storage);
					auto __last         = const_iterator(::std::cbegin(this->_M_storage));
					__last += __bit_distance;
					return __last;
				}
		}

		// observers
		bool
		empty() const
		{
			if constexpr (__is_word_bit_extents_v<extents>)
				{
					return ::std::empty(this->_M_storage);
				}
				else 
				{
					return this->_M_extents.begin_position(this->_M_storage) == this->_M_extents.end_position(this->_M_storage);
				}
		}

		constexpr const __R&
		base() const& noexcept
		{
			return _M_storage;
		}

		constexpr __R&
		  base() &
		  noexcept
		{
			return _M_storage;
		}

		constexpr __R&&
		  base() &&
		  noexcept
		{
			return ::std::move(_M_storage);
		}

		constexpr bool
		test(difference_type __pos) const noexcept
		{
			return *::std::next(cbegin(), __pos);
		}

		constexpr difference_type
		count() const noexcept
		{
			return static_cast<difference_type>(size());
		}

		constexpr size_type
		count(bool __value) const noexcept
		{
			std::size_t __count = 0;
			for (const auto& __val : *this)
				{
					__count += (static_cast<bool>(__val) == __value) ? 1 : 0;
				}
			return __count;
		}

		constexpr size_type
		population_count() const noexcept
		{
			return count(true);
		}

		constexpr bool
		all() const noexcept
		{
			const __word_type __all_val = ~__word_type{};
			for (const auto& __val : _M_storage)
				{
					if (__val == __all_val)
						{
							continue;
						}
					return false;
				}
			return true;
		}

		constexpr bool
		any() const noexcept
		{
			const __word_type __zero_val{};
			for (const auto& __val : _M_storage)
				{
					if (__val == __zero_val)
						{
							continue;
						}
					return true;
				}
			return false;
		}

		constexpr bool
		none() const noexcept
		{
			const __word_type __zero_val{};
			for (const auto& __val : _M_storage)
				{
					if (__val == __zero_val)
						{
							continue;
						}
					return false;
				}
			return true;
		}

		constexpr size_type
		size() const noexcept
		{
			return this->_M_extents.end_position(this->_M_storage) -
			       this->_M_extents.begin_position(this->_M_storage);
		}

		template<typename __RightR, typename __RightEx>
		friend constexpr bool
		operator==(const __bit_view& __left, const __bit_view<__RightR, __RightEx>& __right)
		{
			using __Left  = __bit_view;
			using __Right = __bit_view<__RightR, __RightEx>;
			if constexpr (__Left::__is_directly_comparable<__Right>)
				{
					return __left._M_storage == __right._M_storage;
				}
			else
				{
					auto __left_size  = __left.size();
					auto __right_size = __right.size();
					if (__left_size != __right_size)
						{
							return false;
						}
					if constexpr (std::is_same_v<typename __Left::__word_type,
					                typename __Right::__word_type> &&
					              __is_word_bit_extents_v<typename __Left::extents> &&
					              __is_word_bit_extents_v<typename __Right::extents>)
						{
							auto __left_it0  = ::std::cbegin(__left._M_storage);
							auto __left_it1  = ::std::cend(__left._M_storage);
							auto __right_it0 = ::std::cbegin(__right._M_storage);
							auto __right_it1 = ::std::cend(__right._M_storage);
							return ::std::equal(__left_it0, __left_it1, __right_it0, __right_it1);
						}
					else
						{
							auto __left_it0  = __left.cbegin();
							auto __left_it1  = __left.cend();
							auto __right_it0 = __right.cbegin();
							auto __right_it1 = __right.cbegin();
							return ::std::equal(
							  __left_it0, __left_it1, __right_it0, __right_it1, std::equal_to<bool>());
						}
				}
		}

		template<typename __RightR, typename __RightEx>
		friend constexpr bool
		operator!=(const __bit_view& __left, const __bit_view<__RightR, __RightEx>& __right)
		{
			using __Left  = __bit_view;
			using __Right = __bit_view<__RightR, __RightEx>;
			if constexpr (__Left::__is_directly_comparable<__Right>)
				{
					return __left._M_storage != __right._M_storage;
				}
			else
				{
					auto __left_size  = __left.size();
					auto __right_size = __right.size();
					if (__left_size == __right_size)
						{
							if constexpr (std::is_same_v<typename __Left::__word_type,
							                typename __Right::__word_type> &&
							              __is_word_bit_extents_v<typename __Left::extents> &&
							              __is_word_bit_extents_v<typename __Right::extents>)
								{
									auto __left_it0  = ::std::cbegin(__left._M_storage);
									auto __left_it1  = ::std::cend(__left._M_storage);
									auto __right_it0 = ::std::cbegin(__right._M_storage);
									auto __right_it1 = ::std::cend(__right._M_storage);
									return !::std::equal(__left_it0, __left_it1, __right_it0, __right_it1);
								}
							else
								{
									auto __left_it0  = __left.cbegin();
									auto __left_it1  = __left.cend();
									auto __right_it0 = __right.cbegin();
									auto __right_it1 = __right.cbegin();
									return !::std::equal(
									  __left_it0, __left_it1, __right_it0, __right_it1, std::equal_to<bool>());
								}
						}
					return false;
				}
		}

		template<typename __RightR, typename __RightEx>
		friend constexpr bool
		operator<(const __bit_view& __left, const __bit_view<__RightR, __RightEx>& __right)
		{
			using __Left  = __bit_view;
			using __Right = __bit_view<__RightR, __RightEx>;
			if constexpr (__Left::__is_directly_comparable<__Right>)
				{
					return __left._M_storage < __right._M_storage;
				}
			else
				{
					auto __leftfirst = __left.cbegin();
					auto __leftlast =  __left.cend();
					auto __rightfirst = __right.cbegin();
					auto __rightlast =  __right.cend();
					return ::std::lexicographical_compare(
					  std::move(__leftfirst), std::move(__leftlast), std::move(__rightfirst), std::move(__rightlast), std::less<bool>());
				}
		}

		template<typename __RightR, typename __RightEx>
		friend constexpr bool
		operator<=(const __bit_view& __left, const __bit_view<__RightR, __RightEx>& __right)
		{
			using __Left  = __bit_view;
			using __Right = __bit_view<__RightR, __RightEx>;
			if constexpr (__Left::__is_directly_comparable<__Right>)
				{
					return __left._M_storage <= __right._M_storage;
				}
			else
				{
					return !(__left > __right);
				}
		}

		template<typename __RightR, typename __RightEx>
		friend constexpr bool
		operator>(const __bit_view& __left, const __bit_view<__RightR, __RightEx>& __right)
		{
			using __Left  = __bit_view;
			using __Right = __bit_view<__RightR, __RightEx>;
			if constexpr (__Left::__is_directly_comparable<__Right>)
				{
					return __left._M_storage > __right._M_storage;
				}
			else
				{
					return ::std::lexicographical_compare(
					  __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), std::greater<bool>());
				}
		}

		template<typename __RightR, typename __RightEx>
		friend constexpr bool
		operator>=(const __bit_view& __left, const __bit_view<__RightR, __RightEx>& __right)
		{
			using __Left         = __bit_view;
			using __Right        = __bit_view<__RightR, __RightEx>;
			if constexpr (__Left::__is_directly_comparable<__Right>)
				{
					return __left._M_storage >= __right._M_storage;
				}
			else
				{
					return !(__left < __right);
				}
		}

	private:
		size_type
		_M_bit_distance() const
		{
			return this->_M_extents.end_position(this->_M_storage) -
			       this->_M_extents.begin_position(this->_M_storage);
		}
	};

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_BIT_VIEW_H
