#pragma once

#ifndef BITSY_BIT_ITERATOR_HPP
#define BITSY_BIT_ITERATOR_HPP

#include <itsy/version.hpp>

#if BITSY_SOURCE_LIBSTDCXX
#include <bits/bit_iterator.h>
#elif BITSY_SOURCE_LIBCXX
#include <bit_iterator.h>
#else
#include <itsy/detail/bit_iterator.h>
#endif

namespace bitsy
{
	template<typename T>
	using binary_digits = __BIT_STRUCTURES_NAMESPACE::__binary_digits<T>;

	template<typename T>
	inline constexpr auto binary_digits_v = binary_digits<T>::value;

	using bit_value = __BIT_STRUCTURES_NAMESPACE::__bit_value;

	inline constexpr bit_value bit0 = __BIT_STRUCTURES_NAMESPACE::__bit0;
	inline constexpr bit_value bit1 = __BIT_STRUCTURES_NAMESPACE::__bit1;

	template<typename Ref, typename Mask>
	using bit_reference = __BIT_STRUCTURES_NAMESPACE::__bit_reference<Ref, Mask>;
	template<typename Pointer>
	using bit_pointer = __BIT_STRUCTURES_NAMESPACE::__bit_pointer<Pointer>;
	template<typename It>
	using bit_iterator = __BIT_STRUCTURES_NAMESPACE::__bit_iterator<It>;
} // namespace bitsy

#endif // BITSY_BIT_ITERATOR_HPP
