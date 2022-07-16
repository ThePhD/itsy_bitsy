# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

# # # # itsy.bitsy, single
# # # Required minimum version statement
cmake_minimum_required(VERSION 3.20.0)

# # # itsy.bitsy single generation header
# generate the single header if we can find the python3 interpreter
find_package(PythonInterp 3)

if (NOT PYTHONINTERP_FOUND)
	message(FATAL_ERROR "itsy.bitsy single header cannot be generated as python 3 has not been found: install or set the python 3 interpreter to generate the single header")
endif()

# to generate, need all of the existing header files
file(GLOB_RECURSE itsy.bitsy.generated_header_sources LIST_DIRECTORIES false CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../include/**/*.*)
add_custom_command(
	COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/include/itsy"
	COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/single.py" --input "${CMAKE_CURRENT_SOURCE_DIR}/../include" --output "${CMAKE_CURRENT_BINARY_DIR}/include/itsy/bitsy.hpp" "${CMAKE_CURRENT_BINARY_DIR}/include/itsy/forward.hpp"
	DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/single.py" "${itsy.bitsy.generated_header_sources}"
	OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/itsy/bitsy.hpp" "${CMAKE_CURRENT_BINARY_DIR}/include/itsy/forward.hpp")
add_custom_target(itsy.bitsy.single_header_generator ALL
	DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/single.py"
	"${CMAKE_CURRENT_BINARY_DIR}/include/itsy/bitsy.hpp" "${CMAKE_CURRENT_BINARY_DIR}/include/itsy/forward.hpp" 
	"${itsy.bitsy.generated_header_sources}")

# # # itsy.bitsy generated single header library
add_library(itsy.bitsy.single INTERFACE)
add_library(itsy::bitsy::single ALIAS itsy.bitsy.single)
set_target_properties(itsy.bitsy.single
	PROPERTIES
	EXPORT_NAME itsy::bitsy::single
	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/include")
add_dependencies(itsy.bitsy.single itsy.bitsy.single_header_generator)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/itsy/bitsy.hpp" "${CMAKE_CURRENT_BINARY_DIR}/include/itsy/forward.hpp"
	DESTINATION include/itsy/single/itsy)
