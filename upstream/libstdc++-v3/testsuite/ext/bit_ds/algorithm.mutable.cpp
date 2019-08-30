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

#include <bit_ds_tests_require.h>

#include <ext/bit>

#include <cstddef>
#include <cstdint>
#include <span>
#include <ranges>
#include <deque>
#include <list>
#include <string>

template<typename Zeroes, typename Ones>
void
bit_copy_X_algorithm_test_zeroes_ones_before(Zeroes& zeroes_view, Ones& ones_view)
{
	REQUIRE(zeroes_view.none());
	REQUIRE_FALSE(zeroes_view.any());
	REQUIRE_FALSE(zeroes_view.all());

	REQUIRE_FALSE(ones_view.none());
	REQUIRE(ones_view.any());
	REQUIRE(ones_view.all());
}

template<typename Zeroes, typename Ones>
void
bit_copy_X_algorithm_test_zeroes_ones_before_comparisons(Zeroes& zeroes_view, Ones& ones_view)
{
	REQUIRE(ones_view != zeroes_view);
	REQUIRE(ones_view > zeroes_view);
	REQUIRE_FALSE(ones_view < zeroes_view);
	REQUIRE_FALSE(ones_view == zeroes_view);
	REQUIRE(ones_view >= zeroes_view);
	REQUIRE_FALSE(ones_view <= zeroes_view);
}

template<typename Zeroes, typename Ones>
void
bit_copy_X_algorithm_test_zeroes_ones_after(Zeroes& zeroes_view, Ones& ones_view)
{
	REQUIRE_FALSE(zeroes_view.none());
	REQUIRE(zeroes_view.any());
	REQUIRE(zeroes_view.all());

	REQUIRE_FALSE(ones_view.none());
	REQUIRE(ones_view.any());
	REQUIRE(ones_view.all());
}

template<typename Zeroes, typename Ones>
void
bit_copy_X_algorithm_test_zeroes_ones_after_comparisons(Zeroes& zeroes_view, Ones& ones_view)
{
	REQUIRE(ones_view == zeroes_view);
	REQUIRE_FALSE(ones_view > zeroes_view);
	REQUIRE_FALSE(ones_view < zeroes_view);
	REQUIRE_FALSE(ones_view != zeroes_view);
	REQUIRE(ones_view >= zeroes_view);
	REQUIRE(ones_view <= zeroes_view);
}

