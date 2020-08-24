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

#ifndef ITSY_BITSY_BIT_VIEW_HPP
#define ITSY_BITSY_BIT_VIEW_HPP

#include <itsy/version.hpp>
#include <itsy/bit_iterator.hpp>

#include <itsy/detail/bit_view.hpp>

namespace bitsy
{
	template<typename Range>
	class word_bit_bounds : public ::ITSY_BITSY_SOURCE_NAMESPACE::__word_bit_bounds<Range> {
	private:
		using base_t = ::ITSY_BITSY_SOURCE_NAMESPACE::__word_bit_bounds<Range>; 
	public:
		using base_t::base_t;
	};

	template<typename Range>
	class dynamic_bit_bounds_for : public ::ITSY_BITSY_SOURCE_NAMESPACE::__dynamic_bit_bounds_for<Range> {
	private:
		using base_t = ::ITSY_BITSY_SOURCE_NAMESPACE::__dynamic_bit_bounds_for<Range>;
	public:
		using base_t::base_t;
	};

	template<std::size_t first, std::size_t last>
	class bit_bounds : public ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_bounds<first, last> {
	private:
		using base_t = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_bounds<first, last>;
	public:
		using base_t::base_t;		
	};

	class dynamic_bit_bounds : public ::ITSY_BITSY_SOURCE_NAMESPACE::__dynamic_bit_bounds {
	private:
		using base_t = ::ITSY_BITSY_SOURCE_NAMESPACE::__dynamic_bit_bounds;
	public:
		using base_t::base_t;
	};

	template<typename Range, typename Bounds = word_bit_bounds<Range>>
	class bit_view : public ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_view<Range, Bounds> {
	private:
		using base_t = ::ITSY_BITSY_SOURCE_NAMESPACE::__bit_view<Range, Bounds>;
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

#endif // ITSY_BITSY_BIT_VIEW_HPP
