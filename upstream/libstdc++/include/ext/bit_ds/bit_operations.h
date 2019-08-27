
// Core bit operations -*- C++ -*-

// Copyright (C) 2019-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file ext/bit_ds/bit_operations.h
 *  This file is a GNU extension to the Standard C++ Library.
 *  It's goal is to provide low-level, platform-independent operations that
 *  are usable by the rest of the abstractions in the Bit Data Structures
 *  library. This includes a few type traits-like checkers,
 *  some forward declarations, and additional low-level
 *  utilities for manipulating bits.
 */

#pragma once

#ifndef _EXT_BIT_DS_BIT_OPERATIONS_H
#define _EXT_BIT_DS_BIT_OPERATIONS_H 1

#if (defined(__cplusplus) && __cplusplus >= 201703L)

#include <bits/c++config.h>

#include <cstddef>
#include <cstdint>
#include <climits>
#include <iterator>
#include <type_traits>
#include <utility>

namespace __gnu_cxx _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION

	// forward declarations
	class __bit_value;
	template<typename, typename>
	class __bit_reference;
	template<typename>
	class __bit_pointer;
	template<typename>
	class __bit_iterator;

	template<typename>
	struct __dependent_false : std::false_type
	{
	};

	template<typename _Type>
	inline constexpr bool __dependent_false_v = __dependent_false<_Type>::value;

	template<typename _Type, typename _UType = ::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	struct __is_code_unit
	: ::std::integral_constant<bool,
	    ::std::is_same_v<_UType, char> || ::std::is_same_v<_UType, wchar_t> ||
	      ::std::is_same_v<_UType, char16_t> || ::std::is_same_v<_UType, char32_t>
#if defined(__cpp_char8_t)
	      || ::std::is_same_v<_UType, char8_t>
