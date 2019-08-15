
set(itsy_bitsy_tests_sources
	"source/main.cpp"

	"source/bit_detail.shift_and_preserve.cpp"

	"source/bit_iterator.cpp"

	"source/bit_view.cpp"
	"source/bit_view.subrange.cpp"
	"source/bit_view.extents.cpp"
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


add_executable(itsy_bitsy_tests ${itsy_bitsy_tests_sources})
set_target_properties(itsy_bitsy_tests PROPERTIES 
	VERSION ${PROJECT_VERSION}
)
target_include_directories(itsy_bitsy_tests PRIVATE 
	../include
	../../vendor/range-v3/include
)
target_link_libraries(itsy_bitsy_tests 
	itsy::bitsy
	${CMAKE_DL_LIBS}
)
if (MSVC)
	target_compile_options(itsy_bitsy_tests PRIVATE 
		/std:c++latest
		/EHsc 
		/utf-8
		/experimental:preprocessor
		/permissive-
	)
else()
	target_compile_options(itsy_bitsy_tests PRIVATE 
		-std=c++2a
		-Wno-unknown-warning -Wno-unknown-warning-option
		-Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors
	)
endif()


add_test(NAME itsy_bitsy_tests COMMAND itsy_bitsy_tests)
