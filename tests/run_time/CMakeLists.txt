# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

file(GLOB_RECURSE itsy.bitsy.tests.run_time.sources CONFIGURE_DEPENDS source/**)

add_executable(itsy.bitsy.tests.run_time ${itsy.bitsy.tests.run_time.sources})
set_target_properties(itsy.bitsy.tests.run_time PROPERTIES 
	VERSION ${PROJECT_VERSION}
)
target_include_directories(itsy.bitsy.tests.run_time PRIVATE 
	../include
	../../vendor/range-v3/include
	../../vendor/catch2/include
)
target_link_libraries(itsy.bitsy.tests.run_time
	PRIVATE
	itsy::bitsy
	${CMAKE_DL_LIBS}
)
if (MSVC)
	target_compile_definitions(itsy.bitsy.tests.run_time PRIVATE
		_SILENCE_CLANG_CONCEPTS_MESSAGE
	)
	target_compile_options(itsy.bitsy.tests.run_time PRIVATE 
		/std:c++latest
		/EHsc 
		/utf-8
		$<$<NOT:$<BOOL:${ITSY_BITSY_CLANG_CL}>>:/experimental:preprocessor>
		/permissive-
		/W4
	)
else()
	target_compile_options(itsy.bitsy.tests.run_time PRIVATE 
		-std=c++2a
		-Wno-unknown-warning -Wno-unknown-warning-option
		-Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors
	)
endif()


add_test(NAME itsy.bitsy.tests.run_time COMMAND itsy.bitsy.tests.run_time)
