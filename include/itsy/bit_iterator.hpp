// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#pragma once

#ifndef ITSY_BITSY_BIT_ITERATOR_HPP
#define ITSY_BITSY_BIT_ITERATOR_HPP

#include <itsy/version.hpp>

#include <itsy/bit_operations.hpp>

#include <itsy/detail/bit_iterator.hpp>

namespace bitsy
{
	using bit_value = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_value;

	inline constexpr bit_value bit0{false};
	inline constexpr bit_value bit1{true};

	template<typename T>
	using bit_mask_type = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_mask_type<T>;

	template<typename T>
	using bit_mask_type_t = typename bit_mask_type<T>::type;

	template<typename Ref, typename Mask>
	using bit_reference = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_reference<Ref, Mask>;

	template<typename Pointer>
	using bit_pointer = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_pointer<Pointer>;

	template<typename It>
	using bit_iterator = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_iterator<It>;
} // namespace bitsy

#endif // ITSY_BITSY_BIT_ITERATOR_HPP
