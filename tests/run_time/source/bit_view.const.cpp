#include <bitsy_tests/constants.hpp>
#include <bitsy_tests/generic_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/bit_view.hpp>

#include <range/v3/view/subrange.hpp>

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

TEMPLATE_TEST_CASE("bit_view<const T> extents", "[bit_view<const T>][extents]", std::uint64_t,
  std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t,
  std::int8_t, char32_t, char16_t, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
}
