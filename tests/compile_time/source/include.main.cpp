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

#include <string_view>

int
main(int, char* [])
{
	static constexpr unsigned data[] = { 0b0001, 0b0010 };
	static constexpr bitsy::bit_view<std::basic_string_view<unsigned>> data_bits(&data[0], 2);

	static_assert(data_bits[0], "First bit is not true (expected: true)!");
	static_assert(!data_bits.test(1), "Second bit is true  (expected: false)!");
	static_assert(*(data_bits.begin() + bitsy::binary_digits_v<unsigned> + 1),
	  "Second bit in second word is not true (expected: true)!");
	static_assert(data_bits.size() == (sizeof(unsigned) * CHAR_BIT * 2),
	  "The size of the bit view is not 2 x unsigned");
	static_assert(data_bits.size() == (bitsy::binary_digits_v<unsigned> * 2),
	  "The size of the bit view is not 2 x unsigned");
	static_assert(!data_bits[3].value(), "The bit is true (expected: false)!");

	return 0;
}