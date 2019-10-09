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

#if (defined(_MSC_VER)) || (defined(__cplusplus) && __cplusplus >= 201703L)

#include <itsy/detail/bit_iterator.hpp>
#include <itsy/detail/ebco.hpp>
#include <itsy/detail/algorithm.hpp>

#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <climits>
#include <cassert>

#include <itsy/detail/namespace_default_begin.hpp>

#ifdef ITSY_BITSY_DETAIL_SBO_CONSTEXPR_CAPABLE
#define ITSY_BITSY_ALLOCATOR_CONSTEXPR constexpr
#else
#define ITSY_BITSY_ALLOCATOR_CONSTEXPR
#endif

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	template<typename _Word, typename _Allocator = ::std::allocator<_Word>>
	inline constexpr ::std::size_t
	     __default_small_buffer_size_v = (sizeof(_Word*) + sizeof(_Word*)) / sizeof(_Word);

	template<typename _Word,
	     ::std::size_t _InlineWords =
	          __default_small_buffer_size_v<_Word, ::std::allocator<_Word>>,
	     typename _Allocator = ::std::allocator<_Word>>
	class __small_bit_vector : private __ebco<_Allocator, 0>
	{
	private:
		template<typename, ::std::size_t, typename>
		friend class __small_bit_vector;

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc>
		friend constexpr bool
		operator==(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
		     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc>
		friend constexpr bool
		operator!=(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
		     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc>
		friend constexpr bool
		operator<(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
		     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc>
		friend constexpr bool
		operator<=(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
		     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc>
		friend constexpr bool
		operator>(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
		     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc>
		friend constexpr bool
		operator>=(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
		     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right);

		using __alloc_base          = __ebco<_Allocator, 0>;
		using __underlying          = __any_to_underlying_t<_Word>;
		using __unsigned_underlying = ::std::make_unsigned_t<__underlying>;
		using __alloc = ::std::remove_cv_t<::std::remove_reference_t<__unwrap_t<_Allocator>>>;
		using __alloc_traits         = ::std::allocator_traits<__alloc>;
		using __size_type            = typename __alloc_traits::size_type;
		using __base_value_type      = typename __alloc_traits::value_type;
		using __base_pointer         = typename __alloc_traits::pointer;
		using __base_const_pointer   = typename __alloc_traits::const_pointer;
		using __base_reference       = decltype(*::std::declval<__base_pointer>());
		using __base_const_reference = decltype(*::std::declval<__base_const_pointer>());
		using __difference_type      = typename __alloc_traits::difference_type;

	public:
		// member types
		using allocator       = _Allocator;
		using value_type      = __bit_value;
		using reference       = __bit_reference<__base_reference>;
		using const_reference = __bit_reference<__base_const_reference>;
		using pointer         = __bit_pointer<__base_pointer>;
		using const_pointer   = __bit_pointer<__base_const_pointer>;
		using iterator        = __bit_iterator<__base_pointer>;
		using const_iterator  = __bit_iterator<__base_const_pointer>;
		using size_type       = __size_type;
		using difference_type = __difference_type;

		// constructors
		// constructors: default
		__small_bit_vector() noexcept(noexcept(allocator()))
		: __alloc_base(), _M_buf_or_ptr(_S_init_empty_storage())
		{
		}

		// constructors: copy
		__small_bit_vector(const __small_bit_vector& __right)
		: __alloc_base(
		       __alloc_traits::select_on_container_copy_construction(__right.get_allocator()))
		, _M_buf_or_ptr(_S_init_base_storage(
		       __right._M_storage_pointer(), __right._M_storage_pointer_end()))
		{
		}

		__small_bit_vector(const __small_bit_vector& __right, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(_S_init_base_storage(
		       __right._M_storage_pointer(), __right._M_storage_pointer_end()))
		{
		}

		// constructors: move
		__small_bit_vector(__small_bit_vector&& __right)
		: __alloc_base(::std::move(__right.get_allocator()))
		, _M_buf_or_ptr(_S_steal<true>(this->get_allocator(), ::std::move(__right._M_buf_or_ptr),
		       ::std::move(__right.get_allocator())))
		{
		}

		__small_bit_vector(__small_bit_vector&& __right, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(_S_steal(this->get_allocator(), ::std::move(__right._M_buf_or_ptr),
		       ::std::move(__right.get_allocator())))
		{
		}

		// constructors: allocator
		explicit __small_bit_vector(const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc), _M_buf_or_ptr(_S_init_empty_storage())
		{
		}

		// constructors: rangeable
		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> &&
		                        !::std::is_same_v<_It, std::in_place_t> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list> &&
		                        !__is_same_no_cvref_v<_It, __small_bit_vector>>* = nullptr>
		__small_bit_vector(_It __it, _Sen __sen)
		: __alloc_base()
		, _M_buf_or_ptr(
		       _S_init_storage(this->get_allocator(), ::std::move(__it), ::std::move(__sen)))
		{
		}

		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> &&
		                        !::std::is_same_v<_It, std::in_place_t> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list> &&
		                        !__is_same_no_cvref_v<_It, __small_bit_vector>>* = nullptr>
		__small_bit_vector(_It __it, _Sen __sen, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(
		       _S_init_storage(this->get_allocator(), ::std::move(__it), ::std::move(__sen)))
		{
		}

		// constructors: size, value
		__small_bit_vector(size_type __desired_count)
		: __alloc_base()
		, _M_buf_or_ptr(_S_init_storage_count_zero(this->get_allocator(), __desired_count))
		{
		}

		__small_bit_vector(size_type __desired_count, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(_S_init_storage_count_zero(this->get_allocator(), __desired_count))
		{
		}

		__small_bit_vector(size_type __desired_count, const value_type& __initial_value)
		: __alloc_base()
		, _M_buf_or_ptr(_S_init_storage_count_value(this->get_allocator(), __desired_count,
		       __initial_value ? static_cast<__base_value_type>(
		                              ::std::numeric_limits<__unsigned_underlying>::max())
		                       : __base_value_type()))
		{
		}

		__small_bit_vector(size_type __desired_count, const value_type& __initial_value,
		     const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(_S_init_storage_count_value(this->get_allocator(), __desired_count,
		       __initial_value ? static_cast<__base_value_type>(
		                              ::std::numeric_limits<__unsigned_underlying>::max())
		                       : __base_value_type()))
		{
		}

		// constructors: initializer_list
		__small_bit_vector(::std::initializer_list<value_type> __il)
		: __small_bit_vector(__il.begin(), __il.end())
		{
		}

		__small_bit_vector(::std::initializer_list<value_type> __il, const allocator& __mem_alloc)
		: __small_bit_vector(__il.begin(), __il.end(), __mem_alloc)
		{
		}

		// constructors: in_place
		// constructors: (in_place) rangeable
		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list>>* =
		          nullptr>
		__small_bit_vector(std::in_place_t, _It __it, _Sen __sen)
		: __alloc_base()
		, _M_buf_or_ptr(
		       _S_init_base_storage(this->get_allocator(), ::std::move(__it), ::std::move(__sen)))
		{
		}

		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list>>* =
		          nullptr>
		__small_bit_vector(::std::in_place_t, _It __it, _Sen __sen, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(
		       _S_init_base_storage(this->get_allocator(), ::std::move(__it), ::std::move(__sen)))
		{
		}

		// constructors: (in_place) size, value
		__small_bit_vector(::std::in_place_t, size_type __desired_count)
		: __alloc_base()
		, _M_buf_or_ptr(_S_init_base_storage_count_zero(this->get_allocator(), __desired_count))
		{
		}

		__small_bit_vector(
		     ::std::in_place_t, size_type __desired_count, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(_S_init_base_storage_count_zero(this->get_allocator(), __desired_count))
		{
		}

		__small_bit_vector(::std::in_place_t, size_type __desired_count,
		     const __base_value_type& __initial_value)
		: __alloc_base()
		, _M_buf_or_ptr(_S_init_base_storage_count_value(
		       this->get_allocator(), __desired_count, __initial_value))
		{
		}

		__small_bit_vector(::std::in_place_t, size_type __desired_count,
		     const __base_value_type& __initial_value, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(_S_init_base_storage_count_value(
		       this->get_allocator(), __desired_count, __initial_value))
		{
		}

		// constructors: (in_place) initializer_list
		__small_bit_vector(::std::in_place_t, ::std::initializer_list<__base_value_type> __il)
		: __small_bit_vector(std::in_place, __il.begin(), __il.end())
		{
		}

		__small_bit_vector(::std::in_place_t, ::std::initializer_list<__base_value_type> __il,
		     const allocator& __mem_alloc)
		: __small_bit_vector(std::in_place, __il.begin(), __il.end(), __mem_alloc)
		{
		}

		// destructor
		~__small_bit_vector() noexcept
		{
			this->_M_destroy();
		}

		// assignment
		__small_bit_vector&
		operator=(__small_bit_vector&& __right) noexcept
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
									this->_M_base_assign(
									     ::std::make_move_iterator(
									          __right._M_storage_pointer()),
									     ::std::make_move_iterator(
									          __right._M_storage_pointer_end()));
								}
						}
				}
			return *this;
		}

		__small_bit_vector&
		operator=(const __small_bit_vector& __right)
		{
			// do we have to take the allocator from the right?
			if constexpr (__alloc_traits::propagate_on_container_move_assignment::value)
				{
					// are they not always equal...?
					if constexpr (!__alloc_traits::is_always_equal::value)
						{
							// ... are they actually not equal... ?!
							if (this->get_allocator() != __right.get_allocator())
								{
									// fek. Clear everything first because
									// we will be trucking over our allocator
									this->clear();
								}
						}
					// propagate the right allocator...
					this->__alloc_base::_M_get_value() = __right.get_allocator();
				}
			// alright, now vomit out all the elements
			this->_M_base_assign(__right._M_storage_pointer(), __right._M_storage_pointer_end());
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
			size_type __size = this->_M_is_sbo() ? this->_M_buf_or_ptr._M_buf._M_size()
			                                     : this->_M_buf_or_ptr._M_ptr._M_size();
			return __size;
		}

		constexpr size_type
		capacity() const
		{
			size_type __capacity = this->_M_is_sbo() ? this->_M_buf_or_ptr._M_buf._M_capacity()
			                                         : this->_M_buf_or_ptr._M_ptr._M_capacity();
			return __capacity;
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
			return iterator(
			     this->_M_buf_or_ptr._M_storage_pointer(), this->_M_first_bit_index());
		}

		iterator
		end()
		{
			size_type __last_bit_it_index = this->_M_last_bit_index();
			__base_pointer __storage_last = this->_M_buf_or_ptr._M_storage_pointer_end();
			if (__last_bit_it_index != 0)
				{
					--__storage_last;
				}
			return iterator(__storage_last, __last_bit_it_index);
		}

		const_iterator
		begin() const
		{
			return this->cbegin();
		}

		const_iterator
		end() const
		{
			return this->cend();
		}

		const_iterator
		cbegin() const
		{
			return const_iterator(
			     this->_M_buf_or_ptr._M_storage_pointer(), this->_M_first_bit_index());
		}

		const_iterator
		cend() const
		{
			size_type __last_bit_it_index       = this->_M_last_bit_index();
			__base_const_pointer __storage_last = this->_M_buf_or_ptr._M_storage_pointer_end();
			if (__last_bit_it_index != 0)
				{
					--__storage_last;
				}
			return const_iterator(__storage_last, __last_bit_it_index);
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
					for (size_type __boundary =
					          __len - (__len % (__binary_digits_v<__base_value_type>));
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
			size_type __starting_size = this->_M_buf_or_ptr._M_size();
			if (__starting_size == 0)
				{
					return this->_M_emplace_back_unchecked_0(::std::forward<_Args>(__args)...);
				}

			size_type __starting_capacity = this->_M_buf_or_ptr._M_capacity();
			if (this->_M_buf_or_ptr._M_size() == __starting_capacity)
				{
					// make room first
					_S_grow_storage_of_size_with_strategy(
					     this->get_allocator(), this->_M_buf_or_ptr, __starting_size);
				}

			size_type __desired_size = __starting_size + 1;
			__base_pointer __storage_last =
			     this->_M_storage_pointer(__desired_size) +
			     __bit_to_element_size<__base_value_type>(__desired_size);
			__base_pointer __storage_it = __storage_last - 1;
			size_type __last_bit        = _S_last_bit_index(__starting_size);
			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_reference __storage_ref = *__storage_it;
			reference __ref(__storage_ref, __last_bit);
			if constexpr (noexcept(::std::declval<reference&>().set(
			                   ::std::forward<_Args>(__args)...)))
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
			this->_M_buf_or_ptr._M_set_size(__desired_size);
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
			size_type __starting_size = this->_M_buf_or_ptr._M_size();
			if (__starting_size == 0)
				{
					return this->_M_emplace_back_unchecked_0(::std::forward<_Args>(__args)...);
				}

			size_type __starting_capacity  = this->_M_buf_or_ptr._M_capacity();
			__base_pointer __storage_first = this->_M_storage_pointer();
			if (__starting_size == __starting_capacity)
				{
					// make room first
					__storage_first =
					     _S_grow_storage(this->get_allocator(), this->_M_buf_or_ptr);
				}

			size_type __desired_size = __starting_size + 1;
			__base_pointer __storage_last =
			     __storage_first + __bit_to_element_size<__base_value_type>(__desired_size);
			size_type __last_bit = _S_last_bit_index(__starting_size);
			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_pointer __storage_it = __storage_first;
			value_type __saved =
			     reference(*__storage_it, __max_binary_index_v<__base_value_type>);
			{
				__base_reference __storage_ref = *__storage_it;
				__storage_ref <<= 1;
				reference __ref(__storage_ref, 0);
				if constexpr (noexcept(::std::declval<reference&>().set(
				                   ::std::forward<_Args>(__args)...)))
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
										_S_destroy(
										     this->get_allocator(), __storage_last - 1);
									}
								__storage_ref >>= 1;
								reference(__storage_ref,
								     __max_binary_index_v<__base_value_type>) = __saved;
								// rethrow, and drown myself in tears
								throw;
							}
					}
				++__storage_it;
			}
			for (; __storage_it != __storage_last; ++__storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					value_type __before_shift =
					     reference(__storage_ref, __max_binary_index_v<__base_value_type>);
					__storage_ref <<= 1;
					reference __ref(__storage_ref, 0);
					__ref.set(__saved);
					__saved = __before_shift;
				}
			this->_M_buf_or_ptr._M_set_size(__desired_size);
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
					reference __bit_ref =
					     this->emplace_front(::std::forward<_Args>(__args)...);
					return iterator(__bit_ref.address(), __bit_ref.position());
				}

			size_type __starting_size = this->_M_buf_or_ptr._M_size();
			size_type __starting_storage_size =
			     __bit_to_element_size<__base_value_type>(__starting_size);
			size_type __last_bit          = _S_last_bit_index(__starting_size);
			__base_pointer __storage_last = __storage_first + __starting_storage_size;
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
			size_type __starting_capacity = this->_M_buf_or_ptr._M_capacity();
			__storage_last =
			     __storage_first + __bit_to_element_size<__base_value_type>(__desired_size);
			__base_pointer __storage_it = const_cast<__base_pointer>(__where.base());
			if (__starting_size == __starting_capacity)
				{
					// make room first
					difference_type __preserved_distance = __storage_it - __storage_first;
					__storage_first = _S_grow_storage_of_size_with_strategy(
					     this->get_allocator(), this->_M_buf_or_ptr, __starting_size);
					__storage_it   = __storage_first + __preserved_distance;
					__storage_last = __storage_first +
					                 __bit_to_element_size<__base_value_type>(__desired_size);
				}

			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_pointer __storage_where       = __storage_it;
			__base_reference __first_storage_ref = *__storage_it;
			value_type __saved =
			     reference(__first_storage_ref, __max_binary_index_v<__base_value_type>);
			if (__where_pos == 0)
				{
					__first_storage_ref <<= 1;
				}
			else
				{
					__shift_left_preserve_right<__base_value_type>(
					     __first_storage_ref, __where_pos, 1);
				}
			reference __first_bit_ref(__first_storage_ref, __where_pos);
			__first_bit_ref.set(::std::forward<_Args>(__args)...);
			++__storage_it;

			for (; __storage_it != __storage_last; ++__storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					reference __before_shift_ref(
					     __storage_ref, __max_binary_index_v<__base_value_type>);
					value_type __before_shift = __before_shift_ref;
					__storage_ref <<= 1;
					reference __ref(__storage_ref, 0);
					__ref.set(__saved);
					__saved = __before_shift;
				}

			this->_M_buf_or_ptr._M_set_size(__desired_size);
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
					return iterator(const_cast<__base_pointer>(::std::move(__where).base()),
					     __where.position());
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

		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It>>* = nullptr>
		iterator
		insert(const_iterator __where, _It __first, _Sen __last)
		{
			using _SenCategory = typename ::std::iterator_traits<_Sen>::iterator_category;
			if (__first == __last)
				{
					return iterator(const_cast<__base_pointer>(::std::move(__where).base()),
					     __where.position());
				}

			// FIXME: a better implementation, please
			if constexpr (__is_iterator_category_or_better_v<::std::bidirectional_iterator_tag,
			                   _SenCategory>)
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
					reference __old_bit(
					     *__old_storage_it, __max_binary_index_v<__base_value_type>);
					__old_bit = __saved;
				}

			this->_M_shrink_at_edge_1(__starting_size);
			this->_M_buf_or_ptr._M_set_size(__starting_size - 1);
		}

		void
		pop_back() noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return;
				}
			this->_M_shrink_at_edge_1(__starting_size);
			this->_M_buf_or_ptr._M_set_size(__starting_size - 1);
		}

		iterator
		erase(const_iterator __where) noexcept(
		     ::std::is_nothrow_move_constructible_v<__base_value_type>)
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
					__shift_right_preserve_right<__base_value_type>(
					     __first_storage_ref, __where_pos - 1, 1);
				}
			__base_pointer __old_storage_it = __storage_it;
			++__storage_it;
			for (; __storage_it != __storage_last; ++__storage_it, (void)++__old_storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					value_type __preserved         = reference(__storage_ref, 0);
					reference __old_bit(
					     *__old_storage_it, __max_binary_index_v<__base_value_type>);
					__old_bit = __preserved;
					__storage_ref >>= 1;
				}

			this->_M_shrink_at_edge_1(__starting_size);
			this->_M_buf_or_ptr._M_set_size(__starting_size - 1);
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
					return iterator(
					     const_cast<__base_pointer>(__first.base()), __first.position());
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

		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It>>* = nullptr>
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

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag,
			                   _ItCategory>)
				{
					size_type __desired_count = static_cast<size_type>(__last - __first);
					__base_pointer __storage_pointer = this->_M_storage_pointer();
					if (__desired_count > this->capacity())
						{
							__storage_pointer = _S_grow_storage_to(
							     __mem_alloc, this->_M_buf_or_ptr, __desired_count);
						}
					size_type __storage_size = this->_M_storage_size();
					size_type __desired_storage_count =
					     __bit_to_element_size<__base_value_type>(__desired_count);
					if (__storage_size < __desired_storage_count)
						{
							_S_trampoline_construct_n_using(__mem_alloc,
							     __storage_pointer + __storage_size,
							     __desired_storage_count - __storage_size,
							     &_S_construct_default);
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
					_S_grow_storage_to(
					     this->get_allocator(), this->_M_buf_or_ptr, __desired_count);
				}
		}

		void
		clear()
		{
			this->_M_destroy();
			this->_M_buf_or_ptr._M_set_size(0);
		}

	private:
		struct _Storage
		{
			size_type _M_bit_size;
			__base_value_type* _M_first;
			__base_value_type* _M_last;

			constexpr __base_pointer
			_M_storage_pointer() noexcept
			{
				return this->_M_first;
			}

			constexpr __base_const_pointer
			_M_storage_pointer() const noexcept
			{
				return this->_M_first;
			}

			constexpr __base_pointer
			_M_storage_pointer_end() noexcept
			{
				return this->_M_first + this->_M_storage_size();
			}

			constexpr __base_const_pointer
			_M_storage_pointer_end() const noexcept
			{
				return this->_M_first + this->_M_storage_size();
			}

			constexpr size_type
			_M_size() const noexcept
			{
				return this->_M_bit_size;
			}

			constexpr void
			_M_set_size(size_type __value) noexcept
			{
				this->_M_bit_size = __value;
			}

			constexpr size_type
			_M_storage_size() const noexcept
			{
				return __bit_to_element_size<__base_value_type>(this->_M_size());
			}

			constexpr size_type
			_M_capacity() const noexcept
			{
				return this->_M_storage_capacity() * __binary_digits_v<__base_value_type>;
			}

			constexpr size_type
			_M_storage_capacity() const noexcept
			{
				return this->_M_last - this->_M_first;
			}
		};

		struct _SboStorage
		{
			size_type _M_bit_size;
			__uninit<__base_value_type> _M_buf[_InlineWords == 0 ? 1 : _InlineWords];

			constexpr __base_pointer
			_M_storage_pointer() noexcept
			{
				difference_type __index = static_cast<difference_type>(0) -
				                          static_cast<difference_type>(_S_is_hyper_sbo_able);
				__uninit<__base_value_type>& __ref = this->_M_buf[__index];
				return ::std::addressof(__ref._M_value);
			}

			constexpr __base_const_pointer
			_M_storage_pointer() const noexcept
			{
				difference_type __index = static_cast<difference_type>(0) -
				                          static_cast<difference_type>(_S_is_hyper_sbo_able);
				const __uninit<__base_value_type>& __ref = this->_M_buf[__index];
				return ::std::addressof(__ref._M_value);
			}

			constexpr __base_pointer
			_M_storage_pointer_end() noexcept
			{
				__uninit<__base_value_type>& __ref = this->_M_buf[0];
				return ::std::addressof(__ref._M_value) + this->_M_storage_size();
			}

			constexpr __base_const_pointer
			_M_storage_pointer_end() const noexcept
			{
				const __uninit<__base_value_type>& __ref = this->_M_buf[0];
				return ::std::addressof(__ref._M_value) + this->_M_storage_size();
			}

			constexpr __base_value_type
			_M_sbo_bits() const noexcept
			{
				static constexpr size_type __sbo_mask = ~(_S_inline_bits_for_size - 1);
				return (this->_M_bit_size & __sbo_mask) >> _S_inline_first_bit_index;
			}

			static constexpr size_type
			_S_first_bit_index() noexcept
			{
				return _S_is_hyper_sbo_able ? _S_inline_first_bit_index : 0;
			}

			static constexpr size_type
			_M_storage_capacity() noexcept
			{
				return _InlineWords + static_cast<size_type>(_S_is_hyper_sbo_able);
			}

			constexpr size_type
			_M_capacity() const noexcept
			{
				return _S_inline_max_bit_count;
			}

			constexpr size_type
			_M_size() const noexcept
			{
				if constexpr (_S_is_hyper_sbo_able)
					{
						static constexpr size_type __size_mask =
						     (_S_inline_bits_for_size - 1);
						return this->_M_bit_size & __size_mask;
					}
				else
					{
						return this->_M_bit_size;
					}
			}

			constexpr void
			_M_set_size(size_type __value) noexcept
			{
				if constexpr (_S_is_hyper_sbo_able)
					{
						static constexpr size_type __size_mask =
						     (_S_inline_bits_for_size - 1);
						this->_M_bit_size =
						     (this->_M_bit_size & ~__size_mask) | (__value & __size_mask);
					}
				else
					{
						this->_M_bit_size = __value;
					}
			}

			constexpr size_type
			_M_storage_size() const noexcept
			{
				return __bit_to_element_size<__base_value_type>(this->_M_size());
			}
		};

		union _EitherStorage
		{
			size_type _M_either_bit_size;
			_SboStorage _M_buf;
			_Storage _M_ptr;

			constexpr _EitherStorage() : _M_buf()
			{
			}

			constexpr _EitherStorage(::std::in_place_t) : _M_ptr()
			{
			}

			constexpr __base_pointer
			_M_storage_pointer() noexcept
			{
				if (_S_is_sbo(*this))
					{
						return this->_M_buf._M_storage_pointer();
					}
				else
					{
						return this->_M_ptr._M_storage_pointer();
					}
			}

			constexpr __base_const_pointer
			_M_storage_pointer() const noexcept
			{
				if (_S_is_sbo(*this))
					{
						return this->_M_buf._M_storage_pointer();
					}
				else
					{
						return this->_M_ptr._M_storage_pointer();
					}
			}

			constexpr __base_pointer
			_M_storage_pointer_end() noexcept
			{
				if (_S_is_sbo(*this))
					{
						return this->_M_buf._M_storage_pointer_end();
					}
				else
					{
						return this->_M_ptr._M_storage_pointer_end();
					}
			}

			constexpr __base_const_pointer
			_M_storage_pointer_end() const noexcept
			{
				if (_S_is_sbo(*this))
					{
						return this->_M_buf._M_storage_pointer_end();
					}
				else
					{
						return this->_M_ptr._M_storage_pointer_end();
					}
			}

			constexpr size_type
			_M_first_bit_index() const noexcept
			{
				if constexpr (_S_is_hyper_sbo_able)
					{
						return _S_is_sbo(*this) ? _S_inline_first_bit_index : 0;
					}
				else
					{
						return 0;
					}
			}

			constexpr size_type
			_M_storage_capacity() const noexcept
			{
				return _S_is_sbo(*this) ? this->_M_buf._M_storage_capacity()
				                        : this->_M_ptr._M_storage_capacity();
			}

			constexpr size_type
			_M_capacity() const noexcept
			{
				return this->_M_storage_capacity() * __binary_digits_v<__base_value_type>;
			}

			constexpr size_type
			_M_size() const noexcept
			{
				if constexpr (_S_is_hyper_sbo_able)
					{
						return _S_is_sbo(*this) ? this->_M_buf._M_size()
						                        : this->_M_ptr._M_size();
					}
				else
					{
						return this->_M_either_bit_size;
					}
			}

			constexpr void
			_M_set_size(size_type __value) noexcept
			{
				if constexpr (_S_is_hyper_sbo_able)
					{
						static constexpr size_type __size_mask =
						     (_S_inline_bits_for_size - 1);
						this->_M_bit_size =
						     (this->_M_bit_size & ~__size_mask) | (__value & __size_mask);
					}
				else
					{
						this->_M_either_bit_size = __value;
					}
			}

			constexpr size_type
			_M_storage_size() const noexcept
			{
				return __bit_to_element_size<__base_value_type>(this->_M_size());
			}
		} _M_buf_or_ptr;

		// this cuts of too many optimizations
		// and is too difficult to do properly:
		// keep off permanently for now...
		inline static constexpr bool _S_is_hyper_sbo_able =
		     false && ::std::is_same_v<size_type, __base_value_type> &&
		     (sizeof(_SboStorage) == sizeof(__base_value_type[_InlineWords + 1]));
		inline static constexpr size_type _S_inline_innate_max_bit_count =
		     _InlineWords * __binary_digits_v<__base_value_type>;
		inline static constexpr size_type _S_inline_bits_for_size =
		     __binary_digits_v<size_type> - __bit_firstl_one(_S_inline_innate_max_bit_count);
		inline static constexpr size_type _S_inline_first_bit_index = _S_inline_bits_for_size;
		inline static constexpr size_type _S_inline_max_bit_count =
		     _S_inline_innate_max_bit_count +
		     (_S_is_hyper_sbo_able ? __binary_digits_v<size_type> - _S_inline_first_bit_index
		                           : 0);

		constexpr bool
		_M_is_sbo() const noexcept
		{
			return _S_is_sbo(this->_M_buf_or_ptr);
		}

		constexpr size_type
		_M_storage_capacity() const noexcept
		{
			size_type __size = this->_M_is_sbo()
			                        ? this->_M_buf_or_ptr._M_buf._M_storage_capacity()
			                        : this->_M_buf_or_ptr._M_ptr._M_storage_capacity();
			return __size;
		}

		constexpr size_type
		_M_storage_capacity(size_type __at) const noexcept
		{
			size_type __size = _S_is_sbo_size(__at)
			                        ? this->_M_buf_or_ptr._M_buf._M_storage_capacity()
			                        : this->_M_buf_or_ptr._M_ptr._M_storage_capacity();
			return __size;
		}

		constexpr size_type
		_M_storage_size() const noexcept
		{
			size_type __size = this->_M_is_sbo() ? this->_M_buf_or_ptr._M_buf._M_storage_size()
			                                     : this->_M_buf_or_ptr._M_ptr._M_storage_size();
			return __size;
		}

		constexpr __base_const_pointer
		_M_storage_pointer() const noexcept
		{
			return this->_M_is_sbo() ? this->_M_buf_or_ptr._M_buf._M_storage_pointer()
			                         : this->_M_buf_or_ptr._M_ptr._M_storage_pointer();
		}

		constexpr __base_pointer
		_M_storage_pointer() noexcept
		{
			return this->_M_is_sbo() ? this->_M_buf_or_ptr._M_buf._M_storage_pointer()
			                         : this->_M_buf_or_ptr._M_ptr._M_storage_pointer();
		}

		constexpr __base_pointer
		_M_storage_pointer_end() noexcept
		{
			return this->_M_storage_pointer() + this->_M_storage_size();
		}

		constexpr __base_const_pointer
		_M_storage_pointer_end() const noexcept
		{
			return this->_M_storage_pointer() + this->_M_storage_size();
		}

		constexpr __base_const_pointer
		_M_storage_pointer(size_type __at) const noexcept
		{
			return _S_is_sbo_size(__at) ? this->_M_buf_or_ptr._M_buf._M_storage_pointer()
			                            : this->_M_buf_or_ptr._M_ptr._M_storage_pointer();
		}

		constexpr __base_pointer
		_M_storage_pointer(size_type __at) noexcept
		{
			return _S_is_sbo_size(__at) ? this->_M_buf_or_ptr._M_buf._M_storage_pointer()
			                            : this->_M_buf_or_ptr._M_ptr._M_storage_pointer();
		}

		constexpr __base_pointer
		_M_storage_pointer_end(size_type __at) noexcept
		{
			return this->_M_storage_pointer(__at) +
			       __bit_to_element_size<__base_value_type>(__at);
		}

		constexpr __base_const_pointer
		_M_storage_pointer_end(size_type __at) const noexcept
		{
			return this->_M_storage_pointer(__at) +
			       __bit_to_element_size<__base_value_type>(__at);
		}

		constexpr size_type
		_M_first_bit_index() const noexcept
		{
			return this->_M_buf_or_ptr._M_first_bit_index();
		}

		constexpr size_type
		_M_last_bit_index() const noexcept
		{
			return _S_last_bit_index(this->size());
		}

		void
		_M_shrink_at_edge_1(size_type __starting_size, size_type __last_bit)
		{
			if (__last_bit == 0)
				{
					__alloc& __mem_alloc = this->get_allocator();
					_S_destroy(__mem_alloc, this->_M_storage_pointer_end() - 1, 1);
					if (!_S_is_sbo_size(__starting_size) &&
					     _S_is_sbo_size(__starting_size - 1))
						{
							_S_shrink_storage(
							     __mem_alloc, this->_M_buf_or_ptr, __starting_size - 1);
						}
				}
		}

		void
		_M_shrink_at_edge_1(size_type __starting_size)
		{
			size_type __last_bit = _S_last_bit_index(__starting_size - 1);
			this->_M_shrink_at_edge_1(__starting_size, __last_bit);
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
			this->_M_buf_or_ptr._M_set_size(1);
			return __ref;
		}

		template<typename _It, typename _Sen>
		void
		_M_base_assign(_It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;

			if (__first == __last)
				{
					this->clear();
					return;
				}

			__alloc& __mem_alloc = this->get_allocator();

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag,
			                   _ItCategory>)
				{
					size_type __desired_storage_count =
					     static_cast<size_type>(__last - __first);
					size_type __desired_count =
					     __element_to_bit_size<__base_value_type>(__desired_storage_count);
					size_type __storage_capacity     = this->_M_storage_capacity();
					__base_pointer __storage_pointer = this->_M_storage_pointer();
					bool __orphans_in_the_allocators_wake =
					     __desired_storage_count > __storage_capacity;
					if (__orphans_in_the_allocators_wake)
						{
							__storage_pointer = _S_grow_storage_to<true>(
							     __mem_alloc, this->_M_buf_or_ptr, __desired_count);
						}
					size_type __storage_size = this->_M_storage_size();
					if (__orphans_in_the_allocators_wake)
						{
							_S_trampoline_construct_n_using<false>(__mem_alloc,
							     __storage_pointer, __desired_storage_count, 0,
							     &_S_construct_iterator<_It>, __first);
							this->_M_buf_or_ptr._M_set_size(__desired_count);
						}
					else
						{
							for (size_type __index = 0;
							     __index < __storage_size && __first != __last;
							     (void)++__index, (void)++__first)
								{
									*(__storage_pointer + __index) = *__first;
								}
							_S_trampoline_construct_using<false>(__mem_alloc,
							     __storage_pointer + __storage_size, __storage_capacity,
							     __first, __last, &_S_construct_iterator<_It>);
							this->_M_buf_or_ptr._M_set_size(__desired_count);
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
									__first_it = _S_grow_storage_of_size_with_strategy(
									     __mem_alloc, this->_M_buf_or_ptr,
									     __element_to_bit_size<__base_value_type>(
									          __old_storage_size));
									__first_it += __old_storage_size;
									__last_it =
									     this->_M_buf_or_ptr._M_storage_pointer_end();
								}
							_S_construct_iterator<_It>(__mem_alloc, __first_it, __first);
							++__first_it;
							++__first;
							++__current_storage_size;
						}
					this->_M_buf_or_ptr._M_set_size(
					     __element_to_bit_size<__base_value_type>(__current_storage_size));
				}
		}

		void
		_M_destroy()
		{
			const bool __using_sbo         = this->_M_is_sbo();
			const size_type __storage_size = __using_sbo
			                                      ? this->_M_buf_or_ptr._M_buf._M_storage_size()
			                                      : this->_M_buf_or_ptr._M_ptr._M_storage_size();
			__alloc& __mem_alloc = this->get_allocator();
			if (__using_sbo)
				{
					__base_pointer __storage_pointer =
					     this->_M_buf_or_ptr._M_buf._M_storage_pointer();
					_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
					return;
				}

			__base_pointer __storage_pointer = this->_M_buf_or_ptr._M_ptr._M_storage_pointer();
			size_type __storage_capacity     = this->_M_buf_or_ptr._M_ptr._M_storage_size();
			if (__storage_pointer == nullptr || __storage_capacity == 0)
				{
					return;
				}
			_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
			__alloc_traits::deallocate(__mem_alloc, __storage_pointer, __storage_capacity);
		}

		template<bool _Pocma>
		void
		_M_steal(__small_bit_vector&& __right)
		{
			this->clear();
			if constexpr (_Pocma)
				{
					// totes yoink
					this->__alloc_base::get_value() = ::std::move(__right.get_allocator());
				}
			_S_steal<_Pocma>(this->get_allocator(), ::std::move(__right._M_buf_or_ptr),
			     ::std::move(__right.get_allocator()));
		}

		template<bool _Pocma>
		static _EitherStorage
		_S_steal(allocator& __left_alloc, _EitherStorage&& __right, allocator&& __right_alloc)
		{
			const bool __right_using_sbo = _S_is_sbo(__right);
			if (__right_using_sbo)
				{
					__alloc& __pocma_alloc = _Pocma ? __left_alloc : __right_alloc;
					// gotta do the SBO shuffle...
					_EitherStorage __left            = _S_init_empty_storage();
					__base_pointer __storage_pointer = __left._M_buf._M_storage_pointer();
					__base_pointer __right_storage_pointer =
					     __right._M_buf_or_ptr._M_buf._M_storage_pointer();
					size_type __right_storage_size =
					     __right._M_buf_or_ptr._M_buf._M_storage_size();
					_S_construct_move_old_pointer<false>(
					     __left_alloc, __storage_pointer, __right_storage_size);
					// must destroy old SBO contents
					// since they can't actually be stolen!
					_S_destroy(__pocma_alloc, __right_storage_pointer, __right_storage_size);
					return __left;
				}
			else
				{
					// just steal guts
					_EitherStorage __left = ::std::move(__right._M_buf_or_ptr);
					__right._M_buf_or_ptr = __right._S_init_empty_heap_storage();
					return __left;
				}
		}

		static constexpr bool
		_S_is_sbo(const _EitherStorage& __storage) noexcept
		{
			return _S_is_sbo_size(__storage._M_either_bit_size);
		}

		static constexpr bool
		_S_is_sbo_size(size_type __bit_size) noexcept
		{
			return _S_inline_max_bit_count != 0 && __bit_size <= _S_inline_max_bit_count;
		}

		static constexpr size_type
		_S_last_bit_index(size_type __pos) noexcept
		{
			return __pos % __binary_digits_v<__base_value_type>;
		}

		template<bool _DeallocateOnFailure, typename _Fx, typename... _Args>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_trampoline_construct_n_using(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     size_type __alloc_capacity, size_type __desired_count, _Fx&& __fx,
		     _Args&&... __args) noexcept(::std::is_nothrow_invocable_v<_Fx, __alloc&,
		     __base_pointer, _Args...>)
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

		template<bool _DeallocateOnFailure, typename _It, typename _Sen, typename _Fx,
		     typename... _Args>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_trampoline_construct_using(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     size_type __alloc_capacity, _It __first, _Sen __last, _Fx&& __fx,
		     _Args&&... __args) noexcept(::std::is_nothrow_invocable_v<_Fx, __alloc&,
		     __base_pointer, _It&, _Args...>)
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
									__fx(__mem_alloc, __storage_pointer + __lifetime_count,
									     __first, ::std::forward<_Args>(__args)...);
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
		_S_construct_sized_with(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     size_type __desired_count, const __base_value_type& __initial_value)
		{
			_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
			     __desired_count, &_S_construct_initial_value, __initial_value);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_sized(
		     __alloc& __mem_alloc, __base_pointer __storage_pointer, size_type __desired_count)
		{
			_S_trampoline_construct_n_using<false>(
			     __mem_alloc, __storage_pointer, 0, __desired_count, &_S_construct_zero);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_default(__alloc& __mem_alloc, __base_pointer __storage_pointer) noexcept(
		     ::std::is_nothrow_default_constructible_v<__base_value_type>)
		{
			__alloc_traits::construct(__mem_alloc, __storage_pointer);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_zero(__alloc& __mem_alloc, __base_pointer __storage_pointer) noexcept(
		     noexcept(
		          __alloc_traits::construct(__mem_alloc, __storage_pointer, __base_value_type())))
		{
			__alloc_traits::construct(__mem_alloc, __storage_pointer, __base_value_type());
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_initial_value(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     const __base_value_type&
		          __initial_value) noexcept(noexcept(__alloc_traits::construct(__mem_alloc,
		     __storage_pointer, __initial_value)))
		{
			__alloc_traits::construct(__mem_alloc, __storage_pointer, __initial_value);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_move_old_pointer(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     __base_pointer& __old_pointer) noexcept(::std::
		          is_nothrow_move_constructible_v<__base_value_type>)
		{
			if (::std::is_nothrow_move_constructible_v<__base_value_type>)
				{
					__alloc_traits::construct(
					     __mem_alloc, __storage_pointer, ::std::move(*__old_pointer));
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
		_S_construct_iterator(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     _It& __it) noexcept(::std::is_nothrow_constructible_v<__base_value_type,
		     decltype(*__it)>)
		{
			__alloc_traits::construct(__mem_alloc, __storage_pointer, *__it);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage(__alloc& __mem_alloc, _EitherStorage& __storage)
		{
			return _S_grow_storage_of_size_with_strategy(
			     __mem_alloc, __storage, __storage._M_size());
		}

		template<bool _OrphanObjects = false>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_to(
		     __alloc& __mem_alloc, _EitherStorage& __storage, size_type __desired_capacity)
		{
			return _S_grow_storage_of_size_to<_OrphanObjects>(
			     __mem_alloc, __storage, __storage._M_size(), __desired_capacity);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_of_size_with_strategy(
		     __alloc& __mem_alloc, _EitherStorage& __storage, size_type __old_size)
		{
			return _S_grow_storage_of_size_to(__mem_alloc, __storage, __old_size,
			     __old_size < 1
			          ? (_S_inline_max_bit_count < 1 ? __binary_digits_v<__base_value_type> * 4
			                                         : _S_inline_max_bit_count)
			          : __old_size * 2);
		}

		template<bool _OrphanObjects = false>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_of_size_to(__alloc& __mem_alloc, _EitherStorage& __storage,
		     size_type __old_size, size_type __desired_capacity)
		{
			bool __using_sbo = _S_is_sbo(__storage);
			if (__using_sbo)
				{
					if (_S_is_sbo_size(__desired_capacity))
						{
							// we are already in SBO, the capacity is already fine
							return __storage._M_buf._M_storage_pointer();
						}
					// transfer to non-SBO storage and grow
					return _S_transfer_inline_to_normal(
					     __mem_alloc, __storage, __desired_capacity);
				}
			else
				{
					size_type __desired_storage_capacity =
					     __bit_to_element_size<__base_value_type>(__desired_capacity);
					size_type __old_storage_capacity = __storage._M_ptr._M_storage_capacity();
					if (__desired_storage_capacity <= __old_storage_capacity)
						{
							// nothing needs doing
							return __storage._M_ptr._M_storage_pointer_end();
						}

					// need to grow
					__base_pointer __old_storage_pointer =
					     __storage._M_ptr._M_storage_pointer();
					size_type __old_storage_size =
					     __bit_to_element_size<__base_value_type>(__old_size);

					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_capacity);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}

					if (__old_storage_pointer != nullptr)
						{
							__base_pointer __old_storage_pointer_move_arg =
							     __old_storage_pointer;
							if (!_OrphanObjects)
								{
									_S_trampoline_construct_n_using<true>(__mem_alloc,
									     __storage_pointer, __desired_storage_capacity,
									     __old_storage_size,
									     &_S_construct_move_old_pointer,
									     __old_storage_pointer_move_arg);
								}
							_S_destroy(
							     __mem_alloc, __old_storage_pointer, __old_storage_size);
							__alloc_traits::deallocate(
							     __mem_alloc, __old_storage_pointer, __old_storage_capacity);
						}

					__storage._M_ptr._M_first = __storage_pointer;
					__storage._M_ptr._M_last  = __storage_pointer + __desired_storage_capacity;
					if (!_OrphanObjects)
						{
							__storage._M_ptr._M_set_size(__old_storage_size);
						}
					return __storage_pointer;
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_shrink_storage(
		     __alloc& __mem_alloc, _EitherStorage& __storage, size_type __desired_capacity)
		{
			bool __using_sbo = _S_is_sbo(__storage);
			size_type __desired_storage_capacity =
			     __bit_to_element_size<__base_value_type>(__desired_capacity);
			size_type __old_size                 = __storage._M_size();
			size_type __old_storage_size         = __storage._M_storage_size();
			size_type __old_storage_capacity     = __storage._M_storage_capacity();
			__base_pointer __old_storage_pointer = __storage._M_storage_pointer();

			if (_S_is_sbo_size(__desired_capacity))
				{
					if (__using_sbo)
						{
							// already using SBO: just shrink bit size
							// and deconstruct edge words
							size_type __desired_old_storage_size_diff =
							     __old_storage_size - __desired_storage_capacity;
							_S_destroy(__mem_alloc,
							     __old_storage_pointer + __desired_storage_capacity,
							     __desired_old_storage_size_diff);
							__storage._M_buf._M_set_size(__desired_capacity);
							return __storage._M_buf._M_storage_pointer();
						}

					// lifetime reset
					_S_unchecked_switch_storage_to_sbo(__storage);
					__base_pointer __storage_pointer = __storage._M_buf._M_storage_pointer();
					if constexpr (::std::is_nothrow_invocable_v<
					                   decltype(&_S_construct_move_old_pointer), __alloc&,
					                   __base_pointer, __base_pointer>)
						{
							__base_pointer __old_storage_pointer_move_arg =
							     __old_storage_pointer;
							_S_trampoline_construct_n_using<false>(__mem_alloc,
							     __storage_pointer, 0, __desired_storage_capacity,
							     &_S_construct_move_old_pointer,
							     __old_storage_pointer_move_arg);
						}
					else
						{
							// awh geez
							// tread carefully now...
							try
								{
									__base_pointer __old_storage_pointer_move_arg =
									     __old_storage_pointer;
									_S_trampoline_construct_n_using<false>(__mem_alloc,
									     __storage_pointer, 0, __desired_storage_capacity,
									     &_S_construct_move_old_pointer,
									     __old_storage_pointer_move_arg);
								}
							catch (...)
								{
									// something went to shit, fast!
									// Restore old pointers, don't deallocate/destroy,
									// rethrow!
									_S_unchecked_switch_storage_to_heap(__storage);
									__storage._M_ptr._M_bit_size = __old_size;
									__storage._M_ptr._M_first    = __old_storage_pointer;
									__storage._M_ptr._M_last =
									     __old_storage_pointer + __old_storage_capacity;
									throw;
								}
						}
					_S_destroy(__mem_alloc, __old_storage_pointer, __old_storage_size);
					__alloc_traits::deallocate(
					     __mem_alloc, __old_storage_pointer, __old_storage_capacity);

					__storage._M_buf._M_set_size(__desired_capacity);

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
					     __desired_storage_capacity, __desired_storage_capacity,
					     &_S_construct_move_old_pointer, __old_storage_pointer_move_arg);

					size_type __storage_capacity = __storage._M_ptr._M_storage_capacity();
					size_type __storage_size     = __storage._M_ptr._M_storage_size();
					_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
					__alloc_traits::deallocate(
					     __mem_alloc, __storage_pointer, __storage_capacity);

					return __storage_pointer;
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_transfer_inline_to_normal(
		     __alloc& __mem_alloc, _EitherStorage& __storage, size_type __desired_capacity)
		{
			size_type __old_size                 = __storage._M_buf._M_size();
			size_type __old_storage_size         = __storage._M_buf._M_storage_size();
			__base_pointer __old_storage_pointer = __storage._M_buf._M_storage_pointer();
			size_type __desired_storage_capacity =
			     __bit_to_element_size<__base_value_type>(__desired_capacity);
			__base_pointer __storage_pointer =
			     __alloc_traits::allocate(__mem_alloc, __desired_storage_capacity);
			if (__storage_pointer == nullptr)
				{
					throw ::std::bad_alloc();
				}

			if constexpr (_S_is_hyper_sbo_able)
				{
					// Hyper SBO (stealing bits from size parameter)
					// mislaigns all copies, so we need to do it through bit iterators after
					// junk-initializing parameters
					_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer,
					     __desired_storage_capacity, __old_size, &_S_construct_default);

					iterator __old_it(
					     __old_storage_pointer, __storage._M_buf._S_first_bit_index());
					iterator __it(__storage_pointer, 0);
					::std::copy(::std::move(__old_it), __old_size, ::std::move(__it));
				}
			else
				{
					// we are not using Hyper SBO:
					// do can blanket copy/move of original data
					__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
					_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer,
					     __desired_storage_capacity, __old_storage_size,
					     &_S_construct_move_old_pointer, __old_storage_pointer_move_arg);
				}

			// destroy union data
			_S_destroy(__mem_alloc, __old_storage_pointer, __old_storage_size);

			// finally, swap union storage...
			_S_unchecked_switch_storage_to_heap(__storage);
			__storage._M_ptr._M_bit_size = __old_size;
			__storage._M_ptr._M_first    = __storage_pointer;
			__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_capacity;

			return __storage_pointer;
		}

		static constexpr _EitherStorage
		_S_init_empty_storage()
		{
			if constexpr (_S_inline_max_bit_count < 1)
				{
					return _S_init_empty_heap_storage();
				}
			else
				{
					return _EitherStorage();
				}
		}

		static constexpr _EitherStorage
		_S_init_empty_heap_storage()
		{
			return _EitherStorage(::std::in_place);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_unchecked_switch_storage_to_heap(_EitherStorage& __storage)
		{
			// lifetime reset
			__storage._M_buf.~_SboStorage();
			if (false /*::std::is_constant_evaluated()*/)
				{
					// FIXME: destroy + launder + construct_at for constexpr
#if 0
					:::std::construct_at(::std::addressof(__storage._M_ptr));
#endif // :c
				}
			else
				{
					// FIXME: can we directly ::std::launder() here
					// rather than placement new?
					new (::std::addressof(__storage._M_ptr)) _Storage();
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_unchecked_switch_storage_to_sbo(_EitherStorage& __storage)
		{
			__storage._M_ptr.~_Storage();
			if (false /*::std::is_constant_evaluated()*/)
				{
#if 0
					// FIXME: destroy + launder + construct_at for constexpr
					::std::construct_at(::std::addressof(__storage._M_buf));
#endif // :c
				}
			else
				{
					// FIXME: can we directly ::std::launder() here
					// rather than placement new?
					new (::std::addressof(__storage._M_buf)) _SboStorage();
				}
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR _EitherStorage
		_S_init_base_storage(__alloc& __mem_alloc, _It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;
			if (__first == __last)
				{
					// nothing to write into
					return _S_init_empty_storage();
				}

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag,
			                   _ItCategory>)
				{
					size_type __desired_storage_count =
					     static_cast<size_type>(__last - __first);
					size_type __desired_count =
					     __element_to_bit_size<__base_value_type>(__desired_storage_count);
					if (_S_is_sbo_size(__desired_count))
						{
							_EitherStorage __storage = _S_init_empty_storage();
							__base_pointer __storage_pointer =
							     __storage._M_buf._M_storage_pointer();
							_S_trampoline_construct_using<false>(__mem_alloc,
							     __storage_pointer, 0, ::std::move(__first),
							     ::std::move(__last), &_S_construct_iterator<_It>);
							__storage._M_buf._M_set_size(__desired_count);
							return __storage;
						}

					_EitherStorage __storage = _S_init_empty_heap_storage();
					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}
					_S_trampoline_construct_using<true>(__mem_alloc, __storage_pointer,
					     __desired_storage_count, ::std::move(__first), ::std::move(__last),
					     &_S_construct_iterator<_It>);
					__storage._M_ptr._M_first = __storage_pointer;
					__storage._M_ptr._M_last  = __storage_pointer + __desired_storage_count;
					__storage._M_ptr._M_set_size(__desired_count);
					return __storage;
				}
			else
				{
					_EitherStorage __storage         = _S_init_empty_storage();
					size_type __current_size         = 0;
					__base_pointer __storage_pointer = __storage._M_storage_pointer();
					// FIXME: this storage needs the Strong Exception Guarantee
					for (; __first != __last;
					     (void)__current_size += __binary_digits_v<__base_value_type>,
					     (void)++__first, (void)++__storage_pointer)
						{
							if (_S_is_sbo_size(__current_size) &&
							     __current_size == _S_inline_max_bit_count)
								{
									// well, we ran out of Small Buffer bits...
									size_type __current_storage_size =
									     __bit_to_element_size<__base_value_type>(
									          __current_size);
									__storage_pointer = _S_transfer_inline_to_normal(
									     __mem_alloc, __storage, __current_size * 2);
									__storage_pointer += __current_storage_size;
								}
							else if (!_S_is_sbo_size(__current_size) &&
							         __storage_pointer == __storage._M_ptr._M_last)
								{
									size_type __current_storage_size =
									     __bit_to_element_size<__base_value_type>(
									          __current_size);
									__storage_pointer =
									     _S_grow_storage_of_size_with_strategy(
									          __mem_alloc, __storage, __current_size);
									__storage_pointer += __current_storage_size;
								}
							_S_construct_iterator(__mem_alloc, __storage_pointer, __first);
							__storage._M_set_size(__current_size);
						}
					__storage._M_set_size(__current_size);
					return __storage;
				}
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR _EitherStorage
		_S_init_storage(__alloc& __mem_alloc, _It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;
			if (__first == __last)
				{
					// nothing to write into
					return _S_init_empty_storage();
				}

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag,
			                   _ItCategory>)
				{
					size_type __desired_count = static_cast<size_type>(__last - __first);
					size_type __desired_storage_count =
					     __bit_to_element_size<__base_value_type>(__desired_count);
					if (_S_is_sbo_size(__desired_count))
						{
							_EitherStorage __storage = _S_init_empty_storage();
							__base_pointer __storage_pointer =
							     __storage._M_buf._M_storage_pointer();
							_S_trampoline_construct_n_using<false>(__mem_alloc,
							     __storage_pointer, 0, __desired_storage_count,
							     &_S_construct_default);
							iterator __storage_it(
							     __storage_pointer, __storage._M_buf._S_first_bit_index());
							::std::copy(
							     ::std::move(__first), ::std::move(__last), __storage_it);
							__storage._M_buf._M_set_size(
							     static_cast<size_type>(__desired_count));
							return __storage;
						}

					_EitherStorage __storage = _S_init_empty_heap_storage();
					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}
					_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer,
					     __desired_storage_count, __desired_storage_count,
					     &_S_construct_default);
					__storage._M_ptr._M_first = __storage_pointer;
					__storage._M_ptr._M_last  = __storage_pointer + __desired_storage_count;
					__storage._M_ptr._M_set_size(__desired_count);
					iterator __storage_it(__storage_pointer, 0);
					::std::copy(::std::move(__first), ::std::move(__last), __storage_it);
					return __storage;
				}
			else
				{
					_EitherStorage __storage         = _S_init_empty_storage();
					size_type __current_size         = 0;
					__base_pointer __storage_pointer = __storage._M_storage_pointer();
					iterator __storage_it(__storage_pointer, __storage._M_first_bit_index());
					// FIXME: this storage needs the Strong Exception Guarantee
					for (; __first != __last;
					     ++__current_size, (void)++__first, (void)++__storage_it)
						{
							if (_S_is_sbo_size(__current_size) &&
							     __current_size == _S_inline_max_bit_count)
								{
									// well, we ran out of Small Buffer bits...
									size_type __current_storage_size =
									     __bit_to_element_size<__base_value_type>(
									          __current_size);
									__storage_pointer = _S_transfer_inline_to_normal(
									     __mem_alloc, __storage, __current_size * 2);
									__storage_it = iterator(
									     __storage_pointer + __current_storage_size,
									     __storage_it.position());
								}
							else if (!_S_is_sbo_size(__current_size) &&
							         __storage_it.base() == __storage._M_ptr._M_last)
								{
									size_type __current_storage_size =
									     __bit_to_element_size<__base_value_type>(
									          __current_size);
									__storage_pointer =
									     _S_grow_storage_of_size_with_strategy(
									          __mem_alloc, __storage, __current_size);

									__storage_it = iterator(
									     __storage_pointer + __current_storage_size,
									     __storage_it.position());
								}
							if (__storage_it.position() == 0)
								{
									_S_construct_default(__mem_alloc, __storage_it.base());
								}
							*__storage_it = *__first;
							__storage._M_set_size(__current_size);
						}
					__storage._M_set_size(__current_size);
					return __storage;
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR _EitherStorage
		_S_init_storage_count_value(__alloc& __mem_alloc, size_type __desired_count,
		     const __base_value_type& __initial_value)
		{
			if (__desired_count == static_cast<size_type>(0))
				{
					return _S_init_empty_storage();
				}

			size_type __desired_storage_count =
			     __bit_to_element_size<__base_value_type>(__desired_count);
			if (_S_is_sbo_size(__desired_count))
				{
					_EitherStorage __storage         = _S_init_empty_storage();
					__base_pointer __storage_pointer = __storage._M_buf._M_storage_pointer();
					_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
					     __desired_storage_count, &_S_construct_initial_value,
					     __initial_value);
					__storage._M_buf._M_set_size(__desired_count);
					return __storage;
				}

			_EitherStorage __storage = _S_init_empty_heap_storage();
			__base_pointer __storage_pointer =
			     __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
			if (__storage_pointer == nullptr)
				{
					throw ::std::bad_alloc();
				}
			_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer,
			     __desired_storage_count, __desired_storage_count, &_S_construct_initial_value,
			     __initial_value);
			__storage._M_ptr._M_first = __storage_pointer;
			__storage._M_ptr._M_last  = __storage_pointer + __desired_storage_count;
			__storage._M_ptr._M_set_size(__desired_count);
			return __storage;
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR _EitherStorage
		_S_init_storage_count_zero(__alloc& __mem_alloc, size_type __desired_count)
		{
			return _S_init_storage_count_value(
			     __mem_alloc, __desired_count, __base_value_type());
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR _EitherStorage
		_S_init_base_storage_count_zero(__alloc& __mem_alloc, size_type __desired_storage_count)
		{
			return _S_init_storage_count_value(__mem_alloc,
			     __element_to_bit_size<__base_value_type>(__desired_storage_count),
			     __base_value_type());
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR _EitherStorage
		_S_init_base_storage_count_value(__alloc& __mem_alloc, size_type __desired_storage_count,
		     const __base_value_type& __initial_value)
		{
			return _S_init_storage_count_value(__mem_alloc,
			     __element_to_bit_size<__base_value_type>(__desired_storage_count),
			     __initial_value);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_destroy(
		     __alloc& __mem_alloc, __base_pointer __storage_pointer, size_type __desired_count)
		{
			for (; __desired_count-- > 0;)
				{
					__alloc_traits::destroy(
					     __mem_alloc, (__storage_pointer + __desired_count));
				}
		}
	};

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc>
	constexpr bool
	operator==(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
	     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right)
	{
		auto __left_size  = __left.size();
		auto __right_size = __right.size();
		if (__left_size != __right_size)
			{
				return false;
			}

		return ::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc>
	constexpr bool
	operator!=(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
	     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right)
	{
		auto __left_size  = __left.size();
		auto __right_size = __right.size();
		if (__left_size != __right_size)
			{
				return true;
			}
		return !::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc>
	constexpr bool
	operator<(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
	     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right)
	{
		return ::std::lexicographical_compare(
		     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc>
	constexpr bool
	operator<=(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
	     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right)
	{
		return !(__left > __right);
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc>
	constexpr bool
	operator>(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
	     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right)
	{
		return ::std::lexicographical_compare(__left.cbegin(), __left.cend(), __right.cbegin(),
		     __right.cend(), std::greater<bool>());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc>
	constexpr bool
	operator>=(const __small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc>& __left,
	     const __small_bit_vector<_RightTy, _RightInline, _RightAlloc>& __right)
	{
		return !(__left < __right);
	}
} // namespace ITSY_BITSY_DETAIL_NAMESPACE

#undef ITSY_BITSY_ALLOCATOR_CONSTEXPR

#include <itsy/detail/namespace_default_end.hpp>

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_SMALL_BIT_VECTOR_HPP
