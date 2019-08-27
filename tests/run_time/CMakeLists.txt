# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See http://www.boost.org/libs/out_ptr/ for documentation.

set(itsy.bitsy.tests.sources
	"source/main.cpp"

	"source/algorithm.cpp"
	"source/algorithm.mutable.cpp"

	"source/bit_operations.cpp"
	"source/bit_operations.detail.shift_and_preserve.cpp"

	"source/bit_iterator.cpp"

	"source/bit_view.cpp"
	"source/bit_view.subrange.cpp"
	"source/bit_view.bounds.cpp"
	"source/bit_view.const.cpp"
	"source/bit_view.flip.set.reset.cpp"

	"source/dynamic_bitset.constructors.cpp"

	"source/dynamic_bitset.push_front.push_back.cpp"

	"source/dynamic_bitset.reference_wrapper.cpp"
	"source/dynamic_bitset.reference_wrapper.signed.cpp"

	"source/dynamic_bitset.insert.cpp"
	"source/dynamic_bitset.insert.signed.cpp"
	"source/dynamic_bitset.insert.erase.clear.cpp"
	"source/dynamic_bitset.insert.erase.clear.signed.cpp"
	"source/dynamic_bitset.insert.erase.clear.bulk.small.cpp"
	"source/dynamic_bitset.insert.erase.clear.bulk.small.signed.cpp"
	"source/dynamic_bitset.insert.erase.clear.bulk.large.cpp"
	"source/dynamic_bitset.insert.erase.clear.bulk.large.signed.cpp"
)


add_executable(itsy.bitsy.tests ${itsy.bitsy.tests.sources})
set_target_properties(itsy.bitsy.tests PROPERTIES 
	VERSION ${PROJECT_VERSION}
)
target_include_directories(itsy.bitsy.tests PRIVATE 
	../include
	../../vendor/range-v3/include
	../../vendor/catch2/include
)
target_link_libraries(itsy.bitsy.tests
	PRIVATE
	itsy::bitsy
	${CMAKE_DL_LIBS}
)
if (MSVC)
	target_compile_options(itsy.bitsy.tests PRIVATE 
		/std:c++latest
		/EHsc 
		/utf-8
		/experimental:preprocessor
		/permissive-
		/W4
	)
else()
	target_compile_options(itsy.bitsy.tests PRIVATE 
		-std=c++2a
		-Wno-unknown-warning -Wno-unknown-warning-option
		-Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors
	)
endif()


add_test(NAME itsy.bitsy.tests COMMAND itsy.bitsy.tests)
