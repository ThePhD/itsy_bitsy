#ifndef __BIT_ITERATOR_H
#define __BIT_ITERATOR_H 1

#if defined(_MSC_VER) || (defined(__cplusplus) && __cplusplus >= 201703L)

#include <cstddef>
#include <type_traits>
#include <cassert>
#include <limits>
#include <climits>
#include <utility>
#include <iterator>

#ifndef __BIT_STRUCTURES_NAMESPACE
#define __BIT_STRUCTURES_NAMESPACE_DEFAULTED 1
#define __BIT_STRUCTURES_NAMESPACE __gnu_cxx
#endif // __BIT_STRUCTURES_NAMESPACE default

#include <bitsy/detail/binary_digits.h>

namespace __BIT_STRUCTURES_NAMESPACE
{

  template<typename __A, typename __B>
  constexpr inline bool __is_same_no_cvref_v =
    std::is_same_v<::std::remove_cv_t<std::remove_reference_t<__A>>,
      ::std::remove_cv_t<std::remove_reference_t<__B>>>;

  template<typename __Pos, typename __Mask>
  inline constexpr __Pos
  __mask_to_pos(__Mask __mask)
  {
    // if the mask is zero something has gone horribly wrong
    assert(__mask != static_cast<__Mask>(0));
    __Pos __pos = static_cast<__Pos>(0);
    while (__mask != static_cast<__Mask>(0))
    {
      ++__pos;
      __mask >>= 1;
    }
    return static_cast<__Pos>(__pos);
  }

  template<typename __Mask, typename __Pos>
  inline constexpr __Mask
  __pos_to_mask(__Pos __pos)
  {
    // position never exceeds the capacity to show it
    assert(__pos < __binary_digits_v<__Pos>);
    return static_cast<__Mask>(static_cast<__Pos>(1) << __pos);
  }

  // forward declarations
  class __bit_value;
  template<typename, typename>
  class __const_bit_reference;
  template<typename, typename>
  class __bit_reference;
  template<typename>
  class __bit_pointer;
  template<typename>
  class __const_bit_pointer;

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

    template<typename __WR, typename __M>
    constexpr __bit_value(const __bit_reference<__WR, __M>& __ref) noexcept
    : __bval(static_cast<bool>(__ref))
    {}

    template<typename __WR, std::enable_if_t<!__is_same_no_cvref_v<__WR, __bit_value>>* = nullptr>
    explicit constexpr __bit_value(__WR __val) noexcept : __bit_value(::std::move(__val), 0)
    {}

    template<class __WR>
    constexpr __bit_value(__WR __val, size_type __pos) noexcept
    : __bval((__val & __pos_to_mask<__mask_type>(__pos)) == 0)
    {}

    // assignment
    constexpr __bit_value&
    operator=(const __bit_value& r) noexcept = default;

    template<typename __WR, typename __M>
    constexpr __bit_value&
    operator=(const __bit_reference<__WR, __M>& __ref) noexcept
    {
      __bval = static_cast<bool>(__ref);
      return *this;
    }

    template<typename __WR>
    constexpr __bit_value&
    assign(__WR __val) noexcept
    {
      assign(__val, 0);
      return *this;
    }

    template<typename __WR>
    constexpr __bit_value&
    assign(__WR __val, size_type __pos) noexcept
    {
      __bval = (__val & __pos_to_mask<__mask_type>(__pos)) != 0;
      return *this;
    }

    // compound assignment
    constexpr __bit_value&
    operator&=(__bit_value __right) noexcept
    {
      __bval = __right.__bval;
      return *this;
    }

