#include <itsy_tests/shared_insert_erase_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/dynamic_bitset.hpp>

#include <range/v3/view/subrange.hpp>

#include <vector>
#include <deque>
#include <list>
#include <string>

TEMPLATE_TEST_CASE("dynamic_bitset insert/erase/clear test, unsigned",
  "[dynamic_bitset][insert][erase][clear][unsigned]", std::uint64_t, std::uint32_t, std::uint16_t,
  std::uint8_t, std::byte, char32_t, char16_t, unsigned char, std::size_t)
{
	SECTION("vector")
	{
		bitsy::basic_dynamic_bitset<std::vector<TestType>> storage;
		dynamic_bitset_insert_erase_test<TestType>(storage);
	}
	SECTION("std::basic_string")
	{
		bitsy::basic_dynamic_bitset<std::basic_string<TestType>> storage;
		dynamic_bitset_insert_erase_test<TestType>(storage);
	}
	SECTION("deque")
	{
		bitsy::basic_dynamic_bitset<std::deque<TestType>> storage;
		dynamic_bitset_insert_erase_test<TestType>(storage);
	}
	SECTION("list")
	{
		bitsy::basic_dynamic_bitset<std::list<TestType>> storage;
		dynamic_bitset_insert_erase_test<TestType>(storage);
	}
}