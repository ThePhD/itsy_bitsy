#ifndef ITSY_BITSY_DETAIL_BIT_BUFFER_H
#define ITSY_BITSY_DETAIL_BIT_BUFFER_H 1

#if (defined(_MSC_VER)) || (defined(__cplusplus) && __cplusplus >= 201703L)

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
#else
#include <itsy/detail/bit_iterator.h>
#endif

#include <cstddef>
#include <type_traits>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{

	template<typename __Word, ::std::size_t __Inline_Words,
	  typename __Allocator = std::allocator<__Word>>
	class __bit_buffer
	{
	public:
	private:
		__Allocator __alloc;
		::std::size_t __bit_size;
	};

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_BIT_BUFFER_H
