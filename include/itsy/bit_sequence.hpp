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

#ifndef ITSY_BITSY_BIT_SEQUENCE_HPP
#define ITSY_BITSY_BIT_SEQUENCE_HPP

#include <itsy/version.hpp>

#include <itsy/bit_operations.hpp>
#include <itsy/bit_iterator.hpp>
#include <itsy/bit_view.hpp>

#include <itsy/detail/bit_sequence.hpp>

#include <vector>

namespace bitsy
{

	template<typename C>
	class bit_sequence : public ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_sequence<C> {
	private:
		using base_t = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_sequence<C>;
	public:
		using difference_type = typename base_t::difference_type;
		using size_type       = typename base_t::size_type;
		using value_type      = typename base_t::value_type;
		using reference       = typename base_t::reference;
		using const_reference = typename base_t::const_reference;
		using iterator_category = typename base_t::iterator_category;
		using iterator_concept = typename base_t::iterator_concept;
		using pointer           = typename base_t::pointer;
		using iterator          = typename base_t::iterator;
		using sentinel          = typename base_t::sentinel;
		using const_iterator    = typename base_t::const_iterator;
		using const_sentinel    = typename base_t::const_sentinel;
		using container_type    = typename base_t::container_type;

		using base_t::base_t;
		using base_t::operator=;
	};

	template<typename T, typename Allocator = std::allocator<T>>
	class bit_vector : public bit_sequence<std::vector<T, Allocator>> {
	private:
		using base_t = bit_sequence<std::vector<T, Allocator>>;
	public:
		using difference_type = typename base_t::difference_type;
		using size_type       = typename base_t::size_type;
		using value_type      = typename base_t::value_type;
		using reference       = typename base_t::reference;
		using const_reference = typename base_t::const_reference;
		using iterator_category = typename base_t::iterator_category;
		using iterator_concept = typename base_t::iterator_concept;
		using pointer           = typename base_t::pointer;
		using iterator          = typename base_t::iterator;
		using sentinel          = typename base_t::sentinel;
		using const_iterator    = typename base_t::const_iterator;
		using const_sentinel    = typename base_t::const_sentinel;
		using container_type    = typename base_t::container_type;

		using base_t::base_t;
		using base_t::operator=;
	};

} // namespace bitsy

#endif // ITSY_BITSY_BIT_SEQUENCE_HPP
