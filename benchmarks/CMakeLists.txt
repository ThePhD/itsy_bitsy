# # minimum required version information
cmake_minimum_required(VERSION 3.11)

# # project declaration
project(itsy.bitsy.benchmarks VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "A project to benchmark typical operations on dynamic bitsets in the standard library.")

# # Fetch dependencies
# Google Benchmark
FetchContent_Declare(
	googlebenchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
)
FetchContent_GetProperties(googlebenchmark)

if(NOT googlebenchmark_POPULATED)
	FetchContent_Populate(googlebenchmark)
	set(BENCHMARK_ENABLE_INSTALL OFF CACHE INTERNAL "")
	set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "")
	set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE INTERNAL "")
	set(BENCHMARK_ENABLE_WERROR OFF CACHE INTERNAL "")
	set(BENCHMARK_FORCE_WERROR OFF CACHE INTERNAL "")
	add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})
endif()

# # Benchmark Executable
file(GLOB_RECURSE itsy.bitsy.benchmarks.sources CONFIGURE_DEPENDS source/**)

add_executable(itsy.bitsy.benchmarks ${itsy.bitsy.benchmarks.sources})
target_include_directories(itsy.bitsy.benchmarks PRIVATE
	include
)
target_link_libraries(itsy.bitsy.benchmarks PRIVATE
	itsy::bitsy
	benchmark
	${CMAKE_DL_LIBS}
)
target_compile_options(itsy.bitsy.benchmarks PRIVATE 
	${--utf8-literal-encoding}
	${--utf8-source-encoding}
	${--disable-permissive}
	${--warn-pedantic}
	${--warn-all}
	${--warn-extra}
	${--warn-errors}
)

# # Benchmark Tools
# add_subdirectory(tools)