#endif
	    >
	{
	};

	template<typename _Type>
	inline constexpr bool __is_code_unit_v = __is_code_unit<_Type>::value;

	template<template<typename...> typename _Op, typename... _Args>
	using __is_detected = typename ::std::__detector<::std::__nonesuch, void, _Op, _Args...>::value_t;

	template<template<typename...> typename _Op, typename... _Args>
	using __detected_t = typename ::std::__detector<::std::__nonesuch, void, _Op, _Args...>::type;

	template<class Default, template<typename...> typename _Op, typename... _Args>
	using __detected_or = ::std::__detector<Default, void, _Op, _Args...>;

	template<template<typename...> typename _Op, typename... _Args>
	inline constexpr bool __is_detected_v = __is_detected<_Op, _Args...>::value;

	template<typename _Type>
	using __unwrap = ::std::__inv_unwrap<_Type>;

	template<typename _Type>
	using __unwrap_t = typename __unwrap<_Type>::type;

	struct __dummy_tag
	{
	};

	template<typename _Type, typename = void>
	class __un_binary_digits
	{
	};

	template<typename _Type>
	class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_integral_v<_Type>>>
	: public ::std::integral_constant<::std::size_t, ::std::numeric_limits<_Type>::digits>
	{
	};

	template<typename _Type>
	class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_enum_v<_Type>>>
	: public ::std::integral_constant<::std::size_t,
	    ::std::numeric_limits<::std::underlying_type_t<_Type>>::digits>
	{
	};

	template<typename _Type>
	class __binary_digits
	: public __un_binary_digits<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename _Type>
	inline constexpr auto __binary_digits_v = __binary_digits<_Type>::value;

	template<typename _Type>
	inline constexpr auto __max_binary_index_v = __binary_digits_v<_Type> - 1;

	template<typename, typename = void>
	class __un_bit_mask_type
	{
	};

	template<typename _Type>
	class __un_bit_mask_type<_Type,
	  std::enable_if_t<std::is_integral_v<_Type> || std::is_enum_v<_Type>>>
	{
	public:
		using type = _Type;
	};

	template<typename _Type>
	class __bit_mask_type
	: public __un_bit_mask_type<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename T>
	using __bit_mask_type_t = typename __bit_mask_type<T>::type;

	template<typename _Arg>
	constexpr decltype(auto) __unwrap_ref(_Arg && __arg)
	{
		return static_cast<__unwrap_t<_Arg>>(::std::forward<_Arg>(__arg));
	}

	template<typename _Container>
	constexpr decltype(auto) __adl_begin(_Container && __container)
	{
		using ::std::begin;
		return begin(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto) __adl_end(_Container && __container)
	{
		using ::std::end;
		return end(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto) __adl_cbegin(_Container && __container)
	{
		using ::std::cbegin;
		return cbegin(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto) __adl_cend(_Container && __container)
	{
		using ::std::cend;
		return cend(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto) __adl_empty(_Container && __container)
	{
		using ::std::empty;
		return empty(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto) __adl_size(_Container && __container)
	{
		using ::std::size;
		return size(::std::forward<_Container>(__container));
	}

	template<typename _Left, typename _Right>
	constexpr void __adl_swap(_Left & __left, _Right & __right)
	{
		using ::std::swap;
		return swap(__left, __right);
	}

	template<typename _It>
	struct __is_bit_iterator : ::std::false_type
	{
	};

	template<typename _It>
	struct __is_bit_iterator<__bit_iterator<_It>> : ::std::true_type
	{
	};

	template<typename _It>
	inline constexpr bool __is_bit_iterator_v = __is_bit_iterator<_It>::value;

	template<typename _Target, typename _Actual>
	using __is_iterator_category_or_better = ::std::is_base_of<_Target, _Actual>;

	template<typename _Target, typename _Actual>
	inline constexpr bool __is_iterator_category_or_better_v =
	  __is_iterator_category_or_better<_Target, _Actual>::value;

	template<typename _LeftType, typename _RightType>
	inline constexpr bool __is_same_no_cvref_v =
	  ::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_LeftType>>,
	    ::std::remove_cv_t<::std::remove_reference_t<_RightType>>>;

	template<typename _Enumish, typename = void>
	struct __any_to_underlying
	{
		using type = _Enumish;
	};

	template<typename _Enumish>
	struct __any_to_underlying<_Enumish, ::std::enable_if_t<::std::is_enum_v<_Enumish>>>
	{
		using type = ::std::underlying_type_t<_Enumish>;
	};

	template<typename _Enumish>
	using __any_to_underlying_t = typename __any_to_underlying<_Enumish>::type;

	template<typename _Integralish>
	inline constexpr auto __to_underlying_if_enum(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish>)
			{
				return static_cast<::std::underlying_type_t<_Integralish>>(__val);
			}
		else
			{
				return __val;
			}
	}

	template<typename _Integralish>
	inline constexpr auto __to_underlying_if_enum_or_char_t(_Integralish __val) noexcept
	{
		if constexpr (::std::is_same_v<_Integralish, char>)
			{
				using _UTy =
				  ::std::conditional_t<::std::is_signed_v<char>, ::std::int_least8_t, ::std::uint_least8_t>;
				return static_cast<_UTy>(__val);
			}
		else if constexpr (::std::is_same_v<_Integralish, wchar_t>)
			{
				if constexpr (::std::is_signed_v<wchar_t>)
					{
						if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least8_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>, ::std::int_least8_t,
								  ::std::uint_least8_t>;
								return static_cast<_UTy>(__val);
							}
						else if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least16_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>, ::std::int_least16_t,
								  ::std::uint_least16_t>;
								return static_cast<_UTy>(__val);
							}
						else if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least32_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>, ::std::int_least32_t,
								  ::std::uint_least32_t>;
								return static_cast<_UTy>(__val);
							}
						else
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>, ::std::int_least64_t,
								  ::std::uint_least64_t>;
								return static_cast<_UTy>(__val);
							}
					}
				else
					{
						return static_cast<uint_least8_t>(__val);
					}
			}
#if defined(__cpp_char8_t)
		else if constexpr (::std::is_same_v<_Integralish, char8_t>)
			{
				return static_cast<unsigned char>(__val);
			}
#endif // char8_t
		else if constexpr (::std::is_same_v<_Integralish, char16_t>)
			{
				return static_cast<uint_least16_t>(__val);
			}
		else if constexpr (::std::is_same_v<_Integralish, char32_t>)
			{
				return static_cast<uint_least32_t>(__val);
			}
		else
			{
				return __to_underlying_if_enum(__val);
			}
	}

	template<typename _Type>
	using __has_size_function_test = decltype(::std::declval<_Type&>().size());

	template<typename _Container>
	using __has_value_type_test = decltype(_Container::value_type);

	template<typename _Type>
	using __has_pair_iterator_insert_test =
	  decltype(::std::declval<_Type&>().insert(__adl_cbegin(::std::declval<_Type&>()),
	    __adl_cbegin(::std::declval<_Type&>()), __adl_cend(::std::declval<_Type&>())));

	template<typename _Container, typename = void>
	class __is_bit_container_test : public ::std::false_type
	{
	};

	template<typename _Container>
	class __is_bit_container_test<_Container,
	  ::std::enable_if_t<__is_detected_v<__has_value_type_test, _Container>>>
	: public ::std::integral_constant<bool,
	    ::std::is_same_v<typename _Container::value_type, __bit_value>>
	{
	};

	template<typename _Container>
	class __is_bit_container
	: ::std::integral_constant<bool, __is_bit_container_test<_Container>::value>
	{
	};

	template<typename _Container>
	inline constexpr bool __is_bit_container_v = __is_bit_container<_Container>::value;

	template<typename __Iter>
	using __invoke_iter_as_mutable_test = decltype(__iter_as_mutable(::std::declval<__Iter>()));

	template<typename __Iter>
	using __is_iter_as_mutable_invokable = __is_detected<__invoke_iter_as_mutable_test, __Iter>;

	template<typename __Iter>
	inline constexpr bool __is_iter_as_mutable_invokable_v =
	  __is_iter_as_mutable_invokable<__Iter>::value;

	template<typename _FromIt, typename _Container>
	constexpr auto __iter_as_mutable_from_begin(_FromIt & __from_it, _Container & __source) noexcept
	{
		using _ToIt = decltype(__adl_begin(__source));

		if constexpr (::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_ToIt>>, _FromIt>)
			{
				(void)__source;
				return _ToIt(__from_it);
			}
		else if constexpr (__is_iter_as_mutable_invokable_v<_FromIt&>)
			{
				(void)__source;
				return __iter_as_mutable(__from_it);
			}
		else if constexpr (__is_detected_v<__has_pair_iterator_insert_test, _Container>)
			{
				// http://eel.is/c++draft/container.requirements#sequence.reqmts-8
				// "The iterator returned from a.insert(p, i, j)
				// points to the copy of the first element inserted into a,
				// or p if i == j."
				// in other words, this is our cheat code to avoid
				// hitting the worst-case-scenario here
				return __source.insert(__from_it, __adl_cend(__source), __adl_cend(__source));
			}
		else if constexpr (::std::is_invocable_r_v<bool, ::std::not_equal_to<>, _ToIt, _FromIt> &&
		                   (::std::is_same_v<
		                      typename ::std::iterator_traits<_FromIt>::iterator_category,
		                      ::std::forward_iterator_tag> ||
		                     ::std::is_same_v<
		                       typename ::std::iterator_traits<_FromIt>::iterator_category,
		                       ::std::bidirectional_iterator_tag>))
			{
				// we can avoid 2N walk of iterators
				// by just moving up by them if they're
				// comparable to one another
				auto __begin_it = __adl_begin(__source);
				while (__begin_it != __from_it)
					{
						++__begin_it;
					}
				return __begin_it;
			}
		else
			{
				// either this is random access and O(1),
				// or this is some other weird iterator and it's O(2N)
				auto __begin_it = __adl_begin(__source);
				auto __it_dist  = ::std::distance(_FromIt(__begin_it), __from_it);
				std::advance(__begin_it, __it_dist);
				return __begin_it;
			}
	}

	template<typename _FromIt, typename _Container>
	constexpr auto __iter_as_mutable_from_end(_FromIt & __from_it, _Container & __source) noexcept
	{
		using _ToIt = decltype(__adl_end(__source));

		if constexpr (::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_ToIt>>, _FromIt>)
			{
				(void)__source;
				return _ToIt(__from_it);
			}
		else if constexpr (__is_iter_as_mutable_invokable_v<_FromIt&>)
			{
				(void)__source;
				return __iter_as_mutable(__from_it);
			}
		else if constexpr (__is_detected_v<__has_pair_iterator_insert_test, _Container>)
			{
				// http://eel.is/c++draft/container.requirements#sequence.reqmts-8
				// "The iterator returned from a.insert(p, i, j)
				// points to the copy of the first element inserted into a,
				// or p if i == j."
				// in other words, this is our cheat code to avoid
				// hitting the worst-case-scenario here
				return __source.insert(__from_it, __adl_cend(__source), __adl_cend(__source));
			}
		else if constexpr (::std::is_invocable_r_v<bool, ::std::not_equal_to<>, _ToIt, _FromIt> &&
		                   (::std::is_same_v<
		                     typename ::std::iterator_traits<_FromIt>::iterator_category,
		                     ::std::bidirectional_iterator_tag>))
			{
				// we can avoid 2N walk of iterators
				// by just moving up by them if they're
				// comparable to one another
				auto __begin_it = __adl_end(__source);
				while (__begin_it != __from_it)
					{
						--__begin_it;
					}
				return __begin_it;
			}
		else if constexpr (::std::is_invocable_r_v<bool, ::std::not_equal_to<>, _ToIt, _FromIt> &&
		                   (::std::is_same_v<
		                     typename ::std::iterator_traits<_FromIt>::iterator_category,
		                     ::std::forward_iterator_tag>))
			{
				// we can avoid 2N walk of iterators
				// by just moving up by them if they're
				// comparable to one another
				auto __begin_it = __adl_begin(__source);
				while (__begin_it != __from_it)
					{
						++__begin_it;
					}
				return __begin_it;
			}
		else
			{
				// either this is random access and O(1),
				// or this is some other weird iterator and it's O(2N)
				auto __end_it  = __adl_end(__source);
				auto __it_dist = ::std::distance(__from_it, _FromIt(__end_it));
				std::advance(__end_it, __it_dist);
				return __end_it;
			}
	}

	// the following functions provide
	// a more complete set of operations
	// than is provided by the actual <bit>
	// header, and supports more types too
	// (e.g., enumerations, character types)
	// these are fundametnally useful and thus
	// included here

	template<typename _Integralish>
	constexpr int __basic_countl_zero(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __not_is_set =
				  (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) ==
				  static_cast<_Integralish>(0);
				if (__not_is_set)
					{
						__num += 1;
					}
				else
					{
						break;
					}
			}
		return __num;
	}

	template<typename _Integralish>
	constexpr int __basic_countl_one(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __is_set =
				  (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				  static_cast<_Integralish>(0);
				if (__is_set)
					{
						__num += 1;
					}
				else
					{
						break;
					}
			}
		return __num;
	}

	template<typename _Integralish>
	constexpr int __basic_countr_zero(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>;
		     ++__bit_index)
			{
				bool __not_is_set =
				  (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) ==
				  static_cast<_Integralish>(0);
				if (__not_is_set)
					{
						__num += 1;
					}
				else
					{
						break;
					}
			}
		return __num;
	}

	template<typename _Integralish>
	constexpr int __basic_countr_one(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>;
		     ++__bit_index)
			{
				bool __is_set =
				  (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				  static_cast<_Integralish>(0);
				if (__is_set)
					{
						__num += 1;
					}
				else
					{
						break;
					}
			}
		return __num;
	}

	template<typename _Integralish>
	constexpr int __basic_firstr_one(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>;
		     ++__bit_index)
			{
				bool __is_set =
				  (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				  static_cast<_Integralish>(0);
				if (__is_set)
					{
						return static_cast<int>(__bit_index + 1);
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int __basic_firstr_zero(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>;
		     ++__bit_index)
			{
				bool __is_not_set =
				  (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) ==
				  static_cast<_Integralish>(0);
				if (__is_not_set)
					{
						return static_cast<int>(__bit_index + 1);
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int __basic_firstl_one(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __is_set =
				  (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				  static_cast<_Integralish>(0);
				if (__is_set)
					{
						return static_cast<int>(__binary_digits_v<_Integralish> - __bit_index);
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int __basic_firstl_zero(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __is_not_set =
				  (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) ==
				  static_cast<_Integralish>(0);
				if (__is_not_set)
					{
						return static_cast<int>(__bit_index + 1);
					}
				else
					{
						break;
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int __basic_popcount(_Integralish __val) noexcept
	{
		if constexpr (__binary_digits_v<_Integralish> <= 128)
			{
				__val = __val - ((__val >> 1) & (_Integralish) ~(_Integralish)0 / 3);
				__val = (__val & (_Integralish) ~(_Integralish)0 / 15 * 3) +
				        ((__val >> 2) & (_Integralish) ~(_Integralish)0 / 15 * 3);
				__val = (__val + (__val >> 4)) & (_Integralish) ~(_Integralish)0 / 255 * 15;
				return (_Integralish)(__val * ((_Integralish) ~(_Integralish)0 / 255)) >>
				       (sizeof(_Integralish) - 1) * CHAR_BIT; // count
			}
		else
			{
				int __num = 0;
				for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>;
				     ++__bit_index)
					{
						bool __is_set = (__val & (static_cast<_Integralish>(1) << __bit_index)) !=
						                static_cast<_Integralish>(0);
						__num += static_cast<int>(__is_set);
					}
				return __num;
			}
	}

	template<typename _Integralish>
	constexpr int __unsigned_countl_zero(_Integralish __val) noexcept
	{
		int __countl_zero_val;
#if defined(__cpp_lib_bitops)
		__countl_zero_val = ::std::countl_zero(__val);
#else
		if (__val == 0)
			{
				(void)__countl_zero_val;
				return static_cast<int>(__binary_digits_v<_Integralish>);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				__countl_zero_val = __builtin_clz(__val) -
				                    (__binary_digits_v<unsigned int> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				__countl_zero_val = __builtin_clzl(__val) -
				                    (__binary_digits_v<unsigned long> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				__countl_zero_val = __builtin_clzll(__val) - (__binary_digits_v<unsigned long long> -
				                                               __binary_digits_v<_Integralish>);
			}
		else
			{
				__countl_zero_val = __basic_countl_zero(__val);
			}
#endif
		return __countl_zero_val;
	}

	template<typename _Integralish>
	constexpr int __unsigned_countl_one(_Integralish __val) noexcept
	{
		return __unsigned_countl_zero(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int __unsigned_countr_zero(_Integralish __val) noexcept
	{
		int __countr_zero_val;
#if defined(__cpp_lib_bitops)
		__countr_zero_val = ::std::countr_zero(__val);
#else
		if (__val == 0)
			{
				(void)__countr_zero_val;
				return static_cast<int>(__binary_digits_v<_Integralish>);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				__countr_zero_val = __builtin_ctz(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				__countr_zero_val = __builtin_ctzl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				__countr_zero_val = __builtin_ctzll(__val);
			}
		else
			{
				__countr_zero_val = __basic_countr_zero(__val);
			}
#endif
		return __countr_zero_val;
	}

	template<typename _Integralish>
	constexpr int __unsigned_countr_one(_Integralish __val) noexcept
	{
		return __unsigned_countr_zero(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int __unsigned_firstr_one(_Integralish __val) noexcept
	{
		int __firstr_one_val;
#if 0
		// FUTURE LOOKING: if/when "find first set" is added to the collection of 
		// intrinsics standardized by C++ 
		// Test would be: #if __cpp_lib_bitops > 201908L, or similar... 
		__firstr_one_val = __basic_firstr_one(__val);
#else
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				__firstr_one_val = __builtin_ffs(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				__firstr_one_val = __builtin_ffsl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				__firstr_one_val = __builtin_ffsll(__val);
			}
		else
			{
				__firstr_one_val = __basic_firstr_one(__val);
			}
#endif
		return __firstr_one_val;
	}

	template<typename _Integralish>
	constexpr int __unsigned_firstr_zero(_Integralish __val) noexcept
	{
		return __unsigned_firstr_one(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int __unsigned_firstl_one(_Integralish __val) noexcept
	{
		int __firstl_one_val;
#if 0
		// FUTURE LOOKING: if/when "find first set" is added to the collection of 
		// intrinsics standardized by C++ 
		// Test would be: #if __cpp_lib_bitops > 201908L, or similar... 
		__firstr_one_val = __basic_firstr_one(__val);
#else
		if (__val == 0)
			{
				(void)__firstl_one_val;
				return static_cast<int>(0);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				__firstl_one_val = __builtin_clz(__val) + 1 -
				                   (__binary_digits_v<unsigned int> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				__firstl_one_val = __builtin_clzl(__val) + 1 -
				                   (__binary_digits_v<unsigned long> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				__firstl_one_val =
				  __builtin_clzll(__val) + 1 -
				  (__binary_digits_v<unsigned long long> - __binary_digits_v<_Integralish>);
			}
		else
			{
				__firstl_one_val = __basic_firstl_one(__val);
			}
#endif
		return __firstl_one_val;
	}

	template<typename _Integralish>
	constexpr int __unsigned_firstl_zero(_Integralish __val) noexcept
	{
		return __unsigned_firstl_one(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int __unsigned_popcount(_Integralish __val) noexcept
	{
		int __popcount_val;
#if defined(__cpp_lib_bitops)
		__popcount_val = ::std::popcount(__val);
#else
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				__popcount_val = __builtin_popcountl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				__popcount_val = __builtin_popcountl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				__popcount_val = __builtin_popcountll(__val);
			}
		else
			{
				__popcount_val = __basic_popcount(__val);
			}
#endif
		return __popcount_val;
	}

	template<typename _Integralish>
	constexpr int __countl_zero(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __countl_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// destroy sign bit
						__val = static_cast<_Integralish>(
						  static_cast<_UIntegralish>(__val) &
						  static_cast<_UIntegralish>(::std::numeric_limits<_Integralish>::max()));
					}
				int __countl_zero_val = __unsigned_countl_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// remove +1 that comes from sign bit
						--__countl_zero_val;
					}
				return __countl_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int __countl_one(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __countl_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// force set sign bit
						__val = static_cast<_Integralish>(
						  static_cast<_UIntegralish>(__val) |
						  (static_cast<_UIntegralish>(1) << __max_binary_index_v<_UIntegralish>));
					}
				int __countl_one_val = __unsigned_countl_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// remove +1 that comes from sign bit
						--__countl_one_val;
					}
				return __countl_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int __countr_zero(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __countr_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish   = ::std::make_unsigned_t<_Integralish>;
				int __countr_zero_val = __unsigned_countr_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__countr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return __binary_digits_v<_Integralish>;
							}
					}
				return __countr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int __countr_one(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __countr_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish   = ::std::make_unsigned_t<_Integralish>;
				int __countr_zero_val = __unsigned_countr_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__countr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return __binary_digits_v<_Integralish>;
							}
					}
				return __countr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int __firstr_one(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __firstr_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish  = ::std::make_unsigned_t<_Integralish>;
				int __firstr_one_val = __unsigned_firstr_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__firstr_one_val == __binary_digits_v<_UIntegralish>)
							{
								return 0;
							}
					}
				return __firstr_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int __firstr_zero(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __firstr_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish   = ::std::make_unsigned_t<_Integralish>;
				int __firstr_zero_val = __unsigned_firstr_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__firstr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return 0;
							}
					}
				return __firstr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int __firstl_one(_Integralish __val)
	{

		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __firstl_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// force clear sign bit
						__val = static_cast<_Integralish>(
						  static_cast<_UIntegralish>(__val) &
						  static_cast<_UIntegralish>(::std::numeric_limits<_Integralish>::max()));
					}
				int __firstl_one_val = __unsigned_firstl_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__firstl_one_val == 0)
							{
								return 0;
							}
						--__firstl_one_val;
					}
				return __firstl_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int __firstl_zero(_Integralish __val)
	{

		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __firstl_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// force set sign bit
						__val = static_cast<_Integralish>(
						  static_cast<_UIntegralish>(__val) |
						  (static_cast<_UIntegralish>(1) << __max_binary_index_v<_UIntegralish>));
					}
				int __firstl_zero_val = __unsigned_firstl_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__firstl_zero_val == 0)
							{
								return 0;
							}
						return __firstl_zero_val - 1;
					}
				else
					{
						return __firstl_zero_val;
					}
			}
	}

	template<typename _Integralish>
	constexpr int __popcount(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __popcount(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// force clear sign bit
						__val = static_cast<_Integralish>(
						  static_cast<_UIntegralish>(__val) &
						  static_cast<_UIntegralish>(::std::numeric_limits<_Integralish>::max()));
					}
				int __popcount_val = __unsigned_popcount(static_cast<_UIntegralish>(__val));
				return __popcount_val;
			}
	}

	template<typename _Pos, typename _Mask>
	inline constexpr _Pos __mask_to_pos(_Mask __mask) noexcept
	{
		_Pos __pos = static_cast<_Pos>(0);
		while (__mask != static_cast<_Mask>(0))
			{
				++__pos;
				__mask >>= 1;
			}
		return static_cast<_Pos>(__pos);
	}

	template<typename _Mask, typename _Pos>
	inline constexpr _Mask __pos_to_mask(_Pos __pos) noexcept
	{
		return static_cast<_Mask>(static_cast<_Mask>(1) << __pos);
	}

	template<typename _Mask, typename _Pos>
	inline constexpr _Mask __pos_to_all_1_mask(_Pos __pos) noexcept
	{
		_Mask __mask(static_cast<_Mask>(2) << __pos);
		__mask = static_cast<_Mask>(__to_underlying_if_enum_or_char_t(__mask) - 1);
		return __mask;
	}

	template<typename _Word, bool _ShiftLeft, bool _PreserveLeft, typename _Ref, typename _Pos,
	  typename _Shift>
	inline constexpr void __shift_and_preserve(
	  _Ref & __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		_Word __preservation      = __storage_ref;
		_Word __preservation_mask = __pos_to_all_1_mask<_Word>(__pos_position);
		if constexpr (_PreserveLeft)
			{
				__preservation_mask = ~__preservation_mask;
			}
		_Word __preservation_complement_mask = ~__preservation_mask;

		__preservation = __preservation & __preservation_mask;
		if constexpr (_ShiftLeft)
			{
				__storage_ref <<= __shift_by;
			}
		else
			{
				__storage_ref >>= __shift_by;
			}
		// restore bits from desired "untouched" section
		__storage_ref = (__storage_ref & __preservation_complement_mask) | (__preservation);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void __shift_left_preserve_right(
	  _Ref & __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, true, false>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void __shift_right_preserve_right(
	  _Ref & __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, false, false>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void __shift_left_preserve_left(
	  _Ref & __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, true, true>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void __shift_right_preserve_left(
	  _Ref & __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, false, true>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Pos>
	inline constexpr _Word __merge_bits_at(_Word & __lsb, _Word & __msb, _Pos __bit_position)
	{
		_Word __lsb_mask = __pos_to_all_1_mask<_Word>(__bit_position);
		_Word __msb_mask = ~__lsb_mask;
		return (__lsb & __lsb_mask) | (__msb & __msb_mask);
	}

	template<typename _Word, typename _Ref, typename _Pos>
	inline constexpr _Word __replace_most_significant_bits_from(
	  _Ref & __target, _Ref & __donor, _Pos __num_bits)
	{
		_Word __donor_give_mask  = __pos_to_all_1_mask<_Word>(__num_bits - 1);
		_Word __target_keep_mask = (~__donor_give_mask) >> __num_bits;
		_Pos __at                = __binary_digits_v<_Word> - __num_bits;
		return (__target & __target_keep_mask) | ((__donor & __donor_give_mask) << __at);
	}

	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace __gnu_cxx_GLIBCXX_VISIBILITY(default)

#endif // __cplusplus is on 20/2a or better

#endif
