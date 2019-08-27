// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

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
