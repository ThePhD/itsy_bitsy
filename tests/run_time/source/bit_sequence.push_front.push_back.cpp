// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy_tests/constants.hpp>
#include <itsy_tests/shared_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

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

TEMPLATE_TEST_CASE("bit_sequence insertion functionality", "[bit_sequence][insert]", std::uint64_t,
     std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
     std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t,
     std::ptrdiff_t)
{
	const TestType max  = static_cast<TestType>(std::numeric_limits<
          std::conditional_t<std::is_same_v<TestType, std::byte>, unsigned char, TestType>>::max());
	const TestType zero = static_cast<TestType>(0ULL);

	std::array<TestType, 2> word_data{ max, zero };
	std::span<TestType> word_view(word_data.data(), word_data.size());
	bitsy::bit_view<std::span<TestType>> word_insertion_view(word_view);
	bitsy::bit_view<std::span<TestType>, bitsy::bit_bounds<0, 13>> static_insertion_view(
	     word_view);

	SECTION("homogenous")
	{
		SECTION("on word boundary")
		{
			bitsy::bit_sequence<std::vector<TestType>> sequence0(
			     std::in_place, std::vector<TestType>{ static_cast<TestType>(0),
			                         static_cast<TestType>(1), static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence1(
			     std::in_place, std::vector<TestType>{ static_cast<TestType>(0),
			                         static_cast<TestType>(1), static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence2(
			     std::in_place, std::vector<TestType>{ static_cast<TestType>(0),
			                         static_cast<TestType>(1), static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence3(
			     std::in_place, std::vector<TestType>{ static_cast<TestType>(0),
			                         static_cast<TestType>(1), static_cast<TestType>(2) });

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
			     std::in_place, std::vector<TestType>{ static_cast<TestType>(0),
			                         static_cast<TestType>(1), static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence1(
			     std::in_place, std::vector<TestType>{ static_cast<TestType>(0),
			                         static_cast<TestType>(1), static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence2(
			     std::in_place, std::vector<TestType>{ static_cast<TestType>(0),
			                         static_cast<TestType>(1), static_cast<TestType>(2) });
			bitsy::bit_sequence<std::vector<TestType>> sequence3(
			     std::in_place, std::vector<TestType>{ static_cast<TestType>(0),
			                         static_cast<TestType>(1), static_cast<TestType>(2) });

			std::size_t seq_size0 = insert_into_sequence<insert_action::push_front>(
			     sequence0, static_insertion_view);
			std::size_t seq_size1 = insert_into_sequence<insert_action::push_back>(
			     sequence1, static_insertion_view);
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