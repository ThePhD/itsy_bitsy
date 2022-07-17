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

#include <itsy/bitsy.hpp>

#include <ztd/idk/span.hpp>
#include <ztd/ranges/subrange.hpp>

#include <vector>

template<typename TestType>
constexpr bool
is_even_respecting_boundaries(std::size_t i) noexcept
{
	std::size_t modulo = i % bitsy::binary_digits_v<TestType>;
	return (modulo % 2) == 0;
}

template<typename TestType, typename BitSequence>
void
bit_sequence_insert_erase_test(BitSequence& bs)
{
	const std::size_t original_size    = bs.size();
	const std::size_t pre_insert_size  = original_size + 2;
	const std::size_t post_insert_size = pre_insert_size + bitsy::binary_digits_v<TestType>;

	REQUIRE(original_size == 0);
	REQUIRE(bs.empty());
	REQUIRE(bs.size() == 0);
	REQUIRE(bs.cbegin() == bs.cend());
	REQUIRE(bs.begin() == bs.end());
	REQUIRE_FALSE(bs.cbegin() != bs.cend());
	REQUIRE_FALSE(bs.begin() != bs.end());
	bs.assign(2, false);

	REQUIRE(bs.size() == pre_insert_size);
	{
		auto bs_it = bs.begin();
		REQUIRE(*bs_it == bitsy::bit0);
		++bs_it;
		REQUIRE(*bs_it == bitsy::bit0);
		++bs_it;
		REQUIRE(bs_it == bs.cend());
	}

	for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
		{
			auto it  = bs.insert(++bs.cbegin(), true);
			bool val = *it;
			REQUIRE(val);
		}

	REQUIRE_FALSE(bs.empty());
	REQUIRE(bs.size() == post_insert_size);
	REQUIRE_FALSE(bs.cbegin() == bs.cend());
	REQUIRE_FALSE(bs.begin() == bs.end());
	REQUIRE(bs.cbegin() != bs.cend());
	REQUIRE(bs.begin() != bs.end());

	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool value = bs[i];
			if (i == 0 || i == (1 + bitsy::binary_digits_v<TestType>))
				{
					REQUIRE_FALSE(value);
				}
			else
				{
					REQUIRE(value);
				}
		}

	for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
		{
			auto target = bs.cbegin();
			std::advance(target, 1);
			auto it                   = bs.erase(target);
			const bool val            = *it;
			const bool expected_val   = (i < (bitsy::binary_digits_v<TestType> - 1));
			std::size_t size          = bs.size();
			std::size_t expected_size = static_cast<std::size_t>(post_insert_size - i - 1);
			REQUIRE(val == expected_val);
			REQUIRE(size == expected_size);
		}

	REQUIRE(bs.size() == pre_insert_size);
	REQUIRE_FALSE(bs.empty());
	REQUIRE_FALSE(bs.cbegin() == bs.cend());
	REQUIRE_FALSE(bs.begin() == bs.end());
	REQUIRE(bs.cbegin() != bs.cend());
	REQUIRE(bs.begin() != bs.end());

	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool value = bs[i];
			REQUIRE_FALSE(value);
		}

	bs.clear();

	REQUIRE(bs.size() == 0);
	REQUIRE(bs.empty());
	REQUIRE(bs.cbegin() == bs.cend());
	REQUIRE(bs.begin() == bs.end());
	REQUIRE_FALSE(bs.cbegin() != bs.cend());
	REQUIRE_FALSE(bs.begin() != bs.end());
}

