// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy/bit_view.hpp>

#include <ztd/idk/span.hpp>

#include <vector>
#include <cstdint>
#include <cstddef>

int
main()
{
	std::vector<std::size_t> storage{ 0, 1 };
	bitsy::bit_view<ztd::span<const std::size_t>> b(storage);
	auto ref = *b.begin();
	ref      = true;

	return 0;
}
