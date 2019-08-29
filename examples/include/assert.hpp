//  Copyright ⓒ 2019-2019 ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#pragma once

#ifndef ITSY_BITSY_EXAMPLES_ASSERT
#define ITSY_BITSY_EXAMPLES_ASSERT

#ifndef NDEBUG

#include <iostream>
#include <cstdlib>

#define ITSY_BITSY_C_ASSERT_MSG(condition, message)                                           \
	(!(condition) ? ((void)(std::cerr << "Assertion `" #condition "` failed in " << __FILE__    \
	                                  << " line " << __LINE__ << ": " << message << std::endl), \
	                  (void)std::abort())                                                       \
	              : (void)0)

#define ITSY_BITSY_C_ASSERT(condition)                                                     \
	(!(condition) ? ((void)(std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
	                                  << " line " << __LINE__ << std::endl),                 \
	                  (void)std::abort())                                                    \
	              : (void)0)

#else

#define ITSY_BITSY_EXAMPLE_ASSERT_MSG(condition, message) \
	(false ? ((void)(condition), (void)(message)) : (void)0)

#define ITSY_BITSY_C_ASSERT(condition) (false ? ((void)(condition)) : (void)0)

#endif // NDEBUG

#endif // ITSY_BITSY_EXAMPLES_ASSERT
