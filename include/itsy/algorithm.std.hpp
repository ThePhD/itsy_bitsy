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

#ifndef ITSY_BITSY_STD_ALGORITHM_HPP
#define ITSY_BITSY_STD_ALGORITHM_HPP

#include <itsy/version.hpp>

#include <itsy/algorithm.hpp>

namespace std
{
	template<typename _It, typename _Type>
	constexpr ::bitsy::bit_iterator<_It>
	find(::bitsy::bit_iterator<_It> __first, ::bitsy::bit_iterator<_It> __last, const _Type& __val)
	{
		return ::bitsy::bit_find(::std::move(__first), ::std::move(__last), __val);
	}

	template<typename _InputIt, typename _ForwardIt>
	constexpr ::bitsy::bit_iterator<_InputIt>
	find_first_of(::bitsy::bit_iterator<_InputIt> __first, ::bitsy::bit_iterator<_InputIt> __last,
	  _ForwardIt __search_first, _ForwardIt __search_last)
	{
		return ::bitsy::bit_find_first_of(::std::move(__first), ::std::move(__last),
		  ::std::move(__search_first), ::std::move(__search_last));
	}

	template<typename _It0, typename _It1>
	constexpr bool
	equal(::bitsy::bit_iterator<_It0> __first0, ::bitsy::bit_iterator<_It0> __last0,
	  ::bitsy::bit_iterator<_It1> __first1, ::bitsy::bit_iterator<_It1> __last1)
	{
		return ::bitsy::bit_equal(
		  ::std::move(__first0), ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
	}

	template<typename _It0, typename _It1>
	constexpr bool
	equal(::bitsy::bit_iterator<_It0> __first0, ::bitsy::bit_iterator<_It0> __last0,
	  ::bitsy::bit_iterator<_It1> __first1)
	{
		return ::bitsy::bit_equal(::std::move(__first0), ::std::move(__last0), ::std::move(__first1));
	}

	template<typename _InputIt0, typename _InputIt1>
	constexpr bool
	lexicographical_compare(::bitsy::bit_iterator<_InputIt0> __first0,
	  ::bitsy::bit_iterator<_InputIt0> __last0, ::bitsy::bit_iterator<_InputIt1> __first1,
	  ::bitsy::bit_iterator<_InputIt1> __last1)
	{
		return ::bitsy::bit_lexicographical_compare(
		  ::std::move(__first0), ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
	}

	template<typename _It, typename _Type>
	constexpr typename std::iterator_traits<::bitsy::bit_iterator<_It>>::difference_type
	count(::bitsy::bit_iterator<_It> __first, ::bitsy::bit_iterator<_It> __last, const _Type& __value)
	{
		return ::bitsy::bit_count(::std::move(__first), ::std::move(__last), __value);
	}

	template<typename _ForwardIt>
	constexpr ::bitsy::bit_iterator<_ForwardIt>
	is_sorted_until(
	  ::bitsy::bit_iterator<_ForwardIt> __first, ::bitsy::bit_iterator<_ForwardIt> __last)
	{
		return ::bitsy::bit_is_sorted_until(::std::move(__first), ::std::move(__last));
	}

	template<typename _ForwardIt>
	constexpr bool
	is_sorted(::bitsy::bit_iterator<_ForwardIt> __first, ::bitsy::bit_iterator<_ForwardIt> __last)
	{
		return ::bitsy::bit_is_sorted(::std::move(__first), ::std::move(__last));
	}

	template<typename _It, typename _OutputIt>
	constexpr _OutputIt
	copy(::bitsy::bit_iterator<_It> __first, ::bitsy::bit_iterator<_It> __last, _OutputIt __out_first)
	{
		return ::bitsy::bit_copy(::std::move(__first), ::std::move(__last), ::std::move(__out_first));
	}

	template<typename _It, typename _Size, typename _OutputIt>
	constexpr _OutputIt
	copy_n(::bitsy::bit_iterator<_It> __first, _Size __count, _OutputIt __out_first)
	{
		return ::bitsy::bit_copy_n(::std::move(__first), __count, ::std::move(__out_first));
	}

	template<typename _ForwardIt, typename _Type>
	constexpr ::bitsy::bit_iterator<_ForwardIt>
	fill(::bitsy::bit_iterator<_ForwardIt> __first, ::bitsy::bit_iterator<_ForwardIt> __last,
	  const _Type& __value)
	{
		return ::bitsy::bit_fill(::std::move(__first), ::std::move(__last), __value);
	}

	template<typename _OutputIt, typename _Size, typename _Type>
	constexpr ::bitsy::bit_iterator<_OutputIt>
	fill_n(::bitsy::bit_iterator<_OutputIt> __first, _Size __count, const _Type& __value)
	{
		return ::bitsy::bit_fill_n(::std::move(__first), ::std::move(__count), __value);
	}
} // namespace std

#endif // ITSY_BITSY_STD_ALGORITHM_HPP
