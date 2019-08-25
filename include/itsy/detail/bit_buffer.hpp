#pragma once

#ifndef ITSY_BITSY_DETAIL_BIT_BUFFER_HPP
#define ITSY_BITSY_DETAIL_BIT_BUFFER_HPP 1

#if (defined(_MSC_VER)) || (defined(__cplusplus) && __cplusplus >= 201703L)

#include <itsy/detail/bit_iterator.hpp>

#include <cstddef>
#include <type_traits>

#include <itsy/detail/namespace_default_begin.hpp>

namespace ITSY_BITSY_DETAIL_NAMESPACE
{
	template<typename _Word, typename _Allocator>
	inline constexpr ::std::size_t
	  __recommended_word_size_v = sizeof(_Word) +
	                              sizeof(typename ::std::allocator_traits<_Allocator>::size_type);

	template<typename _Word,
	  ::std::size_t _Inline_Words = __recommended_word_size_v<_Word, ::std::allocator<_Word>>,
	  typename _Allocator         = ::std::allocator<_Word>>
	class __bit_buffer
	{
	public:
		using allocator = _Allocator;
		using pointer   = typename ::std::allocator_traits<allocator>::pointer;
		using size_type = typename ::std::allocator_traits<allocator>::size_type;

	private:
		allocator _M_alloc;

		struct _Sbo_storage
		{
			static constexpr ::std::size_t bit_count = __binary_digits_v<_Word>;
			_Word _M_buf[_Inline_Words];
		};
		struct _Storage
		{
			_Word* _M_ptr;
			::std::size_t _M_bit_size;
		};
		union _Either_storage
		{
			_Sbo_storage _M_buf;
			_Storage _M_ptr;
		} _M_buf_or_ptr;
	};

} // namespace ITSY_BITSY_DETAIL_NAMESPACE

#include <itsy/detail/namespace_default_end.hpp>

#endif // __cplusplus is on 20/2a or better

#endif // ITSY_BITSY_DETAIL_BIT_BUFFER_HPP
