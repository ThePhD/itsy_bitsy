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

TEMPLATE_TEST_CASE("bit_view functionality with operations", "[bit_view<T>][operations]", std::uint64_t, std::uint32_t,
     std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t, std::int8_t, char32_t, char16_t,
     char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	using BinaryDigitsType                = ztd::any_to_underlying_t<TestType>;
	constexpr ::std::size_t binary_digits = bitsy::binary_digits_v<BinaryDigitsType>;

	constexpr std::array<TestType, 4> original_data0 = { { (TestType)'m', (TestType)'e', (TestType)'o',
		(TestType)'w' } };
	constexpr std::array<TestType, 4> original_data1 = { { (TestType)'m', (TestType)'e', (TestType)'o',
		(TestType)'w' } };

	{
		std::array<TestType, 4> data0 = original_data0;
		std::array<TestType, 4> data1 = original_data1;
		ztd::span<TestType> view0(data0);
		ztd::span<TestType> view1(data1);
		bitsy::bit_span<TestType> bitview0     = view0;
		bitsy::bit_span<TestType> bitview1     = view1;
		const std::array<TestType, 4> expected = original_data0;
		const auto& same_as_bitview0           = bitview0 &= bitview1;
		REQUIRE(std::addressof(same_as_bitview0) == std::addressof(bitview0));
		const bool is_equal = std::equal(data0.begin(), data0.end(), expected.begin(), expected.end());
		REQUIRE(is_equal);
	}

	{
		std::array<TestType, 4> data0 = original_data0;
		std::array<TestType, 4> data1 = original_data1;
		ztd::span<TestType> view0(data0);
		ztd::span<TestType> view1(data1);
		bitsy::bit_span<TestType> bitview0     = view0;
		bitsy::bit_span<TestType> bitview1     = view1;
		const std::array<TestType, 4> expected = original_data0;
		const auto& same_as_bitview0           = bitview0 |= bitview1;
		REQUIRE(std::addressof(same_as_bitview0) == std::addressof(bitview0));
		const bool is_equal = std::equal(data0.begin(), data0.end(), expected.begin(), expected.end());
		REQUIRE(is_equal);
	}

	{
		std::array<TestType, 4> data0 = original_data0;
		std::array<TestType, 4> data1 = original_data1;
		ztd::span<TestType> view0(data0);
		ztd::span<TestType> view1(data1);
		bitsy::bit_span<TestType> bitview0     = view0;
		bitsy::bit_span<TestType> bitview1     = view1;
		const std::array<TestType, 4> expected = { { (TestType)0, (TestType)0, (TestType)0, (TestType)0 } };
		const auto& same_as_bitview0           = bitview0 ^= bitview1;
		REQUIRE(std::addressof(same_as_bitview0) == std::addressof(bitview0));
		const bool is_equal = std::equal(data0.begin(), data0.end(), expected.begin(), expected.end());
		REQUIRE(is_equal);
	}

	{
		std::array<TestType, 4> data0 = original_data0;
		ztd::span<TestType> view0(data0);
		bitsy::bit_span<TestType> bitview0     = view0;
		const std::array<TestType, 4> expected = { { (TestType)'o', (TestType)'w', (TestType)0, (TestType)0 } };
		const auto& same_as_bitview0           = bitview0 <<= (binary_digits * 2);
		REQUIRE(std::addressof(same_as_bitview0) == std::addressof(bitview0));
		const bool is_equal = std::equal(data0.begin(), data0.end(), expected.begin(), expected.end());
		REQUIRE(is_equal);
	}

	{
		std::array<TestType, 4> data0 = original_data0;
		ztd::span<TestType> view0(data0);
		bitsy::bit_span<TestType> bitview0     = view0;
		const std::array<TestType, 4> expected = { { (TestType)0, (TestType)0, (TestType)'m', (TestType)'e' } };
		const auto& same_as_bitview0           = bitview0 >>= (binary_digits * 2);
		REQUIRE(std::addressof(same_as_bitview0) == std::addressof(bitview0));
		const bool is_equal = std::equal(data0.begin(), data0.end(), expected.begin(), expected.end());
		REQUIRE(is_equal);
	}
}