template<typename TestType>
void
bit_ds_test_case_algorithm_mutable_homongenous()
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones   = static_cast<TestType>(
    std::numeric_limits<__gnu_cxx::xx::detail::any_to_underlying_t<TestType>>::max());
	static constexpr std::size_t container_size = 500;
	static constexpr std::size_t container_bit_size =
	  container_size * __gnu_cxx::xx::binary_digits_v<TestType>;
	static constexpr std::size_t tiny_container_size = 5;
	SECTION("matching")
	{
		SECTION("copy")
		{
			SECTION("vector")
			{
				std::vector<TestType> backing_store_zeroes(container_size, zeroes);
				std::vector<TestType> backing_store_ones(container_size, ones);
				__gnu_cxx::xx::bit_span<TestType> zeroes_view(backing_store_zeroes);
				__gnu_cxx::xx::bit_span<TestType> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				__gnu_cxx::xx::bit_copy(ones_view.cbegin(), ones_view.cend(), zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
			SECTION("deque")
			{
				using container = std::deque<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				container backing_store_ones(container_size, ones);
				__gnu_cxx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> zeroes_view(
				  backing_store_zeroes);
				__gnu_cxx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> ones_view( iew(
				  backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				__gnu_cxx::xx::xx::bit_copy(ones_view.cbegin(), ones_view.cend(), zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
			SECTION("list")
			{
				using container = std::list<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				container backing_store_ones(container_size, ones);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> zeroes_view(
				  backing_store_zeroes);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> ones_v iew(
				  backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				__gnu_cxx::xx::xx::bit_copy(ones_view.cbegin(), ones_view.cend(), zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
		}
		SECTION("copy_n")
		{
			SECTION("vector")
			{
				std::vector<TestType> backing_store_zeroes(container_size, zeroes);
				std::vector<TestType> backing_store_ones(container_size, ones);
				__gnu_cxx::xx::xx::bit_span<TestType> zeroes_view(backing_store_zeroes);
				__gnu_cxx::xx::xx::bit_span<TestType> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);
				bit_copy_X_algorithm_test_zeroes_ones_before_comparisons(zeroes_view, ones_view);

				__gnu_cxx::xx::xx::bit_copy_n(ones_view.cbegin(), container_bit_size, zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
				bit_copy_X_algorithm_test_zeroes_ones_after_comparisons(zeroes_view, ones_view);
			}
			SECTION("deque")
			{
				using container = std::deque<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				container backing_store_ones(container_size, ones);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> zeroes_view(
				  backing_store_zeroes);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> ones_v iew(
				  backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				__gnu_cxx::xx::xx::bit_copy_n(ones_view.cbegin(), container_bit_size, zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
			SECTION("list")
			{
				using container = std::list<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				container backing_store_ones(container_size, ones);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> zeroes_view(
				  backing_store_zeroes);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> ones_v iew(
				  backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				__gnu_cxx::xx::xx::bit_copy_n(ones_view.cbegin(), container_bit_size, zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
		}
		SECTION("do nothing")
		{
			SECTION("copy")
			{
				using container = std::list<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(tiny_container_size, zeroes);
				container backing_store_ones(tiny_container_size, ones);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> zeroes_view(
				  backing_store_zeroes);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> ones_v iew(
				  backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				__gnu_cxx::xx::xx::bit_copy(ones_view.cbegin(), ones_view.cbegin(), zeroes_view.end());

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);
			}
			SECTION("copy_n")
			{
				using container = std::deque<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(tiny_container_size, zeroes);
				container backing_store_ones(tiny_container_size, ones);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> zeroes_view(
				  backing_store_zeroes);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> ones_v iew(
				  backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				__gnu_cxx::xx::xx::bit_copy_n(ones_view.cbegin(), 0, zeroes_view.end());

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);
			}
		}
		SECTION("fill")
		{
			SECTION("vector")
			{
				std::vector<TestType> backing_store_ones(container_size, ones);
				__gnu_cxx::xx::xx::bit_span<TestType> ones_view(backing_store_ones);

				__gnu_cxx::xx::xx::bit_fill(ones_view.begin(), ones_view.end(), false);
				REQUIRE(ones_view.none());
				REQUIRE_FALSE(ones_view.any());
				REQUIRE_FALSE(ones_view.all());
			}
			SECTION("deque")
			{
				using container = std::deque<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> zeroes_view(
				  backing_store_zeroes);

				__gnu_cxx::xx::xx::bit_fill(zeroes_view.begin(), zeroes_view.end(), true);
				REQUIRE_FALSE(zeroes_view.none());
				REQUIRE(zeroes_view.any());
				REQUIRE(zeroes_view.all());
			}
			SECTION("list")
			{
				using container = std::list<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_ones(container_size, ones);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> ones_v iew(
				  backing_store_ones);

				__gnu_cxx::xx::xx::bit_fill(ones_view.begin(), ones_view.end(), false);
				REQUIRE(ones_view.none());
				REQUIRE_FALSE(ones_view.any());
				REQUIRE_FALSE(ones_view.all());
			}
		}
		SECTION("fill_n")
		{
			SECTION("vector")
			{
				std::vector<TestType> backing_store_ones(container_size, ones);
				__gnu_cxx::xx::xx::bit_span<TestType> ones_view(backing_store_ones);

				__gnu_cxx::xx::xx::bit_fill_n(ones_view.begin(), ones_view.size(), false);
				REQUIRE(ones_view.none());
				REQUIRE_FALSE(ones_view.any());
				REQUIRE_FALSE(ones_view.all());
			}
			SECTION("deque")
			{
				using container = std::deque<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> zeroes_view(
				  backing_store_zeroes);

				__gnu_cxx::xx::xx::bit_fill_n(zeroes_view.begin(), zeroes_view.size(), true);
				REQUIRE_FALSE(zeroes_view.none());
				REQUIRE(zeroes_view.any());
				REQUIRE(zeroes_view.all());
			}
			SECTION("list")
			{
				using container = std::list<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_ones(container_size, ones);
				__gnu_cxx::xx::xx::bit_view<std::ranges::subrange<iterator, sentinel>> ones_v iew(
				  backing_store_ones);

				__gnu_cxx::xx::xx::bit_fill_n(ones_view.begin(), ones_view.size(), false);
				REQUIRE(ones_view.none());
				REQUIRE_FALSE(ones_view.any());
				REQUIRE_FALSE(ones_view.all());
			}
		}
	}
}

template<typename TestType>
bit_ds_test_case_algorithm_mutable_heterogenous()
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones   = static_cast<TestType>(
    std::numeric_limits<__gnu_cxx::xx::xx::detail::any_to_underlying_t<TestType>>::max());
	static constexpr std::size_t container0_size = 1000;
	static constexpr std::size_t container1_size = 250;
	static constexpr std::size_t container1_bit_size =
	  container1_size * __gnu_cxx::xx::xx::binary_digits_v<TestType>;

	SECTION("copy")
	{
		std::basic_string<TestType> backing_store_zeroes(container0_size, zeroes);
		std::basic_string<TestType> backing_store_ones(container1_size, ones);
		__gnu_cxx::xx::xx::bit_span<TestType> zeroes_view(backing_store_zeroes);
		__gnu_cxx::xx::xx::bit_span<TestType> ones_view(backing_store_ones);

		auto zeroes_view_first = zeroes_view.cbegin();
		++zeroes_view_first;
		__gnu_cxx::xx::xx::bit_copy(ones_view.cbegin(), ones_view.cend(), zeroes_view_first);

		auto zeroes_view_it   = zeroes_view.cbegin();
		auto zeroes_view_last = zeroes_view.cend();
		for (std::size_t i = 0; zeroes_view_it != zeroes_view_last; ++zeroes_view_it, ++i)
			{
				__gnu_cxx::xx::xx::bit_valueal = *zeroes_view_it;
				bool expected_comp_val         = false;
				if (i > 0 && i < (container1_bit_size + 1))
					{
						expected_comp_val = true;
					}
				const bool comp_val = val.value();
				REQUIRE(comp_val == expected_comp_val);
			}
	}
	SECTION("copy_n")
	{
		std::basic_string<TestType> backing_store_zeroes(container0_size, zeroes);
		std::basic_string<TestType> backing_store_ones(container1_size, ones);
		__gnu_cxx::xx::xx::bit_span<TestType> zeroes_view(backing_store_zeroes);
		__gnu_cxx::xx::xx::bit_span<TestType> ones_view(backing_store_ones);

		auto zeroes_view_first = zeroes_view.cbegin();
		++zeroes_view_first;
		__gnu_cxx::xx::xx::bit_copy_n(ones_view.cbegin(), container1_bit_size, zeroes_view_first);

		auto zeroes_view_it   = zeroes_view.cbegin();
		auto zeroes_view_last = zeroes_view.cend();
		for (std::size_t i = 0; zeroes_view_it != zeroes_view_last; ++zeroes_view_it, ++i)
			{
				__gnu_cxx::xx::xx::bit_valueal = *zeroes_view_it;
				bool expected_comp_val         = false;
				if (i > 0 && i < (container1_bit_size + 1))
					{
						expected_comp_val = true;
					}
				const bool comp_val = val.value();
				REQUIRE(comp_val == expected_comp_val);
			}
	}
}

template<typename... TestTypes>
void
bit_ds_test_cases()
{
	bit_ds_test_case_algorithm_mutable_homongenous<TestTypes>()...;
	bit_ds_test_case_algorithm_mutable_heterogenous<TestTypes>()...;
}

int
main()
{
	bit_ds_test_cases<std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte,
	  std::int64_t, std::int32_t, std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char,
	  signed char, std::size_t, std::ptrdiff_t>();
	return 0;
}
