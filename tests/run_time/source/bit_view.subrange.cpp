// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy_tests/constants.hpp>
#include <itsy_tests/shared_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <cstddef>
#include <cstdint>
#include <span>
#include <iterator>

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <string>

TEMPLATE_TEST_CASE("bit_view functionality with subranges", "[bit_view<T>][subrange]",
  std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
  std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t,
  std::ptrdiff_t)
{
	// non-exhaustive
	constexpr std::ptrdiff_t off_indices[] = { 1, 2, 3, 4, 5, 6,
		5 + 2 * bitsy::binary_digits_v<TestType>, 3 + 8 * bitsy::binary_digits_v<TestType>,
		3 + 12 * bitsy::binary_digits_v<TestType>, 7 + 17 * bitsy::binary_digits_v<TestType>,
		4 + 23 * bitsy::binary_digits_v<TestType> };
	// exhaustive
	constexpr std::ptrdiff_t on_indices[] = { 0, 0 + 2 * bitsy::binary_digits_v<TestType>,
		0 + 7 * bitsy::binary_digits_v<TestType>, 0 + 12 * bitsy::binary_digits_v<TestType>,
		0 + 17 * bitsy::binary_digits_v<TestType>, 0 + 22 * bitsy::binary_digits_v<TestType>,
		0 + 27 * bitsy::binary_digits_v<TestType>, 1 + 29 * bitsy::binary_digits_v<TestType> };

	constexpr std::size_t expected_bits = expected_words * bitsy::binary_digits_v<TestType>;

	constexpr TestType b00 = static_cast<TestType>(0x00);
	constexpr TestType b01 = static_cast<TestType>(0x01);
	constexpr TestType b10 = static_cast<TestType>(0x02);

	SECTION("subrange")
	{
		SECTION("deque")
		{
			std::deque<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
				b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
			generic_bit_tests<TestType, false, true>(storage, on_indices, off_indices, expected_bits);
		}
		SECTION("list")
		{
			std::list<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
				b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
			generic_bit_tests<TestType, false, true>(storage, on_indices, off_indices, expected_bits);
		}
#if 0 
		// NOT SUPPORTED YET
		SECTION("forward_list")
		{
			std::forward_list<TestType> storage{ b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
				b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
				b10 };
			generic_bit_tests<TestType, false, true>(storage, on_indices, off_indices, expected_bits);
		}
#endif
	}
}
