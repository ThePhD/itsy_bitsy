#pragma once

#ifndef BITSY_DYNAMIC_BITSET_HPP
#define BITSY_DYNAMIC_BITSET_HPP

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
// <ThePhD>: __GLIBCXX__ is in compressed ISO date format as an Unsigned Long
// compare to September 1st, 2019 to know if GSOC finished.
// Should have been merged by this time, anyways,
// but this is past me, calling out future me if I fail :D

// GSoC finished, and bit iterator should be in bits/bit_iterator.h
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#include <bits/dynamic_bitset.h>

#elif defined(_LIBCPP_VERSION) && _LIBCPP_VERSION > 11000
// _LIBCPP_VERSION is VER_NUMBER RELEASE_NUM, where VER_NUMBER is
// the latest version and RELEASE_NUM is
// GSoC finished, and bit iterator should be in bits/bit_iterator.h
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#include <dynamic_bitset.h>

#else

#define __BIT_STRUCTURES_NAMESPACE __std_detail
#include <bitsy/detail/dynamic_bitset.h>

#endif

#include <bitsy/bit_iterator.hpp>
#include <bitsy/bit_view.hpp>
#include <bitsy/bit_span.hpp>

#include <cstddef>
#include <vector>

namespace bitsy
{
  template<typename C>
  using basic_dynamic_bitset = __BIT_STRUCTURES_NAMESPACE::__basic_dynamic_bitset<C>;

  using dynamic_bitset = basic_dynamic_bitset<std::vector<std::size_t>>;
} // namespace bitsy

#endif // BITSY_DYNAMIC_BITSET_HPP
