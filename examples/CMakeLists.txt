#  Copyright ⓒ 2018-2019 ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

# # Examples
function (make_example example_source_file itsy_bitsy_target target_suffix)
	if (NOT TARGET ${itsy_bitsy_target})
		return()
	endif()
	cmake_path(GET example_source_file STEM LAST_ONLY example_source_name)
	set(example_target itsy.bitsy.example.${example_source_name}${target_suffix})
	add_executable(${example_target} ${example_source_file})
	target_compile_options(${example_target}
		PRIVATE 
		${--utf8-literal-encoding}
		${--utf8-source-encoding}
		${--disable-permissive}
		${--warn-pedantic}
		${--warn-all}
		${--warn-extra}
		${--warn-errors}
	)
	target_compile_definitions(${example_target} PRIVATE
		__STDC_WANT_LIB_EXT1__=1)
	target_link_libraries(${example_target}
		PRIVATE
		ztd::idk
		${itsy_bitsy_target}
	)
	target_include_directories(${example_target} PRIVATE
		include
	)
	if (ITSY_BITSY_TESTS)
		add_test(NAME ${example_target} COMMAND ${example_target})
	endif()
endfunction()

file(GLOB_RECURSE itsy.bitsy.example.sources
	CONFIGURE_DEPENDS
	source/*.cpp)

foreach (example_source_name ${itsy.bitsy.example.sources})
	make_example(${example_source_name} itsy::bitsy "")
	if (ITSY_BITSY_SINGLE)
		make_example(${example_source_name} itsy::bitsy::single ".single")
	endif()
endforeach()
