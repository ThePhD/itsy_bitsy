// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#pragma once

#ifndef ITSY_BITSY_TESTS_SHARED_TESTS_HPP
#define ITSY_BITSY_TESTS_SHARED_TESTS_HPP

#include <catch2/catch.hpp>

#include <itsy_tests/constants.hpp>

#include <itsy/bitsy.hpp>

#include <ranges>
#include <span>

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
bit_view_test_iteration(BitView& view_bits, On& on_indices, Off& off_indices,
     std::size_t expected_bits = expected_words * bitsy::binary_digits_v<TestType>)
{
	const std::size_t expected_on_bits  = std::size(on_indices);
	const std::size_t expected_off_bits = expected_bits - expected_on_bits;

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
					}
				else
					{
						++iter_off_count;
					}
			}
		REQUIRE(iter_count == expected_bits);
		REQUIRE(iter_on_count == expected_on_bits);
		REQUIRE(iter_off_count == expected_off_bits);
	}

	REQUIRE(view_bits.one_count() == expected_on_bits);
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
bit_view_test_writability(BitSpan& span_bits, On& on_indices,
     std::size_t expected_bits = expected_words * bitsy::binary_digits_v<TestType>)
{
	const std::size_t initial_expected_on_bits  = std::size(on_indices);
	const std::size_t initial_expected_off_bits = expected_bits - initial_expected_on_bits;

	std::size_t post_expected_on_bits  = 0;
	std::size_t post_expected_off_bits = expected_bits - post_expected_on_bits;

	REQUIRE(span_bits.one_count() == initial_expected_on_bits);
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

	REQUIRE(span_bits.one_count() == post_expected_on_bits);
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

	REQUIRE(span_bits.one_count() == initial_expected_on_bits);
	REQUIRE(span_bits.count(true) == initial_expected_on_bits);
	REQUIRE(span_bits.count(false) == initial_expected_off_bits);

	for (const auto& set_index : on_indices)
		{
			auto set_index_bit = span_bits[set_index];
			REQUIRE(set_index_bit);
			REQUIRE(set_index_bit == span_bits.test(set_index));
			span_bits.set(set_index, false);
			REQUIRE_FALSE(set_index_bit);
			REQUIRE(set_index_bit == span_bits.test(set_index));
		}

	REQUIRE(span_bits.one_count() == post_expected_on_bits);
	REQUIRE(span_bits.count(true) == post_expected_on_bits);
	REQUIRE(span_bits.count(false) == post_expected_off_bits);

	for (const auto& set_index : on_indices)
		{
			auto set_index_bit = span_bits[set_index];
			REQUIRE_FALSE(set_index_bit);
			REQUIRE(set_index_bit == span_bits.test(set_index));
			span_bits.set(set_index, true);
			REQUIRE(set_index_bit);
			REQUIRE(set_index_bit == span_bits.test(set_index));
		}

	REQUIRE(span_bits.one_count() == initial_expected_on_bits);
	REQUIRE(span_bits.count(true) == initial_expected_on_bits);
	REQUIRE(span_bits.count(false) == initial_expected_off_bits);

	for (const auto& set_index : on_indices)
		{
			auto set_index_bit = span_bits[set_index];
			REQUIRE(set_index_bit);
			REQUIRE(set_index_bit == span_bits.test(set_index));
			span_bits[set_index] = false;
			REQUIRE_FALSE(set_index_bit);
			REQUIRE(set_index_bit == span_bits.test(set_index));
		}

	REQUIRE(span_bits.one_count() == post_expected_on_bits);
	REQUIRE(span_bits.count(true) == post_expected_on_bits);
	REQUIRE(span_bits.count(false) == post_expected_off_bits);

	for (const auto& set_index : on_indices)
		{
			auto set_index_bit = span_bits[set_index];
			REQUIRE_FALSE(set_index_bit);
			REQUIRE(set_index_bit == span_bits.test(set_index));
			span_bits[set_index] = true;
			REQUIRE(set_index_bit);
			REQUIRE(set_index_bit == span_bits.test(set_index));
		}

	REQUIRE(span_bits.popcount() == initial_expected_on_bits);
	REQUIRE(span_bits.count(true) == initial_expected_on_bits);
	REQUIRE(span_bits.count(false) == initial_expected_off_bits);
}

