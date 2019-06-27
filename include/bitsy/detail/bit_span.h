#ifndef __BIT_SPAN_H
#define __BIT_SPAN_H 1

#if defined(_MSC_VER) || (defined(__cplusplus) && __cplusplus >= 201703L)

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
#else
#include <bitsy/detail/bit_iterator.h>
#include <bitsy/detail/bit_view.h>
#endif

#include <cstddef>
#include <type_traits>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{

  template<typename __R>
  class __bit_span : private __bit_view<__R>
  {
  private:
    template<typename>
    friend class __bit_view;
    template<typename>
    friend class __dynamic_bitset;

    using __base_t          = __bit_view<__R>;
    using __base_iterator   = typename __base_t::__base_iterator;
    using __base_sentinel   = typename __base_t::__base_sentinel;
    using __base_c_iterator = typename __base_t::__base_c_iterator;
    using __base_c_sentinel = typename __base_t::__base_c_sentinel;
    using __base_pointer    = typename __base_t::__base_pointer;
    using __base_reference  = typename __base_t::__base_reference;
    using __iterator        = __bit_iterator<__base_iterator>;
    using __sentinel        = __bit_iterator<__base_sentinel>;
    using __c_iterator      = __const_bit_iterator<__base_c_iterator>;
    using __c_sentinel      = __const_bit_iterator<__base_c_sentinel>;
    using __word_type       = typename __base_t::__word_type;

  public:
    using difference_type   = typename ::std::iterator_traits<__base_iterator>::difference_type;
    using size_type         = ::std::make_unsigned_t<difference_type>;
    using value_type        = __bit_value;
    using reference         = __bit_reference<__base_reference, __word_type>;
    using pointer           = __bit_pointer<__base_pointer>;
    using iterator_category = typename __base_t::iterator_category;
    // TODO: strengthen guarantees by checking for `iterator_concept`
    // on iterator_traits
    using iterator_concept = iterator_category;
    using iterator         = __iterator;
    using sentinel         = __sentinel;
    using const_iterator   = __c_iterator;
    using const_sentinel   = __c_sentinel;

    // constructors
    using __base_t::__base_t;

    // assignment
    using __base_t::operator=;

    // modifiers
    constexpr void
    set(size_type __pos = 0, bool __val = true) noexcept
    {
      auto it = begin();
      std::advance(it, __pos);
      *it = __val;
    }

    constexpr void
    set(size_type __pos, size_type __len, bool __val = true) noexcept
    {
      auto it = begin();
      for (; __len-- > 0; ++it)
      {
        *it = __val;
      }
    }

    constexpr void
    flip(size_type __pos = 0) noexcept
    {
      auto it = begin();
      std::advance(it, __pos);
      auto ref = *it;
      ref      = !static_cast<bool>(ref);
    }

    constexpr void
    flip(size_type __pos, size_type __len) noexcept
    {
      auto it = begin();
      for (; __len-- > 0; ++it)
      {
        auto ref = *it;
        ref      = !static_cast<bool>(ref);
      }
    }

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

    constexpr iterator
    begin() noexcept
    {
      return iterator(::std::begin(this->__storage));
    }

    constexpr sentinel
    end() noexcept
    {
      return sentinel(::std::end(this->__storage));
    }

    constexpr const_iterator
    begin() const noexcept
    {
      return cbegin();
    }

    constexpr const_sentinel
    end() const noexcept
    {
      return cend();
    }

    constexpr const_iterator
    cbegin() const noexcept
    {
      return const_iterator(::std::cbegin(this->__storage));
    }

    constexpr const_sentinel
    cend() const noexcept
    {
      return const_sentinel(::std::cend(this->__storage));
    }
  };

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // __BIT_SPAN_H
