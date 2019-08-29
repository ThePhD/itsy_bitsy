// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#include <itsy/bit_view.hpp>

#include <vector>
#include <cstdint>
#include <cstddef>
#include <span>

int
main()
{
	std::vector<std::size_t> storage{ 0, 1 };
	bitsy::bit_view<std::span<const std::size_t>> b(storage);
	(*b.begin()) = true;

	return 0;
}