#pragma once

#ifndef ITSY_BITSY_BIT_ITERATOR_HPP
#define ITSY_BITSY_BIT_ITERATOR_HPP

#include <itsy/version.hpp>

#include <itsy/bit_operations.hpp>

#include <itsy/detail/bit_iterator.hpp>

namespace bitsy
{
	using bit_value = ITSY_BITSY_DETAIL_NAMESPACE::__bit_value;

	inline constexpr bit_value bit0 = ITSY_BITSY_DETAIL_NAMESPACE::__bit0;
	inline constexpr bit_value bit1 = ITSY_BITSY_DETAIL_NAMESPACE::__bit1;

	template<typename T>
	using bit_mask_type = ITSY_BITSY_DETAIL_NAMESPACE::__bit_mask_type<T>;

	template<typename T>
	using bit_mask_type_t = typename bit_mask_type<T>::type;

	template<typename Ref, typename Mask = bit_mask_type_t<Ref>>
	using bit_reference = ITSY_BITSY_DETAIL_NAMESPACE::__bit_reference<Ref, Mask>;

	template<typename Pointer>
	using bit_pointer = ITSY_BITSY_DETAIL_NAMESPACE::__bit_pointer<Pointer>;

	template<typename It>
	using bit_iterator = ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<It>;
} // namespace bitsy

#endif // ITSY_BITSY_BIT_ITERATOR_HPP
