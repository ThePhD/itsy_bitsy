// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

int
main(int argc, char* argv[])
{
	int result = Catch::Session().run(argc, argv);
	return result;
}
