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

#ifndef ITSY_BITSY_DETAIL_SMALL_BIT_VECTOR_HPP
#define ITSY_BITSY_DETAIL_SMALL_BIT_VECTOR_HPP 1

#include <itsy/detail/bit_iterator.hpp>
#include <itsy/detail/ebco.hpp>
#include <itsy/detail/algorithm.hpp>

#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <climits>
#include <cassert>

#ifdef ITSY_BITSY_DETAIL_SBO_CONSTEXPR_CAPABLE
#define ITSY_BITSY_ALLOCATOR_CONSTEXPR constexpr
#define ITSY_BITSY_BLESSED_CONSTEXPR constexpr
#else
#define ITSY_BITSY_ALLOCATOR_CONSTEXPR
#define ITSY_BITSY_BLESSED_CONSTEXPR
#endif

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	template<typename _Type, typename _Allocator>
	inline constexpr ::std::size_t __compute_small_buffer_size_v =
	     (sizeof(_Type*) +
	          sizeof(typename ::std::allocator_traits<::std::remove_reference_t<__unwrap_t<_Allocator>>>::size_type)) /
	     sizeof(_Type);

	template<typename _Type, typename _Allocator = ::std::allocator<_Type>>
	inline constexpr ::std::size_t __default_small_buffer_size_v =
	     __compute_small_buffer_size_v<_Type, _Allocator> < 1 ? 1 : __compute_small_buffer_size_v<_Type, _Allocator>;

	template<typename _Type,
	     ::std::size_t _InlineWords = __default_small_buffer_size_v<_Type, ::std::allocator<_Type>>,
	     typename _Allocator = ::std::allocator<_Type>, bool _Packed = true>
	class __packed_small_bit_vector : private __ebco<_Allocator, 0>
	{
	private:
		template<typename, ::std::size_t, typename, bool>
		friend class __packed_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class __small_bit_vector;

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator==(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator!=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator<(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator<=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator>(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator>=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		using __alloc_base           = __ebco<_Allocator, 0>;
		using __underlying           = __any_to_underlying_t<_Type>;
		using __unsigned_underlying  = ::std::make_unsigned_t<__underlying>;
		using __alloc                = ::std::remove_cv_t<::std::remove_reference_t<__unwrap_t<_Allocator>>>;
		using __alloc_traits         = ::std::allocator_traits<__alloc>;
		using __size_type            = typename __alloc_traits::size_type;
		using __base_value_type      = typename __alloc_traits::value_type;
		using __base_pointer         = typename __alloc_traits::pointer;
		using __base_const_pointer   = typename __alloc_traits::const_pointer;
		using __base_reference       = decltype(*::std::declval<__base_pointer>());
		using __base_const_reference = decltype(*::std::declval<__base_const_pointer>());
		using __difference_type      = typename __alloc_traits::difference_type;

		inline static constexpr __size_type _S_inline_innate_max_bit_count =
		     static_cast<__size_type>(_InlineWords * __binary_digits_v<__base_value_type>);
		inline static constexpr __size_type _S_bits_for_inline_size =
		     __binary_digits_v<__underlying> - __bit_firstl_one(_S_inline_innate_max_bit_count);
		inline static constexpr bool _S_is_hyper_sbo_capable =
		     // FIXME: size calculations in a few places are busted
		     // currently broken -- fix it up later after doing a full analysis
		     // of where size is being used mid-operation to compute things
		     // that it should be computed upfront and cached
		     // (e.g., with __old_size/__old_storage_size/
		     // __capacity/__storage_capacity etc.)
		     false && _Packed && (_InlineWords > 0) && ::std::is_integral_v<__underlying> &&
		     (_S_bits_for_inline_size <= __binary_digits_v<__underlying>);
		inline static constexpr __size_type _S_extra_storage_words =
		     (sizeof(__size_type) - sizeof(__base_value_type)) / sizeof(__base_value_type);
		inline static constexpr __size_type _S_inline_max_bit_count =
		     _S_inline_innate_max_bit_count +
		     (_S_is_hyper_sbo_capable
		               ? (_S_extra_storage_words + __binary_digits_v<__underlying> - _S_bits_for_inline_size)
		               : 0);
		inline static constexpr __size_type _S_end_storage_buffer_index =
		     _InlineWords + static_cast<__size_type>(_S_is_hyper_sbo_capable);

		template<typename _It>
		using _S_construct_iterator_type = void (*)(__alloc&, __base_pointer, _It&) noexcept(
#if ITSY_BITSY_IS_ON(ITSY_BITSY_CLANG_I_)
		     false
#else
		     ::std::is_nothrow_constructible_v<__base_value_type, decltype(*::std::declval<_It&>())>
#endif
		);

	public:
		// member types
		using allocator                                   = _Allocator;
		using value_type                                  = __bit_value;
		using reference                                   = __bit_reference<__base_reference>;
		using const_reference                             = __bit_reference<__base_const_reference>;
		using pointer                                     = __bit_pointer<__base_pointer>;
		using const_pointer                               = __bit_pointer<__base_const_pointer>;
		using iterator                                    = __bit_iterator<__base_pointer>;
		using const_iterator                              = __bit_iterator<__base_const_pointer>;
		using sentinel                                    = __bit_iterator<__base_pointer>;
		using const_sentinel                              = __bit_iterator<__base_const_pointer>;
		using size_type                                   = __size_type;
		using difference_type                             = __difference_type;
		using iterator_category                           = typename iterator::iterator_category;
		using iterator_concept                            = typename iterator::iterator_concept;
		static constexpr inline size_type inline_capacity = _S_inline_max_bit_count;

		// constructors
		// constructors: default
		__packed_small_bit_vector() : __alloc_base()
		{
			_S_init_empty_storage_into(this->_M_buf_or_ptr);
		}

		// constructors: copy
		__packed_small_bit_vector(const __packed_small_bit_vector& __right)
		: __packed_small_bit_vector(__right._M_is_sbo(), __right)
		{
		}

		__packed_small_bit_vector(const __packed_small_bit_vector& __right, const allocator& __mem_alloc)
		: __packed_small_bit_vector(__right._M_is_sbo(), __right, __mem_alloc)
		{
		}

		// constructors: move
		__packed_small_bit_vector(__packed_small_bit_vector&& __right)
		: __packed_small_bit_vector(__right._M_is_sbo(), ::std::move(__right))
		{
		}

		__packed_small_bit_vector(__packed_small_bit_vector&& __right, const allocator& __mem_alloc)
		: __packed_small_bit_vector(__right._M_is_sbo(), ::std::move(__right), __mem_alloc)
		{
		}

		// constructors: allocator
		explicit __packed_small_bit_vector(const allocator& __mem_alloc) : __alloc_base(__mem_alloc)
		{
			_S_init_empty_storage_into(this->_M_buf_or_ptr);
		}

		// constructors: rangeable
		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> && !::std::is_same_v<_It, ::std::in_place_t> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list> &&
		                        !__is_same_no_cvref_v<_It, __packed_small_bit_vector>>* = nullptr>
		__packed_small_bit_vector(_It __it, _Sen __sen) : __alloc_base()
		{
			_S_init_storage_into(this->_M_buf_or_ptr, this->get_allocator(), ::std::move(__it), ::std::move(__sen));
		}

		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> && !::std::is_same_v<_It, ::std::in_place_t> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list> &&
		                        !__is_same_no_cvref_v<_It, __packed_small_bit_vector>>* = nullptr>
		__packed_small_bit_vector(_It __it, _Sen __sen, const allocator& __mem_alloc) : __alloc_base(__mem_alloc)
		{
			_S_init_storage_into(this->_M_buf_or_ptr, this->get_allocator(), ::std::move(__it), ::std::move(__sen));
		}

		// constructors: size, value
		explicit __packed_small_bit_vector(size_type __desired_count) : __alloc_base()
		{
			_S_init_storage_count_zero_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count);
		}

		explicit __packed_small_bit_vector(size_type __desired_count, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_storage_count_zero_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count);
		}

		__packed_small_bit_vector(size_type __desired_count, const value_type& __initial_value) : __alloc_base()
		{
			_S_init_storage_count_value_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count,
			     __initial_value
			          ? static_cast<__base_value_type>(::std::numeric_limits<__unsigned_underlying>::max())
			          : __base_value_type());
		}

		__packed_small_bit_vector(
		     size_type __desired_count, const value_type& __initial_value, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_storage_count_value_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count,
			     __initial_value
			          ? static_cast<__base_value_type>(::std::numeric_limits<__unsigned_underlying>::max())
			          : __base_value_type());
		}

		// constructors: initializer_list
		__packed_small_bit_vector(::std::initializer_list<value_type> __il)
		: __packed_small_bit_vector(__il.begin(), __il.end())
		{
		}

		__packed_small_bit_vector(::std::initializer_list<value_type> __il, const allocator& __mem_alloc)
		: __packed_small_bit_vector(__il.begin(), __il.end(), __mem_alloc)
		{
		}

		// constructors: in_place
		// constructors: (in_place) default
		__packed_small_bit_vector(std::in_place_t) : __alloc_base()
		{
			_S_init_empty_storage_into(this->_M_buf_or_ptr);
		}

		explicit __packed_small_bit_vector(std::in_place_t, const allocator& __mem_alloc) noexcept(
		     noexcept(allocator(__mem_alloc)))
		: __alloc_base(__mem_alloc)
		{
			_S_init_empty_storage_into(this->_M_buf_or_ptr);
		}

		// constructors: (in_place) rangeable
		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list>>* = nullptr>
		__packed_small_bit_vector(::std::in_place_t, _It __it, _Sen __sen) : __alloc_base()
		{
			_S_init_base_storage_into(
			     this->_M_buf_or_ptr, this->get_allocator(), ::std::move(__it), ::std::move(__sen));
		}

		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list>>* = nullptr>
		__packed_small_bit_vector(::std::in_place_t, _It __it, _Sen __sen, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_base_storage_into(
			     this->_M_buf_or_ptr, this->get_allocator(), ::std::move(__it), ::std::move(__sen));
		}

		// constructors: (in_place) size, value
		explicit __packed_small_bit_vector(::std::in_place_t, size_type __desired_count) : __alloc_base()
		{
			_S_init_base_storage_count_zero_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count);
		}

		explicit __packed_small_bit_vector(::std::in_place_t, size_type __desired_count, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_base_storage_count_zero_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count);
		}

		__packed_small_bit_vector(
		     ::std::in_place_t, size_type __desired_count, const __base_value_type& __initial_value)
		: __alloc_base()
		{
			_S_init_base_storage_count_value_into(
			     this->_M_buf_or_ptr, this->get_allocator(), __desired_count, __initial_value);
		}

		__packed_small_bit_vector(::std::in_place_t, size_type __desired_count,
		     const __base_value_type& __initial_value, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_base_storage_count_value_into(
			     this->_M_buf_or_ptr, this->get_allocator(), __desired_count, __initial_value);
		}

		// constructors: (in_place) initializer_list
		__packed_small_bit_vector(::std::in_place_t, ::std::initializer_list<__base_value_type> __il)
		: __packed_small_bit_vector(::std::in_place, __il.begin(), __il.end())
		{
		}

		__packed_small_bit_vector(
		     ::std::in_place_t, ::std::initializer_list<__base_value_type> __il, const allocator& __mem_alloc)
		: __packed_small_bit_vector(::std::in_place, __il.begin(), __il.end(), __mem_alloc)
		{
		}

		// destructor
		~__packed_small_bit_vector() noexcept
		{
			this->_M_destroy<true, true>();
		}

		// assignment
		__packed_small_bit_vector&
		operator=(__packed_small_bit_vector&& __right) noexcept
		{
			if constexpr (__alloc_traits::propagate_on_container_move_assignment::value)
				{
					this->_M_steal<true>(::std::move(__right));
				}
			else
				{
					// okay, we're not allowed to propagate,
					// but we still have to transfer??? Oh boy...
					if constexpr (__alloc_traits::is_always_equal::value)
						{
							// equal: cheat and steal
							this->_M_steal<false>(::std::move(__right));
						}
					else
						{
							// okay... so they're not ALWAYS equal
							if (this->get_allocator() == __right.get_allocator())
								{
									// equal: cheat and steal
									this->_M_steal<false>(::std::move(__right));
								}
							else
								{
									// alright, so it's not POCMA, it's not always equal,
									// and the allocators are not equivalent.
									// Don't transfer the allocators, basically do
									// dummy assign...
									// so we have to literally transfer contents
									// one by one by one...
									// maybe we can move the contents?? Hopefully.
									size_type __desired_count = __right.size();
									this->_M_base_assign(
									     ::std::make_move_iterator(__right._M_storage_pointer()),
									     ::std::make_move_iterator(__right._M_storage_pointer_end()),
										&__desired_count);
								}
						}
				}
			return *this;
		}

		__packed_small_bit_vector&
		operator=(const __packed_small_bit_vector& __right)
		{
			// do we have to take the allocator from the right?
			if constexpr (__alloc_traits::propagate_on_container_copy_assignment::value)
				{
					// are they not always equal...?
					if constexpr (!__alloc_traits::is_always_equal::value)
						{
							// ... are they actually not equal... ?!
							if (this->get_allocator() != __right.get_allocator())
								{
									// fek. Clear everything first because
									// we will be trucking over our allocator
									this->_M_destroy<false, true>();
								}
						}
					// propagate the right allocator...
					this->get_allocator() = __right.get_allocator();
				}
			// alright, now vomit out all the elements
			size_type __desired_count = __right.size();
			this->_M_base_assign(__right._M_storage_pointer(), __right._M_storage_pointer_end(), &__desired_count);
			return *this;
		}

		// observers
		reference
		front()
		{
			__base_pointer __first = this->_M_storage_pointer();
			return reference(*__first, this->_M_first_bit_index());
		}

		const_reference
		front() const
		{
			__base_const_pointer __first = this->_M_storage_pointer();
			return const_reference(*__first, this->_M_first_bit_index());
		}

		reference
		back()
		{
			iterator __last = this->end();
			--__last;
			return *__last;
		}

		const_reference
		back() const
		{
			const_iterator __last = this->end();
			--__last;
			return *__last;
		}

		constexpr size_type
		size() const
		{
			if (this->_M_is_sbo())
				{
					return _S_size_sbo(this->_M_buf_or_ptr);
				}
			else
				{
					return _S_size_heap(this->_M_buf_or_ptr);
				}
		}

		constexpr size_type
		capacity() const
		{
			if (this->_M_is_sbo())
				{
					return _S_capacity_sbo(this->_M_buf_or_ptr);
				}
			else
				{
					return _S_capacity_heap(this->_M_buf_or_ptr);
				}
		}

		constexpr bool
		empty() const
		{
			return this->size() == 0;
		}

		constexpr bool
		is_inline()
		{
			return this->_M_is_sbo();
		}

		constexpr allocator&
		get_allocator()
		{
			return __alloc_base::_M_get_value();
		}

		constexpr const allocator&
		get_allocator() const
		{
			return __alloc_base::_M_get_value();
		}

		// observers: iterators
		iterator
		begin()
		{
			return iterator(this->_M_storage_pointer(), this->_M_first_bit_index());
		}

		sentinel
		end()
		{
			size_type __last_bit_it_index = this->_M_last_bit_index();
			__base_pointer __storage_last = this->_M_storage_pointer_end();
			if (__last_bit_it_index != 0)
				{
					--__storage_last;
				}
			return sentinel(__storage_last, __last_bit_it_index);
		}

		const_iterator
		begin() const
		{
			return this->cbegin();
		}

		const_sentinel
		end() const
		{
			return this->cend();
		}

		const_iterator
		cbegin() const
		{
			return const_iterator(this->_M_storage_pointer(), this->_M_first_bit_index());
		}

		const_sentinel
		cend() const
		{
			size_type __last_bit_it_index       = this->_M_last_bit_index();
			__base_const_pointer __storage_last = this->_M_storage_pointer_end();
			if (__last_bit_it_index != 0)
				{
					--__storage_last;
				}
			return const_sentinel(__storage_last, __last_bit_it_index);
		}

		// observers: bit testing
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
			const_iterator __last = this->cend();
			return __bit_find(this->cbegin(), __last, false) == __last;
		}

		constexpr bool
		any() const noexcept
		{
			const_iterator __last = this->cend();
			return __bit_find(this->cbegin(), __last, true) != __last;
		}

		constexpr bool
		none() const noexcept
		{
			const_iterator __last = this->cend();
			return __bit_find(this->cbegin(), __last, true) == __last;
		}

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
					__base_pointer __it_base = ::std::move(__it).base();
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

		// modifiers: insert
		reference
		push_back(value_type __value)
		{
			return this->emplace_back(::std::move(__value));
		}

		template<typename... _Args>
		reference
		emplace_back(_Args&&... __args)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return this->_M_emplace_back_unchecked_0(::std::forward<_Args>(__args)...);
				}

			size_type __starting_capacity = this->capacity();
			if (__starting_size == __starting_capacity)
				{
					// make room first
					_S_grow_storage_of_size_with_strategy(
					     this->get_allocator(), this->_M_buf_or_ptr, __starting_size);
				}

			size_type __desired_size = __starting_size + 1;
			__base_pointer __storage_last =
			     this->_M_storage_pointer() + __bit_to_element_size<__base_value_type>(__desired_size);
			__base_pointer __storage_it = __storage_last - 1;
			size_type __last_bit        = _S_last_bit_index(__starting_size);
			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_reference __storage_ref = *__storage_it;
			reference __ref(__storage_ref, __last_bit);
			if constexpr (noexcept(::std::declval<reference&>().set(::std::forward<_Args>(__args)...)))
				{
					__ref.set(::std::forward<_Args>(__args)...);
				}
			else
				{
					try
						{
							__ref.set(::std::forward<_Args>(__args)...);
						}
					catch (...)
						{
							if (__last_bit == 0)
								{
									_S_destroy(this->get_allocator(), __storage_last - 1);
								}
							// rethrow, and drown myself in tears
							throw;
						}
				}
			this->_M_set_size(__desired_size);
			return __ref;
		}

		reference
		push_front(value_type __value)
		{
			return emplace_front(::std::move(__value));
		}

		template<typename... _Args>
		reference
		emplace_front(_Args&&... __args)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return this->_M_emplace_back_unchecked_0(::std::forward<_Args>(__args)...);
				}

			size_type __starting_capacity  = this->capacity();
			__base_pointer __storage_first = this->_M_storage_pointer();
			if (__starting_size == __starting_capacity)
				{
					// make room first
					__storage_first = _S_grow_storage(this->get_allocator(), this->_M_buf_or_ptr);
				}

			size_type __desired_size = __starting_size + 1;
			__base_pointer __storage_last =
			     __storage_first + __bit_to_element_size<__base_value_type>(__desired_size);
			size_type __last_bit = _S_last_bit_index(__starting_size);
			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_pointer __storage_it = __storage_first;
			value_type __saved          = reference(*__storage_it, __max_binary_index_v<__base_value_type>);
			{
				__base_reference __storage_ref = *__storage_it;
				__storage_ref <<= 1;
				reference __ref(__storage_ref, 0);
				if constexpr (noexcept(::std::declval<reference&>().set(::std::forward<_Args>(__args)...)))
					{
						__ref.set(::std::forward<_Args>(__args)...);
					}
				else
					{
						// Booooy howdy, whoever wrote one of these that can throw
						// I sure do dislike your code IMMENSELY. And while I dislike your
						// code, I love you, and I'm sure that -- with hecka amounts of group
						// therapy -- we can get through whatever made you do this, together.
						// ♥
						try
							{
								__ref.set(::std::forward<_Args>(__args)...);
							}
						catch (...)
							{
								if (__last_bit == 0)
									{
										_S_destroy(this->get_allocator(), __storage_last - 1);
									}
								__storage_ref >>= 1;
								reference(__storage_ref, __max_binary_index_v<__base_value_type>) = __saved;
								// rethrow, and drown myself in tears
								throw;
							}
					}
				++__storage_it;
			}
			for (; __storage_it != __storage_last; ++__storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					value_type __before_shift = reference(__storage_ref, __max_binary_index_v<__base_value_type>);
					__storage_ref <<= 1;
					reference __ref(__storage_ref, 0);
					__ref.set(__saved);
					__saved = __before_shift;
				}
			this->_M_set_size(__desired_size);
			return reference(*__storage_first, 0);
		}

		template<typename... _Args>
		iterator
		emplace(const_iterator __where, _Args&&... __args)
		{
			size_type __where_pos             = __where.position();
			__base_const_pointer __where_base = __where.base();
			__base_pointer __storage_first    = this->_M_storage_pointer();
			if (__where_base == __storage_first && __where_pos == 0)
				{
					reference __bit_ref = this->emplace_front(::std::forward<_Args>(__args)...);
					return iterator(__bit_ref.address(), __bit_ref.position());
				}

			size_type __starting_size         = this->size();
			size_type __starting_storage_size = __bit_to_element_size<__base_value_type>(__starting_size);
			size_type __last_bit              = _S_last_bit_index(__starting_size);
			__base_pointer __storage_last     = __storage_first + __starting_storage_size;
			if (__where_base == __storage_last)
				{
					reference __bit_ref = this->emplace_back(::std::forward<_Args>(__args)...);
					return iterator(__bit_ref.address(), __bit_ref.position());
				}
			--__storage_last;
			if (__where_base == __storage_last && __where_pos == __last_bit)
				{
					reference __bit_ref = this->emplace_back(::std::forward<_Args>(__args)...);
					return iterator(__bit_ref.address(), __bit_ref.position());
				}

			size_type __desired_size      = __starting_size + 1;
			size_type __starting_capacity = this->capacity();
			__storage_last              = __storage_first + __bit_to_element_size<__base_value_type>(__desired_size);
			__base_pointer __storage_it = const_cast<__base_pointer>(__where.base());
			if (__starting_size == __starting_capacity)
				{
					// make room first
					difference_type __preserved_distance = __storage_it - __storage_first;
					__storage_first                      = _S_grow_storage_of_size_with_strategy(
                              this->get_allocator(), this->_M_buf_or_ptr, __starting_size);
					__storage_it   = __storage_first + __preserved_distance;
					__storage_last = __storage_first + __bit_to_element_size<__base_value_type>(__desired_size);
				}

			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_pointer __storage_where       = __storage_it;
			__base_reference __first_storage_ref = *__storage_it;
			value_type __saved = reference(__first_storage_ref, __max_binary_index_v<__base_value_type>);
			if (__where_pos == 0)
				{
					__first_storage_ref <<= 1;
				}
			else
				{
					__shift_left_preserve_right<__base_value_type>(__first_storage_ref, __where_pos, 1);
				}
			reference __first_bit_ref(__first_storage_ref, __where_pos);
			__first_bit_ref.set(::std::forward<_Args>(__args)...);
			++__storage_it;

			for (; __storage_it != __storage_last; ++__storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					reference __before_shift_ref(__storage_ref, __max_binary_index_v<__base_value_type>);
					value_type __before_shift = __before_shift_ref;
					__storage_ref <<= 1;
					reference __ref(__storage_ref, 0);
					__ref.set(__saved);
					__saved = __before_shift;
				}

			this->_M_set_size(__desired_size);
			return iterator(__storage_where, __where_pos);
		}

		iterator
		insert(const_iterator __where, value_type __value)
		{
			return this->emplace(::std::move(__where), ::std::move(__value));
		}

		iterator
		insert(const_iterator __where, size_type __desired_count, value_type __value)
		{
			if (__desired_count == 0)
				{
					return iterator(const_cast<__base_pointer>(::std::move(__where).base()), __where.position());
				}

			// FIXME: a better implementation, please.
			if (__where == this->cbegin())
				{
					size_type __index = 0;
					for (; __index < __desired_count; ++__index)
						{
							this->push_front(__value);
						}
					return this->begin();
				}
			if (__where == this->cend())
				{
					size_type __index = 0;
					for (; __index < __desired_count; ++__index)
						{
							this->push_back(__value);
						}
					return this->end() - __index;
				}

			iterator __where_next = insert(::std::move(__where), __value);
			for (size_type __index = 1; __index < __desired_count; ++__index)
				{
					++__where_next;
					__where_next = insert(::std::move(__where_next), __value);
				}
			return __where_next;
		}

		iterator
		insert(const_iterator __where, ::std::initializer_list<value_type> __il)
		{
			return insert(::std::move(__where), __il.begin(), __il.end());
		}

		template<typename _It, typename _Sen, ::std::enable_if_t<!::std::is_arithmetic_v<_It>>* = nullptr>
		iterator
		insert(const_iterator __where, _It __first, _Sen __last)
		{
			using _SenCategory = typename ::std::iterator_traits<_Sen>::iterator_category;
			if (__first == __last)
				{
					return iterator(const_cast<__base_pointer>(::std::move(__where).base()), __where.position());
				}

			// FIXME: a better implementation, please
			if constexpr (__is_iterator_category_or_better_v<::std::bidirectional_iterator_tag, _SenCategory>)
				{
					if (__where == this->cbegin())
						{
							--__last;
							bool __the_last_time = __last == __first;
							this->push_front(*__last);
							for (; !__the_last_time;)
								{
									--__last;
									__the_last_time = __last == __first;
									this->push_front(*__last);
								}
							return this->begin();
						}
				}
			if (__where == this->cend())
				{
					size_type __index = 0;
					for (; __first != __last; ++__first, (void)++__index)
						{
							this->push_back(*__first);
						}
					return this->end() - __index;
				}

			size_type __preserve_old_position = __where - this->cbegin();

			iterator __where_next = this->insert(::std::move(__where), *__first);
			++__first;
			for (; __first != __last; ++__first)
				{
					++__where_next;
					__where_next = this->insert(::std::move(__where_next), *__first);
				}
			return this->begin() + __preserve_old_position;
		}

		// modifiers: erase
		void
		pop_front() noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return;
				}

			__base_pointer __storage_it   = this->_M_storage_pointer();
			__base_pointer __storage_last = this->_M_storage_pointer_end();
			*__storage_it >>= 1;
			__base_pointer __old_storage_it = __storage_it;
			++__storage_it;
			for (; __storage_it != __storage_last; ++__storage_it, (void)++__old_storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					value_type __saved             = reference(__storage_ref, 0);
					__storage_ref >>= 1;
					reference __old_bit(*__old_storage_it, __max_binary_index_v<__base_value_type>);
					__old_bit = __saved;
				}

			this->_M_maybe_shrink_at_edge_size_1(__starting_size);
			this->_M_set_size(__starting_size - 1);
		}

		void
		pop_back() noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return;
				}
			this->_M_maybe_shrink_at_edge_size_1(__starting_size);
			this->_M_set_size(__starting_size - 1);
		}

		iterator
		erase(const_iterator __where) noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return this->end();
				}

			__base_const_pointer __where_base = __where.base();
			__base_pointer __storage_last     = this->_M_storage_pointer_end();
			if (__where_base == __storage_last)
				{
					this->pop_back();
					return this->end();
				}

			size_type __where_pos = __where.position();
			size_type __last_bit  = _S_last_bit_index(__starting_size);
			--__storage_last;
			if (__storage_last == __where_base)
				{
					size_type __last_bit_index = __last_bit - 1;
					if (__where_pos >= __last_bit_index)
						{
							this->pop_back();
							return this->end();
						}
				}
			++__storage_last;

			__base_pointer __storage_first = this->_M_storage_pointer();
			if (__where_base == __storage_first && __where_pos == 0)
				{
					this->pop_front();
					return iterator(__storage_first, 0);
				}

			__base_pointer __storage_it          = const_cast<__base_pointer>(__where_base);
			__base_pointer __storage_it_where    = __storage_it;
			__base_reference __first_storage_ref = *__storage_it;
			if (__where_pos == 0)
				{
					__first_storage_ref >>= 1;
				}
			else
				{
					__shift_right_preserve_right<__base_value_type>(__first_storage_ref, __where_pos - 1, 1);
				}
			__base_pointer __old_storage_it = __storage_it;
			++__storage_it;
			for (; __storage_it != __storage_last; ++__storage_it, (void)++__old_storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					value_type __preserved         = reference(__storage_ref, 0);
					reference __old_bit(*__old_storage_it, __max_binary_index_v<__base_value_type>);
					__old_bit = __preserved;
					__storage_ref >>= 1;
				}

			this->_M_maybe_shrink_at_edge_size_1(__starting_size);
			this->_M_set_size(__starting_size - 1);
			return iterator(__storage_it_where, __where_pos);
		}

		iterator
		erase(const_iterator __first, const_iterator __last) noexcept(
		     ::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			if (this->empty())
				{
					return this->end();
				}
			if (__first == __last)
				{
					return iterator(const_cast<__base_pointer>(__first.base()), __first.position());
				}

			// FIXME: a better implementation, please
			auto __this_first = this->cbegin();
			auto __this_last  = this->cend();
			if (__first == __this_first && __last == __this_last)
				{
					this->clear();
					return this->end();
				}
			if (__first == __this_first)
				{
					size_type __popfronts = static_cast<size_type>(__last - __first);
					for (size_type __index = 0; __index < __popfronts; ++__index)
						{
							this->pop_front();
						}
					return this->begin();
				}
			else if (__last == __this_last)
				{
					size_type __popbacks = static_cast<size_type>(__last - __first);
					for (size_type __index = 0; __index < __popbacks; ++__index)
						{
							this->pop_back();
						}
					return this->end();
				}

			--__last;
			bool __continue_erasing = __first != __last;
			iterator __where_next   = this->erase(__last);
			for (; __continue_erasing;)
				{
					__last = ::std::move(__where_next);
					--__last;
					__continue_erasing = __last != __first;
					__where_next       = this->erase(__last);
				}
			return __where_next;
		}

		// modifiers: assign
		void
		assign(size_type __desired_count, value_type __value)
		{
			// FIXME: BETTER implementation, please.
			this->clear();
			this->insert(this->cend(), __desired_count, __value);
		}

		void
		assign(::std::initializer_list<value_type> __il)
		{
			this->assign(__il.begin(), __il.end());
		}

		template<typename _It, typename _Sen, ::std::enable_if_t<!::std::is_arithmetic_v<_It>>* = nullptr>
		void
		assign(_It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;

			if (__first == __last)
				{
					this->clear();
					return;
				}

			// FIXME: detect if __first is a bit_iterator
			// and do __base_value_type-based construction of new elements
			// on top of regular copy for even more speed

			__alloc& __mem_alloc = this->get_allocator();

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, _ItCategory>)
				{
					size_type __desired_count        = static_cast<size_type>(__last - __first);
					__base_pointer __storage_pointer = this->_M_storage_pointer();
					if (__desired_count > this->capacity())
						{
							__storage_pointer =
							     _S_grow_storage_to(__mem_alloc, this->_M_buf_or_ptr, __desired_count);
						}
					size_type __storage_size          = this->_M_storage_size();
					size_type __desired_storage_count = __bit_to_element_size<__base_value_type>(__desired_count);
					if (__storage_size < __desired_storage_count)
						{
							_S_trampoline_construct_n_using(__mem_alloc, __storage_pointer + __storage_size,
							     __desired_storage_count - __storage_size, &_S_construct_default);
						}
					iterator __bit_it(__storage_pointer, this->_M_first_bit_index());
					::std::copy_n(__first, __desired_count, __bit_it);
				}
			else
				{
					// F E K .
					// Okay...
					iterator __first_bit_it = this->begin();
					iterator __last_bit_it  = this->end();
					for (;; ++__first)
						{
							if (__first == __last)
								{
									return;
								}
							if (__first_bit_it == __last_bit_it)
								{
									// Well, damn...
									// we are out of space: start using regular insertion
									break;
								}
							*__first_bit_it = *__first;
						}
					while (__first != __last)
						{
							this->push_back(*__first);
						}
				}
		}

		void
		shrink_to_fit()
		{
			size_type __capacity = this->capacity();
			size_type __size     = this->size();
			if (__capacity > __size)
				{
					_S_shrink_storage(this->get_allocator(), this->_M_buf_or_ptr, __size);
				}
		}

		void
		reserve(size_type __desired_count)
		{
			size_type __capacity = this->capacity();
			if (__capacity < __desired_count)
				{
					_S_grow_storage_to(this->get_allocator(), this->_M_buf_or_ptr, __desired_count);
				}
		}

		void
		clear()
		{
			this->_M_destroy<false, false>();
		}

	private:
		__packed_small_bit_vector(bool __is_sbo, const __packed_small_bit_vector& __right)
		: __alloc_base(__alloc_traits::select_on_container_copy_construction(__right.get_allocator()))
		, _M_buf_or_ptr(this->get_allocator(), _S_init_base_storage(_S_storage_pointer(__right._M_buf_or_ptr),
		                                            _S_storage_pointer_end(__right._M_buf_or_ptr)))
		{
			_S_fixup_storage(this->_M_buf_or_ptr, __is_sbo);
		}

		__packed_small_bit_vector(
		     bool __is_sbo, const __packed_small_bit_vector& __right, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(this->get_allocator(), _S_init_base_storage(_S_storage_pointer(__right._M_buf_or_ptr),
		                                            _S_storage_pointer_end(__right._M_buf_or_ptr)))
		{
			_S_fixup_storage(this->_M_buf_or_ptr, __is_sbo);
		}

		__packed_small_bit_vector(bool __is_sbo, __packed_small_bit_vector&& __right)
		: __alloc_base(::std::move(__right.get_allocator()))
		, _M_buf_or_ptr(_S_steal<true>(
		       this->get_allocator(), ::std::move(__right._M_buf_or_ptr), ::std::move(__right.get_allocator())))
		{
			_S_fixup_storage(this->_M_buf_or_ptr, __is_sbo);
		}

		__packed_small_bit_vector(bool __is_sbo, __packed_small_bit_vector&& __right, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(
		       _S_steal(__mem_alloc, ::std::move(__right._M_buf_or_ptr), ::std::move(__right.get_allocator())))
		{
			_S_fixup_storage(this->_M_buf_or_ptr, __is_sbo);
		}

		struct _Storage
		{
			size_type _M_bit_size;
			__base_value_type* _M_last;

			constexpr _Storage() noexcept : _Storage(0, nullptr)
			{
			}

			constexpr _Storage(__base_pointer __last_ptr) noexcept : _Storage(0, __last_ptr)
			{
			}

			constexpr _Storage(size_type __bit_size, __base_pointer __last_ptr) noexcept
			: _M_bit_size(__bit_size), _M_last(__last_ptr)
			{
			}

			constexpr _Storage(const _Storage& __right) noexcept = default;
			constexpr _Storage&
			operator=(const _Storage& __right) noexcept = default;
		};

		struct _HyperSboStorage
		{
			__uninit<__base_value_type> _M_buf[_InlineWords + (_S_extra_storage_words) + 1];
		};

		struct _RegularSboStorage
		{
			// if InlineWords is zero but is some obscene custom integer
			// type (e.g., uint512_t or something) then do not
			// use it, otherwise space losses could be unacceptably large
			// despite having _InlineWords == 0
			using __space_saving_type = ::std::conditional_t<_InlineWords == 0, unsigned char, __base_value_type>;
			size_type _M_bit_size;
			__uninit<__space_saving_type> _M_buf[_InlineWords == 0 ? 1 : _InlineWords];
		};

		using _SboStorage = ::std::conditional_t<_S_is_hyper_sbo_capable, _HyperSboStorage, _RegularSboStorage>;

		struct _EitherStorage
		{
			__base_pointer _M_first;
			union
			{
				_SboStorage _M_buf;
				_Storage _M_ptr;
			};

			constexpr _EitherStorage(const _EitherStorage&) = delete;
			constexpr _EitherStorage(_EitherStorage&&)      = delete;
			constexpr _EitherStorage&
			operator=(const _EitherStorage&) = delete;
			constexpr _EitherStorage&
			operator=(_EitherStorage&&) = delete;

			constexpr _EitherStorage() : _M_first()
			{
				if constexpr (inline_capacity > 0)
					{
						_S_storage_construct_sbo(*this);
					}
				else
					{
						_S_storage_construct_heap(*this);
					}
			}

			constexpr _EitherStorage(::std::in_place_t) : _M_first(), _M_ptr()
			{
				this->_M_ptr._M_bit_size = 0;
				this->_M_first           = nullptr;
				this->_M_ptr._M_last     = nullptr;
			}

			constexpr _EitherStorage(
			     ::std::in_place_t, __alloc& __mem_alloc, bool __is_sbo, const _EitherStorage& __right)
			{
				if constexpr (inline_capacity > 0)
					{
						if (__is_sbo)
							{
								size_type __storage_count = _S_storage_size_heap(__right);
								_S_storage_construct_sbo(*this);

								this->_M_first = ::std::addressof(this->_M_buf._M_buf[0]._M_value);
								__base_pointer __storage_pointer     = this->_M_first;
								__base_pointer __old_storage_pointer = __right._M_first;
								for (size_type __index = 0; __index < __storage_count;
								     (void)++__index, (void)++__storage_pointer, (void)++__old_storage_pointer)
									{
										_S_construct_initial_value(
										     __mem_alloc, __storage_pointer, *__old_storage_pointer);
									}
								_S_set_size_sbo(*this);
								return;
							}
					}
				_S_storage_construct_heap(*this);
				this->_M_first           = __right._M_first;
				this->_M_ptr._M_bit_size = __right._M_ptr._M_bit_size;
				this->_M_ptr._M_last     = __right._M_ptr._M_last;
			}

			constexpr _EitherStorage(
			     ::std::in_place_t, __alloc& __mem_alloc, bool __is_sbo, _EitherStorage&& __right)
			{
				if constexpr (inline_capacity > 0)
					{
						if (__is_sbo)
							{
								size_type __storage_count = _S_storage_size_heap(__right);
								_S_storage_construct_sbo(*this);

								this->_M_first = ::std::addressof(this->_M_buf._M_buf[0]._M_value);
								__base_pointer __storage_pointer     = this->_M_first;
								__base_pointer __old_storage_pointer = __right._M_first;
								for (size_type __index = 0; __index < __storage_count;
								     (void)++__index, (void)++__storage_pointer)
									{
										_S_construct_move_old_pointer(
										     __mem_alloc, __storage_pointer, __old_storage_pointer);
									}
								_S_set_size_sbo(*this);
								return;
							}
					}
				_S_storage_construct_heap(*this);
				this->_M_first           = __right._M_first;
				this->_M_ptr._M_bit_size = __right._M_ptr._M_bit_size;
				this->_M_ptr._M_last     = __right._M_ptr._M_last;
			}
		} _M_buf_or_ptr;

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_storage_construct_sbo(_EitherStorage& __storage)
		{
			if (false)
				{
					// std::construct_at(::std::addressof(__storage._M_buf));
				}
			else
				{
					new (::std::addressof(__storage._M_buf)) _SboStorage();
					_S_fixup_storage(__storage, true);
					_S_set_size_sbo(__storage, 0);
				}
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_storage_construct_heap(_EitherStorage& __storage)
		{
			if (false)
				{
					// std::construct_at(::std::addressof(__storage._M_buf));
				}
			else
				{
					new (::std::addressof(__storage._M_ptr)) _Storage();
				}
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_switch_storage_to_heap(_EitherStorage& __storage)
		{
			if (!_S_is_sbo(__storage))
				{
					return;
				}
			_S_unchecked_switch_storage_to_heap(__storage);
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_unchecked_switch_storage_to_heap(_EitherStorage& __storage)
		{
			// lifetime reset
			if (false /*::std::is_constant_evaluated()*/)
				{
					// FIXME: destroy + launder + construct_at for constexpr
#if 0
					::std::destruct_at(::std::addressof(__storage._M_buf));
					::std::construct_at(::std::addressof(__storage._M_ptr), nullptr);
					__storage._M_first = nullptr;
#endif // :c
				}
			else
				{
					__storage._M_buf.~_SboStorage();
				}
			_S_storage_construct_heap(__storage);
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_switch_storage_to_sbo(_EitherStorage& __storage)
		{
			if (_S_is_sbo(__storage))
				{
					return;
				}
			_S_unchecked_switch_storage_to_sbo(__storage);
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_unchecked_switch_storage_to_sbo(_EitherStorage& __storage)
		{
			if (false /*::std::is_constant_evaluated()*/)
				{
#if 0
					// FIXME: destroy + launder + construct_at for constexpr
					::std::construct_at(::std::addressof(__storage._M_buf), __storage._M_first);
#endif // :c
				}
			else
				{
					__storage._M_ptr.~_Storage();
				}
			_S_storage_construct_sbo(__storage);
		}

		void
		_M_set_size(size_type __desired_size)
		{
			_S_set_size(this->_M_buf_or_ptr, __desired_size);
		}

		static constexpr void
		_S_set_size_sbo(_EitherStorage& __storage, size_type __desired_size)
		{
			if constexpr (_S_is_hyper_sbo_capable)
				{
					constexpr size_type __inverse_shift =
					     __binary_digits_v<__underlying> - _S_bits_for_inline_size;
					constexpr __base_value_type __size_mask =
					     __pos_to_all_1_mask<__base_value_type>(_S_bits_for_inline_size);
					__base_value_type& __last_element =
					     __storage._M_buf._M_buf[_S_end_storage_buffer_index - 1]._M_value;
					__base_value_type __packed_desired_size =
					     static_cast<__base_value_type>(__desired_size << __inverse_shift);
					__last_element = __packed_desired_size | (__last_element & __size_mask);
				}
			else
				{
					__storage._M_buf._M_bit_size = __desired_size;
				}
		}

		static constexpr void
		_S_set_size(_EitherStorage& __storage, size_type __desired_size)
		{
			if (_S_is_sbo(__storage))
				{
					_S_set_size_sbo(__storage, __desired_size);
				}
			else
				{
					__storage._M_ptr._M_bit_size = __desired_size;
				}
		}

		static constexpr size_type
		_S_size_sbo(const _EitherStorage& __storage)
		{
			if constexpr (_S_is_hyper_sbo_capable)
				{
					constexpr size_type __inverse_shift =
					     __binary_digits_v<__underlying> - _S_bits_for_inline_size;
					constexpr __base_value_type __size_mask =
					     __pos_to_all_1_mask<__base_value_type>(_S_bits_for_inline_size);
					const __base_value_type& __last_element =
					     __storage._M_buf._M_buf[_S_end_storage_buffer_index - 1]._M_value;
					__base_value_type __unpacked_desired_size =
					     static_cast<__base_value_type>(__last_element >> __inverse_shift);
					return static_cast<size_type>(__unpacked_desired_size);
				}
			else
				{
					return __storage._M_buf._M_bit_size;
				}
		}

		static constexpr size_type
		_S_size_heap(const _EitherStorage& __storage)
		{
			return __storage._M_ptr._M_bit_size;
		}

		static constexpr size_type
		_S_size(const _EitherStorage& __storage)
		{
			if (_S_is_sbo(__storage))
				{
					return _S_size_sbo(__storage);
				}
			return _S_size_heap(__storage);
		}

		constexpr size_type
		_M_storage_size() const noexcept
		{
			return __bit_to_element_size<__base_value_type>(this->size());
		}

		static constexpr size_type
		_S_storage_size_sbo(const _EitherStorage& __storage) noexcept
		{
			return __bit_to_element_size<__base_value_type>(_S_size_sbo(__storage));
		}

		static constexpr size_type
		_S_storage_size_heap(const _EitherStorage& __storage) noexcept
		{
			return __bit_to_element_size<__base_value_type>(_S_size_heap(__storage));
		}

		constexpr size_type
		_M_storage_capacity() const noexcept
		{
			return _S_storage_capacity(this->_M_buf_or_ptr);
		}

		static constexpr size_type
		_S_storage_capacity_sbo(const _EitherStorage&) noexcept
		{
			if constexpr (_S_is_hyper_sbo_capable)
				{
					return _S_end_storage_buffer_index;
				}
			else
				{
					return _InlineWords;
				}
		}

		static constexpr size_type
		_S_storage_capacity_heap(const _EitherStorage& __storage) noexcept
		{
			return __storage._M_ptr._M_last - __storage._M_first;
		}

		static constexpr size_type
		_S_storage_capacity(const _EitherStorage& __storage) noexcept
		{
			if (_S_is_sbo(__storage))
				{
					return _S_storage_capacity_sbo(__storage);
				}
			return _S_storage_capacity_heap(__storage);
		}

		static constexpr size_type
		_S_capacity_heap(const _EitherStorage& __storage) noexcept
		{
			return __element_to_bit_size<__base_value_type>(_S_storage_capacity_heap(__storage));
		}

		static constexpr size_type
		_S_capacity_sbo(const _EitherStorage& __storage) noexcept
		{
			return __element_to_bit_size<__base_value_type>(_S_storage_capacity_sbo(__storage));
		}

		static constexpr size_type
		_S_capacity(const _EitherStorage& __storage) noexcept
		{
			if (_S_is_sbo(__storage))
				{
					return _S_capacity_sbo(__storage);
				}
			return _S_capacity_heap(__storage);
		}

		constexpr bool
		_M_is_sbo() const noexcept
		{
			return _S_is_sbo(this->_M_buf_or_ptr);
		}

		static constexpr bool
		_S_is_sbo(const _EitherStorage& __storage) noexcept
		{
			if constexpr (_S_inline_max_bit_count < 1)
				{
					return false;
				}
			else
				{
					__base_const_pointer __storage_pointer = _S_storage_pointer(__storage);
					__base_const_pointer __lower_inline_storage_pointer =
					     ::std::addressof(__storage._M_buf._M_buf[0]._M_value);
					__base_const_pointer __upper_inline_storage_pointer =
					     ::std::addressof((*(__storage._M_buf._M_buf + _S_end_storage_buffer_index))._M_value);
					return __storage_pointer >= __lower_inline_storage_pointer &&
					       __storage_pointer < __upper_inline_storage_pointer;
				}
		}

		static constexpr bool
		_S_is_sbo_size(size_type __size) noexcept
		{
			return _S_inline_max_bit_count > 0 && __size <= _S_inline_max_bit_count;
		}

		constexpr __base_const_pointer
		_M_storage_pointer() const noexcept
		{
			return _S_storage_pointer(this->_M_buf_or_ptr);
		}

		constexpr __base_pointer
		_M_storage_pointer() noexcept
		{
			return _S_storage_pointer(this->_M_buf_or_ptr);
		}

		static constexpr __base_const_pointer
		_S_storage_pointer(const _EitherStorage& __storage) noexcept
		{
			return __storage._M_first;
		}

		static constexpr __base_pointer
		_S_storage_pointer(_EitherStorage& __storage) noexcept
		{
			return __storage._M_first;
		}

		constexpr __base_pointer
		_M_storage_pointer_end() noexcept
		{
			return _S_storage_pointer_end(this->_M_buf_or_ptr);
		}

		constexpr __base_const_pointer
		_M_storage_pointer_end() const noexcept
		{
			return _S_storage_pointer_end(this->_M_buf_or_ptr);
		}

		static constexpr __base_pointer
		_S_storage_pointer_end(_EitherStorage& __storage) noexcept
		{
			if (_S_is_sbo(__storage))
				{
					return __storage._M_first + _S_storage_size_sbo(__storage);
				}
			else
				{
					return __storage._M_first +
					       __bit_to_element_size<__base_value_type>(__storage._M_ptr._M_bit_size);
				}
		}

		static constexpr __base_const_pointer
		_S_storage_pointer_end(const _EitherStorage& __storage) noexcept
		{
			if (_S_is_sbo(__storage))
				{
					return _S_storage_pointer(__storage) + _S_storage_size_sbo(__storage);
				}
			else
				{
					return _S_storage_pointer(__storage) +
					       __bit_to_element_size<__base_value_type>(__storage._M_ptr._M_bit_size);
				}
		}

		constexpr size_type
		_M_first_bit_index() const noexcept
		{
			return _S_first_bit_index();
		}

		static constexpr size_type
		_S_first_bit_index() noexcept
		{
			return 0;
		}

		constexpr size_type
		_M_last_bit_index() const noexcept
		{
			return _S_last_bit_index(this->size());
		}

		static constexpr size_type
		_S_last_bit_index(size_type __pos) noexcept
		{
			return __pos % __binary_digits_v<__base_value_type>;
		}

		void
		_M_maybe_shrink_at_edge_bit_1(size_type __last_bit)
		{
			if (__last_bit == 0)
				{
					__alloc& __mem_alloc = this->get_allocator();
					_S_destroy(__mem_alloc, this->_M_storage_pointer_end() - 1, 1);
				}
		}

		void
		_M_maybe_shrink_at_edge_size_1(size_type __starting_size)
		{
			size_type __last_bit = _S_last_bit_index(__starting_size - 1);
			this->_M_maybe_shrink_at_edge_bit_1(__last_bit);
		}

		void
		_M_construct_at_edge_1(size_type __last_bit, __base_pointer __storage_last)
		{
			if (__last_bit != 0)
				{
					return;
				}
			__alloc& __mem_alloc = this->get_allocator();
			_S_construct_default(__mem_alloc, __storage_last - 1);
		}

		template<typename... _Args>
		reference
		_M_emplace_back_unchecked_0(_Args&&... __args)
		{
			__base_pointer __storage_first = this->_M_storage_pointer();
			_S_construct_default(this->get_allocator(), __storage_first);
			__base_reference __storage_ref = *__storage_first;
			reference __ref(__storage_ref, 0);
			__ref.set(::std::forward<_Args>(__args)...);
			this->_M_set_size(1);
			return __ref;
		}

		template<typename _It, typename _Sen>
		void
		_M_base_assign(_It __first, _Sen __last, size_type* __maybe_desired_count = nullptr)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;

			if (__first == __last)
				{
					this->clear();
					return;
				}

			__alloc& __mem_alloc = this->get_allocator();

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, _ItCategory>)
				{
					size_type __desired_storage_count = static_cast<size_type>(__last - __first);
					size_type __desired_count = __maybe_desired_count ? *__maybe_desired_count : __element_to_bit_size<__base_value_type>(__desired_storage_count);
					size_type __storage_capacity          = this->_M_storage_capacity();
					__base_pointer __storage_pointer      = this->_M_storage_pointer();
					bool __orphans_in_the_allocators_wake = __desired_storage_count > __storage_capacity;
					if (__orphans_in_the_allocators_wake)
						{
							__storage_pointer =
							     _S_grow_storage_to<true>(__mem_alloc, this->_M_buf_or_ptr, __desired_count);
						}
					size_type __storage_size = this->_M_storage_size();
					if (__orphans_in_the_allocators_wake)
						{
							constexpr _S_construct_iterator_type<_It> __construction_fx = &_S_construct_iterator<_It>;
							this->_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer,
								__desired_storage_count, __desired_storage_count,
								__construction_fx, __first);
							_S_set_size(this->_M_buf_or_ptr, __desired_count);
						}
					else
						{
							for (size_type __index = 0; __index < __storage_size && __first != __last;
							     (void)++__index, (void)++__first)
								{
									*(__storage_pointer + __index) = *__first;
								}
							constexpr _S_construct_iterator_type<_It> __construction_fx = &_S_construct_iterator<_It>;
							this->_S_trampoline_construct_using<false>(__mem_alloc,
							     __storage_pointer + __storage_size, __storage_capacity, __first, __last,
							     __construction_fx);
							_S_set_size(this->_M_buf_or_ptr, __desired_count);
						}
				}
			else
				{
					// FIXME: exception safety the whole damn block...
					size_type __current_storage_size = 0;
					__base_pointer __first_it        = this->_M_storage_pointer();
					__base_pointer __last_it         = this->_M_storage_pointer_end();
					for (;; ++__first)
						{
							if (__first == __last)
								{
									return;
								}
							if (__first_it == __last_it)
								{
									break;
								}
							*__first_it = *__first;
							++__current_storage_size;
						}
					while (__first != __last)
						{
							if (__first_it == __last_it)
								{
									size_type __old_storage_size = __last_it - __first_it;
									__first_it = _S_grow_storage_of_size_with_strategy(__mem_alloc,
									     this->_M_buf_or_ptr,
									     __element_to_bit_size<__base_value_type>(__old_storage_size));
									__first_it += __old_storage_size;
									__last_it = this->_M_storage_pointer_end();
								}
							_S_construct_iterator<_It>(__mem_alloc, __first_it, __first);
							++__first_it;
							++__first;
							++__current_storage_size;
						}
					size_type __desired_count = __maybe_desired_count ? *__maybe_desired_count : __element_to_bit_size<__base_value_type>(__current_storage_size);
					this->_M_set_size(__desired_count);
				}
		}

		template<bool _Destruct, bool _Deallocate = true>
		void
		_M_destroy()
		{
			const bool __using_sbo = this->_M_is_sbo();
			const size_type __storage_size =
			     __using_sbo ? _S_storage_size_sbo(this->_M_buf_or_ptr) : _S_storage_size_heap(this->_M_buf_or_ptr);
			__alloc& __mem_alloc = this->get_allocator();
			if (__using_sbo)
				{
					__base_pointer __storage_pointer = this->_M_storage_pointer();
					_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
					if constexpr (!_Destruct)
						{
							this->_M_set_size(0);
						}
					return;
				}

			__base_pointer __storage_pointer = this->_M_storage_pointer();
			size_type __storage_capacity     = _S_storage_capacity_heap(this->_M_buf_or_ptr);
			if constexpr (!_Destruct)
				{
					if constexpr (inline_capacity > 0)
						{
							if constexpr (_Deallocate)
								{
									_S_unchecked_switch_storage_to_sbo(this->_M_buf_or_ptr);
									_S_fixup_storage(this->_M_buf_or_ptr, true);
								}
							this->_M_set_size(0);
						}
					else
						{
							if constexpr (_Deallocate)
								{
									this->_M_buf_or_ptr._M_first       = nullptr;
									this->_M_buf_or_ptr._M_ptr._M_last = nullptr;
								}
							this->_M_set_size(0);
						}
				}
			if (__storage_pointer != nullptr && __storage_capacity != 0)
				{
					_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
					if constexpr (_Deallocate)
						{
							__alloc_traits::deallocate(__mem_alloc, __storage_pointer, __storage_capacity);
						}
				}
		}

		void
		_M_revive()
		{
			if (this->_M_is_sbo())
				{
					return;
				}
			if (this->_M_buf_or_ptr._M_first != this->_M_buf_or_ptr._M_ptr._M_last)
				{
					return;
				}

			// must revive container
			_S_grow_storage_of_size_with_strategy<false>(this->get_allocator(), this->_M_buf_or_ptr, 0);
		}

		template<bool _Pocma>
		void
		_M_steal(__packed_small_bit_vector&& __right)
		{
			this->clear();
			if constexpr (_Pocma)
				{
					// totes yoink
					this->__alloc_base::get_value() = ::std::move(__right.get_allocator());
				}
			_S_steal_into<_Pocma>(this->get_allocator(), ::std::move(this->_M_buf_or_ptr),
			     ::std::move(__right._M_buf_or_ptr), ::std::move(__right.get_allocator()));
		}

		template<bool _Pocma>
		static _EitherStorage
		_S_steal(
		     allocator& __left_alloc, _EitherStorage&& __left, _EitherStorage&& __right, allocator&& __right_alloc)
		{
			const bool __right_using_sbo = _S_is_sbo(__right);
			if (__right_using_sbo)
				{
					__alloc& __pocma_alloc = _Pocma ? __left_alloc : __right_alloc;
					// gotta do the SBO shuffle...
					__base_pointer __storage_pointer       = __left._M_first;
					__base_pointer __right_storage_pointer = __right._M_first;
					size_type __right_storage_size         = __right._M_buf_or_ptr._M_buf._M_storage_size();
					_S_construct_move_old_pointer<false>(__left_alloc, __storage_pointer, __right_storage_size);
					// must destroy old SBO contents
					// since they can't actually be stolen!
					_S_destroy(__pocma_alloc, __right_storage_pointer, __right_storage_size);
					return __left;
				}
			else
				{
					// just steal guts
					__left                = ::std::move(__right._M_buf_or_ptr);
					__right._M_buf_or_ptr = _S_init_empty_heap_storage();
				}
		}

		template<bool _Pocma>
		static void
		_S_steal_into(
		     allocator& __left_alloc, _EitherStorage&& __left, _EitherStorage&& __right, allocator&& __right_alloc)
		{
			__left = _S_steal<_Pocma>(__left_alloc, ::std::move(__right), ::std::move(__right_alloc));
		}

		template<bool _DeallocateOnFailure, typename _Fx, typename... _Args>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_trampoline_construct_n_using(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     size_type __alloc_capacity, size_type __desired_count, _Fx&& __fx,
		     _Args&&... __args) noexcept(::std::is_nothrow_invocable_v<_Fx, __alloc&, __base_pointer, _Args...>)
		{
			static constexpr bool __is_construct_noexcept =
			     ::std::is_nothrow_invocable_v<_Fx, __alloc&, __base_pointer, _Args...>;
			size_type __lifetime_count = 0;
			if constexpr (__is_construct_noexcept)
				{
					(void)__alloc_capacity;
					for (; __lifetime_count < __desired_count; ++__lifetime_count)
						{
							__fx(__mem_alloc, __storage_pointer + __lifetime_count,
							     ::std::forward<_Args>(__args)...);
						}
				}
			else
				{
					try
						{
							for (; __lifetime_count < __desired_count; ++__lifetime_count)
								{
									__fx(__mem_alloc, __storage_pointer + __lifetime_count,
									     ::std::forward<_Args>(__args)...);
								}
						}
					catch (...)

						{
							// destroy everything that failed to construct
							_S_destroy(__mem_alloc, __storage_pointer, __lifetime_count);
							if constexpr (_DeallocateOnFailure)
								{
									// nuke memory if we need to
									__alloc_traits::deallocate(
									     __mem_alloc, __storage_pointer, __alloc_capacity);
								}
							else
								{
									(void)__alloc_capacity;
								}
							// rethrow exception
							throw;
						}
				}
		}

		template<bool _DeallocateOnFailure, typename _It, typename _Sen, typename _Fx, typename... _Args>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_trampoline_construct_using(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     size_type __alloc_capacity, _It __first, _Sen __last, _Fx&& __fx,
		     _Args&&... __args) noexcept(::std::is_nothrow_invocable_v<_Fx, __alloc&, __base_pointer, _It&, _Args...>)
		{
			static constexpr bool __is_construct_noexcept =
			     ::std::is_nothrow_invocable_v<_Fx, __alloc&, __base_pointer, _It&, _Args...>;
			size_type __lifetime_count = 0;
			if constexpr (__is_construct_noexcept)
				{
					(void)__alloc_capacity;
					for (; __first != __last; (void)++__lifetime_count, ++__first)
						{
							__fx(__mem_alloc, __storage_pointer + __lifetime_count, __first,
							     ::std::forward<_Args>(__args)...);
						}
				}
			else
				{
					try
						{
							for (; __first != __last; (void)++__lifetime_count, ++__first)
								{
									__fx(__mem_alloc, __storage_pointer + __lifetime_count, __first,
									     ::std::forward<_Args>(__args)...);
								}
						}
					catch (...)
						{
							// destroy everything that failed to construct
							_S_destroy(__mem_alloc, __storage_pointer, __lifetime_count);
							if constexpr (_DeallocateOnFailure)
								{
									// nuke memory if we need to
									__alloc_traits::deallocate(
									     __mem_alloc, __storage_pointer, __alloc_capacity);
								}
							else
								{
									(void)__alloc_capacity;
								}
							// rethrow exception
							throw;
						}
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_default(__alloc& __mem_alloc, __base_pointer __storage_pointer) noexcept(
		     ::std::is_nothrow_default_constructible_v<__base_value_type>)
		{
			if constexpr (::std::is_trivial_v<__base_value_type> &&
			              !__is_detected_v<__allocator_construct_invocable_test, __alloc&, __base_pointer>)
				{
					(void)__mem_alloc;
					new (__storage_pointer) __base_value_type;
				}
			else
				{
					__alloc_traits::construct(__mem_alloc, __storage_pointer);
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_initial_value(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     const __base_value_type& __initial_value) noexcept(noexcept(__alloc_traits::construct(__mem_alloc,
		     __storage_pointer, __initial_value)))
		{
			__alloc_traits::construct(__mem_alloc, __storage_pointer, __initial_value);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_move_old_pointer(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     __base_pointer& __old_pointer) noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			if (::std::is_nothrow_move_constructible_v<__base_value_type>)
				{
					__alloc_traits::construct(__mem_alloc, __storage_pointer, ::std::move(*__old_pointer));
				}
			else
				{
					// must degrade to a copy operation,
					// otherwise a throw from a move would be impossible to
					// recover from for the __base_value_type in question
					__alloc_traits::construct(__mem_alloc, __storage_pointer, *__old_pointer);
				}
			++__old_pointer;
		}

		template<typename _It>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_iterator(__alloc& __mem_alloc, __base_pointer __storage_pointer, _It& __it) noexcept(
		     ::std::is_nothrow_constructible_v<__base_value_type, decltype(*__it)>)
		{
			__alloc_traits::construct(__mem_alloc, __storage_pointer, *__it);
		}

		static constexpr size_type
		_S_growth_strategy(size_type __old_size)
		{
			return __old_size < 1 ? (_S_inline_max_bit_count < 1 ? __binary_digits_v<__base_value_type> * 4
			                                                     : _S_inline_max_bit_count * 2)
			                      : __old_size * 2;
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage(__alloc& __mem_alloc, _EitherStorage& __storage)
		{
			return _S_grow_storage_of_size_with_strategy(__mem_alloc, __storage, _S_size(__storage));
		}

		template<bool _OrphanObjects = false>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_to(__alloc& __mem_alloc, _EitherStorage& __storage, size_type __desired_capacity)
		{
			return _S_grow_storage_of_size_to<_OrphanObjects>(
			     __mem_alloc, __storage, _S_size(__storage), __desired_capacity);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_of_size_with_strategy(__alloc& __mem_alloc, _EitherStorage& __storage, size_type __old_size)
		{
			return _S_grow_storage_of_size_to(__mem_alloc, __storage, __old_size, _S_growth_strategy(__old_size));
		}

		template<bool _OrphanObjects = false>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_of_size_to(
		     __alloc& __mem_alloc, _EitherStorage& __storage, size_type __old_size, size_type __desired_capacity)
		{
			bool __using_sbo = _S_is_sbo(__storage);
			if (__using_sbo)
				{
					if (_S_is_sbo_size(__desired_capacity))
						{
							// we are already in SBO, the capacity is already fine
							return _S_storage_pointer(__storage);
						}
					// transfer to non-SBO storage and grow
					return _S_transfer_inline_to_heap(__mem_alloc, __storage, __desired_capacity);
				}
			else
				{
					size_type __desired_storage_capacity =
					     __bit_to_element_size<__base_value_type>(__desired_capacity);
					size_type __old_storage_capacity = _S_storage_capacity(__storage);
					if (__desired_storage_capacity <= __old_storage_capacity)
						{
							// nothing needs doing
							return _S_storage_pointer(__storage);
						}

					// need to grow
					__base_pointer __old_storage_pointer = _S_storage_pointer(__storage);
					size_type __old_storage_size         = __bit_to_element_size<__base_value_type>(__old_size);

					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_capacity);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}

					if (__old_storage_pointer != nullptr)
						{
							__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
							if (!_OrphanObjects)
								{
									_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer,
									     __desired_storage_capacity, __old_storage_size,
									     &_S_construct_move_old_pointer, __old_storage_pointer_move_arg);
								}
							_S_destroy(__mem_alloc, __old_storage_pointer, __old_storage_size);
							__alloc_traits::deallocate(
							     __mem_alloc, __old_storage_pointer, __old_storage_capacity);
						}

					__storage._M_first       = __storage_pointer;
					__storage._M_ptr._M_last = __storage_pointer + __desired_storage_capacity;
					if (!_OrphanObjects)
						{
							_S_set_size(__storage, __old_storage_size);
						}
					return __storage_pointer;
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_shrink_storage(__alloc& __mem_alloc, _EitherStorage& __storage, __base_pointer __old_storage_pointer,
		     size_type __desired_capacity)
		{
			bool __using_sbo                     = _S_is_sbo(__storage, __old_storage_pointer);
			size_type __desired_storage_capacity = __bit_to_element_size<__base_value_type>(__desired_capacity);
			size_type __old_size                 = _S_size(__storage);
			size_type __old_storage_size         = _S_storage_size(__storage);
			size_type __old_storage_capacity     = _S_storage_capacity(__storage);

			if (_S_is_sbo_size(__desired_capacity))
				{
					if (__using_sbo)
						{
							// already using SBO: just shrink bit size
							// and deconstruct edge words
							size_type __desired_old_storage_size_diff =
							     __old_storage_size - __desired_storage_capacity;
							_S_destroy(__mem_alloc, __old_storage_pointer + __desired_storage_capacity,
							     __desired_old_storage_size_diff);
							_S_set_size_sbo(__storage, __desired_capacity);
							return _S_storage_pointer(__storage);
						}

					// lifetime reset
					_S_unchecked_switch_storage_to_sbo(__storage);
					_S_fixup_storage(__storage._M_buf_or_ptr, true);
					__base_pointer __storage_pointer = _S_storage_pointer(__storage);
					if constexpr (::std::is_nothrow_invocable_v<decltype(&_S_construct_move_old_pointer), __alloc&,
					                   __base_pointer, __base_pointer>)
						{
							__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
							_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
							     __desired_storage_capacity, &_S_construct_move_old_pointer,
							     __old_storage_pointer_move_arg);
						}
					else
						{
							// awh geez
							// tread carefully now...
							try
								{
									__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
									_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
									     __desired_storage_capacity, &_S_construct_move_old_pointer,
									     __old_storage_pointer_move_arg);
								}
							catch (...)
								{
									// something went to shit, fast!
									// Restore old pointers, don't deallocate/destroy,
									// rethrow!
									_S_unchecked_switch_storage_to_heap(__storage);
									__storage._M_first       = __old_storage_pointer;
									__storage._M_ptr._M_last = __old_storage_pointer + __old_storage_capacity;
									__storage._M_ptr._M_bit_size = __old_size;
									throw;
								}
						}
					_S_destroy(__mem_alloc, __old_storage_pointer, __old_storage_size);
					__alloc_traits::deallocate(__mem_alloc, __old_storage_pointer, __old_storage_capacity);

					_S_set_size(__storage, __desired_capacity);

					return __storage_pointer;
				}
			else
				{
					// shrink, but no SBO
					// also implies old size was not SBO to begin with
#if 0
					assert(!__using_sbo);
#endif
					// WARNING: C++ has no realloc
					// method on allocators
					// this means we allocate,
					// move, destroy, and then cry bitter tears
					// if it all fails
					// would be nice if there was a reallocate method
					// that did all of this _for_ me >.>
					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_capacity);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}
					__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
					_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer,
					     __desired_storage_capacity, __desired_storage_capacity, &_S_construct_move_old_pointer,
					     __old_storage_pointer_move_arg);

					size_type __storage_capacity = __storage._M_ptr._M_storage_capacity();
					size_type __storage_size     = __storage._M_ptr._M_storage_size();
					_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
					__alloc_traits::deallocate(__mem_alloc, __storage_pointer, __storage_capacity);

					return __storage_pointer;
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_transfer_inline_to_heap_with_strategy(__alloc& __mem_alloc, _EitherStorage& __storage)
		{
			size_type __old_size = _S_size(__storage);
			return _S_transfer_inline_to_heap(__mem_alloc, __storage, _S_growth_strategy(__old_size));
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_transfer_inline_to_heap(__alloc& __mem_alloc, _EitherStorage& __storage, size_type __desired_capacity)
		{
			if (!_S_is_sbo(__storage))
				{
					return _S_storage_pointer(__storage);
				}
			size_type __old_size                 = _S_size_sbo(__storage);
			size_type __old_storage_size         = _S_storage_size_sbo(__storage);
			__base_pointer __old_storage_pointer = _S_storage_pointer(__storage);
			size_type __desired_storage_capacity = __bit_to_element_size<__base_value_type>(__desired_capacity);
			__base_pointer __storage_pointer     = __alloc_traits::allocate(__mem_alloc, __desired_storage_capacity);
			if (__storage_pointer == nullptr)
				{
					throw ::std::bad_alloc();
				}

			__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
			_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer, __desired_storage_capacity,
			     __old_storage_size, &_S_construct_move_old_pointer, __old_storage_pointer_move_arg);

			// destroy union data
			_S_destroy(__mem_alloc, __old_storage_pointer, __old_storage_size);

			// finally, swap union storage...
			_S_unchecked_switch_storage_to_heap(__storage);
			__storage._M_first           = __storage_pointer;
			__storage._M_ptr._M_bit_size = __old_size;
			__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_capacity;

			return __storage_pointer;
		}

		static constexpr std::pair<_EitherStorage, bool>
		_S_init_empty_storage()
		{
			if constexpr (_S_inline_max_bit_count < 1)
				{
					return _S_init_empty_heap_storage();
				}
			else
				{
					return { _EitherStorage(), true };
				}
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_empty_storage_into(_EitherStorage& __storage)
		{
			if constexpr (_S_inline_max_bit_count < 1)
				{
					return _S_init_empty_heap_storage_into(__storage);
				}
			else
				{
					_S_switch_storage_to_sbo(__storage);
					_S_set_size_sbo(__storage, 0);
					_S_fixup_storage(__storage, true);
					return true;
				}
		}

		static constexpr void
		_S_fixup_storage(_EitherStorage& __storage, bool __is_sbo)
		{
			if constexpr (inline_capacity > 0)
				{
					if (__is_sbo)
						{
							__storage._M_first = ::std::addressof(__storage._M_buf._M_buf[0]._M_value);
						}
				}
			else
				{
					(void)__is_sbo;
				}
		}

		static constexpr std::pair<_EitherStorage, bool>
		_S_init_empty_heap_storage()
		{
			return { _EitherStorage(::std::in_place), false };
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_empty_heap_storage_into(_EitherStorage& __storage)
		{
			_S_switch_storage_to_heap(__storage);
			__storage._M_first           = nullptr;
			__storage._M_ptr._M_last     = nullptr;
			__storage._M_ptr._M_bit_size = 0;
			return false;
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_base_storage(__alloc& __mem_alloc, _It __first, _Sen __last)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_base_storage_into(
			     __storage_and_is_sbo.first, __mem_alloc, ::std::move(__first), ::std::move(__last));
			return __storage_and_is_sbo;
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR bool
		_S_init_base_storage_into(_EitherStorage& __storage, __alloc& __mem_alloc, _It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;
			if (__first == __last)
				{
					// nothing to write into
					return _S_init_empty_storage_into(__storage);
				}

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, _ItCategory>)
				{
					size_type __desired_storage_count = static_cast<size_type>(__last - __first);
					size_type __desired_count = __element_to_bit_size<__base_value_type>(__desired_storage_count);
					if (_S_is_sbo_size(__desired_count))
						{
							_S_switch_storage_to_sbo(__storage);
							__base_pointer __storage_pointer                  = _S_storage_pointer(__storage);
							constexpr _S_construct_iterator_type<_It> __construction_fx = &_S_construct_iterator<_It>;
							_S_trampoline_construct_using<false>(__mem_alloc, __storage_pointer, 0,
							     ::std::move(__first), ::std::move(__last), __construction_fx);
							_S_set_size_sbo(__storage, __desired_count);
							return true;
						}

					_S_storage_construct_heap(__storage);
					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}
					constexpr _S_construct_iterator_type<_It> __construction_fx = &_S_construct_iterator<_It>;
					_S_trampoline_construct_using<true>(__mem_alloc, __storage_pointer, __desired_storage_count,
					     ::std::move(__first), ::std::move(__last), __construction_fx);
					__storage._M_first           = __storage_pointer;
					__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_count;
					__storage._M_ptr._M_bit_size = __desired_count;
					return false;
				}
			else
				{
					_S_switch_storage_to_sbo(__storage);
					size_type __current_size         = __binary_digits_v<__base_value_type>;
					size_type __current_index        = 0;
					__base_pointer __storage_pointer = _S_storage_pointer(__storage);
					// FIXME: this storage needs the Strong Exception Guarantee
					for (; __first != __last && _S_is_sbo_size(__current_size);
					     (void)(__current_size += __binary_digits_v<__base_value_type>),
					     (void)(__current_index += __binary_digits_v<__base_value_type>), (void)++__first,
					     (void)++__storage_pointer)
						{
							_S_construct_iterator(__mem_alloc, __storage_pointer, __first);
							_S_set_size(__storage, __current_size);
						}
					if (__first == __last)
						{
							return false;
						}
					size_type __transfer_size = __bit_to_element_size<__base_value_type>(__current_index);
					__storage_pointer         = _S_transfer_inline_to_heap_with_strategy(__mem_alloc, __storage);
					__storage_pointer += __transfer_size;
					for (; __first != __last; (void)(__current_size += __binary_digits_v<__base_value_type>),
					     (void)(__current_index += __binary_digits_v<__base_value_type>), (void)++__first,
					     (void)++__storage_pointer)
						{
							if (__storage_pointer == __storage._M_ptr._M_last)
								{
									size_type __current_storage_size =
									     __bit_to_element_size<__base_value_type>(__current_index);
									__storage_pointer = _S_grow_storage_of_size_with_strategy(
									     __mem_alloc, __storage, __current_index);
									__storage_pointer += __current_storage_size;
								}
							_S_construct_iterator(__mem_alloc, __storage_pointer, __first);
							_S_set_size(__storage, __current_size);
						}
					return false;
				}
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_storage(__alloc& __mem_alloc, _It __first, _Sen __last)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_into(
			     __storage_and_is_sbo.first, __mem_alloc, ::std::move(__first), ::std::move(__last));
			return __storage_and_is_sbo;
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_storage_into(_EitherStorage& __storage, __alloc& __mem_alloc, _It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;
			if (__first == __last)
				{
					// nothing to write into
					return _S_init_empty_storage_into(__storage);
				}

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, _ItCategory>)
				{
					size_type __desired_count         = static_cast<size_type>(__last - __first);
					size_type __desired_storage_count = __bit_to_element_size<__base_value_type>(__desired_count);
					if (_S_is_sbo_size(__desired_count))
						{
							_S_switch_storage_to_sbo(__storage);
							__base_pointer __storage_pointer = _S_storage_pointer(__storage);
							_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
							     __desired_storage_count, &_S_construct_default);
							iterator __storage_it(__storage_pointer, _S_first_bit_index());
							::std::copy(::std::move(__first), ::std::move(__last), __storage_it);
							_S_set_size_sbo(__storage, static_cast<size_type>(__desired_count));
							return true;
						}

					_S_storage_construct_heap(__storage);
					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}
					_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer, __desired_storage_count,
					     __desired_storage_count, &_S_construct_default);
					__storage._M_first           = __storage_pointer;
					__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_count;
					__storage._M_ptr._M_bit_size = __desired_count;
					iterator __storage_it(__storage_pointer, 0);
					::std::copy(::std::move(__first), ::std::move(__last), __storage_it);
					return false;
				}
			else
				{
					_S_switch_storage_to_sbo(__storage);
					size_type __current_size         = 1;
					size_type __current_index        = 0;
					__base_pointer __storage_pointer = _S_storage_pointer(__storage);
					iterator __storage_it(__storage_pointer, _S_first_bit_index());
					// FIXME: this storage needs the Strong Exception Guarantee
					for (; __first != __last && _S_is_sbo_size(__current_size);
					     ++__current_size, (void)++__current_index, (void)++__first, (void)++__storage_it)
						{
							if (__storage_it.position() == 0)
								{
									_S_construct_default(__mem_alloc, __storage_it.base());
								}
							*__storage_it = *__first;
							_S_set_size(__storage, __current_size);
						}

					if (__first == __last)
						{
							return false;
						}

					// well, we ran out of Small Buffer bits...
					size_type __current_storage_size = __bit_to_element_size<__base_value_type>(__current_index);
					__storage_pointer = _S_transfer_inline_to_heap_with_strategy(__mem_alloc, __storage);
					__storage_it = iterator(__storage_pointer + __current_storage_size, __storage_it.position());

					for (; __first != __last;
					     ++__current_size, (void)++__current_index, (void)++__first, (void)++__storage_it)
						{
							__base_pointer __storage_it_base = __storage_it.base();
							if (__storage_it_base == __storage._M_ptr._M_last)
								{
									size_type __current_storage_size =
									     __bit_to_element_size<__base_value_type>(__current_index);
									__storage_pointer = _S_grow_storage_of_size_with_strategy(
									     __mem_alloc, __storage, __current_index);
									__storage_it_base = __storage_pointer + __current_storage_size;
									__storage_it      = iterator(__storage_it_base, __storage_it.position());
								}
							if (__storage_it.position() == 0)
								{
									_S_construct_default(__mem_alloc, __storage_it_base);
								}
							*__storage_it = *__first;
							_S_set_size(__storage, __current_size);
						}
					return false;
				}
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_storage_count_value(
		     __alloc& __mem_alloc, size_type __desired_count, const __base_value_type& __initial_value)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_count_value_into(
			     __storage_and_is_sbo.first, __mem_alloc, __desired_count, __initial_value);
			return __storage_and_is_sbo;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_storage_count_value_into(_EitherStorage& __storage, __alloc& __mem_alloc, size_type __desired_count,
		     const __base_value_type& __initial_value)
		{
			if (__desired_count == static_cast<size_type>(0))
				{
					return _S_init_empty_storage_into(__storage);
				}

			size_type __desired_storage_count = __bit_to_element_size<__base_value_type>(__desired_count);
			if (_S_is_sbo_size(__desired_count))
				{
					_S_switch_storage_to_sbo(__storage);
					__base_pointer __storage_pointer = _S_storage_pointer(__storage);
					_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
					     __desired_storage_count, &_S_construct_initial_value, __initial_value);
					_S_set_size_sbo(__storage, __desired_count);
					return true;
				}

			_S_switch_storage_to_heap(__storage);
			__base_pointer __storage_pointer = __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
			if (__storage_pointer == nullptr)
				{
					throw ::std::bad_alloc();
				}
			_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer, __desired_storage_count,
			     __desired_storage_count, &_S_construct_initial_value, __initial_value);
			__storage._M_first           = __storage_pointer;
			__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_count;
			__storage._M_ptr._M_bit_size = __desired_count;
			return false;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_storage_count_zero(__alloc& __mem_alloc, size_type __desired_count)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_count_value_into(
			     __storage_and_is_sbo.first, __mem_alloc, __desired_count, __base_value_type());
			return __storage_and_is_sbo;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_storage_count_zero_into(_EitherStorage& __storage, __alloc& __mem_alloc, size_type __desired_count)
		{
			return _S_init_storage_count_value_into(__storage, __mem_alloc, __desired_count, __base_value_type());
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_base_storage_count_zero(__alloc& __mem_alloc, size_type __desired_storage_count)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_count_value_into(__storage_and_is_sbo.first, __mem_alloc,
			     __element_to_bit_size<__base_value_type>(__desired_storage_count), __base_value_type());
			return __storage_and_is_sbo;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_base_storage_count_zero_into(
		     _EitherStorage& __storage, __alloc& __mem_alloc, size_type __desired_storage_count)
		{
			return _S_init_storage_count_value_into(__storage, __mem_alloc,
			     __element_to_bit_size<__base_value_type>(__desired_storage_count), __base_value_type());
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_base_storage_count_value(
		     __alloc& __mem_alloc, size_type __desired_storage_count, const __base_value_type& __initial_value)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_count_value_into(
			     __mem_alloc, __element_to_bit_size<__base_value_type>(__desired_storage_count), __initial_value);
			return __storage_and_is_sbo;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_base_storage_count_value_into(_EitherStorage& __storage, __alloc& __mem_alloc,
		     size_type __desired_storage_count, const __base_value_type& __initial_value)
		{
			return _S_init_storage_count_value_into(__storage, __mem_alloc,
			     __element_to_bit_size<__base_value_type>(__desired_storage_count), __initial_value);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_destroy(__alloc& __mem_alloc, __base_pointer __storage_pointer, size_type __desired_count)
		{
			for (; __desired_count-- > 0;)
				{
					__alloc_traits::destroy(__mem_alloc, (__storage_pointer + __desired_count));
				}
		}
	}; // namespace ITSY_BITSY_SOURCE_NAMESPACE

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator==(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		auto __left_size  = __left.size();
		auto __right_size = __right.size();
		if (__left_size != __right_size)
			{
				return false;
			}

		return ::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator!=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		auto __left_size  = __left.size();
		auto __right_size = __right.size();
		if (__left_size != __right_size)
			{
				return true;
			}
		return !::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator<(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		return ::std::lexicographical_compare(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator<=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		return !(__left > __right);
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator>(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		return ::std::lexicographical_compare(
		     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::greater<bool>());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator>=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		return !(__left < __right);
	}

	template<typename _Type,
	     ::std::size_t _InlineWords = __default_small_buffer_size_v<_Type, ::std::allocator<_Type>>,
	     typename _Allocator        = ::std::allocator<_Type>>
	class __small_bit_vector : public __packed_small_bit_vector<_Type, _InlineWords, _Allocator, false>
	{
	private:
		template<typename, ::std::size_t, typename, bool>
		friend class __packed_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class __small_bit_vector;

		using __base_t = __packed_small_bit_vector<_Type, _InlineWords, _Allocator, false>;

	public:

		using __base_t::__base_t;
		__small_bit_vector(const __small_bit_vector&) = default;
		__small_bit_vector(__small_bit_vector&&) = default;

		__small_bit_vector& operator=(const __small_bit_vector&) = default;
		__small_bit_vector& operator=(__small_bit_vector&&) = default;
	};
} // namespace ITSY_BITSY_SOURCE_NAMESPACE

#undef ITSY_BITSY_ALLOCATOR_CONSTEXPR

#endif // ITSY_BITSY_DETAIL_SMALL_BIT_VECTOR_HPP
