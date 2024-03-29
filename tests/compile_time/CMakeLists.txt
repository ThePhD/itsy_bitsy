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
	PRIVATE itsy::bitsy ${CMAKE_DL_LIBS})
target_include_directories(itsy_bitsy.tests.compilation
	PRIVATE
	../include
	../../vendor/span-lite/include
	../../vendor/range-v3/include)
target_compile_definitions(itsy_bitsy.tests.compilation PRIVATE
	ITSY_BITSY_USE_RANGEV3_SPAN=1
	ITSY_BITSY_USE_NONSTD_SPAN=0)
if (MSVC)
	target_compile_options(itsy_bitsy.tests.compilation
		PRIVATE 
		/std:c++17 
		/EHsc 
		/utf-8
		/permissive-
	)
else()
	target_compile_options(itsy_bitsy.tests.compilation
		PRIVATE -std=c++17
		-Wno-unknown-warning -Wno-unknown-warning-option
		-Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors)
endif()

add_test(NAME itsy_bitsy.tests.compilation COMMAND itsy_bitsy.tests.compilation)

# # Single inclusion tests
add_subdirectory(single)
