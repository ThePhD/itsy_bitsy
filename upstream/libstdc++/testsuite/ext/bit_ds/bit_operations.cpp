// bit data structures extension tests -*- C++ -*-

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

#include <bit_ds_test_case_require.h>

#include <ext/bit>

#include <cstddef>
#include <cstdint>

template<typename TestType>
void
bit_ds_test_case_bit_operations_popcount()
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones   = static_cast<TestType>(
    std::numeric_limits<__gnu_cxx::xx::detail::any_to_underlying_t<TestType>>::max());
	const int zeroes_val          = __gnu_cxx::xx::popcount(zeroes);
	const int expected_zeroes_val = 0;
	const int ones_val            = __gnu_cxx::xx::popcount(ones);
	const int expected_ones_val   = __gnu_cxx::xx::binary_digits_v<TestType>;
	REQUIRE(zeroes_val == expected_zeroes_val);
	REQUIRE(ones_val == expected_ones_val);

	SECTION("value lsb -> msb")
	{
		TestType val{};
		for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
			{
				val |= static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = __gnu_cxx::xx::popcount(val);
				const int expected_value = static_cast<int>(i + 1);
				REQUIRE(value == expected_value);
			}
	}
	SECTION("value msb -> lsb")
	{
		TestType val{};
		for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
			{
				val |= TestType(static_cast<TestType>(1) << i);
				const int value          = __gnu_cxx::xx::popcount(val);
				const int expected_value = static_cast<int>(__gnu_cxx::xx::binary_digits_v<TestType> - i);
				REQUIRE(value == expected_value);
			}
	}
}

template<typename TestType>
void
bit_ds_test_case_bit_operations_firstrl_one()
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones   = static_cast<TestType>(
    std::numeric_limits<__gnu_cxx::xx::detail::any_to_underlying_t<TestType>>::max());

	const int firstr_one_zeroes_val          = __gnu_cxx::xx::firstr_one(zeroes);
	const int firstl_one_zeroes_val          = __gnu_cxx::xx::firstl_one(zeroes);
	const int expected_firstr_one_zeroes_val = 0;
	const int expected_firstl_one_zeroes_val = 0;
	const int firstr_one_ones_val            = __gnu_cxx::xx::firstr_one(ones);
	const int firstl_one_ones_val            = __gnu_cxx::xx::firstl_one(ones);
	const int expected_firstr_one_ones_val   = 1;
	const int expected_firstl_one_ones_val   = 1;
	REQUIRE(firstr_one_ones_val == expected_firstr_one_ones_val);
	REQUIRE(firstl_one_ones_val == expected_firstl_one_ones_val);
	REQUIRE(firstr_one_zeroes_val == expected_firstr_one_zeroes_val);
	REQUIRE(firstl_one_zeroes_val == expected_firstl_one_zeroes_val);

	SECTION("val lsb -> msb")
	{
		SECTION("firstr_one")
		{
			for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
				{
					TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = __gnu_cxx::xx::firstr_one(val);
					const int expected_value = static_cast<int>(i + 1);
					REQUIRE(value == expected_value);
				}
		}
		SECTION("firstl_one")
		{
			for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
				{
					TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = __gnu_cxx::xx::firstl_one(val);
					const int expected_value = static_cast<int>(__gnu_cxx::xx::binary_digits_v<TestType> - i);
					REQUIRE(value == expected_value);
				}
		}
	}
	SECTION("val msb -> lsb")
	{
		SECTION("firstr_one")
		{
			for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
				{
					TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = __gnu_cxx::xx::firstr_one(val);
					const int expected_value = static_cast<int>(i + 1);
					REQUIRE(value == expected_value);
				}
		}
		SECTION("firstl_one")
		{
			for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
				{
					TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = __gnu_cxx::xx::firstl_one(val);
					const int expected_value = static_cast<int>(__gnu_cxx::xx::binary_digits_v<TestType> - i);
					REQUIRE(value == expected_value);
				}
		}
	}
}

