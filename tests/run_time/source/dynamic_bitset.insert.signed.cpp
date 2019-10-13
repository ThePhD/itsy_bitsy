// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy/tests/shared_insert_erase_tests.hpp>
#include <itsy/tests/tracking_allocator.hpp>

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <vector>
#include <deque>
#include <list>
#include <string>

TEMPLATE_TEST_CASE("dynamic_bitset bulk insert test, signed",
     "[dynamic_bitset][bulk][insert][signed]", std::int64_t, std::int32_t, std::int16_t,
     std::int8_t, char, signed char, std::ptrdiff_t)
{
	SECTION("packed_dynamic_bitset<..., tracking_allocator>")
	{
		using allocator     = bitsy::tests::tracking_allocator<std::allocator<TestType>>;
		using allocator_ref = std::reference_wrapper<allocator>;
		allocator alloc{};
		{
			bitsy::packed_dynamic_bitset<TestType, allocator_ref> storage(alloc);
			bit_sequence_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(alloc.alive() == 0);
		REQUIRE(alloc.allocations_alive() == 0);
	}
	SECTION("packed_dynamic_bitset")
	{
		bitsy::packed_dynamic_bitset<TestType> storage;
		bit_sequence_insert_test_bulk_small<TestType>(storage);
	}
	SECTION("dynamic_bitset<..., tracking_allocator>")
	{
		using allocator     = bitsy::tests::tracking_allocator<std::allocator<TestType>>;
		using allocator_ref = std::reference_wrapper<allocator>;
		allocator alloc{};
		{
			bitsy::dynamic_bitset<TestType, allocator_ref> storage(alloc);
			bit_sequence_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(alloc.alive() == 0);
		REQUIRE(alloc.allocations_alive() == 0);
	}
	SECTION("dynamic_bitset")
	{
		bitsy::dynamic_bitset<TestType> storage;
		bit_sequence_insert_test_bulk_small<TestType>(storage);
	}
}
