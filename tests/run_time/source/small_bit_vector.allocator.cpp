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

#include <catch2/catch.hpp>

#include <itsy/bitsy.hpp>

#include <cstddef>
#include <cstdint>

TEMPLATE_TEST_CASE("small_bit_vector allocator", "[small_bit_vector<T>][allocator]", std::uint64_t,
     std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
     std::int16_t, std::int8_t, char32_t, char16_t, char, unsigned char, signed char,
     std::ptrdiff_t, std::size_t)
{
	using sbv_allocator     = bitsy::tests::tracking_allocator<std::allocator<TestType>>;
	using sbv_allocator_ref = std::reference_wrapper<sbv_allocator>;
	using tracking_sbv      = bitsy::small_bit_vector<TestType, 2, sbv_allocator_ref>;

	sbv_allocator empty_bit_vec_allocator;
	{
		tracking_sbv empty_bit_vec(empty_bit_vec_allocator);
		sbv_allocator& empty_bit_vec_alloc = empty_bit_vec.get_allocator();
		auto empty_bit_vec_size            = empty_bit_vec.size();
		REQUIRE(empty_bit_vec_size == 0);
		auto empty_bit_vec_empty = empty_bit_vec.empty();
		REQUIRE(empty_bit_vec_empty);
		auto empty_bit_vec_is_inline = empty_bit_vec.is_inline();
		REQUIRE(empty_bit_vec_is_inline);
		auto empty_bit_vec_alloc_alive = empty_bit_vec_alloc.alive();
		REQUIRE(empty_bit_vec_alloc_alive == 0);
		auto empty_bit_vec_alloc_allocations_alive = empty_bit_vec_alloc.allocations_alive();
		REQUIRE(empty_bit_vec_alloc_allocations_alive == 0);
		auto empty_bit_vec_alloc_constructions = empty_bit_vec_alloc.constructions();
		REQUIRE(empty_bit_vec_alloc_constructions == 0);
		auto empty_bit_vec_alloc_destructions = empty_bit_vec_alloc.destructions();
		REQUIRE(empty_bit_vec_alloc_destructions == 0);
		auto empty_bit_vec_alloc_allocations = empty_bit_vec_alloc.allocations();
		REQUIRE(empty_bit_vec_alloc_allocations == 0);
		auto empty_bit_vec_alloc_deallocations = empty_bit_vec_alloc.deallocations();
		REQUIRE(empty_bit_vec_alloc_deallocations == 0);
	}
	REQUIRE(empty_bit_vec_allocator.alive() == 0);
	REQUIRE(empty_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(empty_bit_vec_allocator.allocations() == empty_bit_vec_allocator.deallocations());
	REQUIRE(empty_bit_vec_allocator.destructions() == empty_bit_vec_allocator.constructions());

	sbv_allocator il_empty_bit_vec_allocator;
	{
		std::initializer_list<bitsy::bit_value> il_empty{};
		tracking_sbv il_empty_bit_vec(il_empty, il_empty_bit_vec_allocator);
		sbv_allocator& il_empty_bit_vec_alloc = il_empty_bit_vec.get_allocator();
		auto il_empty_bit_vec_size            = il_empty_bit_vec.size();
		REQUIRE(il_empty_bit_vec_size == 0);
		auto il_empty_bit_vec_empty = il_empty_bit_vec.empty();
		REQUIRE(il_empty_bit_vec_empty);
		auto il_empty_bit_vec_is_inline = il_empty_bit_vec.is_inline();
		REQUIRE(il_empty_bit_vec_is_inline);
		auto il_empty_bit_vec_alloc_alive = il_empty_bit_vec_alloc.alive();
		REQUIRE(il_empty_bit_vec_alloc_alive == 0);
		auto il_empty_bit_vec_alloc_allocations_alive =
		     il_empty_bit_vec_alloc.allocations_alive();
		REQUIRE(il_empty_bit_vec_alloc_allocations_alive == 0);
		auto il_empty_bit_vec_alloc_constructions = il_empty_bit_vec_alloc.constructions();
		REQUIRE(il_empty_bit_vec_alloc_constructions == 0);
		auto il_empty_bit_vec_alloc_destructions = il_empty_bit_vec_alloc.destructions();
		REQUIRE(il_empty_bit_vec_alloc_destructions == 0);
		auto il_empty_bit_vec_alloc_allocations = il_empty_bit_vec_alloc.allocations();
		REQUIRE(il_empty_bit_vec_alloc_allocations == 0);
		auto il_empty_bit_vec_alloc_deallocations = il_empty_bit_vec_alloc.deallocations();
		REQUIRE(il_empty_bit_vec_alloc_deallocations == 0);
		REQUIRE(std::equal(
		     il_empty_bit_vec.begin(), il_empty_bit_vec.end(), il_empty.begin(), il_empty.end()));
	}
	REQUIRE(il_empty_bit_vec_allocator.alive() == 0);
	REQUIRE(il_empty_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(
	     il_empty_bit_vec_allocator.allocations() == il_empty_bit_vec_allocator.deallocations());
	REQUIRE(
	     il_empty_bit_vec_allocator.destructions() == il_empty_bit_vec_allocator.constructions());

	sbv_allocator il_in_sbo_bit_vec_allocator;
	{
		std::initializer_list<bitsy::bit_value> il_in_sbo_bit_vec_expected{ true, false, true,
			false };
		tracking_sbv il_in_sbo_bit_vec({ true, false, true, false }, il_in_sbo_bit_vec_allocator);
		sbv_allocator& il_in_sbo_bit_vec_alloc = il_in_sbo_bit_vec.get_allocator();
		auto il_in_sbo_bit_vec_size            = il_in_sbo_bit_vec.size();
		REQUIRE(il_in_sbo_bit_vec_size == 4);
		auto il_in_sbo_bit_vec_empty = il_in_sbo_bit_vec.empty();
		REQUIRE_FALSE(il_in_sbo_bit_vec_empty);
		auto il_in_sbo_bit_vec_is_inline = il_in_sbo_bit_vec.is_inline();
		REQUIRE(il_in_sbo_bit_vec_is_inline);
		auto il_in_sbo_bit_vec_alloc_alive = il_in_sbo_bit_vec_alloc.alive();
		REQUIRE(il_in_sbo_bit_vec_alloc_alive == 1);
		auto il_in_sbo_bit_vec_alloc_allocations_alive =
		     il_in_sbo_bit_vec_alloc.allocations_alive();
		REQUIRE(il_in_sbo_bit_vec_alloc_allocations_alive == 0);
		auto il_in_sbo_bit_vec_alloc_constructions = il_in_sbo_bit_vec_alloc.constructions();
		REQUIRE(il_in_sbo_bit_vec_alloc_constructions == 1);
		auto il_in_sbo_bit_vec_alloc_destructions = il_in_sbo_bit_vec_alloc.destructions();
		REQUIRE(il_in_sbo_bit_vec_alloc_destructions == 0);
		auto il_in_sbo_bit_vec_alloc_allocations = il_in_sbo_bit_vec_alloc.allocations();
		REQUIRE(il_in_sbo_bit_vec_alloc_allocations == 0);
		auto il_in_sbo_bit_vec_alloc_deallocations = il_in_sbo_bit_vec_alloc.deallocations();
		REQUIRE(il_in_sbo_bit_vec_alloc_deallocations == 0);
		REQUIRE(std::equal(il_in_sbo_bit_vec.begin(), il_in_sbo_bit_vec.end(),
		     il_in_sbo_bit_vec_expected.begin(), il_in_sbo_bit_vec_expected.end()));
	}
	REQUIRE(il_in_sbo_bit_vec_allocator.alive() == 0);
	REQUIRE(il_in_sbo_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(
	     il_in_sbo_bit_vec_allocator.allocations() == il_in_sbo_bit_vec_allocator.deallocations());
	REQUIRE(il_in_sbo_bit_vec_allocator.destructions() ==
	        il_in_sbo_bit_vec_allocator.constructions());

	sbv_allocator fl_empty_bit_vec_allocator;
	{
		tracking_sbv fl_empty_bit_vec(std::begin(bitsy::tests::source_small()),
		     std::begin(bitsy::tests::source_small()), fl_empty_bit_vec_allocator);
		sbv_allocator& fl_empty_bit_vec_alloc = fl_empty_bit_vec.get_allocator();
		auto fl_empty_bit_vec_size            = fl_empty_bit_vec.size();
		REQUIRE(fl_empty_bit_vec_size == 0);
		auto fl_empty_bit_vec_empty = fl_empty_bit_vec.empty();
		REQUIRE(fl_empty_bit_vec_empty);
		auto fl_empty_bit_vec_is_inline = fl_empty_bit_vec.is_inline();
		REQUIRE(fl_empty_bit_vec_is_inline);
		auto fl_empty_bit_vec_alloc_alive = fl_empty_bit_vec_alloc.alive();
		REQUIRE(fl_empty_bit_vec_alloc_alive == 0);
		auto fl_empty_bit_vec_alloc_allocations_alive =
		     fl_empty_bit_vec_alloc.allocations_alive();
		REQUIRE(fl_empty_bit_vec_alloc_allocations_alive == 0);
		auto fl_empty_bit_vec_alloc_constructions = fl_empty_bit_vec_alloc.constructions();
		REQUIRE(fl_empty_bit_vec_alloc_constructions == 0);
		auto fl_empty_bit_vec_alloc_destructions = fl_empty_bit_vec_alloc.destructions();
		REQUIRE(fl_empty_bit_vec_alloc_destructions == 0);
		auto fl_empty_bit_vec_alloc_allocations = fl_empty_bit_vec_alloc.allocations();
		REQUIRE(fl_empty_bit_vec_alloc_allocations == 0);
		auto fl_empty_bit_vec_alloc_deallocations = fl_empty_bit_vec_alloc.deallocations();
		REQUIRE(fl_empty_bit_vec_alloc_deallocations == 0);
		REQUIRE(std::equal(std::begin(bitsy::tests::source_small()),
		     std::begin(bitsy::tests::source_small()), fl_empty_bit_vec.begin(),
		     fl_empty_bit_vec.end()));
	}
	REQUIRE(fl_empty_bit_vec_allocator.alive() == 0);
	REQUIRE(fl_empty_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(
	     fl_empty_bit_vec_allocator.allocations() == fl_empty_bit_vec_allocator.deallocations());
	REQUIRE(
	     fl_empty_bit_vec_allocator.destructions() == fl_empty_bit_vec_allocator.constructions());

	sbv_allocator fl_inplace_empty_bit_vec_allocator;
	{
		std::initializer_list<TestType> il_inplace_source{};
		tracking_sbv fl_inplace_empty_bit_vec(std::in_place, std::begin(il_inplace_source),
		     std::end(il_inplace_source), fl_inplace_empty_bit_vec_allocator);
		sbv_allocator& fl_inplace_empty_bit_vec_alloc = fl_inplace_empty_bit_vec.get_allocator();
		auto fl_inplace_empty_bit_vec_size            = fl_inplace_empty_bit_vec.size();
		REQUIRE(fl_inplace_empty_bit_vec_size == 0);
		auto fl_inplace_empty_bit_vec_empty = fl_inplace_empty_bit_vec.empty();
		REQUIRE(fl_inplace_empty_bit_vec_empty);
		auto fl_inplace_empty_bit_vec_is_inline = fl_inplace_empty_bit_vec.is_inline();
		REQUIRE(fl_inplace_empty_bit_vec_is_inline);
		auto fl_inplace_empty_bit_vec_alloc_alive = fl_inplace_empty_bit_vec_alloc.alive();
		REQUIRE(fl_inplace_empty_bit_vec_alloc_alive == 0);
		auto fl_inplace_empty_bit_vec_alloc_allocations_alive =
		     fl_inplace_empty_bit_vec_alloc.allocations_alive();
		REQUIRE(fl_inplace_empty_bit_vec_alloc_allocations_alive == 0);
		auto fl_inplace_empty_bit_vec_alloc_constructions =
		     fl_inplace_empty_bit_vec_alloc.constructions();
		REQUIRE(fl_inplace_empty_bit_vec_alloc_constructions == 0);
		auto fl_inplace_empty_bit_vec_alloc_destructions =
		     fl_inplace_empty_bit_vec_alloc.destructions();
		REQUIRE(fl_inplace_empty_bit_vec_alloc_destructions == 0);
		auto fl_inplace_empty_bit_vec_alloc_allocations =
		     fl_inplace_empty_bit_vec_alloc.allocations();
		REQUIRE(fl_inplace_empty_bit_vec_alloc_allocations == 0);
		auto fl_inplace_empty_bit_vec_alloc_deallocations =
		     fl_inplace_empty_bit_vec_alloc.deallocations();
		REQUIRE(fl_inplace_empty_bit_vec_alloc_deallocations == 0);
		REQUIRE(std::equal(bitsy::bit_iterator<const TestType*>(il_inplace_source.begin()),
		     bitsy::bit_iterator<const TestType*>(il_inplace_source.end()),
		     fl_inplace_empty_bit_vec.begin(), fl_inplace_empty_bit_vec.end()));
	}
	REQUIRE(fl_inplace_empty_bit_vec_allocator.alive() == 0);
	REQUIRE(fl_inplace_empty_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(fl_inplace_empty_bit_vec_allocator.allocations() ==
	        fl_inplace_empty_bit_vec_allocator.deallocations());
	REQUIRE(fl_inplace_empty_bit_vec_allocator.destructions() ==
	        fl_inplace_empty_bit_vec_allocator.constructions());

	sbv_allocator fl_in_sbo_bit_vec_allocator;
	{
		tracking_sbv fl_in_sbo_bit_vec(std::cbegin(bitsy::tests::source_small()),
		     std::cend(bitsy::tests::source_small()), fl_in_sbo_bit_vec_allocator);
		sbv_allocator& fl_in_sbo_bit_vec_alloc = fl_in_sbo_bit_vec.get_allocator();
		auto fl_in_sbo_bit_vec_size            = fl_in_sbo_bit_vec.size();
		REQUIRE(fl_in_sbo_bit_vec_size == std::size(bitsy::tests::source_small()));
		auto fl_in_sbo_bit_vec_empty = fl_in_sbo_bit_vec.empty();
		REQUIRE_FALSE(fl_in_sbo_bit_vec_empty);
		auto fl_in_sbo_bit_vec_is_inline = fl_in_sbo_bit_vec.is_inline();
		REQUIRE(fl_in_sbo_bit_vec_is_inline);
		auto fl_in_sbo_bit_vec_alloc_alive = fl_in_sbo_bit_vec_alloc.alive();
		REQUIRE(fl_in_sbo_bit_vec_alloc_alive == 1);
		auto fl_in_sbo_bit_vec_alloc_allocations_alive =
		     fl_in_sbo_bit_vec_alloc.allocations_alive();
		REQUIRE(fl_in_sbo_bit_vec_alloc_allocations_alive == 0);
		auto fl_in_sbo_bit_vec_alloc_constructions = fl_in_sbo_bit_vec_alloc.constructions();
		REQUIRE(fl_in_sbo_bit_vec_alloc_constructions == 1);
		auto fl_in_sbo_bit_vec_alloc_destructions = fl_in_sbo_bit_vec_alloc.destructions();
		REQUIRE(fl_in_sbo_bit_vec_alloc_destructions == 0);
		auto fl_in_sbo_bit_vec_alloc_allocations = fl_in_sbo_bit_vec_alloc.allocations();
		REQUIRE(fl_in_sbo_bit_vec_alloc_allocations == 0);
		auto fl_in_sbo_bit_vec_alloc_deallocations = fl_in_sbo_bit_vec_alloc.deallocations();
		REQUIRE(fl_in_sbo_bit_vec_alloc_deallocations == 0);
		REQUIRE(std::equal(std::cbegin(bitsy::tests::source_small()),
		     std::cend(bitsy::tests::source_small()), fl_in_sbo_bit_vec.begin(),
		     fl_in_sbo_bit_vec.end()));
	}
	REQUIRE(fl_in_sbo_bit_vec_allocator.alive() == 0);
	REQUIRE(fl_in_sbo_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(
	     fl_in_sbo_bit_vec_allocator.allocations() == fl_in_sbo_bit_vec_allocator.deallocations());
	REQUIRE(fl_in_sbo_bit_vec_allocator.destructions() ==
	        fl_in_sbo_bit_vec_allocator.constructions());

	sbv_allocator fl_inplace_in_sbo_bit_vec_allocator;
	{
		std::initializer_list<TestType> il_inplace_source{ static_cast<TestType>(12) };
		std::ptrdiff_t il_inplace_source_size =
		     static_cast<std::ptrdiff_t>(il_inplace_source.size());
		tracking_sbv fl_inplace_in_sbo_bit_vec(std::in_place, std::begin(il_inplace_source),
		     std::end(il_inplace_source), fl_inplace_in_sbo_bit_vec_allocator);
		sbv_allocator& fl_inplace_in_sbo_bit_vec_alloc =
		     fl_inplace_in_sbo_bit_vec.get_allocator();
		std::ptrdiff_t fl_inplace_in_sbo_bit_vec_size =
		     static_cast<std::ptrdiff_t>(fl_inplace_in_sbo_bit_vec.size());
		REQUIRE(fl_inplace_in_sbo_bit_vec_size ==
		        bitsy::element_to_bit_size<TestType>(il_inplace_source_size));
		auto fl_inplace_in_sbo_bit_vec_empty = fl_inplace_in_sbo_bit_vec.empty();
		REQUIRE_FALSE(fl_inplace_in_sbo_bit_vec_empty);
		auto fl_inplace_in_sbo_bit_vec_is_inline = fl_inplace_in_sbo_bit_vec.is_inline();
		REQUIRE(fl_inplace_in_sbo_bit_vec_is_inline);
		auto fl_inplace_in_sbo_bit_vec_alloc_alive = fl_inplace_in_sbo_bit_vec_alloc.alive();
		REQUIRE(fl_inplace_in_sbo_bit_vec_alloc_alive == 1);
		auto fl_inplace_in_sbo_bit_vec_alloc_allocations_alive =
		     fl_inplace_in_sbo_bit_vec_alloc.allocations_alive();
		REQUIRE(fl_inplace_in_sbo_bit_vec_alloc_allocations_alive == 0);
		auto fl_inplace_in_sbo_bit_vec_alloc_constructions =
		     fl_inplace_in_sbo_bit_vec_alloc.constructions();
		REQUIRE(fl_inplace_in_sbo_bit_vec_alloc_constructions == il_inplace_source_size);
		auto fl_inplace_in_sbo_bit_vec_alloc_destructions =
		     fl_inplace_in_sbo_bit_vec_alloc.destructions();
		REQUIRE(fl_inplace_in_sbo_bit_vec_alloc_destructions == 0);
		auto fl_inplace_in_sbo_bit_vec_alloc_allocations =
		     fl_inplace_in_sbo_bit_vec_alloc.allocations();
		REQUIRE(fl_inplace_in_sbo_bit_vec_alloc_allocations == 0);
		auto fl_inplace_in_sbo_bit_vec_alloc_deallocations =
		     fl_inplace_in_sbo_bit_vec_alloc.deallocations();
		REQUIRE(fl_inplace_in_sbo_bit_vec_alloc_deallocations == 0);
		REQUIRE(std::equal(bitsy::bit_iterator<const TestType*>(il_inplace_source.begin()),
		     bitsy::bit_iterator<const TestType*>(il_inplace_source.end()),
		     fl_inplace_in_sbo_bit_vec.begin(), fl_inplace_in_sbo_bit_vec.end()));
	}
	REQUIRE(fl_inplace_in_sbo_bit_vec_allocator.alive() == 0);
	REQUIRE(fl_inplace_in_sbo_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(fl_inplace_in_sbo_bit_vec_allocator.allocations() ==
	        fl_inplace_in_sbo_bit_vec_allocator.deallocations());
	REQUIRE(fl_inplace_in_sbo_bit_vec_allocator.destructions() ==
	        fl_inplace_in_sbo_bit_vec_allocator.constructions());

	sbv_allocator cv_in_sbo_bit_vec_allocator;
	{
		tracking_sbv cv_in_sbo_bit_vec(
		     std::size(bitsy::tests::source_small_all_1()), true, cv_in_sbo_bit_vec_allocator);
		sbv_allocator& cv_in_sbo_bit_vec_alloc = cv_in_sbo_bit_vec.get_allocator();
		auto cv_in_sbo_bit_vec_size            = cv_in_sbo_bit_vec.size();
		REQUIRE(cv_in_sbo_bit_vec_size == std::size(bitsy::tests::source_small()));
		auto cv_in_sbo_bit_vec_empty = cv_in_sbo_bit_vec.empty();
		REQUIRE_FALSE(cv_in_sbo_bit_vec_empty);
		auto cv_in_sbo_bit_vec_is_inline = cv_in_sbo_bit_vec.is_inline();
		REQUIRE(cv_in_sbo_bit_vec_is_inline);
		auto cv_in_sbo_bit_vec_alloc_alive = cv_in_sbo_bit_vec_alloc.alive();
		REQUIRE(cv_in_sbo_bit_vec_alloc_alive == 1);
		auto cv_in_sbo_bit_vec_alloc_allocations_alive =
		     cv_in_sbo_bit_vec_alloc.allocations_alive();
		REQUIRE(cv_in_sbo_bit_vec_alloc_allocations_alive == 0);
		auto cv_in_sbo_bit_vec_alloc_constructions = cv_in_sbo_bit_vec_alloc.constructions();
		REQUIRE(cv_in_sbo_bit_vec_alloc_constructions == 1);
		auto cv_in_sbo_bit_vec_alloc_destructions = cv_in_sbo_bit_vec_alloc.destructions();
		REQUIRE(cv_in_sbo_bit_vec_alloc_destructions == 0);
		auto cv_in_sbo_bit_vec_alloc_allocations = cv_in_sbo_bit_vec_alloc.allocations();
		REQUIRE(cv_in_sbo_bit_vec_alloc_allocations == 0);
		auto cv_in_sbo_bit_vec_alloc_deallocations = cv_in_sbo_bit_vec_alloc.deallocations();
		REQUIRE(cv_in_sbo_bit_vec_alloc_deallocations == 0);
		REQUIRE(std::equal(std::cbegin(bitsy::tests::source_small_all_1()),
		     std::cend(bitsy::tests::source_small_all_1()), cv_in_sbo_bit_vec.begin(),
		     cv_in_sbo_bit_vec.end()));
	}
	REQUIRE(cv_in_sbo_bit_vec_allocator.alive() == 0);
	REQUIRE(cv_in_sbo_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(
	     cv_in_sbo_bit_vec_allocator.allocations() == cv_in_sbo_bit_vec_allocator.deallocations());
	REQUIRE(cv_in_sbo_bit_vec_allocator.destructions() ==
	        cv_in_sbo_bit_vec_allocator.constructions());

	sbv_allocator il_on_heap_bit_vec_allocator;
	{
		const std::ptrdiff_t il_large_size                   = bitsy::tests::il_large().size();
		const std::ptrdiff_t il_large_expected_allocations   = 1;
		const std::ptrdiff_t il_large_expected_deallocations = 0;
		const std::ptrdiff_t il_large_expected_constructions =
		     bitsy::bit_to_element_size<TestType>(il_large_size);
		const std::ptrdiff_t il_large_expected_destructions = 0;
		const std::ptrdiff_t il_large_expected_alive =
		     il_large_expected_constructions - il_large_expected_destructions;
		const std::ptrdiff_t il_large_expected_allocations_alive =
		     il_large_expected_allocations - il_large_expected_deallocations;
		tracking_sbv il_on_heap_bit_vec(bitsy::tests::il_large(), il_on_heap_bit_vec_allocator);
		sbv_allocator& il_on_heap_bit_vec_alloc = il_on_heap_bit_vec.get_allocator();
		auto il_on_heap_bit_vec_size = static_cast<std::ptrdiff_t>(il_on_heap_bit_vec.size());
		REQUIRE(il_on_heap_bit_vec_size == il_large_size);
		auto il_on_heap_bit_vec_empty = il_on_heap_bit_vec.empty();
		REQUIRE_FALSE(il_on_heap_bit_vec_empty);
		auto il_on_heap_bit_vec_is_inline = il_on_heap_bit_vec.is_inline();
		REQUIRE_FALSE(il_on_heap_bit_vec_is_inline);
		auto il_on_heap_bit_vec_alloc_alive = il_on_heap_bit_vec_alloc.alive();
		REQUIRE(il_on_heap_bit_vec_alloc_alive == il_large_expected_alive);
		auto il_on_heap_bit_vec_alloc_allocations_alive =
		     il_on_heap_bit_vec_alloc.allocations_alive();
		REQUIRE(
		     il_on_heap_bit_vec_alloc_allocations_alive == il_large_expected_allocations_alive);
		auto il_on_heap_bit_vec_alloc_constructions = il_on_heap_bit_vec_alloc.constructions();
		REQUIRE(il_on_heap_bit_vec_alloc_constructions == il_large_expected_constructions);
		auto il_on_heap_bit_vec_alloc_destructions = il_on_heap_bit_vec_alloc.destructions();
		REQUIRE(il_on_heap_bit_vec_alloc_destructions == il_large_expected_destructions);
		auto il_on_heap_bit_vec_alloc_allocations = il_on_heap_bit_vec_alloc.allocations();
		REQUIRE(il_on_heap_bit_vec_alloc_allocations == il_large_expected_allocations);
		auto il_on_heap_bit_vec_alloc_deallocations = il_on_heap_bit_vec_alloc.deallocations();
		REQUIRE(il_on_heap_bit_vec_alloc_deallocations == il_large_expected_deallocations);
		REQUIRE(std::equal(std::cbegin(bitsy::tests::il_large()),
		     std::cend(bitsy::tests::il_large()), il_on_heap_bit_vec.begin(),
		     il_on_heap_bit_vec.end()));
	}
	REQUIRE(il_on_heap_bit_vec_allocator.alive() == 0);
	REQUIRE(il_on_heap_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(il_on_heap_bit_vec_allocator.allocations() ==
	        il_on_heap_bit_vec_allocator.deallocations());
	REQUIRE(il_on_heap_bit_vec_allocator.destructions() ==
	        il_on_heap_bit_vec_allocator.constructions());

	sbv_allocator fl_on_heap_bit_vec_allocator;
	{
		const std::ptrdiff_t fl_large_size = std::size(bitsy::tests::source_large());
		const std::ptrdiff_t fl_large_expected_allocations   = 1;
		const std::ptrdiff_t fl_large_expected_deallocations = 0;
		const std::ptrdiff_t fl_large_expected_constructions =
		     bitsy::bit_to_element_size<TestType>(fl_large_size);
		const std::ptrdiff_t fl_large_expected_destructions = 0;
		const std::ptrdiff_t fl_large_expected_alive =
		     fl_large_expected_constructions - fl_large_expected_destructions;
		const std::ptrdiff_t fl_large_expected_allocations_alive =
		     fl_large_expected_allocations - fl_large_expected_deallocations;
		tracking_sbv fl_on_heap_bit_vec(std::cbegin(bitsy::tests::source_large()),
		     std::cend(bitsy::tests::source_large()), fl_on_heap_bit_vec_allocator);
		sbv_allocator& fl_on_heap_bit_vec_alloc = fl_on_heap_bit_vec.get_allocator();
		auto fl_on_heap_bit_vec_size = static_cast<std::ptrdiff_t>(fl_on_heap_bit_vec.size());
		REQUIRE(fl_on_heap_bit_vec_size == fl_large_size);
		auto fl_on_heap_bit_vec_empty = fl_on_heap_bit_vec.empty();
		REQUIRE_FALSE(fl_on_heap_bit_vec_empty);
		auto fl_on_heap_bit_vec_is_inline = fl_on_heap_bit_vec.is_inline();
		REQUIRE_FALSE(fl_on_heap_bit_vec_is_inline);
		auto fl_on_heap_bit_vec_alloc_alive = fl_on_heap_bit_vec_alloc.alive();
		REQUIRE(fl_on_heap_bit_vec_alloc_alive == fl_large_expected_alive);
		auto fl_on_heap_bit_vec_alloc_allocations_alive =
		     fl_on_heap_bit_vec_alloc.allocations_alive();
		REQUIRE(
		     fl_on_heap_bit_vec_alloc_allocations_alive == fl_large_expected_allocations_alive);
		auto fl_on_heap_bit_vec_alloc_constructions = fl_on_heap_bit_vec_alloc.constructions();
		REQUIRE(fl_on_heap_bit_vec_alloc_constructions == fl_large_expected_constructions);
		auto fl_on_heap_bit_vec_alloc_destructions = fl_on_heap_bit_vec_alloc.destructions();
		REQUIRE(fl_on_heap_bit_vec_alloc_destructions == fl_large_expected_destructions);
		auto fl_on_heap_bit_vec_alloc_allocations = fl_on_heap_bit_vec_alloc.allocations();
		REQUIRE(fl_on_heap_bit_vec_alloc_allocations == fl_large_expected_allocations);
		auto fl_on_heap_bit_vec_alloc_deallocations = fl_on_heap_bit_vec_alloc.deallocations();
		REQUIRE(fl_on_heap_bit_vec_alloc_deallocations == fl_large_expected_deallocations);
		REQUIRE(std::equal(std::cbegin(bitsy::tests::source_large()),
		     std::cend(bitsy::tests::source_large()), fl_on_heap_bit_vec.begin(),
		     fl_on_heap_bit_vec.end()));
	}
	REQUIRE(fl_on_heap_bit_vec_allocator.alive() == 0);
	REQUIRE(fl_on_heap_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(fl_on_heap_bit_vec_allocator.allocations() ==
	        fl_on_heap_bit_vec_allocator.deallocations());
	REQUIRE(fl_on_heap_bit_vec_allocator.destructions() ==
	        fl_on_heap_bit_vec_allocator.constructions());

	sbv_allocator cv_on_heap_bit_vec_allocator;
	{
		const std::ptrdiff_t cv_large_size = std::size(bitsy::tests::source_large_all_1());
		const std::ptrdiff_t cv_large_expected_allocations   = 1;
		const std::ptrdiff_t cv_large_expected_deallocations = 0;
		const std::ptrdiff_t cv_large_expected_constructions =
		     bitsy::bit_to_element_size<TestType>(cv_large_size);
		const std::ptrdiff_t cv_large_expected_destructions = 0;
		const std::ptrdiff_t cv_large_expected_alive =
		     cv_large_expected_constructions - cv_large_expected_destructions;
		const std::ptrdiff_t cv_large_expected_allocations_alive =
		     cv_large_expected_allocations - cv_large_expected_deallocations;
		tracking_sbv cv_on_heap_bit_vec(std::size(bitsy::tests::source_large_all_1()),
		     bitsy::bit1, cv_on_heap_bit_vec_allocator);
		sbv_allocator& cv_on_heap_bit_vec_alloc = cv_on_heap_bit_vec.get_allocator();
		auto cv_on_heap_bit_vec_size = static_cast<std::ptrdiff_t>(cv_on_heap_bit_vec.size());
		REQUIRE(cv_on_heap_bit_vec_size == cv_large_size);
		auto cv_on_heap_bit_vec_empty = cv_on_heap_bit_vec.empty();
		REQUIRE_FALSE(cv_on_heap_bit_vec_empty);
		auto cv_on_heap_bit_vec_is_inline = cv_on_heap_bit_vec.is_inline();
		REQUIRE_FALSE(cv_on_heap_bit_vec_is_inline);
		auto cv_on_heap_bit_vec_alloc_alive = cv_on_heap_bit_vec_alloc.alive();
		REQUIRE(cv_on_heap_bit_vec_alloc_alive == cv_large_expected_alive);
		auto cv_on_heap_bit_vec_alloc_allocations_alive =
		     cv_on_heap_bit_vec_alloc.allocations_alive();
		REQUIRE(
		     cv_on_heap_bit_vec_alloc_allocations_alive == cv_large_expected_allocations_alive);
		auto cv_on_heap_bit_vec_alloc_constructions = cv_on_heap_bit_vec_alloc.constructions();
		REQUIRE(cv_on_heap_bit_vec_alloc_constructions == cv_large_expected_constructions);
		auto cv_on_heap_bit_vec_alloc_destructions = cv_on_heap_bit_vec_alloc.destructions();
		REQUIRE(cv_on_heap_bit_vec_alloc_destructions == cv_large_expected_destructions);
		auto cv_on_heap_bit_vec_alloc_allocations = cv_on_heap_bit_vec_alloc.allocations();
		REQUIRE(cv_on_heap_bit_vec_alloc_allocations == cv_large_expected_allocations);
		auto cv_on_heap_bit_vec_alloc_deallocations = cv_on_heap_bit_vec_alloc.deallocations();
		REQUIRE(cv_on_heap_bit_vec_alloc_deallocations == cv_large_expected_deallocations);
		REQUIRE(std::equal(std::cbegin(bitsy::tests::source_large_all_1()),
		     std::cend(bitsy::tests::source_large_all_1()), cv_on_heap_bit_vec.begin(),
		     cv_on_heap_bit_vec.end()));
	}
	REQUIRE(cv_on_heap_bit_vec_allocator.alive() == 0);
	REQUIRE(cv_on_heap_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(cv_on_heap_bit_vec_allocator.allocations() ==
	        cv_on_heap_bit_vec_allocator.deallocations());
	REQUIRE(cv_on_heap_bit_vec_allocator.destructions() ==
	        cv_on_heap_bit_vec_allocator.constructions());

	sbv_allocator fl_bidi_on_heap_bit_vec_allocator;
	{
		const std::ptrdiff_t fl_bidi_large_size = std::size(bitsy::tests::list_large());
		const std::ptrdiff_t fl_bidi_large_expected_allocations   = 1;
		const std::ptrdiff_t fl_bidi_large_expected_deallocations = 0;
		const std::ptrdiff_t fl_bidi_large_expected_constructions =
		     bitsy::bit_to_element_size<TestType>(fl_bidi_large_size);
		const std::ptrdiff_t fl_bidi_large_expected_destructions = 0;
		const std::ptrdiff_t fl_bidi_large_expected_alive =
		     bitsy::bit_to_element_size<TestType>(fl_bidi_large_size);
		const std::ptrdiff_t fl_bidi_large_expected_allocations_alive =
		     fl_bidi_large_expected_allocations - fl_bidi_large_expected_deallocations;
		tracking_sbv fl_bidi_on_heap_bit_vec(std::cbegin(bitsy::tests::list_large()),
		     std::cend(bitsy::tests::list_large()), fl_bidi_on_heap_bit_vec_allocator);
		sbv_allocator& fl_bidi_on_heap_bit_vec_alloc = fl_bidi_on_heap_bit_vec.get_allocator();
		auto fl_bidi_on_heap_bit_vec_size =
		     static_cast<std::ptrdiff_t>(fl_bidi_on_heap_bit_vec.size());
		REQUIRE(fl_bidi_on_heap_bit_vec_size == fl_bidi_large_size);
		auto fl_bidi_on_heap_bit_vec_empty = fl_bidi_on_heap_bit_vec.empty();
		REQUIRE_FALSE(fl_bidi_on_heap_bit_vec_empty);
		auto fl_bidi_on_heap_bit_vec_is_inline = fl_bidi_on_heap_bit_vec.is_inline();
		REQUIRE_FALSE(fl_bidi_on_heap_bit_vec_is_inline);
		auto fl_bidi_on_heap_bit_vec_alloc_alive = fl_bidi_on_heap_bit_vec_alloc.alive();
		REQUIRE(fl_bidi_on_heap_bit_vec_alloc_alive == fl_bidi_large_expected_alive);
		auto fl_bidi_on_heap_bit_vec_alloc_allocations_alive =
		     fl_bidi_on_heap_bit_vec_alloc.allocations_alive();
		REQUIRE(fl_bidi_on_heap_bit_vec_alloc_allocations_alive ==
		        fl_bidi_large_expected_allocations_alive);
		auto fl_bidi_on_heap_bit_vec_alloc_constructions =
		     fl_bidi_on_heap_bit_vec_alloc.constructions();
		REQUIRE(
		     fl_bidi_on_heap_bit_vec_alloc_constructions >= fl_bidi_large_expected_constructions);
		auto fl_bidi_on_heap_bit_vec_alloc_destructions =
		     fl_bidi_on_heap_bit_vec_alloc.destructions();
		REQUIRE(
		     fl_bidi_on_heap_bit_vec_alloc_destructions >= fl_bidi_large_expected_destructions);
		auto fl_bidi_on_heap_bit_vec_alloc_allocations =
		     fl_bidi_on_heap_bit_vec_alloc.allocations();
		REQUIRE(fl_bidi_on_heap_bit_vec_alloc_allocations >= fl_bidi_large_expected_allocations);
		auto fl_bidi_on_heap_bit_vec_alloc_deallocations =
		     fl_bidi_on_heap_bit_vec_alloc.deallocations();
		REQUIRE(
		     fl_bidi_on_heap_bit_vec_alloc_deallocations >= fl_bidi_large_expected_deallocations);
		REQUIRE(std::equal(std::cbegin(bitsy::tests::list_large()),
		     std::cend(bitsy::tests::list_large()), fl_bidi_on_heap_bit_vec.begin(),
		     fl_bidi_on_heap_bit_vec.end()));
	}
	REQUIRE(fl_bidi_on_heap_bit_vec_allocator.alive() == 0);
	REQUIRE(fl_bidi_on_heap_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(fl_bidi_on_heap_bit_vec_allocator.allocations() ==
	        fl_bidi_on_heap_bit_vec_allocator.deallocations());
	REQUIRE(fl_bidi_on_heap_bit_vec_allocator.destructions() ==
	        fl_bidi_on_heap_bit_vec_allocator.constructions());

	sbv_allocator cv_bidi_on_heap_bit_vec_allocator;
	{
		const std::ptrdiff_t cv_bidi_large_size = std::size(bitsy::tests::list_large_all_1());
		const std::ptrdiff_t cv_bidi_large_expected_allocations   = 1;
		const std::ptrdiff_t cv_bidi_large_expected_deallocations = 0;
		const std::ptrdiff_t cv_bidi_large_expected_constructions =
		     bitsy::bit_to_element_size<TestType>(cv_bidi_large_size);
		const std::ptrdiff_t cv_bidi_large_expected_destructions = 0;
		const std::ptrdiff_t cv_bidi_large_expected_alive =
		     bitsy::bit_to_element_size<TestType>(cv_bidi_large_size);
		const std::ptrdiff_t cv_bidi_large_expected_allocations_alive =
		     cv_bidi_large_expected_allocations - cv_bidi_large_expected_deallocations;
		tracking_sbv cv_bidi_on_heap_bit_vec(
		     cv_bidi_large_size, true, cv_bidi_on_heap_bit_vec_allocator);
		sbv_allocator& cv_bidi_on_heap_bit_vec_alloc = cv_bidi_on_heap_bit_vec.get_allocator();
		auto cv_bidi_on_heap_bit_vec_size =
		     static_cast<std::ptrdiff_t>(cv_bidi_on_heap_bit_vec.size());
		REQUIRE(cv_bidi_on_heap_bit_vec_size == cv_bidi_large_size);
		auto cv_bidi_on_heap_bit_vec_empty = cv_bidi_on_heap_bit_vec.empty();
		REQUIRE_FALSE(cv_bidi_on_heap_bit_vec_empty);
		auto cv_bidi_on_heap_bit_vec_is_inline = cv_bidi_on_heap_bit_vec.is_inline();
		REQUIRE_FALSE(cv_bidi_on_heap_bit_vec_is_inline);
		auto cv_bidi_on_heap_bit_vec_alloc_alive = cv_bidi_on_heap_bit_vec_alloc.alive();
		REQUIRE(cv_bidi_on_heap_bit_vec_alloc_alive == cv_bidi_large_expected_alive);
		auto cv_bidi_on_heap_bit_vec_alloc_allocations_alive =
		     cv_bidi_on_heap_bit_vec_alloc.allocations_alive();
		REQUIRE(cv_bidi_on_heap_bit_vec_alloc_allocations_alive ==
		        cv_bidi_large_expected_allocations_alive);
		auto cv_bidi_on_heap_bit_vec_alloc_constructions =
		     cv_bidi_on_heap_bit_vec_alloc.constructions();
		REQUIRE(
		     cv_bidi_on_heap_bit_vec_alloc_constructions >= cv_bidi_large_expected_constructions);
		auto cv_bidi_on_heap_bit_vec_alloc_destructions =
		     cv_bidi_on_heap_bit_vec_alloc.destructions();
		REQUIRE(
		     cv_bidi_on_heap_bit_vec_alloc_destructions >= cv_bidi_large_expected_destructions);
		auto cv_bidi_on_heap_bit_vec_alloc_allocations =
		     cv_bidi_on_heap_bit_vec_alloc.allocations();
		REQUIRE(cv_bidi_on_heap_bit_vec_alloc_allocations >= cv_bidi_large_expected_allocations);
		auto cv_bidi_on_heap_bit_vec_alloc_deallocations =
		     cv_bidi_on_heap_bit_vec_alloc.deallocations();
		REQUIRE(
		     cv_bidi_on_heap_bit_vec_alloc_deallocations >= cv_bidi_large_expected_deallocations);
		REQUIRE(std::equal(std::cbegin(bitsy::tests::list_large_all_1()),
		     std::cend(bitsy::tests::list_large_all_1()), cv_bidi_on_heap_bit_vec.begin(),
		     cv_bidi_on_heap_bit_vec.end()));
	}
	REQUIRE(cv_bidi_on_heap_bit_vec_allocator.alive() == 0);
	REQUIRE(cv_bidi_on_heap_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(cv_bidi_on_heap_bit_vec_allocator.allocations() ==
	        cv_bidi_on_heap_bit_vec_allocator.deallocations());
	REQUIRE(cv_bidi_on_heap_bit_vec_allocator.destructions() ==
	        cv_bidi_on_heap_bit_vec_allocator.constructions());

	sbv_allocator cv_inplace_bidi_on_heap_bit_vec_allocator;
	{
		const std::ptrdiff_t cv_inplace_bidi_large_size = bitsy::element_to_bit_size<TestType>(
		     bitsy::bit_to_element_size<TestType>(std::size(bitsy::tests::list_large_all_1())));
		const std::ptrdiff_t cv_inplace_bidi_large_expected_allocations   = 1;
		const std::ptrdiff_t cv_inplace_bidi_large_expected_deallocations = 0;
		const std::ptrdiff_t cv_inplace_bidi_large_expected_constructions =
		     bitsy::bit_to_element_size<TestType>(cv_inplace_bidi_large_size);
		const std::ptrdiff_t cv_inplace_bidi_large_expected_destructions = 0;
		const std::ptrdiff_t cv_inplace_bidi_large_expected_alive =
		     bitsy::bit_to_element_size<TestType>(cv_inplace_bidi_large_size);
		const std::ptrdiff_t cv_inplace_bidi_large_expected_allocations_alive =
		     cv_inplace_bidi_large_expected_allocations -
		     cv_inplace_bidi_large_expected_deallocations;
		tracking_sbv cv_inplace_bidi_on_heap_bit_vec(std::in_place,
		     bitsy::bit_to_element_size<TestType>(cv_inplace_bidi_large_size),
		     static_cast<TestType>(
		          std::numeric_limits<bitsy::detail::__any_to_underlying_t<TestType>>::max()),
		     cv_inplace_bidi_on_heap_bit_vec_allocator);
		sbv_allocator& cv_inplace_bidi_on_heap_bit_vec_alloc =
		     cv_inplace_bidi_on_heap_bit_vec.get_allocator();
		auto cv_inplace_bidi_on_heap_bit_vec_size =
		     static_cast<std::ptrdiff_t>(cv_inplace_bidi_on_heap_bit_vec.size());
		REQUIRE(cv_inplace_bidi_on_heap_bit_vec_size == cv_inplace_bidi_large_size);
		auto cv_inplace_bidi_on_heap_bit_vec_empty = cv_inplace_bidi_on_heap_bit_vec.empty();
		REQUIRE_FALSE(cv_inplace_bidi_on_heap_bit_vec_empty);
		auto cv_inplace_bidi_on_heap_bit_vec_is_inline =
		     cv_inplace_bidi_on_heap_bit_vec.is_inline();
		REQUIRE_FALSE(cv_inplace_bidi_on_heap_bit_vec_is_inline);
		auto cv_inplace_bidi_on_heap_bit_vec_alloc_alive =
		     cv_inplace_bidi_on_heap_bit_vec_alloc.alive();
		REQUIRE(
		     cv_inplace_bidi_on_heap_bit_vec_alloc_alive == cv_inplace_bidi_large_expected_alive);
		auto cv_inplace_bidi_on_heap_bit_vec_alloc_allocations_alive =
		     cv_inplace_bidi_on_heap_bit_vec_alloc.allocations_alive();
		REQUIRE(cv_inplace_bidi_on_heap_bit_vec_alloc_allocations_alive ==
		        cv_inplace_bidi_large_expected_allocations_alive);
		auto cv_inplace_bidi_on_heap_bit_vec_alloc_constructions =
		     cv_inplace_bidi_on_heap_bit_vec_alloc.constructions();
		REQUIRE(cv_inplace_bidi_on_heap_bit_vec_alloc_constructions >=
		        cv_inplace_bidi_large_expected_constructions);
		auto cv_inplace_bidi_on_heap_bit_vec_alloc_destructions =
		     cv_inplace_bidi_on_heap_bit_vec_alloc.destructions();
		REQUIRE(cv_inplace_bidi_on_heap_bit_vec_alloc_destructions >=
		        cv_inplace_bidi_large_expected_destructions);
		auto cv_inplace_bidi_on_heap_bit_vec_alloc_allocations =
		     cv_inplace_bidi_on_heap_bit_vec_alloc.allocations();
		REQUIRE(cv_inplace_bidi_on_heap_bit_vec_alloc_allocations >=
		        cv_inplace_bidi_large_expected_allocations);
		auto cv_inplace_bidi_on_heap_bit_vec_alloc_deallocations =
		     cv_inplace_bidi_on_heap_bit_vec_alloc.deallocations();
		REQUIRE(cv_inplace_bidi_on_heap_bit_vec_alloc_deallocations >=
		        cv_inplace_bidi_large_expected_deallocations);
		REQUIRE(std::find(cv_inplace_bidi_on_heap_bit_vec.cbegin(),
		             cv_inplace_bidi_on_heap_bit_vec.cend(),
		             false) == cv_inplace_bidi_on_heap_bit_vec.cend());
	}
	REQUIRE(cv_inplace_bidi_on_heap_bit_vec_allocator.alive() == 0);
	REQUIRE(cv_inplace_bidi_on_heap_bit_vec_allocator.allocations_alive() == 0);
	REQUIRE(cv_inplace_bidi_on_heap_bit_vec_allocator.allocations() ==
	        cv_inplace_bidi_on_heap_bit_vec_allocator.deallocations());
	REQUIRE(cv_inplace_bidi_on_heap_bit_vec_allocator.destructions() ==
	        cv_inplace_bidi_on_heap_bit_vec_allocator.constructions());
}
