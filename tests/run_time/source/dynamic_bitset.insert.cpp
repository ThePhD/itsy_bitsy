#include <itsy_tests/shared_insert_erase_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/dynamic_bitset.hpp>

#include <vector>
#include <deque>
#include <list>
#include <string>

TEMPLATE_TEST_CASE("dynamic_bitset bulk insert test, unsigned",
  "[dynamic_bitset][bulk][insert][unsigned]", std::uint64_t, std::uint32_t, std::uint16_t,
  std::uint8_t, std::byte, char32_t, char16_t, unsigned char, std::size_t)
{
	SECTION("vector")
	{
		bitsy::basic_dynamic_bitset<std::vector<TestType>> storage;
		dynamic_bitset_insert_test_bulk_small<TestType>(storage);
	}
	SECTION("std::basic_string")
	{
		bitsy::basic_dynamic_bitset<std::basic_string<TestType>> storage;
		dynamic_bitset_insert_test_bulk_small<TestType>(storage);
	}
	SECTION("deque")
	{
		bitsy::basic_dynamic_bitset<std::deque<TestType>> storage;
		dynamic_bitset_insert_test_bulk_small<TestType>(storage);
	}
	SECTION("list")
	{
		bitsy::basic_dynamic_bitset<std::list<TestType>> storage;
		dynamic_bitset_insert_test_bulk_small<TestType>(storage);
	}
}
