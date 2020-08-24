// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#ifndef ITSY_BITSY_DETAIL_BIT_ITERATOR_HPP
#define ITSY_BITSY_DETAIL_BIT_ITERATOR_HPP 1

#include <itsy/version.hpp>

#include <itsy/forward.hpp>
#include <itsy/detail/bit_detail.hpp>
#include <itsy/detail/bit_operations.hpp>

#include <cstddef>
#include <type_traits>
#include <cassert>
#include <limits>
#include <climits>
#include <utility>
#include <iterator>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{

	class __bit_value
	{
	private:
		using __mask_type = ::std::size_t;

		bool __bval;

	public:
		// types
		using size_type = ::std::size_t;

		// constructors
		__bit_value() noexcept = default;

		constexpr __bit_value(const __bit_value&) noexcept = default;

		constexpr __bit_value(bool __val) noexcept : __bval(__val)
		{
		}

		template<typename _WordRef, typename _Mask>
		constexpr __bit_value(const __bit_reference<_WordRef, _Mask>& __ref) noexcept
		: __bval(static_cast<bool>(__ref))
		{
		}

		template<typename _WordRef, ::std::enable_if_t<!__is_same_no_cvref_v<_WordRef, __bit_value> &&
		                                               !__is_same_no_cvref_v<_WordRef, bool>>* = nullptr>
		explicit constexpr __bit_value(_WordRef&& __val) noexcept : __bit_value(::std::forward<_WordRef>(__val), 0)
		{
		}

		template<typename _WordRef>
		constexpr __bit_value(_WordRef&& __val, size_type __pos) noexcept
		: __bval((::std::forward<_WordRef>(__val) & __pos_to_mask<__mask_type>(__pos)) != 0)
		{
		}

		// assignment
		constexpr __bit_value&
		operator=(const __bit_value&) noexcept = default;

		template<typename _WordRef, typename _Mask>
		constexpr __bit_value&
		operator=(const __bit_reference<_WordRef, _Mask>& __ref) noexcept
		{
			__bval = static_cast<bool>(__ref);
			return *this;
		}

		template<typename _RightWordRef>
		constexpr __bit_value&
		assign(_RightWordRef __val) noexcept
		{
			assign(__val, 0);
			return *this;
		}

		template<typename _RightWordRef>
		constexpr __bit_value&
		assign(_RightWordRef __val, size_type __pos) noexcept
		{
			__bval = (__val & __pos_to_mask<__mask_type>(__pos)) != 0;
			return *this;
		}

		// compound assignment
		constexpr __bit_value&
		operator&=(__bit_value __right) noexcept
		{
			__bval &= __right.__bval;
			return *this;
		}

		constexpr __bit_value&
		operator|=(__bit_value __right) noexcept
		{
			__bval |= __right.__bval;
			return *this;
		}
		constexpr __bit_value&
		operator^=(__bit_value __right) noexcept
		{
			__bval ^= __right.__bval;
			return *this;
		}

		// observers
		constexpr bool
		value() const noexcept
		{
			return __bval;
		}

		explicit constexpr operator bool() const noexcept
		{
			return value();
		}

		// modifiers
		constexpr __bit_value&
		set(bool __val = true) noexcept
		{
			__bval = __val;
			return *this;
		}

		constexpr __bit_value&
		reset() noexcept
		{
			__bval = false;
			return *this;
		}

		constexpr __bit_value&
		flip() noexcept
		{
			__bval = !__bval;
			return *this;
		}

		// swap
		friend void
		swap(__bit_value& __left, __bit_value& __right) noexcept
		{
			__adl_swap(__left.__bval, __right.__bval);
		}

		friend constexpr bool
		operator==(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval == __right.__bval;
		}
		friend constexpr bool
		operator!=(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval != __right.__bval;
		}
		friend constexpr bool
		operator<(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval < __right.__bval;
		}
		friend constexpr bool
		operator<=(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval <= __right.__bval;
		}
		friend constexpr bool
		operator>(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval > __right.__bval;
		}
		friend constexpr bool
		operator>=(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval >= __right.__bval;
		}
	};

	inline constexpr __bit_value __bit0(0u);
	inline constexpr __bit_value __bit1(1u);

	template<typename _WordRef, typename _Mask = __bit_mask_type_t<_WordRef>>
	class __bit_reference
	{
	private:
		template<typename, typename>
		friend class __bit_reference;

		using __mask_type          = _Mask;
		using __cv_word_type       = ::std::remove_reference_t<__unwrap_t<_WordRef>>;
		using __word_type          = ::std::remove_cv_t<__cv_word_type>;
		using __integral_word_type = __any_to_underlying_t<__word_type>;

	public:
		using value_type = bool;
		using mask_type  = __mask_type;
		using size_type  = ::std::size_t;

		// constructors
		constexpr __bit_reference(bool __val) noexcept = delete;

		constexpr __bit_reference(const __bit_reference& __right) noexcept
		: _M_word(__right._M_word), _M_mask(__right._M_mask)
		{
		}

		constexpr explicit __bit_reference(_WordRef __val) noexcept : __bit_reference(__val, 0)
		{
		}

		constexpr __bit_reference(_WordRef __val, size_type __pos) noexcept
		: _M_word(__val), _M_mask(__pos_to_mask<mask_type>(__pos))
		{
		}

		// assignment
		constexpr __bit_reference&
		operator=(const __bit_reference& __right) noexcept
		{
			return this->set(__right.value());
		}

		template<typename _RightWordRef, typename _RightMask,
		     ::std::enable_if_t<!::std::is_same_v<_RightWordRef, _WordRef> || !::std::is_same_v<_RightMask, _Mask>>* =
		          nullptr>
		constexpr __bit_reference&
		operator=(const __bit_reference<_RightWordRef, _RightMask>& __right) noexcept
		{
			return this->set(__right.value());
		}

		constexpr __bit_reference&
		operator=(__bit_value __val) noexcept
		{
			return this->set(__val.value());
		}

		constexpr __bit_reference&
		operator=(bool __val) noexcept
		{
			return this->set(__val);
		}

		// compound assignment
		constexpr __bit_reference&
		operator&=(__bit_value __right) noexcept
		{
			return this->set(value() && __right.value());
		}

		constexpr __bit_reference&
		operator|=(__bit_value __right) noexcept
		{
			return this->set(value() || __right.value());
		}

		constexpr __bit_reference&
		operator^=(__bit_value __right) noexcept
		{
			return this->set(value() ^ __right.value());
		}

		// conversions
		constexpr operator bool() const noexcept
		{
			return this->value();
		}

		// observers
		constexpr size_type
		position() const noexcept
		{
			return __mask_to_pos<size_type>(this->_M_mask);
		}

		constexpr mask_type
		mask() const noexcept
		{
			return this->_M_mask;
		}

		constexpr bool
		value() const noexcept
		{
			return (this->_M_word & this->_M_mask) != static_cast<mask_type>(0);
		}

		constexpr ::std::add_pointer_t<__cv_word_type>
		address() const noexcept
		{
			return std::addressof(this->_M_word);
		}

		// modifiers
		constexpr __bit_reference&
		set(__bit_value __val) noexcept
		{
			return this->set(__val.value());
		}

		constexpr __bit_reference&
		set(bool __val) noexcept
		{
			// must cast to integral type to
			// use unary minus, otherwise math falls apart
			// with enums like std::byte!
			__word_type __bit_val = static_cast<__word_type>(-static_cast<::std::make_signed_t<__word_type>>(
			     __val ? static_cast<__integral_word_type>(1) : static_cast<__integral_word_type>(0)));
			this->_M_word ^= (__bit_val ^ this->_M_word) & this->_M_mask;
			return *this;
		}

		constexpr __bit_reference&
		set() noexcept
		{
			this->_M_word |= this->_M_mask;
			return *this;
		}

		constexpr __bit_reference&
		reset() noexcept
		{
			this->_M_word &= ~(this->_M_mask);
			return *this;
		}

		constexpr __bit_reference&
		flip() noexcept
		{
			this->_M_word ^= this->_M_mask;
			return *this;
		}

		// swap
		constexpr friend void
		swap(__bit_reference& __left, __bit_reference& __right) noexcept(
		     ::std::is_nothrow_swappable_v<__word_type>&& ::std::is_nothrow_swappable_v<__mask_type>)
		{
			if (__left.value() == __right.value())
				{
					return;
				}
			__left.flip();
			__right.flip();
		}

	private:
		_WordRef _M_word;
		mask_type _M_mask;
	};

	template<typename _Pointer>
	class __bit_pointer
	{
	private:
		template<typename>
		friend class __bit_pointer;

		using __base_iterator   = __unwrap_t<_Pointer>;
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __word_type       = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __base_reference  = typename ::std::iterator_traits<__base_iterator>::reference;

	public:
		// types
		using iterator_type     = _Pointer;
		using iterator_category = typename ::std::iterator_traits<iterator_type>::iterator_category;
		using iterator_concept  = __iterator_concept_t<iterator_type>;
		using value_type        = __bit_value;
		using reference         = __bit_reference<__base_reference, __bit_mask_type_t<__word_type>>;
		using pointer           = reference*;
		using size_type         = __size_type;
		using difference_type   = __difference_type;

		// constructors
		constexpr __bit_pointer() noexcept : _M_base_it(), _M_bit_ref_storage()
		{
		}

		constexpr __bit_pointer(const __bit_pointer& __right) noexcept
		: _M_base_it(__right._M_base_it), _M_bit_ref_storage(__right._M_base_it)
		{
		}

		constexpr __bit_pointer(__bit_pointer&& __right) noexcept
		: _M_base_it(::std::move(__right._M_base_it)), _M_bit_ref_storage(::std::move(__right._M_base_it))
		{
		}

		template<typename _RightPointer, ::std::enable_if_t<!std::is_same_v<_Pointer, _RightPointer>>* = nullptr>
		constexpr __bit_pointer(const __bit_pointer<_RightPointer>& __right) noexcept
		: _M_base_it(static_cast<_Pointer>(__right._M_base_it))
		, _M_bit_ref_storage(_M_create_storage(this->_M_is_alive(), this->_M_base_it, __right.position()))
		{
		}

		constexpr __bit_pointer(::std::nullptr_t) noexcept : __bit_pointer()
		{
		}

		explicit constexpr __bit_pointer(iterator_type __pointer) noexcept : __bit_pointer(::std::move(__pointer), 0)
		{
		}

		constexpr __bit_pointer(iterator_type __pointer, size_type __position) noexcept
		: _M_base_it(::std::move(__pointer))
		, _M_bit_ref_storage(_M_create_storage(this->_M_is_alive(), this->_M_base_it, __position))
		{
		}

		// destructor
		~__bit_pointer()
		{
			this->_M_destroy_if_present();
		}

		// assignment
		constexpr __bit_pointer&
		operator=(const __bit_pointer& __right) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = __right._M_base_it;
			this->_M_construct_if_present(__right.position());
			return *this;
		}

		constexpr __bit_pointer&
		operator=(__bit_pointer&& __right) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = ::std::move(__right._M_base_it);
			this->_M_construct_if_present(__right.position());
			return *this;
		}

		constexpr __bit_pointer& operator=(::std::nullptr_t) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = _Pointer{};
			return *this;
		}

		template<typename _RightPointer,
		     ::std::enable_if_t<!::std::is_same_v<_Pointer, _RightPointer> &&
		                        ::std::is_convertible_v<_RightPointer, _Pointer>>* = nullptr>
		__bit_pointer&
		operator=(const __bit_pointer<_RightPointer>& __right) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = static_cast<_Pointer>(__right._M_base_it);
			this->_M_construct_if_present(__right.position());
			return *this;
		}

		template<typename _RightPointer,
		     ::std::enable_if_t<!::std::is_same_v<_Pointer, _RightPointer> &&
		                        ::std::is_convertible_v<_RightPointer, _Pointer>>* = nullptr>
		constexpr __bit_pointer&
		operator=(__bit_pointer<_RightPointer>&& __right) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = ::std::move(__right._M_base_it);
			this->_M_construct_if_present(__right.position());
			return *this;
		}

		// observers
		constexpr iterator_type&
		base() &
		{
			return this->_M_base_it;
		}

		constexpr const iterator_type&
		base() const&
		{
			return this->_M_base_it;
		}

		constexpr iterator_type&&
		base() &&
		{
			return ::std::move(this->_M_base_it);
		}

		explicit constexpr operator bool() const noexcept
		{
			return this->_M_is_alive();
		}

		constexpr reference
		operator*() const noexcept
		{
			return this->_M_bit_ref_storage._M_value;
		}

		constexpr pointer
		operator->() const noexcept
		{
			return std::addressof(const_cast<__bit_pointer*>(this)->_M_bit_ref_storage._M_value);
		}

		// swap
		friend constexpr void
		swap(__bit_pointer& __left, __bit_pointer& __right) noexcept(
		     ::std::is_nothrow_swappable_v<_Pointer>&& ::std::is_nothrow_swappable_v<size_type>)
		{
			const bool __left_alive  = __left._M_is_alive();
			const bool __right_alive = __right._M_is_alive();
			if (__left_alive && __right_alive)
				{
					__adl_swap(__left._M_base_it, __right._M_base_it);
					__adl_swap(__left._M_bit_ref_storage._M_value, __right._M_bit_ref_storage._M_value);
				}
			else if (__left_alive && !__right_alive)
				{
					__adl_swap(__left._M_base_it, __right._M_base_it);
					__right._M_destroy_dummy();
					__right._M_construct(__left.position());
					__left._M_destroy();
				}
			else if (!__left_alive && __right_alive)
				{
					__adl_swap(__left._M_base_it, __right._M_base_it);
					__left._M_destroy_dummy();
					__left._M_construct(__right.position());
					__right._M_destroy();
				}
			else
				{
					__adl_swap(__left._M_base_it, __right._M_base_it);
				}
		}

		// comparison
		template<typename __RightIt>
		friend constexpr bool
		operator==(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			return __left.base() == __right.base() && __left.position() == __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator!=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			return __left.base() != __right.base() || __left.position() != __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator<(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			if (__left.base() < __right.base())
				{
					return true;
				}
			if (__left.base() > __right.base())
				{
					return false;
				}
			return __left.position() < __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator<=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			if (__left.base() <= __right.base())
				{
					return true;
				}
			if (__left.base() > __right.base())
				{
					return false;
				}
			return __left.position() <= __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator>(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			if (__left.base() > __right.base())
				{
					return true;
				}
			if (__left.base() < __right.base())
				{
					return false;
				}
			return __left.position() > __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator>=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			if (__left.base() >= __right.base())
				{
					return true;
				}
			if (__left.base() < __right.base())
				{
					return false;
				}
			return __left.position() >= __left.position();
		}

	private:
		using _Uninit = __uninit<reference>;

		constexpr bool
		_M_is_alive() const
		{
			if constexpr (::std::is_pointer_v<iterator_type>)
				{
					return this->_M_base_it != nullptr;
				}
			else
				{
					if constexpr (__is_detected_v<__adl_to_address_test, iterator_type>)
						{
							return __adl_to_address(this->_M_base_it) != nullptr;
						}
					else
						{
							// Well, time to eat shit with MSVC, I guess!
							// FIXME: MSVC will die here for its iterator types
							// on debug modes.
							// nothing can do right now: to_address catches span,
							// but other types will still be shit
							return this->_M_base_it != iterator_type{};
						}
				}
		}

		constexpr void
		_M_destroy_if_present()
		{
			if (this->_M_is_alive())
				{
					this->_M_destroy();
				}
			else
				{
					this->_M_destroy_dummy();
				}
		}

		constexpr void
		_M_destroy()
		{
			this->_M_bit_ref_storage._M_value.~reference();
		}

		constexpr void
		_M_destroy_dummy()
		{
			// nothing to do
		}

		constexpr void
		_M_construct_if_present(size_type __position)
		{
			if (this->_M_is_alive())
				{
					this->_M_construct(__position);
				}
		}

		constexpr void
		_M_construct(size_type __position)
		{
			// FIXME: wait for new construct_at constexpr magic stuff
			new (std::addressof(this->_M_bit_ref_storage._M_value)) reference(*(this->_M_base_it), __position);
		}

		static constexpr _Uninit
		_M_create_storage(bool __is_alive, iterator_type& __base_it, size_type __position)
		{
			if (__is_alive)
				{
					return _Uninit(::std::in_place, *__unwrap_ref(__base_it), __position);
				}
			else
				{
					return _Uninit();
				}
		}

		iterator_type _M_base_it;
		_Uninit _M_bit_ref_storage;
	};

	template<typename _It>
	class __bit_iterator
	{
	private:
		template<typename>
		friend class __bit_iterator;

		using __base_iterator   = __unwrap_t<_It>;
		using __pointer         = typename ::std::iterator_traits<__base_iterator>::pointer;
		using __word_type       = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __mask_type       = __bit_mask_type_t<__word_type>;
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __word_ref_type   = typename ::std::iterator_traits<__base_iterator>::reference;

	public:
		using iterator_type     = __base_iterator;
		using iterator_category = typename ::std::iterator_traits<iterator_type>::iterator_category;
		using iterator_concept  = __iterator_concept_t<iterator_type>;
		using value_type        = __bit_value;
		using pointer           = __bit_pointer<iterator_type>;
		using reference         = __bit_reference<__word_ref_type, __mask_type>;
		using size_type         = __size_type;
		using difference_type   = __difference_type;

		// constructors
		constexpr __bit_iterator() noexcept                      = default;
		constexpr __bit_iterator(const __bit_iterator&) noexcept = default;
		constexpr __bit_iterator(__bit_iterator&&) noexcept      = default;
		explicit constexpr __bit_iterator(iterator_type __i) noexcept : __bit_iterator(::std::move(__i), 0)
		{
		}
		constexpr __bit_iterator(iterator_type __i, size_type __pos) noexcept
		: _M_base_it(::std::move(__i)), _M_pos(__pos)
		{
		}

		template<typename _RightIt, ::std::enable_if_t<!std::is_same_v<_It, _RightIt>>* = nullptr>
		constexpr __bit_iterator(__bit_iterator<_RightIt>&& __right) noexcept;
		template<typename _RightIt, ::std::enable_if_t<!std::is_same_v<_It, _RightIt>>* = nullptr>
		constexpr __bit_iterator(const __bit_iterator<_RightIt>& __right) noexcept;

		// assignment
		constexpr __bit_iterator&
		operator=(const __bit_iterator& __right) noexcept = default;
		constexpr __bit_iterator&
		operator=(__bit_iterator&& __right) noexcept = default;

		// observers
		constexpr reference
		operator*() const noexcept
		{
			return reference(*this->_M_base_it, this->_M_pos);
		}

		constexpr pointer
		operator->() const noexcept
		{
			return pointer(this->_M_base_it, this->_M_pos);
		}

		constexpr reference
		operator[](difference_type n) const
		{
			__bit_iterator __shifted = *this + n;
			return *__shifted;
		}

		constexpr iterator_type
		base() const noexcept
		{
			return this->_M_base_it;
		}

		constexpr size_type
		position() const noexcept
		{
			return this->_M_pos;
		}

		constexpr __mask_type
		mask() const noexcept
		{
			return __pos_to_mask<__mask_type>(_M_pos);
		}

		// arithmetic
		constexpr __bit_iterator&
		operator++()
		{
			++this->_M_pos;
			if (this->_M_pos == __binary_digits_v<__word_type>)
				{
					this->_M_pos = 0;
					++this->_M_base_it;
				}

			return *this;
		}

		constexpr __bit_iterator&
		operator--()
		{
			if (this->_M_pos == 0)
				{
					this->_M_pos = __max_binary_index_v<__word_type>;
					--this->_M_base_it;
				}
			else
				{
					--this->_M_pos;
				}

			return *this;
		}

		constexpr __bit_iterator
		operator++(int)
		{
			auto __saved = *this;
			++__saved;
			return __saved;
		}

		constexpr __bit_iterator
		operator--(int)
		{
			auto __saved = *this;
			--__saved;
			return __saved;
		}

		constexpr __bit_iterator
		operator+(difference_type __n) const
		{
			auto __saved = *this;
			__saved += __n;
			return __saved;
		}

		constexpr __bit_iterator
		operator-(difference_type __n) const
		{
			auto __saved = *this;
			__saved -= __n;
			return __saved;
		}

		constexpr __bit_iterator&
		operator+=(difference_type __n)
		{
			if (__n < 0)
				{
					return this->operator-=(-__n);
				}
			if (__n == 0)
				{
					return *this;
				}
			__size_type __bit_advancement = __n % __binary_digits_v<__word_type>;
			this->_M_pos += __bit_advancement;
			if (this->_M_pos > __binary_digits_v<__word_type>)
				{
					// put it back in the proper range
					this->_M_pos -= __binary_digits_v<__word_type>;
					// going forward by one extra since we
					// overflow binary digit count
					::std::advance(this->_M_base_it, (__n / __binary_digits_v<__word_type>)+1);
					return *this;
				}

			::std::advance(this->_M_base_it, __n / __binary_digits_v<__word_type>);
			return *this;
		}

		constexpr __bit_iterator&
		operator-=(difference_type __n)
		{
			if (__n < 0)
				{
					return this->operator+=(-__n);
				}
			if (__n == 0)
				{
					return *this;
				}
			__size_type __bit_advancement    = __n % __binary_digits_v<__word_type>;
			difference_type __it_advancement = __n / __binary_digits_v<__word_type>;
			if (__bit_advancement > this->_M_pos)
				{
					// put it back in the proper range
					this->_M_pos = __binary_digits_v<__word_type> - __bit_advancement;
					// going forward by one extra since we
					// overflow binary digit count
					++__it_advancement;
					::std::advance(this->_M_base_it, -__it_advancement);
					return *this;
				}

			this->_M_pos -= __bit_advancement;
			::std::advance(this->_M_base_it, -static_cast<difference_type>(__n / __binary_digits_v<__word_type>));
			return *this;
		}

		friend constexpr difference_type
		operator-(const __bit_iterator& __left, const __bit_iterator& __right)
		{
			return (::std::distance(__right._M_base_it, __left._M_base_it) * __binary_digits_v<__word_type>)+(
			     __left._M_pos - __right._M_pos);
		}

		// comparison
		template<typename __RightIt>
		friend constexpr bool
		operator==(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			return __left.base() == __right.base() && __left.position() == __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator!=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			return __left.base() != __right.base() || __left.position() != __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator<(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			if (__left.base() < __right.base())
				{
					return true;
				}
			if (__left.base() > __right.base())
				{
					return false;
				}
			return __left.position() < __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator<=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			if (__left.base() <= __right.base())
				{
					return true;
				}
			if (__left.base() > __right.base())
				{
					return false;
				}
			return __left.position() <= __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator>(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			if (__left.base() > __right.base())
				{
					return true;
				}
			if (__left.base() < __right.base())
				{
					return false;
				}
			return __left.position() > __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator>=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			if (__left.base() >= __right.base())
				{
					return true;
				}
			if (__left.base() < __right.base())
				{
					return false;
				}
			return __left.position() >= __right.position();
		}

		// swap
		friend constexpr void
		swap(__bit_iterator& __left, __bit_iterator& __right) noexcept(
		     ::std::is_nothrow_swappable_v<iterator_type>&& ::std::is_nothrow_swappable_v<size_type>)
		{
			__adl_swap(__left._M_base_it, __right._M_base_it);
			__adl_swap(__left._M_pos, __right._M_pos);
		}

	private:
		iterator_type _M_base_it;
		size_type _M_pos;
	};

	template<typename _It>
	template<typename _RightIt, ::std::enable_if_t<!std::is_same_v<_It, _RightIt>>*>
	constexpr __bit_iterator<_It>::__bit_iterator(__bit_iterator<_RightIt>&& __right) noexcept
	: __bit_iterator(::std::move(__right).base(), ::std::move(__right).position())
	{
	}

	template<typename _It>
	template<typename _RightIt, ::std::enable_if_t<!std::is_same_v<_It, _RightIt>>*>
	constexpr __bit_iterator<_It>::__bit_iterator(const __bit_iterator<_RightIt>& __right) noexcept
	: __bit_iterator(__right.base(), __right.position())
	{
	}

} // namespace ITSY_BITSY_SOURCE_NAMESPACE

#endif // ITSY_BITSY_DETAIL_BIT_ITERATOR_HPP
