#pragma once

#ifndef BITSY_BIT_VIEW_HPP
#define BITSY_BIT_VIEW_HPP

#include <itsy/version.hpp>

#if BITSY_SOURCE_LIBSTDCXX
#include <bits/bit_view.h>
#elif BITSY_SOURCE_LIBCXX
#include <bit_view.h>
#else
#include <itsy/detail/bit_view.h>
#endif

#include <itsy/bit_iterator.hpp>

namespace bitsy
{
	template<typename Range>
	using word_bit_extents = __BIT_STRUCTURES_NAMESPACE::__word_bit_extents<Range>;

	template<typename Range>
	using dynamic_bit_extents_for = __BIT_STRUCTURES_NAMESPACE::__dynamic_bit_extents_for<Range>;

	template<std::size_t first, std::size_t last>
	using static_bit_extents = __BIT_STRUCTURES_NAMESPACE::__static_bit_extents<first, last>;

	using dynamic_bit_extents = __BIT_STRUCTURES_NAMESPACE::__dynamic_bit_extents;

	template<typename R, typename Extents = word_bit_extents<R>>
	using bit_view = __BIT_STRUCTURES_NAMESPACE::__bit_view<R, Extents>;
} // namespace bitsy

#endif // BITSY_BIT_VIEW_HPP
