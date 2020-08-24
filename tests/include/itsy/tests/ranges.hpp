// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

// ranges shim for std libraries that haven't caught up

#ifndef ITSY_BITSY_TESTS_RANGES_HPP
#define ITSY_BITSY_TESTS_RANGES_HPP

#include <itsy/bitsy.hpp>

#include <cstddef>

namespace bitsy::tests
{
	enum class subrange_kind : bool { unsized, sized };

	template <typename _It, typename _Sen = _It,
		subrange_kind _Kind = ::ITSY_BITSY_SOURCE_NAMESPACE::__is_iterator_concept_or_better_v<::std::random_access_iterator_tag,
			                      _It>&& ::std::is_same_v<_It, _Sen>
			? subrange_kind::sized
			: subrange_kind::unsized>
	class subrange {
	public:
		using iterator          = _It;
		using const_iterator    = iterator;
		using sentinel          = _Sen;
		using const_sentinel    = sentinel;
		using iterator_category = typename ::std::iterator_traits<iterator>::iterator_category;
		using iterator_concept  = ::ITSY_BITSY_SOURCE_NAMESPACE::__iterator_concept_t<iterator>;
		using pointer           = typename ::std::iterator_traits<iterator>::pointer;
		using const_pointer     = pointer;
		using reference         = typename ::std::iterator_traits<iterator>::reference;
		using const_reference   = reference;
		using value_type        = typename ::std::iterator_traits<iterator>::value_type;
		using difference_type   = ::std::conditional_t<::std::is_same_v<iterator_concept, ::std::output_iterator_tag>,
               ptrdiff_t, typename ::std::iterator_traits<iterator>::difference_type>;
		using size_type         = ::std::make_unsigned_t<difference_type>;

		constexpr subrange() noexcept = default;

		template <typename _Range,
			::std::enable_if_t<!::std::is_same_v<::ITSY_BITSY_SOURCE_NAMESPACE::__remove_cvref_t<_Range>, subrange>>* = nullptr>
		constexpr subrange(_Range&& __range) noexcept
		: subrange(::ITSY_BITSY_SOURCE_NAMESPACE::__adl_begin(__range), ::ITSY_BITSY_SOURCE_NAMESPACE::__adl_end(__range)) {
		}

		constexpr subrange(iterator __it, sentinel __sen) noexcept
		: _M_it(::std::move(__it)), _M_sen(::std::move(__sen)) {
		}

		constexpr iterator begin() const noexcept {
			return this->_M_it;
		}

		constexpr sentinel end() const noexcept {
			return this->_M_sen;
		}

		constexpr bool empty() const noexcept {
			return this->_M_it == this->_M_sen;
		}

		template <subrange_kind _Dummy = _Kind, ::std::enable_if_t<_Dummy == subrange_kind::sized>* = nullptr>
		constexpr size_type size() const noexcept {
			return ::std::distance(this->_M_it, this->_M_sen);
		}

		template <typename _Dummy = _It,
			::std::enable_if_t<
				::ITSY_BITSY_SOURCE_NAMESPACE::__is_iterator_concept_or_better_v<::ITSY_BITSY_SOURCE_NAMESPACE::__contiguous_iterator_tag, _Dummy>>* = nullptr>
		constexpr pointer data() const noexcept {
			return ::std::addressof(*this->_M_it);
		}

	private:
		iterator _M_it;
		sentinel _M_sen;
	};

} // namespace bitsy::tests


#endif // ITSY_BITSY_TESTS_RANGES_HPP
