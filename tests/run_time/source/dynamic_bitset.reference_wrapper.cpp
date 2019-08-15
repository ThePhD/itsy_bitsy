#include <itsy_tests/shared_insert_erase_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/dynamic_bitset.hpp>

#include <vector>
#include <deque>
#include <list>
#include <string>

TEMPLATE_TEST_CASE("dynamic_bitset reference_wrapper bulk insert test, unsigned",
  "[dynamic_bitset][reference_wrapper][bulk][insert][unsigned]", std::uint64_t, std::uint32_t,
  std::uint16_t, std::uint8_t, std::byte, char32_t, char16_t, unsigned char, std::size_t)
{
	SECTION("vector")
	{
		std::vector<TestType> backing_storage;
		{
			bitsy::basic_dynamic_bitset<std::reference_wrapper<std::vector<TestType>>> storage(
			  std::in_place, backing_storage);
			dynamic_bitset_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(backing_storage.size() > 0);
	}
	SECTION("std::basic_string")
	{
		std::basic_string<TestType> backing_storage;
		{
			bitsy::basic_dynamic_bitset<std::reference_wrapper<std::basic_string<TestType>>> storage(
			  std::in_place, backing_storage);
			dynamic_bitset_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(backing_storage.size() > 0);
	}
	SECTION("deque")
	{
		std::deque<TestType> backing_storage;
		{
			bitsy::basic_dynamic_bitset<std::reference_wrapper<std::deque<TestType>>> storage(
			  std::in_place, backing_storage);
			dynamic_bitset_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(backing_storage.size() > 0);
	}
	SECTION("list")
	{
		std::list<TestType> backing_storage;
		{
			bitsy::basic_dynamic_bitset<std::reference_wrapper<std::list<TestType>>> storage(
			  std::in_place, backing_storage);
			dynamic_bitset_insert_test_bulk_small<TestType>(storage);
		}
		REQUIRE(backing_storage.size() > 0);
	}
}
