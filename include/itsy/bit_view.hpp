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

#ifndef ITSY_BITSY_BIT_VIEW_HPP
#define ITSY_BITSY_BIT_VIEW_HPP

#include <itsy/algorithm.hpp>
#include <itsy/bit_iterator.hpp>
#include <itsy/bit_operations.hpp>

#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/unwrap.hpp>
#include <ztd/idk/assert.hpp>
#include <ztd/ranges/iterator.hpp>
#include <ztd/ranges/range.hpp>

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <utility>
#include <algorithm>


namespace bitsy
{
	template<typename _Container>
	class word_bit_bounds
	{
	private:
		using __container_type  = ::std::remove_reference_t<::ztd::unwrap_t<_Container>>;
		using __base_iterator   = ::ztd::ranges::range_iterator_t<__container_type>;
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
					     ::ztd::ranges::ranges_adl::adl_size(__container) * binary_digits_v<__base_value_type>);
				}
			else if constexpr (::ztd::is_detected_v<__ib_detail::__has_size_function_test, const __container_type&>)
				{
					return static_cast<__size_type>(__container.size() * binary_digits_v<__base_value_type>);
				}
			else
				{
					return static_cast<__size_type>(
					     ::std::distance(::std::cbegin(__container), ::std::cend(__container)) *
					     binary_digits_v<__base_value_type>);
				}
		}
	};

	template<::std::size_t _BeginBit, ::std::size_t _EndBit>
	class bit_bounds
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
	class dynamic_bit_bounds_for
	{
	private:
		using __container_type  = ::ztd::remove_cvref_t<::ztd::unwrap_t<_Container>>;
		using __range_ref       = std::add_lvalue_reference_t<__container_type>;
		using __base_iterator   = decltype(::std::begin(::std::declval<__range_ref>()));
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __value_type      = typename ::std::iterator_traits<__base_iterator>::value_type;

	public:
		__size_type first;
		__size_type last;

		dynamic_bit_bounds_for(const __range_ref __range) noexcept
		: first(0), last(::ztd::ranges::ranges_adl::adl_size(__range) * binary_digits_v<__value_type>)
		{
		}

		dynamic_bit_bounds_for(__size_type __first, __size_type __last) noexcept : first(__first), last(__last)
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

	class dynamic_bit_bounds
	{
	public:
		::std::size_t first;
		::std::size_t last;

		template<typename _Container>
		dynamic_bit_bounds(const _Container& __container) noexcept : dynamic_bit_bounds(0, __container)
		{
		}

		template<typename _Container, ::std::enable_if_t<!::std::is_arithmetic_v<_Container>>* = nullptr>
		dynamic_bit_bounds(::std::size_t __first, const _Container& __container) noexcept
		: first(__first)
		, last(__first +
		       (::ztd::ranges::ranges_adl::adl_size(::ztd::unwrap(__container)) *
		            binary_digits_v<typename ::std::iterator_traits<decltype(::ztd::ranges::ranges_adl::adl_begin(
		                 ::ztd::unwrap(__container)))>::value_type>))
		{
		}

		dynamic_bit_bounds(::std::size_t __first, ::std::size_t __last) noexcept : first(__first), last(__last)
		{
		}

		template<typename _Container>
		constexpr ::std::size_t
		begin_position(const _Container&) const noexcept
		{
			return first;
		}

		template<typename _Container>
		constexpr ::std::size_t
		end_position(const _Container&) const noexcept
		{
			return last;
		}
	};

	namespace __ib_detail
	{
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
		class __bounds_storage<_Bounds,
		     ::std::enable_if_t<::std::is_final_v<_Bounds> || !::std::is_object_v<_Bounds>>> : private _Bounds
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

		template<typename>
		struct __is_word_bit_bounds : ::std::false_type
		{
		};

		template<typename container_type>
		struct __is_word_bit_bounds<word_bit_bounds<container_type>> : ::std::true_type
		{
		};

		template<typename _Type>
		inline constexpr bool __is_word_bit_bounds_v = __is_word_bit_bounds<_Type>::value;

		template<typename _Type>
		struct __is_word_or_bit_bounds : __is_word_bit_bounds<_Type>
		{
		};

		template<::std::size_t __First, ::std::size_t __Last>
		struct __is_word_or_bit_bounds<bit_bounds<__First, __Last>> : ::std::true_type
		{
		};

		template<typename _Type>
		inline constexpr bool __is_word_or_bit_bounds_v = __is_word_or_bit_bounds<_Type>::value;

	} // namespace __ib_detail

	template<typename _Range, typename _Bounds = word_bit_bounds<::ztd::unwrap_t<_Range>>>
	class bit_view : __ib_detail::__bounds_storage<_Bounds>
	{
	private:
		template<typename, typename>
		friend class bit_view;
		template<typename>
		friend class bit_sequence;

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator==(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator!=(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator<(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator<=(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator>(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator>=(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right);

		using __base_t                   = __ib_detail::__bounds_storage<_Bounds>;
		using __range                    = ::std::remove_reference_t<::ztd::unwrap_t<_Range>>;
		using __range_ref                = std::add_lvalue_reference_t<__range>;
		using __base_iterator            = ::ztd::ranges::range_iterator_t<__range_ref>;
		using __base_sentinel            = ::ztd::ranges::range_sentinel_t<__range_ref>;
		using __base_c_iterator          = ::ztd::ranges::range_const_iterator_t<__range_ref>;
		using __base_c_sentinel          = ::ztd::ranges::range_const_sentinel_t<__range_ref>;
		using __base_pointer             = ::ztd::ranges::iterator_pointer_t<__base_iterator>;
		using __base_reference           = ::ztd::ranges::iterator_reference_t<__base_iterator>;
		using __base_c_pointer           = ::ztd::ranges::iterator_pointer_t<__base_c_iterator>;
		using __base_c_reference         = ::ztd::ranges::iterator_reference_t<__base_c_iterator>;
		using __iterator                 = bit_iterator<__base_iterator>;
		using __sentinel                 = bit_iterator<__base_sentinel>;
		using __c_iterator               = bit_iterator<__base_c_iterator>;
		using __c_sentinel               = bit_iterator<__base_c_sentinel>;
		using __base_value_type          = ::ztd::ranges::iterator_value_type_t<__base_iterator>;
		using __integral_base_value_type = ::ztd::any_to_underlying_t<__base_value_type>;
		using __reference                = bit_reference<__base_reference, bit_mask_type_t<__base_value_type>>;
		using __const_reference          = bit_reference<__base_c_reference, bit_mask_type_t<__base_value_type>>;
		using __base_iterator_category   = ::ztd::ranges::iterator_concept_t<__base_iterator>;
		using __base_c_iterator_category = ::ztd::ranges::iterator_concept_t<__base_c_iterator>;

	public:
		using difference_type        = ::ztd::ranges::iterator_difference_type_t<__base_iterator>;
		using size_type              = ::std::make_unsigned_t<difference_type>;
		using value_type             = bit_value;
		using reference              = __reference;
		using const_reference        = __const_reference;
		using pointer                = bit_pointer<__base_pointer>;
		using const_pointer          = bit_pointer<__base_c_pointer>;
		using iterator_category      = ::ztd::ranges::iterator_category_t<__base_iterator>;
		using iterator_concept       = ::ztd::ranges::iterator_concept_t<__base_iterator>;
		using iterator               = __iterator;
		using sentinel               = __sentinel;
		using const_iterator         = __c_iterator;
		using const_sentinel         = __c_sentinel;
		using reverse_iterator       = ::std::reverse_iterator<iterator>;
		using reverse_sentinel       = ::std::reverse_iterator<sentinel>;
		using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;
		using const_reverse_sentinel = ::std::reverse_iterator<const_sentinel>;
		using container_type         = _Range;
		using bounds_type            = _Bounds;

		constexpr bit_view() noexcept(::std::is_nothrow_default_constructible_v<
		     container_type>&& ::std::is_nothrow_default_constructible_v<bounds_type>)
		: __base_t(), _M_storage()
		{
		}

		template<typename _Arg, typename... _Args,
		     ::std::enable_if_t<!__ib_detail::__is_same_no_cvref_v<bit_view, _Arg> &&
		                             !__ib_detail::__is_same_no_cvref_v<bounds_type, _Arg>,
		          void*> = nullptr>
		constexpr bit_view(_Arg&& __arg, _Args&&... __args) noexcept(::std::is_nothrow_constructible_v<container_type,
		     _Arg, _Args...>&& ::std::is_nothrow_default_constructible_v<bounds_type>)
		: __base_t(), _M_storage(::std::forward<_Arg>(__arg), ::std::forward<_Args>(__args)...)
		{
		}

		template<typename... _Args>
		constexpr bit_view(bounds_type __extents, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<container_type,
		          _Args...>&& ::std::is_nothrow_move_constructible_v<bounds_type>)
		: __base_t(std::move(__extents)), _M_storage(::std::forward<_Args>(__args)...)
		{
		}

		constexpr bit_view(const bit_view& __right) = default;
		constexpr bit_view(bit_view&& __right)      = default;

		constexpr bit_view&
		operator=(const bit_view& __right) = default;
		constexpr bit_view&
		operator=(bit_view&& __right) = default;

		// modifiers
		constexpr reference
		operator[](difference_type __n) noexcept
		{
			auto __it = this->begin();
			__it += __n;
			return *__it;
		}

		constexpr const_reference
		operator[](difference_type __n) const noexcept
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
			bitsy::bit_fill_n(__it, __len, true);
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
			bitsy::bit_fill_n(__it, __len, false);
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
					for (size_type __boundary = __len - (__len % (binary_digits_v<__base_value_type>));
					     __boundary < __len; ++__it, (void)--__len)
						{
							auto ref = *__it;
							ref.flip();
						}
					// process words
					__base_iterator __it_base = ::std::move(__it).base();
					for (; __len > binary_digits_v<__base_value_type>; __len -= binary_digits_v<__base_value_type>)
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
			if constexpr (__ib_detail::__is_word_bit_bounds_v<bounds_type>)
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
			if constexpr (__ib_detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return sentinel(this->_M_storage_end(), 0);
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
			if constexpr (__ib_detail::__is_word_bit_bounds_v<bounds_type>)
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
			if constexpr (__ib_detail::__is_word_bit_bounds_v<bounds_type>)
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

		constexpr reverse_iterator
		rbegin() noexcept
		{
			return ::std::make_reverse_iterator(this->end());
		}

		constexpr reverse_sentinel
		rend() noexcept
		{
			return ::std::make_reverse_iterator(this->begin());
		}

		constexpr const_reverse_iterator
		rbegin() const noexcept
		{
			return ::std::make_reverse_iterator(this->end());
		}

		constexpr const_reverse_sentinel
		rend() const noexcept
		{
			return ::std::make_reverse_iterator(this->begin());
		}

		constexpr const_reverse_iterator
		crbegin() const noexcept
		{
			return ::std::make_reverse_iterator(this->cend());
		}

		constexpr const_reverse_sentinel
		crend() const noexcept
		{
			return ::std::make_reverse_iterator(this->cbegin());
		}

		// observers
		constexpr bool
		empty() const
		{
			if constexpr (__ib_detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return ::ztd::ranges::ranges_adl::adl_empty(this->_M_storage_unwrapped());
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
			return this->_M_storage;
		}

		constexpr container_type&
		base() & noexcept
		{
			return this->_M_storage;
		}

		constexpr container_type&&
		base() && noexcept
		{
			return ::std::move(this->_M_storage);
		}

		constexpr bool
		test(difference_type __pos) const noexcept
		{
			return *::std::next(this->cbegin(), __pos);
		}

		constexpr size_type
		count(value_type __value) const noexcept
		{
			size_type __count = bitsy::bit_count(this->cbegin(), this->cend(), true);
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
			return bitsy::bit_find(this->cbegin(), __last, false) == __last;
		}

		constexpr bool
		any() const noexcept
		{
			const_sentinel __last = this->cend();
			return bitsy::bit_find(this->cbegin(), __last, true) != __last;
		}

		constexpr bool
		none() const noexcept
		{
			const_sentinel __last = this->cend();
			return bitsy::bit_find(this->cbegin(), __last, true) == __last;
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

		// Bit-OR assignment
		template<typename _RightR, typename _RightBounds>
		constexpr bit_view&
		operator|=(const bit_view<_RightR, _RightBounds>& __right) noexcept
		{
			ZTD_ASSERT(this->size() == __right.size());
			auto __left_it    = this->begin();
			auto __left_last  = this->end();
			auto __right_it   = __right.cbegin();
			auto __right_last = __right.cend();
			for (; __right_it != __right_last; (void)++__left_it, ++__right_it)
				{
					*__left_it |= *__right_it;
				}
			return *this;
		}

		// Bit-AND assignment
		template<typename _RightR, typename _RightBounds>
		constexpr bit_view&
		operator&=(const bit_view<_RightR, _RightBounds>& __right) noexcept
		{
			ZTD_ASSERT(this->size() == __right.size());
			auto __left_it    = this->begin();
			auto __left_last  = this->end();
			auto __right_it   = __right.cbegin();
			auto __right_last = __right.cend();
			for (; __right_it != __right_last; (void)++__left_it, ++__right_it)
				{
					*__left_it &= *__right_it;
				}
			return *this;
		}

		// Bit-XOR assignment
		template<typename _RightR, typename _RightBounds>
		constexpr bit_view&
		operator^=(const bit_view<_RightR, _RightBounds>& __right) noexcept
		{
			ZTD_ASSERT(this->size() == __right.size());
			auto __left_it    = this->begin();
			auto __left_last  = this->end();
			auto __right_it   = __right.cbegin();
			auto __right_last = __right.cend();
			for (; __right_it != __right_last; (void)++__left_it, ++__right_it)
				{
					*__left_it ^= *__right_it;
				}
			return *this;
		}

		// Bit-LSHIFT assignment
		template<typename _Constraint = __base_reference, // cf
		     ::std::enable_if_t<                          // cf
		          !::std::is_const_v<_Constraint>         // cf
		          >*                  = nullptr>
		constexpr bit_view&
		operator<<=(::std::size_t __count) noexcept
		{
			ZTD_ASSERT(__count <= this->size());
			// shift by: 10
			// 0101010101 0101001111000100
			//          ^
			// copy(b + __count, e, b);
			// 0101001111000100 XXXXXXXXXX
			// AND              0000000000
			// 0101001111000100 0000000000
			auto __rotate_to = ::std::next(this->begin(), __count);
			::std::fill(::std::rotate(this->begin(), __rotate_to, this->end()), this->end(), bit0);
			return *this;
		}

		// Bit-RSHIFT assignment
		template<typename _Constraint = __base_reference, // cf
		     ::std::enable_if_t<                          // cf
		          !::std::is_const_v<_Constraint>         // cf
		          >*                  = nullptr>
		constexpr bit_view&
		operator>>=(::std::size_t __count) noexcept
		{
			ZTD_ASSERT(__count <= this->size());
			auto __rotate_to = ::std::next(this->rbegin(), __count);
			::std::fill(::std::rotate(this->rbegin(), __rotate_to, this->rend()), this->rend(), bit0);
			return *this;
		}

	private:
		container_type _M_storage;

		template<typename _Right>
		inline static constexpr bool __is_directly_comparable = ::std::is_unsigned_v<__integral_base_value_type> // cf
		     && ::std::is_unsigned_v<typename _Right::__integral_base_value_type>                                // cf
		          && ::std::is_same_v<container_type,
		               typename _Right::container_type>                               // cf
		               && ::std::is_same_v<bounds_type, typename _Right::bounds_type> // cf
		                    && __ib_detail::__is_word_bit_bounds_v<bounds_type>       // cf
		                         && __ib_detail::__is_word_bit_bounds_v<typename _Right::bounds_type>;

		constexpr size_type
		_M_bit_distance() const noexcept
		{
			const __range& __storage = this->_M_storage_unwrapped();
			const auto& __bounds     = this->_M_bounds_unwrapped();
			return static_cast<size_type>(__bounds.end_position(__storage) - __bounds.begin_position(__storage));
		}

		constexpr __base_iterator
		_M_storage_begin() noexcept(
		     noexcept(::ztd::ranges::ranges_adl::adl_begin(::ztd::unwrap(::std::declval<container_type>()))))
		{
			return ::ztd::ranges::ranges_adl::adl_begin(this->_M_storage_unwrapped());
		}

		constexpr __base_sentinel
		_M_storage_end() noexcept(
		     noexcept(::ztd::ranges::ranges_adl::adl_end(::ztd::unwrap(::std::declval<container_type>()))))
		{
			return ::ztd::ranges::ranges_adl::adl_end(this->_M_storage_unwrapped());
		}

		constexpr __base_c_iterator
		_M_storage_begin() const
		     noexcept(noexcept(::ztd::ranges::ranges_adl::adl_begin(::ztd::unwrap(::std::declval<container_type>()))))
		{
			return ::ztd::ranges::ranges_adl::adl_begin(this->_M_storage_unwrapped());
		}

		constexpr __base_c_sentinel
		_M_storage_end() const
		     noexcept(noexcept(::ztd::ranges::ranges_adl::adl_end(::ztd::unwrap(::std::declval<container_type>()))))
		{
			return ::ztd::ranges::ranges_adl::adl_end(this->_M_storage_unwrapped());
		}

		constexpr __base_c_iterator
		_M_storage_cbegin() const noexcept(
		     noexcept(::ztd::ranges::ranges_adl::adl_cbegin(::ztd::unwrap(::std::declval<container_type>()))))
		{
			return ::ztd::ranges::ranges_adl::adl_cbegin(this->_M_storage_unwrapped());
		}

		constexpr __base_c_sentinel
		_M_storage_cend() const
		     noexcept(noexcept(::ztd::ranges::ranges_adl::adl_cend(::ztd::unwrap(::std::declval<container_type>()))))
		{
			return ::ztd::ranges::ranges_adl::adl_cend(this->_M_storage_unwrapped());
		}

		constexpr const __range&
		_M_storage_unwrapped() const& noexcept
		{
			return ::ztd::unwrap(this->_M_storage);
		}

		constexpr __range&&
		_M_storage_unwrapped() const&& noexcept
		{
			return ::ztd::unwrap(this->_M_storage);
		}

		constexpr __range&
		_M_storage_unwrapped() & noexcept
		{
			return ::ztd::unwrap(this->_M_storage);
		}

		constexpr decltype(auto)
		_M_bounds_unwrapped() const noexcept
		{
			return ::ztd::unwrap(static_cast<const __base_t&>(*this).value());
		}

		constexpr decltype(auto)
		_M_bounds_unwrapped() noexcept
		{
			return ::ztd::unwrap(static_cast<__base_t&>(*this).value());
		}
	};

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator==(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = bit_view<_LeftR, _LeftEx>;
		using _Right        = bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              ::ztd::is_detected_v<__ib_detail::__equal_to_test, _LeftStorage, _RightStorage>)
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
				              __ib_detail::__is_word_bit_bounds_v<typename _Left::bounds_type> &&
				              __ib_detail::__is_word_bit_bounds_v<typename _Right::bounds_type>)
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
	operator!=(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = bit_view<_LeftR, _LeftEx>;
		using _Right        = bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              ::ztd::is_detected_v<__ib_detail::__not_equal_to_test, _LeftStorage, _RightStorage>)
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
						              __ib_detail::__is_word_bit_bounds_v<typename _Left::bounds_type> &&
						              __ib_detail::__is_word_bit_bounds_v<typename _Right::bounds_type>)
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
	operator<(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = bit_view<_LeftR, _LeftEx>;
		using _Right        = bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              ::ztd::is_detected_v<__ib_detail::__less_than_test, _LeftStorage, _RightStorage>)
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
	operator<=(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = bit_view<_LeftR, _LeftEx>;
		using _Right        = bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              ::ztd::is_detected_v<__ib_detail::__less_equal_to_test, _LeftStorage, _RightStorage>)
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
	operator>(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = bit_view<_LeftR, _LeftEx>;
		using _Right        = bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              ::ztd::is_detected_v<__ib_detail::__greater_than_test, _LeftStorage, _RightStorage>)
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
	operator>=(const bit_view<_LeftR, _LeftEx>& __left, const bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = bit_view<_LeftR, _LeftEx>;
		using _Right        = bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              ::ztd::is_detected_v<__ib_detail::__greater_equal_to_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage >= __right._M_storage;
			}
		else
			{
				return !(__left < __right);
			}
	}

} // namespace bitsy

#endif // ITSY_BITSY_BIT_VIEW_HPP
