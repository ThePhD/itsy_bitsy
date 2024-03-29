# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.


function (make_run_time_tests itsy_bitsy_target target_suffix)
	if (NOT TARGET ${itsy_bitsy_target})
		return()
	endif()
	file(GLOB_RECURSE itsy-bitsy-tests-run_time-sources CONFIGURE_DEPENDS source/**)
	set(test-target-name itsy.bitsy.tests.run_time${target_suffix})
	add_executable(${test-target-name} ${itsy-bitsy-tests-run_time-sources})
	set_target_properties(${test-target-name} PROPERTIES 
		VERSION ${PROJECT_VERSION}
	)
	target_include_directories(${test-target-name}
		PRIVATE
		../include
	)
	target_link_libraries(${test-target-name}
		PRIVATE
		ztd::idk
		Catch2::Catch2
		${itsy_bitsy_target}
		${CMAKE_DL_LIBS}
	)
	target_compile_options(${test-target-name} PRIVATE 
		${--utf8-literal-encoding}
		${--utf8-source-encoding}
		${--disable-permissive}
		${--warn-pedantic}
		${--warn-all}
		${--warn-extra}
		${--warn-errors}
	)

	add_test(NAME ${test-target-name} COMMAND itsy.bitsy.tests.run_time)
endfunction()

make_run_time_tests(itsy::bitsy "")
if (ITSY_BITSY_SINGLE)
	make_run_time_tests(itsy::bitsy::single ".single")
endif()
