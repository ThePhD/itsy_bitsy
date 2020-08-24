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

#include <itsy/version.hpp>

#include <utility>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	template<typename _Type, ::std::size_t = 0, typename = void>
	class __ebco
	{
	private:
		_Type _M_value;

	public:
		__ebco()              = default;
		__ebco(const __ebco&) = default;
		__ebco(__ebco&&)      = default;
		__ebco&
		operator=(const __ebco&) = default;
		__ebco&
		operator=(__ebco&&) = default;
		__ebco(const _Type& v) : _M_value(v){};
		__ebco(_Type&& v) : _M_value(::std::move(v)){};
		__ebco&
		operator=(const _Type& v)
		{
			this->_M_value = v;
			return *this;
		}
		__ebco&
		operator=(_Type&& v)
		{
			this->_M_value = ::std::move(v);
			return *this;
		};
		template<typename Arg, typename... Args,
		     typename =
		          ::std::enable_if_t<!::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, __ebco> &&
		                             !::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, _Type>>>
		__ebco(Arg&& arg, Args&&... args) : _M_value(::std::forward<Arg>(arg), ::std::forward<Args>(args)...)
		{
		}

		_Type&
		_M_get_value()
		{
			return this->_M_value;
		}

		_Type const&
		_M_get_value() const
		{
			return this->_M_value;
		}
	};

	template<typename _Type, ::std::size_t _Tag>
	class __ebco<_Type, _Tag, ::std::enable_if_t<::std::is_class_v<_Type> && !::std::is_final_v<_Type>>>
	: private _Type
	{
	public:
		__ebco()              = default;
		__ebco(const __ebco&) = default;
		__ebco(__ebco&&)      = default;
		__ebco(const _Type& v) : _Type(v){};
		__ebco(_Type&& v) : _Type(::std::move(v)){};
		template<typename Arg, typename... Args,
		     typename =
		          ::std::enable_if_t<!::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, __ebco> &&
		                             !::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, _Type>>>
		__ebco(Arg&& arg, Args&&... args) : _Type(::std::forward<Arg>(arg), ::std::forward<Args>(args)...)
		{
		}

		__ebco&
		operator=(const __ebco&) = default;
		__ebco&
		operator=(__ebco&&) = default;
		__ebco&
		operator=(const _Type& v)
		{
			static_cast<_Type&>(*this) = v;
			return *this;
		}
		__ebco&
		operator=(_Type&& v)
		{
			static_cast<_Type&>(*this) = ::std::move(v);
			return *this;
		}

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
} // namespace ITSY_BITSY_SOURCE_NAMESPACE

#endif // ITSY_BITSY_DETAIL_EBCO_HPP
