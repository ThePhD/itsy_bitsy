// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy/tests/constants.hpp>

#include <cstddef>

#include <list>

namespace bitsy::tests
{

	const std::initializer_list<bitsy::bit_value>&
	il_empty()
	{
		static std::initializer_list<bitsy::bit_value> src{};
		return src;
	}

	const std::initializer_list<bitsy::bit_value>&
	il_small()
	{
		static std::initializer_list<bitsy::bit_value> src{ true, false, true, false };
		return src;
	}

	const std::list<bool>&
	list_small()
	{
		static std::list<bool> src{ true, true, true, false, false, true };
		return src;
	}

	const std::list<bool>&
	list_small_all_1()
	{
		static std::list<bool> src{ true, true, true, true, true, true };
		return src;
	}

	source_small_type&
	source_small()
	{
		static bool src[5]{ false, true, false, true, false };
		return src;
	}

	source_small_all_1_type&
	source_small_all_1()
	{
		static bool src[3]{ true, true, true };
		return src;
	}

	const std::initializer_list<bitsy::bit_value>&
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

	source_large_type&
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
		return src;
	}

	const std::list<bool>&
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

	source_large_all_1_type&
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
		return src;
	}

	const std::list<bool>&
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
