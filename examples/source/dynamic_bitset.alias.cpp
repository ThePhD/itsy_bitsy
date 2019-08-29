// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#include <itsy/bitsy.hpp>

#include <assert.hpp>

int
main()
{
	bitsy::dynamic_bitset<std::size_t> bits(40, false);

	ITSY_BITSY_C_ASSERT(bits.size() == 40);

	bits[20].set(true);
	bits[21].set(true);

	ITSY_BITSY_C_ASSERT(bits.any());
	ITSY_BITSY_C_ASSERT(!bits.all());
	ITSY_BITSY_C_ASSERT(!bits.none());

	return 0;
}