template<typename TestType, typename BitSequence>
void
bit_sequence_insert_test_bulk_small(BitSequence& bs)
{
	using value_type = typename BitSequence::value_type;
	REQUIRE(bs.empty());
	REQUIRE(bs.size() == 0);

	std::initializer_list<value_type> il0        = { false, true, false, true, false };
	auto insert_it0                              = bs.insert(bs.cbegin(), il0);
	auto expected_insert_it0                     = bs.begin();
	const std::size_t post_insert0_size          = bs.size();
	const std::size_t expected_post_insert0_size = il0.size();
	REQUIRE(insert_it0 == expected_insert_it0);
	REQUIRE(post_insert0_size == expected_post_insert0_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			const bool val          = bs[i];
			const bool expected_val = ((i % 2) == 1);
			REQUIRE(val == expected_val);
		}

	std::initializer_list<value_type> il1        = { true, false };
	auto insert_it1                              = bs.insert(std::next(bs.cbegin(), 5), il1);
	auto expected_insert_it1                     = std::next(bs.begin(), 5);
	const std::size_t post_insert1_size          = bs.size();
	const std::size_t expected_post_insert1_size = il1.size() + expected_post_insert0_size;
	REQUIRE(insert_it1 == expected_insert_it1);
	REQUIRE(post_insert1_size == expected_post_insert1_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			const bool val          = bs[i];
			const bool expected_val = ((i % 2) == 1);
			REQUIRE(val == expected_val);
		}

	std::initializer_list<value_type> il2 = { true, false, true, false, true, false, true, false, true, false, true,
		false };
	auto insert_it2                       = bs.insert(std::next(bs.cbegin(), 3), il2);
	auto expected_insert_it2              = std::next(bs.cbegin(), 3);
	const std::size_t post_insert2_size   = bs.size();
	const std::size_t expected_post_insert2_size = il2.size() + expected_post_insert1_size;
	REQUIRE(insert_it2 == expected_insert_it2);
	REQUIRE(post_insert2_size == expected_post_insert2_size);
	{
		auto bsstart = bs.cbegin();
		auto bsend   = bs.cend();
		for (std::size_t i = 0; bsstart != bsend; ++i, ++bsstart)
			{
				const bool val          = *bsstart;
				const bool expected_val = ((i % 2) == 1);
				REQUIRE(val == expected_val);
			}
	}

	std::initializer_list<value_type> empty_il = {};
	const std::size_t pre_insert3_size         = bs.size();
	auto insert_it3                            = bs.insert(std::next(bs.cbegin(), 3), empty_il);
	auto expected_insert_it3                   = std::next(bs.cbegin(), 3);
	const std::size_t post_insert3_size        = bs.size();
	const std::size_t expected_insert3_size    = empty_il.size() + expected_post_insert2_size;
	REQUIRE(insert_it3 == expected_insert_it3);
	REQUIRE(bs.size() == pre_insert3_size);
	REQUIRE(bs.size() == post_insert3_size);
	REQUIRE(pre_insert3_size == expected_insert3_size);
	REQUIRE(post_insert3_size == expected_insert3_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val                = bs[i];
			const bool expected_val = ((i % 2) == 1);
			REQUIRE(val == expected_val);
		}

	// Sized insert of size 0
	const std::size_t pre_insert4_size      = bs.size();
	auto insert_it4                         = bs.insert(std::next(bs.cbegin(), 3), 0, true);
	auto expected_insert_it4                = std::next(bs.cbegin(), 3);
	const std::size_t post_insert4_size     = bs.size();
	const std::size_t expected_insert4_size = expected_insert3_size;
	REQUIRE(insert_it4 == expected_insert_it4);
	REQUIRE(bs.size() == pre_insert4_size);
	REQUIRE(bs.size() == post_insert4_size);
	REQUIRE(pre_insert4_size == expected_insert4_size);
	REQUIRE(post_insert4_size == expected_insert4_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val                = bs[i];
			const bool expected_val = ((i % 2) == 1);
			REQUIRE(val == expected_val);
		}

	// Sized insert with value
	const std::size_t pre_insert5_size           = bs.size();
	auto insert_it5                              = bs.insert(bs.cend(), 5, true);
	auto expected_insert_it5                     = std::next(bs.cbegin(), expected_insert4_size);
	const std::size_t post_insert5_size          = bs.size();
	const std::size_t expected_post_insert5_size = 5 + expected_insert4_size;
	REQUIRE(insert_it5 == expected_insert_it5);
	REQUIRE(bs.size() == post_insert5_size);
	REQUIRE(pre_insert5_size == expected_insert4_size);
	REQUIRE(post_insert5_size == expected_post_insert5_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val                = bs[i];
			const bool expected_val = (i < pre_insert5_size) ? ((i % 2) == 1) : true;
			REQUIRE(val == expected_val);
		}
}

