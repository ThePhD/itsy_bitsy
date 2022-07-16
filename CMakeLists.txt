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
cmake_minimum_required(VERSION 3.20.0)

# # Project kickstart
# Includes a bunch of basic flags and utilities shared across projects
# See more at the github repository link below
include(FetchContent)
FetchContent_Declare(ztd.cmake
	GIT_REPOSITORY https://github.com/soasis/cmake
	GIT_TAG main)
FetchContent_MakeAvailable(ztd.cmake)
set(CMAKE_PROJECT_INCLUDE ${ZTD_CMAKE_PROJECT_PRELUDE})

# # Project declaration
# informs about the project, gives a description, version and MOST IMPORTANTLY
# the languages the project is going to use. Required.
project(itsy.bitsy
	VERSION 2.0.0
	DESCRIPTION "Standard bit utilities to supplement the C and C++ standard libraries."
	LANGUAGES C CXX)

# # Pre-dependencies
# this is for all the deps we may or may not need before-hand to make things right
if(ITSY_BITSY_READTHEDOCS)
	# ReadTheDocs seems unable to handle the include at the project level: something must be going wrong?
	include(CheckCXXCompilerFlag)
	include(CheckCCompilerFlag)
	include(CheckIPOSupported)
	include(CMakePackageConfigHelpers)
	include(CMakeDependentOption)
	include(CMakePrintHelpers)
	include(GNUInstallDirs)
	include(FeatureSummary)
	include(FetchContent)
	include(CTest)
endif()

# # Top Level Directories
# Check if this is the top-level project or not
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(ITSY_BITSY_IS_TOP_LEVEL_PROJECT ON)
else()
    set(ITSY_BITSY_IS_TOP_LEVEL_PROJECT OFF)
endif()

# Modify bad flags / change defaults if we are the top level
if(ITSY_BITSY_IS_TOP_LEVEL_PROJECT)
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/bin")
	else()
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/bin")
	endif()

	if(NOT DEFINED CMAKE_CXX_STANDARD)
		set(CMAKE_CXX_STANDARD 17)
	endif()

	if(NOT DEFINED CMAKE_C_STANDARD)
		set(CMAKE_C_STANDARD 23)
	endif()

	if(ZTD_CUNEICODE_BENCHMARKS OR ZTD_CUNEICODE_EXAMPLES OR ZTD_CUNEICODE_TESTS OR ZTD_CUNEICODE_SCRATCH)
		# normal flags
		check_compiler_flag(disable-permissive MSVC /permissive- GCC -pedantic)

		# Warning flags
		check_compiler_flag(warn-pedantic MSVC /permissive- GCC -pedantic)
		check_compiler_flag(warn-all MSVC /W4 GCC -Wall)
		check_compiler_flag(warn-errors MSVC /WX GCC -Werror)
		check_compiler_flag(warn-extra GCC -Wextra Clang -Wextra)
		check_compiler_flag(utf8-literal-encoding MSVC /execution-charset:utf-8 GCC -fexec-charset=utf-8)
		check_compiler_flag(utf8-source-encoding MSVC /source-charset:utf-8 GCC -finput-charset=utf-8)
		check_compiler_flag(extra-constexpr-depth MSVC /constexpr:depth2147483647 GCC -fconstexpr-depth=2147483647 Clang -fconstexpr-depth=2147483647)
		check_compiler_flag(extra-constexpr-steps MSVC /constexpr:steps2147483647 GCC -fconstexpr-ops-limit=2147483647 Clang -fconstexpr-steps=2147483647)
		check_compiler_flag(template-debugging-mode GCC -ftemplate-backtrace-limit=0)
	endif()
endif()

# # Options
option(ITSY_BITSY_SINGLE "Enable build of tests" ON)
option(ITSY_BITSY_TESTS "Enable build of tests" ${BUILD_TESTING})
option(ITSY_BITSY_BENCHMARKS "Enable build of benchmarks" OFF)
option(ITSY_BITSY_EXAMPLES "Enable build of examples" OFF)

# # Dependencies
# ztd.idk
FetchContent_Declare(ztd.idk
	GIT_REPOSITORY https://github.com/soasis/idk.git
	GIT_TAG main)
FetchContent_MakeAvailable(ztd.idk)

# # itsy.bitsy Target
# Build Target
file(GLOB_RECURSE itsy-bitsy-sources
	LIST_DIRECTORIES false
	CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/itsy/*)

add_library(itsy.bitsy INTERFACE)
add_library(itsy::bitsy ALIAS itsy.bitsy)
target_link_libraries(itsy.bitsy
	INTERFACE
	ztd::idk)
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
