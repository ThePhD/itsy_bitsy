// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#pragma once

#ifndef ITSY_BITSY_TESTS_SHARED_TESTS_HPP
#define ITSY_BITSY_TESTS_SHARED_TESTS_HPP

#include <testsuite_hooks.h>

#include <itsy/bit_view.hpp>

#include <span>
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
dynamic_bitset_insert_erase_test(BitSequence& bs)
{
	const std::size_t original_size    = bs.size();
	const std::size_t pre_insert_size  = original_size + 2;
	const std::size_t post_insert_size = pre_insert_size + bitsy::binary_digits_v<TestType>;

	VERIFY(original_size == 0);
	VERIFY(bs.empty());
	VERIFY(bs.size() == 0);
	VERIFY(bs.cbegin() == bs.cend());
	VERIFY(bs.begin() == bs.end());
	VERIFY_FALSE(bs.cbegin() != bs.cend());
	VERIFY_FALSE(bs.begin() != bs.end());
	bs.push_back(false);
	bs.push_back(false);

	VERIFY(bs.size() == pre_insert_size);

	for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
		{
			auto it  = bs.insert(++bs.cbegin(), true);
			bool val = *it;
			VERIFY(val);
		}

	VERIFY_FALSE(bs.empty());
	VERIFY(bs.size() == post_insert_size);
	VERIFY_FALSE(bs.cbegin() == bs.cend());
	VERIFY_FALSE(bs.begin() == bs.end());
	VERIFY(bs.cbegin() != bs.cend());
	VERIFY(bs.begin() != bs.end());

	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool value = bs[i];
			if (i == 0 || i == (1 + bitsy::binary_digits_v<TestType>))
				{
					VERIFY_FALSE(value);
				}
			else
				{
					VERIFY(value);
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
			VERIFY(val == expected_val);
			VERIFY(size == expected_size);
		}

	VERIFY(bs.size() == pre_insert_size);
	VERIFY_FALSE(bs.empty());
	VERIFY_FALSE(bs.cbegin() == bs.cend());
	VERIFY_FALSE(bs.begin() == bs.end());
	VERIFY(bs.cbegin() != bs.cend());
	VERIFY(bs.begin() != bs.end());

	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool value = bs[i];
			VERIFY_FALSE(value);
		}

	bs.clear();

	VERIFY(bs.size() == 0);
	VERIFY(bs.empty());
	VERIFY(bs.cbegin() == bs.cend());
	VERIFY(bs.begin() == bs.end());
	VERIFY_FALSE(bs.cbegin() != bs.cend());
	VERIFY_FALSE(bs.begin() != bs.end());
}

template<typename TestType, typename BitSequence>
void
dynamic_bitset_insert_test_bulk_small(BitSequence& bs)
{
	using value_type = typename BitSequence::value_type;
	VERIFY(bs.empty());
	VERIFY(bs.size() == 0);

	std::initializer_list<value_type> il0        = { false, true, false, true, false };
	auto insert_it0                              = bs.insert(bs.cbegin(), il0);
	auto expected_insert_it0                     = bs.begin();
	const std::size_t post_insert0_size          = bs.size();
	const std::size_t expected_post_insert0_size = il0.size();
	VERIFY(insert_it0 == expected_insert_it0);
	VERIFY(post_insert0_size == expected_post_insert0_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			VERIFY(val == ((i % 2) == 1));
		}

	std::initializer_list<value_type> il1        = { true, false };
	auto insert_it1                              = bs.insert(std::next(bs.cbegin(), 5), il1);
	auto expected_insert_it1                     = std::next(bs.begin(), 5);
	const std::size_t post_insert1_size          = bs.size();
	const std::size_t expected_post_insert1_size = il1.size() + expected_post_insert0_size;
	VERIFY(insert_it1 == expected_insert_it1);
	VERIFY(post_insert1_size == expected_post_insert1_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			VERIFY(val == ((i % 2) == 1));
		}

	std::initializer_list<value_type> il2 = { true, false, true, false, true, false, true, false,
		true, false, true, false };
	auto insert_it2                       = bs.insert(std::next(bs.cbegin(), 3), il2);
	auto expected_insert_it2              = std::next(bs.cbegin(), 3);
	const std::size_t post_insert2_size   = bs.size();
	const std::size_t expected_post_insert2_size = il2.size() + expected_post_insert1_size;
	VERIFY(insert_it2 == expected_insert_it2);
	VERIFY(post_insert2_size == expected_post_insert2_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			VERIFY(val == ((i % 2) == 1));
		}

	std::initializer_list<value_type> empty_il = {};
	const std::size_t pre_insert3_size         = bs.size();
	auto insert_it3                            = bs.insert(std::next(bs.cbegin(), 3), empty_il);
	auto expected_insert_it3                   = std::next(bs.cbegin(), 3);
	const std::size_t post_insert3_size        = bs.size();
	const std::size_t expected_insert3_size    = empty_il.size() + expected_post_insert2_size;
	VERIFY(insert_it3 == expected_insert_it3);
	VERIFY(bs.size() == pre_insert3_size);
	VERIFY(bs.size() == post_insert3_size);
	VERIFY(pre_insert3_size == expected_insert3_size);
	VERIFY(post_insert3_size == expected_insert3_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			VERIFY(val == ((i % 2) == 1));
		}
}

