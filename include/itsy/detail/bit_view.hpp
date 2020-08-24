// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#pragma once

#ifndef ITSY_BITSY_DETAIL_BIT_VIEW_HPP
#define ITSY_BITSY_DETAIL_BIT_VIEW_HPP 1

#include <itsy/detail/algorithm.hpp>
#include <itsy/detail/bit_operations.hpp>
#include <itsy/detail/bit_iterator.hpp>
#include <itsy/detail/type_traits.hpp>

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <utility>
#include <algorithm>


namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	template<typename _Container>
	class __word_bit_bounds
	{
	private:
		using __container_type  = __unwrap_t<_Container>;
		using __base_iterator   = decltype(__adl_begin(::std::declval<__container_type>()));
		using __base_value_type = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;

	public:
		static constexpr __size_type
		begin_position(const __container_type&) noexcept
		{
			return 0;
		}

		static constexpr __size_type
		end_position(const __container_type& __container) noexcept
		{
			if constexpr (::std::is_array_v<__container_type>)
				{
					return static_cast<__size_type>(
					     __adl_size(__container) * __binary_digits_v<__base_value_type>);
				}
			else if constexpr (__is_detected_v<__has_size_function_test, const __container_type&>)
				{
					return static_cast<__size_type>(__container.size() * __binary_digits_v<__base_value_type>);
				}
			else
				{
					return static_cast<__size_type>(
					     ::std::distance(::std::cbegin(__container), ::std::cend(__container)) *
					     __binary_digits_v<__base_value_type>);
				}
		}
	};

	template<::std::size_t _BeginBit, ::std::size_t _EndBit>
	class __bit_bounds
	{
	public:
		template<typename _Container>
		static constexpr ::std::size_t
		begin_position(const _Container&) noexcept
		{
			return _BeginBit;
		}

		template<typename _Container>
		static constexpr ::std::size_t
		end_position(const _Container&) noexcept
		{
			return _EndBit;
		}
	};

	template<typename _Container>
	class __dynamic_bit_bounds_for
	{
	private:
		using __container_type  = __unwrap_t<_Container>;
		using __range_ref       = std::add_lvalue_reference_t<__container_type>;
		using __base_iterator   = decltype(::std::begin(::std::declval<__range_ref>()));
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __value_type      = typename ::std::iterator_traits<__base_iterator>::value_type;

	public:
		__size_type first;
		__size_type last;

		__dynamic_bit_bounds_for(const __range_ref __range) noexcept
		: first(0), last(__adl_size(__range) * __binary_digits_v<__value_type>)
		{
		}

		__dynamic_bit_bounds_for(__size_type __first, __size_type __last) noexcept : first(__first), last(__last)
		{
		}

		constexpr __size_type
		begin_position(const __container_type&) const noexcept
		{
			return first;
		}

		constexpr __size_type
		end_position(const __container_type&) const noexcept
		{
			return last;
		}
	};

	class __dynamic_bit_bounds
	{
	public:
		::std::size_t first;
		::std::size_t last;

		template<typename _Container>
		__dynamic_bit_bounds(const _Container& __container) noexcept : __dynamic_bit_bounds(0, __container)
		{
		}

		template<typename _Container, ::std::enable_if_t<!::std::is_arithmetic_v<_Container>>* = nullptr>
		__dynamic_bit_bounds(::std::size_t __first, const _Container& __container) noexcept
		: first(__first)
		, last(__first +
		       (__adl_size(__unwrap_ref(__container)) * __binary_digits_v<typename ::std::iterator_traits<decltype(
		                                                     __adl_begin(__unwrap_ref(__container)))>::value_type>))
		{
		}

		__dynamic_bit_bounds(::std::size_t __first, ::std::size_t __last) noexcept : first(__first), last(__last)
		{
		}

		template<typename _Container>
		constexpr ::std::size_t
		begin_position(const _Container&) const noexcept
		{
			return first;
		}

		template<typename container_type>
		constexpr ::std::size_t
		end_position(const container_type&) const noexcept
		{
			return last;
		}
	};

	template<typename>
	struct __is_word_bit_bounds : ::std::false_type
	{
	};

	template<typename container_type>
	struct __is_word_bit_bounds<__word_bit_bounds<container_type>> : ::std::true_type
	{
	};

	template<typename _Type>
	inline constexpr bool __is_word_bit_bounds_v = __is_word_bit_bounds<_Type>::value;

	template<typename _Type>
	struct __is_word_or_bit_bounds : __is_word_bit_bounds<_Type>
	{
	};

	template<::std::size_t __First, ::std::size_t __Last>
	struct __is_word_or_bit_bounds<__bit_bounds<__First, __Last>> : ::std::true_type
	{
	};

	template<typename _Type>
	inline constexpr bool __is_word_or_bit_bounds_v = __is_word_or_bit_bounds<_Type>::value;

	template<typename _Bounds, typename = void>
	class __bounds_storage : private _Bounds
	{
	public:
		constexpr __bounds_storage()                        = default;
		constexpr __bounds_storage(const __bounds_storage&) = default;
		constexpr __bounds_storage(__bounds_storage&&)      = default;
		template<typename _Arg, typename... _Args,
		     ::std::enable_if_t<!::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_Arg>>,
		          __bounds_storage>>* = nullptr>
		constexpr __bounds_storage(_Arg&& __arg, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<_Bounds, _Arg, _Args...>)
		: _Bounds(::std::forward<_Arg>(__arg), ::std::forward<_Args>(__args)...)
		{
		}

		constexpr __bounds_storage&
		operator=(const __bounds_storage&) = default;
		constexpr __bounds_storage&
		operator=(__bounds_storage&&) = default;
		template<typename _Arg,
		     ::std::enable_if_t<!::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_Arg>>,
		          __bounds_storage>>* = nullptr>
		constexpr __bounds_storage&
		operator=(_Arg&& __arg)
		{
			this->_Bounds::operator=(::std::forward<_Arg>(__arg));
			return *this;
		}

		constexpr _Bounds&
		value() &
		{
			return static_cast<_Bounds&>(*this);
		}

		constexpr const _Bounds&
		value() const&
		{
			return static_cast<const _Bounds&>(*this);
		}

		constexpr _Bounds&&
		value() &&
		{
			return static_cast<_Bounds&&>(*this);
		}
	};

	template<typename _Bounds>
	class __bounds_storage<_Bounds, ::std::enable_if_t<::std::is_final_v<_Bounds> || !::std::is_object_v<_Bounds>>>
	: private _Bounds
	{
	private:
		_Bounds _M_bounds;

	public:
		constexpr __bounds_storage()                        = default;
		constexpr __bounds_storage(const __bounds_storage&) = default;
		constexpr __bounds_storage(__bounds_storage&&)      = default;
		template<typename _Arg, typename... _Args,
		     ::std::enable_if_t<!::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_Arg>>,
		          __bounds_storage>>* = nullptr>
		constexpr __bounds_storage(_Arg&& __arg, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<_Bounds, _Arg, _Args...>)
		: _M_bounds(::std::forward<_Arg>(__arg), ::std::forward<_Args>(__args)...)
		{
		}

		constexpr __bounds_storage&
		operator=(const __bounds_storage&) = default;
		constexpr __bounds_storage&
		operator=(__bounds_storage&&) = default;
		template<typename _Arg,
		     ::std::enable_if_t<!::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_Arg>>,
		          __bounds_storage>>* = nullptr>
		constexpr __bounds_storage&
		operator=(_Arg&& __arg)
		{
			this->_M_nounds = ::std::forward<_Arg>(__arg);
			return *this;
		}

		constexpr _Bounds&
		value() &
		{
			return this->_M_bounds;
		}

		constexpr const _Bounds&
		value() const&
		{
			return this->_M_bounds;
		}

		constexpr _Bounds&&
		value() &&
		{
			return ::std::move(this->_M_bounds);
		}
	};

	template<typename _Range, typename _Bounds = __word_bit_bounds<__unwrap_t<_Range>>>
	class __bit_view : __bounds_storage<_Bounds>
	{
	private:
		template<typename, typename>
		friend class __bit_view;
		template<typename>
		friend class __bit_sequence;

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator==(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator!=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator<(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator<=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator>(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator>=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		using __base_t                   = __detail::__bounds_storage<_Bounds>;
		using __range                    = __unwrap_t<_Range>;
		using __range_ref                = std::add_lvalue_reference_t<__range>;
		using __base_iterator            = decltype(__adl_begin(::std::declval<__range_ref>()));
		using __base_sentinel            = decltype(__adl_end(::std::declval<__range_ref>()));
		using __base_c_iterator          = decltype(__adl_cbegin(::std::declval<__range_ref>()));
		using __base_c_sentinel          = decltype(__adl_cend(::std::declval<__range_ref>()));
		using __base_pointer             = typename ::std::iterator_traits<__base_iterator>::pointer;
		using __base_reference           = typename ::std::iterator_traits<__base_iterator>::reference;
		using __base_c_pointer           = typename ::std::iterator_traits<__base_c_iterator>::pointer;
		using __base_c_reference         = typename ::std::iterator_traits<__base_c_iterator>::reference;
		using __iterator                 = __bit_iterator<__base_iterator>;
		using __sentinel                 = __bit_iterator<__base_sentinel>;
		using __c_iterator               = __bit_iterator<__base_c_iterator>;
		using __c_sentinel               = __bit_iterator<__base_c_sentinel>;
		using __base_value_type          = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __integral_base_value_type = __any_to_underlying_t<__base_value_type>;
		using __reference                = __bit_reference<__base_reference, __bit_mask_type_t<__base_value_type>>;
		using __const_reference          = __bit_reference<__base_c_reference, __bit_mask_type_t<__base_value_type>>;
		using __base_iterator_category   = typename ::std::iterator_traits<__base_iterator>::iterator_category;
		using __base_c_iterator_category = typename ::std::iterator_traits<__base_c_iterator>::iterator_category;

	public:
		using difference_type   = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using size_type         = ::std::make_unsigned_t<difference_type>;
		using value_type        = __bit_value;
		using reference         = __reference;
		using const_reference   = __const_reference;
		using pointer           = __bit_pointer<__base_pointer>;
		using const_pointer     = __bit_pointer<__base_c_pointer>;
		using iterator_category = typename ::std::iterator_traits<__base_iterator>::iterator_category;
		// FIXME: strengthen guarantees by checking for `iterator_concept`
		// on iterator_traits when ranges gets merged
		using iterator_concept = iterator_category;
		using iterator         = __iterator;
		using sentinel         = __sentinel;
		using const_iterator   = __c_iterator;
		using const_sentinel   = __c_sentinel;
		using container_type   = _Range;
		using bounds_type      = _Bounds;

		constexpr __bit_view() noexcept(::std::is_nothrow_default_constructible_v<
		     container_type>&& ::std::is_nothrow_default_constructible_v<bounds_type>)
		: __base_t(), _M_storage()
		{
		}

		template<typename _Arg, typename... _Args,
		     ::std::enable_if_t<!__is_same_no_cvref_v<__bit_view, _Arg> && !__is_same_no_cvref_v<bounds_type, _Arg>,
		          void*> = nullptr>
		constexpr __bit_view(_Arg&& __arg, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<container_type, _Arg,
		          _Args...>&& ::std::is_nothrow_default_constructible_v<bounds_type>)
		: __base_t(), _M_storage(::std::forward<_Arg>(__arg), ::std::forward<_Args>(__args)...)
		{
		}

		template<typename... _Args>
		constexpr __bit_view(bounds_type __extents, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<container_type,
		          _Args...>&& ::std::is_nothrow_move_constructible_v<bounds_type>)
		: __base_t(std::move(__extents)), _M_storage(::std::forward<_Args>(__args)...)
		{
		}

		constexpr __bit_view(const __bit_view& __right) = default;
		constexpr __bit_view(__bit_view&& __right)      = default;

		constexpr __bit_view&
		operator=(const __bit_view& __right) = default;
		constexpr __bit_view&
		operator=(__bit_view&& __right) = default;

		// modifiers
		constexpr reference operator[](difference_type __n) noexcept
		{
			auto __it = this->begin();
			__it += __n;
			return *__it;
		}

		constexpr const_reference operator[](difference_type __n) const noexcept
		{
			auto __it = this->cbegin();
			__it += __n;
			return *__it;
		}

		constexpr void
		set() noexcept
		{
			set(0, this->size());
		}

		// prevent integer promotion
		// from giving users the wrong idea
		constexpr void
		set(bool __value)
		{
			set(value_type(__value));
		}

		constexpr void
		set(value_type __value) noexcept
		{
			set(0, this->size(), __value);
		}

		constexpr void
		set(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.set();
		}

		constexpr void
		set(size_type __pos, bool __val) noexcept
		{
			set(__pos, value_type(__val));
		}

		constexpr void
		set(size_type __pos, value_type __val) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.set(__val);
		}

		constexpr void
		set(size_type __pos, size_type __len) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			__bit_fill_n(__it, __len, true);
		}

		constexpr void
		set(size_type __pos, size_type __len, bool __val) noexcept
		{
			this->set(__pos, __len, value_type(__val));
		}

		constexpr void
		set(size_type __pos, size_type __len, value_type __val) noexcept
		{
			if (__val)
				{
					this->set(__pos, __len);
				}
			else
				{
					this->reset(__pos, __len);
				}
		}

		constexpr void
		reset() noexcept
		{
			reset(0, this->size());
		}

		constexpr void
		reset(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.reset();
		}

		constexpr void
		reset(size_type __pos, size_type __len) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			__bit_fill_n(__it, __len, false);
		}

		constexpr void
		flip() noexcept
		{
			flip(0, this->size());
		}

		constexpr void
		flip(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.flip();
		}

		constexpr void
		flip(size_type __pos, size_type __len) noexcept
		{
			iterator __it = this->begin();
			::std::advance(__it, __pos);
			if constexpr (::std::is_unsigned_v<__base_value_type>)
				{
					// get to word boundary
					for (size_type __boundary = __len - (__len % (__binary_digits_v<__base_value_type>));
					     __boundary < __len; ++__it, (void)--__len)
						{
							auto ref = *__it;
							ref.flip();
						}
					// process words
					__base_iterator __it_base = ::std::move(__it).base();
					for (; __len > __binary_digits_v<__base_value_type>;
					     __len -= __binary_digits_v<__base_value_type>)
						{
							__base_reference __ref_base = *__it_base;
							__ref_base                  = ~__ref_base;
							++__it_base;
						}
					__it = iterator(::std::move(__it_base), 0);
				}
			// process individual bits
			for (; __len-- > 0; ++__it)
				{
					reference __ref = *__it;
					__ref.flip();
				}
		}

		constexpr iterator
		begin() noexcept
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return iterator(this->_M_storage_begin(), 0);
				}
			else
				{
					auto __bit_distance = this->_M_bounds_unwrapped().begin_position(this->_M_storage_unwrapped());
					auto __first        = iterator(this->_M_storage_begin());
					__first += __bit_distance;
					return __first;
				}
		}

		constexpr sentinel
		end() noexcept
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return const_sentinel(this->_M_storage_end(), 0);
				}
			else
				{
					auto __bit_distance = this->_M_bounds_unwrapped().end_position(this->_M_storage_unwrapped());
					auto __last         = const_iterator(this->_M_storage_begin());
					::std::advance(__last, __bit_distance);
					return __last;
				}
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
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return const_iterator(this->_M_storage_cbegin(), 0);
				}
			else
				{
					auto __bit_distance = this->_M_bounds_unwrapped().begin_position(this->_M_storage_unwrapped());
					auto __first        = const_iterator(this->_M_storage_cbegin());
					__first += __bit_distance;
					return __first;
				}
		}

		constexpr const_sentinel
		cend() const noexcept
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return const_sentinel(this->_M_storage_cend(), 0);
				}
			else
				{
					auto __bit_distance = this->_M_bounds_unwrapped().end_position(this->_M_storage_unwrapped());
					auto __last         = const_iterator(this->_M_storage_cbegin());
					__last += __bit_distance;
					return __last;
				}
		}

		// observers
		bool
		empty() const
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return __adl_empty(this->_M_storage_unwrapped());
				}
			else
				{
					return this->_M_bounds_unwrapped().begin_position(this->_M_storage_unwrapped()) ==
					       this->_M_bounds_unwrapped().end_position(this->_M_storage_unwrapped());
				}
		}

		constexpr const container_type&
		base() const& noexcept
		{
			return this->_M_storage_unwrapped();
		}

		constexpr container_type&
		     base() &
		     noexcept
		{
			return this->_M_storage_unwrapped();
		}

		constexpr container_type&&
		     base() &&
		     noexcept
		{
			return ::std::move(this->_M_storage_unwrapped());
		}

		constexpr bool
		test(difference_type __pos) const noexcept
		{
			return *::std::next(this->cbegin(), __pos);
		}

		constexpr size_type
		count(value_type __value) const noexcept
		{
			size_type __count = __bit_count(this->cbegin(), this->cend(), true);
			if (!__value)
				{
					return size() - __count;
				}
			return __count;
		}

		constexpr size_type
		popcount() const noexcept
		{
			return this->count(true);
		}

		constexpr size_type
		one_count() const noexcept
		{
			return this->count(true);
		}

		constexpr size_type
		zero_count() const noexcept
		{
			return this->count(false);
		}

		constexpr bool
		all() const noexcept
		{
			const_sentinel __last = this->cend();
			return __bit_find(this->cbegin(), __last, false) == __last;
		}

		constexpr bool
		any() const noexcept
		{
			const_sentinel __last = this->cend();
			return __bit_find(this->cbegin(), __last, true) != __last;
		}

		constexpr bool
		none() const noexcept
		{
			const_sentinel __last = this->cend();
			return __bit_find(this->cbegin(), __last, true) == __last;
		}

		constexpr size_type
		size() const noexcept
		{
			return this->_M_bit_distance();
		}

		constexpr const bounds_type&
		bounds() const noexcept
		{
			return this->_M_bounds.value();
		}

		constexpr bounds_type&
		bounds() noexcept
		{
			return this->_M_bounds.value();
		}

	private:
		container_type _M_storage;

		template<typename _Right>
		inline static constexpr bool __is_directly_comparable =
		     ::std::is_unsigned_v<__integral_base_value_type>&& ::std::is_unsigned_v<
		          typename _Right::__integral_base_value_type>&& ::std::is_same_v<container_type,
		          typename _Right::container_type>&& ::std::is_same_v<bounds_type, typename _Right::bounds_type>&&
		          __detail::__is_word_bit_bounds_v<bounds_type>&&
		               __detail::__is_word_bit_bounds_v<typename _Right::bounds_type>;

		constexpr size_type
		_M_bit_distance() const noexcept
		{
			return static_cast<size_type>(this->_M_bounds_unwrapped().end_position(this->_M_storage_unwrapped()) -
			                              this->_M_bounds_unwrapped().begin_position(this->_M_storage_unwrapped()));
		}

		constexpr __base_iterator
		_M_storage_begin() noexcept(noexcept(__adl_begin(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_begin(this->_M_storage_unwrapped());
		}

		constexpr __base_sentinel
		_M_storage_end() noexcept(noexcept(__adl_end(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_end(this->_M_storage_unwrapped());
		}

		constexpr __base_c_iterator
		_M_storage_begin() const noexcept(noexcept(__adl_begin(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_begin(this->_M_storage_unwrapped());
		}

		constexpr __base_c_sentinel
		_M_storage_end() const noexcept(noexcept(__adl_end(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_end(this->_M_storage_unwrapped());
		}

		constexpr __base_c_iterator
		_M_storage_cbegin() const noexcept(noexcept(__adl_cbegin(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_cbegin(this->_M_storage_unwrapped());
		}

		constexpr __base_c_sentinel
		_M_storage_cend() const noexcept(noexcept(__adl_cend(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_cend(this->_M_storage_unwrapped());
		}

		constexpr decltype(auto)
		_M_storage_unwrapped() const noexcept
		{
			return __unwrap_ref(this->_M_storage);
		}

		constexpr decltype(auto)
		_M_storage_unwrapped() noexcept
		{
			return __unwrap_ref(this->_M_storage);
		}

		constexpr decltype(auto)
		_M_bounds_unwrapped() const noexcept
		{
			return __unwrap_ref(static_cast<const __base_t&>(*this).value());
		}

		constexpr decltype(auto)
		_M_bounds_unwrapped() noexcept
		{
			return __unwrap_ref(static_cast<__base_t&>(*this).value());
		}
	};

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator==(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__equal_to_test, _LeftStorage, _RightStorage>)
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
				if constexpr (std::is_same_v<typename _Left::__base_value_type,
				                   typename _Right::__base_value_type> &&
				              __detail::__is_word_bit_bounds_v<typename _Left::bounds_type> &&
				              __detail::__is_word_bit_bounds_v<typename _Right::bounds_type>)
					{
						return ::std::equal(__left._M_storage_cbegin(), __left._M_storage_cend(),
						     __right._M_storage_cbegin(), __right._M_storage_cend());
					}
				else
					{
						return ::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
					}
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator!=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__not_equal_to_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage != __right._M_storage;
			}
		else
			{
				auto __left_size  = __left.size();
				auto __right_size = __right.size();
				if (__left_size == __right_size)
					{
						if constexpr (std::is_same_v<typename _Left::__base_value_type,
						                   typename _Right::__base_value_type> &&
						              __detail::__is_word_bit_bounds_v<typename _Left::bounds_type> &&
						              __detail::__is_word_bit_bounds_v<typename _Right::bounds_type>)
							{
								return !::std::equal(__left._M_storage_cbegin(), __left._M_storage_cend(),
								     __right._M_storage_cbegin(), __right._M_storage_cend());
							}
						else
							{
								return !::std::equal(
								     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
							}
					}
				return false;
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator<(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__less_than_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage < __right._M_storage;
			}
		else
			{
				return ::std::lexicographical_compare(
				     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator<=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__less_equal_to_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage <= __right._M_storage;
			}
		else
			{
				return !(__left > __right);
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator>(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__greater_than_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage > __right._M_storage;
			}
		else
			{
				return ::std::lexicographical_compare(
				     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), std::greater<bool>());
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator>=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__greater_equal_to_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage >= __right._M_storage;
			}
		else
			{
				return !(__left < __right);
			}
	}

} // namespace ITSY_BITSY_SOURCE_NAMESPACE

#endif // ITSY_BITSY_DETAIL_BIT_VIEW_HPP
