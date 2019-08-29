// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy/bitsy.hpp>

#include <assert.hpp>

#include <string>
#include <span>
#include <iostream>

int
main()
{
	std::string str = "Howdy!";
	std::cout << str << std::endl;
	// arguments get forwarded directly
	// to underlying range constructor
	bitsy::bit_view<std::span<char>> str_bits(str);

	// iterators
	auto bits_it = str_bits.begin();
	ITSY_BITSY_C_ASSERT(bits_it.position() == 0);
	ITSY_BITSY_C_ASSERT(*bits_it == bitsy::bit0);
	++bits_it;
	ITSY_BITSY_C_ASSERT(bits_it.position() == 1);
	ITSY_BITSY_C_ASSERT(*bits_it == bitsy::bit0);
	bits_it += 4;
	ITSY_BITSY_C_ASSERT(bits_it.position() == 5);
	ITSY_BITSY_C_ASSERT(*bits_it == bitsy::bit0);
	// flip a single bit
	// pointed to by `bits_it`
	bits_it->flip();
	ITSY_BITSY_C_ASSERT(*bits_it == bitsy::bit1);

	// we flipped the ASCII bit
	// for a capital letter!
	std::cout << str << std::endl;
	ITSY_BITSY_C_ASSERT(str == "howdy!");

	return 0;
}
