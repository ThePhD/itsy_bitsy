#  Copyright ⓒ 2018-2019 ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

# # Examples
set(itsy.bitsy.example.sources
	"bit_iterator.cpp"
	"bit_sequence.cpp"
	"bit_sequence.in_place.construct.cpp"
	"bit_view.constexpr.cpp"
	"bit_view.cpp"
	"bit_view.immutable.cpp"
	"dynamic_bitset.alias.cpp"
)

foreach (example_source_name ${itsy.bitsy.example.sources})
	set(example_source_file source/${example_source_name})
	set(example_target itsy.bitsy.example.${example_source_name})
	add_executable(${example_target} ${example_source_file})
	set_target_properties(${example_target} PROPERTIES
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED TRUE
		CXX_EXTENSIONS FALSE
	)
	if (MSVC)
		target_compile_options(${example_target}
			PRIVATE 
			/std:c++latest
			/EHsc 
			/utf-8
			/experimental:preprocessor
			/permissive-
			/W4
		)
	else()
		target_compile_options(${example_target}
			PRIVATE -Wpedantic -Wall -Werror)
	endif()
	target_compile_definitions(${example_target} PRIVATE __STDC_WANT_LIB_EXT1__=1)
	target_link_libraries(${example_target}
		PRIVATE 
		
		itsy::bitsy
	)
	target_include_directories(${example_target} PRIVATE
		"include"
	)
	if (ITSY_BITSY_TESTS)
		add_test(NAME ${example_target} COMMAND ${example_target})
	endif()
endforeach()
