# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

set(itsy-bitsy-tests-fail-sources
	"bit_view.const.modify.cpp"
	"bit_view.const.modify.auto.cpp"
)

foreach (test_name ${itsy-bitsy-tests-fail-sources})
	set(test-file source/${test_name})
	set(test-target itsy_bitsy.tests.fail.${test_name})
	add_executable(${test-target} ${test-file})
	if (MSVC)
		target_compile_options(${test-target} 
			PRIVATE 
			/std:c++17
			/EHsc 
			/utf-8
			/permissive-
		)
	else()
		target_compile_options(${test-target} 
			PRIVATE -std=c++17 
			-Wno-unknown-warning -Wno-unknown-warning-option
		  -Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors)
	endif()
	set_target_properties(${test-target} 
		PROPERTIES 
		EXCLUDE_FROM_ALL TRUE
		EXCLUDE_FROM_DEFAULT_BUILD TRUE
	)
	target_include_directories(${test-target}
		PRIVATE 
		../include
		../../vendor/span-lite/include
	)
	target_link_libraries(${test-target}
		PRIVATE 
		itsy::bitsy
		${CMAKE_DL_LIBS}
	)
	target_compile_definitions(${test-target} PRIVATE
		ITSY_BITSY_USE_RANGEV3_SPAN=1
		ITSY_BITSY_USE_NONSTD_SPAN=0)
	add_test(NAME ${test-target} COMMAND cmake --build . --target ${test-target}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
	set_tests_properties(${test-target}
		PROPERTIES 
		WILL_FAIL true)
endforeach()