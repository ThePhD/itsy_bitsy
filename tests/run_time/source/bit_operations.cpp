// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#include <testsuite_hooks.h>

#include <itsy/bitsy.hpp>

#include <cstddef>
#include <cstdint>

TEMPLATE_TEST_CASE("bit_operations with popcount", "[bit_operations][popcount]", std::uint64_t,
  std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t,
  std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones =
	  static_cast<TestType>(std::numeric_limits<bitsy::detail::any_to_underlying_t<TestType>>::max());
	const int zeroes_val          = bitsy::popcount(zeroes);
	const int expected_zeroes_val = 0;
	const int ones_val            = bitsy::popcount(ones);
	const int expected_ones_val   = bitsy::binary_digits_v<TestType>;
	VERIFY(zeroes_val == expected_zeroes_val);
	VERIFY(ones_val == expected_ones_val);

	SECTION("value lsb -> msb")
	{
		TestType val{};
		for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
			{
				val |= static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = bitsy::popcount(val);
				const int expected_value = static_cast<int>(i + 1);
				VERIFY(value == expected_value);
			}
	}
	SECTION("value msb -> lsb")
	{
		TestType val{};
		for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
			{
				val |= TestType(static_cast<TestType>(1) << i);
				const int value          = bitsy::popcount(val);
				const int expected_value = static_cast<int>(bitsy::binary_digits_v<TestType> - i);
				VERIFY(value == expected_value);
			}
	}
}

TEMPLATE_TEST_CASE("bit_operations with first(r/l)_one", "[bit_operations][first(r/l)_one]",
  std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
  std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t,
  std::ptrdiff_t)
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones =
	  static_cast<TestType>(std::numeric_limits<bitsy::detail::any_to_underlying_t<TestType>>::max());

	const int firstr_one_zeroes_val          = bitsy::firstr_one(zeroes);
	const int firstl_one_zeroes_val          = bitsy::firstl_one(zeroes);
	const int expected_firstr_one_zeroes_val = 0;
	const int expected_firstl_one_zeroes_val = 0;
	const int firstr_one_ones_val            = bitsy::firstr_one(ones);
	const int firstl_one_ones_val            = bitsy::firstl_one(ones);
	const int expected_firstr_one_ones_val   = 1;
	const int expected_firstl_one_ones_val   = 1;
	VERIFY(firstr_one_ones_val == expected_firstr_one_ones_val);
	VERIFY(firstl_one_ones_val == expected_firstl_one_ones_val);
	VERIFY(firstr_one_zeroes_val == expected_firstr_one_zeroes_val);
	VERIFY(firstl_one_zeroes_val == expected_firstl_one_zeroes_val);

	SECTION("val lsb -> msb")
	{
		SECTION("firstr_one")
		{
			for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
				{
					TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = bitsy::firstr_one(val);
					const int expected_value = static_cast<int>(i + 1);
					VERIFY(value == expected_value);
				}
		}
		SECTION("firstl_one")
		{
			for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
				{
					TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = bitsy::firstl_one(val);
					const int expected_value = static_cast<int>(bitsy::binary_digits_v<TestType> - i);
					VERIFY(value == expected_value);
				}
		}
	}
	SECTION("val msb -> lsb")
	{
		SECTION("firstr_one")
		{
			for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
				{
					TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = bitsy::firstr_one(val);
					const int expected_value = static_cast<int>(i + 1);
					VERIFY(value == expected_value);
				}
		}
		SECTION("firstl_one")
		{
			for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
				{
					TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = bitsy::firstl_one(val);
					const int expected_value = static_cast<int>(bitsy::binary_digits_v<TestType> - i);
					VERIFY(value == expected_value);
				}
		}
	}
}

TEMPLATE_TEST_CASE("bit_operations with first(r/l)_zero", "[bit_operations][first(r/l)_zero]",
  std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
  std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t,
  std::ptrdiff_t)
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones =
	  static_cast<TestType>(std::numeric_limits<bitsy::detail::any_to_underlying_t<TestType>>::max());
	const int firstr_zero_zeroes_val          = bitsy::firstr_zero(zeroes);
	const int firstl_zero_zeroes_val          = bitsy::firstl_zero(zeroes);
	const int expected_firstr_zero_zeroes_val = 1;
	const int expected_firstl_zero_zeroes_val = 1;
	const int firstr_zero_ones_val            = bitsy::firstr_zero(ones);
	const int firstl_zero_ones_val            = bitsy::firstl_zero(ones);
	const int expected_firstr_zero_ones_val   = 0;
	const int expected_firstl_zero_ones_val   = 0;
	VERIFY(firstr_zero_zeroes_val == expected_firstr_zero_zeroes_val);
	VERIFY(firstl_zero_zeroes_val == expected_firstl_zero_zeroes_val);
	VERIFY(firstr_zero_ones_val == expected_firstr_zero_ones_val);
	VERIFY(firstl_zero_ones_val == expected_firstl_zero_ones_val);

	SECTION("val lsb -> msb")
	{
		SECTION("firstr_zero")
		{
			for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
				{
					TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = bitsy::firstr_zero(val);
					const int expected_value = static_cast<int>(i + 1);
					VERIFY(value == expected_value);
				}
		}
		SECTION("firstl_zero")
		{
			for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
				{
					TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = bitsy::firstl_zero(val);
					const int expected_value = static_cast<int>(bitsy::binary_digits_v<TestType> - i);
					VERIFY(value == expected_value);
				}
		}
	}
	SECTION("val msb -> lsb")
	{
		SECTION("firstr_zero")
		{
			for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
				{
					TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = bitsy::firstr_zero(val);
					const int expected_value = static_cast<int>(i + 1);
					VERIFY(value == expected_value);
				}
		}
		SECTION("firstl_zero")
		{
			for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
				{
					TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
					const int value          = bitsy::firstl_zero(val);
					const int expected_value = static_cast<int>(bitsy::binary_digits_v<TestType> - i);
					VERIFY(value == expected_value);
				}
		}
	}
}

