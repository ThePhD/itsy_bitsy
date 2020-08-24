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

#ifndef ITSY_BITSY_DYNAMIC_BITSET_HPP
#define ITSY_BITSY_DYNAMIC_BITSET_HPP

#include <itsy/version.hpp>

#include <itsy/bit_sequence.hpp>
#include <itsy/small_bit_vector.hpp>

#include <cstddef>

namespace bitsy
{
	template<typename T, typename Allocator = std::allocator<T>>
	class dynamic_bitset : public small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator> {
	private:
		using base_t = small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator>;
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
		dynamic_bitset(const dynamic_bitset&) = default;
		dynamic_bitset(dynamic_bitset&&) = default;

		dynamic_bitset& operator=(const dynamic_bitset&) = default;
		dynamic_bitset& operator=(dynamic_bitset&&) = default;
	};

	template<typename T, typename Allocator = std::allocator<T>>
	class packed_dynamic_bitset : public packed_small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator> {
	private:
		using base_t = packed_small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator>;
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
		packed_dynamic_bitset(const packed_dynamic_bitset&) = default;
		packed_dynamic_bitset(packed_dynamic_bitset&&) = default;

		packed_dynamic_bitset& operator=(const packed_dynamic_bitset&) = default;
		packed_dynamic_bitset& operator=(packed_dynamic_bitset&&) = default;
	};
} // namespace bitsy

#endif // ITSY_BITSY_DYNAMIC_BITSET_HPP
