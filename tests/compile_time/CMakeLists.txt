# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

file(GLOB_RECURSE itsy.bitsy.tests.compilation.sources CONFIGURE_DEPENDS source/*.cpp)
source_group(compile_test_sources FILES ${itsy.bitsy.tests.compilation.sources})

add_executable(itsy_bitsy.tests.compilation ${itsy.bitsy.tests.compilation.sources})
set_target_properties(itsy_bitsy.tests.compilation
	PROPERTIES
	OUTPUT_NAME itsy_bitsy.tests.compilation
	EXPORT_NAME itsy::bitsy.compilation.test)
target_link_libraries(itsy_bitsy.tests.compilation 
	PRIVATE
	itsy::bitsy
	ztd::idk
	${CMAKE_DL_LIBS})

add_test(NAME itsy_bitsy.tests.compilation COMMAND itsy_bitsy.tests.compilation)

# # Single inclusion tests
add_subdirectory(single)
