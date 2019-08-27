// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#define CATCH_CONFIG_RUNNER
#include <testsuite_hooks.h>

int
main(int argc, char* argv[])
{
	int result = Catch::Session().run(argc, argv);
	return result;
}
