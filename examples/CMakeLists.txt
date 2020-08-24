#  Copyright ⓒ 2018-2019 ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

# # Examples
function (make_example example_source_name itsy_bitsy_target target_suffix)
	set(example_source_file source/${example_source_name})
	if (NOT TARGET ${itsy_bitsy_target})
		return()
	endif()
	set(example_target itsy.bitsy.example.${example_source_name}${target_suffix})
	add_executable(${example_target} ${example_source_file})
	if (MSVC)
		target_compile_options(${example_target}
			PRIVATE 
			/std:c++17
			/EHsc 
			/utf-8
			/permissive-
			/W4
		)
	else()
		target_compile_options(${example_target}
			PRIVATE -std=c++17 -Wpedantic -Wall -Werror)
	endif()
	target_compile_definitions(${example_target} PRIVATE
		__STDC_WANT_LIB_EXT1__=1
		ITSY_BITSY_USE_RANGEV3_SPAN=1
		ITSY_BITSY_USE_NONSTD_SPAN=0)
	target_link_libraries(${example_target}
		PRIVATE
		${itsy_bitsy_target}
	)
	target_include_directories(${example_target} PRIVATE
		include
	)
	target_include_directories(${example_target} SYSTEM PRIVATE
		../vendor/span-lite/include
		../vendor/range-v3/include)
	if (ITSY_BITSY_TESTS)
		add_test(NAME ${example_target} COMMAND ${example_target})
	endif()
endfunction()

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
	make_example(${example_source_name} itsy::bitsy "")
	if (ITSY_BITSY_SINGLE)
		make_example(${example_source_name} itsy::bitsy::single ".single")
	endif()
endforeach()
