// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <cstddef>
#include <cstdint>
#include <span>
#include <initializer_list>

TEMPLATE_TEST_CASE("bit algorithm, const", "[algorithm][const]", std::uint64_t, std::uint32_t,
  std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t, std::int8_t,
  char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	using bit_view = bitsy::bit_span<const TestType>;
	using bit_view_dynamic_bound =
	  bitsy::bit_view<std::span<const TestType>, bitsy::dynamic_bit_bounds>;
	using size_type = typename bit_view::size_type;

	const std::initializer_list<bool> il_false                  = { false };
	const std::initializer_list<bool> il_true                   = { true };
	const std::initializer_list<bitsy::bit_value> il_true_false = { true, false };
	const TestType single_value{ static_cast<TestType>(
		std::numeric_limits<bitsy::detail::any_to_underlying_t<TestType>>::max() &
		~static_cast<bitsy::detail::any_to_underlying_t<TestType>>(0b1111)) };
	// Something a bit larger than typical L1 cache
	// to make sure the compiler can't just swallow it all up in registers
	std::vector<TestType> multi_value(40 * 1024, static_cast<TestType>(0));
	multi_value.push_back(static_cast<TestType>(0x36));
	const bit_view single_word_view(&single_value, &single_value + 1);
	const bit_view multi_word_view(multi_value);

	const size_type expected_single_lsb_zero_bit       = 1;
	const size_type expected_single_lsb_zero_bit_index = expected_single_lsb_zero_bit - 1;
	const size_type expected_single_lsb_one_bit        = 5;
	const size_type expected_single_lsb_one_bit_index  = expected_single_lsb_one_bit - 1;
	const size_type expected_single_zeroes_count       = 4;
	const size_type expected_single_ones_count =
	  bitsy::binary_digits_v<TestType> - expected_single_zeroes_count;

	const size_type expected_multi_lsb_zero_bit       = 1;
	const size_type expected_multi_lsb_zero_bit_index = expected_multi_lsb_zero_bit - 1;
	const size_type expected_multi_lsb_one_bit =
	  (multi_value.size() - 1) * bitsy::binary_digits_v<TestType> + 2;
	const size_type expected_multi_lsb_one_bit_index = expected_multi_lsb_one_bit - 1;
	const size_type expected_multi_ones_count        = 4;
	const size_type expected_multi_ones_view_count   = 2;
	const size_type expected_multi_zeroes_count = multi_word_view.size() - expected_multi_ones_count;
	const size_type expected_multi_zeroes_view_count = expected_multi_lsb_one_bit_index;

	const bit_view_dynamic_bound single_word_zeroes_view(
	  bitsy::dynamic_bit_bounds(0, expected_single_zeroes_count), &single_value, &single_value + 1);
	const bit_view_dynamic_bound single_word_ones_view(
	  bitsy::dynamic_bit_bounds(expected_single_lsb_one_bit_index,
	    expected_single_lsb_one_bit_index + expected_single_ones_count),
	  &single_value, &single_value + 1);
	const bit_view_dynamic_bound multi_word_zeroes_view(
	  bitsy::dynamic_bit_bounds(0, expected_multi_lsb_one_bit_index), multi_value.data(),
	  multi_value.data() + multi_value.size());
	const bit_view_dynamic_bound multi_word_ones_view(
	  bitsy::dynamic_bit_bounds(
	    expected_multi_lsb_one_bit_index, expected_multi_lsb_one_bit_index + 2),
	  multi_value.data(), multi_value.data() + multi_value.size());

	auto single_view_ones_count          = single_word_view.one_count();
	auto single_ones_view_ones_count     = single_word_ones_view.one_count();
	auto single_view_zeroes_count        = single_word_view.zero_count();
	auto single_zeroes_view_zeroes_count = single_word_zeroes_view.zero_count();
	REQUIRE(single_view_ones_count == expected_single_ones_count);
	REQUIRE(single_ones_view_ones_count == expected_single_ones_count);
	REQUIRE(single_view_zeroes_count == expected_single_zeroes_count);
	REQUIRE(single_zeroes_view_zeroes_count == expected_single_zeroes_count);

	auto multi_view_ones_count          = multi_word_view.one_count();
	auto multi_ones_view_ones_count     = multi_word_ones_view.one_count();
	auto multi_view_zeroes_count        = multi_word_view.zero_count();
	auto multi_zeroes_view_zeroes_count = multi_word_zeroes_view.zero_count();
	REQUIRE(multi_view_ones_count == expected_multi_ones_count);
	REQUIRE(multi_ones_view_ones_count == expected_multi_ones_view_count);
	REQUIRE(multi_view_zeroes_count == expected_multi_zeroes_count);
	REQUIRE(multi_zeroes_view_zeroes_count == expected_multi_zeroes_view_count);

	SECTION("single")
	{
		SECTION("find")
		{
			auto find_false = bitsy::bit_find(single_word_view.cbegin(), single_word_view.cend(), false);
			auto find_false_ref       = *find_false;
			size_type find_false_diff = std::distance(single_word_view.cbegin(), find_false);
			auto expected_find_false =
			  std::next(single_word_view.cbegin(), expected_single_lsb_zero_bit_index);
			REQUIRE(find_false == expected_find_false);
			REQUIRE(find_false != single_word_view.cend());
			REQUIRE(find_false == single_word_view.cbegin());
			REQUIRE_FALSE(find_false_ref.value());
			REQUIRE(find_false_diff == expected_single_lsb_zero_bit_index);

			auto find_true = bitsy::bit_find(single_word_view.cbegin(), single_word_view.cend(), true);
			auto find_true_ref       = *find_true;
			size_type find_true_diff = std::distance(single_word_view.cbegin(), find_true);
			auto expected_find_true =
			  std::next(single_word_view.cbegin(), expected_single_lsb_one_bit_index);
			REQUIRE(find_true == expected_find_true);
			REQUIRE(find_true != single_word_view.cend());
			REQUIRE(find_true != single_word_view.cbegin());
			REQUIRE(find_true_ref.value());
			REQUIRE(find_true_diff == expected_single_lsb_one_bit_index);
		}
		SECTION("find_first_of")
		{
			auto find_false = bitsy::bit_find_first_of(
			  single_word_view.cbegin(), single_word_view.cend(), il_false.begin(), il_false.end());
			auto find_false_ref       = *find_false;
			size_type find_false_diff = std::distance(single_word_view.cbegin(), find_false);
			auto expected_find_false =
			  std::next(single_word_view.cbegin(), expected_single_lsb_zero_bit_index);
			REQUIRE(find_false == expected_find_false);
			REQUIRE(find_false != single_word_view.cend());
			REQUIRE(find_false == single_word_view.cbegin());
			REQUIRE_FALSE(find_false_ref.value());
			REQUIRE(find_false_diff == expected_single_lsb_zero_bit_index);

			auto find_true = bitsy::bit_find_first_of(
			  single_word_view.cbegin(), single_word_view.cend(), il_true.begin(), il_true.end());
			auto find_true_ref       = *find_true;
			size_type find_true_diff = std::distance(single_word_view.cbegin(), find_true);
			auto expected_find_true =
			  std::next(single_word_view.cbegin(), expected_single_lsb_one_bit_index);
			REQUIRE(find_true == expected_find_true);
			REQUIRE(find_true != single_word_view.cend());
			REQUIRE(find_true != single_word_view.cbegin());
			REQUIRE(find_true_ref.value());
			REQUIRE(find_true_diff == expected_single_lsb_one_bit_index);

			auto find_all = bitsy::bit_find_first_of(single_word_view.cbegin(), single_word_view.cend(),
			  il_true_false.begin(), il_true_false.end());
			auto find_all_ref       = *find_all;
			size_type find_all_diff = std::distance(single_word_view.cbegin(), find_all);
			auto expected_find_all =
			  std::next(single_word_view.cbegin(), expected_single_lsb_zero_bit_index);
			REQUIRE(find_all == expected_find_all);
			REQUIRE(find_all != single_word_view.cend());
			REQUIRE(find_all == single_word_view.cbegin());
			REQUIRE_FALSE(find_all_ref.value());
			REQUIRE(find_all_diff == expected_single_lsb_zero_bit_index);
		}
		SECTION("count")
		{
			size_type count_true =
			  bitsy::bit_count(single_word_view.cbegin(), single_word_view.cend(), true);
			size_type count_false =
			  bitsy::bit_count(single_word_view.cbegin(), single_word_view.cend(), false);
			size_type count_zeroes_true =
			  bitsy::bit_count(single_word_zeroes_view.cbegin(), single_word_zeroes_view.cend(), true);
			size_type count_zeroes_false =
			  bitsy::bit_count(single_word_zeroes_view.cbegin(), single_word_zeroes_view.cend(), false);
			size_type count_ones_true =
			  bitsy::bit_count(single_word_ones_view.cbegin(), single_word_ones_view.cend(), true);
			size_type count_ones_false =
			  bitsy::bit_count(single_word_ones_view.cbegin(), single_word_ones_view.cend(), false);
			REQUIRE(count_true == expected_single_ones_count);
			REQUIRE(count_false == expected_single_zeroes_count);
			REQUIRE(count_zeroes_true == 0);
			REQUIRE(count_zeroes_false == expected_single_zeroes_count);
			REQUIRE(count_ones_true == expected_single_ones_count);
			REQUIRE(count_ones_false == 0);
		}
		SECTION("is_sorted")
		{
			bool is_sorted = bitsy::bit_is_sorted(single_word_view.cbegin(), single_word_view.cend());
			REQUIRE(is_sorted);

			bool is_sorted_ones =
			  bitsy::bit_is_sorted(single_word_ones_view.cbegin(), single_word_ones_view.cend());
			REQUIRE(is_sorted_ones);

			auto is_sorted_until =
			  bitsy::bit_is_sorted_until(single_word_view.cbegin(), single_word_view.cend());
			size_type is_sorted_until_diff = std::distance(single_word_view.cbegin(), is_sorted_until);
			REQUIRE(is_sorted_until == single_word_view.cend());
			REQUIRE(is_sorted_until_diff == single_word_view.size());

			auto is_sorted_until_ones =
			  bitsy::bit_is_sorted_until(single_word_ones_view.cbegin(), single_word_ones_view.cend());
			size_type is_sorted_until_ones_diff =
			  std::distance(single_word_ones_view.cbegin(), is_sorted_until_ones);
			REQUIRE(is_sorted_until == single_word_ones_view.cend());
			REQUIRE(is_sorted_until_ones_diff == single_word_ones_view.size());
		}
		SECTION("equal-3")
		{
			bool equal = bitsy::bit_equal(
			  single_word_view.cbegin(), single_word_view.cend(), single_word_view.cbegin());
			REQUIRE(equal);

			bool equal_truncated = bitsy::bit_equal(single_word_view.cbegin(),
			  std::next(single_word_view.cbegin(), 4), single_word_view.cbegin());
			REQUIRE(equal_truncated);

			bool equal_empty = bitsy::bit_equal(
			  single_word_view.cbegin(), single_word_view.cbegin(), single_word_view.cend());
			REQUIRE(equal_empty);

			bool equal_first_skewed = bitsy::bit_equal(
			  single_word_ones_view.cbegin(), single_word_ones_view.cend(), single_word_view.cbegin());
			REQUIRE_FALSE(equal_first_skewed);

			bool equal_second_skewed =
			  bitsy::bit_equal(single_word_view.cbegin(), std::next(single_word_view.cbegin(), 4),
			    std::next(single_word_view.cbegin(), expected_single_lsb_one_bit_index));
			REQUIRE_FALSE(equal_second_skewed);
		}
		SECTION("equal-4")
		{
			bool equal = bitsy::bit_equal(single_word_view.cbegin(), single_word_view.cend(),
			  single_word_view.cbegin(), single_word_view.cend());
			REQUIRE(equal);

			bool equal_truncated = bitsy::bit_equal(single_word_view.cbegin(), single_word_view.cend(),
			  single_word_view.cbegin(), std::next(single_word_view.cbegin(), 4));
			REQUIRE_FALSE(equal_truncated);

			bool equal_first_skewed = bitsy::bit_equal(single_word_ones_view.cbegin(),
			  single_word_ones_view.cend(), single_word_view.cbegin(), single_word_view.cend());
			REQUIRE_FALSE(equal_first_skewed);

			bool equal_second_skewed = bitsy::bit_equal(single_word_view.cbegin(),
			  single_word_view.cend(), single_word_ones_view.cbegin(), single_word_ones_view.cend());
			REQUIRE_FALSE(equal_second_skewed);

			bool equal_first_range_empty = bitsy::bit_equal(single_word_view.cbegin(),
			  single_word_view.cbegin(), single_word_view.cbegin(), single_word_view.cend());
			REQUIRE_FALSE(equal_first_range_empty);

			bool equal_second_range_empty = bitsy::bit_equal(single_word_view.cbegin(),
			  single_word_view.cend(), single_word_view.cend(), single_word_view.cend());
			REQUIRE_FALSE(equal_second_range_empty);

			bool equal_all_empty = bitsy::bit_equal(single_word_ones_view.cend(),
			  single_word_ones_view.cend(), single_word_view.cend(), single_word_view.cend());
			REQUIRE(equal_all_empty);
		}
		SECTION("lexicograhic_compare")
		{
			bool lexicocgraphic_compare = bitsy::bit_lexicographical_compare(single_word_view.cbegin(),
			  single_word_view.cend(), single_word_view.cbegin(), single_word_view.cend());
			REQUIRE_FALSE(lexicocgraphic_compare);

			bool lexicocgraphic_compare_first_ones =
			  bitsy::bit_lexicographical_compare(single_word_ones_view.cbegin(),
			    single_word_ones_view.cend(), single_word_view.cbegin(), single_word_view.cend());
			REQUIRE_FALSE(lexicocgraphic_compare_first_ones);

			bool lexicocgraphic_compare_second_ones =
			  bitsy::bit_lexicographical_compare(single_word_view.cbegin(), single_word_view.cend(),
			    single_word_ones_view.cbegin(), single_word_ones_view.cend());
			REQUIRE(lexicocgraphic_compare_second_ones);
		}
	}
	SECTION("multi")
	{
		SECTION("find")
		{
			auto find_false = bitsy::bit_find(multi_word_view.cbegin(), multi_word_view.cend(), false);
			auto find_false_ref       = *find_false;
			size_type find_false_diff = std::distance(multi_word_view.cbegin(), find_false);
			auto expected_find_false =
			  std::next(multi_word_view.cbegin(), expected_multi_lsb_zero_bit_index);
			REQUIRE(find_false == expected_find_false);
			REQUIRE(find_false != multi_word_view.cend());
			REQUIRE(find_false == multi_word_view.cbegin());
			REQUIRE_FALSE(find_false_ref.value());
			REQUIRE(find_false_diff == expected_multi_lsb_zero_bit_index);

			auto find_true     = bitsy::bit_find(multi_word_view.cbegin(), multi_word_view.cend(), true);
			auto find_true_ref = *find_true;
			size_type find_true_diff = std::distance(multi_word_view.cbegin(), find_true);
			auto expected_find_true =
			  std::next(multi_word_view.cbegin(), expected_multi_lsb_one_bit_index);
			REQUIRE(find_true == expected_find_true);
			REQUIRE(find_true != multi_word_view.cend());
			REQUIRE(find_true != multi_word_view.cbegin());
			REQUIRE(find_true_ref.value());
			REQUIRE(find_true_diff == expected_multi_lsb_one_bit_index);
		}
		SECTION("find_first_of")
		{
			auto find_false = bitsy::bit_find_first_of(
			  multi_word_view.cbegin(), multi_word_view.cend(), il_false.begin(), il_false.end());
			auto find_false_ref       = *find_false;
			size_type find_false_diff = std::distance(multi_word_view.cbegin(), find_false);
			auto expected_find_false =
			  std::next(multi_word_view.cbegin(), expected_multi_lsb_zero_bit_index);
			REQUIRE(find_false == expected_find_false);
			REQUIRE(find_false != multi_word_view.cend());
			REQUIRE(find_false == multi_word_view.cbegin());
			REQUIRE_FALSE(find_false_ref.value());
			REQUIRE(find_false_diff == expected_multi_lsb_zero_bit_index);

			auto find_true = bitsy::bit_find_first_of(
			  multi_word_view.cbegin(), multi_word_view.cend(), il_true.begin(), il_true.end());
			auto find_true_ref       = *find_true;
			size_type find_true_diff = std::distance(multi_word_view.cbegin(), find_true);
			auto expected_find_true =
			  std::next(multi_word_view.cbegin(), expected_multi_lsb_one_bit_index);
			REQUIRE(find_true == expected_find_true);
			REQUIRE(find_true != multi_word_view.cend());
			REQUIRE(find_true != multi_word_view.cbegin());
			REQUIRE(find_true_ref.value());
			REQUIRE(find_true_diff == expected_multi_lsb_one_bit_index);

			auto find_all     = bitsy::bit_find_first_of(multi_word_view.cbegin(), multi_word_view.cend(),
        il_true_false.begin(), il_true_false.end());
			auto find_all_ref = *find_all;
			size_type find_all_diff = std::distance(multi_word_view.cbegin(), find_all);
			auto expected_find_all =
			  std::next(multi_word_view.cbegin(), expected_multi_lsb_zero_bit_index);
			REQUIRE(find_all == expected_find_all);
			REQUIRE(find_all != multi_word_view.cend());
			REQUIRE(find_all == multi_word_view.cbegin());
			REQUIRE_FALSE(find_all_ref.value());
			REQUIRE(find_all_diff == expected_multi_lsb_zero_bit_index);
		}
		SECTION("count")
		{
			size_type count_true =
			  bitsy::bit_count(multi_word_view.cbegin(), multi_word_view.cend(), true);
			size_type count_false =
			  bitsy::bit_count(multi_word_view.cbegin(), multi_word_view.cend(), false);
			size_type count_zeroes_true =
			  bitsy::bit_count(multi_word_zeroes_view.cbegin(), multi_word_zeroes_view.cend(), true);
			size_type count_zeroes_false =
			  bitsy::bit_count(multi_word_zeroes_view.cbegin(), multi_word_zeroes_view.cend(), false);
			size_type count_ones_true =
			  bitsy::bit_count(multi_word_ones_view.cbegin(), multi_word_ones_view.cend(), true);
			size_type count_ones_false =
			  bitsy::bit_count(multi_word_ones_view.cbegin(), multi_word_ones_view.cend(), false);
			REQUIRE(count_true == expected_multi_ones_count);
			REQUIRE(count_false == expected_multi_zeroes_count);
			REQUIRE(count_zeroes_true == 0);
			REQUIRE(count_zeroes_false == expected_multi_zeroes_view_count);
			REQUIRE(count_ones_true == expected_multi_ones_view_count);
			REQUIRE(count_ones_false == 0);
		}
		SECTION("is_sorted")
		{
			bool is_sorted = bitsy::bit_is_sorted(multi_word_view.cbegin(), multi_word_view.cend());
			REQUIRE_FALSE(is_sorted);

			bool is_sorted_ones =
			  bitsy::bit_is_sorted(multi_word_ones_view.cbegin(), multi_word_ones_view.cend());
			REQUIRE(is_sorted_ones);

			bool is_sorted_zeroes =
			  bitsy::bit_is_sorted(multi_word_zeroes_view.cbegin(), multi_word_zeroes_view.cend());
			REQUIRE(is_sorted_zeroes);

			auto is_sorted_until =
			  bitsy::bit_is_sorted_until(multi_word_view.cbegin(), multi_word_view.cend());
			size_type is_sorted_until_diff = std::distance(multi_word_view.cbegin(), is_sorted_until);
			REQUIRE(is_sorted_until != multi_word_view.cend());
			size_type expected_is_sorted_until_diff =
			  multi_word_zeroes_view.size() + multi_word_ones_view.size();
			REQUIRE(is_sorted_until_diff == expected_is_sorted_until_diff);

			auto is_sorted_until_ones =
			  bitsy::bit_is_sorted_until(multi_word_ones_view.cbegin(), multi_word_ones_view.cend());
			size_type is_sorted_until_ones_diff =
			  std::distance(multi_word_ones_view.cbegin(), is_sorted_until_ones);
			REQUIRE(is_sorted_until == multi_word_ones_view.cend());
			REQUIRE(is_sorted_until_ones_diff == multi_word_ones_view.size());
		}
		SECTION("equal-3")
		{
			bool equal = bitsy::bit_equal(
			  multi_word_view.cbegin(), multi_word_view.cend(), multi_word_view.cbegin());
			REQUIRE(equal);

			bool equal_truncated = bitsy::bit_equal(
			  multi_word_view.cbegin(), std::next(multi_word_view.cbegin(), 4), multi_word_view.cbegin());
			REQUIRE(equal_truncated);

			bool equal_empty = bitsy::bit_equal(
			  multi_word_view.cbegin(), multi_word_view.cbegin(), multi_word_view.cend());
			REQUIRE(equal_empty);

			bool equal_first_skewed = bitsy::bit_equal(
			  multi_word_ones_view.cbegin(), multi_word_ones_view.cend(), multi_word_view.cbegin());
			REQUIRE_FALSE(equal_first_skewed);

			bool equal_second_skewed =
			  bitsy::bit_equal(multi_word_view.cbegin(), std::next(multi_word_view.cbegin(), 4),
			    std::next(multi_word_view.cbegin(), expected_multi_lsb_one_bit_index));
			REQUIRE_FALSE(equal_second_skewed);
		}
		SECTION("equal-4")
		{
			bool equal = bitsy::bit_equal(multi_word_view.cbegin(), multi_word_view.cend(),
			  multi_word_view.cbegin(), multi_word_view.cend());
			REQUIRE(equal);

			bool equal_truncated = bitsy::bit_equal(multi_word_view.cbegin(), multi_word_view.cend(),
			  multi_word_view.cbegin(), std::next(multi_word_view.cbegin(), 4));
			REQUIRE_FALSE(equal_truncated);

			bool equal_first_skewed = bitsy::bit_equal(multi_word_ones_view.cbegin(),
			  multi_word_ones_view.cend(), multi_word_view.cbegin(), multi_word_view.cend());
			REQUIRE_FALSE(equal_first_skewed);

			bool equal_second_skewed = bitsy::bit_equal(multi_word_view.cbegin(), multi_word_view.cend(),
			  multi_word_ones_view.cbegin(), multi_word_ones_view.cend());
			REQUIRE_FALSE(equal_second_skewed);

			bool equal_first_range_empty = bitsy::bit_equal(multi_word_view.cbegin(),
			  multi_word_view.cbegin(), multi_word_view.cbegin(), multi_word_view.cend());
			REQUIRE_FALSE(equal_first_range_empty);

			bool equal_second_range_empty = bitsy::bit_equal(multi_word_view.cbegin(),
			  multi_word_view.cend(), multi_word_view.cend(), multi_word_view.cend());
			REQUIRE_FALSE(equal_second_range_empty);

			bool equal_all_empty = bitsy::bit_equal(multi_word_ones_view.cend(),
			  multi_word_ones_view.cend(), multi_word_view.cend(), multi_word_view.cend());
			REQUIRE(equal_all_empty);
		}
		SECTION("lexicograhic_compare")
		{
			bool lexicocgraphic_compare = bitsy::bit_lexicographical_compare(multi_word_view.cbegin(),
			  multi_word_view.cend(), multi_word_view.cbegin(), multi_word_view.cend());
			REQUIRE_FALSE(lexicocgraphic_compare);

			bool lexicocgraphic_compare_first_ones =
			  bitsy::bit_lexicographical_compare(multi_word_ones_view.cbegin(),
			    multi_word_ones_view.cend(), multi_word_view.cbegin(), multi_word_view.cend());
			REQUIRE_FALSE(lexicocgraphic_compare_first_ones);

			bool lexicocgraphic_compare_second_ones =
			  bitsy::bit_lexicographical_compare(multi_word_view.cbegin(), multi_word_view.cend(),
			    multi_word_ones_view.cbegin(), multi_word_ones_view.cend());
			REQUIRE(lexicocgraphic_compare_second_ones);
		}
	}
}
