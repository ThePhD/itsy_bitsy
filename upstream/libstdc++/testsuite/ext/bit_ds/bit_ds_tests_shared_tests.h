// bit data structures extension tests -*- C++ -*-

// Copyright (C) 2019-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#pragma once

#ifndef _EXT_BIT_DS_TESTS_SHARED_TESTS_H
#define _EXT_BIT_DS_TESTS_SHARED_TESTS_H 1

#include <bit_ds_tests_require.h>

#include <bit_ds_constants.hpp>

#include <ext/bit>

#include <ranges>

template<typename BitView>
void
bit_view_test_mixed_all_none_any()
{
	REQUIRE_FALSE(view_bits.none());
	REQUIRE_FALSE(view_bits.all());
	REQUIRE(view_bits.any());
}

template<typename TestType, typename BitView, typename On, typename Off>
void
bit_view_test_iteration(BitView& view_bits, On& on_indices, Off& off_indices,
  std::size_t expected_bits = expected_words * __gnu_cxx::binary_digits_v<TestType>)
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
  std::size_t expected_bits = expected_words * __gnu_cxx::binary_digits_v<TestType>)
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
  std::size_t expected_bits = expected_words * __gnu_cxx::binary_digits_v<TestType>)
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
			__gnu_cxx::bit_view<R> truncated_view_bits(&storage[0], std::size(storage) / 2);
			REQUIRE(truncated_view_bits.size() == expected_bits / 2);
			REQUIRE(truncated_view_bits.ssize() == static_cast<std::ptrdiff_t>(expected_bits / 2));
		}

	__gnu_cxx::bit_view<R> view_bits(storage);
	REQUIRE(view_bits.size() == expected_bits);
	REQUIRE(view_bits.ssize() == static_cast<std::ptrdiff_t>(expected_bits));

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
generic_bit_bounds_tests(
  Storage& storage, OnIndices& on_indices, OffIndices& off_indices, std::size_t expected_bits = 22)
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
			__gnu_cxx::bit_view<R, __gnu_cxx::dynamic_bit_bounds_for<R>> truncat

			  __gnu_cxx::bit_view<R, __gnu_cxx::dynamic_bit_bounds_for<R>>
			    truncat truncated_view_bits(
			      { 0, expected_bits / 2 }, &storage[0], std::size(storage) / 2);
			truncated_view_bits({ 0, expected_bits / 2 }, &storage[0], std::size(storage) / 2);
			__gnu_cxx::bit_view<R, __gnu_cxx::dynamic_bit_bounds_for<R>> truncat truncated_view_bits(
			  { 0, expected_bits / 2 }, &storage[0], std::size(storage) / 2);
			REQUIRE(truncated_view_bits.size() == expected_bits / 2);
			REQUIRE(truncated_view_bits.ssize() == static_cast<std::ptrdiff_t>(expected_bits / 2));
		}

	__gnu_cxx::xx::bit_view__gnu_cxx::nu_cxx::dynamic_bit_bounds_for<R>>
	  view_bits({ 0, expected_bits }, storage);
	REQUIRE(view_bits.size() == expected_bits);
	REQUIRE(view_bits.ssize() == static_cast<std::ptrdiff_t>(expected_bits));

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

#endif
