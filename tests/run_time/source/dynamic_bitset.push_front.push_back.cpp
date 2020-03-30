// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy/tests/constants.hpp>
#include <itsy/tests/shared_tests.hpp>
#include <itsy/tests/shared_insert_tests.hpp>
#include <itsy/tests/tracking_allocator.hpp>

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <itsy/tests/ranges.hpp>
#include <itsy/tests/span.hpp>

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

TEMPLATE_TEST_CASE("dynamic_bitset insertion functionality", "[dynamic_bitset][insert]", std::uint64_t, std::uint32_t,
     std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t, std::int8_t, char32_t, char16_t,
     char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	using allocator      = bitsy::tests::tracking_allocator<std::allocator<TestType>>;
	using allocator_ref  = std::reference_wrapper<allocator>;
	using dynamic_bitset = bitsy::dynamic_bitset<TestType, allocator_ref>;

	const TestType max = static_cast<TestType>(
	     std::numeric_limits<std::conditional_t<std::is_same_v<TestType, std::byte>, unsigned char, TestType>>::max());
	const TestType zero = static_cast<TestType>(0ULL);

	std::array<TestType, 2> word_data{ max, zero };
	bitsy::tests::span<TestType> word_view(word_data.data(), word_data.size());
	bitsy::bit_view<bitsy::tests::span<TestType>> word_insertion_view(word_view);
	bitsy::bit_view<bitsy::tests::span<TestType>, bitsy::bit_bounds<0, 13>> static_insertion_view(word_view);

	SECTION("homogenous")
	{
		SECTION("on word boundary")
		{
			allocator sequence0_allocator;
			allocator sequence1_allocator;
			allocator sequence2_allocator;
			allocator sequence3_allocator;

			{
				dynamic_bitset sequence0(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence0_allocator);
				dynamic_bitset sequence1(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence1_allocator);
				dynamic_bitset sequence2(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence2_allocator);
				dynamic_bitset sequence3(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence3_allocator);

				std::size_t seq_size0 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::push_front>(
				     sequence0, word_insertion_view);
				std::size_t seq_size1 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::push_back>(
				     sequence1, word_insertion_view);
				std::size_t seq_size2 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::begin>(
				     sequence2, word_insertion_view);
				std::size_t seq_size3 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::end>(
				     sequence3, word_insertion_view);

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

			REQUIRE(sequence0_allocator.alive() == 0);
			REQUIRE(sequence0_allocator.allocations_alive() == 0);
			REQUIRE(sequence1_allocator.alive() == 0);
			REQUIRE(sequence1_allocator.allocations_alive() == 0);
			REQUIRE(sequence2_allocator.alive() == 0);
			REQUIRE(sequence2_allocator.allocations_alive() == 0);
			REQUIRE(sequence3_allocator.alive() == 0);
			REQUIRE(sequence3_allocator.allocations_alive() == 0);
		}
		SECTION("off word boundary")
		{
			allocator sequence0_allocator;
			allocator sequence1_allocator;
			allocator sequence2_allocator;
			allocator sequence3_allocator;

			{
				dynamic_bitset sequence0(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence0_allocator);
				dynamic_bitset sequence1(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence1_allocator);
				dynamic_bitset sequence2(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence2_allocator);
				dynamic_bitset sequence3(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence3_allocator);

				std::size_t seq_size0 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::push_front>(
				     sequence0, static_insertion_view);
				std::size_t seq_size1 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::push_back>(
				     sequence1, static_insertion_view);
				std::size_t seq_size2 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::begin>(
				     sequence2, static_insertion_view);
				std::size_t seq_size3 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::end>(
				     sequence3, static_insertion_view);

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

			REQUIRE(sequence0_allocator.alive() == 0);
			REQUIRE(sequence0_allocator.allocations_alive() == 0);
			REQUIRE(sequence1_allocator.alive() == 0);
			REQUIRE(sequence1_allocator.allocations_alive() == 0);
			REQUIRE(sequence2_allocator.alive() == 0);
			REQUIRE(sequence2_allocator.allocations_alive() == 0);
			REQUIRE(sequence3_allocator.alive() == 0);
			REQUIRE(sequence3_allocator.allocations_alive() == 0);
		}
	}
}

TEMPLATE_TEST_CASE("bit_vector<..., 0> insertion functionality", "[bit_vector<..., 0>][insert]", std::uint64_t,
     std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t, std::int8_t,
     char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	using allocator      = bitsy::tests::tracking_allocator<std::allocator<TestType>>;
	using allocator_ref  = std::reference_wrapper<allocator>;
	using dynamic_bitset = bitsy::small_bit_vector<TestType, 0, allocator_ref>;

	const TestType max = static_cast<TestType>(
	     std::numeric_limits<std::conditional_t<std::is_same_v<TestType, std::byte>, unsigned char, TestType>>::max());
	const TestType zero = static_cast<TestType>(0ULL);

	std::array<TestType, 2> word_data{ max, zero };
	bitsy::tests::span<TestType> word_view(word_data.data(), word_data.size());
	bitsy::bit_view<bitsy::tests::span<TestType>> word_insertion_view(word_view);
	bitsy::bit_view<bitsy::tests::span<TestType>, bitsy::bit_bounds<0, 13>> static_insertion_view(word_view);

	SECTION("homogenous")
	{
		SECTION("on word boundary")
		{
			allocator sequence0_allocator;
			allocator sequence1_allocator;
			allocator sequence2_allocator;
			allocator sequence3_allocator;

			{
				dynamic_bitset sequence0(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence0_allocator);
				dynamic_bitset sequence1(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence1_allocator);
				dynamic_bitset sequence2(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence2_allocator);
				dynamic_bitset sequence3(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence3_allocator);

				std::size_t seq_size0 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::push_front>(
				     sequence0, word_insertion_view);
				std::size_t seq_size1 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::push_back>(
				     sequence1, word_insertion_view);
				std::size_t seq_size2 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::begin>(
				     sequence2, word_insertion_view);
				std::size_t seq_size3 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::end>(
				     sequence3, word_insertion_view);

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

			REQUIRE(sequence0_allocator.alive() == 0);
			REQUIRE(sequence0_allocator.allocations_alive() == 0);
			REQUIRE(sequence1_allocator.alive() == 0);
			REQUIRE(sequence1_allocator.allocations_alive() == 0);
			REQUIRE(sequence2_allocator.alive() == 0);
			REQUIRE(sequence2_allocator.allocations_alive() == 0);
			REQUIRE(sequence3_allocator.alive() == 0);
			REQUIRE(sequence3_allocator.allocations_alive() == 0);
		}
		SECTION("off word boundary")
		{
			allocator sequence0_allocator;
			allocator sequence1_allocator;
			allocator sequence2_allocator;
			allocator sequence3_allocator;

			{
				dynamic_bitset sequence0(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence0_allocator);
				dynamic_bitset sequence1(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence1_allocator);
				dynamic_bitset sequence2(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence2_allocator);
				dynamic_bitset sequence3(std::in_place,
				     { static_cast<TestType>(0), static_cast<TestType>(1), static_cast<TestType>(2) },
				     sequence3_allocator);

				std::size_t seq_size0 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::push_front>(
				     sequence0, static_insertion_view);
				std::size_t seq_size1 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::push_back>(
				     sequence1, static_insertion_view);
				std::size_t seq_size2 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::begin>(
				     sequence2, static_insertion_view);
				std::size_t seq_size3 = bitsy::tests::insert_into_sequence<bitsy::tests::insert_action::end>(
				     sequence3, static_insertion_view);

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

			REQUIRE(sequence0_allocator.alive() == 0);
			REQUIRE(sequence0_allocator.allocations_alive() == 0);
			REQUIRE(sequence1_allocator.alive() == 0);
			REQUIRE(sequence1_allocator.allocations_alive() == 0);
			REQUIRE(sequence2_allocator.alive() == 0);
			REQUIRE(sequence2_allocator.allocations_alive() == 0);
			REQUIRE(sequence3_allocator.alive() == 0);
			REQUIRE(sequence3_allocator.allocations_alive() == 0);
		}
	}
}
