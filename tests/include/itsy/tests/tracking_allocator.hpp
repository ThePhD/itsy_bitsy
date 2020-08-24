// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See https://github.com/ThePhD/itsy_bitsy#using-the-library for documentation.

#pragma once

#ifndef ITSY_BITSY_TESTS_TRACKING_ALLOCATOR_HPP
#define ITSY_BITSY_TESTS_TRACKING_ALLOCATOR_HPP 1

#include <itsy/bitsy.hpp>

namespace bitsy::tests
{

	template<typename Allocator>
	class tracking_allocator : ::ITSY_BITSY_SOURCE_NAMESPACE::__ebco<Allocator>
	{
	private:
		using base_t            = ::ITSY_BITSY_SOURCE_NAMESPACE::__ebco<Allocator>;
		using base_alloc_traits = std::allocator_traits<Allocator>;

	public:
		using allocator_type     = tracking_allocator;
		using value_type         = typename base_alloc_traits::value_type;
		using pointer            = typename base_alloc_traits::pointer;
		using const_pointer      = typename base_alloc_traits::const_pointer;
		using void_pointer       = typename base_alloc_traits::void_pointer;
		using const_void_pointer = typename base_alloc_traits::const_void_pointer;
		using difference_type    = typename base_alloc_traits::difference_type;
		using size_type          = typename base_alloc_traits::size_type;
		using propagate_on_container_copy_assignment =
		     typename base_alloc_traits::propagate_on_container_copy_assignment;
		using propagate_on_container_move_assignment =
		     typename base_alloc_traits::propagate_on_container_move_assignment;
		using propogate_on_container_swap =
		     typename base_alloc_traits::propagate_on_container_swap;
		using is_always_equal = typename base_alloc_traits::is_always_equal;
		template<typename T>
		using rebind = tracking_allocator<typename base_alloc_traits::template rebind_alloc<T>>;

		tracking_allocator()                          = default;
		tracking_allocator(const tracking_allocator&) = default;
		tracking_allocator(tracking_allocator&&)      = default;
		tracking_allocator&
		operator=(const tracking_allocator&) = default;
		tracking_allocator&
		operator=(tracking_allocator&&) = default;

		tracking_allocator(const Allocator& alloc) : base_t(alloc)
		{
		}
		tracking_allocator(Allocator&& alloc) : base_t(::std::move(alloc))
		{
		}

		template<typename... Args>
		void
		construct(pointer at, Args&&... args)
		{
			base_alloc_traits::construct(this->get_allocator(), at, std::forward<Args>(args)...);
			++constructions_;
		}

		void
		destroy(pointer p)
		{
			base_alloc_traits::destroy(this->get_allocator(), p);
			++this->destructions_;
		}

		pointer
		allocate(size_type n)
		{
			pointer p = base_alloc_traits::allocate(this->get_allocator(), n);
			++this->allocations_;
			return p;
		}

		pointer
		allocate(size_type n, const_void_pointer hint)
		{
			pointer p = base_alloc_traits::allocate(this->get_allocator(), n, hint);
			++this->allocations_;
			return p;
		}

		void
		deallocate(pointer at, size_type n)
		{
			base_alloc_traits::deallocate(this->get_allocator(), at, n);
			++this->deallocations_;
		}

		difference_type
		alive() const
		{
			return this->constructions_ - this->destructions_;
		}

		difference_type
		allocations_alive() const
		{
			return this->allocations_ - this->deallocations_;
		}

		difference_type
		allocations() const
		{
			return this->allocations_;
		}

		difference_type
		deallocations() const
		{
			return this->deallocations_;
		}

		difference_type
		constructions() const
		{
			return this->constructions_;
		}

		difference_type
		destructions() const
		{
			return this->destructions_;
		}

	private:
		difference_type allocations_   = 0;
		difference_type deallocations_ = 0;
		difference_type constructions_ = 0;
		difference_type destructions_  = 0;

		Allocator&
		get_allocator()
		{
			return base_t::_M_get_value();
		}

		const Allocator&
		get_allocator() const
		{
			return base_t::_M_get_value();
		}
	};

} // namespace bitsy::tests

#endif // ITSY_BITSY_TESTS_TRACKING_ALLOCATOR_HPP
