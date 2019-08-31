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

#include <vector>
#include <deque>
#include <list>
#include <string>

template<typename BitSequence, typename Il>
void
test_bitset_constructors_initializer_list(BitSequence& storage, Il& il)
{
	REQUIRE(storage.size() == il.size());
	std::size_t i     = 0;
	auto storage_last = storage.cend();
	for (auto storage_it = storage.cbegin(); storage_it != storage_last; ++i, ++storage_it)
		{
			const bool val          = *storage_it;
			const bool expected_val = (i % 2) == 1;
			REQUIRE(val == expected_val);
		}
	REQUIRE(i == storage.size());
}

template<typename BitSequence, typename SizeType, typename ValueType>
void
test_bitset_constructors_num_val(BitSequence& storage, SizeType num, ValueType constructor_val)
{
	REQUIRE(storage.size() == num);
	std::size_t i     = 0;
	auto storage_last = storage.cend();
	for (auto storage_it = storage.cbegin(); storage_it != storage_last; ++i, ++storage_it)
		{
			const bool val          = *storage_it;
			const bool expected_val = static_cast<bool>(constructor_val);
			REQUIRE(val == expected_val);
		}
	REQUIRE(i == storage.size());
}

template<typename BitSequence, typename SizeType>
void
test_bitset_constructors_num(BitSequence& storage, SizeType num)
{
	test_bitset_constructors_num_val(storage, num, false);
}

template<typename BitSequence, typename Source, typename First, typename Last>
void
test_bitset_constructors_first_last(BitSequence& storage, Source& source, First first, Last last)
{
	const std::size_t expected_size = std::size(source);
	REQUIRE(storage.size() == expected_size);
	std::size_t i     = 0;
	auto storage_last = std::cend(storage);
	for (auto storage_it = std::cbegin(storage); storage_it != storage_last;
	     ++i, ++storage_it, ++first)
		{
			const bool val          = *storage_it;
			const bool expected_val = *first;
			REQUIRE(val == expected_val);
		}
	REQUIRE(i == storage.size());
	REQUIRE(first == last);
}

TEMPLATE_TEST_CASE("bit_sequence constructors test", "[bit_sequence][constructors]", std::uint64_t,
     std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
     std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t,
     std::ptrdiff_t)
{
	SECTION("initializer_list")
	{
		std::initializer_list<bitsy::bit_value> il{ false, true, false, true, false, true, false,
			true, false, true, false, true, false, true, false, true, false, true, false, true,
			false, true, false, true, false, true, false, true, false, true, false, true, false,
			true, false, true, false, true, false, true, false, true, false, true, false, true,
			false, true, false, true, false, true, false, true, false, true, false, true, false,
			true, false, true, false, true, false, true, false, true, false, true, false, true,
			false, true, false, true, false, true, false, true, false, true, false, true, false,
			true, false, true, false, true, false, true, false, true };
		SECTION("vector")
		{
			bitsy::bit_sequence<std::vector<TestType>> storage(il);
			test_bitset_constructors_initializer_list(storage, il);
		}
		SECTION("std::basic_string")
		{
			bitsy::bit_sequence<std::basic_string<TestType>> storage(il);
			test_bitset_constructors_initializer_list(storage, il);
		}
		SECTION("deque")
		{
			bitsy::bit_sequence<std::deque<TestType>> storage(il);
			test_bitset_constructors_initializer_list(storage, il);
		}
		SECTION("list")
		{
			bitsy::bit_sequence<std::list<TestType>> storage(il);
			test_bitset_constructors_initializer_list(storage, il);
		}
	}
	SECTION("num")
	{
		std::size_t num = 516;
		SECTION("vector")
		{
			bitsy::bit_sequence<std::vector<TestType>> storage(num);
			test_bitset_constructors_num(storage, num);
		}
		SECTION("std::basic_string")
		{
			bitsy::bit_sequence<std::basic_string<TestType>> storage(num);
			test_bitset_constructors_num(storage, num);
		}
		SECTION("deque")
		{
			bitsy::bit_sequence<std::deque<TestType>> storage(num);
			test_bitset_constructors_num(storage, num);
		}
		SECTION("list")
		{
			bitsy::bit_sequence<std::list<TestType>> storage(num);
			test_bitset_constructors_num(storage, num);
		}
	}
	SECTION("num, val")
	{
		std::size_t num      = 427;
		bitsy::bit_value val = true;
		SECTION("vector")
		{
			bitsy::bit_sequence<std::vector<TestType>> storage(num, val);
			test_bitset_constructors_num_val(storage, num, val);
		}
		SECTION("std::basic_string")
		{
			bitsy::bit_sequence<std::basic_string<TestType>> storage(num, val);
			test_bitset_constructors_num_val(storage, num, val);
		}
		SECTION("deque")
		{
			bitsy::bit_sequence<std::deque<TestType>> storage(num, val);
			test_bitset_constructors_num_val(storage, num, val);
		}
		SECTION("list")
		{
			bitsy::bit_sequence<std::list<TestType>> storage(num, val);
			test_bitset_constructors_num_val(storage, num, val);
		}
	}
	SECTION("first, last (random access)")
	{
		const bool data[] = { false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, false, true, false, false, false, false, false, false, true, false,
			true, false, true, true, false, false, true, true, true, true, true, true, true,
			true, false, false, true, true, true, true, true, true, true, true, false, false,
			true, true, true, true, true, true, true, true, false, false, true, true, true, true,
			true, true };
		const bool* first = data + 0;
		const bool* last  = data + std::size(data);
		SECTION("vector")
		{
			bitsy::bit_sequence<std::vector<TestType>> storage(first, last);
			test_bitset_constructors_first_last(storage, data, first, last);
		}
		SECTION("std::basic_string")
		{
			bitsy::bit_sequence<std::basic_string<TestType>> storage(first, last);
			test_bitset_constructors_first_last(storage, data, first, last);
		}
		SECTION("deque")
		{
			bitsy::bit_sequence<std::deque<TestType>> storage(first, last);
			test_bitset_constructors_first_last(storage, data, first, last);
		}
		SECTION("list")
		{
			bitsy::bit_sequence<std::list<TestType>> storage(first, last);
			test_bitset_constructors_first_last(storage, data, first, last);
		}
	}
	SECTION("first, last (non-random-access)")
	{
		const std::list<bool> data{ false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, false, true, false, false, false, false, false, false, true,
			false, true, false, true, true, false, false, true, true, true, true, true, true,
			true, true, false, false, true, true, true, true, true, true, true, true, false,
			false, true, true, true, true, true, true, true, true, false, false, true, true,
			true, true, true, true };
		auto first = data.cbegin();
		auto last  = data.cend();
		SECTION("vector")
		{
			bitsy::bit_sequence<std::vector<TestType>> storage(first, last);
			test_bitset_constructors_first_last(storage, data, first, last);
		}
		SECTION("std::basic_string")
		{
			bitsy::bit_sequence<std::basic_string<TestType>> storage(first, last);
			test_bitset_constructors_first_last(storage, data, first, last);
		}
		SECTION("deque")
		{
			bitsy::bit_sequence<std::deque<TestType>> storage(first, last);
			test_bitset_constructors_first_last(storage, data, first, last);
		}
		SECTION("list")
		{
			bitsy::bit_sequence<std::list<TestType>> storage(first, last);
			test_bitset_constructors_first_last(storage, data, first, last);
		}
	}
}
