// std algorithm overloads for bit iterators -*- C++ -*-

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

/** @file ext/bit_ds/bit_algorithm_std.h
 *  This file is a GNU extension to the Standard C++ Library.
 *  It provides overloads to the standard to catch
 *  these algorithmic improvements without having to
 *  explicitly access the Bit Datastructure namespace or
 *  extension name. Considered safe, as this is also done
 *  for vector_bool implementation-defined iterators in
 *  a handful of cases.
 */

#pragma once

#ifndef _EXT_BIT_DS_BIT_ALGORITHM_H
#define _EXT_BIT_DS_BIT_ALGORITHM_H 1

#if (defined(__cplusplus) && __cplusplus >= 201703L)

#include <ext/bit_ds/bit_iterator.h>
#include <ext/bit_ds/bit_algorithm.h>

#include <utility>

namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION

	template<typename _It, typename _Type>
	constexpr ::__gnu_cxx::__bit_iterator<_It> find(::__gnu_cxx::__bit_iterator<_It> __first,
	  ::__gnu_cxx::__bit_iterator<_It> __last, const _Type& __val)
	{
		return ::__gnu_cxx::__bit_find(::std::move(__first), ::std::move(__last), __val);
	}

	template<typename _InputIt, typename _ForwardIt>
	constexpr ::__gnu_cxx::__bit_iterator<_InputIt> find_first_of(
	  ::__gnu_cxx::__bit_iterator<_InputIt> __first, ::__gnu_cxx::__bit_iterator<_InputIt> __last,
	  _ForwardIt __search_first, _ForwardIt __search_last)
	{
		return ::__gnu_cxx::__bit_find_first_of(::std::move(__first), ::std::move(__last),
		  ::std::move(__search_first), ::std::move(__search_last));
	}

	template<typename _It0, typename _It1>
	constexpr bool equal(::__gnu_cxx::__bit_iterator<_It0> __first0,
	  ::__gnu_cxx::__bit_iterator<_It0> __last0, ::__gnu_cxx::__bit_iterator<_It1> __first1,
	  ::__gnu_cxx::__bit_iterator<_It1> __last1)
	{
		return ::__gnu_cxx::__bit_equal(
		  ::std::move(__first0), ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
	}

	template<typename _It0, typename _It1>
	constexpr bool equal(::__gnu_cxx::__bit_iterator<_It0> __first0,
	  ::__gnu_cxx::__bit_iterator<_It0> __last0, ::__gnu_cxx::__bit_iterator<_It1> __first1)
	{
		return ::__gnu_cxx::__bit_equal(
		  ::std::move(__first0), ::std::move(__last0), ::std::move(__first1));
	}

	template<typename _InputIt0, typename _InputIt1>
	constexpr bool lexicographical_compare(::__gnu_cxx::__bit_iterator<_InputIt0> __first0,
	  ::__gnu_cxx::__bit_iterator<_InputIt0> __last0, ::__gnu_cxx::__bit_iterator<_InputIt1> __first1,
	  ::__gnu_cxx::__bit_iterator<_InputIt1> __last1)
	{
		return ::__gnu_cxx::__bit_lexicographical_compare(
		  ::std::move(__first0), ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
	}

	template<typename _It, typename _Type>
	constexpr typename std::iterator_traits<::__gnu_cxx::__bit_iterator<_It>>::difference_type count(
	  ::__gnu_cxx::__bit_iterator<_It> __first, ::__gnu_cxx::__bit_iterator<_It> __last,
	  const _Type& __value)
	{
		return ::__gnu_cxx::__bit_count(::std::move(__first), ::std::move(__last), __value);
	}

	template<typename _ForwardIt>
	constexpr ::__gnu_cxx::__bit_iterator<_ForwardIt> is_sorted_until(
	  ::__gnu_cxx::__bit_iterator<_ForwardIt> __first, ::__gnu_cxx::__bit_iterator<_ForwardIt> __last)
	{
		return ::__gnu_cxx::__bit_is_sorted_until(::std::move(__first), ::std::move(__last));
	}

	template<typename _ForwardIt>
	constexpr bool is_sorted(
	  ::__gnu_cxx::__bit_iterator<_ForwardIt> __first, ::__gnu_cxx::__bit_iterator<_ForwardIt> __last)
	{
		return ::__gnu_cxx::__bit_is_sorted(::std::move(__first), ::std::move(__last));
	}

	template<typename _It, typename _OutputIt>
	constexpr _OutputIt copy(::__gnu_cxx::__bit_iterator<_It> __first,
	  ::__gnu_cxx::__bit_iterator<_It> __last, _OutputIt __out_first)
	{
		return ::__gnu_cxx::__bit_copy(
		  ::std::move(__first), ::std::move(__last), ::std::move(__out_first));
	}

	template<typename _It, typename _Size, typename _OutputIt>
	constexpr _OutputIt copy_n(
	  ::__gnu_cxx::__bit_iterator<_It> __first, _Size __count, _OutputIt __out_first)
	{
		return ::__gnu_cxx::__bit_copy_n(::std::move(__first), __count, ::std::move(__out_first));
	}

	template<typename _ForwardIt, typename _Type>
	constexpr ::__gnu_cxx::__bit_iterator<_ForwardIt> fill(
	  ::__gnu_cxx::__bit_iterator<_ForwardIt> __first, ::__gnu_cxx::__bit_iterator<_ForwardIt> __last,
	  const _Type& __value)
	{
		return ::__gnu_cxx::__bit_fill(::std::move(__first), ::std::move(__last), __value);
	}

	template<typename _OutputIt, typename _Size, typename _Type>
	constexpr ::__gnu_cxx::__bit_iterator<_OutputIt> fill_n(
	  ::__gnu_cxx::__bit_iterator<_OutputIt> __first, _Size __count, const _Type& __value)
	{
		return ::__gnu_cxx::__bit_fill_n(::std::move(__first), ::std::move(__count), __value);
	}

	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std_GLIBCXX_VISIBILITY(default)

#endif // __cplusplus is on 20/2a or better

#endif
