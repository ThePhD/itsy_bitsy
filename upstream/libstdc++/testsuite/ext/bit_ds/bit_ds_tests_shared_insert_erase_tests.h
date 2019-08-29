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

#include <ext/bit>

#include <span>
#include <vector>

template<typename TestType>
constexpr bool
is_even_respecting_boundaries(std::size_t i) noexcept
{
	std::size_t modulo = i % __gnu_cxx::binary_digits_v<TestType>;
	return (modulo % 2) == 0;
}

template<typename TestType, typename BitSequence>
void
bit_sequence_insert_erase_test(BitSequence& bs)
{
	const std::size_t original_size    = bs.size();
	const std::size_t pre_insert_size  = original_size + 2;
	const std::size_t post_insert_size = pre_insert_size + __gnu_cxx::binary_digits_v<TestType>;

	REQUIRE(original_size == 0);
	REQUIRE(bs.empty());
	REQUIRE(bs.size() == 0);
	REQUIRE(bs.cbegin() == bs.cend());
	REQUIRE(bs.begin() == bs.end());
	REQUIRE_FALSE(bs.cbegin() != bs.cend());
	REQUIRE_FALSE(bs.begin() != bs.end());
	bs.push_back(false);
	bs.push_back(false);

	REQUIRE(bs.size() == pre_insert_size);

	for (std::size_t i = 0; i < __gnu_cxx::binary_digits_v<TestType>; ++i)
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
			if (i == 0 || i == (1 + __gnu_cxx::binary_digits_v<TestType>))
				{
					REQUIRE_FALSE(value);
				}
			else
				{
					REQUIRE(value);
				}
		}

	for (std::size_t i = 0; i < __gnu_cxx::binary_digits_v<TestType>; ++i)
		{
			auto target = bs.cbegin();
			std::advance(target, 1);
			auto it                   = bs.erase(target);
			const bool val            = *it;
			const bool expected_val   = (i < (__gnu_cxx::binary_digits_v<TestType> - 1));
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
			bool val = bs[i];
			REQUIRE(val == ((i % 2) == 1));
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
			bool val = bs[i];
			REQUIRE(val == ((i % 2) == 1));
		}

	std::initializer_list<value_type> il2 = { true, false, true, false, true, false, true, false,
		true, false, true, false };
	auto insert_it2                       = bs.insert(std::next(bs.cbegin(), 3), il2);
	auto expected_insert_it2              = std::next(bs.cbegin(), 3);
	const std::size_t post_insert2_size   = bs.size();
	const std::size_t expected_post_insert2_size = il2.size() + expected_post_insert1_size;
	REQUIRE(insert_it2 == expected_insert_it2);
	REQUIRE(post_insert2_size == expected_post_insert2_size);
	for (std::size_t i = 0; i < bs.size(); ++i)
		{
			bool val = bs[i];
			REQUIRE(val == ((i % 2) == 1));
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
			bool val = bs[i];
			REQUIRE(val == ((i % 2) == 1));
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

	const std::size_t full_binary_bits      = __gnu_cxx::xx::binary_digits_v<TestType>;
	const std::size_t high_half_binary_bits = (__gnu_cxx::xx::binary_digits_v<TestType> / 2) +2) +
	                                          static_cast<std::size_t>(std::is_signed_v<TestType>);
	const std::size_t low_half_binary_bits = (__gnu_cxx::binary_digits_v<TestType> / 2);

	std::vector<TestType> insertion_storage(15, static_cast<TestType>(0));
	__gnu_cxx::bit_view<std::span<TestType>> insertion_view(insertion_storage);
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

	auto it_post_erase3 =
	  bs.erase(bs.begin() + 1, bs.begin() + (full_binary_bits + low_half_binary_bits) + 1);
	auto it_post_erase3_dist = std::distance(bs.begin(), it_post_erase3);
	REQUIRE(it_post_erase3_dist == 1);
	const std::size_t post_erase_size3 = bs.size();
	const std::size_t expected_post_erase_size3 =
	  (post_erase_size2 - (full_binary_bits + low_half_binary_bits));
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

#endif
