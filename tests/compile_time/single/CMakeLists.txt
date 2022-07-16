# itsy.bitsy
#
#  Copyright ⓒ 2019-present ThePhD.
#
#  Distributed under the Boost Software License, Version 1.0. (See
#  accompanying file LICENSE or copy at
#  http://www.boost.org/LICENSE_1_0.txt)
#
#  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

file(GLOB_RECURSE itsy.bitsy.tests.compilation.single.sources CONFIGURE_DEPENDS source/*.cpp)
source_group(compile_test_sources_single FILES ${itsy.bitsy.tests.compilation.single.sources})

add_executable(itsy_bitsy.tests.compilation.single ${itsy.bitsy.tests.compilation.single.sources})
set_target_properties(itsy_bitsy.tests.compilation.single
	PROPERTIES
	OUTPUT_NAME itsy_bitsy.tests.compilation.single
	EXPORT_NAME itsy::bitsy.compilation.test.single)
target_link_libraries(itsy_bitsy.tests.compilation.single
	PRIVATE
	itsy::bitsy
	ztd::idk
	${CMAKE_DL_LIBS})

target_compile_options(itsy_bitsy.tests.compilation.single
	PRIVATE
	${--utf8-literal-encoding}
	${--utf8-source-encoding}
	${--disable-permissive}
	${--warn-pedantic}
	${--warn-all}
	${--warn-extra}
	${--warn-errors})

add_test(NAME itsy_bitsy.tests.compilation.single COMMAND itsy_bitsy.tests.compilation.single)
