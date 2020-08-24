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

#ifndef ITSY_BITSY_FORWARD_HPP
#define ITSY_BITSY_FORWARD_HPP

#include <itsy/version.hpp>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{

	template<typename _Type>
	class __bit_mask_type;

	template<typename _Type>
	using __bit_mask_type_t = typename __bit_mask_type<_Type>::type;

	class __bit_value;
	template<typename, typename>
	class __bit_reference;
	template<typename>
	class __bit_pointer;
	template<typename>
	class __bit_iterator;
	
	template<typename>
	class __word_bit_bounds;
	template<::std::size_t, ::std::size_t>
	class __bit_bounds;
	template<typename>
	class __dynamic_bit_bounds_for;
	class __dynamic_bit_bounds;

	template<typename _Range, typename>
	class __bit_view;

	template<typename _Type, ::std::size_t, typename, bool>
	class __packed_small_bit_vector;

} // namespace ITSY_BITSY_SOURCE_NAMESPACE

namespace bitsy
{

	template<typename T>
	using bit_mask_type = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_mask_type<T>;

	template<typename T>
	using bit_mask_type_t = typename bit_mask_type<T>::type;

	using bit_value = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_value;

	template<typename Ref, typename Mask = bit_mask_type_t<Ref>>
	using bit_reference = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_reference<Ref, Mask>;

	template<typename It>
	using bit_pointer = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_pointer<It>;

	template<typename It>
	using bit_iterator = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_iterator<It>;

	template<typename Range>
	class word_bit_bounds;

	template<typename Range>
	class  dynamic_bit_bounds_for;

	template<std::size_t first, std::size_t last>
	class bit_bounds;

	class dynamic_bit_bounds;

	template<typename, typename Bounds>
	class bit_view;

	template<typename, ::std::size_t, typename>
	class packed_small_bit_vector;

	template<typename, ::std::size_t, typename>
	class small_bit_vector;

	template<typename>
	class bit_sequence;

	template<typename, typename>
	class bit_vector;

} // namespace bitsy

#endif // ITSY_BITSY_FORWARD_HPP
