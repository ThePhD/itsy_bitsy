// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <itsy/tests/span.hpp>
#include <itsy/tests/ranges.hpp>

#include <cstddef>
#include <cstdint>
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

TEMPLATE_TEST_CASE("bit algorithm, mutable, homogenously sized containers", "[algorithm][mutable][homogenous]",
     std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t,
     std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones =
	     static_cast<TestType>(std::numeric_limits<bitsy::detail::any_to_underlying_t<TestType>>::max());
	static constexpr std::size_t container_size      = 500;
	static constexpr std::size_t container_bit_size  = container_size * bitsy::binary_digits_v<TestType>;
	static constexpr std::size_t tiny_container_size = 5;
	SECTION("matching")
	{
		SECTION("copy")
		{
			SECTION("vector")
			{
				std::vector<TestType> backing_store_zeroes(container_size, zeroes);
				std::vector<TestType> backing_store_ones(container_size, ones);
				bitsy::bit_view<bitsy::tests::span<TestType>> zeroes_view(backing_store_zeroes);
				bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				bitsy::bit_copy(ones_view.cbegin(), ones_view.cend(), zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
			SECTION("deque")
			{
				using container = std::deque<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				container backing_store_ones(container_size, ones);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> zeroes_view(backing_store_zeroes);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				bitsy::bit_copy(ones_view.cbegin(), ones_view.cend(), zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
			SECTION("list")
			{
				using container = std::list<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				container backing_store_ones(container_size, ones);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> zeroes_view(backing_store_zeroes);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				bitsy::bit_copy(ones_view.cbegin(), ones_view.cend(), zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
		}
		SECTION("copy_n")
		{
			SECTION("vector")
			{
				std::vector<TestType> backing_store_zeroes(container_size, zeroes);
				std::vector<TestType> backing_store_ones(container_size, ones);
				bitsy::bit_view<bitsy::tests::span<TestType>> zeroes_view(backing_store_zeroes);
				bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);
				bit_copy_X_algorithm_test_zeroes_ones_before_comparisons(zeroes_view, ones_view);

				bitsy::bit_copy_n(ones_view.cbegin(), container_bit_size, zeroes_view.begin());

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
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> zeroes_view(backing_store_zeroes);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				bitsy::bit_copy_n(ones_view.cbegin(), container_bit_size, zeroes_view.begin());

				bit_copy_X_algorithm_test_zeroes_ones_after(zeroes_view, ones_view);
			}
			SECTION("list")
			{
				using container = std::list<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(container_size, zeroes);
				container backing_store_ones(container_size, ones);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> zeroes_view(backing_store_zeroes);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				bitsy::bit_copy_n(ones_view.cbegin(), container_bit_size, zeroes_view.begin());

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
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> zeroes_view(backing_store_zeroes);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				bitsy::bit_copy(ones_view.cbegin(), ones_view.cbegin(), zeroes_view.end());

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);
			}
			SECTION("copy_n")
			{
				using container = std::deque<TestType>;
				using iterator  = typename container::iterator;
				using sentinel  = typename container::iterator;
				container backing_store_zeroes(tiny_container_size, zeroes);
				container backing_store_ones(tiny_container_size, ones);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> zeroes_view(backing_store_zeroes);
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> ones_view(backing_store_ones);

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);

				bitsy::bit_copy_n(ones_view.cbegin(), 0, zeroes_view.end());

				bit_copy_X_algorithm_test_zeroes_ones_before(zeroes_view, ones_view);
			}
		}
		SECTION("fill")
		{
			SECTION("vector")
			{
				std::vector<TestType> backing_store_ones(container_size, ones);
				bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

				bitsy::bit_fill(ones_view.begin(), ones_view.end(), false);
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
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> zeroes_view(backing_store_zeroes);

				bitsy::bit_fill(zeroes_view.begin(), zeroes_view.end(), true);
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
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> ones_view(backing_store_ones);

				bitsy::bit_fill(ones_view.begin(), ones_view.end(), false);
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
				bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

				bitsy::bit_fill_n(ones_view.begin(), ones_view.size(), false);
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
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> zeroes_view(backing_store_zeroes);

				bitsy::bit_fill_n(zeroes_view.begin(), zeroes_view.size(), true);
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
				bitsy::bit_view<bitsy::tests::subrange<iterator, sentinel>> ones_view(backing_store_ones);

				bitsy::bit_fill_n(ones_view.begin(), ones_view.size(), false);
				REQUIRE(ones_view.none());
				REQUIRE_FALSE(ones_view.any());
				REQUIRE_FALSE(ones_view.all());
			}
		}
		SECTION("sort")
		{
			SECTION("vector-ones")
			{
				std::vector<TestType> backing_store_ones(container_size, ones);
				bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

				bitsy::bit_sort(ones_view.begin(), ones_view.end());
				REQUIRE(ones_view.all());
				REQUIRE(ones_view.any());
				REQUIRE_FALSE(ones_view.none());
				REQUIRE(bitsy::bit_is_sorted(ones_view.begin(), ones_view.end()));
			}
			SECTION("vector-zeroes")
			{
				std::vector<TestType> backing_store_ones(container_size, zeroes);
				bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

				bitsy::bit_sort(ones_view.begin(), ones_view.end());
				REQUIRE_FALSE(ones_view.all());
				REQUIRE_FALSE(ones_view.any());
				REQUIRE(ones_view.none());
				REQUIRE(bitsy::bit_is_sorted(ones_view.begin(), ones_view.end()));
			}
			SECTION("vector-zeroes-ones")
			{
				std::vector<TestType> backing_store_ones({zeroes, ones});
				bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

				bitsy::bit_sort(ones_view.begin(), ones_view.end());
				REQUIRE_FALSE(ones_view.all());
				REQUIRE(ones_view.any());
				REQUIRE_FALSE(ones_view.none());
				REQUIRE(bitsy::bit_is_sorted(ones_view.begin(), ones_view.end()));
			}
			
			SECTION("vector-mingled")
			{
				std::vector<TestType> backing_store_ones({ones, zeroes, ones, ones, zeroes});
				bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

				bitsy::bit_sort(ones_view.begin(), ones_view.end());
				REQUIRE_FALSE(ones_view.all());
				REQUIRE(ones_view.any());
				REQUIRE_FALSE(ones_view.none());
				REQUIRE(bitsy::bit_is_sorted(ones_view.begin(), ones_view.end()));
			}
		}
	}
}

TEMPLATE_TEST_CASE("bit algorithm, mutable, heterogenously sized containers", "[algorithm][mutable][heterogenous]",
     std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t,
     std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones =
	     static_cast<TestType>(std::numeric_limits<bitsy::detail::any_to_underlying_t<TestType>>::max());
	static constexpr std::size_t container0_size     = 1000;
	static constexpr std::size_t container1_size     = 250;
	static constexpr std::size_t container1_bit_size = container1_size * bitsy::binary_digits_v<TestType>;

	SECTION("copy")
	{
		std::basic_string<TestType> backing_store_zeroes(container0_size, zeroes);
		std::basic_string<TestType> backing_store_ones(container1_size, ones);
		bitsy::bit_view<bitsy::tests::span<TestType>> zeroes_view(backing_store_zeroes);
		bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

		auto zeroes_view_first = zeroes_view.cbegin();
		++zeroes_view_first;
		bitsy::bit_copy(ones_view.cbegin(), ones_view.cend(), zeroes_view_first);

		auto zeroes_view_it   = zeroes_view.cbegin();
		auto zeroes_view_last = zeroes_view.cend();
		for (std::size_t i = 0; zeroes_view_it != zeroes_view_last; ++zeroes_view_it, ++i)
			{
				bitsy::bit_value val   = *zeroes_view_it;
				bool expected_comp_val = false;
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
		bitsy::bit_view<bitsy::tests::span<TestType>> zeroes_view(backing_store_zeroes);
		bitsy::bit_view<bitsy::tests::span<TestType>> ones_view(backing_store_ones);

		auto zeroes_view_first = zeroes_view.cbegin();
		++zeroes_view_first;
		bitsy::bit_copy_n(ones_view.cbegin(), container1_bit_size, zeroes_view_first);

		auto zeroes_view_it   = zeroes_view.cbegin();
		auto zeroes_view_last = zeroes_view.cend();
		for (std::size_t i = 0; zeroes_view_it != zeroes_view_last; ++zeroes_view_it, ++i)
			{
				bitsy::bit_value val   = *zeroes_view_it;
				bool expected_comp_val = false;
				if (i > 0 && i < (container1_bit_size + 1))
					{
						expected_comp_val = true;
					}
				const bool comp_val = val.value();
				REQUIRE(comp_val == expected_comp_val);
			}
	}
}
