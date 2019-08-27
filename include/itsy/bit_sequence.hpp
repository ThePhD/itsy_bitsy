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
	using bit_sequence = ITSY_BITSY_DETAIL_NAMESPACE::__bit_sequence<C>;

} // namespace bitsy

#endif // ITSY_BITSY_BIT_SEQUENCE_HPP
