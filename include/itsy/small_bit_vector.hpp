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

#ifndef ITSY_BITSY_SMALL_BIT_VECTOR_HPP
#define ITSY_BITSY_SMALL_BIT_VECTOR_HPP 1

#include <itsy/version.hpp>

#include <itsy/basic_small_bit_vector.hpp>

namespace bitsy
{

	template<typename _Type, ::std::size_t _InlineWords = default_small_buffer_size_v<_Type, ::std::allocator<_Type>>,
	     typename _Allocator = ::std::allocator<_Type>>
	class packed_small_bit_vector : public basic_small_bit_vector<_Type, _InlineWords, _Allocator, true>
	{
	private:
		template<typename, ::std::size_t, typename, bool>
		friend class basic_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class packed_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class small_bit_vector;

		using __base_t = basic_small_bit_vector<_Type, _InlineWords, _Allocator, true>;

	public:
		using __base_t::__base_t;
		packed_small_bit_vector(const packed_small_bit_vector&) = default;
		packed_small_bit_vector(packed_small_bit_vector&&)      = default;

		packed_small_bit_vector&
		operator=(const packed_small_bit_vector&) = default;
		packed_small_bit_vector&
		operator=(packed_small_bit_vector&&) = default;
	};

	template<typename _Type, ::std::size_t _InlineWords = default_small_buffer_size_v<_Type, ::std::allocator<_Type>>,
	     typename _Allocator = ::std::allocator<_Type>>
	class small_bit_vector : public basic_small_bit_vector<_Type, _InlineWords, _Allocator, false>
	{
	private:
		template<typename, ::std::size_t, typename, bool>
		friend class basic_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class packed_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class small_bit_vector;

		using __base_t = basic_small_bit_vector<_Type, _InlineWords, _Allocator, false>;

	public:
		using __base_t::__base_t;
		small_bit_vector(const small_bit_vector&) = default;
		small_bit_vector(small_bit_vector&&)      = default;

		small_bit_vector&
		operator=(const small_bit_vector&) = default;
		small_bit_vector&
		operator=(small_bit_vector&&) = default;
	};

	template<typename _Type, typename _Allocator = ::std::allocator<_Type>>
	class bit_vector : public basic_small_bit_vector<_Type, 0, _Allocator, false>
	{
	private:
		template<typename, ::std::size_t, typename, bool>
		friend class basic_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class packed_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class small_bit_vector;

		using __base_t = basic_small_bit_vector<_Type, 0, _Allocator, false>;

	public:
		using __base_t::__base_t;
		bit_vector(const bit_vector&) = default;
		bit_vector(bit_vector&&)      = default;

		bit_vector&
		operator=(const bit_vector&) = default;
		bit_vector&
		operator=(bit_vector&&) = default;
	};
} // namespace bitsy

#undef ITSY_BITSY_ALLOCATOR_CONSTEXPR

#endif // ITSY_BITSY_SMALL_BIT_VECTOR_HPP
