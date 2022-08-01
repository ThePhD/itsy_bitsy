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

#include <itsy/bitsy.hpp>

#include <cstddef>

#include <list>

namespace bitsy::tests
{

	constexpr std::size_t expected_words = 30;

	enum class insert_action
	{
		push_front,
		push_back,
		begin,
		end,
	};

	using source_small_type       = bool[5];
	using source_small_all_1_type = bool[3];
	using source_large_type       = bool[592];
	using source_large_all_1_type = bool[589];

	template<typename TestType>
	inline const std::initializer_list<TestType>&
	inplace_il_empty()
	{
		static std::initializer_list<TestType> src{};
		return src;
	}

	template<typename TestType>
	inline const std::initializer_list<TestType>&
	inplace_il_small_all_1()
	{
		static constexpr TestType fill_value =
		     static_cast<TestType>(std::numeric_limits<ztd::any_to_underlying_t<TestType>>::max());
		static std::initializer_list<TestType> src{ fill_value };
		return src;
	}

	template<typename TestType>
	inline const std::initializer_list<TestType>&
	inplace_il_large()
	{
		static constexpr TestType fill_value = static_cast<TestType>(0);
		static std::initializer_list<TestType> src{ fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value };
		return src;
	}

	template<typename TestType>
	inline const std::list<TestType>&
	inplace_list_small_all_1()
	{
		static constexpr TestType fill_value =
		     static_cast<TestType>(std::numeric_limits<ztd::any_to_underlying_t<TestType>>::max());
		static std::list<TestType> src{ fill_value };
		return src;
	}

	template<typename TestType>
	inline const std::list<TestType>&
	inplace_list_large_all_0()
	{
		static constexpr TestType fill_value = static_cast<TestType>(0);
		static std::list<TestType> src{ fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value,
			fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value, fill_value };
		return src;
	}

	const std::initializer_list<bitsy::bit_value>&
	il_empty();

	const std::initializer_list<bitsy::bit_value>&
	il_small();

	const std::list<bool>&
	list_small();

	const std::list<bool>&
	list_small_all_1();

	source_small_type&
	source_small();

	source_small_all_1_type&
	source_small_all_1();

	const std::initializer_list<bitsy::bit_value>&
	il_large();

	source_large_type&
	source_large();

	const std::list<bool>&
	list_large();

	source_large_all_1_type&
	source_large_all_1();

	const std::list<bool>&
	list_large_all_1();

} // namespace bitsy::tests

#endif // ITSY_BITSY_TESTS_CONSTANTS_HPP
