# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

file(GLOB_RECURSE itsy.bitsy.tests.compilation.single.sources CONFIGURE_DEPENDS source/*.cpp)
source_group(compile_test_sources_single FILES ${itsy.bitsy.tests.compilation.single.sources})

add_executable(itsy_bitsy.tests.compilation.single ${itsy.bitsy.tests.compilation.single.sources})
set_target_properties(itsy_bitsy.tests.compilation.single
	PROPERTIES
	OUTPUT_NAME itsy_bitsy.tests.compilation.single
	EXPORT_NAME itsy::bitsy.compilation.test.single)
target_link_libraries(itsy_bitsy.tests.compilation.single
	PRIVATE itsy::bitsy ${CMAKE_DL_LIBS})
target_include_directories(itsy_bitsy.tests.compilation.single
	PRIVATE 
	../include
	../../vendor/range-v3/include
)

if (MSVC)
	target_compile_options(itsy_bitsy.tests.compilation.single
		PRIVATE 
		/std:c++latest 
		/EHsc 
		/utf-8
		/permissive-
	)
else()
	target_compile_options(itsy_bitsy.tests.compilation.single
		PRIVATE -std=c++2a
		-Wno-unknown-warning -Wno-unknown-warning-option
		-Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors)
endif()

add_test(NAME itsy_bitsy.tests.compilation.single COMMAND itsy_bitsy.tests.compilation.single)
