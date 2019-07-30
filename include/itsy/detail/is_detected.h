#ifndef ITSY_BITSY_DETAIL_IS_DETECTED_H
#define ITSY_BITSY_DETAIL_IS_DETECTED_H 1

#if (defined(_MSC_VER)) || (defined(__cplusplus) && __cplusplus >= 201703L)

#if defined(__GLIBCXX__) || defined(_LIBCPP_VERSION)
#include <experimental/type_traits>
#else
#endif


#include <type_traits>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{
#if defined(__GLIBCXX__) || defined(_LIBCPP_VERSION)

	template<template<typename...> class _Op, typename... _Args>
	using __is_detected = ::std::experimental::is_detected<_Op, _Args...>;

	template<template<typename...> class _Op, typename... _Args>
	constexpr bool __is_detected_v = ::std::experimental::is_detected<_Op, _Args...>::value;

#else

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

#endif

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_IS_DETECTED_H
