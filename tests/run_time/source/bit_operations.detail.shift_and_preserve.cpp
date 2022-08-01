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

TEST_CASE("bit detail: shift_and_preserve", "[detail][shift_and_preserve]")
{
	const std::size_t start_val = 0b0010101;

	const std::size_t expected_pright_left_val2  = 0b0101101;
	const std::size_t expected_pright_right_val2 = 0b0001101;
	const std::size_t expected_pleft_left_val2   = 0b0010010;
	const std::size_t expected_pleft_right_val2  = 0b0010010;

	const std::size_t expected_pright_left_val0  = 0b0101011;
	const std::size_t expected_pright_right_val0 = 0b0001011;
	const std::size_t expected_pleft_left_val0   = 0b0010100;
	const std::size_t expected_pleft_right_val0  = 0b0010100;

	std::size_t pright_left_val2  = start_val;
	std::size_t pright_right_val2 = start_val;
	std::size_t pleft_left_val2   = start_val;
	std::size_t pleft_right_val2  = start_val;
	bitsy::__ib_detail::__shift_left_preserve_right<std::size_t>(pright_left_val2, 2, 1);
	bitsy::__ib_detail::__shift_right_preserve_right<std::size_t>(pright_right_val2, 2, 1);
	bitsy::__ib_detail::__shift_left_preserve_left<std::size_t>(pleft_left_val2, 2, 1);
	bitsy::__ib_detail::__shift_right_preserve_left<std::size_t>(pleft_right_val2, 2, 1);

	REQUIRE(pright_left_val2 == expected_pright_left_val2);
	REQUIRE(pright_right_val2 == expected_pright_right_val2);
	REQUIRE(pleft_left_val2 == expected_pleft_left_val2);
	REQUIRE(pleft_right_val2 == expected_pleft_right_val2);

	std::size_t pright_left_val0  = start_val;
	std::size_t pright_right_val0 = start_val;
	std::size_t pleft_left_val0   = start_val;
	std::size_t pleft_right_val0  = start_val;
	bitsy::__ib_detail::__shift_left_preserve_right<std::size_t>(pright_left_val0, 0, 1);
	bitsy::__ib_detail::__shift_right_preserve_right<std::size_t>(pright_right_val0, 0, 1);
	bitsy::__ib_detail::__shift_left_preserve_left<std::size_t>(pleft_left_val0, 0, 1);
	bitsy::__ib_detail::__shift_right_preserve_left<std::size_t>(pleft_right_val0, 0, 1);

	REQUIRE(pright_left_val0 == expected_pright_left_val0);
	REQUIRE(pright_right_val0 == expected_pright_right_val0);
	REQUIRE(pleft_left_val0 == expected_pleft_left_val0);
	REQUIRE(pleft_right_val0 == expected_pleft_right_val0);
}