template<typename TestType, typename BitSequence>
void
dynamic_bitset_insert_erase_test_bulk_small(BitSequence& bs)
{
	VERIFY(bs.empty());
	VERIFY(bs.size() == 0);

	auto insert_it0          = bs.insert(bs.cbegin(), { false, true, false, true, false });
	auto expected_insert_it0 = bs.begin();
	VERIFY(insert_it0 == expected_insert_it0);
	VERIFY(bs.size() == 5);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			VERIFY(val == ((i % 2) == 1));
		}

	auto insert_it1          = bs.insert(std::next(bs.cbegin(), 5), { true, false });
	auto expected_insert_it1 = std::next(bs.begin(), 5);
	VERIFY(insert_it1 == expected_insert_it1);
	VERIFY(bs.size() == 7);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			VERIFY(val == ((i % 2) == 1));
		}

	auto erase_it0          = bs.erase(bs.cend() - 3, bs.cend());
	auto expected_erase_it0 = bs.cend();
	VERIFY(erase_it0 == expected_erase_it0);
	VERIFY(bs.size() == 4);
	VERIFY_FALSE(bs.empty());

	bool val0 = bs[0];
	bool val1 = bs[1];
	bool val2 = bs[2];
	bool val3 = bs[3];
	VERIFY_FALSE(val0);
	VERIFY(val1);
	VERIFY_FALSE(val2);
	VERIFY(val3);

	auto erase_it1          = bs.erase(bs.cbegin(), bs.cbegin() + 4);
	auto expected_erase_it1 = bs.end();
	VERIFY(erase_it1 == expected_erase_it1);
	VERIFY(erase_it1 == bs.cbegin());
	VERIFY(erase_it1 == bs.cend());
	VERIFY(bs.size() == 0);
	VERIFY(bs.empty());
}

