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

#ifndef ITSY_BITSY_DETAIL_ALGORITHM_HPP
#define ITSY_BITSY_DETAIL_ALGORITHM_HPP 1

#include <itsy/detail/bit_iterator.hpp>
#include <itsy/detail/bit_operations.hpp>

#include <algorithm>
#include <iterator>
#include <utility>

namespace ITSY_BITSY_SOURCE_NAMESPACE
{
	template<bool _Value, typename _It>
	constexpr __bit_iterator<_It>
	__bit_find_value(__bit_iterator<_It> __first, __bit_iterator<_It> __last)
	{
		using __iterator       = __bit_iterator<_It>;
		using __base_iterator  = typename __bit_iterator<_It>::iterator_type;
		using __base_reference = typename ::std::iterator_traits<__base_iterator>::reference;

		for (; __first != __last && __first.position() != 0; ++__first)
			{
				if constexpr (_Value)
					{
						if (static_cast<bool>(*__first))
							{
								return __first;
							}
					}
				else
					{
						if (!static_cast<bool>(*__first))
							{
								return __first;
							}
					}
			}
		__base_iterator __first_base = ::std::move(__first).base();
		auto __last_position         = __last.position();
		__base_iterator __last_base  = ::std::move(__last).base();
		for (; __first_base != __last_base; ++__first_base)
			{
				__base_reference __ref_base = *__first_base;
				if constexpr (_Value)
					{
						int __first_lsb = __bit_firstr_one(__ref_base);
						if (__first_lsb != 0)
							{
								return __iterator(::std::move(__first_base), __first_lsb - 1);
							}
					}
				else
					{
						int __first_lsb = __bit_firstr_zero(__ref_base);
						if (__first_lsb != 0)
							{
								return __iterator(::std::move(__first_base), __first_lsb - 1);
							}
					}
			}
		if (__last_position == 0)
			{
				return __last;
			}
		__first = __iterator(::std::move(__first_base), 0);
		__last  = __iterator(::std::move(__last_base), __last_position);
		for (; __first != __last; ++__first)
			{
				if constexpr (_Value)
					{
						if (static_cast<bool>(*__first))
							{
								return __first;
							}
					}
				else
					{
						if (!static_cast<bool>(*__first))
							{
								return __first;
							}
					}
			}
		return __last;
	}

	template<typename _It, typename _Type>
	constexpr __bit_iterator<_It>
	__bit_find(__bit_iterator<_It> __first, __bit_iterator<_It> __last, const _Type& __val)
	{
		if (__first == __last)
			{
				return __first;
			}
		if (__val)
			{
				return __bit_find_value<true>(::std::move(__first), ::std::move(__last));
			}
		else
			{
				return __bit_find_value<false>(::std::move(__first), ::std::move(__last));
			}
	}

	template<typename _InputIt, typename _ForwardIt>
	constexpr __bit_iterator<_InputIt>
	__bit_find_first_of(__bit_iterator<_InputIt> __first, __bit_iterator<_InputIt> __last, _ForwardIt __search_first,
	     _ForwardIt __search_last)
	{
		if (__first == __last || __search_first == __search_last)
			{
				return __last;
			}
		// we note that the value space here is literally 2,
		// and thusly know that, in advance,
		// we can make quite a few hard optimizations
		// we if know in totally what we are looking for
		bool __find_false = false;
		bool __find_true  = false;
		for (; __search_first != __search_last; ++__search_first)
			{
				if (static_cast<bool>(*__search_first))
					{
						__find_true = true;
					}
				else
					{
						__find_false = true;
					}
			}
		if (__find_false && __find_true)
			{
				// literally any value is good enough!
				return __first;
			}
		if (__find_true)
			{
				return __bit_find_value<true>(::std::move(__first), ::std::move(__last));
			}
		else
			{
				return __bit_find_value<false>(::std::move(__first), ::std::move(__last));
			}
	}

