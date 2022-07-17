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

#ifndef ITSY_BITSY_TESTS_SHARED_ALLOCATOR_TESTS_HPP
#define ITSY_BITSY_TESTS_SHARED_ALLOCATOR_TESTS_HPP

#include <itsy/tests/tracking_allocator.hpp>
#include <itsy/tests/constants.hpp>

#include <catch2/catch.hpp>

#include <memory>
#include <cstddef>
#include <list>
#include <type_traits>
#include <iterator>

namespace bitsy::tests
{
	template<typename TestType, typename Allocator, typename Sbv, typename Source>
	void
	allocator_test(Sbv& bit_vec, Source& source)
	{
		using iterator = decltype(std::begin(source));
		static constexpr bool is_bidi =
		     std::is_base_of_v<typename std::iterator_traits<iterator>::iterator_category,
		          std::bidirectional_iterator_tag>;
		static constexpr bool is_bit_source =
		     (::std::is_same_v<typename ::std::iterator_traits<iterator>::value_type, bool> ||
		          ::std::is_same_v<typename ::std::iterator_traits<iterator>::value_type,
		               bitsy::bit_value>);
		static constexpr std::ptrdiff_t size_multiplier =
		     is_bit_source ? 1 : bitsy::binary_digits_v<TestType>;
		static constexpr std::ptrdiff_t expected_inline_size = Sbv::inline_capacity;

		const std::ptrdiff_t source_size = std::size(source) * size_multiplier;
		const std::ptrdiff_t source_storage_size =
		     bitsy::bit_to_element_size<TestType>(source_size);
		const bool expected_on_heap =
		     (expected_inline_size == 0) ? true : (source_size > expected_inline_size);
		const std::ptrdiff_t expected_allocations = expected_on_heap && (source_size > 0) ? 1 : 0;
		const std::ptrdiff_t expected_deallocations = 0;
		const std::ptrdiff_t expected_constructions = source_storage_size;
		const std::ptrdiff_t expected_destructions  = 0;
		const std::ptrdiff_t expected_alive         = source_storage_size;
		const std::ptrdiff_t expected_allocations_alive =
		     expected_allocations - expected_deallocations;
		Allocator& bit_vec_alloc             = bit_vec.get_allocator();
		auto bit_vec_size                    = static_cast<std::ptrdiff_t>(bit_vec.size());
		auto bit_vec_empty                   = bit_vec.empty();
		auto bit_vec_is_inline               = bit_vec.is_inline();
		auto bit_vec_alloc_alive             = bit_vec_alloc.alive();
		auto bit_vec_alloc_allocations_alive = bit_vec_alloc.allocations_alive();
		auto bit_vec_alloc_constructions     = bit_vec_alloc.constructions();
		auto bit_vec_alloc_destructions      = bit_vec_alloc.destructions();
		auto bit_vec_alloc_allocations       = bit_vec_alloc.allocations();
		auto bit_vec_alloc_deallocations     = bit_vec_alloc.deallocations();
		REQUIRE(bit_vec_size == source_size);
		if (source_size == 0)
			{
				REQUIRE(bit_vec_empty);
			}
		else
			{
				REQUIRE_FALSE(bit_vec_empty);
			}
		if (expected_on_heap)
			{
				REQUIRE_FALSE(bit_vec_is_inline);
			}
		else
			{
				REQUIRE(bit_vec_is_inline);
			}
		REQUIRE(bit_vec_alloc_alive == expected_alive);
		REQUIRE(bit_vec_alloc_allocations_alive == expected_allocations_alive);
		if constexpr (is_bidi)
			{
				REQUIRE(bit_vec_alloc_constructions >= expected_constructions);
				REQUIRE(bit_vec_alloc_destructions >= expected_destructions);
				REQUIRE(bit_vec_alloc_allocations >= expected_allocations);
				REQUIRE(bit_vec_alloc_deallocations >= expected_deallocations);
			}
		else
			{
				REQUIRE(bit_vec_alloc_constructions == expected_constructions);
				REQUIRE(bit_vec_alloc_destructions == expected_destructions);
				REQUIRE(bit_vec_alloc_allocations == expected_allocations);
				REQUIRE(bit_vec_alloc_deallocations == expected_deallocations);
			}

		if constexpr (is_bit_source)
			{
				auto source_first = std::begin(source);
				auto first        = bit_vec.cbegin();
				auto last         = bit_vec.cend();
				for (; first != last; ++first, (void)++source_first)
					{
						const auto& expected_val = *source_first;
						const auto& val          = *first;
						REQUIRE(val.value() == expected_val);
					}
			}
		else
			{
				auto source_first = bitsy::bit_iterator<iterator>(std::begin(source), 0);
				auto first        = bit_vec.cbegin();
				auto last         = bit_vec.cend();
				for (std::size_t index = 0; first != last;
				     ++first, (void)++source_first, (void)++index)
					{
						const auto& expected_val = *source_first;
						const auto& val          = *first;
						REQUIRE(val.value() == expected_val.value());
					}
			}
	}

	template<typename Allocator>
	void
	balanced_allocator_test(tracking_allocator<Allocator>& bit_vec_allocator)
	{
		REQUIRE(bit_vec_allocator.alive() == 0);
		REQUIRE(bit_vec_allocator.allocations_alive() == 0);
		REQUIRE(bit_vec_allocator.allocations() == bit_vec_allocator.deallocations());
		REQUIRE(bit_vec_allocator.destructions() == bit_vec_allocator.constructions());
	}
} // namespace bitsy::tests

#endif // ITSY_BITSY_TESTS_SHARED_ALLOCATOR_TESTS_HPP
