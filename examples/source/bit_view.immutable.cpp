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

#include <span>
#include <cstdint>

int
main()
{
	std::vector<std::uint16_t> storage{ 0, 0, 0 };
	bitsy::bit_view<std::span<const std::uint16_t>> bits(storage);

	ITSY_BITSY_C_ASSERT(bits.size() == 48);

	// the below will trigger a compiler error,
	// thus preserving const-safety
	//(*bits.begin()) = true;
	// bits[16] = bitsy::bit1;
	// bits.begin()->flip();

	// can use auto, just showing the actual type
	for (bitsy::bit_reference<const std::uint16_t&> bit_ref : bits)
		{
			ITSY_BITSY_C_ASSERT(!bit_ref.value());
			// cannot use mutable methods: compiler will error!
			// bit_ref.flip();
			// bit_ref.set();
			// bit_ref.reset();
		}


	return 0;
}
