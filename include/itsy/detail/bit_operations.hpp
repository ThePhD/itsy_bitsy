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

#ifndef ITSY_BITSY_DETAIL_BIT_OPERATIONS_HPP
#define ITSY_BITSY_DETAIL_BIT_OPERATIONS_HPP 1

#include <itsy/version.hpp>

#include <itsy/detail/bit_detail.hpp>

#include <climits>
#if ITSY_BITSY_IS_ON(ITSY_BITSY_STD_LIB_BIT_I_)
#include <bit>
#endif // C++20 Bit Operations

#if ITSY_BITSY_IS_ON(ITSY_BITSY_LIBVCXX_I_)
#include <intrin.h>
#else

#endif // VC++ vs. Others

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	template<typename _Integralish>
	constexpr int
	__bit_basic_countl_zero(_Integralish __val) noexcept
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
	constexpr int
	__bit_basic_countl_one(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __is_set = (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
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
	constexpr int
	__bit_basic_countr_zero(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
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
	constexpr int
	__bit_basic_countr_one(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
			{
				bool __is_set = (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
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
	constexpr int
	__bit_basic_firstr_one(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
			{
				bool __is_set = (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				                static_cast<_Integralish>(0);
				if (__is_set)
					{
						return static_cast<int>(__bit_index + 1);
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_firstr_zero(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
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
	constexpr int
	__bit_basic_firstl_one(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __is_set = (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				                static_cast<_Integralish>(0);
				if (__is_set)
					{
						return static_cast<int>(__binary_digits_v<_Integralish> - __bit_index);
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_firstl_zero(_Integralish __val) noexcept
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
	constexpr int
	__bit_basic_popcount(_Integralish __val) noexcept
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
				for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
					{
						bool __is_set = (__val & (static_cast<_Integralish>(1) << __bit_index)) !=
						                static_cast<_Integralish>(0);
						__num += static_cast<int>(__is_set);
					}
				return __num;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_countl_zero(_Integralish __val) noexcept
	{
#if ITSY_BITSY_IS_ON(ITSY_BITSY_STD_LIB_BIT_I_)
		return ::std::countl_zero(__val);
#elif ITSY_BITSY_IS_ON(ITSY_BITSY_VCXX_I_)
#if ITSY_BITSY_IS_ON(ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT_I_)
		if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				unsigned long __index;
				auto __scanval = _BitScanReverse(&__index, __val);
				if (__scanval == 0)
					{
						return __binary_digits_v<_Integralish>;
					}
				return static_cast<int>(__index);
			}
#if INTPTR_MAX >= INT64_MAX
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				unsigned long __index;
				auto __scanval = _BitScanReverse64(&__index, __val);
				if (__scanval == 0)
					{
						return __binary_digits_v<_Integralish>;
					}
				return static_cast<int>(__index);
			}
#endif // 64-bit MSVC only
		else
			{
				return __bit_basic_countl_zero(__val);
			}
#else
		return __bit_basic_countl_zero(__val);
#endif // MSVC lacks constexpr
#else
		if (__val == 0)
			{
				return static_cast<int>(__binary_digits_v<_Integralish>);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_clz(__val) - (__binary_digits_v<unsigned int> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_clzl(__val) - (__binary_digits_v<unsigned long> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_clzll(__val) -
				       (__binary_digits_v<unsigned long long> - __binary_digits_v<_Integralish>);
			}
		else
			{
				return __bit_basic_countl_zero(__val);
			}
#endif
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_countl_one(_Integralish __val) noexcept
	{
		return __bit_unsigned_countl_zero(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_countr_zero(_Integralish __val) noexcept
	{
#if ITSY_BITSY_IS_ON(ITSY_BITSY_STD_LIB_BIT_I_)
		return ::std::countr_zero(__val);
#elif ITSY_BITSY_IS_ON(ITSY_BITSY_VCXX_I_)
#if ITSY_BITSY_IS_ON(ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT_I_)
		if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				unsigned long __index;
				auto __scanval = _BitScanForward(&__index, __val);
				if (__scanval == 0)
					{
						return __binary_digits_v<_Integralish>;
					}
				return static_cast<int>(__index);
			}
#if INTPTR_MAX >= INT64_MAX
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				// _BitScanX64 does not exist in 32-bit
				unsigned long __index;
				auto __scanval = _BitScanForward64(&__index, __val);
				if (__scanval == 0)
					{
						return __binary_digits_v<_Integralish>;
					}
				return static_cast<int>(__index);
			}
#endif // 64-bit MSVC only
		else
			{
				return  __bit_basic_countr_zero(__val);
			}
#else
		return __bit_basic_countr_zero(__val);
#endif // MSVC lacks constexpr
#else
		if (__val == 0)
			{
				return static_cast<int>(__binary_digits_v<_Integralish>);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_ctz(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_ctzl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_ctzll(__val);
			}
		else
			{
				return __bit_basic_countr_zero(__val);
			}
#endif
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_countr_one(_Integralish __val) noexcept
	{
		return __bit_unsigned_countr_zero(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_firstr_one(_Integralish __val) noexcept
	{
#if ITSY_BITSY_IS_ON(ITSY_BITSY_VCXX_I_)
#if ITSY_BITSY_IS_ON(ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT_I_)
		if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				unsigned long __index;
				auto __scanval = _BitScanForward(&__index, __val);
				if (__scanval == 0)
					{
						return 0;
					}
				return static_cast<int>(__index + 1);
			}
#if INTPTR_MAX >= INT64_MAX
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				unsigned long __index;
				auto __scanval = _BitScanForward64(&__index, __val);
				if (__scanval == 0)
					{
						return 0;
					}
				return static_cast<int>(__index + 1);
			}
#endif // 64-bit MSVC only
		else
			{
				return __bit_basic_firstr_one(__val);
			}
#else
		return __bit_basic_firstr_one(__val);
#endif // MSVC lacks constexpr
#else
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_ffs(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_ffsl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_ffsll(__val);
			}
		else
			{
				return __bit_basic_firstr_one(__val);
			}
#endif
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_firstr_zero(_Integralish __val) noexcept
	{
		return __bit_unsigned_firstr_one(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_firstl_one(_Integralish __val) noexcept
	{
#if ITSY_BITSY_IS_ON(ITSY_BITSY_VCXX_I_)
#if ITSY_BITSY_IS_ON(ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT_I_)
		if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				unsigned long __index;
				auto __scanval = _BitScanReverse(&__index, __val);
				if (__scanval == 0)
					{
						return 0;
					}
				return static_cast<int>(__index);
			}
#if INTPTR_MAX >= INT64_MAX
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				unsigned long __index;
				auto __scanval = _BitScanReverse64(&__index, __val);
				if (__scanval == 0)
					{
						return 0;
					}
				return static_cast<int>(__index);
			}
#endif // 64-bit MSVC only
		else
			{
				return __bit_basic_firstl_one(__val);
			}
#else
		return __bit_basic_firstl_one(__val);
#endif // MSVC lacks constexpr
#else
		if (__val == 0)
			{
				return static_cast<int>(0);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_clz(__val) + 1 -
				       (__binary_digits_v<unsigned int> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_clzl(__val) + 1 -
				       (__binary_digits_v<unsigned long> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_clzll(__val) + 1 -
				       (__binary_digits_v<unsigned long long> - __binary_digits_v<_Integralish>);
			}
		else
			{
				return __bit_basic_firstl_one(__val);
			}
#endif
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_firstl_zero(_Integralish __val) noexcept
	{
		return __bit_unsigned_firstl_one(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_popcount(_Integralish __val) noexcept
	{
#if ITSY_BITSY_IS_ON(ITSY_BITSY_STD_LIB_BIT_I_)
		return ::std::popcount(__val);
#elif ITSY_BITSY_IS_ON(ITSY_BITSY_VCXX_I_)
#if ITSY_BITSY_IS_ON(ITSY_BITSY_NONPORTABLE_MSVC_INTRINSICS_I_)
		// WARNING
		// THESE INSTRUCTIONS ARE NOT PORTABLE
		// FIXME: REPLACE WITH SOMETHING MORE PORTABLE,
		// TEST CPUID AND FRIENDS FOR THESE FUNCTIONS,
		// ETC.
		if constexpr (__binary_digits_v<_Integralish> <= 16)
			{
				return static_cast<int>(__popcnt16(__val));
			}
		else if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				return static_cast<int>(__popcnt(__val));
			}
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				return static_cast<int>(__popcnt64(__val));
			}
		else
			{
				return __bit_basic_popcount(__val);
			}
#else
		return __bit_basic_popcount(__val);
#endif
#else
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_popcountl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_popcountl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_popcountll(__val);
			}
		else
			{
				return __bit_basic_popcount(__val);
			}
#endif // Standard C++20 vs. VC++ vs. Others
	}

	template<typename _Integralish>
	constexpr int
	__bit_countl_zero(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_countl_zero(__to_underlying_if_enum_or_char_t(__val));
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
				int __bit_countl_zero_val = __bit_unsigned_countl_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// remove +1 that comes from sign bit
						--__bit_countl_zero_val;
					}
				return __bit_countl_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_countl_one(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_countl_one(__to_underlying_if_enum_or_char_t(__val));
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
				int __bit_countl_one_val = __bit_unsigned_countl_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// remove +1 that comes from sign bit
						--__bit_countl_one_val;
					}
				return __bit_countl_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_countr_zero(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_countr_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish       = ::std::make_unsigned_t<_Integralish>;
				int __bit_countr_zero_val = __bit_unsigned_countr_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_countr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return __binary_digits_v<_Integralish>;
							}
					}
				return __bit_countr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_countr_one(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_countr_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish       = ::std::make_unsigned_t<_Integralish>;
				int __bit_countr_zero_val = __bit_unsigned_countr_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_countr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return __binary_digits_v<_Integralish>;
							}
					}
				return __bit_countr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_firstr_one(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_firstr_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish      = ::std::make_unsigned_t<_Integralish>;
				int __bit_firstr_one_val = __bit_unsigned_firstr_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_firstr_one_val == __binary_digits_v<_UIntegralish>)
							{
								return 0;
							}
					}
				return __bit_firstr_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_firstr_zero(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_firstr_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish       = ::std::make_unsigned_t<_Integralish>;
				int __bit_firstr_zero_val = __bit_unsigned_firstr_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_firstr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return 0;
							}
					}
				return __bit_firstr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_firstl_one(_Integralish __val)
	{

		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_firstl_one(__to_underlying_if_enum_or_char_t(__val));
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
				int __bit_firstl_one_val = __bit_unsigned_firstl_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_firstl_one_val == 0)
							{
								return 0;
							}
						--__bit_firstl_one_val;
					}
				return __bit_firstl_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_firstl_zero(_Integralish __val)
	{

		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_firstl_zero(__to_underlying_if_enum_or_char_t(__val));
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
				int __bit_firstl_zero_val = __bit_unsigned_firstl_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_firstl_zero_val == 0)
							{
								return 0;
							}
						return __bit_firstl_zero_val - 1;
					}
				else
					{
						return __bit_firstl_zero_val;
					}
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_popcount(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_popcount(__to_underlying_if_enum_or_char_t(__val));
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
				int __bit_popcount_val = __bit_unsigned_popcount(static_cast<_UIntegralish>(__val));
				return __bit_popcount_val;
			}
	}

	template<typename _Pos, typename _Mask>
	inline constexpr _Pos
	__mask_to_pos(_Mask __mask) noexcept
	{
		if (__mask == static_cast<_Mask>(0))
			{
				return static_cast<_Pos>(0);
			}
		return static_cast<_Pos>(__bit_firstr_one(__mask) - 1);
	}

	template<typename _Mask, typename _Pos>
	inline constexpr _Mask
	__pos_to_mask(_Pos __pos) noexcept
	{
		return static_cast<_Mask>(static_cast<_Mask>(1) << __pos);
	}

	template<typename _Mask, typename _Pos>
	inline constexpr _Mask
	__pos_to_all_1_mask(_Pos __pos) noexcept
	{
		_Mask __mask(static_cast<_Mask>(2) << __pos);
		__mask = static_cast<_Mask>(__to_underlying_if_enum_or_char_t(__mask) - 1);
		return __mask;
	}

	template<typename _Word, bool _ShiftLeft, bool _PreserveLeft, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void
	__shift_and_preserve(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
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
	inline constexpr void
	__shift_left_preserve_right(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, true, false>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void
	__shift_right_preserve_right(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, false, false>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void
	__shift_left_preserve_left(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, true, true>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void
	__shift_right_preserve_left(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, false, true>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Pos>
	inline constexpr _Word
	__merge_bits_at(_Word& __lsb, _Word& __msb, _Pos __bit_position)
	{
		_Word __lsb_mask = __pos_to_all_1_mask<_Word>(__bit_position);
		_Word __msb_mask = ~__lsb_mask;
		return (__lsb & __lsb_mask) | (__msb & __msb_mask);
	}

	template<typename _Word, typename _Ref, typename _Pos>
	inline constexpr _Word
	__replace_most_significant_bits_from(_Ref& __target, _Ref& __donor, _Pos __num_bits)
	{
		_Word __donor_give_mask  = __pos_to_all_1_mask<_Word>(__num_bits - 1);
		_Word __target_keep_mask = (~__donor_give_mask) >> __num_bits;
		_Pos __at                = __binary_digits_v<_Word> - __num_bits;
		return (__target & __target_keep_mask) | ((__donor & __donor_give_mask) << __at);
	}

} // namespace ITSY_BITSY_SOURCE_NAMESPACE

#endif // ITSY_BITSY_DETAIL_BIT_OPERATIONS_HPP
