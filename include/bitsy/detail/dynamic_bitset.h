#ifndef __DYNAMIC_BITSET_H
#define __DYNAMIC_BITSET_H 1

#if defined(_MSC_VER) || (defined(__cplusplus) && __cplusplus >= 201703L)

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
#else
#include <bitsy/detail/bit_iterator.h>
#include <bitsy/detail/bit_view.h>
#include <bitsy/detail/bit_span.h>
#endif

#include <cstddef>
#include <type_traits>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{

  template<typename __C>
  class __basic_dynamic_bitset : private __bit_span<__C>
  {
  private:
    template<typename>
    friend class __bit_view;
    template<typename>
    friend class __bit_span;

    using __base_t = __bit_span<__C>;

  public:
    using difference_type   = typename __base_t::difference_type;
    using size_type         = typename __base_t::size_type;
    using value_type        = typename __base_t::value_type;
    using reference         = typename __base_t::reference;
    using iterator_category = typename __base_t::iterator_category;
    using iterator_concept  = typename __base_t::iterator_category;
    using pointer           = typename __base_t::pointer;
    using iterator          = typename __base_t::iterator;
    using sentinel          = typename __base_t::sentinel;
    using const_iterator    = typename __base_t::const_iterator;
    using const_sentinel    = typename __base_t::const_sentinel;

    // constructors
    // TODO: proper constructors
    using __base_t::__base_t;

    // assignment
    // TODO: proper operator=
    using __base_t::operator=;

    // modifiers
    using __base_t::flip;
    using __base_t::set;

    // observers
    using __base_t::all;
    using __base_t::any;
    using __base_t::base;
    using __base_t::count;
    using __base_t::none;
    using __base_t::population_count;
    using __base_t::size;
    using __base_t::test;

    using __base_t::operator[];

    using __base_t::begin;
    using __base_t::cbegin;
    using __base_t::cend;
    using __base_t::end;
  };

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // __DYNAMIC_BITSET_H
