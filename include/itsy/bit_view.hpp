#pragma once

#ifndef ITSY_BITSY_BIT_VIEW_HPP
#define ITSY_BITSY_BIT_VIEW_HPP

#include <itsy/version.hpp>
#include <itsy/bit_iterator.hpp>

#include <itsy/detail/bit_view.hpp>

namespace bitsy
{
	template<typename Range>
	using word_bit_extents = ITSY_BITSY_DETAIL_NAMESPACE::__word_bit_extents<Range>;

	template<typename Range>
	using dynamic_bit_extents_for = ITSY_BITSY_DETAIL_NAMESPACE::__dynamic_bit_extents_for<Range>;

	template<std::size_t first, std::size_t last>
	using static_bit_extents = ITSY_BITSY_DETAIL_NAMESPACE::__static_bit_extents<first, last>;

	using dynamic_bit_extents = ITSY_BITSY_DETAIL_NAMESPACE::__dynamic_bit_extents;

	template<typename R, typename Extents = word_bit_extents<R>>
	using bit_view = ITSY_BITSY_DETAIL_NAMESPACE::__bit_view<R, Extents>;
} // namespace bitsy

#endif // ITSY_BITSY_BIT_VIEW_HPP
