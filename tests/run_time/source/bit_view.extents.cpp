#include <bitsy_tests/constants.hpp>
#include <bitsy_tests/generic_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/bit_view.hpp>

#include <range/v3/all.hpp>

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

TEMPLATE_TEST_CASE("bit_view extents testing", "[bit_view<T>][span][extents]", std::uint64_t,
  std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t,
  std::int8_t, char32_t, char16_t, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	// non-exhaustive
	constexpr std::ptrdiff_t off_indices[] = { 1, 2, 3, 4, 5, 6 };
	// exhaustive
	constexpr std::ptrdiff_t on_indices[] = { 0 };

	constexpr std::size_t expected_bits = 15;

	SECTION("vector")
	{
		std::vector<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
			b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
		generic_bit_extents_tests<TestType, false, true>(storage, on_indices, off_indices);
	}
}
