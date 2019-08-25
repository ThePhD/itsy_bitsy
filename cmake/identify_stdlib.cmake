if(__identify_stdlib_include_guard)
    return()
endif()
set(__identify_stdlib_include_guard TRUE)

function (identify_stdlib STDLIBNAME)
	set(idstl_test_dir "${CMAKE_BINARY_DIR}/identify_stdlib")
	set(idstl_libc++_file "${idstl_test_dir}/test_libc++_file.cpp")
	set(idstl_libstdc++_file "${idstl_test_dir}/test_libstdc++_file.cpp")
	set(idstl_vc++_file "${idstl_test_dir}/test_vc++_file.cpp")

	file(WRITE "${idstl_libc++_file}" 
	[==[
	#include <cstddef>
	#include <ciso646>
	int main (int, char*[]) { 
	#if defined(_LIBCPP_VERSION)
		return 0;
	#else
		return 1;
	#endif
	}
	]==])
	file(WRITE "${idstl_libstdc++_file}" 
	[==[
	#include <cstddef>
	#include <ciso646>
	int main (int, char*[]) { 
	#if defined(__GLIBCXX__)
		return 0;
	#else
		return 1;
	#endif
	}
	]==])
	file(WRITE "${idstl_vc++_file}" 
	[==[
	#include <cstddef>
	#include <ciso646>
	int main (int, char*[]) { 
	#if defined(_STL_LANG) || defined(_YVALS_CORE_H) || defined(_STDEXT)
		return 0;
	#else
		return 1;
	#endif
	}
	]==])

	try_run(is_libc++_run is_libc++_compile "${idstl_test_dir}" "${idstl_libc++_file}"
		CMAKE_FLAGS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}" "CMAKE_C_FLAGS:${CMAKE_C_FLAGS}"
		"CMAKE_C_COMPILER:${CMAKE_C_COMPILER}" "CMAKE_CXX_COMPILER:${CMAKE_CXX_COMPILER}")
	try_run(is_libstdc++_run is_libstdc++_compile "${idstl_test_dir}" "${idstl_libstdc++_file}"
		CMAKE_FLAGS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}" "CMAKE_C_FLAGS:${CMAKE_C_FLAGS}"
		"CMAKE_C_COMPILER:${CMAKE_C_COMPILER}" "CMAKE_CXX_COMPILER:${CMAKE_CXX_COMPILER}")
	try_run(is_vc++_run is_vc++_compile "${idstl_test_dir}" "${idstl_vc++_file}"
		CMAKE_FLAGS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}" "CMAKE_C_FLAGS:${CMAKE_C_FLAGS}"
		"CMAKE_C_COMPILER:${CMAKE_C_COMPILER}" "CMAKE_CXX_COMPILER:${CMAKE_CXX_COMPILER}")

	if (is_libc++_run EQUAL 0)
		set(${STDLIBNAME} libc++ PARENT_SCOPE)
	elseif (is_libstdc++_run EQUAL 0)
		set(${STDLIBNAME} libstdc++ PARENT_SCOPE)
	elseif (is_vc++_run EQUAL 0)
		set(${STDLIBNAME} vc++ PARENT_SCOPE)
	else ()
		set(${STDLIBNAME} unknown PARENT_SCOPE)
	endif()
endfunction()
