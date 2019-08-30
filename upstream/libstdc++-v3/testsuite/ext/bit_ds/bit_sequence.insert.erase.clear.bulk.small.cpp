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

#include <bit_ds_tests_shared_insert_erase_tests.hpp>
#include <bit_ds_tests_require.h>

#include <ext/bit>

#include <vector>
#include <deque>
#include <list>
#include <string>

template<typename TestType>
void
bit_ds_test_bit_sequence_insert_erase_clear_bulk_small()
{
	SECTION("vector")
	{
		__gnu_cxx::bit_sequence<std::vector<TestType>> storage;
		bit_sequence_insert_erase_test_bulk_small<TestType>(storage);
	}
	SECTION("std::basic_string")
	{
		__gnu_cxx::bit_sequence<std::basic_string<TestType>> storage;
		bit_sequence_insert_erase_test_bulk_small<TestType>(storage);
	}
	SECTION("deque")
	{
		__gnu_cxx::bit_sequence<std::deque<TestType>> storage;
		bit_sequence_insert_erase_test_bulk_small<TestType>(storage);
	}
	SECTION("list")
	{
		__gnu_cxx::bit_sequence<std::list<TestType>> storage;
		bit_sequence_insert_erase_test_bulk_small<TestType>(storage);
	}
}

template<typename... TestTypes>
void
bit_ds_test_cases()
{
	bit_ds_test_bit_sequence_insert_erase_clear_bulk_small<TestTypes>()...;
}

int
main()
{
	bit_ds_test_cases<std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, char32_t,
	  char16_t, unsigned char, std::size_t, std::int64_t, std::int32_t, std::int16_t, std::int8_t,
	  char, signed char, std::ptrdiff_t>();
	return 0;
}
