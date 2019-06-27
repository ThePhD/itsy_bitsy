#pragma once

#ifndef BITSY_TESTS_GENERIC_TESTS_HPP
#define BITSY_TESTS_GENERIC_TESTS_HPP

#include <catch2/catch.hpp>

#include <bitsy_tests/constants.hpp>

#include <bitsy/binary_digits.hpp>

template<typename BitView>
void
bit_view_test_mixed_any_all_none(BitView& view_bits)
{
  REQUIRE_FALSE(view_bits.none());
  REQUIRE_FALSE(view_bits.all());
  REQUIRE(view_bits.any());
}

template<typename TestType, typename BitView, typename On, typename Off>
void
bit_view_test_iteration(BitView& view_bits, On& on_indices, Off& off_indices)
{
  constexpr std::size_t expected_bits     = expected_words * bitsy::binary_digits_v<TestType>;
  constexpr std::size_t expected_on_bits  = std::size(on_indices);
  constexpr std::size_t expected_off_bits = expected_bits - expected_on_bits;

  for (const auto& off_index : off_indices)
  {
    bool off_index_bit = view_bits[off_index];
    REQUIRE_FALSE(off_index_bit);
    REQUIRE(off_index_bit == view_bits.test(off_index));
  }

  for (const auto& on_index : on_indices)
  {
    bool on_index_bit = view_bits[on_index];
    REQUIRE(on_index_bit);
    REQUIRE(on_index_bit == view_bits.test(on_index));
  }

  {
    std::size_t iter_count     = 0;
    std::size_t iter_on_count  = 0;
    std::size_t iter_off_count = 0;
    for (const auto& ref : view_bits)
    {
      ++iter_count;
      if (ref)
      {
        ++iter_on_count;
      } else
      {
        ++iter_off_count;
      }
    }
    REQUIRE(iter_count == expected_bits);
    REQUIRE(iter_on_count == expected_on_bits);
    REQUIRE(iter_off_count == expected_off_bits);
  }

  REQUIRE(view_bits.population_count() == expected_on_bits);
  REQUIRE(view_bits.count(true) == expected_on_bits);
  REQUIRE(view_bits.count(false) == expected_off_bits);
}

template<typename BitView>
void
bit_view_test_iterator_comparisons(BitView& view_bits)
{
  auto first = view_bits.begin();
  auto lower = first;
  ++lower;
  auto upper = lower;
  ++upper;
  auto last = view_bits.end();

  REQUIRE(first == first);
  REQUIRE(lower == lower);
  REQUIRE(upper == upper);
  REQUIRE(last == last);

  REQUIRE(first != lower);
  REQUIRE(first != upper);
  REQUIRE(first != last);

  REQUIRE(lower != first);
  REQUIRE(lower != upper);
  REQUIRE(lower != last);

  REQUIRE(upper != first);
  REQUIRE(upper != lower);
  REQUIRE(upper != last);

  REQUIRE(last != first);
  REQUIRE(last != lower);
  REQUIRE(last != upper);

  REQUIRE(first < lower);
  REQUIRE(first < upper);
  REQUIRE(first < last);

  REQUIRE(last > first);
  REQUIRE(last > lower);
  REQUIRE(last > upper);

  REQUIRE(first <= first);
  REQUIRE(first <= lower);
  REQUIRE(first <= upper);
  REQUIRE(first <= last);

  REQUIRE(last >= first);
  REQUIRE(last >= lower);
  REQUIRE(last >= upper);
  REQUIRE(last >= last);
}

template<typename TestType, typename BitSpan, typename On>
void
bit_span_test_writability(BitSpan& span_bits, On& on_indices)
{
  constexpr std::size_t expected_bits = expected_words * bitsy::binary_digits_v<TestType>;
  constexpr std::size_t initial_expected_on_bits  = std::size(on_indices);
  constexpr std::size_t initial_expected_off_bits = expected_bits - initial_expected_on_bits;

  constexpr std::size_t post_expected_on_bits  = expected_bits - std::size(on_indices);
  constexpr std::size_t post_expected_off_bits = expected_bits - post_expected_on_bits;

  REQUIRE(span_bits.population_count() == initial_expected_on_bits);
  REQUIRE(span_bits.count(true) == initial_expected_on_bits);
  REQUIRE(span_bits.count(false) == initial_expected_off_bits);

  for (const auto& flip_index : on_indices)
  {
    auto flip_index_bit = span_bits[flip_index];
    REQUIRE(flip_index_bit);
    REQUIRE(flip_index_bit == span_bits.test(flip_index));
    span_bits.flip(flip_index);
    REQUIRE_FALSE(flip_index_bit);
    REQUIRE(flip_index_bit == span_bits.test(flip_index));
  }

  REQUIRE(span_bits.population_count() == post_expected_on_bits);
  REQUIRE(span_bits.count(true) == post_expected_on_bits);
  REQUIRE(span_bits.count(false) == post_expected_off_bits);

  for (const auto& flip_index : on_indices)
  {
    auto flip_index_bit = span_bits[flip_index];
    REQUIRE_FALSE(flip_index_bit);
    REQUIRE(flip_index_bit == span_bits.test(flip_index));
    flip_index_bit = !static_cast<bool>(flip_index_bit);
    REQUIRE(flip_index_bit);
    REQUIRE(flip_index_bit == span_bits.test(flip_index));
  }

  REQUIRE(span_bits.population_count() == initial_expected_on_bits);
  REQUIRE(span_bits.count(true) == initial_expected_on_bits);
  REQUIRE(span_bits.count(false) == initial_expected_off_bits);

  for (const auto& set_index : on_indices)
  {
    auto set_index_bit = span_bits[set_index];
    REQUIRE(set_index_bit);
    REQUIRE(set_index_bit == span_bits.test(set_index));
    span_bits.set(set_index_bit, false);
    REQUIRE_FALSE(set_index_bit);
    REQUIRE(set_index_bit == span_bits.test(set_index));
  }

  REQUIRE(span_bits.population_count() == post_expected_on_bits);
  REQUIRE(span_bits.count(true) == post_expected_on_bits);
  REQUIRE(span_bits.count(false) == post_expected_off_bits);

  for (const auto& set_index : on_indices)
  {
    auto set_index_bit = span_bits[set_index];
    REQUIRE_FALSE(set_index_bit);
    REQUIRE(set_index_bit == span_bits.test(set_index));
    span_bits.set(set_index_bit, true);
    REQUIRE(set_index_bit);
    REQUIRE(set_index_bit == span_bits.test(set_index));
  }

  REQUIRE(span_bits.population_count() == initial_expected_on_bits);
  REQUIRE(span_bits.count(true) == initial_expected_on_bits);
  REQUIRE(span_bits.count(false) == initial_expected_off_bits);
}

#endif // BITSY_TESTS_GENERIC_TESTS_HPP
