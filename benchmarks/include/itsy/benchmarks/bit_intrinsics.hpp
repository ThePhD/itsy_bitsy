#pragma once

#ifndef ITSY_BITSY_BENCHMARKS_BIT_INTRINSICS_HPP
#define ITSY_BITSY_BENCHMARKS_BIT_INTRINSICS_HPP

#include <cstddef>
#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>
#endif // VC++

namespace itsy_bitsy
{

#if INTPTR_MAX >= INT64_MAX
	inline std::uint64_t
	bit_scan(std::uint64_t value)
	{
#ifdef _MSC_VER
		unsigned long index;
		if (_BitScanForward64(&index, value) == 0)
			{
				return static_cast<std::uint64_t>(64ULL);
			}
		return static_cast<std::uint64_t>(index);
#else
		if (value == 0)
			{
				return static_cast<std::uint64_t>(64ULL);
			}
		return static_cast<std::uint64_t>(__builtin_ctzl(value));
#endif // VC++ vs. Others
	}
#endif // 64-bit errors in MSVC

	inline std::uint32_t
	bit_scan(std::uint32_t value)
	{
#ifdef _MSC_VER
		unsigned long index;
		if (_BitScanForward(&index, value) == 0)
			{
				return static_cast<std::uint32_t>(64ULL);
			}
		return static_cast<std::uint32_t>(index);
#else
		if (value == 0)
			{
				return static_cast<std::uint32_t>(64ULL);
			}
		return static_cast<std::uint32_t>(__builtin_ctz(value));
#endif // VC++ vs. Others
	}

	inline std::uint32_t
	bit_count(std::uint32_t value)
	{
#ifdef _MSC_VER
		return static_cast<std::uint32_t>(__popcnt(value));
#else
		return static_cast<std::uint32_t>(__builtin_popcount(value));
#endif // VC++ vs. Others
	}

#if INTPTR_MAX >= INT64_MAX
	inline std::uint64_t
	bit_count(std::uint64_t value)
	{
#ifdef _MSC_VER
		return static_cast<std::uint64_t>(__popcnt64(value));
#else
		return static_cast<std::uint64_t>(__builtin_popcountll(value));
#endif // VC++ vs. Others
	}
#endif // 32-bit errors in MSVC

} // namespace itsy_bitsy

#endif // ITSY_BITSY_BENCHMARKS_BIT_INTRINSICS_HPP