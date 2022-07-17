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

#ifndef ITSY_BITSY_TESTS_SHARED_INSERT_TESTS_HPP
#define ITSY_BITSY_TESTS_SHARED_INSERT_TESTS_HPP

#include <catch2/catch.hpp>

#include <itsy/tests/constants.hpp>

namespace bitsy::tests
{
	template<insert_action action, typename Sequence, typename Source>
	std::size_t
	insert_into_sequence(Sequence& sequence, Source& source)
	{
		std::size_t seq_size = sequence.size();
		for (std::size_t i = 0; i < source.size(); ++i)
			{
				bool bool_val = source[i];
				const bitsy::bit_value val = bool_val;
				if constexpr (action == insert_action::push_front)
					{
						sequence.push_front(val);
						REQUIRE(sequence.front() == val);
					}
				else if constexpr (action == insert_action::push_back)
					{
						sequence.push_back(val);
						REQUIRE(sequence.back() == val);
					}
				else if constexpr (action == insert_action::begin)
					{
						sequence.insert(sequence.cbegin(), val);
						REQUIRE(sequence.front() == val);
					}
				else if constexpr (action == insert_action::end)
					{
						sequence.insert(sequence.cend(), val);
						REQUIRE(sequence.back() == val);
					}
				std::size_t current_seq_size = sequence.size();
				REQUIRE(current_seq_size == (seq_size + 1));
				seq_size = current_seq_size;
			}
		return seq_size;
	}

} // namespace bitsy::tests

#endif // ITSY_BITSY_TESTS_SHARED_INSERT_TESTS_HPP
