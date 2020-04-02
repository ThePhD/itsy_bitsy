# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

# Primary CMake File

# # Mimum required
cmake_minimum_required(VERSION 3.12.0)

# # Project declaration
# informs about the project, gives a description, version and MOST IMPORTANTLY
# the languages the project is going to use. Required.
project(itsy.bitsy VERSION 1.0.0 DESCRIPTION "Standard bit utilities to supplement the C and C++ standard libraries." LANGUAGES C CXX)

# # Pre-dependencies
# this is for all the deps we may or may not need before-hand to make things right
include(CTest)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# # Options
option(ITSY_BITSY_SINGLE "Enable build of tests" ON)
option(ITSY_BITSY_TESTS "Enable build of tests" ${BUILD_TESTING})
option(ITSY_BITSY_BENCHMARKS "Enable build of benchmarks" OFF)

# # Top Level Directories
# Check if this is the top-level project or not
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(ITSY_BITSY_IS_TOP_LEVEL_PROJECT true)
else()
    set(ITSY_BITSY_IS_TOP_LEVEL_PROJECT false)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (ITSY_BITSY_IS_TOP_LEVEL_PROJECT)
	# Sane directories for easy top-level testing
	if (CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/bin")
	else()
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/bin")
	endif()
	# Sane warning defaults
	# done for us in very latest CMake (as of August 16)
	# but not before, so.
	if (MSVC)
		string(REGEX REPLACE "/W[0-4]" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
		string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	endif()
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC")
		set(ITSY_BITSY_CLANG_CL ON)
	else()
		set(ITSY_BITSY_CLANG_CL OFF)
	endif()
	if (ITSY_BITSY_TESTS)
		enable_testing()
	endif()
endif()


# # itsy.bitsy Target
# Build Target
file(GLOB_RECURSE itsy-bitsy-sources
	LIST_DIRECTORIES false
	CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/itsy/*)

add_library(itsy.bitsy INTERFACE)
add_library(itsy::bitsy ALIAS itsy.bitsy)
target_include_directories(itsy.bitsy INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# # Install Target
# Version configurations
configure_package_config_file(
	cmake/itsy.bitsy-config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/itsy.bitsy-config.cmake"
	INSTALL_DESTINATION lib/cmake/itsy.bitsy
	NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/itsy.bitsy-config-version.cmake"
	COMPATIBILITY AnyNewerVersion)

export(TARGETS itsy.bitsy FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/itsy.bitsy-targets.cmake")

install(TARGETS itsy.bitsy
	EXPORT itsy.bitsy)

install(EXPORT itsy.bitsy
	FILE itsy.bitsy-targets.cmake
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/itsy.bitsy")

install(DIRECTORY include/itsy
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/itsy.bitsy-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/itsy.bitsy-config-version.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/itsy.bitsy")

# pkg-config support, except on Windows
if(NOT WIN32 OR NOT CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
	set(PKGCONFIG_INSTALL_DIR
		"${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig"
		CACHE PATH "Path where itsy.bitsy.pc is installed")
	
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/itsy.bitsy.pc.in" "${CMAKE_CURRENT_BINARY_DIR}/itsy.bitsy.pc" @ONLY)
	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/itsy.bitsy.pc" DESTINATION "${PKGCONFIG_INSTALL_DIR}")
endif()

if (ITSY_BITSY_SINGLE)
	add_subdirectory(single)
endif()

# # Benchmarks, Tests, Examples
if (ITSY_BITSY_TESTS)
	add_subdirectory(tests)
endif()
if (ITSY_BITSY_EXAMPLES)
	add_subdirectory(examples)
endif()
if (ITSY_BITSY_BENCHMARKS)
	add_subdirectory(benchmarks)
endif()
if (ITSY_BITSY_DOCS)
	add_subdirectory(docs)
endif()
