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
	add_executable(${test-target} EXCLUDE_FROM_ALL ${test-file})
	target_compile_options(${test-target} 
		PRIVATE 
		${--utf8-literal-encoding}
		${--utf8-source-encoding}
		${--disable-permissive}
		${--warn-pedantic}
		${--warn-all}
		${--warn-extra}
		${--warn-errors}
	)
	target_link_libraries(${test-target}
		PRIVATE 
		itsy::bitsy
		ztd::idk
		${CMAKE_DL_LIBS}
	)
	add_test(NAME ${test-target} COMMAND cmake --build . --target ${test-target}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
	set_tests_properties(${test-target}
		PROPERTIES 
		WILL_FAIL true)
endforeach()
