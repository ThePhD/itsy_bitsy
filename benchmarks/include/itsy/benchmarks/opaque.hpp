// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#pragma once

#ifndef ITSY_BITSY_DETAIL_OPAQUE_HPP
#define ITSY_BITSY_DETAIL_OPAQUE_HPP 1

#include <cstddef>

namespace bitsy
{
	namespace benchmarks
	{
		std::size_t
		opaque_benchmark_loop_limit();

		bool
		opaque_true();

		bool
		opaque_false();
	} // namespace benchmarks
} // namespace bitsy

#endif // ITSY_BITSY_DETAIL_OPAQUE_HPP