	template<typename _It0, typename _It1>
	constexpr bool
	__bit_equal(__bit_iterator<_It0> __first0, __bit_iterator<_It0> __last0, __bit_iterator<_It1> __first1)
	{
		using __iterator0          = __bit_iterator<_It0>;
		using __iterator1          = __bit_iterator<_It1>;
		using __iterator_category0 = typename __iterator0::iterator_category;
		using __iterator_category1 = typename __iterator1::iterator_category;
		using __base_iterator0     = typename __iterator0::iterator_type;
		using __base_iterator1     = typename __iterator1::iterator_type;
		using __base_value_type0   = typename ::std::iterator_traits<__base_iterator0>::value_type;
		using __base_value_type1   = typename ::std::iterator_traits<__base_iterator1>::value_type;
		if constexpr (::std::is_unsigned_v<__base_value_type0> && ::std::is_unsigned_v<__base_value_type1> &&
		              ::std::is_same_v<__base_value_type0, __base_value_type1>)
			{
				if constexpr (__is_iterator_category_or_better_v<::std::forward_iterator_tag,
				                   __iterator_category0> &&
				              __is_iterator_category_or_better_v<::std::forward_iterator_tag, __iterator_category1>)
					{
						if (__first0.position() == __first1.position())
							{
								// can compare base items
								if (__first0.position() != 0)
									{
										// align to word boundary
										for (; __first0 != __last0 && __first0.position() != 0;
										     ++__first0, (void)++__first1)
											{
												if (!(*__first0 == *__first1))
													{
														return false;
													}
											}
									}
								auto __last0_position          = __last0.position();
								__base_iterator0 __first_base0 = ::std::move(__first0).base();
								__base_iterator0 __last_base0  = ::std::move(__last0).base();
								__base_iterator1 __first_base1 = ::std::move(__first1).base();
								std::pair<__base_iterator0, __base_iterator1> __base_mismatch =
								     ::std::mismatch(__first_base0, __last_base0, __first_base1);
								bool __base_equal = __base_mismatch.first == __last_base0;
								if (__last0_position == 0)
									{
										return __base_equal;
									}
								else if (!__base_equal)
									{
										return false;
									}
								__first0 = __iterator0(::std::move(__base_mismatch.first), 0);
								__first1 = __iterator1(::std::move(__base_mismatch.second), 0);
							}
					}
				else
					{
						if (__first0.position() == 0 && __first1.position() == 0 && __last0.position() == 0)
							{
								// can compare base items
								__base_iterator0 __first_base0 = ::std::move(__first0).base();
								__base_iterator0 __last_base0  = ::std::move(__last0).base();
								__base_iterator1 __first_base1 = ::std::move(__first1).base();
								return ::std::equal(::std::move(__first_base0), ::std::move(__last_base0),
								     ::std::move(__first_base1));
							}
					}
			}
		for (; __first0 != __last0; ++__first0, (void)++__first1)
			{
				if (!(*__first0 == *__first1))
					{
						return false;
					}
			}
		return __first0 == __last0;
	}

