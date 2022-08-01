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

#ifndef ITSY_BITSY_DETAIL_BIT_DETAIL_HPP
#define ITSY_BITSY_DETAIL_BIT_DETAIL_HPP 1

#include <itsy/version.hpp>

#include <itsy/forward.hpp>
#include <itsy/binary_digits.hpp>

#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/unwrap.hpp>
#include <ztd/idk/to_mutable_iter.hpp>
#include <ztd/ranges/adl.hpp>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <iterator>
#include <type_traits>
#include <utility>
#include <memory>
#include <functional>

namespace bitsy
{
	namespace __ib_detail
	{
		struct __dummy_tag
		{
		};

		template<typename Alloc, typename... Args>
		using __allocator_construct_invocable_test =
		     decltype(::std::declval<Alloc>().construct(::std::declval<Args>()...));

		template<typename _Type>
		union alignas(_Type) __uninit
		{
			constexpr __uninit() : _M_dummy()
			{
			}

			template<typename... _Args>
			constexpr __uninit(::std::in_place_t, _Args&&... __args) : _M_value(::std::forward<_Args>(__args)...)
			{
			}

			char _M_dummy;
			_Type _M_value;
		};

		template<typename _LeftType, typename _RightType>
		inline constexpr bool __is_same_no_cvref_v =
		     ::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_LeftType>>,
		          ::std::remove_cv_t<::std::remove_reference_t<_RightType>>>;

		template<typename _Type>
		using __has_size_function_test = decltype(::std::declval<_Type&>().size());

		template<typename _Left, typename _Right = _Left>
		using __equal_to_test = decltype(::std::declval<_Left&>() == ::std::declval<_Right&>());

		template<typename _Left, typename _Right = _Left>
		using __not_equal_to_test = decltype(::std::declval<_Left&>() != ::std::declval<_Right&>());

		template<typename _Left, typename _Right = _Left>
		using __less_than_test = decltype(::std::declval<_Left&>() < ::std::declval<_Right&>());

		template<typename _Left, typename _Right = _Left>
		using __less_equal_to_test = decltype(::std::declval<_Left&>() <= ::std::declval<_Right&>());

		template<typename _Left, typename _Right = _Left>
		using __greater_than_test = decltype(::std::declval<_Left&>() > ::std::declval<_Right&>());

		template<typename _Left, typename _Right = _Left>
		using __greater_equal_to_test = decltype(::std::declval<_Left&>() >= ::std::declval<_Right&>());

		template<typename _Container>
		using __has_value_type_test = decltype(_Container::value_type);

		template<typename _Type>
		using __has_pair_iterator_insert_test =
		     decltype(::std::declval<_Type&>().insert(::ztd::ranges::ranges_adl::adl_cbegin(::std::declval<_Type&>()),
		          ::ztd::ranges::ranges_adl::adl_cbegin(::std::declval<_Type&>()),
		          ::ztd::ranges::ranges_adl::adl_cend(::std::declval<_Type&>())));

		template<typename _Container, typename = void>
		class __is_bit_container_test : public ::std::false_type
		{
		};

		template<typename _Container>
		class __is_bit_container_test<_Container,
		     ::std::enable_if_t<::ztd::is_detected_v<__has_value_type_test, _Container>>>
		: public ::std::integral_constant<bool, ::std::is_same_v<typename _Container::value_type, bit_value>>
		{
		};

		template<typename _Container>
		class __is_bit_container : ::std::integral_constant<bool, __is_bit_container_test<_Container>::value>
		{
		};

		template<typename _Container>
		inline constexpr bool __is_bit_container_v = __is_bit_container<_Container>::value;

		template<typename _It>
		struct __is_bit_iterator : ::std::false_type
		{
		};

		template<typename _It>
		struct __is_bit_iterator<bit_iterator<_It>> : ::std::true_type
		{
		};

		template<typename _It>
		inline constexpr bool __is_bit_iterator_v = __is_bit_iterator<_It>::value;
	} // namespace __ib_detail
} // namespace bitsy

#endif // ITSY_BITSY_DETAIL_BIT_DETAIL_HPP