template<typename TestType, typename BitSequence>
void
bit_sequence_insert_erase_test_bulk_small(BitSequence& bs)
{
	REQUIRE(bs.empty());
	REQUIRE(bs.size() == 0);

	auto insert_it0          = bs.insert(bs.cbegin(), { false, true, false, true, false });
	auto expected_insert_it0 = bs.begin();
	REQUIRE(insert_it0 == expected_insert_it0);
	REQUIRE(bs.size() == 5);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			REQUIRE(val == ((i % 2) == 1));
		}

	auto insert_it1          = bs.insert(std::next(bs.cbegin(), 5), { true, false });
	auto expected_insert_it1 = std::next(bs.begin(), 5);
	REQUIRE(insert_it1 == expected_insert_it1);
	REQUIRE(bs.size() == 7);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			REQUIRE(val == ((i % 2) == 1));
		}

	auto erase_it0          = bs.erase(bs.cend() - 3, bs.cend());
	auto expected_erase_it0 = bs.cend();
	REQUIRE(erase_it0 == expected_erase_it0);
	REQUIRE(bs.size() == 4);
	REQUIRE_FALSE(bs.empty());

	bool val0 = bs[0];
	bool val1 = bs[1];
	bool val2 = bs[2];
	bool val3 = bs[3];
	REQUIRE_FALSE(val0);
	REQUIRE(val1);
	REQUIRE_FALSE(val2);
	REQUIRE(val3);

	auto erase_it1          = bs.erase(bs.cbegin(), bs.cbegin() + 4);
	auto expected_erase_it1 = bs.end();
	REQUIRE(erase_it1 == expected_erase_it1);
	REQUIRE(erase_it1 == bs.cbegin());
	REQUIRE(erase_it1 == bs.cend());
	REQUIRE(bs.size() == 0);
	REQUIRE(bs.empty());
}

