# # itsy_bitsy


cmake_minimum_required(VERSION 3.12.0)

# # Project declaration
# informs about the project, gives a description, version and MOST IMPORTANTLY
# the languages the project is going to use. Required.
project(itsy_bitsy VERSION 1.0.0 DESCRIPTION "Standard Unicode utilities to supplement the C and C++ standard libraries." LANGUAGES C CXX)

# # Options
option(ITSY_BITSY_TESTS "Enable build of tests" OFF)
option(ITSY_BITSY_BENCHMARKS "Enable build of benchmarks" OFF)

if (ITSY_BITSY_TESTS OR ITSY_BITSY_BENCHMARKS)
	# # # Top-Level Directories
	if (CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/bin")
	else()
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/bin")
	endif()
endif()


set(itsy_bitsy_sources
	"${CMAKE_CURRENT_SOURCE_DIR}/include/itsy/detail/bit_iterator.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/itsy/detail/bit_view.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/itsy/detail/dynamic_bitset.h"

	"${CMAKE_CURRENT_SOURCE_DIR}/include/itsy/bit_iterator.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/itsy/bit_view.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/itsy/dynamic_bitset.hpp"
)

add_library(itsy_bitsy INTERFACE)
target_sources(itsy_bitsy INTERFACE ${itsy_bitsy_sources})
add_library(itsy::bitsy ALIAS itsy_bitsy)
target_include_directories(itsy_bitsy INTERFACE 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
	$<INSTALL_INTERFACE:include>
)

# # Benchmarks, Tests, Examples
if (ITSY_BITSY_TESTS OR ITSY_BITSY_BENCHMARKS)
	if (MSVC)
		string(REGEX REPLACE "/W[0-4]" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
		string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	endif()
endif()
if (ITSY_BITSY_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif(ITSY_BITSY_TESTS)
if (ITSY_BITSY_BENCHMARKS)
	add_subdirectory(benchmarks)
endif(ITSY_BITSY_BENCHMARKS)
