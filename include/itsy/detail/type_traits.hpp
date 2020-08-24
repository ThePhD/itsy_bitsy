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

#ifndef ITSY_BITSY_DETAIL_TYPE_TRAITS_HPP
#define ITSY_BITSY_DETAIL_TYPE_TRAITS_HPP 1

#include <itsy/version.hpp>

#include <type_traits>
#include <functional>
#include <iterator>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{

#ifdef __cpp_lib_concepts
	using __contiguous_iterator_tag = ::std::contiguous_iterator_tag;
#else
	class __contiguous_iterator_tag : public ::std::random_access_iterator_tag {};
#endif

	template <typename _Type>
	using __remove_cvref_t = ::std::remove_cv_t<::std::remove_reference_t<_Type>>;

	template<typename _Type, template<typename...> class _Templ>
	struct __is_specialization_of_impl : std::false_type
	{
	};

	template<typename... _Args, template<typename...> class _Templ>
	struct __is_specialization_of_impl<_Templ<_Args...>, _Templ> : std::true_type
	{
	};

	template<typename _Type, template<typename...> class _Templ>
	using __is_specialization_of = __is_specialization_of_impl<::std::remove_cv_t<_Type>, _Templ>;

	template<typename _Type, template<typename...> class _Templ>
	inline constexpr bool __is_specialization_of_v = __is_specialization_of<_Type, _Templ>::value;

	template<typename>
	struct __dependent_false : std::false_type
	{
	};

	template<typename _Type>
	inline constexpr bool __dependent_false_v = __dependent_false<_Type>::value;

	template<typename _Type, typename _UType = ::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	struct __is_code_unit
	: ::std::integral_constant<bool, ::std::is_same_v<_UType, char> || ::std::is_same_v<_UType, wchar_t> ||
	                                      ::std::is_same_v<_UType, char16_t> || ::std::is_same_v<_UType, char32_t>
#if ITSY_BITSY_IS_ON(ITSY_BITSY_STD_CHAR8_T_I_)
	                                      || ::std::is_same_v<_UType, char8_t>
#endif
	       >
	{
	};

	template<typename _Type>
	inline constexpr bool __is_code_unit_v = __is_code_unit<_Type>::value;

	struct __nonesuch
	{
		__nonesuch(__nonesuch const&) = delete;
		__nonesuch&
		operator=(__nonesuch const&) = delete;
		~__nonesuch()                = delete;
	};

	template<class Default, class AlwaysVoid, template<class...> class Op, class... Args>
	struct __detector
	{
		using value_t = std::false_type;
		using type    = Default;
	};

	template<class Default, template<class...> class Op, class... Args>
	struct __detector<Default, std::void_t<Op<Args...>>, Op, Args...>
	{
		using value_t = std::true_type;
		using type    = Op<Args...>;
	};

	template<template<class...> class Op, class... Args>
	using __is_detected = typename __detector<__nonesuch, void, Op, Args...>::value_t;

	template<template<class...> class Op, class... Args>
	using __detected_t = typename __detector<__nonesuch, void, Op, Args...>::type;

	template<class Default, template<class...> class Op, class... Args>
	using __detected_or = __detector<Default, void, Op, Args...>;

	template<template<typename...> class _Op, typename... _Args>
	constexpr bool __is_detected_v = __is_detected<_Op, _Args...>::value;

	template<typename _Type, typename = ::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	struct __unwrap
	{
		using type = _Type;
	};

	template<typename _Dummy, typename _Type>
	struct __unwrap<_Dummy, ::std::reference_wrapper<_Type>>
	{
		using type = ::std::add_lvalue_reference_t<_Type>;
	};

	template<typename _Type>
	using __unwrap_t = typename __unwrap<_Type>::type;

	template<typename _It>
	using __weakly_incrementable_test = decltype(++::std::declval<_It&>());

	template<typename _It>
	using __weakly_decrementable_test = decltype(--::std::declval<_It&>());

	template<typename _It>
	inline constexpr bool __weakly_incrementable_v = __is_detected_v<__weakly_incrementable_test, _It>;

	template<typename _It>
	inline constexpr bool __weakly_decrementable_v = __is_detected_v<__weakly_decrementable_test, _It>;

	template <typename _It>
	using __iterator_category_t =
		typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_category;

	template <typename _It, typename = void>
	struct __iterator_concept_or_fallback {
		using type = ::std::conditional_t<::std::is_pointer_v<__remove_cvref_t<_It>>, __contiguous_iterator_tag,
			__iterator_category_t<_It>>;
	};

	template <typename _It>
	struct __iterator_concept_or_fallback<_It,
		::std::void_t<typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_concept>> {
		using type = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_concept;
	};

	template <typename _It>
	using __iterator_concept_or_fallback_t =
		typename __iterator_concept_or_fallback<::std::remove_reference_t<_It>>::type;

	template <typename _It>
	using __iterator_concept_t = __iterator_concept_or_fallback_t<_It>;

	template <typename _Tag, typename _It>
	inline constexpr bool __is_iterator_concept_or_better_v = ::std::is_base_of_v<_Tag, __iterator_concept_t<_It>>;

} // namespace ITSY_BITSY_SOURCE_NAMESPACE

#endif // ITSY_BITSY_DETAIL_TYPE_TRAITS_HPP