	template<typename _It0, typename _It1>
	constexpr bool
	__bit_equal(__bit_iterator<_It0> __first0, __bit_iterator<_It0> __last0, __bit_iterator<_It1> __first1,
	     __bit_iterator<_It1> __last1)
	{
		using __iterator0          = __bit_iterator<_It0>;
		using __iterator1          = __bit_iterator<_It1>;
		using __iterator_category0 = typename __iterator0::iterator_category;
		using __iterator_category1 = typename __iterator1::iterator_category;
		using __base_iterator0     = typename __iterator0::iterator_type;
		using __base_iterator1     = typename __iterator1::iterator_type;
		using __base_value_type0   = typename ::std::iterator_traits<__base_iterator0>::value_type;
		using __base_value_type1   = typename ::std::iterator_traits<__base_iterator1>::value_type;
		if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, __iterator_category0> &&
		              __is_iterator_category_or_better_v<::std::random_access_iterator_tag, __iterator_category1>)
			{
				auto __dist0 = ::std::distance(__first0, __last0);
				auto __dist1 = ::std::distance(__first1, __last1);
				if (__dist0 != __dist1)
					{
						return false;
					}
			}
		if constexpr (::std::is_unsigned_v<__base_value_type0> && ::std::is_unsigned_v<__base_value_type1> &&
		              ::std::is_same_v<__base_value_type0, __base_value_type1>)
			{
				if constexpr (__is_iterator_category_or_better_v<::std::forward_iterator_tag,
				                   __iterator_category0> &&
				              __is_iterator_category_or_better_v<::std::forward_iterator_tag, __iterator_category1>)
					{
						if (__first0.position() == __first1.position())
							{
								// align to word boundary
								for (; __first0 != __last0 && __first1 != __last1 && __first0.position() != 0;
								     ++__first0, (void)++__first1)
									{
										if (!(*__first0 == *__first1))
											{
												return false;
											}
									}
								auto __last0_position          = __last0.position();
								auto __last1_position          = __last1.position();
								__base_iterator0 __first_base0 = ::std::move(__first0).base();
								__base_iterator0 __last_base0  = ::std::move(__last0).base();
								__base_iterator1 __first_base1 = ::std::move(__first1).base();
								__base_iterator1 __last_base1  = ::std::move(__last1).base();
								bool __base_equal =
								     ::std::equal(__first_base0, __last_base0, __first_base1, __last_base1);
								if (__last0_position == 0 && __last1_position == 0)
									{
										return __base_equal;
									}
								else if (!__base_equal)
									{
										return false;
									}
								__first0 = __iterator0(::std::move(__last_base0), 0);
								__first1 = __iterator1(::std::move(__last_base1), 0);
							}
					}
				else
					{
						if (__first0.position() == 0 && __first1.position() == 0 && __last0.position() == 0 &&
						     __last1.position() == 0)
							{
								// can compare base items
								__base_iterator0 __first_base0 = ::std::move(__first0).base();
								__base_iterator0 __last_base0  = ::std::move(__last0).base();
								__base_iterator1 __first_base1 = ::std::move(__first1).base();
								__base_iterator1 __last_base1  = ::std::move(__last1).base();
								return ::std::equal(::std::move(__first_base0), ::std::move(__last_base0),
								     ::std::move(__first_base1), ::std::move(__last_base1));
							}
					}
			}
		for (; __first0 != __last0 && __first1 != __last1; ++__first0, (void)++__first1)
			{
				if (!(*__first0 == *__first1))
					{
						return false;
					}
			}
		return __first0 == __last0 && __first1 == __last1;
	}

	template<typename _InputIt0, typename _InputIt1>
	constexpr bool
	__bit_lexicographical_compare(__bit_iterator<_InputIt0> __first0, __bit_iterator<_InputIt0> __last0,
	     __bit_iterator<_InputIt1> __first1, __bit_iterator<_InputIt1> __last1)
	{
		using __iterator0          = __bit_iterator<_InputIt0>;
		using __iterator1          = __bit_iterator<_InputIt1>;
		using __reference0         = typename ::std::iterator_traits<__iterator0>::reference;
		using __reference1         = typename ::std::iterator_traits<__iterator1>::reference;
		using __iterator_category0 = typename ::std::iterator_traits<__iterator0>::iterator_category;
		using __iterator_category1 = typename ::std::iterator_traits<__iterator1>::iterator_category;
		using __base_iterator0     = typename __iterator0::iterator_type;
		using __base_iterator1     = typename __iterator1::iterator_type;
		using __base_value_type0   = typename ::std::iterator_traits<__base_iterator0>::value_type;
		using __base_value_type1   = typename ::std::iterator_traits<__base_iterator1>::value_type;
		if constexpr (::std::is_unsigned_v<__base_value_type0> && ::std::is_unsigned_v<__base_value_type1> &&
		              ::std::is_same_v<__base_value_type0, __base_value_type1>)
			{
				if constexpr (__is_iterator_category_or_better_v<::std::forward_iterator_tag,
				                   __iterator_category0> &&
				              __is_iterator_category_or_better_v<::std::forward_iterator_tag, __iterator_category1>)
					{
						if (__first0.position() == __first1.position())
							{
								if (__first0.position() != 0)
									{
										for (; __first0 != __last0 && __first1 != __last1 &&
										       __first0.position() != 0;
										     ++__first0, (void)++__first1)
											{
												__reference0 __ref_base0 = *__first0;
												__reference1 __ref_base1 = *__first1;
												if (__ref_base0 < __ref_base1)
													{
														return true;
													}
												if (__ref_base1 < __ref_base0)
													{
														return false;
													}
											}
									}
								auto __last0_position          = __last0.position();
								auto __last1_position          = __last1.position();
								__base_iterator0 __first_base0 = ::std::move(__first0).base();
								__base_iterator0 __last_base0  = ::std::move(__last0).base();
								__base_iterator1 __first_base1 = ::std::move(__first1).base();
								__base_iterator1 __last_base1  = ::std::move(__last1).base();
								bool __base_lexicographic_compare =
								     ::std::lexicographical_compare(::std::move(__first_base0), __last_base0,
								          ::std::move(__first_base1), __last_base1);

								if (__last0_position == 0 && __last1_position == 0)
									{
										return __base_lexicographic_compare;
									}
								else if (!__base_lexicographic_compare)
									{
										return false;
									}
								__first0 = __iterator0(::std::move(__last_base0), 0);
								__first1 = __iterator1(::std::move(__last_base1), 0);
							}
					}
				else
					{
						if (__first0.position() == 0 && __first1.position() == 0 && __last0.position() == 0 &&
						     __last1.position() == 0)
							{
								__base_iterator0 __first_base0 = ::std::move(__first0).base();
								__base_iterator0 __last_base0  = ::std::move(__last0).base();
								__base_iterator1 __first_base1 = ::std::move(__first1).base();
								__base_iterator1 __last_base1  = ::std::move(__last1).base();
								return ::std::lexicographical_compare(::std::move(__first_base0),
								     ::std::move(__last_base0), ::std::move(__first_base1),
								     ::std::move(__last_base1));
							}
					}
			}

		// base case
		for (; __first0 != __last0 && __first1 != __last1; ++__first0, (void)++__first1)
			{
				__reference0 __ref_base0 = *__first0;
				__reference1 __ref_base1 = *__first1;
				if (__ref_base0 < __ref_base1)
					{
						return true;
					}
				if (__ref_base1 < __ref_base0)
					{
						return false;
					}
			}
		return __first0 == __last0 && __first1 != __last1;
	}

	template<bool _CheckPosition, typename _ForwardIt>
	constexpr bool
	__bit_is_sorted_until_single_bit_position(
	     __bit_iterator<_ForwardIt>& __first, __bit_iterator<_ForwardIt>& __it, __bit_iterator<_ForwardIt>& __last)
	{
		while (__it != __first && (!_CheckPosition || __it.position() != 0))
			{
				if (__it == __last)
					{
						// reached end, we're okay
						return true;
					}
				if (*__it < *__first)
					{
						return true;
					}
				__first = __it;
				++__it;
			}
		//__first = __it;
		return false;
	}

	template<typename _ForwardIt>
	constexpr __bit_iterator<_ForwardIt>
	__bit_is_sorted_until_unsigned(__bit_iterator<_ForwardIt> __first, __bit_iterator<_ForwardIt> __last)
	{
		if (__first == __last)
			{
				return __last;
			}

		using __iterator      = __bit_iterator<_ForwardIt>;
		using __base_iterator = typename __iterator::iterator_type;

		// advance all the bits first
		__iterator __it = __first;
		++__it;
		if (__it == __last)
			{
				return __it;
			}
		if (__bit_is_sorted_until_single_bit_position<true>(__first, __it, __last))
			{
				return __it;
			}
		auto __last_position        = __last.position();
		__base_iterator __it_base   = __it.base();
		__base_iterator __last_base = __last.base();
		if (__it_base != __last_base)
			{
				// now we can work on individual words and use
				// popcount optimization
				using __value_type       = typename __bit_iterator<_ForwardIt>::value_type;
				using __base_reference   = typename ::std::iterator_traits<__base_iterator>::reference;
				using __base_value_type  = typename ::std::iterator_traits<__base_iterator>::value_type;
				__value_type __first_val = *__first;
				if (!__first_val)
					{
						// we are currently at zero
						for (; __it_base != __last_base; ++__it_base)
							{
								__base_reference __ref_base = *__it_base;
								if (__ref_base == static_cast<__base_value_type>(0))
									{
										continue;
									}
								::std::size_t __first_lsb_bit = __bit_firstr_one(__ref_base) - 1;
								const int __all_set_bits      = __bit_popcount(__ref_base);
								const int __expected_set_bits =
								     static_cast<int>(__binary_digits_v<__base_value_type> - __first_lsb_bit);
								if (__expected_set_bits == __all_set_bits)
									{
										// still sorted, go to next section
										++__it_base;
										break;
									}
								__iterator __it_tail(__it_base, __first_lsb_bit);
								for (; __first_lsb_bit < __binary_digits_v<__base_value_type>;
								     ++__first_lsb_bit, (void)++__it_tail)
									{
										bool __tail_bit_val = *__it_tail;
										if (!__tail_bit_val)
											{
												// found the last sorted position
												return __it_tail;
											}
									}
							}
					}

				// we encountered our first 1
				// and it was still sorted
				// now we count all the trues
				// until we get a false
				while (__it_base != __last_base)
					{
						__base_reference __ref_base = *__it_base;
						const int __first_zero      = __bit_firstr_zero(__ref_base);
						if (__first_zero != 0)
							{
								// we found the anamoly
								return __iterator(__it_base, __first_zero - 1);
							}
						++__it_base;
					}
			}
		if (__last_position == 0)
			{
				return __last;
			}
		if (__it == __last)
			{
				return __it;
			}
		if (__bit_is_sorted_until_single_bit_position<true>(__first, __it, __last))
			{
				return __it;
			}
		return __last;
	}

	template<typename _ForwardIt>
	constexpr __bit_iterator<_ForwardIt>
	__bit_is_sorted_until(__bit_iterator<_ForwardIt> __first, __bit_iterator<_ForwardIt> __last)
	{
		using __iterator        = __bit_iterator<_ForwardIt>;
		using __base_iterator   = typename __iterator::iterator_type;
		using __base_value_type = typename ::std::iterator_traits<__base_iterator>::value_type;
		if constexpr (::std::is_unsigned_v<__base_value_type>)
			{
				return __bit_is_sorted_until_unsigned(::std::move(__first), ::std::move(__last));
			}
		else
			{
				using __value_type = typename __iterator::value_type;

				return ::std::is_sorted_until(
				     ::std::move(__first), ::std::move(__last), ::std::less<__value_type>());
			}
	}

	template<typename _ForwardIt>
	constexpr bool
	__bit_is_sorted(__bit_iterator<_ForwardIt> __first, __bit_iterator<_ForwardIt> __last)
	{
		return __bit_is_sorted_until(__first, __last) == __last;
	}

	template<bool _Value, typename _InputIt>
	constexpr typename ::std::iterator_traits<__bit_iterator<_InputIt>>::difference_type
	__bit_count_value(__bit_iterator<_InputIt> __first, __bit_iterator<_InputIt> __last)
	{
		using __iterator        = __bit_iterator<_InputIt>;
		using __base_iterator   = typename __iterator::iterator_type;
		using __base_value_type = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __difference_type = typename ::std::iterator_traits<__iterator>::difference_type;

		__difference_type __count = 0;
		if (__first == __last)
			{
				return __count;
			}
		while (__first.position() != 0)
			{
				if (__first == __last)
					{
						return __count;
					}
				if constexpr (_Value)
					{
						__count += static_cast<__difference_type>(static_cast<bool>(*__first));
					}
				else
					{
						__count += static_cast<__difference_type>(!static_cast<bool>(*__first));
					}
				++__first;
			}

		auto __last_position         = __last.position();
		__base_iterator __first_base = ::std::move(__first).base();
		__base_iterator __last_base  = ::std::move(__last).base();
		while (__first_base != __last_base)
			{
				if constexpr (_Value)
					{
						__count += __bit_popcount(*__first_base);
					}
				else
					{
						__count += (__binary_digits_v<__base_value_type> - __bit_popcount(*__first_base));
					}
				++__first_base;
			}
		if (__last_position == 0)
			{
				return __count;
			}
		__first = __iterator(::std::move(__first_base), 0);
		while (__first != __last)
			{
				if constexpr (_Value)
					{
						__count += static_cast<__difference_type>(static_cast<bool>(*__first));
					}
				else
					{
						__count += static_cast<__difference_type>(!static_cast<bool>(*__first));
					}
				++__first;
			}

		return __count;
	}

	template<typename _InputIt, typename _Type>
	constexpr typename ::std::iterator_traits<__bit_iterator<_InputIt>>::difference_type
	__bit_count(__bit_iterator<_InputIt> __first, __bit_iterator<_InputIt> __last, const _Type& __value)
	{
		if (static_cast<bool>(__value))
			{
				return __bit_count_value<true>(::std::move(__first), ::std::move(__last));
			}
		else
			{
				return __bit_count_value<false>(::std::move(__first), ::std::move(__last));
			}
	}

	template<typename _It, typename _OutputIt>
	constexpr __bit_iterator<_OutputIt>
	__bit_copy_same(__bit_iterator<_It> __first, __bit_iterator<_It> __last, __bit_iterator<_OutputIt> __out_first)
	{
		using __iterator          = __bit_iterator<_It>;
		using __out_iterator      = __bit_iterator<_OutputIt>;
		using __out_base_iterator = typename __out_iterator::iterator_type;

		// align to 0 boundary
		// we already checked __out_first's position
		// is equal to this one,
		// so this is okay to do for both
		for (; __first != __last && __first.position() != 0; ++__first, (void)++__out_first)
			{
				*__out_first = *__first;
			}

		auto __last_position = __last.position();
		__out_base_iterator __out_it_base =
		     ::std::copy(::std::move(__first).base(), __last.base(), ::std::move(__out_first).base());
		__out_iterator __out_it(::std::move(__out_it_base), 0);
		if (__last_position == 0)
			{
				return __out_it;
			}
		// copy the last bits
		__iterator __last_it(::std::move(__last).base(), 0);
		for (; __last_position > 0; --__last_position, (void)++__out_it, (void)__last_it)
			{
				*__out_it = *__last_it;
			}
		return __out_it;
	}

	template<typename _It, typename _OutputIt>
	constexpr _OutputIt
	__bit_copy(__bit_iterator<_It> __first, __bit_iterator<_It> __last, _OutputIt __out_first)
	{
		if (__first == __last)
			{
				return __out_first;
			}
		if constexpr (__is_bit_iterator_v<_OutputIt>)
			{
				using __base_iterator       = typename __bit_iterator<_It>::iterator_type;
				using __out_base_iterator   = typename _OutputIt::iterator_type;
				using __base_value_type     = typename ::std::iterator_traits<__base_iterator>::value_type;
				using __out_base_value_type = typename ::std::iterator_traits<__out_base_iterator>::value_type;
				if constexpr (::std::is_same_v<__base_value_type, __out_base_value_type> ||
				              ::std::is_assignable_v<__out_base_value_type, __base_value_type>)
					{
						if (__first.position() == __out_first.position())
							{
								return __bit_copy_same(
								     ::std::move(__first), ::std::move(__last), ::std::move(__out_first));
							}
					}
			}
		for (; __first != __last; ++__first, (void)++__out_first)
			{
				*__out_first = *__first;
			}
		return __out_first;
	}

	template<typename _It, typename _Size, typename _OutputIt>
	constexpr __bit_iterator<_OutputIt>
	__bit_copy_n_same(__bit_iterator<_It> __first, _Size __count, __bit_iterator<_OutputIt> __out_first)
	{
		using __iterator          = __bit_iterator<_It>;
		using __base_iterator     = typename __iterator::iterator_type;
		using __base_value_type   = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __out_iterator      = __bit_iterator<_OutputIt>;
		using __out_base_iterator = typename __out_iterator::iterator_type;

		// align to 0 boundary
		// we already checked __out_first's position
		// is equal to this one,
		// so this is okay to do for both
		for (; __count > 0 && __first.position() != 0; ++__first, (void)++__out_first, (void)--__count)
			{
				*__out_first = *__first;
			}

		_Size __n_base                    = __count / __binary_digits_v<__base_value_type>;
		__out_base_iterator __out_it_base = ::std::copy_n(__first.base(), __n_base, ::std::move(__out_first).base());
		__out_iterator __out_it(::std::move(__out_it_base), 0);
		_Size __last_pos = __count % __binary_digits_v<__base_value_type>;
		if (__last_pos == 0)
			{
				return __out_it;
			}

		// copy the last bits
		// FIXME: C++20 ranges have ranges::copy which returns
		// incremented in/out
		// FIXME: this is technically inefficient,
		// (incrementing the iterator if it's not a
		// random access iterator or better)
		// but then we'd have to re-implement copy_n
		// so we can get the last iterator properly
		// from the copy operation
		// FIXME: optimize std lib to have
		// internal __copy_n_ref op that takes
		// first by reference
		__base_iterator __last_it_base = ::std::next(::std::move(__first).base(), __n_base);
		__iterator __last_it(::std::move(__last_it_base), 0);
		for (; __last_pos > 0; --__last_pos, (void)++__out_it, (void)++__last_it)
			{
				*__out_it = *__last_it;
			}

		return __out_it;
	}

	template<typename _It, typename _Size, typename _OutputIt>
	constexpr _OutputIt
	__bit_copy_n(__bit_iterator<_It> __first, _Size __count, _OutputIt __out_first)
	{
		if (__count < static_cast<_Size>(1))
			{
				return __out_first;
			}
		if constexpr (__is_bit_iterator_v<_OutputIt>)
			{
				using __base_iterator       = typename __bit_iterator<_It>::iterator_type;
				using __out_base_iterator   = typename _OutputIt::iterator_type;
				using __base_value_type     = typename ::std::iterator_traits<__base_iterator>::value_type;
				using __out_base_value_type = typename ::std::iterator_traits<__out_base_iterator>::value_type;
				if constexpr (::std::is_same_v<__base_value_type, __out_base_value_type> ||
				              ::std::is_assignable_v<__out_base_value_type, __base_value_type>)
					{
						if (__first.position() == __out_first.position())
							{
								return __bit_copy_n_same(
								     ::std::move(__first), ::std::move(__count), ::std::move(__out_first));
							}
					}
			}
		for (; __count > 0; ++__first, (void)++__out_first, (void)--__count)
			{
				*__out_first = *__first;
			}
		return __out_first;
	}

	template<bool _Value, typename _ForwardIt>
	constexpr __bit_iterator<_ForwardIt>
	__bit_fill_value(__bit_iterator<_ForwardIt> __first, __bit_iterator<_ForwardIt> __last)
	{
		using __iterator                   = __bit_iterator<_ForwardIt>;
		using __base_iterator              = typename __iterator::iterator_type;
		using __base_value_type            = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __base_underlying_value_type = __any_to_underlying_t<__base_value_type>;

		for (; __first != __last && __first.position() != 0; ++__first)
			{
				if constexpr (_Value)
					{
						(*__first).set();
					}
				else
					{
						(*__first).reset();
					}
			}
		auto __last_position         = __last.position();
		__base_iterator __first_base = ::std::move(__first).base();
		__base_iterator __last_base  = ::std::move(__last).base();
		for (; __first_base != __last_base; ++__first_base)
			{
				if constexpr (_Value)
					{
						*__first_base = static_cast<__base_value_type>(
						     ::std::numeric_limits<__base_underlying_value_type>::max());
					}
				else
					{
						*__first_base = static_cast<__base_value_type>(0);
					}
			}
		__first = __iterator(::std::move(__first_base), 0);
		for (; __last_position > 0; --__last_position, (void)++__first)
			{
				if constexpr (_Value)
					{
						(*__first).set();
					}
				else
					{
						(*__first).reset();
					}
			}
		return __first;
	}

	template<typename _ForwardIt, typename _Type>
	constexpr __bit_iterator<_ForwardIt>
	__bit_fill(__bit_iterator<_ForwardIt> __first, __bit_iterator<_ForwardIt> __last, const _Type& __value)
	{
		if (static_cast<bool>(__value))
			{
				return __bit_fill_value<true>(::std::move(__first), ::std::move(__last));
			}
		else
			{
				return __bit_fill_value<false>(::std::move(__first), ::std::move(__last));
			}
	}

	template<bool _Value, typename _ForwardIt, typename _Size>
	constexpr __bit_iterator<_ForwardIt>
	__bit_fill_n_value(__bit_iterator<_ForwardIt> __first, _Size __count)
	{
		using __iterator                   = __bit_iterator<_ForwardIt>;
		using __difference_type            = typename __iterator::difference_type;
		using __base_iterator              = typename __iterator::iterator_type;
		using __base_value_type            = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __base_underlying_value_type = __any_to_underlying_t<__base_value_type>;

		for (; __count > 0 && __first.position() != 0; ++__first, (void)--__count)
			{
				if constexpr (_Value)
					{
						(*__first).set();
					}
				else
					{
						(*__first).reset();
					}
			}
		__base_iterator __first_base = ::std::move(__first).base();
		for (; __count >= static_cast<__difference_type>(__binary_digits_v<__base_value_type>);
		     ++__first_base, (void)(__count -= __binary_digits_v<__base_value_type>))
			{
				if constexpr (_Value)
					{
						*__first_base = static_cast<__base_value_type>(
						     ::std::numeric_limits<__base_underlying_value_type>::max());
					}
				else
					{
						*__first_base = static_cast<__base_value_type>(0);
					}
			}
		__first = __iterator(::std::move(__first_base), 0);
		for (; __count > 0; ++__first, (void)--__count)
			{
				if constexpr (_Value)
					{
						(*__first).set();
					}
				else
					{
						(*__first).reset();
					}
			}
		return __first;
	}

	template<typename _OutputIt, typename _Size, typename _Type>
	constexpr __bit_iterator<_OutputIt>
	__bit_fill_n(__bit_iterator<_OutputIt> __first, _Size __count, const _Type& __value)
	{
		if (static_cast<bool>(__value))
			{
				return __bit_fill_n_value<true>(::std::move(__first), ::std::move(__count));
			}
		else
			{
				return __bit_fill_n_value<false>(::std::move(__first), ::std::move(__count));
			}
	}

	template<typename _RandomAccessIt>
	constexpr void
	__bit_sort(__bit_iterator<_RandomAccessIt> __first, __bit_iterator<_RandomAccessIt> __last)
	{
		if (__first == __last)
			return;
		auto __maxbits = ::std::distance(__first, __last);
		auto __ones = __bit_count_value<true>(__first, ::std::move(__last));
		auto __zeroes = __maxbits - __ones;
		auto __mid_it = __bit_fill_n_value<false>(::std::move(__first), __zeroes);
		(void)__bit_fill_n_value<true>(::std::move(__mid_it), __ones);
	}
} // namespace ITSY_BITSY_SOURCE_NAMESPACE

#endif // ITSY_BITSY_DETAIL_ALGORITHM_HPP
