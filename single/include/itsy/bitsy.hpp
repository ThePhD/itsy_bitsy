// =============================================================================
//
// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.
//
// =============================================================================

/* This is an automatically generated header file.
*  Generated from the itsy.bitsy repository at 2020-04-18 03:08:13.397124,
*  Version v0.8 (Revision 256e7bd).
*/

#ifndef ITSY_BITSY_SINGLE_INCLUDE_HPP
#define ITSY_BITSY_SINGLE_INCLUDE_HPP

// beginning of itsy/bitsy.hpp

// beginning of itsy/version.hpp

#include <cstddef>
#include <cstdint>

#if (defined(__has_include) && __has_include(<version>))
#include <version>
#endif

#define itsy_bitsy_bit_iterator 201908L
#define itsy_bitsy_bit_view 201908L
#define itsy_bitsy_dynamic_bit_set 201908L

#if defined(__clang__)

#define ITSY_BITSY_GCC 0
#define ITSY_BITSY_CLANG 1
#define ITSY_BITSY_VCXX 0

#elif defined(__GNUC__)

#define ITSY_BITSY_GCC 1
#define ITSY_BITSY_CLANG 0
#define ITSY_BITSY_VCXX 0

#else

#define ITSY_BITSY_GCC 0
#define ITSY_BITSY_CLANG 0
#define ITSY_BITSY_VCXX 1

#endif

#if defined(__GLIBCXX__)

#define ITSY_BITSY_LIBSTDCXX 1
#define ITSY_BITSY_LIBCXX 0
#define ITSY_BITSY_LIBVCXX 0

#elif defined(_LIBCPP_VERSION)

#define ITSY_BITSY_LIBSTDCXX 0
#define ITSY_BITSY_LIBCXX 1
#define ITSY_BITSY_LIBVCXX 0

#else

#define ITSY_BITSY_LIBSTDCXX 0
#define ITSY_BITSY_LIBCXX 0
#define ITSY_BITSY_LIBVCXX 1

#endif

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20201201UL
#ifndef ITSY_BITSY_DETAIL_NAMESPACE
#define ITSY_BITSY_DETAIL_NAMESPACE __gnu_cxx
#endif // detail namespace

#define ITSY_BITSY_SOURCE_LIBSTDCXX 1
#define ITSY_BITSY_SOURCE_LIBCXX 0
#define ITSY_BITSY_SOURCE_LIBVCXX 0

#elif defined(_LIBCPP_VERSION) && _LIBCPP_VERSION > 20000

#ifndef ITSY_BITSY_DETAIL_NAMESPACE
#define ITSY_BITSY_DETAIL_NAMESPACE __gnu_cxx
#endif // detail namespace

#define ITSY_BITSY_SOURCE_LIBSTDCXX 0
#define ITSY_BITSY_SOURCE_LIBCXX 1
#define ITSY_BITSY_SOURCE_LIBVCXX 0

#else

#ifndef ITSY_BITSY_DETAIL_NAMESPACE
#define ITSY_BITSY_DETAIL_NAMESPACE bitsy::__detail
#endif // detail namespace

#define ITSY_BITSY_SOURCE_LIBSTDCXX 0
#define ITSY_BITSY_SOURCE_LIBCXX 0
#define ITSY_BITSY_SOURCE_LIBVCXX 1

#endif

namespace bitsy
{
	// 4 bits per MAJOR MINOR PATCH
	inline constexpr std::uint64_t tag_version = 0x010000;
	// YYYYDD feature-macro like value
	inline constexpr std::uint64_t feature_version = 201908L;
} // namespace bitsy

// end of itsy/version.hpp

// beginning of itsy/forward.hpp

#ifndef ITSY_BITSY_FORWARD_HPP
#define ITSY_BITSY_FORWARD_HPP

namespace ITSY_BITSY_DETAIL_NAMESPACE
{

	template<typename _Type>
	class __bit_mask_type;

	template<typename _Type>
	using __bit_mask_type_t = typename __bit_mask_type<_Type>::type;

	class __bit_value;
	template<typename, typename>
	class __bit_reference;
	template<typename>
	class __bit_pointer;
	template<typename>
	class __bit_iterator;
	
	template<typename>
	class __word_bit_bounds;
	template<::std::size_t, ::std::size_t>
	class __bit_bounds;
	template<typename>
	class __dynamic_bit_bounds_for;
	class __dynamic_bit_bounds;

	template<typename _Range, typename>
	class __bit_view;

	template<typename _Type, ::std::size_t, typename, bool>
	class __packed_small_bit_vector;

} // namespace ITSY_BITSY_DETAIL_NAMESPACE

namespace bitsy
{

	template<typename T>
	using bit_mask_type = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_mask_type<T>;

	template<typename T>
	using bit_mask_type_t = typename bit_mask_type<T>::type;

	using bit_value = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_value;

	template<typename Ref, typename Mask = bit_mask_type_t<Ref>>
	using bit_reference = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_reference<Ref, Mask>;

	template<typename It>
	using bit_pointer = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_pointer<It>;

	template<typename It>
	using bit_iterator = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<It>;

	template<typename Range>
	class word_bit_bounds;

	template<typename Range>
	class  dynamic_bit_bounds_for;

	template<std::size_t first, std::size_t last>
	class bit_bounds;

	class dynamic_bit_bounds;

	template<typename, typename Bounds>
	class bit_view;

	template<typename, ::std::size_t, typename>
	class packed_small_bit_vector;

	template<typename, ::std::size_t, typename>
	class small_bit_vector;

	template<typename>
	class bit_sequence;

	template<typename, typename>
	class bit_vector;

} // namespace bitsy

#endif // ITSY_BITSY_FORWARD_HPP
// end of itsy/forward.hpp

// beginning of itsy/bit_iterator.hpp

// beginning of itsy/bit_operations.hpp

// beginning of itsy/detail/bit_operations.hpp

// beginning of itsy/detail/bit_detail.hpp

// beginning of itsy/detail/type_traits.hpp

#include <type_traits>
#include <functional>
#include <iterator>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{

#ifdef __cpp_lib_concepts
	using __contiguous_iterator_tag = ::std::contiguous_iterator_tag;
#else
	class __contiguous_iterator_tag : public ::std::random_access_iterator_tag {};
#endif

	template <typename _Type>
	using __remove_cvref_t = ::std::remove_cv_t<::std::remove_reference_t<_Type>>;

	template<typename _Type, template<typename...> class _Templ>
	struct __is_specialization_of_impl : std::false_type
	{
	};

	template<typename... _Args, template<typename...> class _Templ>
	struct __is_specialization_of_impl<_Templ<_Args...>, _Templ> : std::true_type
	{
	};

	template<typename _Type, template<typename...> class _Templ>
	using __is_specialization_of = __is_specialization_of_impl<::std::remove_cv_t<_Type>, _Templ>;

	template<typename _Type, template<typename...> class _Templ>
	inline constexpr bool __is_specialization_of_v = __is_specialization_of<_Type, _Templ>::value;

	template<typename>
	struct __dependent_false : std::false_type
	{
	};

	template<typename _Type>
	inline constexpr bool __dependent_false_v = __dependent_false<_Type>::value;

	template<typename _Type, typename _UType = ::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	struct __is_code_unit
	: ::std::integral_constant<bool, ::std::is_same_v<_UType, char> || ::std::is_same_v<_UType, wchar_t> ||
	                                      ::std::is_same_v<_UType, char16_t> || ::std::is_same_v<_UType, char32_t>
#if defined(__cpp_char8_t)
	                                      || ::std::is_same_v<_UType, char8_t>
#endif
	       >
	{
	};

	template<typename _Type>
	inline constexpr bool __is_code_unit_v = __is_code_unit<_Type>::value;

	struct __nonesuch
	{
		__nonesuch(__nonesuch const&) = delete;
		__nonesuch&
		operator=(__nonesuch const&) = delete;
		~__nonesuch()                = delete;
	};

	template<class Default, class AlwaysVoid, template<class...> class Op, class... Args>
	struct __detector
	{
		using value_t = std::false_type;
		using type    = Default;
	};

	template<class Default, template<class...> class Op, class... Args>
	struct __detector<Default, std::void_t<Op<Args...>>, Op, Args...>
	{
		using value_t = std::true_type;
		using type    = Op<Args...>;
	};

	template<template<class...> class Op, class... Args>
	using __is_detected = typename __detector<__nonesuch, void, Op, Args...>::value_t;

	template<template<class...> class Op, class... Args>
	using __detected_t = typename __detector<__nonesuch, void, Op, Args...>::type;

	template<class Default, template<class...> class Op, class... Args>
	using __detected_or = __detector<Default, void, Op, Args...>;

	template<template<typename...> class _Op, typename... _Args>
	constexpr bool __is_detected_v = __is_detected<_Op, _Args...>::value;

	template<typename _Type, typename = ::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	struct __unwrap
	{
		using type = _Type;
	};

	template<typename _Dummy, typename _Type>
	struct __unwrap<_Dummy, ::std::reference_wrapper<_Type>>
	{
		using type = ::std::add_lvalue_reference_t<_Type>;
	};

	template<typename _Type>
	using __unwrap_t = typename __unwrap<_Type>::type;

	template<typename _It>
	using __weakly_incrementable_test = decltype(++::std::declval<_It&>());

	template<typename _It>
	using __weakly_decrementable_test = decltype(--::std::declval<_It&>());

	template<typename _It>
	inline constexpr bool __weakly_incrementable_v = __is_detected_v<__weakly_incrementable_test, _It>;

	template<typename _It>
	inline constexpr bool __weakly_decrementable_v = __is_detected_v<__weakly_decrementable_test, _It>;

	template <typename _It>
	using __iterator_category_t =
		typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_category;

	template <typename _It, typename = void>
	struct __iterator_concept_or_fallback {
		using type = ::std::conditional_t<::std::is_pointer_v<__remove_cvref_t<_It>>, __contiguous_iterator_tag,
			__iterator_category_t<_It>>;
	};

	template <typename _It>
	struct __iterator_concept_or_fallback<_It,
		::std::void_t<typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_concept>> {
		using type = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_concept;
	};

	template <typename _It>
	using __iterator_concept_or_fallback_t =
		typename __iterator_concept_or_fallback<::std::remove_reference_t<_It>>::type;

	template <typename _It>
	using __iterator_concept_t = __iterator_concept_or_fallback_t<_It>;

	template <typename _Tag, typename _It>
	inline constexpr bool __is_iterator_concept_or_better_v = ::std::is_base_of_v<_Tag, __iterator_concept_t<_It>>;

} // namespace ITSY_BITSY_DETAIL_NAMESPACE

