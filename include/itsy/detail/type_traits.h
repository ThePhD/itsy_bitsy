#ifndef ITSY_BITSY_DETAIL_TYPE_TRAITS_H
#define ITSY_BITSY_DETAIL_TYPE_TRAITS_H 1

#if (defined(_MSC_VER)) || (defined(__cplusplus) && __cplusplus >= 201703L)

#include <type_traits>
#include <functional>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{
#if defined(__GLIBCXX__)

	template<template<typename...> class _Op, class... _Args>
	using __is_detected = ::std::__detector<::std::__nonesuch, void, Op, Args...>::value_t;

	template<template<typename...> class Op, class... Args>
	using __detected_t = typaname ::std::__detector<::std::__nonesuch, void, Op, Args...>::type;

	template<class Default, template<class...> class Op, class... Args>
	using __detected_or = ::std::__detector<Default, void, Op, Args...>;

	template<template<typename...> class _Op, typename... _Args>
	inline constexpr bool __is_detected_v = __is_detected<_Op, _Args...>::value;

	template<typename _Type>
	using __unwrap = ::std::__inv_unwrap<_Type>;

	template<typename _Type>
	using __unwrap_t = typename __unwrap<_Type>::type;

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

#endif

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_TYPE_TRAITS_H
