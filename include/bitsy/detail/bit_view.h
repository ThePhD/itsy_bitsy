#ifndef __BIT_VIEW_H
#define __BIT_VIEW_H 1

#if (defined(_MSC_VER)) || (defined(__cplusplus) && __cplusplus >= 201703L)

#if defined(__GLIBCXX__) && __GLIBCXX__ > 20190901UL
#else
#include <bitsy/detail/bit_iterator.h>
#endif

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <utility>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

namespace __BIT_STRUCTURES_NAMESPACE
{

  template<typename __R>
  class __bit_view
  {
  private:
    template<typename>
    friend class __bit_span;
    template<typename>
    friend class __dynamic_bitset;

    using __base_iterator   = decltype(::std::begin(::std::declval<__R>()));
    using __base_sentinel   = decltype(::std::end(::std::declval<__R>()));
    using __base_c_iterator = decltype(::std::cbegin(::std::declval<__R>()));
    using __base_c_sentinel = decltype(::std::cend(::std::declval<__R>()));
    using __base_pointer    = typename ::std::iterator_traits<__base_iterator>::pointer;
    using __base_reference  = typename ::std::iterator_traits<__base_iterator>::reference;
    using __iterator        = __const_bit_iterator<__base_iterator>;
    using __sentinel        = __const_bit_iterator<__base_sentinel>;
    using __c_iterator      = __const_bit_iterator<__base_c_iterator>;
    using __c_sentinel      = __const_bit_iterator<__base_c_sentinel>;
    using __word_type       = typename ::std::iterator_traits<__base_iterator>::value_type;

    __R __storage;

  public:
    using difference_type   = typename ::std::iterator_traits<__base_iterator>::difference_type;
    using size_type         = ::std::make_unsigned_t<difference_type>;
    using reference         = __const_bit_reference<__base_reference, __word_type>;
    using pointer           = __const_bit_pointer<__base_pointer>;
    using iterator_category = typename ::std::iterator_traits<__base_iterator>::iterator_category;
    // TODO: strengthen guarantees by checking for `iterator_concept`
    // on iterator_traits
    using iterator_concept = iterator_category;
    using iterator         = __iterator;
    using sentinel         = __sentinel;
    using const_iterator   = __c_iterator;
    using const_sentinel   = __c_sentinel;

    template<typename __Arg, typename... __Args,
      ::std::enable_if_t<!__is_same_no_cvref_v<__bit_view, __Arg>, void*> = nullptr>
    __bit_view(__Arg&& __arg, __Args&&... __args) noexcept(
      noexcept(__R(::std::forward<__Arg>(__arg), ::std::forward<__Args>(__args)...)))
    : __storage(::std::forward<__Arg>(__arg), ::std::forward<__Args>(__args)...)
    {}

    __bit_view(const __bit_view& __right) noexcept(noexcept(__R(__right.__storage))) = default;
    __bit_view(__bit_view&& __right) noexcept(
      noexcept(__R(::std::move(__right.__storage)))) = default;

    __bit_view&
    operator                                               =(const __bit_view& __right) noexcept(
      noexcept(::std::declval<__R>() = __right.__storage)) = default;
    __bit_view&
    operator=(__bit_view&& __right) noexcept(
      noexcept(::std::declval<__R>() = ::std::move(__right.__storage))) = default;

    constexpr const __R&
    base() const& noexcept
    {
      return __storage;
    }

    constexpr __R&
      base() &
      noexcept
    {
      return __storage;
    }

    constexpr __R&&
      base() &&
      noexcept
    {
      return ::std::move(__storage);
    }

    constexpr bool
    test(difference_type __pos) const noexcept
    {
      return *::std::next(cbegin(), __pos);
    }

    constexpr bool operator[](difference_type __pos) const noexcept
    {
      return test(__pos);
    }

    constexpr difference_type
    count() const noexcept
    {
      return static_cast<difference_type>(size());
    }

    constexpr size_type
    count(bool __value) const noexcept
    {
      std::size_t __count = 0;
      for (const auto& __val : *this)
      {
        __count += (static_cast<bool>(__val) == __value) ? 1 : 0;
      }
      return __count;
    }

    constexpr size_type
    population_count() const noexcept
    {
      return count(true);
    }

    constexpr bool
    all() const noexcept
    {
      const __word_type __all_val = ~__word_type{};
      for (const auto& __val : __storage)
      {
        if (__val == __all_val)
        {
          continue;
        }
        return false;
      }
      return true;
    }

    constexpr bool
    any() const noexcept
    {
      const __word_type __zero_val{};
      for (const auto& __val : __storage)
      {
        if (__val == __zero_val)
        {
          continue;
        }
        return true;
      }
      return false;
    }

    constexpr bool
    none() const noexcept
    {
      const __word_type __zero_val{};
      for (const auto& __val : __storage)
      {
        if (__val == __zero_val)
        {
          continue;
        }
        return false;
      }
      return true;
    }

    constexpr size_type
    size() const noexcept
    {
      return ::std::size(__storage) * __binary_digits_v<__word_type>;
    }

    constexpr iterator
    begin() noexcept
    {
      return iterator(::std::begin(__storage));
    }

    constexpr sentinel
    end() noexcept
    {
      return sentinel(::std::end(__storage));
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
      return const_iterator(::std::cbegin(__storage));
    }

    constexpr const_sentinel
    cend() const noexcept
    {
      return const_sentinel(::std::cend(__storage));
    }
  };

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // __BIT_VIEW_H
