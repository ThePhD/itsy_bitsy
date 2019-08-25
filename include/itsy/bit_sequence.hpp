#pragma once

#ifndef ITSY_BITSY_BIT_SEQUENCE_HPP
#define ITSY_BITSY_BIT_SEQUENCE_HPP

#include <itsy/version.hpp>

#include <itsy/bit_operations.hpp>
#include <itsy/bit_iterator.hpp>
#include <itsy/bit_view.hpp>

#include <itsy/detail/bit_sequence.hpp>

namespace bitsy
{
	template<typename C>
	using basic_bit_sequence = ITSY_BITSY_DETAIL_NAMESPACE::__basic_bit_sequence<C>;

} // namespace bitsy

#endif // ITSY_BITSY_BIT_SEQUENCE_HPP
