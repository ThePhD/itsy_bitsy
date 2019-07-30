file(GLOB_RECURSE ITSY_BITSY_COMPILATION_TEST_SOURCES source/*.cpp)
source_group(compile_test_sources FILES ${ITSY_BITSY_COMPILATION_TEST_SOURCES})

add_executable(itsy_bitsy.compilation.test ${ITSY_BITSY_COMPILATION_TEST_SOURCES})
set_target_properties(itsy_bitsy.compilation.test
	PROPERTIES
	OUTPUT_NAME itsy_bitsy.compilation.test
	EXPORT_NAME itsy::bitsy.compilation.test)
target_link_libraries(itsy_bitsy.compilation.test 
	PRIVATE itsy::bitsy ${CMAKE_DL_LIBS})
target_include_directories(itsy_bitsy.compilation.test
	PRIVATE 
	../include
	../../vendor/range-v3/include
)

if (MSVC)
	target_compile_options(itsy_bitsy.compilation.test
		PRIVATE 
		/std:c++latest 
		/EHsc 
		/utf-8
		/experimental:preprocessor
		/permissive-
	)
else()
	target_compile_options(itsy_bitsy.compilation.test
		PRIVATE -std=c++2a
		-Wno-unknown-warning -Wno-unknown-warning-option
		-Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors)
endif()

add_test(NAME itsy_bitsy.compilation.test COMMAND itsy_bitsy.compilation.test)
