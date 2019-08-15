#pragma once

#ifndef BITSY_DETAIL_HPP
#define BITSY_DETAIL_HPP

#include <itsy/version.hpp>

#include <itsy/detail/bit_detail.h>

namespace bitsy
{
	namespace detail
	{

		using __BIT_STRUCTURES_NAMESPACE::__shift_and_preserve;
		using __BIT_STRUCTURES_NAMESPACE::__shift_left_preserve_left;
		using __BIT_STRUCTURES_NAMESPACE::__shift_left_preserve_right;
		using __BIT_STRUCTURES_NAMESPACE::__shift_right_preserve_left;
		using __BIT_STRUCTURES_NAMESPACE::__shift_right_preserve_right;

	} // namespace detail
} // namespace bitsy

#endif // BITSY_DETAIL_HPP