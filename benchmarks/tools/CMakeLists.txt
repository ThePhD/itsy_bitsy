# # itsy_bitsy benchmarking tools

# minimum required version information
cmake_minimum_required(VERSION 3.20.0)


# project declaration
project(itsy.bitsy.benchmark.tools VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "A project to generate graphs and data for checking performance and correctness of bit utilities.")

# # Dependencies
# Standard Dependencies
find_package(Python3)
# Needed utilities
include(identify_stdlib)

# # Setup
identify_stdlib(current_stdlib)
message(STATUS "itsy.bitsy.benchmark.tools: benchmarks will be reported for ${current_stdlib} ...")

set(ITSY_BITSY_BENCHMARKS_RESULTS_GRAPH_SOURCEFILE "${CMAKE_CURRENT_SOURCE_DIR}/sources.json")
set(ITSY_BITSY_BENCHMARKS_RESULTS_GRAPH_INPUTFILE "${CMAKE_SOURCE_DIR}/benchmarks/results/fresh/sources.json")
set(ITSY_BITSY_BENCHMARKS_RESULTS_OUTFILE "${CMAKE_SOURCE_DIR}/benchmarks/results/fresh/${current_stdlib}.itsy.bitsy.benchmarks.json")
set(ITSY_BITSY_BENCHMARKS_RESULTS_OUTDIR "${CMAKE_SOURCE_DIR}/benchmarks/results/fresh")
set(ITSY_BITSY_BENCHMARKS_ANALYSIS_OUTDIR "${CMAKE_SOURCE_DIR}/benchmarks/results/fresh")
option(ITSY_BITSY_BENCHMARKS_REPETITIONS "Number of repetitions to perform. Each repetition has a number of iterations: higher means a lot more time is spent benchmarking." 15)

# # Commands and Targets
file(GENERATE OUTPUT "${ITSY_BITSY_BENCHMARKS_RESULTS_GRAPH_INPUTFILE}"
	INPUT "${ITSY_BITSY_BENCHMARKS_RESULTS_GRAPH_SOURCEFILE}")

add_custom_command(
	OUTPUT "${ITSY_BITSY_BENCHMARKS_RESULTS_OUTFILE}"
	COMMAND itsy.bitsy.benchmarks
		"--benchmark_out=${ITSY_BITSY_BENCHMARKS_RESULTS_OUTFILE}" 
		"--benchmark_out_format=json" 
		"--benchmark_repetitions=${ITSY_BITSY_BENCHMARKS_REPETITIONS}"
	DEPENDS itsy.bitsy.benchmarks
	COMMENT "Executing Benchmarks and outputting to '${ITSY_BITSY_BENCHMARKS_RESULTS_OUTFILE}'"
)

add_custom_target(itsy.bitsy.benchmarks.data_generator
	DEPENDS "${ITSY_BITSY_BENCHMARKS_RESULTS_OUTFILE}"
)

if (Python3_Interpreter_FOUND)
	add_custom_target(itsy.bitsy.benchmarks.graphs_generator
		COMMAND ${Python3_EXECUTABLE} "-m" "${CMAKE_SOURCE_DIR}/benchmarks/tools/generate_graphs" 
			"--source=${ITSY_BITSY_BENCHMARKS_RESULTS_OUTFILE}"
			"--output=${ITSY_BITSY_BENCHMARKS_ANALYSIS_OUTDIR}"
		DEPENDS itsy.bitsy.benchmarks itsy.bitsy.benchmarks.data_generator "${ITSY_BITSY_BENCHMARKS_RESULTS_GRAPH_INPUTFILE}"
		COMMENT "Graphing '${ITSY_BITSY_BENCHMARKS_RESULTS_OUTFILE}' data to '${ITSY_BITSY_BENCHMARKS_RESULTS_OUTDIR}'"
	)
endif()
