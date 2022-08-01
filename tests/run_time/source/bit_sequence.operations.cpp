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

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <ztd/idk/span.hpp>

#include <cstddef>
#include <cstdint>
#include <iterator>

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <string>

TEMPLATE_TEST_CASE("bit_sequence functionality with operations", "[bit_sequence<T>][operations]", std::uint64_t,
     std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t, std::int8_t,
     char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	using BinaryDigitsType                = ztd::any_to_underlying_t<TestType>;
	constexpr ::std::size_t binary_digits = bitsy::binary_digits_v<BinaryDigitsType>;

	constexpr std::array<TestType, 4> original_backing_data0 = { { (TestType)'m', (TestType)'e', (TestType)'o',
		(TestType)'w' } };
	constexpr std::array<TestType, 4> original_backing_data1 = { { (TestType)'m', (TestType)'e', (TestType)'o',
		(TestType)'w' } };

	bitsy::bit_sequence<std::vector<TestType>> original_data0(
	     ::std::in_place, original_backing_data0.cbegin(), original_backing_data0.cend());
	bitsy::bit_sequence<std::vector<TestType>> original_data1(
	     ::std::in_place, original_backing_data1.cbegin(), original_backing_data1.cend());

	{
		auto data0                             = original_data0;
		auto data1                             = original_data1;
		const auto data2                       = data0 & data1;
		const auto& data0_ref                  = data0 &= data1;
		const std::array<TestType, 4> expected = original_backing_data0;
		REQUIRE(std::addressof(data0_ref) == std::addressof(data0));
		REQUIRE(std::addressof(data2) != std::addressof(data0));
		const bool is_equal0 = std::equal(data0.base().begin(), data0.base().end(), expected.begin(), expected.end());
		const bool is_equal1 = std::equal(data2.base().begin(), data2.base().end(), expected.begin(), expected.end());
		REQUIRE(is_equal0);
		REQUIRE(is_equal1);
	}

	{
		auto data0                             = original_data0;
		auto data1                             = original_data1;
		const auto data2                       = data0 | data1;
		const auto& data0_ref                  = data0 |= data1;
		const std::array<TestType, 4> expected = original_backing_data0;
		REQUIRE(std::addressof(data0_ref) == std::addressof(data0));
		REQUIRE(std::addressof(data2) != std::addressof(data0));
		const bool is_equal0 = std::equal(data0.base().begin(), data0.base().end(), expected.begin(), expected.end());
		const bool is_equal1 = std::equal(data2.base().begin(), data2.base().end(), expected.begin(), expected.end());
		REQUIRE(is_equal0);
		REQUIRE(is_equal1);
	}

	{
		auto data0                             = original_data0;
		auto data1                             = original_data1;
		const auto data2                       = data0 ^ data1;
		const auto& data0_ref                  = data0 ^= data1;
		const std::array<TestType, 4> expected = { { (TestType)0, (TestType)0, (TestType)0, (TestType)0 } };
		REQUIRE(std::addressof(data0_ref) == std::addressof(data0));
		REQUIRE(std::addressof(data2) != std::addressof(data0));
		const bool is_equal0 = std::equal(data0.base().begin(), data0.base().end(), expected.begin(), expected.end());
		const bool is_equal1 = std::equal(data2.base().begin(), data2.base().end(), expected.begin(), expected.end());
		REQUIRE(is_equal0);
		REQUIRE(is_equal1);
	}

	{
		auto data0                             = original_data0;
		const auto data2                       = data0 << (binary_digits * 2);
		const auto& data0_ref                  = data0 <<= (binary_digits * 2);
		const std::array<TestType, 4> expected = { { (TestType)'o', (TestType)'w', (TestType)0, (TestType)0 } };
		REQUIRE(std::addressof(data0_ref) == std::addressof(data0));
		REQUIRE(std::addressof(data2) != std::addressof(data0));
		const bool is_equal0 = std::equal(data0.base().begin(), data0.base().end(), expected.begin(), expected.end());
		const bool is_equal1 = std::equal(data2.base().begin(), data2.base().end(), expected.begin(), expected.end());
		REQUIRE(is_equal0);
		REQUIRE(is_equal1);
	}

	{
		auto data0                             = original_data0;
		const auto data2                       = data0 >> (binary_digits * 2);
		const auto& data0_ref                  = data0 >>= (binary_digits * 2);
		const std::array<TestType, 4> expected = { { (TestType)0, (TestType)0, (TestType)'m', (TestType)'e' } };
		REQUIRE(std::addressof(data0_ref) == std::addressof(data0));
		REQUIRE(std::addressof(data2) != std::addressof(data0));
		const bool is_equal0 = std::equal(data0.base().begin(), data0.base().end(), expected.begin(), expected.end());
		const bool is_equal1 = std::equal(data2.base().begin(), data2.base().end(), expected.begin(), expected.end());
		REQUIRE(is_equal0);
		REQUIRE(is_equal1);
	}
}
