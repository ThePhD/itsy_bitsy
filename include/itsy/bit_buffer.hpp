#pragma once

#ifndef BITSY_SMALL_BIT_BUFFER_HPP
#define BITSY_SMALL_BIT_BUFFER_HPP

#include <cstddef>
#include <cstdint>

#include <itsy/version.hpp>

#if BITSY_SOURCE_LIBSTDCXX
#include <bits/bit_buffer.h>
#elif BITSY_SOURCE_LIBCXX
#include <bit_buffer.h>
#else
#include <itsy/detail/bit_buffer.h>
#endif


namespace bitsy
{
	template<typename Word, ::std::size_t InlineBufferSize>
	using bit_buffer = __BIT_STRUCTURES_NAMESPACE::__bit_buffer<Word, InlineBufferSize>;
} // namespace bitsy

#endif // BITSY_SMALL_BIT_BUFFER_HPP
