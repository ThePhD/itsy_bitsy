#pragma once

#ifndef BITSY_DYNAMIC_BITSET_HPP
#define BITSY_DYNAMIC_BITSET_HPP

#include <itsy/version.hpp>

#if BITSY_SOURCE_LIBSTDCXX
#include <bits/dynamic_bitset.h>
#elif BITSY_SOURCE_LIBCXX
#include <dynamic_bitset.h>
#else
#include <itsy/detail/dynamic_bitset.h>
#endif

#include <itsy/bit_iterator.hpp>
#include <itsy/bit_view.hpp>

#include <cstddef>
#include <vector>

namespace bitsy
{
	template<typename C>
	using basic_dynamic_bitset = __BIT_STRUCTURES_NAMESPACE::__basic_dynamic_bitset<C>;

	using dynamic_bitset = basic_dynamic_bitset<std::vector<std::size_t>>;
} // namespace bitsy

#endif // BITSY_DYNAMIC_BITSET_HPP
