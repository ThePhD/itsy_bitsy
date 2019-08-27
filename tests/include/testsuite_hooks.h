// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

// shim file to simulate libstdc++ tests...

#include <catch2/catch.hpp>

#define VERIFY(...) REQUIRE(__VA_ARGS__)
#define VERIFY_FALSE(...) REQUIRE_FALSE(__VA_ARGS__)
