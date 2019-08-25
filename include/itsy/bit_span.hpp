#pragma once

#ifndef ITSY_BITSY_BIT_SPAN_HPP
#define ITSY_BITSY_BIT_SPAN_HPP

#include <itsy/version.hpp>

#include <itsy/bit_view.hpp>

#include <span>

namespace bitsy
{
	template<typename T, typename Extent = word_bit_extents<std::span<T>>>
	using bit_span = bit_view<std::span<T>>;
} // namespace bitsy

#endif // ITSY_BITSY_BIT_SPAN_HPP
