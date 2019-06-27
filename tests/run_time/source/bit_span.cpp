#include <bitsy_tests/constants.hpp>
#include <bitsy_tests/generic_tests.hpp>

#include <catch2/catch.hpp>

#include <bitsy/bit_span.hpp>

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

TEMPLATE_TEST_CASE("bit_span functionality with ranges", "[bit_span][ranges]", std::size_t,
  std::uint32_t, std::uint16_t, std::uint8_t, std::byte, char32_t, char16_t, unsigned char,
  signed char, std::int32_t, std::int64_t)
{
  // non-exhaustive
  constexpr std::ptrdiff_t off_indices[] = { 0, 1, 2, 3, 4, 5, 6,
    5 + 2 * bitsy::binary_digits_v<TestType>, 3 + 8 * bitsy::binary_digits_v<TestType>,
    3 + 12 * bitsy::binary_digits_v<TestType>, 7 + 17 * bitsy::binary_digits_v<TestType>,
    4 + 23 * bitsy::binary_digits_v<TestType> };
  // exhaustive
  constexpr std::ptrdiff_t on_indices[] = { 0 + 2 * bitsy::binary_digits_v<TestType>,
    0 + 7 * bitsy::binary_digits_v<TestType>, 0 + 12 * bitsy::binary_digits_v<TestType>,
    0 + 17 * bitsy::binary_digits_v<TestType>, 0 + 22 * bitsy::binary_digits_v<TestType>,
    0 + 27 * bitsy::binary_digits_v<TestType>, 1 + 29 * bitsy::binary_digits_v<TestType> };

  constexpr std::size_t expected_bits = expected_words * bitsy::binary_digits_v<TestType>;

  constexpr TestType b00 = static_cast<TestType>(0x00);
  constexpr TestType b01 = static_cast<TestType>(0x01);
  constexpr TestType b10 = static_cast<TestType>(0x02);

  SECTION("span")
  {
    auto storage_test = [&](auto& storage) {
      using R = std::span<TestType>;

      REQUIRE(std::size(storage) == expected_words);
      {
        bitsy::bit_span<R> truncated_view_bits(&storage[0], std::size(storage) / 2);
        REQUIRE(truncated_view_bits.size() == expected_bits / 2);
        REQUIRE(truncated_view_bits.count() == static_cast<std::ptrdiff_t>(expected_bits / 2));
      }

      bitsy::bit_span<R> view_bits(storage);
      REQUIRE(view_bits.size() == expected_bits);
      REQUIRE(view_bits.count() == static_cast<std::ptrdiff_t>(expected_bits));

      bit_view_test_mixed_any_all_none(view_bits);
      bit_view_test_iteration<TestType>(view_bits, on_indices, off_indices);
      bit_view_test_iterator_comparisons(view_bits);
      bit_span_test_writability<TestType>(view_bits, on_indices);
    };
    SECTION("vector")
    {
      std::vector<TestType> storage{ b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
        b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
      storage_test(storage);
    }
    SECTION("std::array")
    {
      std::array<TestType, expected_words> storage{ b00, b00, b01, b00, b00, b00, b00, b01, b00,
        b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
        b01, b00, b10 };
      storage_test(storage);
    }
    SECTION("std::basic_string")
    {
      std::basic_string<TestType> storage{ b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
        b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
        b10 };
      storage_test(storage);
    }
    SECTION("c array")
    {
      TestType storage[expected_words]{ b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
        b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
      storage_test(storage);
    }
  }
  SECTION("subrange")
  {
    auto storage_test = [&](auto& storage) {
      using R = ranges::subrange<decltype(std::begin(storage)), decltype(std::end(storage))>;
      R view(std::begin(storage), std::end(storage));
      bitsy::bit_span<R> view_bits(std::move(view));

      bit_view_test_mixed_any_all_none(view_bits);
      bit_view_test_iteration<TestType>(view_bits, on_indices, off_indices);
      bit_span_test_writability<TestType>(view_bits, on_indices);
    };
    SECTION("deque")
    {
      std::deque<TestType> storage{ b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
        b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
      storage_test(storage);
    }
    SECTION("list")
    {
      std::list<TestType> storage{ b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
        b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
      storage_test(storage);
    }
    SECTION("forward_list")
    {
      std::forward_list<TestType> storage{ b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
        b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
        b10 };
      storage_test(storage);
    }
  }
}