template<typename TestType, bool check_iterator_comparisons = true, bool check_writability = true,
     typename Storage, typename OnIndices, typename OffIndices>
void
generic_bit_tests(Storage& storage, OnIndices& on_indices, OffIndices& off_indices,
     std::size_t expected_bits = expected_words * bitsy::binary_digits_v<TestType>)
{
	using span_range = std::span<TestType>;
	using sub_range =
	     std::ranges::subrange<decltype(std::begin(storage)), decltype(std::end(storage))>;
	using c_sub_range =
	     std::ranges::subrange<decltype(std::cbegin(storage)), decltype(std::cend(storage))>;
	using R = std::conditional_t<std::is_constructible_v<span_range, Storage&>, span_range,
	     std::conditional_t<std::is_const_v<TestType>, c_sub_range, sub_range>>;

	if constexpr (check_iterator_comparisons)
		{
			REQUIRE(std::size(storage) == expected_words);
			bitsy::bit_view<R> truncated_view_bits(&storage[0], std::size(storage) / 2);
			REQUIRE(truncated_view_bits.size() == expected_bits / 2);
		}

	bitsy::bit_view<R> view_bits(storage);
	REQUIRE(view_bits.size() == expected_bits);

	bit_view_test_mixed_any_all_none(view_bits);
	bit_view_test_iteration<TestType>(view_bits, on_indices, off_indices, expected_bits);
	if constexpr (check_iterator_comparisons)
		{
			bit_view_test_iterator_comparisons(view_bits);
		}
	if constexpr (check_writability)
		{
			bit_view_test_writability<TestType>(view_bits, on_indices, expected_bits);
		}
}

template<typename TestType, bool check_iterator_comparisons = true, bool check_writability = true,
     typename Storage, typename OnIndices, typename OffIndices>
void
generic_bit_bounds_tests(Storage& storage, OnIndices& on_indices, OffIndices& off_indices,
     std::size_t expected_bits = 22)
{
	using span_range = std::span<TestType>;
	using sub_range =
	     std::ranges::subrange<decltype(std::begin(storage)), decltype(std::end(storage))>;
	using c_sub_range =
	     std::ranges::subrange<decltype(std::cbegin(storage)), decltype(std::cend(storage))>;
	using R = std::conditional_t<std::is_constructible_v<span_range, Storage&>, span_range,
	     std::conditional_t<std::is_const_v<TestType>, c_sub_range, sub_range>>;

	if constexpr (std::is_same_v<span_range, R>)
		{
			bitsy::bit_view<R, bitsy::dynamic_bit_bounds_for<R>> truncated_view_bits(
			     { 0, expected_bits / 2 }, &storage[0], std::size(storage) / 2);
			REQUIRE(truncated_view_bits.size() == expected_bits / 2);
		}

	bitsy::bit_view<R, bitsy::dynamic_bit_bounds_for<R>> view_bits({ 0, expected_bits }, storage);
	REQUIRE(view_bits.size() == expected_bits);

	bit_view_test_mixed_any_all_none(view_bits);
	bit_view_test_iteration<TestType>(view_bits, on_indices, off_indices, expected_bits);
	if constexpr (check_iterator_comparisons)
		{
			bit_view_test_iterator_comparisons(view_bits);
		}
	if constexpr (check_writability)
		{
			bit_view_test_writability<TestType>(view_bits, on_indices, expected_bits);
		}
}

#endif // BITSY_TESTS_SHARED_TESTS_HPP