TEMPLATE_TEST_CASE("bit_operations with count(r/l)_one", "[bit_operations][count(r/l)_one]",
  std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
  std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t,
  std::ptrdiff_t)
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones =
	  static_cast<TestType>(std::numeric_limits<bitsy::detail::any_to_underlying_t<TestType>>::max());

	const int countr_one_zeroes_val          = bitsy::countr_one(zeroes);
	const int countl_one_zeroes_val          = bitsy::countl_one(zeroes);
	const int expected_countr_one_zeroes_val = 0;
	const int expected_countl_one_zeroes_val = 0;
	const int countr_one_ones_val            = bitsy::countr_one(ones);
	const int countl_one_ones_val            = bitsy::countl_one(ones);
	const int expected_countr_one_ones_val   = bitsy::binary_digits_v<TestType>;
	const int expected_countl_one_ones_val   = bitsy::binary_digits_v<TestType>;
	VERIFY(countr_one_ones_val == expected_countr_one_ones_val);
	VERIFY(countl_one_ones_val == expected_countl_one_ones_val);
	VERIFY(countr_one_zeroes_val == expected_countr_one_zeroes_val);
	VERIFY(countl_one_zeroes_val == expected_countl_one_zeroes_val);

	SECTION("val lsb -> msb")
	{
		SECTION("countr_one")
		{
			for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
				{
					auto underlying_val =
					  bitsy::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = bitsy::countr_one(val);
					const int expected_value = static_cast<int>(i + 1);
					VERIFY(value == expected_value);
				}
		}
		SECTION("countl_one")
		{
			for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
				{
					auto underlying_val =
					  bitsy::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val    = ones & val_mask;
					const int value = bitsy::countl_one(val);
					const int expected_value =
					  (i == (bitsy::binary_digits_v<TestType> - 1)) ? bitsy::binary_digits_v<TestType> : 0;
					VERIFY(value == expected_value);
				}
		}
	}
	SECTION("val msb -> lsb")
	{
		SECTION("countr_one")
		{
			for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
				{
					auto underlying_val =
					  bitsy::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = bitsy::countr_one(val);
					const int expected_value = static_cast<int>(i + 1);
					VERIFY(value == expected_value);
				}
		}
		SECTION("countl_one")
		{
			for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
				{
					auto underlying_val =
					  bitsy::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val    = ones & val_mask;
					const int value = bitsy::countl_one(val);
					const int expected_value =
					  (i == (bitsy::binary_digits_v<TestType> - 1)) ? bitsy::binary_digits_v<TestType> : 0;
					VERIFY(value == expected_value);
				}
		}
	}
}

TEMPLATE_TEST_CASE("bit_operations with count(r/l)_zero", "[bit_operations][count(r/l)_zero]",
  std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
  std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t,
  std::ptrdiff_t)
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones =
	  static_cast<TestType>(std::numeric_limits<bitsy::detail::any_to_underlying_t<TestType>>::max());
	const int countr_zero_zeroes_val          = bitsy::countr_zero(zeroes);
	const int countl_zero_zeroes_val          = bitsy::countl_zero(zeroes);
	const int expected_countr_zero_zeroes_val = bitsy::binary_digits_v<TestType>;
	const int expected_countl_zero_zeroes_val = bitsy::binary_digits_v<TestType>;
	const int countr_zero_ones_val            = bitsy::countr_zero(ones);
	const int countl_zero_ones_val            = bitsy::countl_zero(ones);
	const int expected_countr_zero_ones_val   = 0;
	const int expected_countl_zero_ones_val   = 0;
	VERIFY(countr_zero_zeroes_val == expected_countr_zero_zeroes_val);
	VERIFY(countl_zero_zeroes_val == expected_countl_zero_zeroes_val);
	VERIFY(countr_zero_ones_val == expected_countr_zero_ones_val);
	VERIFY(countl_zero_ones_val == expected_countl_zero_ones_val);

	SECTION("val lsb -> msb")
	{
		SECTION("countr_zero")
		{
			for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
				{
					auto underlying_val =
					  bitsy::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = bitsy::countr_zero(val);
					const int expected_value = 0;
					VERIFY(value == expected_value);
				}
		}
		SECTION("countl_zero")
		{
			for (std::size_t i = 0; i < bitsy::binary_digits_v<TestType>; ++i)
				{
					auto underlying_val =
					  bitsy::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = bitsy::countl_zero(val);
					const int expected_value = static_cast<int>(bitsy::binary_digits_v<TestType> - (i + 1));
					VERIFY(value == expected_value);
				}
		}
	}
	SECTION("val msb -> lsb")
	{
		SECTION("countr_zero")
		{
			for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
				{
					auto underlying_val =
					  bitsy::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = bitsy::countr_zero(val);
					const int expected_value = 0;
					VERIFY(value == expected_value);
				}
		}
		SECTION("countl_zero")
		{
			for (std::size_t i = bitsy::binary_digits_v<TestType>; i-- > 0;)
				{
					auto underlying_val =
					  bitsy::detail::to_underlying_if_enum_or_char_t(static_cast<TestType>(1) << i);
					TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
					TestType val_mask =
					  static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
					TestType val             = ones & val_mask;
					const int value          = bitsy::countl_zero(val);
					const int expected_value = static_cast<int>(bitsy::binary_digits_v<TestType> - (i + 1));
					VERIFY(value == expected_value);
				}
		}
	}
}