template<typename TestType, typename BitSequence>
void
bit_sequence_insert_erase_test_bulk_large(BitSequence& bs)
{
	REQUIRE(bs.empty());
	REQUIRE(bs.size() == 0);

	const std::size_t full_binary_bits = bitsy::binary_digits_v<TestType>;
	const std::size_t high_half_binary_bits =
	     (bitsy::binary_digits_v<TestType> / 2) + static_cast<std::size_t>(std::is_signed_v<TestType>);
	const std::size_t low_half_binary_bits = (bitsy::binary_digits_v<TestType> / 2);

	std::vector<TestType> insertion_storage(15, static_cast<TestType>(0));
	bitsy::bit_view<::ztd::span<TestType>> insertion_view(insertion_storage);
	{
		auto start  = insertion_view.begin();
		auto finish = insertion_view.end();
		for (std::size_t i = 0; start != finish; ++start, ++i)
			{
				*start = is_even_respecting_boundaries<TestType>(i);
			}
	}

	auto it_post_insertion      = bs.insert(bs.cbegin(), insertion_view.begin(), insertion_view.end());
	auto it_post_insertion_dist = std::distance(bs.begin(), it_post_insertion);
	REQUIRE(it_post_insertion_dist == 0);
	const std::size_t post_insertion_size          = bs.size();
	const std::size_t expected_post_insertion_size = insertion_view.size();
	REQUIRE(post_insertion_size == expected_post_insertion_size);
	{
		auto start    = insertion_view.begin();
		auto finish   = insertion_view.end();
		auto bsstart  = bs.begin();
		auto bsfinish = bs.end();
		for (std::size_t i = 0; start != finish; ++i, ++bsstart, ++start)
			{
				bool expected = is_even_respecting_boundaries<TestType>(i);
				bool iv_val   = *start;
				bool bs_val   = *bsstart;
				REQUIRE(expected == iv_val);
				REQUIRE(expected == bs_val);
				REQUIRE(bs_val == iv_val);
			}
		REQUIRE(bsstart == bsfinish);
	}

	auto it_post_erase0      = bs.erase(bs.begin(), bs.begin() + full_binary_bits);
	auto it_post_erase0_dist = std::distance(bs.begin(), it_post_erase0);
	REQUIRE(it_post_erase0_dist == 0);
	const std::size_t post_erase_size0          = bs.size();
	const std::size_t expected_post_erase_size0 = (post_insertion_size - full_binary_bits);
	REQUIRE(post_erase_size0 == expected_post_erase_size0);
	{
		auto bsstart  = bs.cbegin();
		auto bsfinish = bs.cend();
		for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
			{
				bool expected = is_even_respecting_boundaries<TestType>(i);
				bool bs_val   = *bsstart;
				REQUIRE(expected == bs_val);
			}
	}

	auto it_post_erase1      = bs.erase(bs.begin(), bs.begin() + (full_binary_bits * 3));
	auto it_post_erase1_dist = std::distance(bs.begin(), it_post_erase1);
	REQUIRE(it_post_erase1_dist == 0);
	const std::size_t post_erase_size1          = bs.size();
	const std::size_t expected_post_erase_size1 = (post_erase_size0 - full_binary_bits * 3);
	REQUIRE(post_erase_size1 == expected_post_erase_size1);
	{
		auto bsstart  = bs.cbegin();
		auto bsfinish = bs.cend();
		for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
			{
				bool expected = is_even_respecting_boundaries<TestType>(i);
				bool bs_val   = *bsstart;
				REQUIRE(expected == bs_val);
			}
	}

	auto it_post_erase2      = bs.erase(bs.begin() + 1, bs.begin() + high_half_binary_bits + 1);
	auto it_post_erase2_dist = std::distance(bs.begin(), it_post_erase2);
	REQUIRE(it_post_erase2_dist == 1);
	const std::size_t post_erase_size2          = bs.size();
	const std::size_t expected_post_erase_size2 = (post_erase_size1 - high_half_binary_bits);
	REQUIRE(post_erase_size2 == expected_post_erase_size2);
	if constexpr (!std::is_signed_v<TestType>)
		{
			auto bsstart  = bs.cbegin();
			auto bsfinish = bs.cend();
			for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
				{
					bool expected = is_even_respecting_boundaries<TestType>(i);
					bool bs_val   = *bsstart;
					REQUIRE(expected == bs_val);
				}
		}

	auto it_post_erase3      = bs.erase(bs.begin() + 1, bs.begin() + (full_binary_bits + low_half_binary_bits) + 1);
	auto it_post_erase3_dist = std::distance(bs.begin(), it_post_erase3);
	REQUIRE(it_post_erase3_dist == 1);
	const std::size_t post_erase_size3          = bs.size();
	const std::size_t expected_post_erase_size3 = (post_erase_size2 - (full_binary_bits + low_half_binary_bits));
	REQUIRE(post_erase_size3 == expected_post_erase_size3);
	{
		auto bsstart  = bs.cbegin();
		auto bsfinish = bs.cend();
		for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
			{
				bool expected = is_even_respecting_boundaries<TestType>(i);
				bool bs_val   = *bsstart;
				REQUIRE(expected == bs_val);
			}
	}

	auto it_post_erase4      = bs.erase(bs.begin(), bs.begin() + 3);
	auto it_post_erase4_dist = std::distance(bs.begin(), it_post_erase4);
	REQUIRE(it_post_erase4_dist == 0);
	const std::size_t post_erase_size4          = bs.size();
	const std::size_t expected_post_erase_size4 = (post_erase_size3 - 3);
	REQUIRE(post_erase_size4 == expected_post_erase_size4);
	if constexpr (!std::is_signed_v<TestType>)
		{
			auto bsstart  = bs.cbegin();
			auto bsfinish = bs.cend();
			for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
				{
					bool expected = !is_even_respecting_boundaries<TestType>(i);
					bool bs_val   = *bsstart;
					REQUIRE(expected == bs_val);
				}
		}

	auto it_post_erase5      = bs.erase(bs.begin(), bs.begin() + 1);
	auto it_post_erase5_dist = std::distance(bs.begin(), it_post_erase5);
	REQUIRE(it_post_erase5_dist == 0);
	const std::size_t post_erase_size5          = bs.size();
	const std::size_t expected_post_erase_size5 = (post_erase_size4 - 1);
	REQUIRE(post_erase_size5 == expected_post_erase_size5);
	if constexpr (!std::is_signed_v<TestType>)
		{
			auto bsstart  = bs.cbegin();
			auto bsfinish = bs.cend();
			for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
				{
					bool expected = is_even_respecting_boundaries<TestType>(i);
					bool bs_val   = *bsstart;
					REQUIRE(expected == bs_val);
				}
		}

	auto it_post_erase6      = bs.erase(bs.begin(), bs.begin() + 4);
	auto it_post_erase6_dist = std::distance(bs.begin(), it_post_erase6);
	REQUIRE(it_post_erase6_dist == 0);
	const std::size_t post_erase_size6          = bs.size();
	const std::size_t expected_post_erase_size6 = (post_erase_size5 - 4);
	REQUIRE(post_erase_size6 == expected_post_erase_size6);
	if constexpr (!std::is_signed_v<TestType>)
		{
			auto bsstart  = bs.cbegin();
			auto bsfinish = bs.cend();
			for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
				{
					bool expected = is_even_respecting_boundaries<TestType>(i);
					bool bs_val   = *bsstart;
					REQUIRE(expected == bs_val);
				}
		}

	auto it_post_erase7      = bs.erase(bs.cbegin(), bs.cend());
	auto it_post_erase7_dist = std::distance(bs.begin(), it_post_erase7);
	REQUIRE(it_post_erase7_dist == 0);
	const std::size_t post_erase_size7          = bs.size();
	const std::size_t expected_post_erase_size7 = 0;
	REQUIRE(post_erase_size7 == expected_post_erase_size7);
	REQUIRE(it_post_erase7 == bs.cend());
}

template<typename TestType, typename BitSequence>
void
bit_sequence_resize_test_bulk_small(BitSequence& bs)
{
	REQUIRE(bs.empty());
	REQUIRE(bs.size() == 0);

	bs.resize(12);
	REQUIRE(bs.size() == 12);
	REQUIRE(std::none_of(bs.begin(), bs.end(), [](auto val) { return val; }));

	bs.resize(5);
	REQUIRE(bs.size() == 5);
	REQUIRE(std::none_of(bs.begin(), bs.end(), [](auto val) { return val; }));

	bs.resize(13, true);
	REQUIRE(bs.size() == 13);
	auto middle = bs.begin() + 5;
	REQUIRE(std::none_of(bs.begin(), middle, [](auto val) { return val; }));
	REQUIRE(std::all_of(middle, bs.end(), [](auto val) { return val; }));

	bs.resize(2, true);
	REQUIRE(bs.size() == 2);
	REQUIRE(std::none_of(bs.begin(), bs.end(), [](auto val) { return val; }));
}

#endif // ITSY_BITSY_TESTS_SHARED_TESTS_HPP
