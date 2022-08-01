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

#include <vector>
#include <cassert>

int
main()
{
	// construct with initializer list
	bitsy::bit_sequence<std::vector<std::size_t>> bits{ false, true, true, false, false };
	// construct from iterators just like other containers
	bitsy::bit_sequence<std::vector<std::size_t>> other_bits(bits.cbegin(), bits.cend());

	// can compare
	ITSY_BITSY_C_ASSERT(bits == other_bits);
	ITSY_BITSY_C_ASSERT(!(bits != other_bits));

	// insertion
	bits.push_back(false);
	bits.insert(bits.begin() + 2, { true, true });
	ITSY_BITSY_C_ASSERT(bits.size() == 8);
	ITSY_BITSY_C_ASSERT(bits.count(true) == 4);

	// erasure
	bits.erase(bits.begin() + 1, bits.begin() + 3);
	ITSY_BITSY_C_ASSERT(bits.size() == 6);
	ITSY_BITSY_C_ASSERT(bits.popcount() == 2);

	// comparison works exactly the same
	ITSY_BITSY_C_ASSERT(bits != other_bits);
	ITSY_BITSY_C_ASSERT(!(bits == other_bits));

	return 0;
}
