set(itsy_bitsy_scratch_sources
	"source/main.cpp"
)


add_executable(itsy_bitsy_scratch EXCLUDE_FROM_ALL ${itsy_bitsy_scratch_sources})
set_target_properties(itsy_bitsy_scratch PROPERTIES 
	VERSION ${PROJECT_VERSION}
)
target_include_directories(itsy_bitsy_scratch PRIVATE 
	../include
	../../vendor/range-v3/include
)
target_link_libraries(itsy_bitsy_scratch 
	itsy::bitsy
	${CMAKE_DL_LIBS}
)
if (MSVC)
	target_compile_options(itsy_bitsy_scratch PRIVATE 
		/std:c++latest
		/EHsc 
		/utf-8
		/experimental:preprocessor
		/permissive-
	)
else()
	target_compile_options(itsy_bitsy_scratch PRIVATE 
		-std=c++2a
		-Wno-unknown-warning -Wno-unknown-warning-option
		-Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors
	)
endif()
