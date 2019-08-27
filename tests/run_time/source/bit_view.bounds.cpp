// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#include <itsy_tests/constants.hpp>
#include <itsy_tests/shared_tests.hpp>

#include <testsuite_hooks.h>

#include <itsy/bitsy.hpp>

#include <cstddef>
#include <cstdint>
#include <span>
#include <ranges>
#include <iterator>

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <string>

TEMPLATE_TEST_CASE("bit_view bounds testing", "[bit_view<T>][span][bounds]", std::uint64_t,
  std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t,
  std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	// non-exhaustive
	constexpr std::ptrdiff_t off_indices[] = { 1, 2, 3, 4, 5, 6 };
	// exhaustive
	constexpr std::ptrdiff_t on_indices[] = { 0 };

	constexpr std::size_t expected_bits = 15;

	constexpr TestType b00 = static_cast<TestType>(0x00);
	constexpr TestType b01 = static_cast<TestType>(0x01);
	constexpr TestType b10 = static_cast<TestType>(0x02);

	SECTION("vector")
	{
		std::vector<TestType> storage{ b01, b00, b10, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
			b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		generic_bit_bounds_tests<TestType, true, true>(
		  storage, on_indices, off_indices, expected_bits);
	}
	SECTION("deque")
	{
		std::deque<TestType> storage{ b01, b00, b10, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
			b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		generic_bit_bounds_tests<TestType, true, true>(
		  storage, on_indices, off_indices, expected_bits);
	}
	SECTION("deque")
	{
		std::deque<TestType> storage{ b01, b00, b10, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
			b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		generic_bit_bounds_tests<TestType, true, true>(
		  storage, on_indices, off_indices, expected_bits);
	}
}
