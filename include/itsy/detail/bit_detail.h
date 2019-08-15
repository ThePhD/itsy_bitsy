#pragma once

#ifndef ITSY_BITSY_DETAIL_BIT_DETAIL_H
#define ITSY_BITSY_DETAIL_BIT_DETAIL_H 1

#if defined(_MSC_VER) || (defined(__cplusplus) && __cplusplus >= 201703L)

#include <itsy/detail/type_traits.h>

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>
#include <cassert>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{
	// forward declarations
	class __bit_value;
	template<typename, typename>
	class __bit_reference;
	template<typename>
	class __bit_pointer;
	template<typename>
	class __bit_iterator;

	struct __dummy_tag
	{
	};

	template<typename _Type, typename = void>
	class __un_binary_digits
	: public ::std::integral_constant<::std::size_t, ::std::numeric_limits<_Type>::digits>
	{
		static_assert(::std::is_integral_v<_Type> || ::std::is_same_v<_Type, ::std::byte>,
		  "the type passed to binary_digits must be integral, an "
		  "enumeration type, or ::std::byte.");
	};

	template<typename _Type>
	class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_enum_v<_Type>>>
	: public ::std::integral_constant<::std::size_t,
	    ::std::numeric_limits<::std::underlying_type_t<_Type>>::digits>
	{
		static_assert(::std::is_integral_v<_Type> || ::std::is_same_v<_Type, ::std::byte> ||
		                ::std::is_enum_v<_Type>,
		  "the type passed to binary_digits must be integral, an "
		  "enumeration type, or ::std::byte.");
	};

	template<typename _Type>
	class __binary_digits
	: public __un_binary_digits<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename _Type>
	inline constexpr auto __binary_digits_v = __binary_digits<_Type>::value;

	template<typename _Type>
	inline constexpr auto __max_binary_index_v = __binary_digits_v<_Type> - 1;

	template<typename _Arg>
	decltype(auto)
	__unwrap_ref(_Arg&& __arg)
	{
		return static_cast<__unwrap_t<_Arg>>(::std::forward<_Arg>(__arg));
	}

	template<typename _Container>
	decltype(auto)
	__adl_begin(_Container&& __container)
	{
		using ::std::begin;
		return begin(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	decltype(auto)
	__adl_end(_Container&& __container)
	{
		using ::std::end;
		return end(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	decltype(auto)
	__adl_cbegin(_Container&& __container)
	{
		using ::std::cbegin;
		return cbegin(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	decltype(auto)
	__adl_cend(_Container&& __container)
	{
		using ::std::cend;
		return cend(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	decltype(auto)
	__adl_empty(_Container&& __container)
	{
		using ::std::empty;
		return empty(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	decltype(auto)
	__adl_size(_Container&& __container)
	{
		using ::std::size;
		return size(::std::forward<_Container>(__container));
	}

	template<typename _Left, typename _Right>
	void
	__adl_swap(_Left& __left, _Right& __right)
	{
		using ::std::swap;
		return swap(__left, __right);
	}

	template<typename _Target, typename _Actual>
	using __is_iterator_category_or_better = ::std::is_base_of<_Target, _Actual>;

	template<typename _Target, typename _Actual>
	inline constexpr bool __is_iterator_category_or_better_v =
	  __is_iterator_category_or_better<_Target, _Actual>::value;

	template<typename _LeftType, typename _RightType>
	inline constexpr bool __is_same_no_cvref_v =
	  ::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_LeftType>>,
	    ::std::remove_cv_t<::std::remove_reference_t<_RightType>>>;

	template<typename _Enumish, typename = void>
	struct __any_to_underlying
	{
		using type = _Enumish;
	};

	template<typename _Enumish>
	struct __any_to_underlying<_Enumish, ::std::enable_if_t<::std::is_enum_v<_Enumish>>>
	{
		using type = ::std::underlying_type_t<_Enumish>;
	};

	template<typename _Enumish>
	using __any_to_underlying_t = typename __any_to_underlying<_Enumish>::type;

	template<typename _Integralish>
	inline constexpr auto
	__to_underlying_if_enum(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish>)
			{
				return static_cast<::std::underlying_type_t<_Integralish>>(__val);
			}
		else
			{
				return __val;
			}
	}

	template<typename _Pos, typename _Mask>
	inline constexpr _Pos
	__mask_to_pos(_Mask __mask) noexcept
	{
		// if the mask is zero something has gone horribly wrong
		assert(__mask != static_cast<_Mask>(0));
		_Pos __pos = static_cast<_Pos>(0);
		while (__mask != static_cast<_Mask>(0))
			{
				++__pos;
				__mask >>= 1;
			}
		return static_cast<_Pos>(__pos);
	}

	template<typename _Mask, typename _Pos>
	inline constexpr _Mask
	__pos_to_mask(_Pos __pos) noexcept
	{
		// position never exceeds the capacity to show it
		assert(__pos < __binary_digits_v<_Pos>);
		return static_cast<_Mask>(static_cast<_Pos>(1) << __pos);
	}

	template<typename _Mask, typename _Pos>
	inline constexpr _Mask
	__pos_to_all_1_mask(_Pos __pos) noexcept
	{
		// position never exceeds the capacity to show it
		assert(__pos < __binary_digits_v<_Pos>);
		_Mask __mask(static_cast<_Mask>(1));
		while (__pos != 0)
			{
				__mask |= static_cast<_Mask>(static_cast<_Mask>(1) << __pos);
				--__pos;
			}
		return __mask;
	}

	template<typename _Word, bool _ShiftLeft, bool _PreserveLeft, typename _Ref, typename _Pos,
	  typename _Shift>
	inline constexpr void
	__shift_and_preserve(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		_Word __preservation      = __storage_ref;
		_Word __preservation_mask = __pos_to_all_1_mask<_Word>(__pos_position);
		if constexpr (_PreserveLeft)
			{
				__preservation_mask = ~__preservation_mask;
			}
		_Word __preservation_complement_mask = ~__preservation_mask;

		__preservation = __preservation & __preservation_mask;
		if constexpr (_ShiftLeft)
			{
				__storage_ref <<= __shift_by;
			}
		else
			{
				__storage_ref >>= __shift_by;
			}
		// restore bits from desired "untouched" section
		__storage_ref = (__storage_ref & __preservation_complement_mask) | (__preservation);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void
	__shift_left_preserve_right(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, true, false>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void
	__shift_right_preserve_right(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, false, false>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void
	__shift_left_preserve_left(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, true, true>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Ref, typename _Pos, typename _Shift>
	inline constexpr void
	__shift_right_preserve_left(_Ref& __storage_ref, _Pos __pos_position, _Shift __shift_by)
	{
		return __shift_and_preserve<_Word, false, true>(__storage_ref, __pos_position, __shift_by);
	}

	template<typename _Word, typename _Pos>
	inline constexpr _Word
	__merge_bits_at(_Word& __lsb, _Word& __msb, _Pos __bit_position)
	{
		_Word __lsb_mask = __pos_to_all_1_mask<_Word>(__bit_position);
		_Word __msb_mask = ~__lsb_mask;
		return (__lsb & __lsb_mask) | (__msb & __msb_mask);
	}

	template<typename _Word, typename _Ref, typename _Pos>
	inline constexpr _Word
	__replace_most_significant_bits_from(_Ref& __target, _Ref& __donor, _Pos __num_bits)
	{
		_Word __donor_give_mask  = __pos_to_all_1_mask<_Word>(__num_bits - 1);
		_Word __target_keep_mask = (~__donor_give_mask) >> __num_bits;
		_Pos __at                = __binary_digits_v<_Word> - __num_bits;
		return (__target & __target_keep_mask) | ((__donor & __donor_give_mask) << __at);
	}

	template<typename _Type>
	using __has_size_function_test = decltype(::std::declval<_Type&>().size());

	template<typename _Container>
	using __has_value_type_test = decltype(_Container::value_type);

	template<typename _Type>
	using __has_pair_iterator_insert_test =
	  decltype(::std::declval<_Type&>().insert(__adl_cbegin(::std::declval<_Type&>()),
	    __adl_cbegin(::std::declval<_Type&>()), __adl_cend(::std::declval<_Type&>())));

	template<typename _Container, typename = void>
	class __is_bit_container_test : public ::std::false_type
	{
	};

	template<typename _Container>
	class __is_bit_container_test<_Container,
	  ::std::enable_if_t<__is_detected_v<__has_value_type_test, _Container>>>
	: public ::std::integral_constant<bool,
	    ::std::is_same_v<typename _Container::value_type, __bit_value>>
	{
	};

	template<typename _Container>
	class __is_bit_container
	: ::std::integral_constant<bool, __is_bit_container_test<_Container>::value>
	{
	};

	template<typename _Container>
	inline constexpr bool __is_bit_container_v = __is_bit_container<_Container>::value;

	template<typename __Iter>
	using __invoke_iter_as_mutable_test = decltype(__iter_as_mutable(::std::declval<__Iter>()));

	template<typename __Iter>
	using __is_iter_as_mutable_invokable = __is_detected<__invoke_iter_as_mutable_test, __Iter>;

	template<typename __Iter>
	inline constexpr bool __is_iter_as_mutable_invokable_v =
	  __is_iter_as_mutable_invokable<__Iter>::value;

	template<typename _FromIt, typename _Container>
	constexpr auto
	__iter_as_mutable_from_begin(_FromIt& __from_it, _Container& __source) noexcept
	{
		using _ToIt = decltype(__adl_begin(__source));

		if constexpr (::std::is_same_v<::std::remove_cvref_t<_ToIt>, _FromIt>)
			{
				(void)__source;
				return _ToIt(__from_it);
			}
		else if constexpr (__is_iter_as_mutable_invokable_v<_FromIt&>)
			{
				(void)__source;
				return __iter_as_mutable(__from_it);
			}
		else if constexpr (__is_detected_v<__has_pair_iterator_insert_test, _Container>)
			{
				// http://eel.is/c++draft/container.requirements#sequence.reqmts-8
				// "The iterator returned from a.insert(p, i, j)
				// points to the copy of the first element inserted into a,
				// or p if i == j."
				// in other words, this is our cheat code to avoid
				// hitting the worst-case-scenario here
				return __source.insert(__from_it, __adl_cend(__source), __adl_cend(__source));
			}
		else if constexpr (::std::is_invocable_r_v<bool, ::std::not_equal_to<>, _ToIt, _FromIt> &&
		                   (::std::is_same_v<
		                      typename ::std::iterator_traits<_FromIt>::iterator_category,
		                      ::std::forward_iterator_tag> ||
		                     ::std::is_same_v<
		                       typename ::std::iterator_traits<_FromIt>::iterator_category,
		                       ::std::bidirectional_iterator_tag>))
			{
				// we can avoid 2N walk of iterators
				// by just moving up by them if they're
				// comparable to one another
				auto __begin_it = __adl_begin(__source);
				while (__begin_it != __from_it)
					{
						++__begin_it;
					}
				return __begin_it;
			}
		else
			{
				// either this is random access and O(1),
				// or this is some other weird iterator and it's O(2N)
				auto __begin_it = __adl_begin(__source);
				auto __it_dist  = ::std::distance(_FromIt(__begin_it), __from_it);
				std::advance(__begin_it, __it_dist);
				return __begin_it;
			}
	}

	template<typename _FromIt, typename _Container>
	constexpr auto
	__iter_as_mutable_from_end(_FromIt& __from_it, _Container& __source) noexcept
	{
		using _ToIt = decltype(__adl_end(__source));

		if constexpr (::std::is_same_v<::std::remove_cvref_t<_ToIt>, _FromIt>)
			{
				(void)__source;
				return _ToIt(__from_it);
			}
		else if constexpr (__is_iter_as_mutable_invokable_v<_FromIt&>)
			{
				(void)__source;
				return __iter_as_mutable(__from_it);
			}
		else if constexpr (__is_detected_v<__has_pair_iterator_insert_test, _Container>)
			{
				// http://eel.is/c++draft/container.requirements#sequence.reqmts-8
				// "The iterator returned from a.insert(p, i, j)
				// points to the copy of the first element inserted into a,
				// or p if i == j."
				// in other words, this is our cheat code to avoid
				// hitting the worst-case-scenario here
				return __source.insert(__from_it, __adl_cend(__source), __adl_cend(__source));
			}
		else if constexpr (::std::is_invocable_r_v<bool, ::std::not_equal_to<>, _ToIt, _FromIt> &&
		                   (::std::is_same_v<
		                     typename ::std::iterator_traits<_FromIt>::iterator_category,
		                     ::std::bidirectional_iterator_tag>))
			{
				// we can avoid 2N walk of iterators
				// by just moving up by them if they're
				// comparable to one another
				auto __begin_it = __adl_end(__source);
				while (__begin_it != __from_it)
					{
						--__begin_it;
					}
				return __begin_it;
			}
		else if constexpr (::std::is_invocable_r_v<bool, ::std::not_equal_to<>, _ToIt, _FromIt> &&
		                   (::std::is_same_v<
		                     typename ::std::iterator_traits<_FromIt>::iterator_category,
		                     ::std::forward_iterator_tag>))
			{
				// we can avoid 2N walk of iterators
				// by just moving up by them if they're
				// comparable to one another
				auto __begin_it = __adl_begin(__source);
				while (__begin_it != __from_it)
					{
						++__begin_it;
					}
				return __begin_it;
			}
		else
			{
				// either this is random access and O(1),
				// or this is some other weird iterator and it's O(2N)
				auto __end_it  = __adl_end(__source);
				auto __it_dist = ::std::distance(__from_it, _FromIt(__end_it));
				std::advance(__end_it, __it_dist);
				return __end_it;
			}
	}
} // namespace __BIT_STRUCTURES_NAMESPACE

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_BIT_ITERATOR_H
