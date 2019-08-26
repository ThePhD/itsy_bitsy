#pragma once

#ifndef ITSY_BITSY_DYNAMIC_BITSET_HPP
#define ITSY_BITSY_DYNAMIC_BITSET_HPP

#include <itsy/version.hpp>

#include <itsy/bit_sequence.hpp>

#include <cstddef>
#include <vector>

namespace bitsy
{
	template<typename T, typename Allocator = std::allocator<T>>
	using dynamic_bitset = bit_sequence<std::vector<T, Allocator>>;
} // namespace bitsy

#endif // ITSY_BITSY_DYNAMIC_BITSET_HPP
