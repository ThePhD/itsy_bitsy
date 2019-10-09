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

#ifndef ITSY_BITSY_DETAIL_EBCO_HPP
#define ITSY_BITSY_DETAIL_EBCO_HPP 1

#if (defined(_MSC_VER)) || (defined(__cplusplus) && __cplusplus >= 201703L)

#include <utility>

#include <itsy/detail/namespace_default_begin.hpp>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	template<typename _Type, ::std::size_t = 0, typename = void>
	struct __ebco
	{
		_Type value;

		__ebco()              = default;
		__ebco(const __ebco&) = default;
		__ebco(__ebco&&)      = default;
		__ebco&
		operator=(const __ebco&) = default;
		__ebco&
		operator=(__ebco&&) = default;
		__ebco(const _Type& v) : value(v){};
		__ebco(_Type&& v) : value(::std::move(v)){};
		__ebco&
		operator=(const _Type& v)
		{
			value = v;
		}
		__ebco&
		operator=(_Type&& v)
		{
			value = ::std::move(v);
		};
		template<typename Arg, typename... Args,
		     typename = ::std::enable_if_t<
		          !::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, __ebco> &&
		          !::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, _Type>>>
		__ebco(Arg&& arg, Args&&... args)
		: _Type(::std::forward<Arg>(arg), ::std::forward<Args>(args)...){};

		_Type&
		_M_get_value()
		{
			return value;
		}

		_Type const&
		_M_get_value() const
		{
			return value;
		}
	};

	template<typename _Type, ::std::size_t _Tag>
	struct __ebco<_Type, _Tag,
	     ::std::enable_if_t<::std::is_class_v<_Type> && !::std::is_final_v<_Type>>> : _Type
	{
		__ebco()              = default;
		__ebco(const __ebco&) = default;
		__ebco(__ebco&&)      = default;
		__ebco(const _Type& v) : _Type(v){};
		__ebco(_Type&& v) : _Type(::std::move(v)){};
		template<typename Arg, typename... Args,
		     typename = ::std::enable_if_t<
		          !::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, __ebco> &&
		          !::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, _Type>>>
		__ebco(Arg&& arg, Args&&... args)
		: _Type(::std::forward<Arg>(arg), ::std::forward<Args>(args)...){};

		__ebco&
		operator=(const __ebco&) = default;
		__ebco&
		operator=(__ebco&&) = default;
		__ebco&
		operator=(const _Type& v)
		{
			static_cast<_Type&>(*this) = v;
		}
		__ebco&
		operator=(_Type&& v)
		{
			static_cast<_Type&>(*this) = ::std::move(v);
		};

		_Type&
		_M_get_value()
		{
			return static_cast<_Type&>(*this);
		}

		_Type const&
		_M_get_value() const
		{
			return static_cast<_Type const&>(*this);
		}
	};
} // namespace ITSY_BITSY_DETAIL_NAMESPACE

#include <itsy/detail/namespace_default_end.hpp>

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_EBCO_HPP
