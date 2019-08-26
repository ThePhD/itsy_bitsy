#pragma once

#ifndef ITSY_BITSY_DYNAMIC_BITSET_HPP
#define ITSY_BITSY_DYNAMIC_BITSET_HPP

#include <itsy/version.hpp>

#include <itsy/bit_sequence.hpp>

#include <cstddef>
#include <vector>

namespace bitsy
{
	template<typename C>
	using basic_dynamic_bitset = basic_bit_sequence<C>;

	template<typename T, typename Allocator = std::allocator<T>>
	using dynamic_bitset = basic_dynamic_bitset<std::vector<T, Allocator>>;
} // namespace bitsy

#endif // ITSY_BITSY_DYNAMIC_BITSET_HPP
