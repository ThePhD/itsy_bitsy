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

#ifndef ITSY_BITSY_TESTS_CONSTANTS_HPP
#define ITSY_BITSY_TESTS_CONSTANTS_HPP

#include <itsy/bit_iterator.hpp>

#include <cstddef>

#include <list>

namespace bitsy::tests
{

	inline constexpr std::size_t expected_words = 30;

	enum class insert_action
	{
		push_front,
		push_back,
		begin,
		end,
	};

	inline const std::initializer_list<bitsy::bit_value>&
	il_small()
	{
		static std::initializer_list<bitsy::bit_value> src{ true, false, true, false };
		return src;
	}

	inline const std::list<bool>&
	list_small()
	{
		static std::list<bool> src{ true, true, true, false, false, true };
		return src;
	}

	inline const std::list<bool>&
	list_small_all_1()
	{
		static std::list<bool> src{ true, true, true, true, true, true };
		return src;
	}

	inline decltype(auto)
	source_small()
	{
		static bool src[5]{ false, true, false, true, false };
		return (src);
	}

	inline decltype(auto)
	source_small_all_1()
	{
		static bool src[5]{ true, true, true, true, true };
		return (src);
	}

	inline const std::initializer_list<bitsy::bit_value>&
	il_large()
	{
		static std::initializer_list<bitsy::bit_value> src{ true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false };
		return src;
	}

	inline decltype(auto)
	source_large()
	{
		static bool src[]{ true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false };
		return (src);
	}

	inline const std::list<bool>&
	list_large()
	{
		static std::list<bool> src{ true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false, true, false,
			true, false, true, true, false, false, true, false, true, false, true, true, false,
			false, true, false, true, false, true, true, false, false, true, false, true, false,
			true, true, false, false, true, false, true, false, true, true, false, false, true,
			false, true, false, true, true, false, false, true, false, true, false, true, true,
			false, false, true, false, true, false, true, true, false, false, true, false, true,
			false, true, true, false, false, true, false, true, false, true, true, false, false,
			true, false, true, false, true, true, false, false, true, false, true, false, true,
			true, false, false, true, false, true, false, true, true, false, false };
		return src;
	}

	inline decltype(auto)
	source_large_all_1()
	{
		static bool src[]{ true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true };
		return (src);
	}

	inline const std::list<bool>&
	list_large_all_1()
	{
		static std::list<bool> src{ true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true,
			true, true, true, true, true, true, true, true, true, true, true, true, true, true };
		return src;
	}

} // namespace bitsy::tests

#endif // ITSY_BITSY_TESTS_CONSTANTS_HPP
