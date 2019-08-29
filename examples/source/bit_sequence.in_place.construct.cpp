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

#include <cstdint>

int
main()
{
	std::vector<std::uint32_t> words{ 0xff00ff00, 0xff00ff00 };
	bitsy::bit_sequence<std::vector<std::uint32_t>> bits(std::in_place, std::move(words));

	const std::size_t bits_size = bits.size();

	// size of the container is 2 words
	ITSY_BITSY_C_ASSERT(bits_size == bitsy::binary_digits_v<std::uint32_t> * 2);
	ITSY_BITSY_C_ASSERT(bits_size == 64);

	// assert 16-bit pattern
	for (std::size_t index = 0; index < bits_size; ++index)
		{
			if ((index % 16) < 8)
				{
					ITSY_BITSY_C_ASSERT(!bits[index]);
				}
			else
				{
					ITSY_BITSY_C_ASSERT(bits[index]);
				}
		}

	return 0;
}