template<typename TestType>
void
bit_ds_test_case_bit_operations_firstrl_zero()
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones   = static_cast<TestType>(
    std::numeric_limits<__gnu_cxx::xx::detail::any_to_underlying_t<TestType>>::max());
	const int firstr_zero_zeroes_val          = __gnu_cxx::xx::firstr_zero(zeroes);
	const int firstl_zero_zeroes_val          = __gnu_cxx::xx::firstl_zero(zeroes);
	const int expected_firstr_zero_zeroes_val = 1;
	const int expected_firstl_zero_zeroes_val = 1;
	const int firstr_zero_ones_val            = __gnu_cxx::xx::firstr_zero(ones);
	const int firstl_zero_ones_val            = __gnu_cxx::xx::firstl_zero(ones);
	const int expected_firstr_zero_ones_val   = 0;
	const int expected_firstl_zero_ones_val   = 0;
	REQUIRE(firstr_zero_zeroes_val == expected_firstr_zero_zeroes_val);
	REQUIRE(firstl_zero_zeroes_val == expected_firstl_zero_zeroes_val);
	REQUIRE(firstr_zero_ones_val == expected_firstr_zero_ones_val);
	REQUIRE(firstl_zero_ones_val == expected_firstl_zero_ones_val);

	SECTION("val lsb -> msb")
	{
		SECTION("firstr_zero")
		{
			for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
				{
					TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = __gnu_cxx::xx::firstr_zero(val);
					const int expected_value = static_cast<int>(i + 1);
					REQUIRE(value == expected_value);
				}
		}
		SECTION("firstl_zero")
		{
			for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
				{
					TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = __gnu_cxx::xx::firstl_zero(val);
					const int expected_value = static_cast<int>(__gnu_cxx::xx::binary_digits_v<TestType> - i);
					REQUIRE(value == expected_value);
				}
		}
	}
	SECTION("val msb -> lsb")
	{
		SECTION("firstr_zero")
		{
			for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
				{
					TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = __gnu_cxx::xx::firstr_zero(val);
					const int expected_value = static_cast<int>(i + 1);
					REQUIRE(value == expected_value);
				}
		}
		SECTION("firstl_zero")
		{
			for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
				{
					TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = __gnu_cxx::xx::firstl_zero(val);
					const int expected_value = static_cast<int>(__gnu_cxx::xx::binary_digits_v<TestType> - i);
					REQUIRE(value == expected_value);
				}
		}
	}
}

