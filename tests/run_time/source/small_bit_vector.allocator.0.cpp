// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#include <itsy/tests/tracking_allocator.hpp>
#include <itsy/tests/constants.hpp>
#include <itsy/tests/shared_allocator_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <cstddef>
#include <cstdint>

TEMPLATE_TEST_CASE("small_bit_vector<T, 0> allocator", "[small_bit_vector<T, 0>][allocator]",
     std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t,
     std::int32_t, std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char,
     std::ptrdiff_t, std::size_t)
{
	using sbv_allocator     = bitsy::tests::tracking_allocator<std::allocator<TestType>>;
	using sbv_allocator_ref = std::reference_wrapper<sbv_allocator>;
	using tracking_sbv      = bitsy::small_bit_vector<TestType, 0, sbv_allocator_ref>;

	SECTION("normal")
	{
		SECTION("empty")
		{
			sbv_allocator empty_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::il_empty();
				tracking_sbv bit_vec(empty_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(empty_bit_vec_allocator);
		}
		SECTION("initializer_list")
		{
			sbv_allocator il_empty_bit_vec_allocator;
			{
				std::initializer_list<bitsy::bit_value> expected{};
				tracking_sbv bit_vec({}, il_empty_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(il_empty_bit_vec_allocator);

			sbv_allocator il_arg_empty_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::il_empty();
				tracking_sbv bit_vec(expected, il_arg_empty_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(il_arg_empty_bit_vec_allocator);

			sbv_allocator il_in_sbo_bit_vec_allocator;
			{
				std::initializer_list<bitsy::bit_value> expected{ true, false, true, false };
				tracking_sbv bit_vec({ true, false, true, false }, il_in_sbo_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(il_in_sbo_bit_vec_allocator);

			sbv_allocator il_arg_in_sbo_bit_vec_allocator;
			{
				std::initializer_list<bitsy::bit_value> expected{ true, false, true, false };
				tracking_sbv bit_vec(expected, il_arg_in_sbo_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(il_arg_in_sbo_bit_vec_allocator);

			sbv_allocator il_arg_on_heap_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::il_large();
				tracking_sbv bit_vec(expected, il_arg_on_heap_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(il_arg_on_heap_bit_vec_allocator);
		}
		SECTION("first, last")
		{
			sbv_allocator fl_empty_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::il_empty();
				tracking_sbv bit_vec(
				     std::begin(expected), std::begin(expected), fl_empty_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_empty_bit_vec_allocator);

			sbv_allocator fl_in_sbo_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::source_small();
				tracking_sbv bit_vec(
				     std::cbegin(expected), std::cend(expected), fl_in_sbo_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_in_sbo_bit_vec_allocator);

			sbv_allocator fl_on_heap_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::source_large();
				tracking_sbv bit_vec(
				     std::cbegin(expected), std::cend(expected), fl_on_heap_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_on_heap_bit_vec_allocator);

			sbv_allocator fl_bidi_on_heap_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::list_large();
				tracking_sbv bit_vec(std::begin(expected), std::end(expected),
				     fl_bidi_on_heap_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_bidi_on_heap_bit_vec_allocator);
		}
		SECTION("count, value")
		{
			sbv_allocator cv_in_sbo_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::source_small_all_1();
				tracking_sbv bit_vec(std::size(expected), true, cv_in_sbo_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(cv_in_sbo_bit_vec_allocator);

			sbv_allocator cv_on_heap_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::source_large_all_1();
				tracking_sbv bit_vec(std::size(expected), true, cv_on_heap_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(cv_on_heap_bit_vec_allocator);

			sbv_allocator cv_bidi_on_heap_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::list_large_all_1();
				tracking_sbv bit_vec(
				     std::size(expected), true, cv_bidi_on_heap_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(cv_bidi_on_heap_bit_vec_allocator);
		}
	}
	SECTION("in_place")
	{
		SECTION("empty")
		{
			sbv_allocator empty_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::inplace_il_empty<TestType>();
				tracking_sbv bit_vec(std::in_place, empty_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(empty_bit_vec_allocator);
		}
		SECTION("first, last")
		{
			sbv_allocator fl_inplace_empty_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::inplace_il_empty<TestType>();
				tracking_sbv bit_vec(std::in_place, std::cbegin(expected), std::cend(expected),
				     fl_inplace_empty_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_inplace_empty_bit_vec_allocator);

			sbv_allocator fl_inplace_in_sbo_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::inplace_il_small_all_1<TestType>();
				tracking_sbv bit_vec(std::in_place, std::begin(expected), std::end(expected),
				     fl_inplace_in_sbo_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_inplace_in_sbo_bit_vec_allocator);

			sbv_allocator fl_inplace_on_heap_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::inplace_il_large<TestType>();
				tracking_sbv bit_vec(std::in_place, std::begin(expected), std::end(expected),
				     fl_inplace_on_heap_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_inplace_on_heap_bit_vec_allocator);

			sbv_allocator fl_inplace_bidi_in_sbo_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::inplace_list_small_all_1<TestType>();
				tracking_sbv bit_vec(std::in_place, std::begin(expected), std::end(expected),
				     fl_inplace_bidi_in_sbo_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_inplace_bidi_in_sbo_bit_vec_allocator);

			sbv_allocator fl_inplace_bidi_on_heap_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::inplace_list_large_all_0<TestType>();
				tracking_sbv bit_vec(std::in_place, std::begin(expected), std::end(expected),
				     fl_inplace_bidi_on_heap_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(fl_inplace_bidi_on_heap_bit_vec_allocator);
		}
		SECTION("count, value")
		{
			sbv_allocator cv_inplace_in_sbo_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::inplace_il_small_all_1<TestType>();
				tracking_sbv bit_vec(std::in_place, std::size(expected), *expected.begin(),
				     cv_inplace_in_sbo_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(cv_inplace_in_sbo_bit_vec_allocator);

			sbv_allocator cv_inplace_on_heap_bit_vec_allocator;
			{
				const auto& expected = bitsy::tests::inplace_list_large_all_0<TestType>();
				tracking_sbv bit_vec(std::in_place, std::size(expected), *expected.begin(),
				     cv_inplace_on_heap_bit_vec_allocator);
				bitsy::tests::allocator_test<TestType, sbv_allocator>(bit_vec, expected);
			}
			bitsy::tests::balanced_allocator_test(cv_inplace_on_heap_bit_vec_allocator);
		}
	}
}