// end of itsy/detail/type_traits.hpp

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>
#include <memory>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	struct __dummy_tag
	{
	};

	template<typename Alloc, typename... Args>
	using __allocator_construct_invocable_test =
	     decltype(::std::declval<Alloc>().construct(::std::declval<Args>()...));

	template<typename _Type>
	union alignas(_Type) __uninit
	{
		constexpr __uninit() : _M_dummy()
		{
		}

		template<typename... _Args>
		constexpr __uninit(::std::in_place_t, _Args&&... __args) : _M_value(::std::forward<_Args>(__args)...)
		{
		}

		char _M_dummy;
		_Type _M_value;
	};

	template<typename _Type, typename = void>
	class __un_binary_digits
	{
	};

	template<typename _Type>
	class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_integral_v<_Type>>>
	: public ::std::integral_constant<::std::size_t, ::std::numeric_limits<_Type>::digits>
	{
	};

	template<typename _Type>
	class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_enum_v<_Type>>>
	: public ::std::integral_constant<::std::size_t, ::std::numeric_limits<::std::underlying_type_t<_Type>>::digits>
	{
	};

	template<typename _Type>
	class __binary_digits : public __un_binary_digits<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename _Type>
	inline constexpr auto __binary_digits_v = __binary_digits<_Type>::value;

	template<typename _Type>
	inline constexpr auto __max_binary_index_v = __binary_digits_v<_Type> - 1;

	template<typename _Type, typename _SizeType>
	constexpr _SizeType
	__bit_to_element_size(_SizeType __bit_size)
	{
		return static_cast<_SizeType>((__bit_size + __max_binary_index_v<_Type>) / __binary_digits_v<_Type>);
	}

	template<typename _Type, typename _SizeType>
	constexpr _SizeType
	__element_to_bit_size(_SizeType __element_size)
	{
		return static_cast<_SizeType>(__element_size * __binary_digits_v<_Type>);
	}

	template<typename, typename = void>
	class __un_bit_mask_type
	{
	};

	template<typename _Type>
	class __un_bit_mask_type<_Type, std::enable_if_t<std::is_integral_v<_Type> || std::is_enum_v<_Type>>>
	{
	public:
		using type = _Type;
	};

	template<typename _Type>
	class __bit_mask_type : public __un_bit_mask_type<::std::remove_cv_t<::std::remove_reference_t<_Type>>>
	{
	};

	template<typename _Type>
	using __bit_mask_type_t = typename __bit_mask_type<_Type>::type;

	template<typename _Arg>
	constexpr decltype(auto)
	__unwrap_ref(_Arg&& __arg)
	{
		return static_cast<__unwrap_t<_Arg>>(::std::forward<_Arg>(__arg));
	}

	template<typename _Container>
	constexpr decltype(auto)
	__adl_begin(_Container&& __container)
	{
		using ::std::begin;
		return begin(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto)
	__adl_end(_Container&& __container)
	{
		using ::std::end;
		return end(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto)
	__adl_cbegin(_Container&& __container)
	{
		using ::std::cbegin;
		return cbegin(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto)
	__adl_cend(_Container&& __container)
	{
		using ::std::cend;
		return cend(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto)
	__adl_empty(_Container&& __container)
	{
		using ::std::empty;
		return empty(::std::forward<_Container>(__container));
	}

	template<typename _Container>
	constexpr decltype(auto)
	__adl_size(_Container&& __container)
	{
		using ::std::size;
		return size(::std::forward<_Container>(__container));
	}

	template<typename _Left, typename _Right>
	constexpr void
	__adl_swap(_Left& __left, _Right& __right)
	{
		using ::std::swap;
		return swap(__left, __right);
	}

	template<typename _It>
	struct __is_bit_iterator : ::std::false_type
	{
	};

	template<typename _It>
	struct __is_bit_iterator<__bit_iterator<_It>> : ::std::true_type
	{
	};

	template<typename _It>
	inline constexpr bool __is_bit_iterator_v = __is_bit_iterator<_It>::value;

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

	template<typename _Integralish>
	inline constexpr auto
	__to_underlying_if_enum_or_char_t(_Integralish __val) noexcept
	{
		if constexpr (::std::is_same_v<_Integralish, char>)
			{
				using _UTy =
				     ::std::conditional_t<::std::is_signed_v<char>, ::std::int_least8_t, ::std::uint_least8_t>;
				return static_cast<_UTy>(__val);
			}
		else if constexpr (::std::is_same_v<_Integralish, wchar_t>)
			{
				if constexpr (::std::is_signed_v<wchar_t>)
					{
						if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least8_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>,
								     ::std::int_least8_t, ::std::uint_least8_t>;
								return static_cast<_UTy>(__val);
							}
						else if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least16_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>,
								     ::std::int_least16_t, ::std::uint_least16_t>;
								return static_cast<_UTy>(__val);
							}
						else if constexpr (sizeof(wchar_t) <= sizeof(::std::uint_least32_t))
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>,
								     ::std::int_least32_t, ::std::uint_least32_t>;
								return static_cast<_UTy>(__val);
							}
						else
							{
								using _UTy = ::std::conditional_t<::std::is_signed_v<wchar_t>,
								     ::std::int_least64_t, ::std::uint_least64_t>;
								return static_cast<_UTy>(__val);
							}
					}
				else
					{
						return static_cast<uint_least8_t>(__val);
					}
			}
#if defined(__cpp_char8_t)
		else if constexpr (::std::is_same_v<_Integralish, char8_t>)
			{
				return static_cast<unsigned char>(__val);
			}
#endif // char8_t
		else if constexpr (::std::is_same_v<_Integralish, char16_t>)
			{
				return static_cast<uint_least16_t>(__val);
			}
		else if constexpr (::std::is_same_v<_Integralish, char32_t>)
			{
				return static_cast<uint_least32_t>(__val);
			}
		else
			{
				return __to_underlying_if_enum(__val);
			}
	}

	template<typename _Type>
	using __has_size_function_test = decltype(::std::declval<_Type&>().size());

	template<typename _Left, typename _Right = _Left>
	using __equal_to_test = decltype(::std::declval<_Left&>() == ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __not_equal_to_test = decltype(::std::declval<_Left&>() != ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __less_than_test = decltype(::std::declval<_Left&>() < ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __less_equal_to_test = decltype(::std::declval<_Left&>() <= ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __greater_than_test = decltype(::std::declval<_Left&>() > ::std::declval<_Right&>());

	template<typename _Left, typename _Right = _Left>
	using __greater_equal_to_test = decltype(::std::declval<_Left&>() >= ::std::declval<_Right&>());

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
	class __is_bit_container_test<_Container, ::std::enable_if_t<__is_detected_v<__has_value_type_test, _Container>>>
	: public ::std::integral_constant<bool, ::std::is_same_v<typename _Container::value_type, __bit_value>>
	{
	};

	template<typename _Container>
	class __is_bit_container : ::std::integral_constant<bool, __is_bit_container_test<_Container>::value>
	{
	};

	template<typename _Container>
	inline constexpr bool __is_bit_container_v = __is_bit_container<_Container>::value;

	template<typename __Iter>
	using __invoke_iter_as_mutable_test = decltype(__iter_as_mutable(::std::declval<__Iter>()));

	template<typename __Iter>
	using __is_iter_as_mutable_invokable = __is_detected<__invoke_iter_as_mutable_test, __Iter>;

	template<typename __Iter>
	inline constexpr bool __is_iter_as_mutable_invokable_v = __is_iter_as_mutable_invokable<__Iter>::value;

	template<typename _FromIt, typename _Container>
	constexpr auto
	__iter_as_mutable_from_begin(_FromIt& __from_it, _Container& __source) noexcept
	{
		using _ToIt = decltype(__adl_begin(__source));

		if constexpr (::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_ToIt>>, _FromIt>)
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
		                   (::std::is_same_v<typename ::std::iterator_traits<_FromIt>::iterator_category,
		                         ::std::forward_iterator_tag> ||
		                        ::std::is_same_v<typename ::std::iterator_traits<_FromIt>::iterator_category,
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

		if constexpr (::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_ToIt>>, _FromIt>)
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
		                   (::std::is_same_v<typename ::std::iterator_traits<_FromIt>::iterator_category,
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
		                   (::std::is_same_v<typename ::std::iterator_traits<_FromIt>::iterator_category,
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

	template <typename _It>
	decltype(auto) __adl_to_address (const _It& __it) noexcept {
#if __cpp_to_address
		using ::std::to_address;
#endif
		return to_address(__it);
	}

	template <typename _It>
	using __adl_to_address_test = decltype(__adl_to_address(::std::declval<_It>()));

} // namespace ITSY_BITSY_DETAIL_NAMESPACE

// end of itsy/detail/bit_detail.hpp

#include <climits>
#if defined(__cpp_lib_bitops)
#include <bit>
#endif // C++20 Bit Operations

#if defined(_MSC_VER)
#include <intrin.h>
#else

#endif // VC++ vs. Others

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	template<typename _Integralish>
	constexpr int
	__bit_basic_countl_zero(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __not_is_set =
				     (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) ==
				     static_cast<_Integralish>(0);
				if (__not_is_set)
					{
						__num += 1;
					}
				else
					{
						break;
					}
			}
		return __num;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_countl_one(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __is_set = (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				                static_cast<_Integralish>(0);
				if (__is_set)
					{
						__num += 1;
					}
				else
					{
						break;
					}
			}
		return __num;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_countr_zero(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
			{
				bool __not_is_set =
				     (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) ==
				     static_cast<_Integralish>(0);
				if (__not_is_set)
					{
						__num += 1;
					}
				else
					{
						break;
					}
			}
		return __num;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_countr_one(_Integralish __val) noexcept
	{
		int __num = 0;
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
			{
				bool __is_set = (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				                static_cast<_Integralish>(0);
				if (__is_set)
					{
						__num += 1;
					}
				else
					{
						break;
					}
			}
		return __num;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_firstr_one(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
			{
				bool __is_set = (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				                static_cast<_Integralish>(0);
				if (__is_set)
					{
						return static_cast<int>(__bit_index + 1);
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_firstr_zero(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
			{
				bool __is_not_set =
				     (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) ==
				     static_cast<_Integralish>(0);
				if (__is_not_set)
					{
						return static_cast<int>(__bit_index + 1);
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_firstl_one(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __is_set = (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) !=
				                static_cast<_Integralish>(0);
				if (__is_set)
					{
						return static_cast<int>(__binary_digits_v<_Integralish> - __bit_index);
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_firstl_zero(_Integralish __val) noexcept
	{
		for (::std::size_t __bit_index = __binary_digits_v<_Integralish>; __bit_index-- > 0;)
			{
				bool __is_not_set =
				     (__val & static_cast<_Integralish>(static_cast<_Integralish>(1) << __bit_index)) ==
				     static_cast<_Integralish>(0);
				if (__is_not_set)
					{
						return static_cast<int>(__bit_index + 1);
					}
				else
					{
						break;
					}
			}
		return 0;
	}

	template<typename _Integralish>
	constexpr int
	__bit_basic_popcount(_Integralish __val) noexcept
	{
		if constexpr (__binary_digits_v<_Integralish> <= 128)
			{
				__val = __val - ((__val >> 1) & (_Integralish) ~(_Integralish)0 / 3);
				__val = (__val & (_Integralish) ~(_Integralish)0 / 15 * 3) +
				        ((__val >> 2) & (_Integralish) ~(_Integralish)0 / 15 * 3);
				__val = (__val + (__val >> 4)) & (_Integralish) ~(_Integralish)0 / 255 * 15;
				return (_Integralish)(__val * ((_Integralish) ~(_Integralish)0 / 255)) >>
				       (sizeof(_Integralish) - 1) * CHAR_BIT; // count
			}
		else
			{
				int __num = 0;
				for (::std::size_t __bit_index = 0; __bit_index < __binary_digits_v<_Integralish>; ++__bit_index)
					{
						bool __is_set = (__val & (static_cast<_Integralish>(1) << __bit_index)) !=
						                static_cast<_Integralish>(0);
						__num += static_cast<int>(__is_set);
					}
				return __num;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_countl_zero(_Integralish __val) noexcept
	{
#if defined(__cpp_lib_bitops)
		return ::std::countl_zero(__val);
#elif defined(_MSC_VER)
#if ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT != 0
		if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				unsigned long __index;
				auto __scanval = _BitScanReverse(&__index, __val);
				if (__scanval == 0)
					{
						return __binary_digits_v<_Integralish>;
					}
				return static_cast<int>(__index);
			}
#if INTPTR_MAX >= INT64_MAX
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				unsigned long __index;
				auto __scanval = _BitScanReverse64(&__index, __val);
				if (__scanval == 0)
					{
						return __binary_digits_v<_Integralish>;
					}
				return static_cast<int>(__index);
			}
#endif // 64-bit MSVC only
		else
			{
				return __bit_basic_countl_zero(__val);
			}
#else
		return __bit_basic_countl_zero(__val);
#endif // MSVC lacks constexpr
#else
		if (__val == 0)
			{
				return static_cast<int>(__binary_digits_v<_Integralish>);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_clz(__val) - (__binary_digits_v<unsigned int> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_clzl(__val) - (__binary_digits_v<unsigned long> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_clzll(__val) -
				       (__binary_digits_v<unsigned long long> - __binary_digits_v<_Integralish>);
			}
		else
			{
				return __bit_basic_countl_zero(__val);
			}
#endif
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_countl_one(_Integralish __val) noexcept
	{
		return __bit_unsigned_countl_zero(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_countr_zero(_Integralish __val) noexcept
	{
#if defined(__cpp_lib_bitops)
		return ::std::countr_zero(__val);
#elif defined(_MSC_VER)
#if ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT
		if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				unsigned long __index;
				auto __scanval = _BitScanForward(&__index, __val);
				if (__scanval == 0)
					{
						return __binary_digits_v<_Integralish>;
					}
				return static_cast<int>(__index);
			}
#if INTPTR_MAX >= INT64_MAX
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				// _BitScanX64 does not exist in 32-bit
				unsigned long __index;
				auto __scanval = _BitScanForward64(&__index, __val);
				if (__scanval == 0)
					{
						return __binary_digits_v<_Integralish>;
					}
				return static_cast<int>(__index);
			}
#endif // 64-bit MSVC only
		else
			{
				return  __bit_basic_countr_zero(__val);
			}
#else
		return __bit_basic_countr_zero(__val);
#endif // MSVC lacks constexpr
#else
		if (__val == 0)
			{
				return static_cast<int>(__binary_digits_v<_Integralish>);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_ctz(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_ctzl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_ctzll(__val);
			}
		else
			{
				return __bit_basic_countr_zero(__val);
			}
#endif
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_countr_one(_Integralish __val) noexcept
	{
		return __bit_unsigned_countr_zero(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_firstr_one(_Integralish __val) noexcept
	{
#if defined(_MSC_VER)
#if ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT
		if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				unsigned long __index;
				auto __scanval = _BitScanForward(&__index, __val);
				if (__scanval == 0)
					{
						return 0;
					}
				return static_cast<int>(__index + 1);
			}
#if INTPTR_MAX >= INT64_MAX
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				unsigned long __index;
				auto __scanval = _BitScanForward64(&__index, __val);
				if (__scanval == 0)
					{
						return 0;
					}
				return static_cast<int>(__index + 1);
			}
#endif // 64-bit MSVC only
		else
			{
				return __bit_basic_firstr_one(__val);
			}
#else
		return __bit_basic_firstr_one(__val);
#endif // MSVC lacks constexpr
#else
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_ffs(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_ffsl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_ffsll(__val);
			}
		else
			{
				return __bit_basic_firstr_one(__val);
			}
#endif
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_firstr_zero(_Integralish __val) noexcept
	{
		return __bit_unsigned_firstr_one(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_firstl_one(_Integralish __val) noexcept
	{
#if defined(_MSC_VER)
#if ITSY_BITSY_MSVC_HAS_ACHIEVED_CONSTEXPR_ENLIGHTENMENT
		if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				unsigned long __index;
				auto __scanval = _BitScanReverse(&__index, __val);
				if (__scanval == 0)
					{
						return 0;
					}
				return static_cast<int>(__index);
			}
#if INTPTR_MAX >= INT64_MAX
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				unsigned long __index;
				auto __scanval = _BitScanReverse64(&__index, __val);
				if (__scanval == 0)
					{
						return 0;
					}
				return static_cast<int>(__index);
			}
#endif // 64-bit MSVC only
		else
			{
				return __bit_basic_firstl_one(__val);
			}
#else
		return __bit_basic_firstl_one(__val);
#endif // MSVC lacks constexpr
#else
		if (__val == 0)
			{
				return static_cast<int>(0);
			}
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_clz(__val) + 1 -
				       (__binary_digits_v<unsigned int> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_clzl(__val) + 1 -
				       (__binary_digits_v<unsigned long> - __binary_digits_v<_Integralish>);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_clzll(__val) + 1 -
				       (__binary_digits_v<unsigned long long> - __binary_digits_v<_Integralish>);
			}
		else
			{
				return __bit_basic_firstl_one(__val);
			}
#endif
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_firstl_zero(_Integralish __val) noexcept
	{
		return __bit_unsigned_firstl_one(static_cast<_Integralish>(~__val));
	}

	template<typename _Integralish>
	constexpr int
	__bit_unsigned_popcount(_Integralish __val) noexcept
	{
#if defined(__cpp_liBb_bitops)
		return ::std::popcount(__val);
#elif defined(_MSC_VER)
#if defined(ITSY_BITSY_NONPORTABLE_MSVC_INTRINSICS)
		// WARNING
		// THESE INSTRUCTIONS ARE NOT PORTABLE
		// FIXME: REPLACE WITH SOMETHING MORE PORTABLE,
		// TEST CPUID AND FRIENDS FOR THESE FUNCTIONS,
		// ETC.
		if constexpr (__binary_digits_v<_Integralish> <= 16)
			{
				return static_cast<int>(__popcnt16(__val));
			}
		else if constexpr (__binary_digits_v<_Integralish> <= 32)
			{
				return static_cast<int>(__popcnt(__val));
			}
		else if constexpr (__binary_digits_v<_Integralish> <= 64)
			{
				return static_cast<int>(__popcnt64(__val));
			}
		else
			{
				return __bit_basic_popcount(__val);
			}
#else
		return __bit_basic_popcount(__val);
#endif
#else
		if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned int>)
			{
				return __builtin_popcountl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long>)
			{
				return __builtin_popcountl(__val);
			}
		else if constexpr (__binary_digits_v<_Integralish> <= __binary_digits_v<unsigned long long>)
			{
				return __builtin_popcountll(__val);
			}
		else
			{
				return __bit_basic_popcount(__val);
			}
#endif // Standard C++20 vs. VC++ vs. Others
	}

	template<typename _Integralish>
	constexpr int
	__bit_countl_zero(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_countl_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// destroy sign bit
						__val = static_cast<_Integralish>(
						     static_cast<_UIntegralish>(__val) &
						     static_cast<_UIntegralish>(::std::numeric_limits<_Integralish>::max()));
					}
				int __bit_countl_zero_val = __bit_unsigned_countl_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// remove +1 that comes from sign bit
						--__bit_countl_zero_val;
					}
				return __bit_countl_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_countl_one(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_countl_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// force set sign bit
						__val = static_cast<_Integralish>(
						     static_cast<_UIntegralish>(__val) |
						     (static_cast<_UIntegralish>(1) << __max_binary_index_v<_UIntegralish>));
					}
				int __bit_countl_one_val = __bit_unsigned_countl_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// remove +1 that comes from sign bit
						--__bit_countl_one_val;
					}
				return __bit_countl_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_countr_zero(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_countr_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish       = ::std::make_unsigned_t<_Integralish>;
				int __bit_countr_zero_val = __bit_unsigned_countr_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_countr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return __binary_digits_v<_Integralish>;
							}
					}
				return __bit_countr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_countr_one(_Integralish __val) noexcept
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_countr_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish       = ::std::make_unsigned_t<_Integralish>;
				int __bit_countr_zero_val = __bit_unsigned_countr_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_countr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return __binary_digits_v<_Integralish>;
							}
					}
				return __bit_countr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_firstr_one(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_firstr_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish      = ::std::make_unsigned_t<_Integralish>;
				int __bit_firstr_one_val = __bit_unsigned_firstr_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_firstr_one_val == __binary_digits_v<_UIntegralish>)
							{
								return 0;
							}
					}
				return __bit_firstr_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_firstr_zero(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_firstr_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish       = ::std::make_unsigned_t<_Integralish>;
				int __bit_firstr_zero_val = __bit_unsigned_firstr_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_firstr_zero_val == __binary_digits_v<_UIntegralish>)
							{
								return 0;
							}
					}
				return __bit_firstr_zero_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_firstl_one(_Integralish __val)
	{

		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_firstl_one(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// force clear sign bit
						__val = static_cast<_Integralish>(
						     static_cast<_UIntegralish>(__val) &
						     static_cast<_UIntegralish>(::std::numeric_limits<_Integralish>::max()));
					}
				int __bit_firstl_one_val = __bit_unsigned_firstl_one(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_firstl_one_val == 0)
							{
								return 0;
							}
						--__bit_firstl_one_val;
					}
				return __bit_firstl_one_val;
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_firstl_zero(_Integralish __val)
	{

		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_firstl_zero(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// force set sign bit
						__val = static_cast<_Integralish>(
						     static_cast<_UIntegralish>(__val) |
						     (static_cast<_UIntegralish>(1) << __max_binary_index_v<_UIntegralish>));
					}
				int __bit_firstl_zero_val = __bit_unsigned_firstl_zero(static_cast<_UIntegralish>(__val));
				if constexpr (std::is_signed_v<_Integralish>)
					{
						if (__bit_firstl_zero_val == 0)
							{
								return 0;
							}
						return __bit_firstl_zero_val - 1;
					}
				else
					{
						return __bit_firstl_zero_val;
					}
			}
	}

	template<typename _Integralish>
	constexpr int
	__bit_popcount(_Integralish __val)
	{
		if constexpr (::std::is_enum_v<_Integralish> || __is_code_unit_v<_Integralish>)
			{
				return __bit_popcount(__to_underlying_if_enum_or_char_t(__val));
			}
		else
			{
				using _UIntegralish = ::std::make_unsigned_t<_Integralish>;
				if constexpr (std::is_signed_v<_Integralish>)
					{
						// force clear sign bit
						__val = static_cast<_Integralish>(
						     static_cast<_UIntegralish>(__val) &
						     static_cast<_UIntegralish>(::std::numeric_limits<_Integralish>::max()));
					}
				int __bit_popcount_val = __bit_unsigned_popcount(static_cast<_UIntegralish>(__val));
				return __bit_popcount_val;
			}
	}

	template<typename _Pos, typename _Mask>
	inline constexpr _Pos
	__mask_to_pos(_Mask __mask) noexcept
	{
		if (__mask == static_cast<_Mask>(0))
			{
				return static_cast<_Pos>(0);
			}
		return static_cast<_Pos>(__bit_firstr_one(__mask) - 1);
	}

	template<typename _Mask, typename _Pos>
	inline constexpr _Mask
	__pos_to_mask(_Pos __pos) noexcept
	{
		return static_cast<_Mask>(static_cast<_Mask>(1) << __pos);
	}

	template<typename _Mask, typename _Pos>
	inline constexpr _Mask
	__pos_to_all_1_mask(_Pos __pos) noexcept
	{
		_Mask __mask(static_cast<_Mask>(2) << __pos);
		__mask = static_cast<_Mask>(__to_underlying_if_enum_or_char_t(__mask) - 1);
		return __mask;
	}

	template<typename _Word, bool _ShiftLeft, bool _PreserveLeft, typename _Ref, typename _Pos, typename _Shift>
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

} // namespace ITSY_BITSY_DETAIL_NAMESPACE

// end of itsy/detail/bit_operations.hpp

namespace bitsy
{
	template<typename T>
	using binary_digits = ITSY_BITSY_DETAIL_NAMESPACE::__binary_digits<T>;

	template<typename T>
	inline constexpr auto binary_digits_v = binary_digits<T>::value;

	template<typename T, typename Size>
	constexpr Size
	bit_to_element_size(Size bit_size)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_to_element_size<T>(bit_size);
	}

	template<typename T, typename Size>
	constexpr Size
	element_to_bit_size(Size element_size)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__element_to_bit_size<T>(element_size);
	}

	namespace detail
	{
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_and_preserve;
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_left_preserve_left;
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_left_preserve_right;
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_right_preserve_left;
		using ITSY_BITSY_DETAIL_NAMESPACE::__shift_right_preserve_right;

		template<typename _Type>
		using any_to_underlying_t = ITSY_BITSY_DETAIL_NAMESPACE::__any_to_underlying_t<_Type>;

		template<typename _Integralish>
		constexpr auto
		to_underlying_if_enum_or_char_t(_Integralish __val) noexcept
		{
			return ITSY_BITSY_DETAIL_NAMESPACE::__to_underlying_if_enum_or_char_t(__val);
		}
	} // namespace detail

	template<typename Integralish>
	constexpr int
	countl_zero(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_countl_zero(value);
	}

	template<typename Integralish>
	constexpr int
	countl_one(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_countl_one(value);
	}

	template<typename Integralish>
	constexpr int
	countr_zero(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_countr_zero(value);
	}

	template<typename Integralish>
	constexpr int
	countr_one(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_countr_one(value);
	}

	template<typename Integralish>
	constexpr int
	firstl_zero(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_firstl_zero(value);
	}

	template<typename Integralish>
	constexpr int
	firstl_one(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_firstl_one(value);
	}

	template<typename Integralish>
	constexpr int
	firstr_zero(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_firstr_zero(value);
	}

	template<typename Integralish>
	constexpr int
	firstr_one(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_firstr_one(value);
	}

	template<typename Integralish>
	constexpr int
	popcount(Integralish value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_popcount(value);
	}

	template<typename Position, typename Mask>
	constexpr Position
	mask_to_position(Mask mask)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__mask_to_pos<Position>(mask);
	}

	template<typename Mask, typename Position>
	constexpr Mask
	position_to_mask(Position position)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__pos_to_mask<Mask>(position);
	}

	template<typename Integralish, typename Position>
	constexpr Integralish
	merge_lsb_and_msb_at(Integralish lsbits, Integralish msbits, Position position)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__merge_bits_at(lsbits, msbits, position);
	}
} // namespace bitsy

// end of itsy/bit_operations.hpp

// beginning of itsy/detail/bit_iterator.hpp

#include <cstddef>
#include <type_traits>
#include <cassert>
#include <limits>
#include <climits>
#include <utility>
#include <iterator>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{

	class __bit_value
	{
	private:
		using __mask_type = ::std::size_t;

		bool __bval;

	public:
		// types
		using size_type = ::std::size_t;

		// constructors
		__bit_value() noexcept = default;

		constexpr __bit_value(const __bit_value&) noexcept = default;

		constexpr __bit_value(bool __val) noexcept : __bval(__val)
		{
		}

		template<typename _WordRef, typename _Mask>
		constexpr __bit_value(const __bit_reference<_WordRef, _Mask>& __ref) noexcept
		: __bval(static_cast<bool>(__ref))
		{
		}

		template<typename _WordRef, ::std::enable_if_t<!__is_same_no_cvref_v<_WordRef, __bit_value> &&
		                                               !__is_same_no_cvref_v<_WordRef, bool>>* = nullptr>
		explicit constexpr __bit_value(_WordRef&& __val) noexcept : __bit_value(::std::forward<_WordRef>(__val), 0)
		{
		}

		template<typename _WordRef>
		constexpr __bit_value(_WordRef&& __val, size_type __pos) noexcept
		: __bval((::std::forward<_WordRef>(__val) & __pos_to_mask<__mask_type>(__pos)) != 0)
		{
		}

		// assignment
		constexpr __bit_value&
		operator=(const __bit_value&) noexcept = default;

		template<typename _WordRef, typename _Mask>
		constexpr __bit_value&
		operator=(const __bit_reference<_WordRef, _Mask>& __ref) noexcept
		{
			__bval = static_cast<bool>(__ref);
			return *this;
		}

		template<typename _RightWordRef>
		constexpr __bit_value&
		assign(_RightWordRef __val) noexcept
		{
			assign(__val, 0);
			return *this;
		}

		template<typename _RightWordRef>
		constexpr __bit_value&
		assign(_RightWordRef __val, size_type __pos) noexcept
		{
			__bval = (__val & __pos_to_mask<__mask_type>(__pos)) != 0;
			return *this;
		}

		// compound assignment
		constexpr __bit_value&
		operator&=(__bit_value __right) noexcept
		{
			__bval &= __right.__bval;
			return *this;
		}

		constexpr __bit_value&
		operator|=(__bit_value __right) noexcept
		{
			__bval |= __right.__bval;
			return *this;
		}
		constexpr __bit_value&
		operator^=(__bit_value __right) noexcept
		{
			__bval ^= __right.__bval;
			return *this;
		}

		// observers
		constexpr bool
		value() const noexcept
		{
			return __bval;
		}

		explicit constexpr operator bool() const noexcept
		{
			return value();
		}

		// modifiers
		constexpr __bit_value&
		set(bool __val = true) noexcept
		{
			__bval = __val;
			return *this;
		}

		constexpr __bit_value&
		reset() noexcept
		{
			__bval = false;
			return *this;
		}

		constexpr __bit_value&
		flip() noexcept
		{
			__bval = !__bval;
			return *this;
		}

		// swap
		friend void
		swap(__bit_value& __left, __bit_value& __right) noexcept
		{
			__adl_swap(__left.__bval, __right.__bval);
		}

		friend constexpr bool
		operator==(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval == __right.__bval;
		}
		friend constexpr bool
		operator!=(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval != __right.__bval;
		}
		friend constexpr bool
		operator<(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval < __right.__bval;
		}
		friend constexpr bool
		operator<=(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval <= __right.__bval;
		}
		friend constexpr bool
		operator>(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval > __right.__bval;
		}
		friend constexpr bool
		operator>=(const __bit_value& __left, const __bit_value& __right) noexcept
		{
			return __left.__bval >= __right.__bval;
		}
	};

	inline constexpr __bit_value __bit0(0u);
	inline constexpr __bit_value __bit1(1u);

	template<typename _WordRef, typename _Mask = __bit_mask_type_t<_WordRef>>
	class __bit_reference
	{
	private:
		template<typename, typename>
		friend class __bit_reference;

		using __mask_type          = _Mask;
		using __cv_word_type       = ::std::remove_reference_t<__unwrap_t<_WordRef>>;
		using __word_type          = ::std::remove_cv_t<__cv_word_type>;
		using __integral_word_type = __any_to_underlying_t<__word_type>;

	public:
		using value_type = bool;
		using mask_type  = __mask_type;
		using size_type  = ::std::size_t;

		// constructors
		constexpr __bit_reference(bool __val) noexcept = delete;

		constexpr __bit_reference(const __bit_reference& __right) noexcept
		: _M_word(__right._M_word), _M_mask(__right._M_mask)
		{
		}

		constexpr explicit __bit_reference(_WordRef __val) noexcept : __bit_reference(__val, 0)
		{
		}

		constexpr __bit_reference(_WordRef __val, size_type __pos) noexcept
		: _M_word(__val), _M_mask(__pos_to_mask<mask_type>(__pos))
		{
		}

		// assignment
		constexpr __bit_reference&
		operator=(const __bit_reference& __right) noexcept
		{
			return this->set(__right.value());
		}

		template<typename _RightWordRef, typename _RightMask,
		     ::std::enable_if_t<!::std::is_same_v<_RightWordRef, _WordRef> || !::std::is_same_v<_RightMask, _Mask>>* =
		          nullptr>
		constexpr __bit_reference&
		operator=(const __bit_reference<_RightWordRef, _RightMask>& __right) noexcept
		{
			return this->set(__right.value());
		}

		constexpr __bit_reference&
		operator=(__bit_value __val) noexcept
		{
			return this->set(__val.value());
		}

		constexpr __bit_reference&
		operator=(bool __val) noexcept
		{
			return this->set(__val);
		}

		// compound assignment
		constexpr __bit_reference&
		operator&=(__bit_value __right) noexcept
		{
			return this->set(value() && __right.value());
		}

		constexpr __bit_reference&
		operator|=(__bit_value __right) noexcept
		{
			return this->set(value() || __right.value());
		}

		constexpr __bit_reference&
		operator^=(__bit_value __right) noexcept
		{
			return this->set(value() ^ __right.value());
		}

		// conversions
		constexpr operator bool() const noexcept
		{
			return this->value();
		}

		// observers
		constexpr size_type
		position() const noexcept
		{
			return __mask_to_pos<size_type>(this->_M_mask);
		}

		constexpr mask_type
		mask() const noexcept
		{
			return this->_M_mask;
		}

		constexpr bool
		value() const noexcept
		{
			return (this->_M_word & this->_M_mask) != static_cast<mask_type>(0);
		}

		constexpr ::std::add_pointer_t<__cv_word_type>
		address() const noexcept
		{
			return std::addressof(this->_M_word);
		}

		// modifiers
		constexpr __bit_reference&
		set(__bit_value __val) noexcept
		{
			return this->set(__val.value());
		}

		constexpr __bit_reference&
		set(bool __val) noexcept
		{
			// must cast to integral type to
			// use unary minus, otherwise math falls apart
			// with enums like std::byte!
			__word_type __bit_val = static_cast<__word_type>(-static_cast<::std::make_signed_t<__word_type>>(
			     __val ? static_cast<__integral_word_type>(1) : static_cast<__integral_word_type>(0)));
			this->_M_word ^= (__bit_val ^ this->_M_word) & this->_M_mask;
			return *this;
		}

		constexpr __bit_reference&
		set() noexcept
		{
			this->_M_word |= this->_M_mask;
			return *this;
		}

		constexpr __bit_reference&
		reset() noexcept
		{
			this->_M_word &= ~(this->_M_mask);
			return *this;
		}

		constexpr __bit_reference&
		flip() noexcept
		{
			this->_M_word ^= this->_M_mask;
			return *this;
		}

		// swap
		constexpr friend void
		swap(__bit_reference& __left, __bit_reference& __right) noexcept(
		     ::std::is_nothrow_swappable_v<__word_type>&& ::std::is_nothrow_swappable_v<__mask_type>)
		{
			if (__left.value() == __right.value())
				{
					return;
				}
			__left.flip();
			__right.flip();
		}

	private:
		_WordRef _M_word;
		mask_type _M_mask;
	};

	template<typename _Pointer>
	class __bit_pointer
	{
	private:
		template<typename>
		friend class __bit_pointer;

		using __base_iterator   = __unwrap_t<_Pointer>;
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __word_type       = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __base_reference  = typename ::std::iterator_traits<__base_iterator>::reference;

	public:
		// types
		using iterator_type     = _Pointer;
		using iterator_category = typename ::std::iterator_traits<iterator_type>::iterator_category;
		using iterator_concept  = __iterator_concept_t<iterator_type>;
		using value_type        = __bit_value;
		using reference         = __bit_reference<__base_reference, __bit_mask_type_t<__word_type>>;
		using pointer           = reference*;
		using size_type         = __size_type;
		using difference_type   = __difference_type;

		// constructors
		constexpr __bit_pointer() noexcept : _M_base_it(), _M_bit_ref_storage()
		{
		}

		constexpr __bit_pointer(const __bit_pointer& __right) noexcept
		: _M_base_it(__right._M_base_it), _M_bit_ref_storage(__right._M_base_it)
		{
		}

		constexpr __bit_pointer(__bit_pointer&& __right) noexcept
		: _M_base_it(::std::move(__right._M_base_it)), _M_bit_ref_storage(::std::move(__right._M_base_it))
		{
		}

		template<typename _RightPointer, ::std::enable_if_t<!std::is_same_v<_Pointer, _RightPointer>>* = nullptr>
		constexpr __bit_pointer(const __bit_pointer<_RightPointer>& __right) noexcept
		: _M_base_it(static_cast<_Pointer>(__right._M_base_it))
		, _M_bit_ref_storage(_M_create_storage(this->_M_is_alive(), this->_M_base_it, __right.position()))
		{
		}

		constexpr __bit_pointer(::std::nullptr_t) noexcept : __bit_pointer()
		{
		}

		explicit constexpr __bit_pointer(iterator_type __pointer) noexcept : __bit_pointer(::std::move(__pointer), 0)
		{
		}

		constexpr __bit_pointer(iterator_type __pointer, size_type __position) noexcept
		: _M_base_it(::std::move(__pointer))
		, _M_bit_ref_storage(_M_create_storage(this->_M_is_alive(), this->_M_base_it, __position))
		{
		}

		// destructor
		~__bit_pointer()
		{
			this->_M_destroy_if_present();
		}

		// assignment
		constexpr __bit_pointer&
		operator=(const __bit_pointer& __right) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = __right._M_base_it;
			this->_M_construct_if_present(__right.position());
			return *this;
		}

		constexpr __bit_pointer&
		operator=(__bit_pointer&& __right) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = ::std::move(__right._M_base_it);
			this->_M_construct_if_present(__right.position());
			return *this;
		}

		constexpr __bit_pointer& operator=(::std::nullptr_t) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = _Pointer{};
			return *this;
		}

		template<typename _RightPointer,
		     ::std::enable_if_t<!::std::is_same_v<_Pointer, _RightPointer> &&
		                        ::std::is_convertible_v<_RightPointer, _Pointer>>* = nullptr>
		__bit_pointer&
		operator=(const __bit_pointer<_RightPointer>& __right) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = static_cast<_Pointer>(__right._M_base_it);
			this->_M_construct_if_present(__right.position());
			return *this;
		}

		template<typename _RightPointer,
		     ::std::enable_if_t<!::std::is_same_v<_Pointer, _RightPointer> &&
		                        ::std::is_convertible_v<_RightPointer, _Pointer>>* = nullptr>
		constexpr __bit_pointer&
		operator=(__bit_pointer<_RightPointer>&& __right) noexcept
		{
			this->_M_destroy_if_present();
			this->_M_base_it = ::std::move(__right._M_base_it);
			this->_M_construct_if_present(__right.position());
			return *this;
		}

		// observers
		constexpr iterator_type&
		base() &
		{
			return this->_M_base_it;
		}

		constexpr const iterator_type&
		base() const&
		{
			return this->_M_base_it;
		}

		constexpr iterator_type&&
		base() &&
		{
			return ::std::move(this->_M_base_it);
		}

		explicit constexpr operator bool() const noexcept
		{
			return this->_M_is_alive();
		}

		constexpr reference
		operator*() const noexcept
		{
			return this->_M_bit_ref_storage._M_value;
		}

		constexpr pointer
		operator->() const noexcept
		{
			return std::addressof(const_cast<__bit_pointer*>(this)->_M_bit_ref_storage._M_value);
		}

		// swap
		friend constexpr void
		swap(__bit_pointer& __left, __bit_pointer& __right) noexcept(
		     ::std::is_nothrow_swappable_v<_Pointer>&& ::std::is_nothrow_swappable_v<size_type>)
		{
			const bool __left_alive  = __left._M_is_alive();
			const bool __right_alive = __right._M_is_alive();
			if (__left_alive && __right_alive)
				{
					__adl_swap(__left._M_base_it, __right._M_base_it);
					__adl_swap(__left._M_bit_ref_storage._M_value, __right._M_bit_ref_storage._M_value);
				}
			else if (__left_alive && !__right_alive)
				{
					__adl_swap(__left._M_base_it, __right._M_base_it);
					__right._M_destroy_dummy();
					__right._M_construct(__left.position());
					__left._M_destroy();
				}
			else if (!__left_alive && __right_alive)
				{
					__adl_swap(__left._M_base_it, __right._M_base_it);
					__left._M_destroy_dummy();
					__left._M_construct(__right.position());
					__right._M_destroy();
				}
			else
				{
					__adl_swap(__left._M_base_it, __right._M_base_it);
				}
		}

		// comparison
		template<typename __RightIt>
		friend constexpr bool
		operator==(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			return __left.base() == __right.base() && __left.position() == __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator!=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			return __left.base() != __right.base() || __left.position() != __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator<(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			if (__left.base() < __right.base())
				{
					return true;
				}
			if (__left.base() > __right.base())
				{
					return false;
				}
			return __left.position() < __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator<=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			if (__left.base() <= __right.base())
				{
					return true;
				}
			if (__left.base() > __right.base())
				{
					return false;
				}
			return __left.position() <= __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator>(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			if (__left.base() > __right.base())
				{
					return true;
				}
			if (__left.base() < __right.base())
				{
					return false;
				}
			return __left.position() > __left.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator>=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
		{
			if (__left.base() >= __right.base())
				{
					return true;
				}
			if (__left.base() < __right.base())
				{
					return false;
				}
			return __left.position() >= __left.position();
		}

	private:
		using _Uninit = __uninit<reference>;

		constexpr bool
		_M_is_alive() const
		{
			if constexpr (::std::is_pointer_v<iterator_type>)
				{
					return this->_M_base_it != nullptr;
				}
			else
				{
					if constexpr (__is_detected_v<__adl_to_address_test, iterator_type>)
						{
							return __adl_to_address(this->_M_base_it) != nullptr;
						}
					else
						{
							// Well, time to eat shit with MSVC, I guess!
							// FIXME: MSVC will die here for its iterator types
							// on debug modes.
							// nothing can do right now: to_address catches span,
							// but other types will still be shit
							return this->_M_base_it != iterator_type{};
						}
				}
		}

		constexpr void
		_M_destroy_if_present()
		{
			if (this->_M_is_alive())
				{
					this->_M_destroy();
				}
			else
				{
					this->_M_destroy_dummy();
				}
		}

		constexpr void
		_M_destroy()
		{
			this->_M_bit_ref_storage._M_value.~reference();
		}

		constexpr void
		_M_destroy_dummy()
		{
			// nothing to do
		}

		constexpr void
		_M_construct_if_present(size_type __position)
		{
			if (this->_M_is_alive())
				{
					this->_M_construct(__position);
				}
		}

		constexpr void
		_M_construct(size_type __position)
		{
			// FIXME: wait for new construct_at constexpr magic stuff
			new (std::addressof(this->_M_bit_ref_storage._M_value)) reference(*(this->_M_base_it), __position);
		}

		static constexpr _Uninit
		_M_create_storage(bool __is_alive, iterator_type& __base_it, size_type __position)
		{
			if (__is_alive)
				{
					return _Uninit(::std::in_place, *__unwrap_ref(__base_it), __position);
				}
			else
				{
					return _Uninit();
				}
		}

		iterator_type _M_base_it;
		_Uninit _M_bit_ref_storage;
	};

	template<typename _It>
	class __bit_iterator
	{
	private:
		template<typename>
		friend class __bit_iterator;

		using __base_iterator   = __unwrap_t<_It>;
		using __pointer         = typename ::std::iterator_traits<__base_iterator>::pointer;
		using __word_type       = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __mask_type       = __bit_mask_type_t<__word_type>;
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __word_ref_type   = typename ::std::iterator_traits<__base_iterator>::reference;

	public:
		using iterator_type     = __base_iterator;
		using iterator_category = typename ::std::iterator_traits<iterator_type>::iterator_category;
		using iterator_concept  = __iterator_concept_t<iterator_type>;
		using value_type        = __bit_value;
		using pointer           = __bit_pointer<iterator_type>;
		using reference         = __bit_reference<__word_ref_type, __mask_type>;
		using size_type         = __size_type;
		using difference_type   = __difference_type;

		// constructors
		constexpr __bit_iterator() noexcept                      = default;
		constexpr __bit_iterator(const __bit_iterator&) noexcept = default;
		constexpr __bit_iterator(__bit_iterator&&) noexcept      = default;
		explicit constexpr __bit_iterator(iterator_type __i) noexcept : __bit_iterator(::std::move(__i), 0)
		{
		}
		constexpr __bit_iterator(iterator_type __i, size_type __pos) noexcept
		: _M_base_it(::std::move(__i)), _M_pos(__pos)
		{
		}

		template<typename _RightIt, ::std::enable_if_t<!std::is_same_v<_It, _RightIt>>* = nullptr>
		constexpr __bit_iterator(__bit_iterator<_RightIt>&& __right) noexcept;
		template<typename _RightIt, ::std::enable_if_t<!std::is_same_v<_It, _RightIt>>* = nullptr>
		constexpr __bit_iterator(const __bit_iterator<_RightIt>& __right) noexcept;

		// assignment
		constexpr __bit_iterator&
		operator=(const __bit_iterator& __right) noexcept = default;
		constexpr __bit_iterator&
		operator=(__bit_iterator&& __right) noexcept = default;

		// observers
		constexpr reference
		operator*() const noexcept
		{
			return reference(*this->_M_base_it, this->_M_pos);
		}

		constexpr pointer
		operator->() const noexcept
		{
			return pointer(this->_M_base_it, this->_M_pos);
		}

		constexpr reference
		operator[](difference_type n) const
		{
			__bit_iterator __shifted = *this + n;
			return *__shifted;
		}

		constexpr iterator_type
		base() const noexcept
		{
			return this->_M_base_it;
		}

		constexpr size_type
		position() const noexcept
		{
			return this->_M_pos;
		}

		constexpr __mask_type
		mask() const noexcept
		{
			return __pos_to_mask<__mask_type>(_M_pos);
		}

		// arithmetic
		constexpr __bit_iterator&
		operator++()
		{
			++this->_M_pos;
			if (this->_M_pos == __binary_digits_v<__word_type>)
				{
					this->_M_pos = 0;
					++this->_M_base_it;
				}

			return *this;
		}

		constexpr __bit_iterator&
		operator--()
		{
			if (this->_M_pos == 0)
				{
					this->_M_pos = __max_binary_index_v<__word_type>;
					--this->_M_base_it;
				}
			else
				{
					--this->_M_pos;
				}

			return *this;
		}

		constexpr __bit_iterator
		operator++(int)
		{
			auto __saved = *this;
			++__saved;
			return __saved;
		}

		constexpr __bit_iterator
		operator--(int)
		{
			auto __saved = *this;
			--__saved;
			return __saved;
		}

		constexpr __bit_iterator
		operator+(difference_type __n) const
		{
			auto __saved = *this;
			__saved += __n;
			return __saved;
		}

		constexpr __bit_iterator
		operator-(difference_type __n) const
		{
			auto __saved = *this;
			__saved -= __n;
			return __saved;
		}

		constexpr __bit_iterator&
		operator+=(difference_type __n)
		{
			if (__n < 0)
				{
					return this->operator-=(-__n);
				}
			if (__n == 0)
				{
					return *this;
				}
			__size_type __bit_advancement = __n % __binary_digits_v<__word_type>;
			this->_M_pos += __bit_advancement;
			if (this->_M_pos > __binary_digits_v<__word_type>)
				{
					// put it back in the proper range
					this->_M_pos -= __binary_digits_v<__word_type>;
					// going forward by one extra since we
					// overflow binary digit count
					::std::advance(this->_M_base_it, (__n / __binary_digits_v<__word_type>)+1);
					return *this;
				}

			::std::advance(this->_M_base_it, __n / __binary_digits_v<__word_type>);
			return *this;
		}

		constexpr __bit_iterator&
		operator-=(difference_type __n)
		{
			if (__n < 0)
				{
					return this->operator+=(-__n);
				}
			if (__n == 0)
				{
					return *this;
				}
			__size_type __bit_advancement    = __n % __binary_digits_v<__word_type>;
			difference_type __it_advancement = __n / __binary_digits_v<__word_type>;
			if (__bit_advancement > this->_M_pos)
				{
					// put it back in the proper range
					this->_M_pos = __binary_digits_v<__word_type> - __bit_advancement;
					// going forward by one extra since we
					// overflow binary digit count
					++__it_advancement;
					::std::advance(this->_M_base_it, -__it_advancement);
					return *this;
				}

			this->_M_pos -= __bit_advancement;
			::std::advance(this->_M_base_it, -static_cast<difference_type>(__n / __binary_digits_v<__word_type>));
			return *this;
		}

		friend constexpr difference_type
		operator-(const __bit_iterator& __left, const __bit_iterator& __right)
		{
			return (::std::distance(__right._M_base_it, __left._M_base_it) * __binary_digits_v<__word_type>)+(
			     __left._M_pos - __right._M_pos);
		}

		// comparison
		template<typename __RightIt>
		friend constexpr bool
		operator==(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			return __left.base() == __right.base() && __left.position() == __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator!=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			return __left.base() != __right.base() || __left.position() != __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator<(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			if (__left.base() < __right.base())
				{
					return true;
				}
			if (__left.base() > __right.base())
				{
					return false;
				}
			return __left.position() < __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator<=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			if (__left.base() <= __right.base())
				{
					return true;
				}
			if (__left.base() > __right.base())
				{
					return false;
				}
			return __left.position() <= __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator>(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			if (__left.base() > __right.base())
				{
					return true;
				}
			if (__left.base() < __right.base())
				{
					return false;
				}
			return __left.position() > __right.position();
		}

		template<typename __RightIt>
		friend constexpr bool
		operator>=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
		{
			if (__left.base() >= __right.base())
				{
					return true;
				}
			if (__left.base() < __right.base())
				{
					return false;
				}
			return __left.position() >= __right.position();
		}

		// swap
		friend constexpr void
		swap(__bit_iterator& __left, __bit_iterator& __right) noexcept(
		     ::std::is_nothrow_swappable_v<iterator_type>&& ::std::is_nothrow_swappable_v<size_type>)
		{
			__adl_swap(__left._M_base_it, __right._M_base_it);
			__adl_swap(__left._M_pos, __right._M_pos);
		}

	private:
		iterator_type _M_base_it;
		size_type _M_pos;
	};

	template<typename _It>
	template<typename _RightIt, ::std::enable_if_t<!std::is_same_v<_It, _RightIt>>*>
	constexpr __bit_iterator<_It>::__bit_iterator(__bit_iterator<_RightIt>&& __right) noexcept
	: __bit_iterator(::std::move(__right).base(), ::std::move(__right).position())
	{
	}

	template<typename _It>
	template<typename _RightIt, ::std::enable_if_t<!std::is_same_v<_It, _RightIt>>*>
	constexpr __bit_iterator<_It>::__bit_iterator(const __bit_iterator<_RightIt>& __right) noexcept
	: __bit_iterator(__right.base(), __right.position())
	{
	}

} // namespace ITSY_BITSY_DETAIL_NAMESPACE

// end of itsy/detail/bit_iterator.hpp

namespace bitsy
{
	using bit_value = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_value;

	inline constexpr bit_value bit0{false};
	inline constexpr bit_value bit1{true};

	template<typename T>
	using bit_mask_type = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_mask_type<T>;

	template<typename T>
	using bit_mask_type_t = typename bit_mask_type<T>::type;

	template<typename Ref, typename Mask>
	using bit_reference = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_reference<Ref, Mask>;

	template<typename Pointer>
	using bit_pointer = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_pointer<Pointer>;

	template<typename It>
	using bit_iterator = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<It>;
} // namespace bitsy

// end of itsy/bit_iterator.hpp

// beginning of itsy/algorithm.hpp

// beginning of itsy/detail/algorithm.hpp

#include <algorithm>
#include <iterator>
#include <utility>

namespace ITSY_BITSY_DETAIL_NAMESPACE
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
} // namespace ITSY_BITSY_DETAIL_NAMESPACE

// end of itsy/detail/algorithm.hpp

namespace bitsy
{
	template<typename _It, typename _Type>
	constexpr bit_iterator<_It>
	bit_find(bit_iterator<_It> __first, bit_iterator<_It> __last, const _Type& __val)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_find(
		     ::std::move(__first), ::std::move(__last), __val);
	}

	template<typename _InputIt, typename _ForwardIt>
	constexpr bit_iterator<_InputIt>
	bit_find_first_of(bit_iterator<_InputIt> __first, bit_iterator<_InputIt> __last,
	     _ForwardIt __search_first, _ForwardIt __search_last)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_find_first_of(::std::move(__first),
		     ::std::move(__last), ::std::move(__search_first), ::std::move(__search_last));
	}

	template<typename _It0, typename _It1>
	constexpr bool
	bit_equal(bit_iterator<_It0> __first0, bit_iterator<_It0> __last0, bit_iterator<_It1> __first1,
	     bit_iterator<_It1> __last1)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_equal(::std::move(__first0),
		     ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
	}

	template<typename _It0, typename _It1>
	constexpr bool
	bit_equal(bit_iterator<_It0> __first0, bit_iterator<_It0> __last0, bit_iterator<_It1> __first1)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_equal(
		     ::std::move(__first0), ::std::move(__last0), ::std::move(__first1));
	}

	template<typename _InputIt0, typename _InputIt1>
	constexpr bool
	bit_lexicographical_compare(bit_iterator<_InputIt0> __first0, bit_iterator<_InputIt0> __last0,
	     bit_iterator<_InputIt1> __first1, bit_iterator<_InputIt1> __last1)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_lexicographical_compare(::std::move(__first0),
		     ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
	}

	template<typename _ForwardIt>
	constexpr bit_iterator<_ForwardIt>
	bit_is_sorted_until(bit_iterator<_ForwardIt> __first, bit_iterator<_ForwardIt> __last)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_is_sorted_until(
		     ::std::move(__first), ::std::move(__last));
	}

	template<typename _ForwardIt>
	constexpr bool
	bit_is_sorted(bit_iterator<_ForwardIt> __first, bit_iterator<_ForwardIt> __last)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_is_sorted(
		     ::std::move(__first), ::std::move(__last));
	}

	template<typename _It, typename _Type>
	constexpr typename std::iterator_traits<bit_iterator<_It>>::difference_type
	bit_count(bit_iterator<_It> __first, bit_iterator<_It> __last, const _Type& __value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_count(
		     ::std::move(__first), ::std::move(__last), __value);
	}

	template<typename _It, typename _OutputIt>
	constexpr _OutputIt
	bit_copy(bit_iterator<_It> __first, bit_iterator<_It> __last, _OutputIt __out_first)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_copy(
		     ::std::move(__first), ::std::move(__last), ::std::move(__out_first));
	}

	template<typename _It, typename _Size, typename _OutputIt>
	constexpr _OutputIt
	bit_copy_n(bit_iterator<_It> __first, _Size __count, _OutputIt __out_first)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_copy_n(
		     ::std::move(__first), __count, ::std::move(__out_first));
	}

	template<typename _ForwardIt, typename _Type>
	constexpr bit_iterator<_ForwardIt>
	bit_fill(
	     bit_iterator<_ForwardIt> __first, bit_iterator<_ForwardIt> __last, const _Type& __value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_fill(
		     ::std::move(__first), ::std::move(__last), __value);
	}

	template<typename _OutputIt, typename _Size, typename _Type>
	constexpr bit_iterator<_OutputIt>
	bit_fill_n(bit_iterator<_OutputIt> __first, _Size __count, const _Type& __value)
	{
		return ITSY_BITSY_DETAIL_NAMESPACE::__bit_fill_n(
		     ::std::move(__first), ::std::move(__count), __value);
	}

	template<typename _RandomAccessIt>
	constexpr void
	bit_sort(bit_iterator<_RandomAccessIt> __first, bit_iterator<_RandomAccessIt> __last)
	{
		ITSY_BITSY_DETAIL_NAMESPACE::__bit_sort(::std::move(__first), ::std::move(__last));
	}
} // namespace bitsy

// end of itsy/algorithm.hpp

// beginning of itsy/algorithm.std.hpp

// beginning of itsy/detail/algorithm.std.hpp

namespace std
{
	template<typename _It, typename _Type>
	constexpr ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It>
	find(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It> __first,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It> __last, const _Type& __val)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_find(
		     ::std::move(__first), ::std::move(__last), __val);
	}

	template<typename _InputIt, typename _ForwardIt>
	constexpr ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_InputIt>
	find_first_of(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_InputIt> __first,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_InputIt> __last, _ForwardIt __search_first,
	     _ForwardIt __search_last)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_find_first_of(::std::move(__first),
		     ::std::move(__last), ::std::move(__search_first), ::std::move(__search_last));
	}

	template<typename _It0, typename _It1>
	constexpr bool
	equal(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It0> __first0,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It0> __last0,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It1> __first1,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It1> __last1)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_equal(::std::move(__first0),
		     ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
	}

	template<typename _It0, typename _It1>
	constexpr bool
	equal(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It0> __first0,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It0> __last0,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It1> __first1)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_equal(
		     ::std::move(__first0), ::std::move(__last0), ::std::move(__first1));
	}

	template<typename _InputIt0, typename _InputIt1>
	constexpr bool
	lexicographical_compare(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_InputIt0> __first0,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_InputIt0> __last0,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_InputIt1> __first1,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_InputIt1> __last1)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_lexicographical_compare(::std::move(__first0),
		     ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
	}

	template<typename _It, typename _Type>
	constexpr typename std::iterator_traits<
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It>>::difference_type
	count(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It> __first,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It> __last, const _Type& __value)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_count(
		     ::std::move(__first), ::std::move(__last), __value);
	}

	template<typename _ForwardIt>
	constexpr ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_ForwardIt>
	is_sorted_until(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_ForwardIt> __first,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_ForwardIt> __last)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_is_sorted_until(
		     ::std::move(__first), ::std::move(__last));
	}

	template<typename _ForwardIt>
	constexpr bool
	is_sorted(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_ForwardIt> __first,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_ForwardIt> __last)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_is_sorted(
		     ::std::move(__first), ::std::move(__last));
	}

	template<typename _It, typename _OutputIt>
	constexpr _OutputIt
	copy(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It> __first,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It> __last, _OutputIt __out_first)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_copy(
		     ::std::move(__first), ::std::move(__last), ::std::move(__out_first));
	}

	template<typename _It, typename _Size, typename _OutputIt>
	constexpr _OutputIt
	copy_n(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_It> __first, _Size __count,
	     _OutputIt __out_first)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_copy_n(
		     ::std::move(__first), __count, ::std::move(__out_first));
	}

	template<typename _ForwardIt, typename _Type>
	constexpr ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_ForwardIt>
	fill(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_ForwardIt> __first,
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_ForwardIt> __last, const _Type& __value)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_fill(
		     ::std::move(__first), ::std::move(__last), __value);
	}

	template<typename _OutputIt, typename _Size, typename _Type>
	constexpr ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_OutputIt>
	fill_n(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_OutputIt> __first, _Size __count,
	     const _Type& __value)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_fill_n(
		     ::std::move(__first), ::std::move(__count), __value);
	}

	template<typename _RandomAccessIt>
	constexpr void
	sort(::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_RandomAccessIt> __first, ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_iterator<_RandomAccessIt> __last)
	{
		return ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_sort(
		     ::std::move(__first), ::std::move(__last));
	}
} // namespace std

