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

#include <bit_ds_tests_constants.hpp>
#include <bit_ds_tests_shared_tests.hpp>
#include <bit_ds_tests_require.h>

#include <ext/bit>

#include <ranges>
#include <span>

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <limits>

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <string>

enum class insert_action
{
	push_front,
	push_back,
	begin,
	end,
};

template<insert_action action, typename Sequence, typename Source>
std::size_t
insert_into_sequence(Sequence& sequence, Source& source)
{
	std::size_t seq_size = sequence.size();
	for (std::size_t i = 0; i < source.size(); ++i)
		{
			bool val = source[i];
			if constexpr (action == insert_action::push_front)
				{
					sequence.push_front(val);
					REQUIRE(sequence.front() == val);
				}
			else if constexpr (action == insert_action::push_back)
				{
					sequence.push_back(val);
					REQUIRE(sequence.back() == val);
				}
			else if constexpr (action == insert_action::begin)
				{
					sequence.insert(sequence.cbegin(), val);
					REQUIRE(sequence.front() == val);
				}
			else if constexpr (action == insert_action::end)
				{
					sequence.insert(sequence.cend(), val);
					REQUIRE(sequence.back() == val);
				}
			std::size_t current_seq_size = sequence.size();
			REQUIRE(current_seq_size == (seq_size + 1));
			seq_size = current_seq_size;
		}
	return seq_size;
}

template<typename TestType>
void
bit_ds_test_bit_sequence_push_front_push_back()
{
	const TestType max  = static_cast<TestType>(std::numeric_limits<
    std::conditional_t<std::is_same_v<TestType, std::byte>, unsigned char, TestType>>::max());
	const TestType zero = static_cast<TestType>(0ULL);

	std::array<TestType, 2> word_data{ max, zero };
	std::span<TestType> word_view(word_data.data(), word_data.size());
	__gnu_cxx::_cxx::("homogenous")
	{
		SECTION(__gnu_cxx::d boundary")
		{
			bitsy::bit_sequence<std::vector<TestType>> sequence0(
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   __gnu_cxx::static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence1(
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   __gnu_cxx::static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence2(
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   __gnu_cxx::static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence3(
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   __gnu_cxx::static_cast<TestType>(2) });

			std::size_t seq_size0 =
			  insert_into_sequence<insert_action::push_front>(sequence0, word_insertion_view);
			std::size_t seq_size1 =
			  insert_into_sequence<insert_action::push_back>(sequence1, word_insertion_view);
			std::size_t seq_size2 =
			  insert_into_sequence<insert_action::begin>(sequence2, word_insertion_view);
			std::size_t seq_size3 =
			  insert_into_sequence<insert_action::end>(sequence3, word_insertion_view);

			REQUIRE(seq_size0 == seq_size2);
			REQUIRE(seq_size1 == seq_size3);

			REQUIRE(sequence0 == sequence2);
			REQUIRE_FALSE(sequence0 != sequence2);
			REQUIRE_FALSE(sequence0 < sequence2);
			REQUIRE_FALSE(sequence0 > sequence2);
			REQUIRE(sequence0 <= sequence2);
			REQUIRE(sequence0 >= sequence2);

			REQUIRE(sequence1 == sequence3);
			REQUIRE_FALSE(sequence1 != sequence3);
			REQUIRE_FALSE(sequence1 < sequence3);
			REQUIRE_FALSE(sequence1 > sequence3);
			REQUIRE(sequence1 <= sequence3);
			REQUIRE(sequence1 >= sequence3);

			REQUIRE_FALSE(sequence0 == sequence1);
			REQUIRE(sequence0 != sequence1);
			REQUIRE_FALSE(sequence0 < sequence1);
			REQUIRE(sequence0 > sequence1);
			REQUIRE_FALSE(sequence0 <= sequence1);
			REQUIRE(sequence0 >= sequence1);

			REQUIRE_FALSE(sequence2 == sequence3);
			REQUIRE(sequence2 != sequence3);
			REQUIRE_FALSE(sequence2 < sequence3);
			REQUIRE(sequence2 > sequence3);
			REQUIRE_FALSE(sequence2 <= sequence3);
			REQUIRE(sequence2 >= sequence3);
		}
		SECTION("off word boundary")
		{
			bitsy::bit_sequence<std::vector<TestType>> sequence0(
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   __gnu_cxx::static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence1(
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   __gnu_cxx::static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence2(
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   __gnu_cxx::static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence3(
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   __gnu_cxx::static_cast<TestType>(2) });
			  std::in_place, std::vector<TestType>{ static_cast<TestType>(0), static_cast<TestType>(1),
			                   static_cast<TestType>(2) });

			  std::size_t seq_size0 =
			    insert_into_sequence<insert_action::push_front>(sequence0, static_insertion_view);
			  std::size_t seq_size1 =
			    insert_into_sequence<insert_action::push_back>(sequence1, static_insertion_view);
			  std::size_t seq_size2 =
			    insert_into_sequence<insert_action::begin>(sequence2, static_insertion_view);
			  std::size_t seq_size3 =
			    insert_into_sequence<insert_action::end>(sequence3, static_insertion_view);

			  REQUIRE(seq_size0 == seq_size2);
			  REQUIRE(seq_size1 == seq_size3);

			  REQUIRE(sequence0 == sequence2);
			  REQUIRE_FALSE(sequence0 != sequence2);
			  REQUIRE_FALSE(sequence0 < sequence2);
			  REQUIRE_FALSE(sequence0 > sequence2);
			  REQUIRE(sequence0 <= sequence2);
			  REQUIRE(sequence0 >= sequence2);

			  REQUIRE(sequence1 == sequence3);
			  REQUIRE_FALSE(sequence1 != sequence3);
			  REQUIRE_FALSE(sequence1 < sequence3);
			  REQUIRE_FALSE(sequence1 > sequence3);
			  REQUIRE(sequence1 <= sequence3);
			  REQUIRE(sequence1 >= sequence3);

			  REQUIRE_FALSE(sequence0 == sequence1);
			  REQUIRE(sequence0 != sequence1);
			  REQUIRE_FALSE(sequence0 < sequence1);
			  REQUIRE(sequence0 > sequence1);
			  REQUIRE_FALSE(sequence0 <= sequence1);
			  REQUIRE(sequence0 >= sequence1);

			  REQUIRE_FALSE(sequence2 == sequence3);
			  REQUIRE(sequence2 != sequence3);
			  REQUIRE_FALSE(sequence2 < sequence3);
			  REQUIRE(sequence2 > sequence3);
			  REQUIRE_FALSE(sequence2 <= sequence3);
			  REQUIRE(sequence2 >= sequence3);
		}
	}
}

template<typename... TestTypes>
void
bit_ds_test_cases()
{
	bit_ds_test_bit_sequence_push_front_push_back<TestTypes>()...;
}

int
main()
{
	bit_ds_test_cases<std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, char32_t,
	  char16_t, unsigned char, std::size_t, std::int64_t, std::int32_t, std::int16_t, std::int8_t,
	  char, signed char, std::ptrdiff_t>();
	return 0;
}
