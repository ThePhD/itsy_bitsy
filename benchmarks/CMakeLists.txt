# # minimum required version information
cmake_minimum_required(VERSION 3.11)

# # project declaration
project(itsy.bitsy.benchmarks VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "A project to benchmark typical operations on dynamic bitsets in the standard library.")

# # Dependencies
# Vendor Dependencies
# Benchmark variables, internal setup
set(BENCHMARK_ENABLE_EXCEPTIONS ON CACHE INTERNAL "Enable the use of exceptions in the benchmark library." FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "Enable testing of the benchmark library." FORCE)
set(BENCHMARK_ENABLE_LTO OFF CACHE INTERNAL "Enable link time optimisation of the benchmark library." FORCE)
set(BENCHMARK_USE_LIBCXX OFF CACHE INTERNAL "Build and test using libc++ as the standard library." FORCE)
set(BENCHMARK_BUILD_32_BITS OFF CACHE INTERNAL "Build a 32 bit version of the library." FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE INTERNAL "Enable installation of benchmark. (Projects embedding benchmark may want to turn this OFF.)" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF CACHE INTERNAL "Allow the downloading and in-tree building of unmet dependencies" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE INTERNAL "Enable building the unit tests which depend on gtest" FORCE)
add_subdirectory(../vendor/benchmark "benchmark")

# # Benchmark Executable
set(itsy.bitsy.benchmarks.sources
	"source/copy_n.cpp"
	"source/copy.cpp"
	"source/count.cpp"
	"source/equal.cpp"
	"source/fill_n.cpp"
	"source/fill.cpp"
	"source/find.cpp"
	"source/is_sorted_until.cpp"
	"source/is_sorted.cpp"
	
	"source/noop.cpp"
	
	"source/main.cpp"
)
add_executable(itsy.bitsy.benchmarks ${itsy.bitsy.benchmarks.sources})
target_include_directories(itsy.bitsy.benchmarks PRIVATE 
	include
	../vendor/range-v3/include
)
target_link_libraries(itsy.bitsy.benchmarks PRIVATE
	itsy::bitsy
	benchmark
	${CMAKE_DL_LIBS}
)
if (MSVC)
	target_compile_options(itsy.bitsy.benchmarks PRIVATE 
		/std:c++latest
		/EHsc 
		/utf-8
		/experimental:preprocessor
		/permissive-
		/W4
	)
else()
	target_compile_options(itsy.bitsy.benchmarks PRIVATE 
		-std=c++2a
		-Wno-unknown-warning -Wno-unknown-warning-option
		-Wall -Werror -Wextra -Wpedantic -pedantic -pedantic-errors
	)
endif()

# # Benchmark Tools
add_subdirectory(tools)