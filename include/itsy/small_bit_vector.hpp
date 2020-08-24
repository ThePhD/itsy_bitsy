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
#define ITSY_BITSY_SMALL_BIT_VECTOR_HPP

#include <itsy/version.hpp>

#include <itsy/detail/small_bit_vector.hpp>

#include <memory>
#include <cstddef>

namespace bitsy
{
	template<typename T, typename Allocator = std::allocator<T>>
	inline constexpr ::std::size_t default_small_buffer_size_v =
	     ::ITSY_BITSY_SOURCE_NAMESPACE::__default_small_buffer_size_v<T, Allocator>;

	template<typename Word,
	     ::std::size_t InlineBufferSize = default_small_buffer_size_v<Word, std::allocator<Word>>,
	     typename Allocator             = std::allocator<Word>>
	class small_bit_vector : public ::ITSY_BITSY_SOURCE_NAMESPACE::__small_bit_vector<Word, InlineBufferSize, Allocator> {
	private:
		using base_t = ::ITSY_BITSY_SOURCE_NAMESPACE::__small_bit_vector<Word, InlineBufferSize, Allocator>;
	public:
		using difference_type = typename base_t::difference_type;
		using size_type       = typename base_t::size_type;
		using value_type      = typename base_t::value_type;
		using reference       = typename base_t::reference;
		using const_reference = typename base_t::const_reference;
		using iterator_category = typename base_t::iterator_category;
		using iterator_concept = typename base_t::iterator_concept;
		using pointer           = typename base_t::pointer;
		using iterator          = typename base_t::iterator;
		using sentinel          = typename base_t::sentinel;
		using const_iterator    = typename base_t::const_iterator;
		using const_sentinel    = typename base_t::const_sentinel;

		using base_t::base_t;
		small_bit_vector(const small_bit_vector&) = default;
		small_bit_vector(small_bit_vector&&) = default;

		small_bit_vector& operator=(const small_bit_vector&) = default;
		small_bit_vector& operator=(small_bit_vector&&) = default;
	};

	template<typename Word,
	     ::std::size_t InlineBufferSize = default_small_buffer_size_v<Word, std::allocator<Word>>,
	     typename Allocator             = std::allocator<Word>>
	class packed_small_bit_vector : public ::ITSY_BITSY_SOURCE_NAMESPACE::__packed_small_bit_vector<Word, InlineBufferSize, Allocator, true> {
	private:
		using base_t = ::ITSY_BITSY_SOURCE_NAMESPACE::__packed_small_bit_vector<Word, InlineBufferSize, Allocator, true>;
	public:
		using difference_type = typename base_t::difference_type;
		using size_type       = typename base_t::size_type;
		using value_type      = typename base_t::value_type;
		using reference       = typename base_t::reference;
		using const_reference = typename base_t::const_reference;
		using iterator_concept = typename base_t::iterator_concept;
		using iterator_category = typename base_t::iterator_category;
		using pointer           = typename base_t::pointer;
		using iterator          = typename base_t::iterator;
		using sentinel          = typename base_t::sentinel;
		using const_iterator    = typename base_t::const_iterator;
		using const_sentinel    = typename base_t::const_sentinel;

		using base_t::base_t;
		packed_small_bit_vector(const packed_small_bit_vector&) = default;
		packed_small_bit_vector(packed_small_bit_vector&&) = default;

		packed_small_bit_vector& operator=(const packed_small_bit_vector&) = default;
		packed_small_bit_vector& operator=(packed_small_bit_vector&&) = default;
	};
} // namespace bitsy

#endif // ITSY_BITSY_SMALL_BIT_VECTOR_HPP