    constexpr __bit_value&
    operator|=(__bit_value __right) noexcept
    {
      __bval = __right.__bval;
      return *this;
    }
    constexpr __bit_value&
    operator^=(__bit_value __right) noexcept
    {
      __bval = __right.__bval;
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
      using std::swap;
      swap(__left.__bval, __right.__bval);
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

  template<typename __WordRef, typename __Mask>
  class __const_bit_reference
  {
  private:
    template<typename, typename>
    friend class __bit_reference;

    using __mask_type = __Mask;
    using __word_type = std::remove_cv_t<std::remove_reference_t<__WordRef>>;

    __WordRef __word;
    __mask_type __mask;

  public:
    using value_type = bool;
    using mask_type  = __mask_type;
    using size_type  = ::std::size_t;

    __const_bit_reference(__WordRef __val) noexcept : __const_bit_reference(__val, 0)
    {}

    __const_bit_reference(__WordRef __val, size_type __pos) noexcept
    : __word(__val), __mask(__pos_to_mask<__mask_type>(__pos))
    {}

    __const_bit_reference() noexcept : __word(), __mask(static_cast<__mask_type>(0))
    {}

    // assignment
    constexpr __const_bit_reference&
    operator=(const __const_bit_reference& other) noexcept = default;

    template<typename __WR, typename __M,
      ::std::enable_if_t<!::std::is_same_v<__WR, __WordRef> || !::std::is_same_v<__M, __Mask>>* =
        nullptr>
    constexpr __const_bit_reference&
    operator=(const __const_bit_reference<__WR, __M>& __right) noexcept
    {
      __word = static_cast<__WordRef>(__right.__word);
      __mask = static_cast<__mask_type>(__right.__mask);
    }

    // conversions
    operator bool() const noexcept
    {
      return (__word & __mask) != static_cast<__mask_type>(0);
    }

    // observers
    constexpr size_type
    position() const noexcept
    {
      return __mask_to_pos<size_type>(__mask);
    }

    constexpr mask_type
    mask() const noexcept
    {
      return __mask;
    }
  };

  template<typename __WordRef, typename __Mask>
  class __bit_reference : private __const_bit_reference<__WordRef, __Mask>
  {
  private:
    using __base_t    = __const_bit_reference<__WordRef, __Mask>;
    using __word_type = typename __base_t::__word_type;
    using __mask_type = typename __base_t::__mask_type;

  public:
    using value_type = bool;
    using mask_type  = __mask_type;
    using size_type  = ::std::make_unsigned_t<__mask_type>;

    using __base_t::__base_t;

    // assignment
    constexpr __bit_reference&
    operator=(__bit_value __val) noexcept
    {
      return this->operator=(__val.value());
    }
    constexpr __bit_reference&
    operator=(bool __val) noexcept
    {
      __word_type __mask = static_cast<__word_type>(__val ? 1 : 0) << position();
      this->__word = (this->__word) & (~mask);
      return *this;
    }

    // observers
    using __base_t::operator bool;
    using __base_t::mask;
    using __base_t::position;
  };

  template<typename __Pointer>
  class __const_bit_pointer
  {
  private:
    template<typename>
    friend class __bit_pointer;

    using __difference_type = typename ::std::iterator_traits<__Pointer>::difference_type;
    using __size_type       = ::std::make_unsigned_t<__difference_type>;
    using __word_type       = typename ::std::iterator_traits<__Pointer>::value_type;
    using __reference       = typename ::std::iterator_traits<__Pointer>::reference;

    __Pointer __base_it;
    __size_type __pos;

  public:
    // types
    using value_type      = __bit_value;
    using reference       = __const_bit_reference<__reference, __word_type>;
    using size_type       = __size_type;
    using difference_type = __difference_type;

    // constructors
    __const_bit_pointer() noexcept = default;

    constexpr __const_bit_pointer(const __const_bit_pointer&) noexcept = default;

    template<class __P, std::enable_if_t<!std::is_same_v<__Pointer, __P>>* = nullptr>
    constexpr __const_bit_pointer(const __const_bit_pointer<__P>& __right) noexcept
    : __base_it(static_cast<__Pointer>(__right.__base_it)), __pos(__right.__p)
    {}

    constexpr __const_bit_pointer(::std::nullptr_t) noexcept : __const_bit_pointer()
    {}

    explicit constexpr __const_bit_pointer(__Pointer __ptr) noexcept : __const_bit_pointer(__ptr, 0)
    {}

    constexpr __const_bit_pointer(__Pointer __ptr, size_type __p) noexcept
    : __base_it(__ptr), __pos(__p)
    {}

    // assignment
    constexpr __const_bit_pointer&
    operator=(const __const_bit_pointer&) noexcept = default;

    constexpr __const_bit_pointer& operator=(::std::nullptr_t) noexcept
    {
      __base_it = nullptr;
      __pos     = 0;
    }

    template<class __P, ::std::enable_if_t<!::std::is_same_v<__Pointer, __P>>* = nullptr>
    constexpr __const_bit_pointer&
    operator=(const __const_bit_pointer<__P>& __right) noexcept
    {
      this->__base_it = static_cast<__Pointer>(__right.__base_it);
      this->__pos     = static_cast<__Pointer>(__right.__pos);
      return *this;
    }

    // observers
    explicit constexpr operator bool() const noexcept
    {
      return this->operator*();
    }

    constexpr reference operator*() const noexcept
    {
      return reference(*__base_it, __pos);
    }

    constexpr __const_bit_pointer const* operator&() const noexcept
    {
      return this;
    }

    // comparison
    template<typename __RightIt>
    friend constexpr bool
    operator==(
      const __const_bit_pointer& __left, const __const_bit_pointer<__RightIt>& __right) noexcept
    {
      return __left.base() == __right.base() && __left.pos() == __left.pos();
    }

    template<typename __RightIt>
    friend constexpr bool
    operator!=(
      const __const_bit_pointer& __left, const __const_bit_pointer<__RightIt>& __right) noexcept
    {
      return __left.base() != __right.base() || __left.pos() != __left.pos();
    }

    template<typename __RightIt>
    friend constexpr bool
    operator<(
      const __const_bit_pointer& __left, const __const_bit_pointer<__RightIt>& __right) noexcept
    {
      if (__left.base() < __right.base())
      {
        return true;
      }
      if (__left.base() > __right.base())
      {
        return false;
      }
      return __left.pos() < __left.pos();
    }

    template<typename __RightIt>
    friend constexpr bool
    operator<=(
      const __const_bit_pointer& __left, const __const_bit_pointer<__RightIt>& __right) noexcept
    {
      if (__left.base() <= __right.base())
      {
        return true;
      }
      if (__left.base() > __right.base())
      {
        return false;
      }
      return __left.pos() <= __left.pos();
    }

    template<typename __RightIt>
    friend constexpr bool
    operator>(
      const __const_bit_pointer& __left, const __const_bit_pointer<__RightIt>& __right) noexcept
    {
      if (__left.base() > __right.base())
      {
        return true;
      }
      if (__left.base() < __right.base())
      {
        return false;
      }
      return __left.pos() > __left.pos();
    }

    template<typename __RightIt>
    friend constexpr bool
    operator>=(
      const __const_bit_pointer& __left, const __const_bit_pointer<__RightIt>& __right) noexcept
    {
      if (__left.base() >= __right.base())
      {
        return true;
      }
      if (__left.base() < __right.base())
      {
        return false;
      }
      return __left.pos() >= __left.pos();
    }
  };

  template<class __Pointer>
  class __bit_pointer : private __const_bit_pointer<__Pointer>
  {
  private:
    using __base_t    = __const_bit_pointer<__Pointer>;
    using __reference = typename __base_t::__reference;
    using __size_type = typename __base_t::__size_type;
    using __word_type = typename __base_t::__word_type;

  public:
    // types
    using value_type      = typename __base_t::value_type;
    using reference       = __bit_reference<__reference, __word_type>;
    using size_type       = __size_type;
    using difference_type = typename __base_t::difference_type;

    // constructors
    __bit_pointer() noexcept = default;

    constexpr __bit_pointer(const __bit_pointer&) noexcept = default;

    template<class __P, std::enable_if_t<!std::is_same_v<__Pointer, __P>>* = nullptr>
    constexpr __bit_pointer(const __bit_pointer<__P>& __right) noexcept
    : __bit_pointer(static_cast<const __base_t&>(__right))
    {}

    template<class __P, std::enable_if_t<!std::is_same_v<__Pointer, __P>>* = nullptr>
    constexpr __bit_pointer(const __const_bit_pointer<__P>& __right) noexcept
    : __base_t(static_cast<__Pointer>(__right.__base_it), __right.__p)
    {}

    constexpr __bit_pointer(::std::nullptr_t) noexcept : __base_t(nullptr)
    {}

    explicit constexpr __bit_pointer(__Pointer __ptr) noexcept : __bit_pointer(__ptr, 0)
    {}

    constexpr __bit_pointer(__Pointer __ptr, size_type __p) noexcept : __base_t(__ptr, __p)
    {}

    // assignment
    constexpr __bit_pointer&
    operator=(const __bit_pointer&) noexcept = default;

    constexpr __bit_pointer& operator=(::std::nullptr_t) noexcept
    {
      __base_t::operator=(nullptr);
      return *this;
    }

    // observers
    using __base_t::operator bool;

    constexpr reference operator*() const noexcept
    {
      return reference(*this->__base_it, this->__pos);
    }

    constexpr __bit_pointer const* operator->() const noexcept
    {
      return this;
    }

    constexpr __bit_pointer* operator->() noexcept
    {
      return this;
    }

    // comparison
    template<typename __RightIt>
    friend constexpr bool
    operator==(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) ==
             static_cast<const __const_bit_pointer<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator!=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) !=
             static_cast<const __const_bit_pointer<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator<(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) <
             static_cast<const __const_bit_pointer<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator<=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) <=
             static_cast<const __const_bit_pointer<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator>(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) >
             static_cast<const __const_bit_pointer<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator>=(const __bit_pointer& __left, const __bit_pointer<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) >=
             static_cast<const __const_bit_pointer<__RightIt>&>(__right);
    }
  };

  template<typename __It>
  class __const_bit_iterator
  {
  private:
    template<typename>
    friend class __bit_iterator;

    using __base_iterator   = __It;
    using __pointer         = typename ::std::iterator_traits<__base_iterator>::pointer;
    using __word_type       = typename ::std::iterator_traits<__base_iterator>::value_type;
    using __mask_type       = ::std::remove_cv_t<std::remove_reference_t<__word_type>>;
    using __difference_type = typename ::std::iterator_traits<__base_iterator>::difference_type;
    using __size_type       = ::std::make_unsigned_t<__difference_type>;
    using __word_ref_type   = typename ::std::iterator_traits<__base_iterator>::reference;

    __base_iterator __base_it;
    __size_type __pos;

  public:
    using iterator          = __const_bit_iterator;
    using iterator_category = typename ::std::iterator_traits<__base_iterator>::iterator_category;
    using value_type        = __bit_value;
    using difference_type   = __difference_type;
    using pointer           = __const_bit_pointer<__pointer>;
    using reference         = __const_bit_reference<__word_ref_type, __mask_type>;
    using size_type         = __size_type;

    // constructors
    constexpr __const_bit_iterator() noexcept                                    = default;
    constexpr __const_bit_iterator(const __const_bit_iterator& __right) noexcept = default;
    // default to least significant bit (0th)
    explicit constexpr __const_bit_iterator(__base_iterator __i) noexcept
    : __const_bit_iterator(::std::move(__i), 0)
    {}
    // __pos range: [0, binary_digits_v<]
    //   to represent lsb (0) to msb (31)
    constexpr __const_bit_iterator(__base_iterator __i, size_type __pos) noexcept
    : __base_it(__i), __pos(__pos)
    {}

    // assignment
    constexpr __const_bit_iterator&
    operator=(const __const_bit_iterator& __right) noexcept = default;

    // observers
    constexpr reference operator*() const noexcept
    {
      return reference(*__base_it, __pos);
    }

    constexpr pointer operator->() const noexcept
    {
      return pointer(__base_it, __pos);
    }

    constexpr reference operator[](difference_type n) const
    {
      __const_bit_iterator __shifted = *this + n;
      return *__shifted;
    }

    constexpr __base_iterator
    base() const noexcept
    {
      return __base_it;
    }

    constexpr size_type
    position() const noexcept
    {
      return __pos;
    }

    constexpr __mask_type
    mask() const noexcept
    {
      return __pos_to_mask<__mask_type>(__pos);
    }

    // arithmetic
    constexpr __const_bit_iterator&
    operator++()
    {
      ++__pos;
      if (__pos == __binary_digits_v<__word_type>)
      {
        __pos = 0;
        ++__base_it;
      }

      return *this;
    }

    constexpr __const_bit_iterator&
    operator--()
    {
      if (__pos == 0)
      {
        __pos = __binary_digits_v<__word_type> - 1;
        --__base_it;
      } else
      {
        --__pos;
      }

      return *this;
    }

    constexpr __const_bit_iterator
    operator++(int)
    {
      auto __saved = *this;
      ++__saved;
      return __saved;
    }

    constexpr __const_bit_iterator
    operator--(int)
    {
      auto __saved = *this;
      --__saved;
      return __saved;
    }

    constexpr __const_bit_iterator
    operator+(difference_type __n) const
    {
      auto __saved = *this;
      __saved += __n;
      return __saved;
    }

    constexpr __const_bit_iterator
    operator-(difference_type __n) const
    {
      auto __saved = *this;
      __saved -= __n;
      return __saved;
    }

    constexpr __const_bit_iterator&
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
      __pos += __bit_advancement;
      if (__pos > __binary_digits_v<__word_type>)
      {
        // put it back in the proper range
        __pos -= __binary_digits_v<__word_type>;
        // going forward by one extra since we
        // overflow binary digit count
        std::advance(__base_it, (__n / __binary_digits_v<__word_type>)+1);
        return *this;
      }

      std::advance(__base_it, __n / __binary_digits_v<__word_type>);
      return *this;
    }

    constexpr __const_bit_iterator&
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
      if (__bit_advancement > __pos)
      {
        // put it back in the proper range
        __pos = __binary_digits_v<__word_type> - __bit_advancement;
        // going forward by one extra since we
        // overflow binary digit count
        ++__it_advancement;
        std::advance(__base_it, -__it_advancement);
        return *this;
      }

      __pos -= __bit_advancement;
      std::advance(__base_it, -(__n / __binary_digits_v<__word_type>));
      return *this;
    }

    // comparison
    template<typename __RightIt>
    friend constexpr bool
    operator==(
      const __const_bit_iterator& __left, const __const_bit_iterator<__RightIt>& __right) noexcept
    {
      return __left.base() == __right.base() && __left.position() == __right.position();
    }

    template<typename __RightIt>
    friend constexpr bool
    operator!=(
      const __const_bit_iterator& __left, const __const_bit_iterator<__RightIt>& __right) noexcept
    {
      return __left.base() != __right.base() || __left.position() != __right.position();
    }

    template<typename __RightIt>
    friend constexpr bool
    operator<(
      const __const_bit_iterator& __left, const __const_bit_iterator<__RightIt>& __right) noexcept
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
    operator<=(
      const __const_bit_iterator& __left, const __const_bit_iterator<__RightIt>& __right) noexcept
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
    operator>(
      const __const_bit_iterator& __left, const __const_bit_iterator<__RightIt>& __right) noexcept
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
    operator>=(
      const __const_bit_iterator& __left, const __const_bit_iterator<__RightIt>& __right) noexcept
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
  };

  template<typename __It>
  class __bit_iterator : private __const_bit_iterator<__It>
  {
  private:
    using __base_t          = __const_bit_iterator<__It>;
    using __base_iterator   = typename __base_t::__base_iterator;
    using __pointer         = typename __base_t::__pointer;
    using __word_type       = typename __base_t::__word_type;
    using __mask_type       = typename __base_t::__mask_type;
    using __size_type       = typename __base_t::__size_type;
    using __difference_type = typename __base_t::__difference_type;
    using __word_ref_type   = typename __base_t::__word_ref_type;

  public:
    using iterator          = __bit_iterator;
    using iterator_category = typename ::std::iterator_traits<__base_iterator>::iterator_category;
    using value_type        = __bit_value;
    using difference_type   = __difference_type;
    using pointer           = __bit_pointer<__pointer>;
    using reference         = __bit_reference<__word_ref_type, __mask_type>;
    using size_type         = __size_type;

    // constructors
    using __base_t::__base_t;

    // assignment
    using __base_t::operator=;

    // observers
    constexpr reference operator*() const noexcept
    {
      return reference(*this->__base_it, this->__pos);
    }

    constexpr pointer operator->() const noexcept
    {
      return pointer(this->__base_it, this->__pos);
    }

    using __base_t::base;
    using __base_t::mask;
    using __base_t::position;

    // arithmetic
    constexpr reference operator[](difference_type n) const
    {
      __bit_iterator __shifted = *this;
      __shifted += n;
      return *__shifted;
    }

    constexpr __bit_iterator&
    operator++()
    {
      __base_t::operator++();
      return *this;
    }

    constexpr __bit_iterator&
    operator--()
    {
      __base_t::operator--();
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

    using __base_t::operator-;
    using __base_t::operator+;

    constexpr __bit_iterator&
    operator+=(difference_type __n)
    {
      __base_t::operator+=(__n);
      return *this;
    }

    constexpr __bit_iterator&
    operator-=(difference_type __n)
    {
      __base_t::operator-=(__n);
      return *this;
    }

    // comparison
    template<typename __RightIt>
    friend constexpr bool
    operator==(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) ==
             static_cast<const __const_bit_iterator<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator!=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) !=
             static_cast<const __const_bit_iterator<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator<(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) <
             static_cast<const __const_bit_iterator<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator<=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) <=
             static_cast<const __const_bit_iterator<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator>(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) >
             static_cast<const __const_bit_iterator<__RightIt>&>(__right);
    }

    template<typename __RightIt>
    friend constexpr bool
    operator>=(const __bit_iterator& __left, const __bit_iterator<__RightIt>& __right) noexcept
    {
      return static_cast<const __base_t&>(__left) >=
             static_cast<const __const_bit_iterator<__RightIt>&>(__right);
    }
  };

} // namespace __BIT_STRUCTURES_NAMESPACE

// clean up macros: don't leak anything
#ifdef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE_DEFAULTED
#undef __BIT_STRUCTURES_NAMESPACE
#endif // __BIT_STRUCTURES_NAMESPACE_DEFAULTED

#endif // __cplusplus is on 20/2a or better

#endif // __BIT_ITERATOR_H
