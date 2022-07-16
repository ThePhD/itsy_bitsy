# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

# # Fetch dependencies
# Catch2
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.13.7
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(run_time)
add_subdirectory(compile_time)
add_subdirectory(compile_failure)