template<typename TestType>
void
bit_ds_test_case_bit_operations_countrl_one()
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones   = static_cast<TestType>(
    std::numeric_limits<__gnu_cxx::xx::detail::any_to_underlying_t<TestType>>::max());

	const int countr_one_zeroes_val          = __gnu_cxx::xx::countr_one(zeroes);
	const int countl_one_zeroes_val          = __gnu_cxx::xx::countl_one(zeroes);
	const int expected_countr_one_zeroes_val = 0;
	const int expected_countl_one_zeroes_val = 0;
	const int countr_one_ones_val            = __gnu_cxx::xx::countr_one(ones);
	const int countl_one_ones_val            = __gnu_cxx::xx::countl_one(ones);
	const int expected_countr_one_ones_val   = __gnu_cxx::xx::binary_digits_v<TestType>;
	const int expected_countl_one_ones_val   = __gnu_cxx::xx::binary_digits_v<TestType>;
	REQUIRE(countr_one_ones_val == expected_countr_one_ones_val);
	REQUIRE(countl_one_ones_val == expected_countl_one_ones_val);
	REQUIRE(countr_one_zeroes_val == expected_countr_one_zeroes_val);
	REQUIRE(countl_one_zeroes_val == expected_countl_one_zeroes_val);

	SECTION("val lsb -> msb")
	{
		SECTION("countr_one")
		{
			for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
				{
					auto underlying_val =
					  __gnu_cxx::xx::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = __gnu_cxx::xx::countr_one(val);
					const int expected_value = static_cast<int>(i + 1);
					REQUIRE(value == expected_value);
				}
		}
		SECTION("countl_one")
		{
			for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
				{
					auto underlying_val =
					  __gnu_cxx::xx::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val    = ones & val_mask;
					const int value = __gnu_cxx::xx::countl_one(val);
					const int expected_value =
					  (i == (__gnu_cxx::xx::binary_digits_v<TestType> - 1)__gnu_cxx::nu_cxx::binary_digits_v<TestType> : 0;
					REQUIRE(value == expected_value);
				}
		}
	}
	SECTION("val msb -> lsb")
	{
		SECTION("countr_one")
		{
			for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
				{
					auto underlying_val =
					  __gnu_cxx::xx::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = __gnu_cxx::xx::countr_one(val);
					const int expected_value = static_cast<int>(i + 1);
					REQUIRE(value == expected_value);
				}
		}
		SECTION("countl_one")
		{
			for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
				{
					auto underlying_val =
					  __gnu_cxx::xx::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val    = ones & val_mask;
					const int value = __gnu_cxx::xx::countl_one(val);
					const int expected_value =
					  (i == (__gnu_cxx::xx::binary_digits_v<TestType> - 1)__gnu_cxx::nu_cxx::binary_digits_v<TestType> : 0;
					REQUIRE(value == expected_value);
				}
		}
	}
}

template<typename TestType>
void
bit_ds_test_case_bit_operations_countrl_zero()
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones   = static_cast<TestType>(
    std::numeric_limits<__gnu_cxx::xx::detail::any_to_underlying_t<TestType>>::max());
	const int countr_zero_zeroes_val          = __gnu_cxx::xx::countr_zero(zeroes);
	const int countl_zero_zeroes_val          = __gnu_cxx::xx::countl_zero(zeroes);
	const int expected_countr_zero_zeroes_val = __gnu_cxx::xx::binary_digits_v<TestType>;
	const int expected_countl_zero_zeroes_val = __gnu_cxx::xx::binary_digits_v<TestType>;
	const int countr_zero_ones_val            = __gnu_cxx::xx::countr_zero(ones);
	const int countl_zero_ones_val            = __gnu_cxx::xx::countl_zero(ones);
	const int expected_countr_zero_ones_val   = 0;
	const int expected_countl_zero_ones_val   = 0;
	REQUIRE(countr_zero_zeroes_val == expected_countr_zero_zeroes_val);
	REQUIRE(countl_zero_zeroes_val == expected_countl_zero_zeroes_val);
	REQUIRE(countr_zero_ones_val == expected_countr_zero_ones_val);
	REQUIRE(countl_zero_ones_val == expected_countl_zero_ones_val);

	SECTION("val lsb -> msb")
	{
		SECTION("countr_zero")
		{
			for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
				{
					auto underlying_val =
					  __gnu_cxx::xx::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = __gnu_cxx::xx::countr_zero(val);
					const int expected_value = 0;
					REQUIRE(value == expected_value);
				}
		}
		SECTION("countl_zero")
		{
			for (std::size_t i = 0; i < __gnu_cxx::xx::binary_digits_v<TestType>; ++i)
				{
					auto underlying_val =
					  __gnu_cxx::xx::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val    = ones & val_mask;
					const int value = __gnu_cxx::xx::countl_zero(val);
					const int expected_value =
					  static_cast<int>(__gnu_cxx::xx::binary_digits_v<TestType> - (i + 1));
					REQUIRE(value == expected_value);
				}
		}
	}
	SECTION("val msb -> lsb")
	{
		SECTION("countr_zero")
		{
			for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
				{
					auto underlying_val =
					  __gnu_cxx::xx::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = __gnu_cxx::xx::countr_zero(val);
					const int expected_value = 0;
					REQUIRE(value == expected_value);
				}
		}
		SECTION("countl_zero")
		{
			for (std::size_t i = __gnu_cxx::xx::binary_digits_v<TestType>; i-- > 0;)
				{
					auto underlying_val =
					  __gnu_cxx::xx::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val    = ones & val_mask;
					const int value = __gnu_cxx::xx::countl_zero(val);
					const int expected_value =
					  static_cast<int>(__gnu_cxx::xx::binary_digits_v<TestType> - (i + 1));
					REQUIRE(value == expected_value);
				}
		}
	}
}

template<typename... TestTypes>
void
bit_ds_test_cases()
{
	bit_ds_test_case_countrl_zero<TestTypes>()...;
	bit_ds_test_case_countrl_one<TestTypes>()...;
	bit_ds_test_case_firstrl_zero<TestTypes>()...;
	bit_ds_test_case_firstrl_one<TestTypes>()...;
	bit_ds_test_case_popcount<TestTypes>()...;
}

int
main()
{
	bit_ds_test_cases<std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte,
	  std::int64_t, std::int32_t, std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char,
	  signed char, std::size_t, std::ptrdiff_t>();
	return 0;
}
