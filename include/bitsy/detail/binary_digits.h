#ifndef __BINARY_DIGITS_H
#define __BINARY_DIGITS_H 1

#if defined(_MSC_VER) || (defined(__cplusplus) && __cplusplus >= 201703L)

#include <cstddef>
#include <type_traits>
#include <limits>
#include <climits>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{

  template<typename __T, typename = void>
  class __un_binary_digits
  : public ::std::integral_constant<::std::size_t, ::std::numeric_limits<__T>::digits>
  {
    static_assert(::std::is_integral_v<__T> || ::std::is_same_v<__T, ::std::byte>,
      "the type passed to binary_digits must be integral, an "
      "enumeration type, or std::byte.");
  };

  template<typename __T>
  class __un_binary_digits<__T, std::enable_if_t<::std::is_enum_v<__T>>>
  : public ::std::integral_constant<::std::size_t,
      ::std::numeric_limits<::std::underlying_type_t<__T>>::digits * CHAR_BIT>
  {
    static_assert(
      ::std::is_integral_v<__T> || ::std::is_same_v<__T, ::std::byte> || ::std::is_enum_v<__T>,
      "the type passed to binary_digits must be integral, an "
      "enumeration type, or std::byte.");
  };

  template<typename __T>
  class __binary_digits
  : public __un_binary_digits<::std::remove_cv_t<::std::remove_reference_t<__T>>>
  {
  };

  template<typename __T>
  constexpr inline auto __binary_digits_v = __binary_digits<__T>::value;

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // __BINARY_DIGITS_H