template<typename TestType, typename BitSequence>
void
dynamic_bitset_insert_erase_test_bulk_large(BitSequence& bs)
{
	VERIFY(bs.empty());
	VERIFY(bs.size() == 0);

	const std::size_t full_binary_bits = bitsy::binary_digits_v<TestType>;
	const std::size_t high_half_binary_bits =
	  (bitsy::binary_digits_v<TestType> / 2) + static_cast<std::size_t>(std::is_signed_v<TestType>);
	const std::size_t low_half_binary_bits = (bitsy::binary_digits_v<TestType> / 2);

	std::vector<TestType> insertion_storage(15, static_cast<TestType>(0));
	bitsy::bit_view<std::span<TestType>> insertion_view(insertion_storage);
	{
		auto start  = insertion_view.begin();
		auto finish = insertion_view.end();
		for (std::size_t i = 0; start != finish; ++start, ++i)
			{
				*start = is_even_respecting_boundaries<TestType>(i);
			}
	}

	auto it_post_insertion = bs.insert(bs.cbegin(), insertion_view.begin(), insertion_view.end());
	auto it_post_insertion_dist = std::distance(bs.begin(), it_post_insertion);
	VERIFY(it_post_insertion_dist == 0);
	const std::size_t post_insertion_size          = bs.size();
	const std::size_t expected_post_insertion_size = insertion_view.size();
	VERIFY(post_insertion_size == expected_post_insertion_size);
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
				VERIFY(expected == iv_val);
				VERIFY(expected == bs_val);
				VERIFY(bs_val == iv_val);
			}
		VERIFY(bsstart == bsfinish);
	}

	auto it_post_erase0      = bs.erase(bs.begin(), bs.begin() + full_binary_bits);
	auto it_post_erase0_dist = std::distance(bs.begin(), it_post_erase0);
	VERIFY(it_post_erase0_dist == 0);
	const std::size_t post_erase_size0          = bs.size();
	const std::size_t expected_post_erase_size0 = (post_insertion_size - full_binary_bits);
	VERIFY(post_erase_size0 == expected_post_erase_size0);
	{
		auto bsstart  = bs.cbegin();
		auto bsfinish = bs.cend();
		for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
			{
				bool expected = is_even_respecting_boundaries<TestType>(i);
				bool bs_val   = *bsstart;
				VERIFY(expected == bs_val);
			}
	}

	auto it_post_erase1      = bs.erase(bs.begin(), bs.begin() + (full_binary_bits * 3));
	auto it_post_erase1_dist = std::distance(bs.begin(), it_post_erase1);
	VERIFY(it_post_erase1_dist == 0);
	const std::size_t post_erase_size1          = bs.size();
	const std::size_t expected_post_erase_size1 = (post_erase_size0 - full_binary_bits * 3);
	VERIFY(post_erase_size1 == expected_post_erase_size1);
	{
		auto bsstart  = bs.cbegin();
		auto bsfinish = bs.cend();
		for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
			{
				bool expected = is_even_respecting_boundaries<TestType>(i);
				bool bs_val   = *bsstart;
				VERIFY(expected == bs_val);
			}
	}

	auto it_post_erase2      = bs.erase(bs.begin() + 1, bs.begin() + high_half_binary_bits + 1);
	auto it_post_erase2_dist = std::distance(bs.begin(), it_post_erase2);
	VERIFY(it_post_erase2_dist == 1);
	const std::size_t post_erase_size2          = bs.size();
	const std::size_t expected_post_erase_size2 = (post_erase_size1 - high_half_binary_bits);
	VERIFY(post_erase_size2 == expected_post_erase_size2);
	if constexpr (!std::is_signed_v<TestType>)
		{
			auto bsstart  = bs.cbegin();
			auto bsfinish = bs.cend();
			for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
				{
					bool expected = is_even_respecting_boundaries<TestType>(i);
					bool bs_val   = *bsstart;
					VERIFY(expected == bs_val);
				}
		}

	auto it_post_erase3 =
	  bs.erase(bs.begin() + 1, bs.begin() + (full_binary_bits + low_half_binary_bits) + 1);
	auto it_post_erase3_dist = std::distance(bs.begin(), it_post_erase3);
	VERIFY(it_post_erase3_dist == 1);
	const std::size_t post_erase_size3 = bs.size();
	const std::size_t expected_post_erase_size3 =
	  (post_erase_size2 - (full_binary_bits + low_half_binary_bits));
	VERIFY(post_erase_size3 == expected_post_erase_size3);
	{
		auto bsstart  = bs.cbegin();
		auto bsfinish = bs.cend();
		for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
			{
				bool expected = is_even_respecting_boundaries<TestType>(i);
				bool bs_val   = *bsstart;
				VERIFY(expected == bs_val);
			}
	}

	auto it_post_erase4      = bs.erase(bs.begin(), bs.begin() + 3);
	auto it_post_erase4_dist = std::distance(bs.begin(), it_post_erase4);
	VERIFY(it_post_erase4_dist == 0);
	const std::size_t post_erase_size4          = bs.size();
	const std::size_t expected_post_erase_size4 = (post_erase_size3 - 3);
	VERIFY(post_erase_size4 == expected_post_erase_size4);
	if constexpr (!std::is_signed_v<TestType>)
		{
			auto bsstart  = bs.cbegin();
			auto bsfinish = bs.cend();
			for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
				{
					bool expected = !is_even_respecting_boundaries<TestType>(i);
					bool bs_val   = *bsstart;
					VERIFY(expected == bs_val);
				}
		}

	auto it_post_erase5      = bs.erase(bs.begin(), bs.begin() + 1);
	auto it_post_erase5_dist = std::distance(bs.begin(), it_post_erase5);
	VERIFY(it_post_erase5_dist == 0);
	const std::size_t post_erase_size5          = bs.size();
	const std::size_t expected_post_erase_size5 = (post_erase_size4 - 1);
	VERIFY(post_erase_size5 == expected_post_erase_size5);
	if constexpr (!std::is_signed_v<TestType>)
		{
			auto bsstart  = bs.cbegin();
			auto bsfinish = bs.cend();
			for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
				{
					bool expected = is_even_respecting_boundaries<TestType>(i);
					bool bs_val   = *bsstart;
					VERIFY(expected == bs_val);
				}
		}

	auto it_post_erase6      = bs.erase(bs.begin(), bs.begin() + 4);
	auto it_post_erase6_dist = std::distance(bs.begin(), it_post_erase6);
	VERIFY(it_post_erase6_dist == 0);
	const std::size_t post_erase_size6          = bs.size();
	const std::size_t expected_post_erase_size6 = (post_erase_size5 - 4);
	VERIFY(post_erase_size6 == expected_post_erase_size6);
	if constexpr (!std::is_signed_v<TestType>)
		{
			auto bsstart  = bs.cbegin();
			auto bsfinish = bs.cend();
			for (std::size_t i = 0; bsstart != bsfinish; ++i, ++bsstart)
				{
					bool expected = is_even_respecting_boundaries<TestType>(i);
					bool bs_val   = *bsstart;
					VERIFY(expected == bs_val);
				}
		}

	auto it_post_erase7      = bs.erase(bs.cbegin(), bs.cend());
	auto it_post_erase7_dist = std::distance(bs.begin(), it_post_erase7);
	VERIFY(it_post_erase7_dist == 0);
	const std::size_t post_erase_size7          = bs.size();
	const std::size_t expected_post_erase_size7 = 0;
	VERIFY(post_erase_size7 == expected_post_erase_size7);
	VERIFY(it_post_erase7 == bs.cend());
}

#endif // ITSY_BITSY_TESTS_SHARED_TESTS_HPP