// end of itsy/detail/algorithm.std.hpp

// end of itsy/algorithm.std.hpp

// beginning of itsy/bit_view.hpp

// beginning of itsy/detail/bit_view.hpp

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <utility>
#include <algorithm>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	template<typename _Container>
	class __word_bit_bounds
	{
	private:
		using __container_type  = __unwrap_t<_Container>;
		using __base_iterator   = decltype(__adl_begin(::std::declval<__container_type>()));
		using __base_value_type = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;

	public:
		static constexpr __size_type
		begin_position(const __container_type&) noexcept
		{
			return 0;
		}

		static constexpr __size_type
		end_position(const __container_type& __container) noexcept
		{
			if constexpr (::std::is_array_v<__container_type>)
				{
					return static_cast<__size_type>(
					     __adl_size(__container) * __binary_digits_v<__base_value_type>);
				}
			else if constexpr (__is_detected_v<__has_size_function_test, const __container_type&>)
				{
					return static_cast<__size_type>(__container.size() * __binary_digits_v<__base_value_type>);
				}
			else
				{
					return static_cast<__size_type>(
					     ::std::distance(::std::cbegin(__container), ::std::cend(__container)) *
					     __binary_digits_v<__base_value_type>);
				}
		}
	};

	template<::std::size_t _BeginBit, ::std::size_t _EndBit>
	class __bit_bounds
	{
	public:
		template<typename _Container>
		static constexpr ::std::size_t
		begin_position(const _Container&) noexcept
		{
			return _BeginBit;
		}

		template<typename _Container>
		static constexpr ::std::size_t
		end_position(const _Container&) noexcept
		{
			return _EndBit;
		}
	};

	template<typename _Container>
	class __dynamic_bit_bounds_for
	{
	private:
		using __container_type  = __unwrap_t<_Container>;
		using __range_ref       = std::add_lvalue_reference_t<__container_type>;
		using __base_iterator   = decltype(::std::begin(::std::declval<__range_ref>()));
		using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __value_type      = typename ::std::iterator_traits<__base_iterator>::value_type;

	public:
		__size_type first;
		__size_type last;

		__dynamic_bit_bounds_for(const __range_ref __range) noexcept
		: first(0), last(__adl_size(__range) * __binary_digits_v<__value_type>)
		{
		}

		__dynamic_bit_bounds_for(__size_type __first, __size_type __last) noexcept : first(__first), last(__last)
		{
		}

		constexpr __size_type
		begin_position(const __container_type&) const noexcept
		{
			return first;
		}

		constexpr __size_type
		end_position(const __container_type&) const noexcept
		{
			return last;
		}
	};

	class __dynamic_bit_bounds
	{
	public:
		::std::size_t first;
		::std::size_t last;

		template<typename _Container>
		__dynamic_bit_bounds(const _Container& __container) noexcept : __dynamic_bit_bounds(0, __container)
		{
		}

		template<typename _Container, ::std::enable_if_t<!::std::is_arithmetic_v<_Container>>* = nullptr>
		__dynamic_bit_bounds(::std::size_t __first, const _Container& __container) noexcept
		: first(__first)
		, last(__first +
		       (__adl_size(__unwrap_ref(__container)) * __binary_digits_v<typename ::std::iterator_traits<decltype(
		                                                     __adl_begin(__unwrap_ref(__container)))>::value_type>))
		{
		}

		__dynamic_bit_bounds(::std::size_t __first, ::std::size_t __last) noexcept : first(__first), last(__last)
		{
		}

		template<typename _Container>
		constexpr ::std::size_t
		begin_position(const _Container&) const noexcept
		{
			return first;
		}

		template<typename container_type>
		constexpr ::std::size_t
		end_position(const container_type&) const noexcept
		{
			return last;
		}
	};

	template<typename>
	struct __is_word_bit_bounds : ::std::false_type
	{
	};

	template<typename container_type>
	struct __is_word_bit_bounds<__word_bit_bounds<container_type>> : ::std::true_type
	{
	};

	template<typename _Type>
	inline constexpr bool __is_word_bit_bounds_v = __is_word_bit_bounds<_Type>::value;

	template<typename _Type>
	struct __is_word_or_bit_bounds : __is_word_bit_bounds<_Type>
	{
	};

	template<::std::size_t __First, ::std::size_t __Last>
	struct __is_word_or_bit_bounds<__bit_bounds<__First, __Last>> : ::std::true_type
	{
	};

	template<typename _Type>
	inline constexpr bool __is_word_or_bit_bounds_v = __is_word_or_bit_bounds<_Type>::value;

	template<typename _Bounds, typename = void>
	class __bounds_storage : private _Bounds
	{
	public:
		constexpr __bounds_storage()                        = default;
		constexpr __bounds_storage(const __bounds_storage&) = default;
		constexpr __bounds_storage(__bounds_storage&&)      = default;
		template<typename _Arg, typename... _Args,
		     ::std::enable_if_t<!::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_Arg>>,
		          __bounds_storage>>* = nullptr>
		constexpr __bounds_storage(_Arg&& __arg, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<_Bounds, _Arg, _Args...>)
		: _Bounds(::std::forward<_Arg>(__arg), ::std::forward<_Args>(__args)...)
		{
		}

		constexpr __bounds_storage&
		operator=(const __bounds_storage&) = default;
		constexpr __bounds_storage&
		operator=(__bounds_storage&&) = default;
		template<typename _Arg,
		     ::std::enable_if_t<!::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_Arg>>,
		          __bounds_storage>>* = nullptr>
		constexpr __bounds_storage&
		operator=(_Arg&& __arg)
		{
			this->_Bounds::operator=(::std::forward<_Arg>(__arg));
			return *this;
		}

		constexpr _Bounds&
		value() &
		{
			return static_cast<_Bounds&>(*this);
		}

		constexpr const _Bounds&
		value() const&
		{
			return static_cast<const _Bounds&>(*this);
		}

		constexpr _Bounds&&
		value() &&
		{
			return static_cast<_Bounds&&>(*this);
		}
	};

	template<typename _Bounds>
	class __bounds_storage<_Bounds, ::std::enable_if_t<::std::is_final_v<_Bounds> || !::std::is_object_v<_Bounds>>>
	: private _Bounds
	{
	private:
		_Bounds _M_bounds;

	public:
		constexpr __bounds_storage()                        = default;
		constexpr __bounds_storage(const __bounds_storage&) = default;
		constexpr __bounds_storage(__bounds_storage&&)      = default;
		template<typename _Arg, typename... _Args,
		     ::std::enable_if_t<!::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_Arg>>,
		          __bounds_storage>>* = nullptr>
		constexpr __bounds_storage(_Arg&& __arg, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<_Bounds, _Arg, _Args...>)
		: _M_bounds(::std::forward<_Arg>(__arg), ::std::forward<_Args>(__args)...)
		{
		}

		constexpr __bounds_storage&
		operator=(const __bounds_storage&) = default;
		constexpr __bounds_storage&
		operator=(__bounds_storage&&) = default;
		template<typename _Arg,
		     ::std::enable_if_t<!::std::is_same_v<::std::remove_cv_t<::std::remove_reference_t<_Arg>>,
		          __bounds_storage>>* = nullptr>
		constexpr __bounds_storage&
		operator=(_Arg&& __arg)
		{
			this->_M_nounds = ::std::forward<_Arg>(__arg);
			return *this;
		}

		constexpr _Bounds&
		value() &
		{
			return this->_M_bounds;
		}

		constexpr const _Bounds&
		value() const&
		{
			return this->_M_bounds;
		}

		constexpr _Bounds&&
		value() &&
		{
			return ::std::move(this->_M_bounds);
		}
	};

	template<typename _Range, typename _Bounds = __word_bit_bounds<__unwrap_t<_Range>>>
	class __bit_view : __bounds_storage<_Bounds>
	{
	private:
		template<typename, typename>
		friend class __bit_view;
		template<typename>
		friend class __bit_sequence;

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator==(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator!=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator<(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator<=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator>(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
		friend constexpr bool
		operator>=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right);

		using __base_t                   = __detail::__bounds_storage<_Bounds>;
		using __range                    = __unwrap_t<_Range>;
		using __range_ref                = std::add_lvalue_reference_t<__range>;
		using __base_iterator            = decltype(__adl_begin(::std::declval<__range_ref>()));
		using __base_sentinel            = decltype(__adl_end(::std::declval<__range_ref>()));
		using __base_c_iterator          = decltype(__adl_cbegin(::std::declval<__range_ref>()));
		using __base_c_sentinel          = decltype(__adl_cend(::std::declval<__range_ref>()));
		using __base_pointer             = typename ::std::iterator_traits<__base_iterator>::pointer;
		using __base_reference           = typename ::std::iterator_traits<__base_iterator>::reference;
		using __base_c_pointer           = typename ::std::iterator_traits<__base_c_iterator>::pointer;
		using __base_c_reference         = typename ::std::iterator_traits<__base_c_iterator>::reference;
		using __iterator                 = __bit_iterator<__base_iterator>;
		using __sentinel                 = __bit_iterator<__base_sentinel>;
		using __c_iterator               = __bit_iterator<__base_c_iterator>;
		using __c_sentinel               = __bit_iterator<__base_c_sentinel>;
		using __base_value_type          = typename ::std::iterator_traits<__base_iterator>::value_type;
		using __integral_base_value_type = __any_to_underlying_t<__base_value_type>;
		using __reference                = __bit_reference<__base_reference, __bit_mask_type_t<__base_value_type>>;
		using __const_reference          = __bit_reference<__base_c_reference, __bit_mask_type_t<__base_value_type>>;
		using __base_iterator_category   = typename ::std::iterator_traits<__base_iterator>::iterator_category;
		using __base_c_iterator_category = typename ::std::iterator_traits<__base_c_iterator>::iterator_category;

	public:
		using difference_type   = typename ::std::iterator_traits<__base_iterator>::difference_type;
		using size_type         = ::std::make_unsigned_t<difference_type>;
		using value_type        = __bit_value;
		using reference         = __reference;
		using const_reference   = __const_reference;
		using pointer           = __bit_pointer<__base_pointer>;
		using const_pointer     = __bit_pointer<__base_c_pointer>;
		using iterator_category = typename ::std::iterator_traits<__base_iterator>::iterator_category;
		// FIXME: strengthen guarantees by checking for `iterator_concept`
		// on iterator_traits when ranges gets merged
		using iterator_concept = iterator_category;
		using iterator         = __iterator;
		using sentinel         = __sentinel;
		using const_iterator   = __c_iterator;
		using const_sentinel   = __c_sentinel;
		using container_type   = _Range;
		using bounds_type      = _Bounds;

		constexpr __bit_view() noexcept(::std::is_nothrow_default_constructible_v<
		     container_type>&& ::std::is_nothrow_default_constructible_v<bounds_type>)
		: __base_t(), _M_storage()
		{
		}

		template<typename _Arg, typename... _Args,
		     ::std::enable_if_t<!__is_same_no_cvref_v<__bit_view, _Arg> && !__is_same_no_cvref_v<bounds_type, _Arg>,
		          void*> = nullptr>
		constexpr __bit_view(_Arg&& __arg, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<container_type, _Arg,
		          _Args...>&& ::std::is_nothrow_default_constructible_v<bounds_type>)
		: __base_t(), _M_storage(::std::forward<_Arg>(__arg), ::std::forward<_Args>(__args)...)
		{
		}

		template<typename... _Args>
		constexpr __bit_view(bounds_type __extents, _Args&&... __args) noexcept(
		     ::std::is_nothrow_constructible_v<container_type,
		          _Args...>&& ::std::is_nothrow_move_constructible_v<bounds_type>)
		: __base_t(std::move(__extents)), _M_storage(::std::forward<_Args>(__args)...)
		{
		}

		constexpr __bit_view(const __bit_view& __right) = default;
		constexpr __bit_view(__bit_view&& __right)      = default;

		constexpr __bit_view&
		operator=(const __bit_view& __right) = default;
		constexpr __bit_view&
		operator=(__bit_view&& __right) = default;

		// modifiers
		constexpr reference operator[](difference_type __n) noexcept
		{
			auto __it = this->begin();
			__it += __n;
			return *__it;
		}

		constexpr const_reference operator[](difference_type __n) const noexcept
		{
			auto __it = this->cbegin();
			__it += __n;
			return *__it;
		}

		constexpr void
		set() noexcept
		{
			set(0, this->size());
		}

		// prevent integer promotion
		// from giving users the wrong idea
		constexpr void
		set(bool __value)
		{
			set(value_type(__value));
		}

		constexpr void
		set(value_type __value) noexcept
		{
			set(0, this->size(), __value);
		}

		constexpr void
		set(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.set();
		}

		constexpr void
		set(size_type __pos, bool __val) noexcept
		{
			set(__pos, value_type(__val));
		}

		constexpr void
		set(size_type __pos, value_type __val) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.set(__val);
		}

		constexpr void
		set(size_type __pos, size_type __len) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			__bit_fill_n(__it, __len, true);
		}

		constexpr void
		set(size_type __pos, size_type __len, bool __val) noexcept
		{
			this->set(__pos, __len, value_type(__val));
		}

		constexpr void
		set(size_type __pos, size_type __len, value_type __val) noexcept
		{
			if (__val)
				{
					this->set(__pos, __len);
				}
			else
				{
					this->reset(__pos, __len);
				}
		}

		constexpr void
		reset() noexcept
		{
			reset(0, this->size());
		}

		constexpr void
		reset(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.reset();
		}

		constexpr void
		reset(size_type __pos, size_type __len) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			__bit_fill_n(__it, __len, false);
		}

		constexpr void
		flip() noexcept
		{
			flip(0, this->size());
		}

		constexpr void
		flip(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.flip();
		}

		constexpr void
		flip(size_type __pos, size_type __len) noexcept
		{
			iterator __it = this->begin();
			::std::advance(__it, __pos);
			if constexpr (::std::is_unsigned_v<__base_value_type>)
				{
					// get to word boundary
					for (size_type __boundary = __len - (__len % (__binary_digits_v<__base_value_type>));
					     __boundary < __len; ++__it, (void)--__len)
						{
							auto ref = *__it;
							ref.flip();
						}
					// process words
					__base_iterator __it_base = ::std::move(__it).base();
					for (; __len > __binary_digits_v<__base_value_type>;
					     __len -= __binary_digits_v<__base_value_type>)
						{
							__base_reference __ref_base = *__it_base;
							__ref_base                  = ~__ref_base;
							++__it_base;
						}
					__it = iterator(::std::move(__it_base), 0);
				}
			// process individual bits
			for (; __len-- > 0; ++__it)
				{
					reference __ref = *__it;
					__ref.flip();
				}
		}

		constexpr iterator
		begin() noexcept
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return iterator(this->_M_storage_begin(), 0);
				}
			else
				{
					auto __bit_distance = this->_M_bounds_unwrapped().begin_position(this->_M_storage_unwrapped());
					auto __first        = iterator(this->_M_storage_begin());
					__first += __bit_distance;
					return __first;
				}
		}

		constexpr sentinel
		end() noexcept
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return const_sentinel(this->_M_storage_end(), 0);
				}
			else
				{
					auto __bit_distance = this->_M_bounds_unwrapped().end_position(this->_M_storage_unwrapped());
					auto __last         = const_iterator(this->_M_storage_begin());
					::std::advance(__last, __bit_distance);
					return __last;
				}
		}

		constexpr const_iterator
		begin() const noexcept
		{
			return this->cbegin();
		}

		constexpr const_sentinel
		end() const noexcept
		{
			return this->cend();
		}

		constexpr const_iterator
		cbegin() const noexcept
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return const_iterator(this->_M_storage_cbegin(), 0);
				}
			else
				{
					auto __bit_distance = this->_M_bounds_unwrapped().begin_position(this->_M_storage_unwrapped());
					auto __first        = const_iterator(this->_M_storage_cbegin());
					__first += __bit_distance;
					return __first;
				}
		}

		constexpr const_sentinel
		cend() const noexcept
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return const_sentinel(this->_M_storage_cend(), 0);
				}
			else
				{
					auto __bit_distance = this->_M_bounds_unwrapped().end_position(this->_M_storage_unwrapped());
					auto __last         = const_iterator(this->_M_storage_cbegin());
					__last += __bit_distance;
					return __last;
				}
		}

		// observers
		bool
		empty() const
		{
			if constexpr (__detail::__is_word_bit_bounds_v<bounds_type>)
				{
					return __adl_empty(this->_M_storage_unwrapped());
				}
			else
				{
					return this->_M_bounds_unwrapped().begin_position(this->_M_storage_unwrapped()) ==
					       this->_M_bounds_unwrapped().end_position(this->_M_storage_unwrapped());
				}
		}

		constexpr const container_type&
		base() const& noexcept
		{
			return this->_M_storage_unwrapped();
		}

		constexpr container_type&
		     base() &
		     noexcept
		{
			return this->_M_storage_unwrapped();
		}

		constexpr container_type&&
		     base() &&
		     noexcept
		{
			return ::std::move(this->_M_storage_unwrapped());
		}

		constexpr bool
		test(difference_type __pos) const noexcept
		{
			return *::std::next(this->cbegin(), __pos);
		}

		constexpr size_type
		count(value_type __value) const noexcept
		{
			size_type __count = __bit_count(this->cbegin(), this->cend(), true);
			if (!__value)
				{
					return size() - __count;
				}
			return __count;
		}

		constexpr size_type
		popcount() const noexcept
		{
			return this->count(true);
		}

		constexpr size_type
		one_count() const noexcept
		{
			return this->count(true);
		}

		constexpr size_type
		zero_count() const noexcept
		{
			return this->count(false);
		}

		constexpr bool
		all() const noexcept
		{
			const_sentinel __last = this->cend();
			return __bit_find(this->cbegin(), __last, false) == __last;
		}

		constexpr bool
		any() const noexcept
		{
			const_sentinel __last = this->cend();
			return __bit_find(this->cbegin(), __last, true) != __last;
		}

		constexpr bool
		none() const noexcept
		{
			const_sentinel __last = this->cend();
			return __bit_find(this->cbegin(), __last, true) == __last;
		}

		constexpr size_type
		size() const noexcept
		{
			return this->_M_bit_distance();
		}

		constexpr const bounds_type&
		bounds() const noexcept
		{
			return this->_M_bounds.value();
		}

		constexpr bounds_type&
		bounds() noexcept
		{
			return this->_M_bounds.value();
		}

	private:
		container_type _M_storage;

		template<typename _Right>
		inline static constexpr bool __is_directly_comparable =
		     ::std::is_unsigned_v<__integral_base_value_type>&& ::std::is_unsigned_v<
		          typename _Right::__integral_base_value_type>&& ::std::is_same_v<container_type,
		          typename _Right::container_type>&& ::std::is_same_v<bounds_type, typename _Right::bounds_type>&&
		          __detail::__is_word_bit_bounds_v<bounds_type>&&
		               __detail::__is_word_bit_bounds_v<typename _Right::bounds_type>;

		constexpr size_type
		_M_bit_distance() const noexcept
		{
			return static_cast<size_type>(this->_M_bounds_unwrapped().end_position(this->_M_storage_unwrapped()) -
			                              this->_M_bounds_unwrapped().begin_position(this->_M_storage_unwrapped()));
		}

		constexpr __base_iterator
		_M_storage_begin() noexcept(noexcept(__adl_begin(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_begin(this->_M_storage_unwrapped());
		}

		constexpr __base_sentinel
		_M_storage_end() noexcept(noexcept(__adl_end(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_end(this->_M_storage_unwrapped());
		}

		constexpr __base_c_iterator
		_M_storage_begin() const noexcept(noexcept(__adl_begin(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_begin(this->_M_storage_unwrapped());
		}

		constexpr __base_c_sentinel
		_M_storage_end() const noexcept(noexcept(__adl_end(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_end(this->_M_storage_unwrapped());
		}

		constexpr __base_c_iterator
		_M_storage_cbegin() const noexcept(noexcept(__adl_cbegin(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_cbegin(this->_M_storage_unwrapped());
		}

		constexpr __base_c_sentinel
		_M_storage_cend() const noexcept(noexcept(__adl_cend(__unwrap_ref(::std::declval<container_type>()))))
		{
			return __adl_cend(this->_M_storage_unwrapped());
		}

		constexpr decltype(auto)
		_M_storage_unwrapped() const noexcept
		{
			return __unwrap_ref(this->_M_storage);
		}

		constexpr decltype(auto)
		_M_storage_unwrapped() noexcept
		{
			return __unwrap_ref(this->_M_storage);
		}

		constexpr decltype(auto)
		_M_bounds_unwrapped() const noexcept
		{
			return __unwrap_ref(static_cast<const __base_t&>(*this).value());
		}

		constexpr decltype(auto)
		_M_bounds_unwrapped() noexcept
		{
			return __unwrap_ref(static_cast<__base_t&>(*this).value());
		}
	};

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator==(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__equal_to_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage == __right._M_storage;
			}
		else
			{
				auto __left_size  = __left.size();
				auto __right_size = __right.size();
				if (__left_size != __right_size)
					{
						return false;
					}
				if constexpr (std::is_same_v<typename _Left::__base_value_type,
				                   typename _Right::__base_value_type> &&
				              __detail::__is_word_bit_bounds_v<typename _Left::bounds_type> &&
				              __detail::__is_word_bit_bounds_v<typename _Right::bounds_type>)
					{
						return ::std::equal(__left._M_storage_cbegin(), __left._M_storage_cend(),
						     __right._M_storage_cbegin(), __right._M_storage_cend());
					}
				else
					{
						return ::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
					}
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator!=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__not_equal_to_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage != __right._M_storage;
			}
		else
			{
				auto __left_size  = __left.size();
				auto __right_size = __right.size();
				if (__left_size == __right_size)
					{
						if constexpr (std::is_same_v<typename _Left::__base_value_type,
						                   typename _Right::__base_value_type> &&
						              __detail::__is_word_bit_bounds_v<typename _Left::bounds_type> &&
						              __detail::__is_word_bit_bounds_v<typename _Right::bounds_type>)
							{
								return !::std::equal(__left._M_storage_cbegin(), __left._M_storage_cend(),
								     __right._M_storage_cbegin(), __right._M_storage_cend());
							}
						else
							{
								return !::std::equal(
								     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
							}
					}
				return false;
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator<(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__less_than_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage < __right._M_storage;
			}
		else
			{
				return ::std::lexicographical_compare(
				     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator<=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__less_equal_to_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage <= __right._M_storage;
			}
		else
			{
				return !(__left > __right);
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator>(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__greater_than_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage > __right._M_storage;
			}
		else
			{
				return ::std::lexicographical_compare(
				     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), std::greater<bool>());
			}
	}

	template<typename _LeftR, typename _LeftEx, typename _RightR, typename _RightEx>
	constexpr bool
	operator>=(const __bit_view<_LeftR, _LeftEx>& __left, const __bit_view<_RightR, _RightEx>& __right)
	{
		using _Left         = __bit_view<_LeftR, _LeftEx>;
		using _Right        = __bit_view<_RightR, _RightEx>;
		using _LeftStorage  = typename _Left::container_type;
		using _RightStorage = typename _Right::container_type;
		if constexpr (_Left::template __is_directly_comparable<_Right> &&
		              __is_detected_v<__greater_equal_to_test, _LeftStorage, _RightStorage>)
			{
				return __left._M_storage >= __right._M_storage;
			}
		else
			{
				return !(__left < __right);
			}
	}

} // namespace ITSY_BITSY_DETAIL_NAMESPACE

// end of itsy/detail/bit_view.hpp

namespace bitsy
{
	template<typename Range>
	class word_bit_bounds : public ::ITSY_BITSY_DETAIL_NAMESPACE::__word_bit_bounds<Range> {
	private:
		using base_t = ::ITSY_BITSY_DETAIL_NAMESPACE::__word_bit_bounds<Range>; 
	public:
		using base_t::base_t;
	};

	template<typename Range>
	class dynamic_bit_bounds_for : public ::ITSY_BITSY_DETAIL_NAMESPACE::__dynamic_bit_bounds_for<Range> {
	private:
		using base_t = ::ITSY_BITSY_DETAIL_NAMESPACE::__dynamic_bit_bounds_for<Range>;
	public:
		using base_t::base_t;
	};

	template<std::size_t first, std::size_t last>
	class bit_bounds : public ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_bounds<first, last> {
	private:
		using base_t = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_bounds<first, last>;
	public:
		using base_t::base_t;		
	};

	class dynamic_bit_bounds : public ::ITSY_BITSY_DETAIL_NAMESPACE::__dynamic_bit_bounds {
	private:
		using base_t = ::ITSY_BITSY_DETAIL_NAMESPACE::__dynamic_bit_bounds;
	public:
		using base_t::base_t;
	};

	template<typename Range, typename Bounds = word_bit_bounds<Range>>
	class bit_view : public ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_view<Range, Bounds> {
	private:
		using base_t = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_view<Range, Bounds>;
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
	};

} // namespace bitsy

// end of itsy/bit_view.hpp

// beginning of itsy/bit_span.hpp

// beginning of itsy/detail/span.hpp

#if defined(__cpp_lib_span)

#include <span>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	using ::std::span;
}

#elif (defined(__has_include) && __has_include(<nonstd/span.hpp>)) || (defined(ITSY_BITSY_USE_NONSTD_SPAN) && ITSY_BITSY_USE_NONSTD_SPAN != 0)

#include <nonstd/span.hpp>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	using ::nonstd::span;
}

#elif defined(__has_include) && __has_include(<range/v3/view/span.hpp>)

#include <range/v3/view/span.hpp>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	using ::ranges::span;
}

#else

#error \
     "Cannot use this feature: a span of some sort is required! Please pull in the submodules or provide your own span on the include paths."

#endif // Span bullshit

// end of itsy/detail/span.hpp

namespace bitsy
{
	template<typename T, typename Bounds = word_bit_bounds<::ITSY_BITSY_DETAIL_NAMESPACE::span<T>>>
	using bit_span = bit_view<::ITSY_BITSY_DETAIL_NAMESPACE::span<T>, Bounds>;
} // namespace bitsy

// end of itsy/bit_span.hpp

// beginning of itsy/small_bit_vector.hpp

// beginning of itsy/detail/small_bit_vector.hpp

// beginning of itsy/detail/ebco.hpp

#include <utility>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	template<typename _Type, ::std::size_t = 0, typename = void>
	class __ebco
	{
	private:
		_Type _M_value;

	public:
		__ebco()              = default;
		__ebco(const __ebco&) = default;
		__ebco(__ebco&&)      = default;
		__ebco&
		operator=(const __ebco&) = default;
		__ebco&
		operator=(__ebco&&) = default;
		__ebco(const _Type& v) : _M_value(v){};
		__ebco(_Type&& v) : _M_value(::std::move(v)){};
		__ebco&
		operator=(const _Type& v)
		{
			this->_M_value = v;
			return *this;
		}
		__ebco&
		operator=(_Type&& v)
		{
			this->_M_value = ::std::move(v);
			return *this;
		};
		template<typename Arg, typename... Args,
		     typename =
		          ::std::enable_if_t<!::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, __ebco> &&
		                             !::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, _Type>>>
		__ebco(Arg&& arg, Args&&... args) : _M_value(::std::forward<Arg>(arg), ::std::forward<Args>(args)...)
		{
		}

		_Type&
		_M_get_value()
		{
			return this->_M_value;
		}

		_Type const&
		_M_get_value() const
		{
			return this->_M_value;
		}
	};

	template<typename _Type, ::std::size_t _Tag>
	class __ebco<_Type, _Tag, ::std::enable_if_t<::std::is_class_v<_Type> && !::std::is_final_v<_Type>>>
	: private _Type
	{
	public:
		__ebco()              = default;
		__ebco(const __ebco&) = default;
		__ebco(__ebco&&)      = default;
		__ebco(const _Type& v) : _Type(v){};
		__ebco(_Type&& v) : _Type(::std::move(v)){};
		template<typename Arg, typename... Args,
		     typename =
		          ::std::enable_if_t<!::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, __ebco> &&
		                             !::std::is_same_v<::std::remove_reference_t<::std::remove_cv_t<Arg>>, _Type>>>
		__ebco(Arg&& arg, Args&&... args) : _Type(::std::forward<Arg>(arg), ::std::forward<Args>(args)...)
		{
		}

		__ebco&
		operator=(const __ebco&) = default;
		__ebco&
		operator=(__ebco&&) = default;
		__ebco&
		operator=(const _Type& v)
		{
			static_cast<_Type&>(*this) = v;
			return *this;
		}
		__ebco&
		operator=(_Type&& v)
		{
			static_cast<_Type&>(*this) = ::std::move(v);
			return *this;
		}

		_Type&
		_M_get_value()
		{
			return static_cast<_Type&>(*this);
		}

		_Type const&
		_M_get_value() const
		{
			return static_cast<_Type const&>(*this);
		}
	};
} // namespace ITSY_BITSY_DETAIL_NAMESPACE

// end of itsy/detail/ebco.hpp

#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <climits>
#include <cassert>

#ifdef ITSY_BITSY_DETAIL_SBO_CONSTEXPR_CAPABLE
#define ITSY_BITSY_ALLOCATOR_CONSTEXPR constexpr
#define ITSY_BITSY_BLESSED_CONSTEXPR constexpr
#else
#define ITSY_BITSY_ALLOCATOR_CONSTEXPR
#define ITSY_BITSY_BLESSED_CONSTEXPR
#endif

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	template<typename _Type, typename _Allocator>
	inline constexpr ::std::size_t __compute_small_buffer_size_v =
	     (sizeof(_Type*) +
	          sizeof(typename ::std::allocator_traits<::std::remove_reference_t<__unwrap_t<_Allocator>>>::size_type)) /
	     sizeof(_Type);

	template<typename _Type, typename _Allocator = ::std::allocator<_Type>>
	inline constexpr ::std::size_t __default_small_buffer_size_v =
	     __compute_small_buffer_size_v<_Type, _Allocator> < 1 ? 1 : __compute_small_buffer_size_v<_Type, _Allocator>;

	template<typename _Type,
	     ::std::size_t _InlineWords = __default_small_buffer_size_v<_Type, ::std::allocator<_Type>>,
	     typename _Allocator = ::std::allocator<_Type>, bool _Packed = true>
	class __packed_small_bit_vector : private __ebco<_Allocator, 0>
	{
	private:
		template<typename, ::std::size_t, typename, bool>
		friend class __packed_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class __small_bit_vector;

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator==(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator!=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator<(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator<=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator>(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked,
		     typename _RightTy, ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
		friend constexpr bool
		operator>=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
		     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right);

		using __alloc_base           = __ebco<_Allocator, 0>;
		using __underlying           = __any_to_underlying_t<_Type>;
		using __unsigned_underlying  = ::std::make_unsigned_t<__underlying>;
		using __alloc                = ::std::remove_cv_t<::std::remove_reference_t<__unwrap_t<_Allocator>>>;
		using __alloc_traits         = ::std::allocator_traits<__alloc>;
		using __size_type            = typename __alloc_traits::size_type;
		using __base_value_type      = typename __alloc_traits::value_type;
		using __base_pointer         = typename __alloc_traits::pointer;
		using __base_const_pointer   = typename __alloc_traits::const_pointer;
		using __base_reference       = decltype(*::std::declval<__base_pointer>());
		using __base_const_reference = decltype(*::std::declval<__base_const_pointer>());
		using __difference_type      = typename __alloc_traits::difference_type;

		inline static constexpr __size_type _S_inline_innate_max_bit_count =
		     static_cast<__size_type>(_InlineWords * __binary_digits_v<__base_value_type>);
		inline static constexpr __size_type _S_bits_for_inline_size =
		     __binary_digits_v<__underlying> - __bit_firstl_one(_S_inline_innate_max_bit_count);
		inline static constexpr bool _S_is_hyper_sbo_capable =
		     // FIXME: size calculations in a few places are busted
		     // currently broken -- fix it up later after doing a full analysis
		     // of where size is being used mid-operation to compute things
		     // that it should be computed upfront and cached
		     // (e.g., with __old_size/__old_storage_size/
		     // __capacity/__storage_capacity etc.)
		     false && _Packed && (_InlineWords > 0) && ::std::is_integral_v<__underlying> &&
		     (_S_bits_for_inline_size <= __binary_digits_v<__underlying>);
		inline static constexpr __size_type _S_extra_storage_words =
		     (sizeof(__size_type) - sizeof(__base_value_type)) / sizeof(__base_value_type);
		inline static constexpr __size_type _S_inline_max_bit_count =
		     _S_inline_innate_max_bit_count +
		     (_S_is_hyper_sbo_capable
		               ? (_S_extra_storage_words + __binary_digits_v<__underlying> - _S_bits_for_inline_size)
		               : 0);
		inline static constexpr __size_type _S_end_storage_buffer_index =
		     _InlineWords + static_cast<__size_type>(_S_is_hyper_sbo_capable);

		template<typename _It>
		using _S_construct_iterator_type = void (*)(__alloc&, __base_pointer, _It&) noexcept(
#if ITSY_BITSY_CLANG != 0
		     false
#else
		     ::std::is_nothrow_constructible_v<__base_value_type, decltype(*::std::declval<_It&>())>
#endif
		);

	public:
		// member types
		using allocator                                   = _Allocator;
		using value_type                                  = __bit_value;
		using reference                                   = __bit_reference<__base_reference>;
		using const_reference                             = __bit_reference<__base_const_reference>;
		using pointer                                     = __bit_pointer<__base_pointer>;
		using const_pointer                               = __bit_pointer<__base_const_pointer>;
		using iterator                                    = __bit_iterator<__base_pointer>;
		using const_iterator                              = __bit_iterator<__base_const_pointer>;
		using sentinel                                    = __bit_iterator<__base_pointer>;
		using const_sentinel                              = __bit_iterator<__base_const_pointer>;
		using size_type                                   = __size_type;
		using difference_type                             = __difference_type;
		using iterator_category                           = typename iterator::iterator_category;
		using iterator_concept                            = typename iterator::iterator_concept;
		static constexpr inline size_type inline_capacity = _S_inline_max_bit_count;

		// constructors
		// constructors: default
		__packed_small_bit_vector() : __alloc_base()
		{
			_S_init_empty_storage_into(this->_M_buf_or_ptr);
		}

		// constructors: copy
		__packed_small_bit_vector(const __packed_small_bit_vector& __right)
		: __packed_small_bit_vector(__right._M_is_sbo(), __right)
		{
		}

		__packed_small_bit_vector(const __packed_small_bit_vector& __right, const allocator& __mem_alloc)
		: __packed_small_bit_vector(__right._M_is_sbo(), __right, __mem_alloc)
		{
		}

		// constructors: move
		__packed_small_bit_vector(__packed_small_bit_vector&& __right)
		: __packed_small_bit_vector(__right._M_is_sbo(), ::std::move(__right))
		{
		}

		__packed_small_bit_vector(__packed_small_bit_vector&& __right, const allocator& __mem_alloc)
		: __packed_small_bit_vector(__right._M_is_sbo(), ::std::move(__right), __mem_alloc)
		{
		}

		// constructors: allocator
		explicit __packed_small_bit_vector(const allocator& __mem_alloc) : __alloc_base(__mem_alloc)
		{
			_S_init_empty_storage_into(this->_M_buf_or_ptr);
		}

		// constructors: rangeable
		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> && !::std::is_same_v<_It, ::std::in_place_t> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list> &&
		                        !__is_same_no_cvref_v<_It, __packed_small_bit_vector>>* = nullptr>
		__packed_small_bit_vector(_It __it, _Sen __sen) : __alloc_base()
		{
			_S_init_storage_into(this->_M_buf_or_ptr, this->get_allocator(), ::std::move(__it), ::std::move(__sen));
		}

		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> && !::std::is_same_v<_It, ::std::in_place_t> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list> &&
		                        !__is_same_no_cvref_v<_It, __packed_small_bit_vector>>* = nullptr>
		__packed_small_bit_vector(_It __it, _Sen __sen, const allocator& __mem_alloc) : __alloc_base(__mem_alloc)
		{
			_S_init_storage_into(this->_M_buf_or_ptr, this->get_allocator(), ::std::move(__it), ::std::move(__sen));
		}

		// constructors: size, value
		explicit __packed_small_bit_vector(size_type __desired_count) : __alloc_base()
		{
			_S_init_storage_count_zero_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count);
		}

		explicit __packed_small_bit_vector(size_type __desired_count, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_storage_count_zero_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count);
		}

		__packed_small_bit_vector(size_type __desired_count, const value_type& __initial_value) : __alloc_base()
		{
			_S_init_storage_count_value_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count,
			     __initial_value
			          ? static_cast<__base_value_type>(::std::numeric_limits<__unsigned_underlying>::max())
			          : __base_value_type());
		}

		__packed_small_bit_vector(
		     size_type __desired_count, const value_type& __initial_value, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_storage_count_value_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count,
			     __initial_value
			          ? static_cast<__base_value_type>(::std::numeric_limits<__unsigned_underlying>::max())
			          : __base_value_type());
		}

		// constructors: initializer_list
		__packed_small_bit_vector(::std::initializer_list<value_type> __il)
		: __packed_small_bit_vector(__il.begin(), __il.end())
		{
		}

		__packed_small_bit_vector(::std::initializer_list<value_type> __il, const allocator& __mem_alloc)
		: __packed_small_bit_vector(__il.begin(), __il.end(), __mem_alloc)
		{
		}

		// constructors: in_place
		// constructors: (in_place) default
		__packed_small_bit_vector(std::in_place_t) : __alloc_base()
		{
			_S_init_empty_storage_into(this->_M_buf_or_ptr);
		}

		explicit __packed_small_bit_vector(std::in_place_t, const allocator& __mem_alloc) noexcept(
		     noexcept(allocator(__mem_alloc)))
		: __alloc_base(__mem_alloc)
		{
			_S_init_empty_storage_into(this->_M_buf_or_ptr);
		}

		// constructors: (in_place) rangeable
		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list>>* = nullptr>
		__packed_small_bit_vector(::std::in_place_t, _It __it, _Sen __sen) : __alloc_base()
		{
			_S_init_base_storage_into(
			     this->_M_buf_or_ptr, this->get_allocator(), ::std::move(__it), ::std::move(__sen));
		}

		template<typename _It, typename _Sen,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_It> &&
		                        !__is_specialization_of_v<_It, ::std::initializer_list>>* = nullptr>
		__packed_small_bit_vector(::std::in_place_t, _It __it, _Sen __sen, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_base_storage_into(
			     this->_M_buf_or_ptr, this->get_allocator(), ::std::move(__it), ::std::move(__sen));
		}

		// constructors: (in_place) size, value
		explicit __packed_small_bit_vector(::std::in_place_t, size_type __desired_count) : __alloc_base()
		{
			_S_init_base_storage_count_zero_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count);
		}

		explicit __packed_small_bit_vector(::std::in_place_t, size_type __desired_count, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_base_storage_count_zero_into(this->_M_buf_or_ptr, this->get_allocator(), __desired_count);
		}

		__packed_small_bit_vector(
		     ::std::in_place_t, size_type __desired_count, const __base_value_type& __initial_value)
		: __alloc_base()
		{
			_S_init_base_storage_count_value_into(
			     this->_M_buf_or_ptr, this->get_allocator(), __desired_count, __initial_value);
		}

		__packed_small_bit_vector(::std::in_place_t, size_type __desired_count,
		     const __base_value_type& __initial_value, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		{
			_S_init_base_storage_count_value_into(
			     this->_M_buf_or_ptr, this->get_allocator(), __desired_count, __initial_value);
		}

		// constructors: (in_place) initializer_list
		__packed_small_bit_vector(::std::in_place_t, ::std::initializer_list<__base_value_type> __il)
		: __packed_small_bit_vector(::std::in_place, __il.begin(), __il.end())
		{
		}

		__packed_small_bit_vector(
		     ::std::in_place_t, ::std::initializer_list<__base_value_type> __il, const allocator& __mem_alloc)
		: __packed_small_bit_vector(::std::in_place, __il.begin(), __il.end(), __mem_alloc)
		{
		}

		// destructor
		~__packed_small_bit_vector() noexcept
		{
			this->_M_destroy<true, true>();
		}

		// assignment
		__packed_small_bit_vector&
		operator=(__packed_small_bit_vector&& __right) noexcept
		{
			if constexpr (__alloc_traits::propagate_on_container_move_assignment::value)
				{
					this->_M_steal<true>(::std::move(__right));
				}
			else
				{
					// okay, we're not allowed to propagate,
					// but we still have to transfer??? Oh boy...
					if constexpr (__alloc_traits::is_always_equal::value)
						{
							// equal: cheat and steal
							this->_M_steal<false>(::std::move(__right));
						}
					else
						{
							// okay... so they're not ALWAYS equal
							if (this->get_allocator() == __right.get_allocator())
								{
									// equal: cheat and steal
									this->_M_steal<false>(::std::move(__right));
								}
							else
								{
									// alright, so it's not POCMA, it's not always equal,
									// and the allocators are not equivalent.
									// Don't transfer the allocators, basically do
									// dummy assign...
									// so we have to literally transfer contents
									// one by one by one...
									// maybe we can move the contents?? Hopefully.
									this->_M_base_assign(
									     ::std::make_move_iterator(__right._M_storage_pointer()),
									     ::std::make_move_iterator(__right._M_storage_pointer_end()));
								}
						}
				}
			return *this;
		}

		__packed_small_bit_vector&
		operator=(const __packed_small_bit_vector& __right)
		{
			// do we have to take the allocator from the right?
			if constexpr (__alloc_traits::propagate_on_container_copy_assignment::value)
				{
					// are they not always equal...?
					if constexpr (!__alloc_traits::is_always_equal::value)
						{
							// ... are they actually not equal... ?!
							if (this->get_allocator() != __right.get_allocator())
								{
									// fek. Clear everything first because
									// we will be trucking over our allocator
									this->_M_destroy<false, true>();
								}
						}
					// propagate the right allocator...
					this->get_allocator() = __right.get_allocator();
				}
			// alright, now vomit out all the elements
			this->_M_base_assign(__right._M_storage_pointer(), __right._M_storage_pointer_end());
			return *this;
		}

		// observers
		reference
		front()
		{
			__base_pointer __first = this->_M_storage_pointer();
			return reference(*__first, this->_M_first_bit_index());
		}

		const_reference
		front() const
		{
			__base_const_pointer __first = this->_M_storage_pointer();
			return const_reference(*__first, this->_M_first_bit_index());
		}

		reference
		back()
		{
			iterator __last = this->end();
			--__last;
			return *__last;
		}

		const_reference
		back() const
		{
			const_iterator __last = this->end();
			--__last;
			return *__last;
		}

		constexpr size_type
		size() const
		{
			if (this->_M_is_sbo())
				{
					return _S_size_sbo(this->_M_buf_or_ptr);
				}
			else
				{
					return _S_size_heap(this->_M_buf_or_ptr);
				}
		}

		constexpr size_type
		capacity() const
		{
			if (this->_M_is_sbo())
				{
					return _S_capacity_sbo(this->_M_buf_or_ptr);
				}
			else
				{
					return _S_capacity_heap(this->_M_buf_or_ptr);
				}
		}

		constexpr bool
		empty() const
		{
			return this->size() == 0;
		}

		constexpr bool
		is_inline()
		{
			return this->_M_is_sbo();
		}

		constexpr allocator&
		get_allocator()
		{
			return __alloc_base::_M_get_value();
		}

		constexpr const allocator&
		get_allocator() const
		{
			return __alloc_base::_M_get_value();
		}

		// observers: iterators
		iterator
		begin()
		{
			return iterator(this->_M_storage_pointer(), this->_M_first_bit_index());
		}

		sentinel
		end()
		{
			size_type __last_bit_it_index = this->_M_last_bit_index();
			__base_pointer __storage_last = this->_M_storage_pointer_end();
			if (__last_bit_it_index != 0)
				{
					--__storage_last;
				}
			return sentinel(__storage_last, __last_bit_it_index);
		}

		const_iterator
		begin() const
		{
			return this->cbegin();
		}

		const_sentinel
		end() const
		{
			return this->cend();
		}

		const_iterator
		cbegin() const
		{
			return const_iterator(this->_M_storage_pointer(), this->_M_first_bit_index());
		}

		const_sentinel
		cend() const
		{
			size_type __last_bit_it_index       = this->_M_last_bit_index();
			__base_const_pointer __storage_last = this->_M_storage_pointer_end();
			if (__last_bit_it_index != 0)
				{
					--__storage_last;
				}
			return const_sentinel(__storage_last, __last_bit_it_index);
		}

		// observers: bit testing
		constexpr bool
		test(difference_type __pos) const noexcept
		{
			return *::std::next(this->cbegin(), __pos);
		}

		constexpr size_type
		count(value_type __value) const noexcept
		{
			size_type __count = __bit_count(this->cbegin(), this->cend(), true);
			if (!__value)
				{
					return size() - __count;
				}
			return __count;
		}

		constexpr size_type
		popcount() const noexcept
		{
			return this->count(true);
		}

		constexpr size_type
		one_count() const noexcept
		{
			return this->count(true);
		}

		constexpr size_type
		zero_count() const noexcept
		{
			return this->count(false);
		}

		constexpr bool
		all() const noexcept
		{
			const_iterator __last = this->cend();
			return __bit_find(this->cbegin(), __last, false) == __last;
		}

		constexpr bool
		any() const noexcept
		{
			const_iterator __last = this->cend();
			return __bit_find(this->cbegin(), __last, true) != __last;
		}

		constexpr bool
		none() const noexcept
		{
			const_iterator __last = this->cend();
			return __bit_find(this->cbegin(), __last, true) == __last;
		}

		// modifiers
		constexpr reference operator[](difference_type __n) noexcept
		{
			auto __it = this->begin();
			__it += __n;
			return *__it;
		}

		constexpr const_reference operator[](difference_type __n) const noexcept
		{
			auto __it = this->cbegin();
			__it += __n;
			return *__it;
		}

		constexpr void
		set() noexcept
		{
			set(0, this->size());
		}

		// prevent integer promotion
		// from giving users the wrong idea
		constexpr void
		set(bool __value)
		{
			set(value_type(__value));
		}

		constexpr void
		set(value_type __value) noexcept
		{
			set(0, this->size(), __value);
		}

		constexpr void
		set(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.set();
		}

		constexpr void
		set(size_type __pos, bool __val) noexcept
		{
			set(__pos, value_type(__val));
		}

		constexpr void
		set(size_type __pos, value_type __val) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.set(__val);
		}

		constexpr void
		set(size_type __pos, size_type __len) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			__bit_fill_n(__it, __len, true);
		}

		constexpr void
		set(size_type __pos, size_type __len, bool __val) noexcept
		{
			this->set(__pos, __len, value_type(__val));
		}

		constexpr void
		set(size_type __pos, size_type __len, value_type __val) noexcept
		{
			if (__val)
				{
					this->set(__pos, __len);
				}
			else
				{
					this->reset(__pos, __len);
				}
		}

		constexpr void
		reset() noexcept
		{
			reset(0, this->size());
		}

		constexpr void
		reset(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.reset();
		}

		constexpr void
		reset(size_type __pos, size_type __len) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			__bit_fill_n(__it, __len, false);
		}

		constexpr void
		flip() noexcept
		{
			flip(0, this->size());
		}

		constexpr void
		flip(size_type __pos) noexcept
		{
			auto __it = this->begin();
			::std::advance(__it, __pos);
			auto ref = *__it;
			ref.flip();
		}

		constexpr void
		flip(size_type __pos, size_type __len) noexcept
		{
			iterator __it = this->begin();
			::std::advance(__it, __pos);
			if constexpr (::std::is_unsigned_v<__base_value_type>)
				{
					// get to word boundary
					for (size_type __boundary = __len - (__len % (__binary_digits_v<__base_value_type>));
					     __boundary < __len; ++__it, (void)--__len)
						{
							auto ref = *__it;
							ref.flip();
						}
					// process words
					__base_pointer __it_base = ::std::move(__it).base();
					for (; __len > __binary_digits_v<__base_value_type>;
					     __len -= __binary_digits_v<__base_value_type>)
						{
							__base_reference __ref_base = *__it_base;
							__ref_base                  = ~__ref_base;
							++__it_base;
						}
					__it = iterator(::std::move(__it_base), 0);
				}
			// process individual bits
			for (; __len-- > 0; ++__it)
				{
					reference __ref = *__it;
					__ref.flip();
				}
		}

		// modifiers: insert
		reference
		push_back(value_type __value)
		{
			return this->emplace_back(::std::move(__value));
		}

		template<typename... _Args>
		reference
		emplace_back(_Args&&... __args)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return this->_M_emplace_back_unchecked_0(::std::forward<_Args>(__args)...);
				}

			size_type __starting_capacity = this->capacity();
			if (__starting_size == __starting_capacity)
				{
					// make room first
					_S_grow_storage_of_size_with_strategy(
					     this->get_allocator(), this->_M_buf_or_ptr, __starting_size);
				}

			size_type __desired_size = __starting_size + 1;
			__base_pointer __storage_last =
			     this->_M_storage_pointer() + __bit_to_element_size<__base_value_type>(__desired_size);
			__base_pointer __storage_it = __storage_last - 1;
			size_type __last_bit        = _S_last_bit_index(__starting_size);
			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_reference __storage_ref = *__storage_it;
			reference __ref(__storage_ref, __last_bit);
			if constexpr (noexcept(::std::declval<reference&>().set(::std::forward<_Args>(__args)...)))
				{
					__ref.set(::std::forward<_Args>(__args)...);
				}
			else
				{
					try
						{
							__ref.set(::std::forward<_Args>(__args)...);
						}
					catch (...)
						{
							if (__last_bit == 0)
								{
									_S_destroy(this->get_allocator(), __storage_last - 1);
								}
							// rethrow, and drown myself in tears
							throw;
						}
				}
			this->_M_set_size(__desired_size);
			return __ref;
		}

		reference
		push_front(value_type __value)
		{
			return emplace_front(::std::move(__value));
		}

		template<typename... _Args>
		reference
		emplace_front(_Args&&... __args)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return this->_M_emplace_back_unchecked_0(::std::forward<_Args>(__args)...);
				}

			size_type __starting_capacity  = this->capacity();
			__base_pointer __storage_first = this->_M_storage_pointer();
			if (__starting_size == __starting_capacity)
				{
					// make room first
					__storage_first = _S_grow_storage(this->get_allocator(), this->_M_buf_or_ptr);
				}

			size_type __desired_size = __starting_size + 1;
			__base_pointer __storage_last =
			     __storage_first + __bit_to_element_size<__base_value_type>(__desired_size);
			size_type __last_bit = _S_last_bit_index(__starting_size);
			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_pointer __storage_it = __storage_first;
			value_type __saved          = reference(*__storage_it, __max_binary_index_v<__base_value_type>);
			{
				__base_reference __storage_ref = *__storage_it;
				__storage_ref <<= 1;
				reference __ref(__storage_ref, 0);
				if constexpr (noexcept(::std::declval<reference&>().set(::std::forward<_Args>(__args)...)))
					{
						__ref.set(::std::forward<_Args>(__args)...);
					}
				else
					{
						// Booooy howdy, whoever wrote one of these that can throw
						// I sure do dislike your code IMMENSELY. And while I dislike your
						// code, I love you, and I'm sure that -- with hecka amounts of group
						// therapy -- we can get through whatever made you do this, together.
						// ♥
						try
							{
								__ref.set(::std::forward<_Args>(__args)...);
							}
						catch (...)
							{
								if (__last_bit == 0)
									{
										_S_destroy(this->get_allocator(), __storage_last - 1);
									}
								__storage_ref >>= 1;
								reference(__storage_ref, __max_binary_index_v<__base_value_type>) = __saved;
								// rethrow, and drown myself in tears
								throw;
							}
					}
				++__storage_it;
			}
			for (; __storage_it != __storage_last; ++__storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					value_type __before_shift = reference(__storage_ref, __max_binary_index_v<__base_value_type>);
					__storage_ref <<= 1;
					reference __ref(__storage_ref, 0);
					__ref.set(__saved);
					__saved = __before_shift;
				}
			this->_M_set_size(__desired_size);
			return reference(*__storage_first, 0);
		}

		template<typename... _Args>
		iterator
		emplace(const_iterator __where, _Args&&... __args)
		{
			size_type __where_pos             = __where.position();
			__base_const_pointer __where_base = __where.base();
			__base_pointer __storage_first    = this->_M_storage_pointer();
			if (__where_base == __storage_first && __where_pos == 0)
				{
					reference __bit_ref = this->emplace_front(::std::forward<_Args>(__args)...);
					return iterator(__bit_ref.address(), __bit_ref.position());
				}

			size_type __starting_size         = this->size();
			size_type __starting_storage_size = __bit_to_element_size<__base_value_type>(__starting_size);
			size_type __last_bit              = _S_last_bit_index(__starting_size);
			__base_pointer __storage_last     = __storage_first + __starting_storage_size;
			if (__where_base == __storage_last)
				{
					reference __bit_ref = this->emplace_back(::std::forward<_Args>(__args)...);
					return iterator(__bit_ref.address(), __bit_ref.position());
				}
			--__storage_last;
			if (__where_base == __storage_last && __where_pos == __last_bit)
				{
					reference __bit_ref = this->emplace_back(::std::forward<_Args>(__args)...);
					return iterator(__bit_ref.address(), __bit_ref.position());
				}

			size_type __desired_size      = __starting_size + 1;
			size_type __starting_capacity = this->capacity();
			__storage_last              = __storage_first + __bit_to_element_size<__base_value_type>(__desired_size);
			__base_pointer __storage_it = const_cast<__base_pointer>(__where.base());
			if (__starting_size == __starting_capacity)
				{
					// make room first
					difference_type __preserved_distance = __storage_it - __storage_first;
					__storage_first                      = _S_grow_storage_of_size_with_strategy(
                              this->get_allocator(), this->_M_buf_or_ptr, __starting_size);
					__storage_it   = __storage_first + __preserved_distance;
					__storage_last = __storage_first + __bit_to_element_size<__base_value_type>(__desired_size);
				}

			this->_M_construct_at_edge_1(__last_bit, __storage_last);

			__base_pointer __storage_where       = __storage_it;
			__base_reference __first_storage_ref = *__storage_it;
			value_type __saved = reference(__first_storage_ref, __max_binary_index_v<__base_value_type>);
			if (__where_pos == 0)
				{
					__first_storage_ref <<= 1;
				}
			else
				{
					__shift_left_preserve_right<__base_value_type>(__first_storage_ref, __where_pos, 1);
				}
			reference __first_bit_ref(__first_storage_ref, __where_pos);
			__first_bit_ref.set(::std::forward<_Args>(__args)...);
			++__storage_it;

			for (; __storage_it != __storage_last; ++__storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					reference __before_shift_ref(__storage_ref, __max_binary_index_v<__base_value_type>);
					value_type __before_shift = __before_shift_ref;
					__storage_ref <<= 1;
					reference __ref(__storage_ref, 0);
					__ref.set(__saved);
					__saved = __before_shift;
				}

			this->_M_set_size(__desired_size);
			return iterator(__storage_where, __where_pos);
		}

		iterator
		insert(const_iterator __where, value_type __value)
		{
			return this->emplace(::std::move(__where), ::std::move(__value));
		}

		iterator
		insert(const_iterator __where, size_type __desired_count, value_type __value)
		{
			if (__desired_count == 0)
				{
					return iterator(const_cast<__base_pointer>(::std::move(__where).base()), __where.position());
				}

			// FIXME: a better implementation, please.
			if (__where == this->cbegin())
				{
					size_type __index = 0;
					for (; __index < __desired_count; ++__index)
						{
							this->push_front(__value);
						}
					return this->begin();
				}
			if (__where == this->cend())
				{
					size_type __index = 0;
					for (; __index < __desired_count; ++__index)
						{
							this->push_back(__value);
						}
					return this->end() - __index;
				}

			iterator __where_next = insert(::std::move(__where), __value);
			for (size_type __index = 1; __index < __desired_count; ++__index)
				{
					++__where_next;
					__where_next = insert(::std::move(__where_next), __value);
				}
			return __where_next;
		}

		iterator
		insert(const_iterator __where, ::std::initializer_list<value_type> __il)
		{
			return insert(::std::move(__where), __il.begin(), __il.end());
		}

		template<typename _It, typename _Sen, ::std::enable_if_t<!::std::is_arithmetic_v<_It>>* = nullptr>
		iterator
		insert(const_iterator __where, _It __first, _Sen __last)
		{
			using _SenCategory = typename ::std::iterator_traits<_Sen>::iterator_category;
			if (__first == __last)
				{
					return iterator(const_cast<__base_pointer>(::std::move(__where).base()), __where.position());
				}

			// FIXME: a better implementation, please
			if constexpr (__is_iterator_category_or_better_v<::std::bidirectional_iterator_tag, _SenCategory>)
				{
					if (__where == this->cbegin())
						{
							--__last;
							bool __the_last_time = __last == __first;
							this->push_front(*__last);
							for (; !__the_last_time;)
								{
									--__last;
									__the_last_time = __last == __first;
									this->push_front(*__last);
								}
							return this->begin();
						}
				}
			if (__where == this->cend())
				{
					size_type __index = 0;
					for (; __first != __last; ++__first, (void)++__index)
						{
							this->push_back(*__first);
						}
					return this->end() - __index;
				}

			size_type __preserve_old_position = __where - this->cbegin();

			iterator __where_next = this->insert(::std::move(__where), *__first);
			++__first;
			for (; __first != __last; ++__first)
				{
					++__where_next;
					__where_next = this->insert(::std::move(__where_next), *__first);
				}
			return this->begin() + __preserve_old_position;
		}

		// modifiers: erase
		void
		pop_front() noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return;
				}

			__base_pointer __storage_it   = this->_M_storage_pointer();
			__base_pointer __storage_last = this->_M_storage_pointer_end();
			*__storage_it >>= 1;
			__base_pointer __old_storage_it = __storage_it;
			++__storage_it;
			for (; __storage_it != __storage_last; ++__storage_it, (void)++__old_storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					value_type __saved             = reference(__storage_ref, 0);
					__storage_ref >>= 1;
					reference __old_bit(*__old_storage_it, __max_binary_index_v<__base_value_type>);
					__old_bit = __saved;
				}

			this->_M_maybe_shrink_at_edge_size_1(__starting_size);
			this->_M_set_size(__starting_size - 1);
		}

		void
		pop_back() noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return;
				}
			this->_M_maybe_shrink_at_edge_size_1(__starting_size);
			this->_M_set_size(__starting_size - 1);
		}

		iterator
		erase(const_iterator __where) noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			size_type __starting_size = this->size();
			if (__starting_size == 0)
				{
					return this->end();
				}

			__base_const_pointer __where_base = __where.base();
			__base_pointer __storage_last     = this->_M_storage_pointer_end();
			if (__where_base == __storage_last)
				{
					this->pop_back();
					return this->end();
				}

			size_type __where_pos = __where.position();
			size_type __last_bit  = _S_last_bit_index(__starting_size);
			--__storage_last;
			if (__storage_last == __where_base)
				{
					size_type __last_bit_index = __last_bit - 1;
					if (__where_pos >= __last_bit_index)
						{
							this->pop_back();
							return this->end();
						}
				}
			++__storage_last;

			__base_pointer __storage_first = this->_M_storage_pointer();
			if (__where_base == __storage_first && __where_pos == 0)
				{
					this->pop_front();
					return iterator(__storage_first, 0);
				}

			__base_pointer __storage_it          = const_cast<__base_pointer>(__where_base);
			__base_pointer __storage_it_where    = __storage_it;
			__base_reference __first_storage_ref = *__storage_it;
			if (__where_pos == 0)
				{
					__first_storage_ref >>= 1;
				}
			else
				{
					__shift_right_preserve_right<__base_value_type>(__first_storage_ref, __where_pos - 1, 1);
				}
			__base_pointer __old_storage_it = __storage_it;
			++__storage_it;
			for (; __storage_it != __storage_last; ++__storage_it, (void)++__old_storage_it)
				{
					__base_reference __storage_ref = *__storage_it;
					value_type __preserved         = reference(__storage_ref, 0);
					reference __old_bit(*__old_storage_it, __max_binary_index_v<__base_value_type>);
					__old_bit = __preserved;
					__storage_ref >>= 1;
				}

			this->_M_maybe_shrink_at_edge_size_1(__starting_size);
			this->_M_set_size(__starting_size - 1);
			return iterator(__storage_it_where, __where_pos);
		}

		iterator
		erase(const_iterator __first, const_iterator __last) noexcept(
		     ::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			if (this->empty())
				{
					return this->end();
				}
			if (__first == __last)
				{
					return iterator(const_cast<__base_pointer>(__first.base()), __first.position());
				}

			// FIXME: a better implementation, please
			auto __this_first = this->cbegin();
			auto __this_last  = this->cend();
			if (__first == __this_first && __last == __this_last)
				{
					this->clear();
					return this->end();
				}
			if (__first == __this_first)
				{
					size_type __popfronts = static_cast<size_type>(__last - __first);
					for (size_type __index = 0; __index < __popfronts; ++__index)
						{
							this->pop_front();
						}
					return this->begin();
				}
			else if (__last == __this_last)
				{
					size_type __popbacks = static_cast<size_type>(__last - __first);
					for (size_type __index = 0; __index < __popbacks; ++__index)
						{
							this->pop_back();
						}
					return this->end();
				}

			--__last;
			bool __continue_erasing = __first != __last;
			iterator __where_next   = this->erase(__last);
			for (; __continue_erasing;)
				{
					__last = ::std::move(__where_next);
					--__last;
					__continue_erasing = __last != __first;
					__where_next       = this->erase(__last);
				}
			return __where_next;
		}

		// modifiers: assign
		void
		assign(size_type __desired_count, value_type __value)
		{
			// FIXME: BETTER implementation, please.
			this->clear();
			this->insert(this->cend(), __desired_count, __value);
		}

		void
		assign(::std::initializer_list<value_type> __il)
		{
			this->assign(__il.begin(), __il.end());
		}

		template<typename _It, typename _Sen, ::std::enable_if_t<!::std::is_arithmetic_v<_It>>* = nullptr>
		void
		assign(_It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;

			if (__first == __last)
				{
					this->clear();
					return;
				}

			// FIXME: detect if __first is a bit_iterator
			// and do __base_value_type-based construction of new elements
			// on top of regular copy for even more speed

			__alloc& __mem_alloc = this->get_allocator();

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, _ItCategory>)
				{
					size_type __desired_count        = static_cast<size_type>(__last - __first);
					__base_pointer __storage_pointer = this->_M_storage_pointer();
					if (__desired_count > this->capacity())
						{
							__storage_pointer =
							     _S_grow_storage_to(__mem_alloc, this->_M_buf_or_ptr, __desired_count);
						}
					size_type __storage_size          = this->_M_storage_size();
					size_type __desired_storage_count = __bit_to_element_size<__base_value_type>(__desired_count);
					if (__storage_size < __desired_storage_count)
						{
							_S_trampoline_construct_n_using(__mem_alloc, __storage_pointer + __storage_size,
							     __desired_storage_count - __storage_size, &_S_construct_default);
						}
					iterator __bit_it(__storage_pointer, this->_M_first_bit_index());
					::std::copy_n(__first, __desired_count, __bit_it);
				}
			else
				{
					// F E K .
					// Okay...
					iterator __first_bit_it = this->begin();
					iterator __last_bit_it  = this->end();
					for (;; ++__first)
						{
							if (__first == __last)
								{
									return;
								}
							if (__first_bit_it == __last_bit_it)
								{
									// Well, damn...
									// we are out of space: start using regular insertion
									break;
								}
							*__first_bit_it = *__first;
						}
					while (__first != __last)
						{
							this->push_back(*__first);
						}
				}
		}

		void
		shrink_to_fit()
		{
			size_type __capacity = this->capacity();
			size_type __size     = this->size();
			if (__capacity > __size)
				{
					_S_shrink_storage(this->get_allocator(), this->_M_buf_or_ptr, __size);
				}
		}

		void
		reserve(size_type __desired_count)
		{
			size_type __capacity = this->capacity();
			if (__capacity < __desired_count)
				{
					_S_grow_storage_to(this->get_allocator(), this->_M_buf_or_ptr, __desired_count);
				}
		}

		void
		clear()
		{
			this->_M_destroy<false, false>();
		}

	private:
		__packed_small_bit_vector(bool __is_sbo, const __packed_small_bit_vector& __right)
		: __alloc_base(__alloc_traits::select_on_container_copy_construction(__right.get_allocator()))
		, _M_buf_or_ptr(this->get_allocator(), _S_init_base_storage(_S_storage_pointer(__right._M_buf_or_ptr),
		                                            _S_storage_pointer_end(__right._M_buf_or_ptr)))
		{
			_S_fixup_storage(this->_M_buf_or_ptr, __is_sbo);
		}

		__packed_small_bit_vector(
		     bool __is_sbo, const __packed_small_bit_vector& __right, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(this->get_allocator(), _S_init_base_storage(_S_storage_pointer(__right._M_buf_or_ptr),
		                                            _S_storage_pointer_end(__right._M_buf_or_ptr)))
		{
			_S_fixup_storage(this->_M_buf_or_ptr, __is_sbo);
		}

		__packed_small_bit_vector(bool __is_sbo, __packed_small_bit_vector&& __right)
		: __alloc_base(::std::move(__right.get_allocator()))
		, _M_buf_or_ptr(_S_steal<true>(
		       this->get_allocator(), ::std::move(__right._M_buf_or_ptr), ::std::move(__right.get_allocator())))
		{
			_S_fixup_storage(this->_M_buf_or_ptr, __is_sbo);
		}

		__packed_small_bit_vector(bool __is_sbo, __packed_small_bit_vector&& __right, const allocator& __mem_alloc)
		: __alloc_base(__mem_alloc)
		, _M_buf_or_ptr(
		       _S_steal(__mem_alloc, ::std::move(__right._M_buf_or_ptr), ::std::move(__right.get_allocator())))
		{
			_S_fixup_storage(this->_M_buf_or_ptr, __is_sbo);
		}

		struct _Storage
		{
			size_type _M_bit_size;
			__base_value_type* _M_last;

			constexpr _Storage() noexcept : _Storage(0, nullptr)
			{
			}

			constexpr _Storage(__base_pointer __last_ptr) noexcept : _Storage(0, __last_ptr)
			{
			}

			constexpr _Storage(size_type __bit_size, __base_pointer __last_ptr) noexcept
			: _M_bit_size(__bit_size), _M_last(__last_ptr)
			{
			}

			constexpr _Storage(const _Storage& __right) noexcept = default;
			constexpr _Storage&
			operator=(const _Storage& __right) noexcept = default;
		};

		struct _HyperSboStorage
		{
			__uninit<__base_value_type> _M_buf[_InlineWords + (_S_extra_storage_words) + 1];
		};

		struct _RegularSboStorage
		{
			// if InlineWords is zero but is some obscene custom integer
			// type (e.g., uint512_t or something) then do not
			// use it, otherwise space losses could be unacceptably large
			// despite having _InlineWords == 0
			using __space_saving_type = ::std::conditional_t<_InlineWords == 0, unsigned char, __base_value_type>;
			size_type _M_bit_size;
			__uninit<__space_saving_type> _M_buf[_InlineWords == 0 ? 1 : _InlineWords];
		};

		using _SboStorage = ::std::conditional_t<_S_is_hyper_sbo_capable, _HyperSboStorage, _RegularSboStorage>;

		struct _EitherStorage
		{
			__base_pointer _M_first;
			union
			{
				_SboStorage _M_buf;
				_Storage _M_ptr;
			};

			constexpr _EitherStorage(const _EitherStorage&) = delete;
			constexpr _EitherStorage(_EitherStorage&&)      = delete;
			constexpr _EitherStorage&
			operator=(const _EitherStorage&) = delete;
			constexpr _EitherStorage&
			operator=(_EitherStorage&&) = delete;

			constexpr _EitherStorage() : _M_first()
			{
				if constexpr (inline_capacity > 0)
					{
						_S_storage_construct_sbo(*this);
					}
				else
					{
						_S_storage_construct_heap(*this);
					}
			}

			constexpr _EitherStorage(::std::in_place_t) : _M_first(), _M_ptr()
			{
				this->_M_ptr._M_bit_size = 0;
				this->_M_first           = nullptr;
				this->_M_ptr._M_last     = nullptr;
			}

			constexpr _EitherStorage(
			     ::std::in_place_t, __alloc& __mem_alloc, bool __is_sbo, const _EitherStorage& __right)
			{
				if constexpr (inline_capacity > 0)
					{
						if (__is_sbo)
							{
								size_type __storage_count = _S_storage_size_heap(__right);
								_S_storage_construct_sbo(*this);

								this->_M_first = ::std::addressof(this->_M_buf._M_buf[0]._M_value);
								__base_pointer __storage_pointer     = this->_M_first;
								__base_pointer __old_storage_pointer = __right._M_first;
								for (size_type __index = 0; __index < __storage_count;
								     (void)++__index, (void)++__storage_pointer, (void)++__old_storage_pointer)
									{
										_S_construct_initial_value(
										     __mem_alloc, __storage_pointer, *__old_storage_pointer);
									}
								_S_set_size_sbo(*this);
								return;
							}
					}
				_S_storage_construct_heap(*this);
				this->_M_first           = __right._M_first;
				this->_M_ptr._M_bit_size = __right._M_ptr._M_bit_size;
				this->_M_ptr._M_last     = __right._M_ptr._M_last;
			}

			constexpr _EitherStorage(
			     ::std::in_place_t, __alloc& __mem_alloc, bool __is_sbo, _EitherStorage&& __right)
			{
				if constexpr (inline_capacity > 0)
					{
						if (__is_sbo)
							{
								size_type __storage_count = _S_storage_size_heap(__right);
								_S_storage_construct_sbo(*this);

								this->_M_first = ::std::addressof(this->_M_buf._M_buf[0]._M_value);
								__base_pointer __storage_pointer     = this->_M_first;
								__base_pointer __old_storage_pointer = __right._M_first;
								for (size_type __index = 0; __index < __storage_count;
								     (void)++__index, (void)++__storage_pointer)
									{
										_S_construct_move_old_pointer(
										     __mem_alloc, __storage_pointer, __old_storage_pointer);
									}
								_S_set_size_sbo(*this);
								return;
							}
					}
				_S_storage_construct_heap(*this);
				this->_M_first           = __right._M_first;
				this->_M_ptr._M_bit_size = __right._M_ptr._M_bit_size;
				this->_M_ptr._M_last     = __right._M_ptr._M_last;
			}
		} _M_buf_or_ptr;

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_storage_construct_sbo(_EitherStorage& __storage)
		{
			if (false)
				{
					// std::construct_at(::std::addressof(__storage._M_buf));
				}
			else
				{
					new (::std::addressof(__storage._M_buf)) _SboStorage();
					_S_fixup_storage(__storage, true);
					_S_set_size_sbo(__storage, 0);
				}
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_storage_construct_heap(_EitherStorage& __storage)
		{
			if (false)
				{
					// std::construct_at(::std::addressof(__storage._M_buf));
				}
			else
				{
					new (::std::addressof(__storage._M_ptr)) _Storage();
				}
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_switch_storage_to_heap(_EitherStorage& __storage)
		{
			if (!_S_is_sbo(__storage))
				{
					return;
				}
			_S_unchecked_switch_storage_to_heap(__storage);
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_unchecked_switch_storage_to_heap(_EitherStorage& __storage)
		{
			// lifetime reset
			if (false /*::std::is_constant_evaluated()*/)
				{
					// FIXME: destroy + launder + construct_at for constexpr
#if 0
					::std::destruct_at(::std::addressof(__storage._M_buf));
					::std::construct_at(::std::addressof(__storage._M_ptr), nullptr);
					__storage._M_first = nullptr;
#endif // :c
				}
			else
				{
					__storage._M_buf.~_SboStorage();
				}
			_S_storage_construct_heap(__storage);
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_switch_storage_to_sbo(_EitherStorage& __storage)
		{
			if (_S_is_sbo(__storage))
				{
					return;
				}
			_S_unchecked_switch_storage_to_sbo(__storage);
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR void
		_S_unchecked_switch_storage_to_sbo(_EitherStorage& __storage)
		{
			if (false /*::std::is_constant_evaluated()*/)
				{
#if 0
					// FIXME: destroy + launder + construct_at for constexpr
					::std::construct_at(::std::addressof(__storage._M_buf), __storage._M_first);
#endif // :c
				}
			else
				{
					__storage._M_ptr.~_Storage();
				}
			_S_storage_construct_sbo(__storage);
		}

		void
		_M_set_size(size_type __desired_size)
		{
			_S_set_size(this->_M_buf_or_ptr, __desired_size);
		}

		static constexpr void
		_S_set_size_sbo(_EitherStorage& __storage, size_type __desired_size)
		{
			if constexpr (_S_is_hyper_sbo_capable)
				{
					constexpr size_type __inverse_shift =
					     __binary_digits_v<__underlying> - _S_bits_for_inline_size;
					constexpr __base_value_type __size_mask =
					     __pos_to_all_1_mask<__base_value_type>(_S_bits_for_inline_size);
					__base_value_type& __last_element =
					     __storage._M_buf._M_buf[_S_end_storage_buffer_index - 1]._M_value;
					__base_value_type __packed_desired_size =
					     static_cast<__base_value_type>(__desired_size << __inverse_shift);
					__last_element = __packed_desired_size | (__last_element & __size_mask);
				}
			else
				{
					__storage._M_buf._M_bit_size = __desired_size;
				}
		}

		static constexpr void
		_S_set_size(_EitherStorage& __storage, size_type __desired_size)
		{
			if (_S_is_sbo(__storage))
				{
					_S_set_size_sbo(__storage, __desired_size);
				}
			else
				{
					__storage._M_ptr._M_bit_size = __desired_size;
				}
		}

		static constexpr size_type
		_S_size_sbo(const _EitherStorage& __storage)
		{
			if constexpr (_S_is_hyper_sbo_capable)
				{
					constexpr size_type __inverse_shift =
					     __binary_digits_v<__underlying> - _S_bits_for_inline_size;
					constexpr __base_value_type __size_mask =
					     __pos_to_all_1_mask<__base_value_type>(_S_bits_for_inline_size);
					const __base_value_type& __last_element =
					     __storage._M_buf._M_buf[_S_end_storage_buffer_index - 1]._M_value;
					__base_value_type __unpacked_desired_size =
					     static_cast<__base_value_type>(__last_element >> __inverse_shift);
					return static_cast<size_type>(__unpacked_desired_size);
				}
			else
				{
					return __storage._M_buf._M_bit_size;
				}
		}

		static constexpr size_type
		_S_size_heap(const _EitherStorage& __storage)
		{
			return __storage._M_ptr._M_bit_size;
		}

		static constexpr size_type
		_S_size(const _EitherStorage& __storage)
		{
			if (_S_is_sbo(__storage))
				{
					return _S_size_sbo(__storage);
				}
			return _S_size_heap(__storage);
		}

		constexpr size_type
		_M_storage_size() const noexcept
		{
			return __bit_to_element_size<__base_value_type>(this->size());
		}

		static constexpr size_type
		_S_storage_size_sbo(const _EitherStorage& __storage) noexcept
		{
			return __bit_to_element_size<__base_value_type>(_S_size_sbo(__storage));
		}

		static constexpr size_type
		_S_storage_size_heap(const _EitherStorage& __storage) noexcept
		{
			return __bit_to_element_size<__base_value_type>(_S_size_heap(__storage));
		}

		constexpr size_type
		_M_storage_capacity() const noexcept
		{
			return _S_storage_capacity(this->_M_buf_or_ptr);
		}

		static constexpr size_type
		_S_storage_capacity_sbo(const _EitherStorage&) noexcept
		{
			if constexpr (_S_is_hyper_sbo_capable)
				{
					return _S_end_storage_buffer_index;
				}
			else
				{
					return _InlineWords;
				}
		}

		static constexpr size_type
		_S_storage_capacity_heap(const _EitherStorage& __storage) noexcept
		{
			return __storage._M_ptr._M_last - __storage._M_first;
		}

		static constexpr size_type
		_S_storage_capacity(const _EitherStorage& __storage) noexcept
		{
			if (_S_is_sbo(__storage))
				{
					_S_storage_size_sbo(__storage);
				}
			return _S_storage_capacity_heap(__storage);
		}

		static constexpr size_type
		_S_capacity_heap(const _EitherStorage& __storage) noexcept
		{
			return __element_to_bit_size<__base_value_type>(_S_storage_capacity_heap(__storage));
		}

		static constexpr size_type
		_S_capacity_sbo(const _EitherStorage& __storage) noexcept
		{
			return __element_to_bit_size<__base_value_type>(_S_storage_capacity_sbo(__storage));
		}

		static constexpr size_type
		_S_capacity(const _EitherStorage& __storage) noexcept
		{
			if (_S_is_sbo(__storage))
				{
					_S_capacity_size_sbo(__storage);
				}
			return _S_capacity_heap(__storage);
		}

		constexpr bool
		_M_is_sbo() const noexcept
		{
			return _S_is_sbo(this->_M_buf_or_ptr);
		}

		static constexpr bool
		_S_is_sbo(const _EitherStorage& __storage) noexcept
		{
			if constexpr (_S_inline_max_bit_count < 1)
				{
					return false;
				}
			else
				{
					__base_const_pointer __storage_pointer = _S_storage_pointer(__storage);
					__base_const_pointer __lower_inline_storage_pointer =
					     ::std::addressof(__storage._M_buf._M_buf[0]._M_value);
					__base_const_pointer __upper_inline_storage_pointer =
					     ::std::addressof((*(__storage._M_buf._M_buf + _S_end_storage_buffer_index))._M_value);
					return __storage_pointer >= __lower_inline_storage_pointer &&
					       __storage_pointer < __upper_inline_storage_pointer;
				}
		}

		static constexpr bool
		_S_is_sbo_size(size_type __size) noexcept
		{
			return _S_inline_max_bit_count > 0 && __size <= _S_inline_max_bit_count;
		}

		constexpr __base_const_pointer
		_M_storage_pointer() const noexcept
		{
			return _S_storage_pointer(this->_M_buf_or_ptr);
		}

		constexpr __base_pointer
		_M_storage_pointer() noexcept
		{
			return _S_storage_pointer(this->_M_buf_or_ptr);
		}

		static constexpr __base_const_pointer
		_S_storage_pointer(const _EitherStorage& __storage) noexcept
		{
			return __storage._M_first;
		}

		static constexpr __base_pointer
		_S_storage_pointer(_EitherStorage& __storage) noexcept
		{
			return __storage._M_first;
		}

		constexpr __base_pointer
		_M_storage_pointer_end() noexcept
		{
			return _S_storage_pointer_end(this->_M_buf_or_ptr);
		}

		constexpr __base_const_pointer
		_M_storage_pointer_end() const noexcept
		{
			return _S_storage_pointer_end(this->_M_buf_or_ptr);
		}

		static constexpr __base_pointer
		_S_storage_pointer_end(_EitherStorage& __storage) noexcept
		{
			if (_S_is_sbo(__storage))
				{
					return __storage._M_first + _S_storage_size_sbo(__storage);
				}
			else
				{
					return __storage._M_first +
					       __bit_to_element_size<__base_value_type>(__storage._M_ptr._M_bit_size);
				}
		}

		static constexpr __base_const_pointer
		_S_storage_pointer_end(const _EitherStorage& __storage) noexcept
		{
			if (_S_is_sbo(__storage))
				{
					return _S_storage_pointer(__storage) + _S_storage_size_sbo(__storage);
				}
			else
				{
					return _S_storage_pointer(__storage) +
					       __bit_to_element_size<__base_value_type>(__storage._M_ptr._M_bit_size);
				}
		}

		constexpr size_type
		_M_first_bit_index() const noexcept
		{
			return _S_first_bit_index();
		}

		static constexpr size_type
		_S_first_bit_index() noexcept
		{
			return 0;
		}

		constexpr size_type
		_M_last_bit_index() const noexcept
		{
			return _S_last_bit_index(this->size());
		}

		static constexpr size_type
		_S_last_bit_index(size_type __pos) noexcept
		{
			return __pos % __binary_digits_v<__base_value_type>;
		}

		void
		_M_maybe_shrink_at_edge_bit_1(size_type __last_bit)
		{
			if (__last_bit == 0)
				{
					__alloc& __mem_alloc = this->get_allocator();
					_S_destroy(__mem_alloc, this->_M_storage_pointer_end() - 1, 1);
				}
		}

		void
		_M_maybe_shrink_at_edge_size_1(size_type __starting_size)
		{
			size_type __last_bit = _S_last_bit_index(__starting_size - 1);
			this->_M_maybe_shrink_at_edge_bit_1(__last_bit);
		}

		void
		_M_construct_at_edge_1(size_type __last_bit, __base_pointer __storage_last)
		{
			if (__last_bit != 0)
				{
					return;
				}
			__alloc& __mem_alloc = this->get_allocator();
			_S_construct_default(__mem_alloc, __storage_last - 1);
		}

		template<typename... _Args>
		reference
		_M_emplace_back_unchecked_0(_Args&&... __args)
		{
			__base_pointer __storage_first = this->_M_storage_pointer();
			_S_construct_default(this->get_allocator(), __storage_first);
			__base_reference __storage_ref = *__storage_first;
			reference __ref(__storage_ref, 0);
			__ref.set(::std::forward<_Args>(__args)...);
			this->_M_set_size(1);
			return __ref;
		}

		template<typename _It, typename _Sen>
		void
		_M_base_assign(_It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;

			if (__first == __last)
				{
					this->clear();
					return;
				}

			__alloc& __mem_alloc = this->get_allocator();

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, _ItCategory>)
				{
					size_type __desired_storage_count = static_cast<size_type>(__last - __first);
					size_type __desired_count = __element_to_bit_size<__base_value_type>(__desired_storage_count);
					size_type __storage_capacity          = this->_M_storage_capacity();
					__base_pointer __storage_pointer      = this->_M_storage_pointer();
					bool __orphans_in_the_allocators_wake = __desired_storage_count > __storage_capacity;
					if (__orphans_in_the_allocators_wake)
						{
							__storage_pointer =
							     _S_grow_storage_to<true>(__mem_alloc, this->_M_buf_or_ptr, __desired_count);
						}
					size_type __storage_size = this->_M_storage_size();
					if (__orphans_in_the_allocators_wake)
						{
							constexpr _S_construct_iterator_type<_It> __construction_fx = &_S_construct_iterator<_It>;
							this->_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer,
							     __desired_storage_count, 0, __construction_fx, __first);
							_S_set_size(this->_M_buf_or_ptr, __desired_count);
						}
					else
						{
							for (size_type __index = 0; __index < __storage_size && __first != __last;
							     (void)++__index, (void)++__first)
								{
									*(__storage_pointer + __index) = *__first;
								}
							constexpr _S_construct_iterator_type<_It> __construction_fx = &_S_construct_iterator<_It>;
							this->_S_trampoline_construct_using<false>(__mem_alloc,
							     __storage_pointer + __storage_size, __storage_capacity, __first, __last,
							     __construction_fx);
							_S_set_size(this->_M_buf_or_ptr, __desired_count);
						}
				}
			else
				{
					// FIXME: exception safety the whole damn block...
					size_type __current_storage_size = 0;
					__base_pointer __first_it        = this->_M_storage_pointer();
					__base_pointer __last_it         = this->_M_storage_pointer_end();
					for (;; ++__first)
						{
							if (__first == __last)
								{
									return;
								}
							if (__first_it == __last_it)
								{
									break;
								}
							*__first_it = *__first;
							++__current_storage_size;
						}
					while (__first != __last)
						{
							if (__first_it == __last_it)
								{
									size_type __old_storage_size = __last_it - __first_it;
									__first_it = _S_grow_storage_of_size_with_strategy(__mem_alloc,
									     this->_M_buf_or_ptr,
									     __element_to_bit_size<__base_value_type>(__old_storage_size));
									__first_it += __old_storage_size;
									__last_it = this->_M_storage_pointer_end();
								}
							_S_construct_iterator<_It>(__mem_alloc, __first_it, __first);
							++__first_it;
							++__first;
							++__current_storage_size;
						}
					this->_M_set_size(__element_to_bit_size<__base_value_type>(__current_storage_size));
				}
		}

		template<bool _Destruct, bool _Deallocate = true>
		void
		_M_destroy()
		{
			const bool __using_sbo = this->_M_is_sbo();
			const size_type __storage_size =
			     __using_sbo ? _S_storage_size_sbo(this->_M_buf_or_ptr) : _S_storage_size_heap(this->_M_buf_or_ptr);
			__alloc& __mem_alloc = this->get_allocator();
			if (__using_sbo)
				{
					__base_pointer __storage_pointer = this->_M_storage_pointer();
					_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
					if constexpr (!_Destruct)
						{
							this->_M_set_size(0);
						}
					return;
				}

			__base_pointer __storage_pointer = this->_M_storage_pointer();
			size_type __storage_capacity     = _S_storage_capacity_heap(this->_M_buf_or_ptr);
			if constexpr (!_Destruct)
				{
					if constexpr (inline_capacity > 0)
						{
							if constexpr (_Deallocate)
								{
									_S_unchecked_switch_storage_to_sbo(this->_M_buf_or_ptr);
									_S_fixup_storage(this->_M_buf_or_ptr, true);
								}
							this->_M_set_size(0);
						}
					else
						{
							if constexpr (_Deallocate)
								{
									this->_M_buf_or_ptr._M_first       = nullptr;
									this->_M_buf_or_ptr._M_ptr._M_last = nullptr;
								}
							this->_M_set_size(0);
						}
				}
			if (__storage_pointer != nullptr && __storage_capacity != 0)
				{
					_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
					if constexpr (_Deallocate)
						{
							__alloc_traits::deallocate(__mem_alloc, __storage_pointer, __storage_capacity);
						}
				}
		}

		void
		_M_revive()
		{
			if (this->_M_is_sbo())
				{
					return;
				}
			if (this->_M_buf_or_ptr._M_first != this->_M_buf_or_ptr._M_ptr._M_last)
				{
					return;
				}

			// must revive container
			_S_grow_storage_of_size_with_strategy<false>(this->get_allocator(), this->_M_buf_or_ptr, 0);
		}

		template<bool _Pocma>
		void
		_M_steal(__packed_small_bit_vector&& __right)
		{
			this->clear();
			if constexpr (_Pocma)
				{
					// totes yoink
					this->__alloc_base::get_value() = ::std::move(__right.get_allocator());
				}
			_S_steal_into<_Pocma>(this->get_allocator(), ::std::move(this->_M_buf_or_ptr),
			     ::std::move(__right._M_buf_or_ptr), ::std::move(__right.get_allocator()));
		}

		template<bool _Pocma>
		static _EitherStorage
		_S_steal(
		     allocator& __left_alloc, _EitherStorage&& __left, _EitherStorage&& __right, allocator&& __right_alloc)
		{
			const bool __right_using_sbo = _S_is_sbo(__right);
			if (__right_using_sbo)
				{
					__alloc& __pocma_alloc = _Pocma ? __left_alloc : __right_alloc;
					// gotta do the SBO shuffle...
					__base_pointer __storage_pointer       = __left._M_first;
					__base_pointer __right_storage_pointer = __right._M_first;
					size_type __right_storage_size         = __right._M_buf_or_ptr._M_buf._M_storage_size();
					_S_construct_move_old_pointer<false>(__left_alloc, __storage_pointer, __right_storage_size);
					// must destroy old SBO contents
					// since they can't actually be stolen!
					_S_destroy(__pocma_alloc, __right_storage_pointer, __right_storage_size);
					return __left;
				}
			else
				{
					// just steal guts
					__left                = ::std::move(__right._M_buf_or_ptr);
					__right._M_buf_or_ptr = _S_init_empty_heap_storage();
				}
		}

		template<bool _Pocma>
		static void
		_S_steal_into(
		     allocator& __left_alloc, _EitherStorage&& __left, _EitherStorage&& __right, allocator&& __right_alloc)
		{
			__left = _S_steal<_Pocma>(__left_alloc, ::std::move(__right), ::std::move(__right_alloc));
		}

		template<bool _DeallocateOnFailure, typename _Fx, typename... _Args>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_trampoline_construct_n_using(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     size_type __alloc_capacity, size_type __desired_count, _Fx&& __fx,
		     _Args&&... __args) noexcept(::std::is_nothrow_invocable_v<_Fx, __alloc&, __base_pointer, _Args...>)
		{
			static constexpr bool __is_construct_noexcept =
			     ::std::is_nothrow_invocable_v<_Fx, __alloc&, __base_pointer, _Args...>;
			size_type __lifetime_count = 0;
			if constexpr (__is_construct_noexcept)
				{
					(void)__alloc_capacity;
					for (; __lifetime_count < __desired_count; ++__lifetime_count)
						{
							__fx(__mem_alloc, __storage_pointer + __lifetime_count,
							     ::std::forward<_Args>(__args)...);
						}
				}
			else
				{
					try
						{
							for (; __lifetime_count < __desired_count; ++__lifetime_count)
								{
									__fx(__mem_alloc, __storage_pointer + __lifetime_count,
									     ::std::forward<_Args>(__args)...);
								}
						}
					catch (...)

						{
							// destroy everything that failed to construct
							_S_destroy(__mem_alloc, __storage_pointer, __lifetime_count);
							if constexpr (_DeallocateOnFailure)
								{
									// nuke memory if we need to
									__alloc_traits::deallocate(
									     __mem_alloc, __storage_pointer, __alloc_capacity);
								}
							else
								{
									(void)__alloc_capacity;
								}
							// rethrow exception
							throw;
						}
				}
		}

		template<bool _DeallocateOnFailure, typename _It, typename _Sen, typename _Fx, typename... _Args>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_trampoline_construct_using(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     size_type __alloc_capacity, _It __first, _Sen __last, _Fx&& __fx,
		     _Args&&... __args) noexcept(::std::is_nothrow_invocable_v<_Fx, __alloc&, __base_pointer, _It&, _Args...>)
		{
			static constexpr bool __is_construct_noexcept =
			     ::std::is_nothrow_invocable_v<_Fx, __alloc&, __base_pointer, _It&, _Args...>;
			size_type __lifetime_count = 0;
			if constexpr (__is_construct_noexcept)
				{
					(void)__alloc_capacity;
					for (; __first != __last; (void)++__lifetime_count, ++__first)
						{
							__fx(__mem_alloc, __storage_pointer + __lifetime_count, __first,
							     ::std::forward<_Args>(__args)...);
						}
				}
			else
				{
					try
						{
							for (; __first != __last; (void)++__lifetime_count, ++__first)
								{
									__fx(__mem_alloc, __storage_pointer + __lifetime_count, __first,
									     ::std::forward<_Args>(__args)...);
								}
						}
					catch (...)
						{
							// destroy everything that failed to construct
							_S_destroy(__mem_alloc, __storage_pointer, __lifetime_count);
							if constexpr (_DeallocateOnFailure)
								{
									// nuke memory if we need to
									__alloc_traits::deallocate(
									     __mem_alloc, __storage_pointer, __alloc_capacity);
								}
							else
								{
									(void)__alloc_capacity;
								}
							// rethrow exception
							throw;
						}
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_default(__alloc& __mem_alloc, __base_pointer __storage_pointer) noexcept(
		     ::std::is_nothrow_default_constructible_v<__base_value_type>)
		{
			if constexpr (::std::is_trivial_v<__base_value_type> &&
			              !__is_detected_v<__allocator_construct_invocable_test, __alloc&, __base_pointer>)
				{
					(void)__mem_alloc;
					new (__storage_pointer) __base_value_type;
				}
			else
				{
					__alloc_traits::construct(__mem_alloc, __storage_pointer);
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_initial_value(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     const __base_value_type& __initial_value) noexcept(noexcept(__alloc_traits::construct(__mem_alloc,
		     __storage_pointer, __initial_value)))
		{
			__alloc_traits::construct(__mem_alloc, __storage_pointer, __initial_value);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_move_old_pointer(__alloc& __mem_alloc, __base_pointer __storage_pointer,
		     __base_pointer& __old_pointer) noexcept(::std::is_nothrow_move_constructible_v<__base_value_type>)
		{
			if (::std::is_nothrow_move_constructible_v<__base_value_type>)
				{
					__alloc_traits::construct(__mem_alloc, __storage_pointer, ::std::move(*__old_pointer));
				}
			else
				{
					// must degrade to a copy operation,
					// otherwise a throw from a move would be impossible to
					// recover from for the __base_value_type in question
					__alloc_traits::construct(__mem_alloc, __storage_pointer, *__old_pointer);
				}
			++__old_pointer;
		}

		template<typename _It>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_construct_iterator(__alloc& __mem_alloc, __base_pointer __storage_pointer, _It& __it) noexcept(
		     ::std::is_nothrow_constructible_v<__base_value_type, decltype(*__it)>)
		{
			__alloc_traits::construct(__mem_alloc, __storage_pointer, *__it);
		}

		static constexpr size_type
		_S_growth_strategy(size_type __old_size)
		{
			return __old_size < 1 ? (_S_inline_max_bit_count < 1 ? __binary_digits_v<__base_value_type> * 4
			                                                     : _S_inline_max_bit_count * 2)
			                      : __old_size * 2;
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage(__alloc& __mem_alloc, _EitherStorage& __storage)
		{
			return _S_grow_storage_of_size_with_strategy(__mem_alloc, __storage, _S_size(__storage));
		}

		template<bool _OrphanObjects = false>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_to(__alloc& __mem_alloc, _EitherStorage& __storage, size_type __desired_capacity)
		{
			return _S_grow_storage_of_size_to<_OrphanObjects>(
			     __mem_alloc, __storage, _S_size(__storage), __desired_capacity);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_of_size_with_strategy(__alloc& __mem_alloc, _EitherStorage& __storage, size_type __old_size)
		{
			return _S_grow_storage_of_size_to(__mem_alloc, __storage, __old_size, _S_growth_strategy(__old_size));
		}

		template<bool _OrphanObjects = false>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_grow_storage_of_size_to(
		     __alloc& __mem_alloc, _EitherStorage& __storage, size_type __old_size, size_type __desired_capacity)
		{
			bool __using_sbo = _S_is_sbo(__storage);
			if (__using_sbo)
				{
					if (_S_is_sbo_size(__desired_capacity))
						{
							// we are already in SBO, the capacity is already fine
							return _S_storage_pointer(__storage);
						}
					// transfer to non-SBO storage and grow
					return _S_transfer_inline_to_heap(__mem_alloc, __storage, __desired_capacity);
				}
			else
				{
					size_type __desired_storage_capacity =
					     __bit_to_element_size<__base_value_type>(__desired_capacity);
					size_type __old_storage_capacity = _S_storage_capacity(__storage);
					if (__desired_storage_capacity <= __old_storage_capacity)
						{
							// nothing needs doing
							return _S_storage_pointer(__storage);
						}

					// need to grow
					__base_pointer __old_storage_pointer = _S_storage_pointer(__storage);
					size_type __old_storage_size         = __bit_to_element_size<__base_value_type>(__old_size);

					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_capacity);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}

					if (__old_storage_pointer != nullptr)
						{
							__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
							if (!_OrphanObjects)
								{
									_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer,
									     __desired_storage_capacity, __old_storage_size,
									     &_S_construct_move_old_pointer, __old_storage_pointer_move_arg);
								}
							_S_destroy(__mem_alloc, __old_storage_pointer, __old_storage_size);
							__alloc_traits::deallocate(
							     __mem_alloc, __old_storage_pointer, __old_storage_capacity);
						}

					__storage._M_first       = __storage_pointer;
					__storage._M_ptr._M_last = __storage_pointer + __desired_storage_capacity;
					if (!_OrphanObjects)
						{
							_S_set_size(__storage, __old_storage_size);
						}
					return __storage_pointer;
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_shrink_storage(__alloc& __mem_alloc, _EitherStorage& __storage, __base_pointer __old_storage_pointer,
		     size_type __desired_capacity)
		{
			bool __using_sbo                     = _S_is_sbo(__storage, __old_storage_pointer);
			size_type __desired_storage_capacity = __bit_to_element_size<__base_value_type>(__desired_capacity);
			size_type __old_size                 = _S_size(__storage);
			size_type __old_storage_size         = _S_storage_size(__storage);
			size_type __old_storage_capacity     = _S_storage_capacity(__storage);

			if (_S_is_sbo_size(__desired_capacity))
				{
					if (__using_sbo)
						{
							// already using SBO: just shrink bit size
							// and deconstruct edge words
							size_type __desired_old_storage_size_diff =
							     __old_storage_size - __desired_storage_capacity;
							_S_destroy(__mem_alloc, __old_storage_pointer + __desired_storage_capacity,
							     __desired_old_storage_size_diff);
							_S_set_size_sbo(__storage, __desired_capacity);
							return _S_storage_pointer(__storage);
						}

					// lifetime reset
					_S_unchecked_switch_storage_to_sbo(__storage);
					_S_fixup_storage(__storage._M_buf_or_ptr, true);
					__base_pointer __storage_pointer = _S_storage_pointer(__storage);
					if constexpr (::std::is_nothrow_invocable_v<decltype(&_S_construct_move_old_pointer), __alloc&,
					                   __base_pointer, __base_pointer>)
						{
							__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
							_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
							     __desired_storage_capacity, &_S_construct_move_old_pointer,
							     __old_storage_pointer_move_arg);
						}
					else
						{
							// awh geez
							// tread carefully now...
							try
								{
									__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
									_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
									     __desired_storage_capacity, &_S_construct_move_old_pointer,
									     __old_storage_pointer_move_arg);
								}
							catch (...)
								{
									// something went to shit, fast!
									// Restore old pointers, don't deallocate/destroy,
									// rethrow!
									_S_unchecked_switch_storage_to_heap(__storage);
									__storage._M_first       = __old_storage_pointer;
									__storage._M_ptr._M_last = __old_storage_pointer + __old_storage_capacity;
									__storage._M_ptr._M_bit_size = __old_size;
									throw;
								}
						}
					_S_destroy(__mem_alloc, __old_storage_pointer, __old_storage_size);
					__alloc_traits::deallocate(__mem_alloc, __old_storage_pointer, __old_storage_capacity);

					_S_set_size(__storage, __desired_capacity);

					return __storage_pointer;
				}
			else
				{
					// shrink, but no SBO
					// also implies old size was not SBO to begin with
#if 0
					assert(!__using_sbo);
#endif
					// WARNING: C++ has no realloc
					// method on allocators
					// this means we allocate,
					// move, destroy, and then cry bitter tears
					// if it all fails
					// would be nice if there was a reallocate method
					// that did all of this _for_ me >.>
					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_capacity);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}
					__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
					_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer,
					     __desired_storage_capacity, __desired_storage_capacity, &_S_construct_move_old_pointer,
					     __old_storage_pointer_move_arg);

					size_type __storage_capacity = __storage._M_ptr._M_storage_capacity();
					size_type __storage_size     = __storage._M_ptr._M_storage_size();
					_S_destroy(__mem_alloc, __storage_pointer, __storage_size);
					__alloc_traits::deallocate(__mem_alloc, __storage_pointer, __storage_capacity);

					return __storage_pointer;
				}
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_transfer_inline_to_heap_with_strategy(__alloc& __mem_alloc, _EitherStorage& __storage)
		{
			size_type __old_size = _S_size(__storage);
			return _S_transfer_inline_to_heap(__mem_alloc, __storage, _S_growth_strategy(__old_size));
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR __base_pointer
		_S_transfer_inline_to_heap(__alloc& __mem_alloc, _EitherStorage& __storage, size_type __desired_capacity)
		{
			if (!_S_is_sbo(__storage))
				{
					return _S_storage_pointer(__storage);
				}
			size_type __old_size                 = _S_size_sbo(__storage);
			size_type __old_storage_size         = _S_storage_size_sbo(__storage);
			__base_pointer __old_storage_pointer = _S_storage_pointer(__storage);
			size_type __desired_storage_capacity = __bit_to_element_size<__base_value_type>(__desired_capacity);
			__base_pointer __storage_pointer     = __alloc_traits::allocate(__mem_alloc, __desired_storage_capacity);
			if (__storage_pointer == nullptr)
				{
					throw ::std::bad_alloc();
				}

			__base_pointer __old_storage_pointer_move_arg = __old_storage_pointer;
			_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer, __desired_storage_capacity,
			     __old_storage_size, &_S_construct_move_old_pointer, __old_storage_pointer_move_arg);

			// destroy union data
			_S_destroy(__mem_alloc, __old_storage_pointer, __old_storage_size);

			// finally, swap union storage...
			_S_unchecked_switch_storage_to_heap(__storage);
			__storage._M_first           = __storage_pointer;
			__storage._M_ptr._M_bit_size = __old_size;
			__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_capacity;

			return __storage_pointer;
		}

		static constexpr std::pair<_EitherStorage, bool>
		_S_init_empty_storage()
		{
			if constexpr (_S_inline_max_bit_count < 1)
				{
					return _S_init_empty_heap_storage();
				}
			else
				{
					return { _EitherStorage(), true };
				}
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_empty_storage_into(_EitherStorage& __storage)
		{
			if constexpr (_S_inline_max_bit_count < 1)
				{
					return _S_init_empty_heap_storage_into(__storage);
				}
			else
				{
					_S_switch_storage_to_sbo(__storage);
					_S_set_size_sbo(__storage, 0);
					_S_fixup_storage(__storage, true);
					return true;
				}
		}

		static constexpr void
		_S_fixup_storage(_EitherStorage& __storage, bool __is_sbo)
		{
			if constexpr (inline_capacity > 0)
				{
					if (__is_sbo)
						{
							__storage._M_first = ::std::addressof(__storage._M_buf._M_buf[0]._M_value);
						}
				}
			else
				{
					(void)__is_sbo;
				}
		}

		static constexpr std::pair<_EitherStorage, bool>
		_S_init_empty_heap_storage()
		{
			return { _EitherStorage(::std::in_place), false };
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_empty_heap_storage_into(_EitherStorage& __storage)
		{
			_S_switch_storage_to_heap(__storage);
			__storage._M_first           = nullptr;
			__storage._M_ptr._M_last     = nullptr;
			__storage._M_ptr._M_bit_size = 0;
			return false;
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_base_storage(__alloc& __mem_alloc, _It __first, _Sen __last)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_base_storage_into(
			     __storage_and_is_sbo.first, __mem_alloc, ::std::move(__first), ::std::move(__last));
			return __storage_and_is_sbo;
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_ALLOCATOR_CONSTEXPR bool
		_S_init_base_storage_into(_EitherStorage& __storage, __alloc& __mem_alloc, _It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;
			if (__first == __last)
				{
					// nothing to write into
					return _S_init_empty_storage_into(__storage);
				}

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, _ItCategory>)
				{
					size_type __desired_storage_count = static_cast<size_type>(__last - __first);
					size_type __desired_count = __element_to_bit_size<__base_value_type>(__desired_storage_count);
					if (_S_is_sbo_size(__desired_count))
						{
							_S_switch_storage_to_sbo(__storage);
							__base_pointer __storage_pointer                  = _S_storage_pointer(__storage);
							constexpr _S_construct_iterator_type<_It> __construction_fx = &_S_construct_iterator<_It>;
							_S_trampoline_construct_using<false>(__mem_alloc, __storage_pointer, 0,
							     ::std::move(__first), ::std::move(__last), __construction_fx);
							_S_set_size_sbo(__storage, __desired_count);
							return true;
						}

					_S_storage_construct_heap(__storage);
					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}
					constexpr _S_construct_iterator_type<_It> __construction_fx = &_S_construct_iterator<_It>;
					_S_trampoline_construct_using<true>(__mem_alloc, __storage_pointer, __desired_storage_count,
					     ::std::move(__first), ::std::move(__last), __construction_fx);
					__storage._M_first           = __storage_pointer;
					__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_count;
					__storage._M_ptr._M_bit_size = __desired_count;
					return false;
				}
			else
				{
					_S_switch_storage_to_sbo(__storage);
					size_type __current_size         = __binary_digits_v<__base_value_type>;
					size_type __current_index        = 0;
					__base_pointer __storage_pointer = _S_storage_pointer(__storage);
					// FIXME: this storage needs the Strong Exception Guarantee
					for (; __first != __last && _S_is_sbo_size(__current_size);
					     (void)(__current_size += __binary_digits_v<__base_value_type>),
					     (void)(__current_index += __binary_digits_v<__base_value_type>), (void)++__first,
					     (void)++__storage_pointer)
						{
							_S_construct_iterator(__mem_alloc, __storage_pointer, __first);
							_S_set_size(__storage, __current_size);
						}
					if (__first == __last)
						{
							return false;
						}
					size_type __transfer_size = __bit_to_element_size<__base_value_type>(__current_index);
					__storage_pointer         = _S_transfer_inline_to_heap_with_strategy(__mem_alloc, __storage);
					__storage_pointer += __transfer_size;
					for (; __first != __last; (void)(__current_size += __binary_digits_v<__base_value_type>),
					     (void)(__current_index += __binary_digits_v<__base_value_type>), (void)++__first,
					     (void)++__storage_pointer)
						{
							if (__storage_pointer == __storage._M_ptr._M_last)
								{
									size_type __current_storage_size =
									     __bit_to_element_size<__base_value_type>(__current_index);
									__storage_pointer = _S_grow_storage_of_size_with_strategy(
									     __mem_alloc, __storage, __current_index);
									__storage_pointer += __current_storage_size;
								}
							_S_construct_iterator(__mem_alloc, __storage_pointer, __first);
							_S_set_size(__storage, __current_size);
						}
					return false;
				}
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_storage(__alloc& __mem_alloc, _It __first, _Sen __last)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_into(
			     __storage_and_is_sbo.first, __mem_alloc, ::std::move(__first), ::std::move(__last));
			return __storage_and_is_sbo;
		}

		template<typename _It, typename _Sen>
		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_storage_into(_EitherStorage& __storage, __alloc& __mem_alloc, _It __first, _Sen __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_It>::iterator_category;
			if (__first == __last)
				{
					// nothing to write into
					return _S_init_empty_storage_into(__storage);
				}

			if constexpr (__is_iterator_category_or_better_v<::std::random_access_iterator_tag, _ItCategory>)
				{
					size_type __desired_count         = static_cast<size_type>(__last - __first);
					size_type __desired_storage_count = __bit_to_element_size<__base_value_type>(__desired_count);
					if (_S_is_sbo_size(__desired_count))
						{
							_S_switch_storage_to_sbo(__storage);
							__base_pointer __storage_pointer = _S_storage_pointer(__storage);
							_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
							     __desired_storage_count, &_S_construct_default);
							iterator __storage_it(__storage_pointer, _S_first_bit_index());
							::std::copy(::std::move(__first), ::std::move(__last), __storage_it);
							_S_set_size_sbo(__storage, static_cast<size_type>(__desired_count));
							return true;
						}

					_S_storage_construct_heap(__storage);
					__base_pointer __storage_pointer =
					     __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
					if (__storage_pointer == nullptr)
						{
							throw ::std::bad_alloc();
						}
					_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer, __desired_storage_count,
					     __desired_storage_count, &_S_construct_default);
					__storage._M_first           = __storage_pointer;
					__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_count;
					__storage._M_ptr._M_bit_size = __desired_count;
					iterator __storage_it(__storage_pointer, 0);
					::std::copy(::std::move(__first), ::std::move(__last), __storage_it);
					return false;
				}
			else
				{
					_S_switch_storage_to_sbo(__storage);
					size_type __current_size         = 1;
					size_type __current_index        = 0;
					__base_pointer __storage_pointer = _S_storage_pointer(__storage);
					iterator __storage_it(__storage_pointer, _S_first_bit_index());
					// FIXME: this storage needs the Strong Exception Guarantee
					for (; __first != __last && _S_is_sbo_size(__current_size);
					     ++__current_size, (void)++__current_index, (void)++__first, (void)++__storage_it)
						{
							if (__storage_it.position() == 0)
								{
									_S_construct_default(__mem_alloc, __storage_it.base());
								}
							*__storage_it = *__first;
							_S_set_size(__storage, __current_size);
						}

					if (__first == __last)
						{
							return false;
						}

					// well, we ran out of Small Buffer bits...
					size_type __current_storage_size = __bit_to_element_size<__base_value_type>(__current_index);
					__storage_pointer = _S_transfer_inline_to_heap_with_strategy(__mem_alloc, __storage);
					__storage_it = iterator(__storage_pointer + __current_storage_size, __storage_it.position());

					for (; __first != __last;
					     ++__current_size, (void)++__current_index, (void)++__first, (void)++__storage_it)
						{
							__base_pointer __storage_it_base = __storage_it.base();
							if (__storage_it_base == __storage._M_ptr._M_last)
								{
									size_type __current_storage_size =
									     __bit_to_element_size<__base_value_type>(__current_index);
									__storage_pointer = _S_grow_storage_of_size_with_strategy(
									     __mem_alloc, __storage, __current_index);
									__storage_it_base = __storage_pointer + __current_storage_size;
									__storage_it      = iterator(__storage_it_base, __storage_it.position());
								}
							if (__storage_it.position() == 0)
								{
									_S_construct_default(__mem_alloc, __storage_it_base);
								}
							*__storage_it = *__first;
							_S_set_size(__storage, __current_size);
						}
					return false;
				}
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_storage_count_value(
		     __alloc& __mem_alloc, size_type __desired_count, const __base_value_type& __initial_value)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_count_value_into(
			     __storage_and_is_sbo.first, __mem_alloc, __desired_count, __initial_value);
			return __storage_and_is_sbo;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_storage_count_value_into(_EitherStorage& __storage, __alloc& __mem_alloc, size_type __desired_count,
		     const __base_value_type& __initial_value)
		{
			if (__desired_count == static_cast<size_type>(0))
				{
					return _S_init_empty_storage_into(__storage);
				}

			size_type __desired_storage_count = __bit_to_element_size<__base_value_type>(__desired_count);
			if (_S_is_sbo_size(__desired_count))
				{
					_S_switch_storage_to_sbo(__storage);
					__base_pointer __storage_pointer = _S_storage_pointer(__storage);
					_S_trampoline_construct_n_using<false>(__mem_alloc, __storage_pointer, 0,
					     __desired_storage_count, &_S_construct_initial_value, __initial_value);
					_S_set_size_sbo(__storage, __desired_count);
					return true;
				}

			_S_switch_storage_to_heap(__storage);
			__base_pointer __storage_pointer = __alloc_traits::allocate(__mem_alloc, __desired_storage_count);
			if (__storage_pointer == nullptr)
				{
					throw ::std::bad_alloc();
				}
			_S_trampoline_construct_n_using<true>(__mem_alloc, __storage_pointer, __desired_storage_count,
			     __desired_storage_count, &_S_construct_initial_value, __initial_value);
			__storage._M_first           = __storage_pointer;
			__storage._M_ptr._M_last     = __storage_pointer + __desired_storage_count;
			__storage._M_ptr._M_bit_size = __desired_count;
			return false;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_storage_count_zero(__alloc& __mem_alloc, size_type __desired_count)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_count_value_into(
			     __storage_and_is_sbo.first, __mem_alloc, __desired_count, __base_value_type());
			return __storage_and_is_sbo;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_storage_count_zero_into(_EitherStorage& __storage, __alloc& __mem_alloc, size_type __desired_count)
		{
			return _S_init_storage_count_value_into(__storage, __mem_alloc, __desired_count, __base_value_type());
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_base_storage_count_zero(__alloc& __mem_alloc, size_type __desired_storage_count)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_count_value_into(__storage_and_is_sbo.first, __mem_alloc,
			     __element_to_bit_size<__base_value_type>(__desired_storage_count), __base_value_type());
			return __storage_and_is_sbo;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_base_storage_count_zero_into(
		     _EitherStorage& __storage, __alloc& __mem_alloc, size_type __desired_storage_count)
		{
			return _S_init_storage_count_value_into(__storage, __mem_alloc,
			     __element_to_bit_size<__base_value_type>(__desired_storage_count), __base_value_type());
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR std::pair<_EitherStorage, bool>
		_S_init_base_storage_count_value(
		     __alloc& __mem_alloc, size_type __desired_storage_count, const __base_value_type& __initial_value)
		{
			std::pair<_EitherStorage, bool> __storage_and_is_sbo;
			__storage_and_is_sbo.second = _S_init_storage_count_value_into(
			     __mem_alloc, __element_to_bit_size<__base_value_type>(__desired_storage_count), __initial_value);
			return __storage_and_is_sbo;
		}

		static ITSY_BITSY_BLESSED_CONSTEXPR bool
		_S_init_base_storage_count_value_into(_EitherStorage& __storage, __alloc& __mem_alloc,
		     size_type __desired_storage_count, const __base_value_type& __initial_value)
		{
			return _S_init_storage_count_value_into(__storage, __mem_alloc,
			     __element_to_bit_size<__base_value_type>(__desired_storage_count), __initial_value);
		}

		static ITSY_BITSY_ALLOCATOR_CONSTEXPR void
		_S_destroy(__alloc& __mem_alloc, __base_pointer __storage_pointer, size_type __desired_count)
		{
			for (; __desired_count-- > 0;)
				{
					__alloc_traits::destroy(__mem_alloc, (__storage_pointer + __desired_count));
				}
		}
	}; // namespace ITSY_BITSY_DETAIL_NAMESPACE

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator==(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		auto __left_size  = __left.size();
		auto __right_size = __right.size();
		if (__left_size != __right_size)
			{
				return false;
			}

		return ::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator!=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		auto __left_size  = __left.size();
		auto __right_size = __right.size();
		if (__left_size != __right_size)
			{
				return true;
			}
		return !::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator<(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		return ::std::lexicographical_compare(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator<=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		return !(__left > __right);
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator>(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		return ::std::lexicographical_compare(
		     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::greater<bool>());
	}

	template<typename _LeftTy, ::std::size_t _LeftInline, typename _LeftAlloc, bool _LeftPacked, typename _RightTy,
	     ::std::size_t _RightInline, typename _RightAlloc, bool _RightPacked>
	constexpr bool
	operator>=(const __packed_small_bit_vector<_LeftTy, _LeftInline, _LeftAlloc, _LeftPacked>& __left,
	     const __packed_small_bit_vector<_RightTy, _RightInline, _RightAlloc, _RightPacked>& __right)
	{
		return !(__left < __right);
	}

	template<typename _Type,
	     ::std::size_t _InlineWords = __default_small_buffer_size_v<_Type, ::std::allocator<_Type>>,
	     typename _Allocator        = ::std::allocator<_Type>>
	class __small_bit_vector : public __packed_small_bit_vector<_Type, _InlineWords, _Allocator, false>
	{
	private:
		template<typename, ::std::size_t, typename, bool>
		friend class __packed_small_bit_vector;
		template<typename, ::std::size_t, typename>
		friend class __small_bit_vector;

		using __base_t = __packed_small_bit_vector<_Type, _InlineWords, _Allocator, false>;

	public:
		using __base_t::__base_t;
	};
} // namespace ITSY_BITSY_DETAIL_NAMESPACE

#undef ITSY_BITSY_ALLOCATOR_CONSTEXPR

// end of itsy/detail/small_bit_vector.hpp

#include <memory>
#include <cstddef>

namespace bitsy
{
	template<typename T, typename Allocator = std::allocator<T>>
	inline constexpr ::std::size_t default_small_buffer_size_v =
	     ::ITSY_BITSY_DETAIL_NAMESPACE::__default_small_buffer_size_v<T, Allocator>;

	template<typename Word,
	     ::std::size_t InlineBufferSize = default_small_buffer_size_v<Word, std::allocator<Word>>,
	     typename Allocator             = std::allocator<Word>>
	class small_bit_vector : public ::ITSY_BITSY_DETAIL_NAMESPACE::__small_bit_vector<Word, InlineBufferSize, Allocator> {
	private:
		using base_t = ::ITSY_BITSY_DETAIL_NAMESPACE::__small_bit_vector<Word, InlineBufferSize, Allocator>;
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

		using base_t::base_t;
	};

	template<typename Word,
	     ::std::size_t InlineBufferSize = default_small_buffer_size_v<Word, std::allocator<Word>>,
	     typename Allocator             = std::allocator<Word>>
	class packed_small_bit_vector : public ::ITSY_BITSY_DETAIL_NAMESPACE::__packed_small_bit_vector<Word, InlineBufferSize, Allocator, true> {
	private:
		using base_t = ::ITSY_BITSY_DETAIL_NAMESPACE::__packed_small_bit_vector<Word, InlineBufferSize, Allocator, true>;
	public:
		using difference_type = typename base_t::difference_type;
		using size_type       = typename base_t::size_type;
		using value_type      = typename base_t::value_type;
		using reference       = typename base_t::reference;
		using const_reference = typename base_t::const_reference;
		using iterator_concept = typename base_t::iterator_concept;
		using iterator_category = typename base_t::iterator_category;
		using pointer           = typename base_t::pointer;
		using iterator          = typename base_t::iterator;
		using sentinel          = typename base_t::sentinel;
		using const_iterator    = typename base_t::const_iterator;
		using const_sentinel    = typename base_t::const_sentinel;

		using base_t::base_t;
	};
} // namespace bitsy

// end of itsy/small_bit_vector.hpp

// beginning of itsy/bit_sequence.hpp

// beginning of itsy/detail/bit_sequence.hpp

#include <cstddef>
#include <type_traits>
#include <utility>
#include <initializer_list>
#include <algorithm>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	template<typename _Container>
	class __bit_sequence : private __bit_view<_Container, __word_bit_bounds<_Container>>
	{
	private:
		template<typename, typename>
		friend class __bit_view;

		using __base_t                   = __bit_view<_Container, __word_bit_bounds<_Container>>;
		using __base_value_type          = typename __base_t::__base_value_type;
		using __integral_base_value_type = typename __base_t::__integral_base_value_type;
		using __base_reference           = typename __base_t::__base_reference;
		using __base_c_reference         = typename __base_t::__base_c_reference;
		using __base_iterator            = typename __base_t::__base_iterator;
		using __base_c_iterator          = typename __base_t::__base_c_iterator;
		using __base_iterator_category   = typename __base_t::__base_iterator_category;
		using __base_c_iterator_category = typename __base_t::__base_c_iterator_category;
		using __range_ref                = typename __base_t::__range_ref;

	public:
		using difference_type = typename __base_t::difference_type;
		using size_type       = typename __base_t::size_type;
		using value_type      = typename __base_t::value_type;
		using reference       = typename __base_t::reference;
		using const_reference = typename __base_t::const_reference;
		using iterator_category = typename __base_t::iterator_category;
		using iterator_concept = __iterator_concept_t<__base_iterator>;
		using pointer           = typename __base_t::pointer;
		using iterator          = typename __base_t::iterator;
		using sentinel          = typename __base_t::sentinel;
		using const_iterator    = typename __base_t::const_iterator;
		using const_sentinel    = typename __base_t::const_sentinel;
		using container_type    = typename __base_t::container_type;

		// constructors
		__bit_sequence() noexcept(noexcept(__base_t())) : __base_t(), _M_bit_pos(__binary_digits_v<__base_value_type>)
		{
		}

		template<typename... _Args>
		__bit_sequence(::std::in_place_t, _Args&&... __args) noexcept(
		     noexcept(__base_t(::std::forward<_Args>(__args)...)))
		: __base_t(::std::forward<_Args>(__args)...), _M_bit_pos(__binary_digits_v<__base_value_type>)
		{
		}

		template<typename _Iterator, typename _Sentinel,
		     std::enable_if_t<!::std::is_arithmetic_v<_Iterator> &&
		                      !::std::is_same_v<_Iterator, ::std::in_place_t>>* = nullptr>
		__bit_sequence(_Iterator __first, _Sentinel __last) noexcept(noexcept(__bit_sequence(
		     __dummy_tag{}, __bit_sequence::_S_efficient_empty_create(::std::move(__first), ::std::move(__last)))))
		: __bit_sequence(
		       __dummy_tag{}, __bit_sequence::_S_efficient_empty_create(::std::move(__first), ::std::move(__last)))
		{
		}

		__bit_sequence(size_type __desired_count) noexcept(
		     noexcept(__bit_sequence(__desired_count, static_cast<value_type>(false))))
		: __bit_sequence(__desired_count, static_cast<value_type>(false))
		{
		}

		__bit_sequence(size_type __desired_count, value_type __val) noexcept(noexcept(
		     __bit_sequence(__dummy_tag{}, __bit_sequence::_S_efficient_empty_create_sized(__desired_count, __val))))
		: __bit_sequence(__dummy_tag{}, __bit_sequence::_S_efficient_empty_create_sized(__desired_count, __val))
		{
		}

		__bit_sequence(::std::initializer_list<value_type> __il) noexcept(
		     noexcept(__bit_sequence(__il.begin(), __il.end())))
		: __bit_sequence(__il.begin(), __il.end())
		{
		}

		__bit_sequence(const __bit_sequence& __right) = default;

		__bit_sequence(__bit_sequence&& __right) = default;

		// assignment
		__bit_sequence&
		operator=(const __bit_sequence& __right) = default;

		__bit_sequence&
		operator=(__bit_sequence&& __right) = default;

		// modifiers
		void
		reserve(size_type __desired_capacity)
		{
			this->_M_storage_unwrapped().reserve(__desired_capacity);
		}

		__bit_sequence&
		assign(const __bit_sequence& __right)
		{
			return this->operator=(__right);
		}

		__bit_sequence&
		assign(__bit_sequence&& __right)
		{
			return this->operator=(::std::move(__right));
		}

		__bit_sequence&
		assign(::std::initializer_list<value_type> __il)
		{
			clear();
			if (__il.size() == 0)
				{
					return *this;
				}
			this->_M_empty_assign(__il.begin(), __il.end());
			return *this;
		}

		template<typename _Iterator, typename _Sentinel,
		     ::std::enable_if_t<!::std::is_arithmetic_v<_Iterator>>* = nullptr>
		__bit_sequence&
		assign(_Iterator __first, _Sentinel __last)
		{
			clear();
			if (__first == __last)
				{
					return *this;
				}
			this->_M_empty_assign(::std::move(__first), ::std::move(__last));
			return *this;
		}

		__bit_sequence&
		assign(size_type __desired_count, value_type __val)
		{
			clear();
			if (__desired_count == static_cast<size_type>(0))
				{
					return *this;
				}

			this->_M_empty_assign_sized(__desired_count, __val);
			return *this;
		}

		using __base_t::flip;
		using __base_t::reset;
		using __base_t::set;

		void
		push_back(value_type __val)
		{
			using __bit_ref = reference;
			__base_iterator __storage_it;
			if (_M_bit_pos == __binary_digits_v<__base_value_type>)
				{
					// FIXME: use optimized push_front of container,
					// if possible!
					__storage_it = this->_M_storage_unwrapped().insert(
					     this->_M_storage_cend(), static_cast<__base_value_type>(0));
					_M_bit_pos = 0;
				}
			else
				{
					__storage_it = this->_M_storage_end();
					--__storage_it;
				}

			__bit_ref __ref(*__storage_it, _M_bit_pos);
			__ref = __val;

			++_M_bit_pos;
		}

		void
		push_front(value_type __val)
		{
			using __bit_ref = reference;
			if (_M_bit_pos == __binary_digits_v<__base_value_type>)
				{
					// FIXME: use optimized push_front of container,
					// if possible!
					this->_M_storage_unwrapped().insert(
					     this->_M_storage_cend(), static_cast<__base_value_type>(0));
					_M_bit_pos = 0;
				}
			++_M_bit_pos;

			auto __storage_first = this->_M_storage_begin();
			auto __storage_last  = this->_M_storage_end();
			value_type __old_val = __val;
			for (; __storage_first != __storage_last; ++__storage_first)
				{
					__base_reference __ref = *__storage_first;
					__bit_ref __front(__ref, 0);
					__bit_ref __back(__ref, __max_binary_index_v<__base_value_type>);
					__old_val = __back;
					__ref <<= 1;
					__front = __val;
					__val   = __old_val;
				}
		}

		iterator
		insert(const_iterator __where, ::std::initializer_list<value_type> __il)
		{
			return this->insert(::std::move(__where), __il.begin(), __il.end());
		}

		iterator
		insert(const_iterator __where, size_type __desired_count, value_type __val)
		{
			if (__desired_count < static_cast<size_type>(1))
				{
					__base_iterator __nowhere =
					     this->_M_storage_unwrapped().insert(__where.base(), __where.base());
					return iterator(::std::move(__nowhere), __where.position());
				}
			iterator __current_pos = this->insert(::std::move(__where), __val);
			for (size_type __index = 1; __index < __desired_count; ++__index)
				{
					__current_pos = this->insert(::std::move(__current_pos), __val);
				}
			return __current_pos;
		}

		template<typename _Iterator, typename _Sentinel>
		iterator
		insert(const_iterator __where, _Iterator __first, _Sentinel __last)
		{
			using _ItCategory = typename ::std::iterator_traits<_Iterator>::iterator_category;

			if (__first == __last)
				{
					__base_c_iterator __where_base = ::std::move(__where).base();
					__base_iterator __nowhere =
					     __iter_as_mutable_from_begin(__where_base, this->_M_storage_unwrapped());
					return iterator(::std::move(__nowhere), __where.position());
				}

			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag, _ItCategory>)
				{
					return this->_M_source_random_access_insert(
					     ::std::move(__where), ::std::move(__first), ::std::move(__last));
				}
			else
				{
					return this->_M_basic_insert(::std::move(__where), ::std::move(__first), ::std::move(__last));
				}
		}

		iterator
		insert(const_iterator __where, value_type __val)
		{
			if (this->empty())
				{
					push_back(__val);
					return --this->end();
				}
			auto __where_base   = ::std::move(__where).base();
			auto __where_pos    = ::std::move(__where).position();
			auto __storage_last = this->_M_storage_cend();
			if (__where.base() == __storage_last)
				{
					push_back(__val);
					return --this->end();
				}
			auto __storage_before_last = __storage_last;
			--__storage_before_last;
			if (__storage_before_last == __where_base && __where_pos >= this->_M_bit_pos)
				{
					push_back(__val);
					return --this->end();
				}
			if (__where_base == this->_M_storage_cbegin() && __where_pos == 0)
				{
					push_front(__val);
					return this->begin();
				}

			// okay, we are inserting somewhere in the
			// middle of the words ...
			// do we have enough space?
			if (this->_M_bit_pos == __binary_digits_v<__base_value_type>)
				{
					// we need more space for this
					// this may also invalidates old iterators,
					// so we need to re-establish
					// the position iterator we had...
					difference_type __saved_dist = ::std::distance(this->_M_storage_cbegin(), __where_base);
					this->_M_storage_unwrapped().insert(
					     this->_M_storage_cend(), static_cast<__base_value_type>(0));
					this->_M_bit_pos = 0;
					__where_base     = this->_M_storage_cbegin();
					::std::advance(__where_base, __saved_dist);
					__storage_last = this->_M_storage_cend();
				}
			__base_iterator __storage_first = this->_M_storage_begin();
			difference_type __storage_dist  = ::std::distance(__base_c_iterator(__storage_first), __where_base);
			__base_iterator __storage_it    = ::std::next(__storage_first, __storage_dist);
			iterator __insertion_return(__storage_it, __where_pos);

			__base_reference __first_ref = *__storage_it;
			++__storage_it;
			reference __first_insert_target(__first_ref, __where_pos);
			// save potential off-the-edge value
			value_type __old_val = reference(__first_ref, __max_binary_index_v<__base_value_type>);

			// are we not at the MSB edge of a word?
			if (__where_pos != __max_binary_index_v<__base_value_type>)
				{
					// we are not at the edge of a word
					// need to shift pertinent values
					if (__where_pos != 0)
						{
							// we are not at the LSB, shift bits
							__shift_left_preserve_right<__base_value_type>(__first_ref, __where_pos, 1);
						}
					else
						{
							__first_ref <<= 1;
						}
				}
			// write new value
			__first_insert_target = __val;

			for (; __storage_it != __storage_last; ++__storage_it)
				{
					__base_reference __storage_current_ref = *__storage_it;
					value_type __saved = reference(__storage_current_ref, __max_binary_index_v<__base_value_type>);
					__storage_current_ref <<= 1;
					reference(__storage_current_ref, 0) = __old_val;
					__old_val                           = __saved;
				}

			++_M_bit_pos;

			return __insertion_return;
		}

		void
		pop_back()
		{
			if (this->empty())
				{
					return;
				}
			--this->_M_bit_pos;
			if (this->_M_bit_pos == 0)
				{
					this->_M_bit_pos = __binary_digits_v<__base_value_type>;
					// FIXME: use optimized pop_back of container,
					// if possible!
					this->_M_storage_unwrapped().erase(--this->_M_storage_cend());
				}
		}

		void
		pop_front()
		{
			if (this->empty())
				{
					return;
				}
			__base_iterator __storage_first  = this->_M_storage_begin();
			__base_iterator __storage_last   = this->_M_storage_end();
			__base_iterator __old_storage_it = __storage_first;
			(*__old_storage_it) >>= 1;
			++__storage_first;
			for (; __storage_first != __storage_last; ++__storage_first, (void)++__old_storage_it)
				{
					__base_reference __storage_ref = *__storage_first;
					value_type __old_val           = reference(__storage_ref, 0);
					__storage_ref >>= 1;
					reference __old_bit_ref(*__old_storage_it, __max_binary_index_v<__base_value_type>);
					__old_bit_ref = __old_val;
				}
			if (this->_M_bit_pos == 0)
				{
					this->_M_bit_pos = __binary_digits_v<__base_value_type>;
					// FIXME: use optimized pop_front of container,
					// if possible!
					this->_M_storage_unwrapped().erase(--this->_M_storage_cend());
				}
			--this->_M_bit_pos;
		}

		constexpr iterator
		erase(const_iterator __first, const_sentinel __last) noexcept
		{
			if (__first == __last)
				{
					__base_iterator __nowhere = this->_M_storage_unwrapped().erase(__first.base(), __first.base());
					return iterator(::std::move(__nowhere), __first.position());
				}
			if (this->empty())
				{
					return this->end();
				}
			if (__first == this->cbegin() && __last == this->cend())
				{
					clear();
					return this->end();
				}
			// if this is a random access iterator,
			// then size computation is cheap
			// and so is bulk, sized removal
			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag, iterator_category>)
				{
					return this->_M_this_random_access_erase(::std::move(__first), ::std::move(__last));
				}
			else
				{
					return this->_M_basic_erase(::std::move(__first), ::std::move(__last));
				}
		}

		constexpr iterator
		erase(const_iterator __where) noexcept
		{
			if (this->empty())
				{
					return this->end();
				}
			auto __where_base   = ::std::move(__where).base();
			auto __where_pos    = ::std::move(__where).position();
			auto __storage_last = this->_M_storage_cend();
			if (__where_base == __storage_last)
				{
					return this->end();
				}
			--__storage_last;
			if (__storage_last == __where_base)
				{
					if (__where_pos >= this->_M_bit_pos)
						{
							pop_back();
							return this->end();
						}
					else if (this->_M_bit_pos - 1 == __where_pos)
						{
							this->pop_back();
							return this->end();
						}
				}
			if (__where_base == this->_M_storage_cbegin() && __where_pos == 0)
				{
					this->pop_front();
					return this->begin();
				}
			// okay, we actually have to remove old bits now...
			__base_iterator __storage_first = this->_M_storage_begin();
			difference_type __storage_dist  = ::std::distance(__base_c_iterator(__storage_first), __where_base);
			__base_iterator __storage_it    = ::std::next(__storage_first, __storage_dist);

			// put __storage_last back to
			// the end iterator
			++__storage_last;

			// save old bits that will be affected by left shift
			__base_reference __storage_ref = *__storage_it;
			if (__where_pos == 0)
				{
					// no old bits matter: just truncate at the desired position
					__storage_ref >>= 1;
				}
			else
				{
					// sigh... old bits do matter, save, truncate, then restore old bits
					__shift_right_preserve_right<__base_value_type>(__storage_ref, __where_pos - 1, 1);
				}

			// great, now shift literally everything else indiscriminately
			auto __old_storage_it  = __storage_it;
			auto __curr_storage_it = __storage_it;
			++__curr_storage_it;
			for (; __curr_storage_it != __storage_last; ++__curr_storage_it, (void)++__old_storage_it)
				{
					// get current iterator's position
					__base_reference __curr_pos_ref = *__curr_storage_it;
					// get least significant bit that is going to
					// be shift-truncated
					value_type __old_val = reference(__curr_pos_ref, 0);
					// assign it to the MSB of the old word
					reference(*__old_storage_it, __max_binary_index_v<__base_value_type>) = __old_val;
					// shift over
					__curr_pos_ref >>= 1;
				}

			// did we chop off an old word?
			if (_M_bit_pos == 0)
				{
					this->_M_bit_pos = __binary_digits_v<__base_value_type> - 1;
					// destroy it
					--__storage_last;
					bool __storage_last_is_current = __storage_it == __storage_last;
					auto __removed_storage_it      = this->_M_storage_unwrapped().erase(__storage_last);
					if (__storage_last_is_current)
						{
							// the storage we had was removed, we need to return
							// that iterator itself
							// otherwise we have invalidation issues!
							return iterator(::std::move(--__removed_storage_it), __where_pos);
						}
				}
			else
				{
					// no, so just decrement and
					// pretend higher bits don't exist
					--this->_M_bit_pos;
				}
			return iterator(::std::move(__storage_it), __where_pos);
		}

		constexpr void
		clear() noexcept
		{
			this->_M_bit_pos = __binary_digits_v<__base_value_type>;
			this->_M_storage_unwrapped().clear();
		}

		constexpr void
		swap(__bit_sequence& __right) noexcept(::std::is_nothrow_swappable_v<container_type>)
		{
			__adl_swap(this->_M_storage_unwrapped(), __right._M_storage);
			__adl_swap(this->_M_bit_pos, __right._M_bit_pos);
		}

		// observers
		using __base_t::all;
		using __base_t::any;
		using __base_t::count;
		using __base_t::none;
		using __base_t::one_count;
		using __base_t::popcount;
		using __base_t::test;
		using __base_t::zero_count;

		using __base_t::operator[];

		bool
		empty() const
		{
			return __adl_empty(this->_M_storage_unwrapped());
		}

		reference
		back() noexcept
		{
			auto __back_it = this->end();
			--__back_it;
			return *(__back_it);
		}

		const_reference
		back() const noexcept
		{
			auto __back_it = this->cend();
			--__back_it;
			return *(__back_it);
		}

		reference
		front() noexcept
		{
			__base_reference __storage_ref = *this->_M_storage_begin();
			return reference(__storage_ref, 0);
		}

		const_reference
		front() const noexcept
		{
			__base_c_reference __storage_ref = *this->_M_storage_cbegin();
			return const_reference(__storage_ref, 0);
		}

		std::add_lvalue_reference_t<_Container>
		base() noexcept
		{
			return this->_M_storage_unwrapped();
		}

		std::add_const_t<std::add_lvalue_reference_t<_Container>>
		base() const noexcept
		{
			return this->_M_storage_unwrapped();
		}

		constexpr size_type
		size() const noexcept
		{
			size_type __word_size = __adl_size(this->_M_storage_unwrapped());
			if (__word_size == 0)
				{
					return 0;
				}
			return (__word_size - 1) * __binary_digits_v<__base_value_type> + this->_M_bit_pos;
		}

		constexpr iterator
		begin() noexcept
		{
			return iterator(this->_M_storage_begin(), 0);
		}

		constexpr sentinel
		end() noexcept
		{
			auto __storage_last = this->_M_storage_end();
			if (this->_M_bit_pos < __binary_digits_v<__base_value_type>)
				{
					--__storage_last;
					return sentinel(::std::move(__storage_last), this->_M_bit_pos);
				}
			return sentinel(::std::move(__storage_last), 0);
		}

		constexpr const_iterator
		begin() const noexcept
		{
			return this->cbegin();
		}

		constexpr const_sentinel
		end() const noexcept
		{
			return this->cend();
		}

		constexpr const_iterator
		cbegin() const noexcept
		{
			return const_iterator(this->_M_storage_begin(), 0);
		}

		constexpr const_sentinel
		cend() const noexcept
		{
			auto __storage_last = this->_M_storage_cend();
			if (this->_M_bit_pos < __binary_digits_v<__base_value_type>)
				{
					--__storage_last;
					return const_sentinel(::std::move(__storage_last), this->_M_bit_pos);
				}
			return const_sentinel(::std::move(__storage_last), 0);
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator==(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) ==
					       static_cast<const typename _Right::__base_t&>(__right);
				}
			return ::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator!=(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) !=
					       static_cast<const typename _Right::__base_t&>(__right);
				}
			return !::std::equal(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator<(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) <
					       static_cast<const typename _Right::__base_t&>(__right);
				}
			return ::std::lexicographical_compare(
			     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::less<bool>());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator<=(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) <=
					       static_cast<const typename _Right::__base_t&>(__right);
				}

			return !::std::lexicographical_compare(
			     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::greater<bool>());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator>(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) >
					       static_cast<const typename _Right::__base_t&>(__right);
				}
			return ::std::lexicographical_compare(
			     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::greater<bool>());
		}

		template<typename _RightContainer>
		friend constexpr bool
		operator>=(const __bit_sequence& __left, const __bit_sequence<_RightContainer>& __right)
		{
			using _Left  = __bit_sequence;
			using _Right = __bit_sequence<_RightContainer>;

			if (__left._M_bit_pos == __binary_digits_v<typename _Left::__base_value_type> &&
			     __right._M_bit_pos == __binary_digits_v<typename _Right::__base_value_type>)
				{
					return static_cast<const typename _Left::__base_t&>(__left) >=
					       static_cast<const typename _Right::__base_t&>(__right);
				}

			return !::std::lexicographical_compare(
			     __left.cbegin(), __left.cend(), __right.cbegin(), __right.cend(), ::std::less<bool>());
		}

	private:
		size_type _M_bit_pos = 0;

		__bit_sequence(__dummy_tag, ::std::pair<container_type, size_type> __container_position) noexcept(
		     noexcept(__base_t(::std::move(__container_position.first))))
		: __base_t(::std::move(__container_position.first)), _M_bit_pos(__container_position.second)
		{
			// avoids inefficiencies by using a static method to create needed data and
			// delegating to some internal constructor which can properly
			// init the data
			// C++ needs a better constructor story, or we'll keep
			// having spammy constructor delegation
			// like this for all eternity...
			// but what do I know? I'm just a GSoCer. c:
		}

		template<typename _Iterator, typename _Sentinel>
		static constexpr void
		_S_efficient_empty_assign_into(
		     _Iterator __first, _Sentinel __last, __range_ref& __storage, size_type& __bit_pos)
		{
			// welp...
			// it's bulk, so only medium slow
			// instead of slow-slow?
			size_type __bit_counter        = 0;
			size_type __modulo_bit_counter = 0;
			__base_iterator __storage_it =
			     __storage.insert(__adl_cend(__storage), static_cast<__base_value_type>(0));
			iterator __it(::std::move(__storage_it), 0);
			for (; __first != __last; ++__first, (void)++__bit_counter, (void)++__modulo_bit_counter, (void)++__it)
				{
					if (__modulo_bit_counter == __binary_digits_v<__base_value_type>)
						{
							__base_iterator __storage_it =
							     __storage.insert(__adl_cend(__storage), static_cast<__base_value_type>(0));
							__it                 = iterator(::std::move(__storage_it), 0);
							__modulo_bit_counter = 0;
						}
					*__it = *__first;
				}
			__bit_pos = __modulo_bit_counter;
		}

		static constexpr void
		_S_efficient_empty_assign_into_sized(
		     size_type __desired_count, value_type __val, __range_ref& __storage, size_type& __bit_pos)
		{
			size_type __word_insertion = (__desired_count / __binary_digits_v<__base_value_type>);
			__bit_pos                  = (__desired_count % __binary_digits_v<__base_value_type>);
			if (__bit_pos == 0)
				{
					__bit_pos = __binary_digits_v<__base_value_type>;
				}
			else
				{
					++__word_insertion;
				}

			__storage.assign(__word_insertion,
			     __val ? static_cast<__base_value_type>(::std::numeric_limits<__integral_base_value_type>::max())
			           : static_cast<__base_value_type>(0));
		}

		template<typename _Iterator, typename _Sentinel>
		constexpr void
		_M_empty_assign(_Iterator __first, _Sentinel __last)
		{
			decltype(auto) __storage = this->_M_storage_unwrapped();
			_S_efficient_empty_assign_into(::std::move(__first), ::std::move(__last), __storage, this->_M_bit_pos);
		}

		constexpr void
		_M_empty_assign_sized(size_type __desired_count, value_type __val)
		{
			decltype(auto) __storage = this->_M_storage_unwrapped();
			_S_efficient_empty_assign_into_sized(__desired_count, __val, __storage, this->_M_bit_pos);
		}

		template<typename _Iterator, typename _Sentinel>
		static constexpr ::std::pair<container_type, size_type>
		_S_efficient_empty_create(_Iterator __first, _Sentinel __last)
		{
			if (__first == __last)
				{
					return { container_type(), static_cast<size_type>(__binary_digits_v<__base_value_type>) };
				}

			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag,
			                   typename ::std::iterator_traits<_Iterator>::iterator_category>)
				{
					size_type __desired_count  = ::std::distance(__first, __last);
					size_type __word_insertion = (__desired_count / __binary_digits_v<__base_value_type>);
					size_type __bit_pos        = (__desired_count % __binary_digits_v<__base_value_type>);
					if (__bit_pos == 0)
						{
							__bit_pos = __binary_digits_v<__base_value_type>;
						}
					else
						{
							++__word_insertion;
						}

					container_type __storage(__word_insertion, static_cast<__base_value_type>(0));
					__base_iterator __storage_it = __storage.begin();
					iterator __copy_it(::std::move(__storage_it), 0);
					::std::copy_n(__first, __desired_count, __copy_it);
					return { ::std::move(__storage), __bit_pos };
				}
			else
				{
					container_type __storage;
					size_type __bit_pos;
					_S_efficient_empty_assign_into(
					     ::std::move(__first), ::std::move(__last), __storage, __bit_pos);
					return { ::std::move(__storage), __bit_pos };
				}
		}

		static constexpr ::std::pair<container_type, size_type>
		_S_efficient_empty_create_sized(size_type __desired_count, value_type __val)
		{
			if (__desired_count < 1)
				{
					return { container_type(), static_cast<size_type>(__binary_digits_v<__base_value_type>) };
				}
			size_type __word_insertion = (__desired_count / __binary_digits_v<__base_value_type>);
			size_type __bit_pos        = (__desired_count % __binary_digits_v<__base_value_type>);
			if (__bit_pos == 0)
				{
					__bit_pos = __binary_digits_v<__base_value_type>;
				}
			else
				{
					++__word_insertion;
				}

			container_type __storage(__word_insertion,
			     __val ? static_cast<__base_value_type>(::std::numeric_limits<__integral_base_value_type>::max())
			           : static_cast<__base_value_type>(0));
			return { ::std::move(__storage), __bit_pos };
		}

		template<typename _Iterator, typename _Sentinel>
		constexpr iterator
		_M_source_random_access_insert(const_iterator __where, _Iterator __first, _Sentinel __last)
		{
			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag, iterator_category>)
				{
					difference_type __insert_bit_count = ::std::distance(__first, __last);
					return this->_M_this_and_source_random_access_insert(
					     __insert_bit_count, ::std::move(__where), ::std::move(__first), ::std::move(__last));
				}
			else
				{
					return this->_M_basic_insert(::std::move(__where), ::std::move(__first), ::std::move(__last));
				}
		}

		template<typename _Iterator, typename _Sentinel>
		constexpr iterator
		_M_this_and_source_random_access_insert(
		     difference_type __insert_bit_count, const_iterator __where, _Iterator __first, _Sentinel __last)
		{
			size_type __where_pos        = __where.position();
			difference_type __where_dist = __where - this->cbegin();
			if (__where_pos == 0)
				{
					// we can copy literally everything
					// without individual bit management
					__base_c_iterator __where_base = ::std::move(__where).base();
					difference_type __insert_word_count =
					     __insert_bit_count / __binary_digits_v<__base_value_type>;
					difference_type __insert_bit_shift = __insert_bit_count % __binary_digits_v<__base_value_type>;
					iterator __shift_insertion_target  = this->_M_copy_words_if_necessary(
                              __insert_word_count, __where_dist, __where_base, __first);
					if (__insert_bit_shift > 0)
						{
							this->_M_basic_insert(__shift_insertion_target, __first, __last);
						}
					iterator __ret = this->begin();
					__ret += __where_dist;
					return __ret;
				}
			// okay now we're back to the boring implementation...
			// first, shove in as many bits until we get to
			// a word boundary using basic insert

			// FIXME: optimize basic less-than-word bulk insertions
			difference_type __bits_to_boundary = __binary_digits_v<__base_value_type> - __where_pos;
			if (__bits_to_boundary >= __insert_bit_count)
				{
					_Iterator __boundary_last = __first;
					__boundary_last += __insert_bit_count;
					return this->_M_basic_insert(
					     ::std::move(__where), ::std::move(__first), ::std::move(__boundary_last));
				}
			iterator __boundary_it =
			     this->_M_basic_insert(::std::move(__where), __first, __first + __bits_to_boundary);
			__base_iterator __boundary_base_it = ::std::move(__boundary_it).base();
			++__boundary_base_it;

			// now insert and copy words, which require no shifts at all
			difference_type __leftover_bits       = __insert_bit_count - __bits_to_boundary;
			difference_type __leftover_words      = __leftover_bits / __binary_digits_v<__base_value_type>;
			difference_type __leftover_words_bits = __leftover_words * __binary_digits_v<__base_value_type>;
			__base_iterator __insertion_point = this->_M_storage_unwrapped().insert(::std::move(__boundary_base_it),
			     static_cast<size_type>(__leftover_words), static_cast<__base_value_type>(0));
			__first += __bits_to_boundary;
			iterator __wheret_word_it =
			     ::std::copy_n(__first, __leftover_words_bits, iterator(__insertion_point, 0));

			// finally, handle the last bits...
			// FIXME: handle bulk less-than-word insertions
			__leftover_bits -= __leftover_words_bits;
			if (__leftover_bits > 0)
				{
					__first += __leftover_words_bits;
					this->_M_basic_insert(__wheret_word_it, __first, __last);
				}
			iterator __ret = this->begin();
			__ret += __where_dist;
			return __ret;
		}

		template<typename _Iterator>
		constexpr iterator
		_M_copy_words_if_necessary(difference_type __insert_word_count, difference_type __where_dist,
		     __base_c_iterator __where_base, _Iterator& __first)
		{
			if (__insert_word_count > 0)
				{
					difference_type __where_base_dist = __where_dist / __binary_digits_v<__base_value_type>;
					difference_type __insert_word_bit_count =
					     __insert_word_count * __binary_digits_v<__base_value_type>;
					__base_iterator __storage_it = this->_M_storage_unwrapped().insert(::std::move(__where_base),
					     static_cast<size_type>(__insert_word_count), static_cast<__base_value_type>(0));
					::std::advance(__storage_it, __where_base_dist);
					iterator __insertion_point = iterator(__storage_it, 0);
					iterator __wheret_copy_it = ::std::copy_n(__first, __insert_word_bit_count, __insertion_point);
					__first += __insert_word_bit_count;
					return __wheret_copy_it;
				}
			return iterator(__iter_as_mutable_from_begin(__where_base, this->_M_storage_unwrapped()), 0);
		}

		template<typename _Iterator, typename _Sentinel>
		constexpr iterator
		_M_basic_insert(const_iterator __where, _Iterator __first, _Sentinel __last)
		{
			bool __is_storage_empty = this->empty();
			if (__is_storage_empty)
				{
					for (; __first != __last; ++__first)
						{
							this->push_back(*__first);
						}
					return this->begin();
				}
			// we can only check cbegin, because
			// we can't save an iterator for
			// wherever "end" is before we start
			// shoveling things in (yay, iterator invalidation...)
			if constexpr (__is_iterator_category_or_better_v<std::random_access_iterator_tag, iterator_category>)
				{
					// if we're inserting at the end,
					// and we are random access,
					// we can get a distance
					// and then use it later on to return the
					// insertion point properly from this method
					if (__where == this->cend())
						{
							difference_type __insertion_point_at = static_cast<difference_type>(this->size());
							for (; __first != __last; ++__first)
								{
									this->push_back(*__first);
								}
							return ::std::next(this->begin(), __insertion_point_at);
						}
				}
			if (__where == this->cbegin())
				{
					for (; __first != __last; ++__first)
						{
							this->push_front(*__first);
						}
					return this->begin();
				}
			if constexpr (__is_iterator_category_or_better_v<::std::bidirectional_iterator_tag, iterator_category> &&
			              __weakly_decrementable_v<_Sentinel>)
				{
					--__last;
					bool __the_last_time   = __last == __first;
					iterator __current_pos = this->insert(::std::move(__where), *__last);
					for (; !__the_last_time;)
						{
							--__last;
							__the_last_time = __last == __first;
							__current_pos   = this->insert(::std::move(__current_pos), *__last);
						}
					return __current_pos;
				}
			else
				{
					iterator __current_pos = this->insert(::std::move(__where), *__first);
					++__first;
					for (; __first != __last; ++__first)
						{
							++__current_pos;
							__current_pos = this->insert(::std::move(__current_pos), *__first);
						}
					return __current_pos;
				}
		}

		constexpr __base_iterator
		_M_maybe_storage_bulk_erase(
		     __base_c_iterator& __first_base_it, size_type __first_position, difference_type __erase_word_count)
		{
			if (__erase_word_count > static_cast<difference_type>(0))
				{
					return this->_M_storage_bulk_erase(__first_base_it, __first_position, __erase_word_count);
				}
			else
				{
					return __iter_as_mutable_from_begin(__first_base_it, this->_M_storage_unwrapped());
				}
		}

		constexpr __base_iterator
		_M_storage_bulk_erase(__base_c_iterator& __first_base_it, size_type __first_position,
		     difference_type __erase_word_count) noexcept
		{
			// are we on a boundary?
			if (__first_position == 0)
				{
					// perfectly aligned on word boundary,
					// no half-word to shift:
					// remove indiscriminately
					auto __storage_it =
					     this->_M_storage_unwrapped().erase(__first_base_it, __first_base_it + __erase_word_count);
					return __storage_it;
				}

			// Not perfectly aligned...
			// attempt to preserve bits on boundaries of removal
			__base_c_iterator __last_base_it = __first_base_it + (__erase_word_count);
			// if the last is equal to end, we're just removing everything aren't we?
			if (__last_base_it == this->_M_storage_cend())
				{
					return this->_M_storage_unwrapped().erase(__first_base_it, __last_base_it);
				}

			// bulk-remove the parts we do not care about
			// and merge tips into a single word that
			// we can perform shifts on later
			// save msb word for later merging into non-removed part, for when the shift happens
			__base_value_type __lsb_word_chunk = *__first_base_it;
			__base_iterator __storage_it       = this->_M_storage_unwrapped().erase(__first_base_it, __last_base_it);
			__base_reference __msb_word_chunk_ref = *__storage_it;
			__base_value_type __msb_word_chunk    = __msb_word_chunk_ref;
			__msb_word_chunk_ref = __merge_bits_at(__lsb_word_chunk, __msb_word_chunk, __first_position);
			return __storage_it;
		}

		constexpr iterator
		_M_this_random_access_erase(const_iterator __first, const_sentinel __last) noexcept
		{
			// early check: are we deleting
			// everything?
			if (__first == this->begin() && __last == this->cend())
				{
					clear();
					return this->end();
				}
			difference_type __erase_bit_count  = ::std::distance(__first, __last);
			difference_type __erase_word_count = __erase_bit_count / __binary_digits_v<__base_value_type>;
			difference_type __erase_bit_shift  = __erase_bit_count % __binary_digits_v<__base_value_type>;
			__base_c_iterator __first_base_it  = __first.base();
			size_type __first_position         = __first.position();
			__base_iterator __first_storage_it =
			     _M_maybe_storage_bulk_erase(__first_base_it, __first_position, __erase_word_count);
			// are we out of bits?
			if (__erase_bit_shift == 0)
				{
					// then we're already done
					return iterator(::std::move(__first_storage_it), __first_position);
				}
			// we are not out of bits:
			// shift down the first, then do the rest
			__base_reference __first_storage_ref = *__first_storage_it;
			if (__first_position == 0)
				{
					__first_storage_ref >>= __erase_bit_shift;
				}
			else
				{
					// bit preserver is inclusive: subtract 1
					size_type __bit_pivot = __first_position - 1;
					__shift_right_preserve_right<__base_value_type>(
					     __first_storage_ref, __bit_pivot, __erase_bit_shift);
				}
			// shift down all other bits now
			__base_iterator __storage_last   = this->_M_storage_end();
			__base_iterator __storage_it     = __first_storage_it;
			__base_iterator __old_storage_it = __first_storage_it;

			++__storage_it;
			for (; __storage_it != __storage_last; ++__storage_it, (void)++__old_storage_it)
				{
					__base_reference __storage_ref     = *__storage_it;     // msb
					__base_reference __old_storage_ref = *__old_storage_it; // lsb
					__old_storage_ref                  = __replace_most_significant_bits_from<__base_value_type>(
                              __old_storage_ref, __storage_ref, __erase_bit_shift);
					__storage_ref >>= __erase_bit_shift;
				}
			// update bit count
			if (this->_M_bit_pos > static_cast<size_type>(__erase_bit_shift))
				{
					// simple rollback
					this->_M_bit_pos -= static_cast<size_type>(__erase_bit_shift);
				}
			else
				{
					// we're going back over a word,
					// so we need to remove the old word
					auto __erase_target = this->_M_storage_unwrapped().cend();
					--__erase_target;
					this->_M_storage_unwrapped().erase(__erase_target);
					// then adjust the bit position
					this->_M_bit_pos =
					     __binary_digits_v<__base_value_type> - (__erase_bit_shift - this->_M_bit_pos);
				}
			return iterator(::std::move(__first_storage_it), __first_position);
		}

		constexpr iterator
		_M_basic_erase(const_iterator __first, const_sentinel __last) noexcept
		{
			// we already checked if we were empty
			--__last;
			// is this the first iterator?
			// if so, this is our last iteration
			bool __the_last_time   = __last == __first;
			iterator __current_pos = this->erase(__last);
			for (; !__the_last_time;)
				{
					// __last is currently invalid
					// because we just killed it...
					__last = ::std::move(__current_pos);
					--__last;
					__the_last_time = __last == __first;
					__current_pos   = this->erase(__last);
				}
			return __current_pos;
		}
	};

} // namespace ITSY_BITSY_DETAIL_NAMESPACE

#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef ITSY_BITSY_DETAIL_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

// end of itsy/detail/bit_sequence.hpp

#include <vector>

namespace bitsy
{

	template<typename C>
	class bit_sequence : public ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_sequence<C> {
	private:
		using base_t = ::ITSY_BITSY_DETAIL_NAMESPACE::__bit_sequence<C>;
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
	};

} // namespace bitsy

// end of itsy/bit_sequence.hpp

// beginning of itsy/dynamic_bitset.hpp

#include <cstddef>

namespace bitsy
{
	template<typename T, typename Allocator = std::allocator<T>>
	class dynamic_bitset : public small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator> {
	private:
		using base_t = small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator>;
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

		using base_t::base_t;
	};

	template<typename T, typename Allocator = std::allocator<T>>
	class packed_dynamic_bitset : public packed_small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator> {
	private:
		using base_t = packed_small_bit_vector<T, default_small_buffer_size_v<T, Allocator>, Allocator>;
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

		using base_t::base_t;
	};
} // namespace bitsy

// end of itsy/dynamic_bitset.hpp

// end of itsy/bitsy.hpp

#endif // ITSY_BITSY_SINGLE_INCLUDE_HPP
