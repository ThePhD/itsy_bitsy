// itsy.bitsy
//
//  Copyright ⓒ 2019-present ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#include <testsuite_hooks.h>

#include <itsy/bitsy.hpp>

#include <cstddef>
#include <cstdint>

TEMPLATE_TEST_CASE("bit_iterator with pointer tests", "[bit_iterator<T*>]", std::uint64_t,
  std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t, std::int16_t,
  std::int8_t, char32_t, char16_t, char, unsigned char, signed char, std::size_t, std::ptrdiff_t)
{
	TestType value = static_cast<TestType>(0x5);
	bitsy::bit_iterator<TestType*> first(std::addressof(value), 0);
	bitsy::bit_iterator<TestType*> last(std::addressof(value) + 1, 0);
	VERIFY(first != last);
	VERIFY(first.base() != last.base());
	VERIFY_FALSE(first == last);
	VERIFY_FALSE(first.base() == last.base());
	VERIFY(first.position() == 0);
	VERIFY(last.position() == 0);
	SECTION("operator[]")
	{
		bool backwards0 = last[-static_cast<std::ptrdiff_t>(bitsy::binary_digits_v<TestType>)];
		bool backwards1 = last[-static_cast<std::ptrdiff_t>(bitsy::binary_digits_v<TestType>) + 1];
		bool backwards2 = last[-static_cast<std::ptrdiff_t>(bitsy::binary_digits_v<TestType>) + 2];
		bool backwards3 = last[-static_cast<std::ptrdiff_t>(bitsy::binary_digits_v<TestType>) + 3];
		bool backwards4 = last[-static_cast<std::ptrdiff_t>(bitsy::binary_digits_v<TestType>) + 4];
		bool backwards5 = last[-static_cast<std::ptrdiff_t>(bitsy::binary_digits_v<TestType>) + 5];
		bool backwards6 = last[-static_cast<std::ptrdiff_t>(bitsy::binary_digits_v<TestType>) + 6];
		VERIFY(backwards0);
		VERIFY_FALSE(backwards1);
		VERIFY(backwards2);
		VERIFY_FALSE(backwards3);
		VERIFY_FALSE(backwards4);
		VERIFY_FALSE(backwards5);
		VERIFY_FALSE(backwards6);
	}
	SECTION("iteration")
	{
		bitsy::bit_iterator<TestType*> it = first;
		std::size_t i                     = 0;
		for (; i < bitsy::binary_digits_v<TestType>; ++i, ++it)
			{
				if (i < 4)
					{
						bool val          = *it;
						bool expected_val = (i % 2) == 0;
						VERIFY(val == expected_val);
					}
			}
		VERIFY(i == bitsy::binary_digits_v<TestType>);
		VERIFY(it == last);
	}
	SECTION("modification")
	{
		bitsy::bit_iterator<TestType*> it = first;
		std::size_t i                     = 0;
		for (; i < bitsy::binary_digits_v<TestType>; ++i, ++it)
			{
				bitsy::bit_reference<TestType&, TestType> val_ref = *it;
				bool initial_val                                  = val_ref;
				bool expected_initial_val                         = (i < 4) ? (i % 2) == 0 : false;
				VERIFY(initial_val == expected_initial_val);

				val_ref.flip();
				bool flip_val          = val_ref;
				bool expected_flip_val = !expected_initial_val;
				VERIFY(flip_val == expected_flip_val);
				VERIFY(flip_val != initial_val);

				it->flip();
				bool flip_flip_val          = val_ref;
				bool expected_flip_flip_val = !expected_flip_val;
				VERIFY(flip_flip_val == expected_flip_flip_val);
				VERIFY(flip_flip_val == initial_val);
				VERIFY(flip_flip_val != flip_val);

				val_ref.set();
				bool empty_set_val          = val_ref;
				bool expected_empty_set_val = true;
				VERIFY(empty_set_val == expected_empty_set_val);

				it->set(false);
				bool set_false_val          = val_ref;
				bool expected_set_false_val = false;
				VERIFY(set_false_val == expected_set_false_val);

				val_ref.set(true);
				bool set_true_val          = val_ref;
				bool expected_set_true_val = true;
				VERIFY(set_true_val == expected_set_true_val);

				it->reset();
				bool reset_val          = val_ref;
				bool expected_reset_val = false;
				VERIFY(reset_val == expected_reset_val);

				*it                     = initial_val;
				bool initial_val_it_set = val_ref;
				VERIFY(initial_val_it_set == initial_val);
				VERIFY(initial_val_it_set == expected_initial_val);
			}
		VERIFY(i == bitsy::binary_digits_v<TestType>);
		VERIFY(it == last);
	}
}
