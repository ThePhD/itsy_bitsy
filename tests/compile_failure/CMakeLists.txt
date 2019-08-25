set(itsy.bitsy.tests.fail.sources
	"bit_view.const.modify.cpp"
	"bit_view.const.modify.auto.cpp"
)

foreach (test_name ${itsy.bitsy.tests.fail.sources})
	set(test_file source/${test_name})
	set(test_target itsy_bitsy.tests.fail.${test_name})
	add_executable(${test_target} ${test_file})
	if (MSVC)
		target_compile_options(${test_target} 
			PRIVATE 
			/std:c++latest
			/EHsc 
			/utf-8
			/experimental:preprocessor
			/permissive-
		)
	else()
		target_compile_options(${test_target} 
			PRIVATE -std=c++2a 
			-Wno-unknown-warning -Wno-unknown-warning-option
		  -Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors)
	endif()
	set_target_properties(${test_target} 
		PROPERTIES 
		EXCLUDE_FROM_ALL TRUE
		EXCLUDE_FROM_DEFAULT_BUILD TRUE
	)
	target_include_directories(${test_target}
		PRIVATE 
		../include
		../../vendor/range-v3/include
	)
	target_link_libraries(${test_target}
		PRIVATE 
		itsy::bitsy
		${CMAKE_DL_LIBS}
	)
	add_test(NAME ${test_target} COMMAND cmake --build . --target ${test_target}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
	set_tests_properties(${test_target} 
		PROPERTIES 
		WILL_FAIL true)
endforeach()