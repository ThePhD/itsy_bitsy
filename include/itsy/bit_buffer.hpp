#pragma once

#ifndef ITSY_BITSY_SMALL_BIT_BUFFER_HPP
#define ITSY_BITSY_SMALL_BIT_BUFFER_HPP

#include <cstddef>
#include <cstdint>

#include <itsy/version.hpp>

#include <itsy/detail/bit_buffer.hpp>

namespace bitsy
{
	template<typename Word, ::std::size_t InlineBufferSize>
	using bit_buffer = ITSY_BITSY_DETAIL_NAMESPACE::__bit_buffer<Word, InlineBufferSize>;
} // namespace bitsy

#endif // ITSY_BITSY_SMALL_BIT_BUFFER_HPP
