// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy/benchmarks/opaque.hpp>

namespace bitsy
{
	namespace benchmarks
	{
		std::size_t
		opaque_benchmark_loop_limit()
		{
			return 400000;
		}

		bool
		opaque_true()
		{
			return true;
		}

		bool
		opaque_false()
		{
			return false;
		}
	} // namespace benchmarks
} // namespace bitsy
