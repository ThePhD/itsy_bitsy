> 🎵 And the itsy-bitsy spider,  
> 🎶 climbed up the spout again...

# 🕸️ itsy.bitsy 🕸️

`itsy.bitsy` is a library for working with and manipulating bits. It comes with 3 different pertinent abstraction layers:

- Bit Sequences
  - A family of types contained in the `bitsy::bit_sequence<Container>` class template.
  - Supports having reference wrapped containers as well, such as `bitsy::bit_sequence<std::reference_wrapper<Container>>`.
- Bit Ranges
  - A family of types contained in the `bitsy::bit_view<Range, Bounds>` class template.
  - `Range` can be any range type, owning or non-owning. For the class to be effective, it should be a non-owning range.
  - `Bounds` can be any type that provides a `begin_position(const R&)` and `end_position(const R&)` functions, or just one of the default ones contained in the library such as `bitsy::bit_bounds<FirstN, LastN>`, `bitsy::word_bit_bounds`, or `bitsy::dynamic_bit_bounds`.
- Bit Iterators
  - An iterator over a bits of a `word` type. A `word` type is one of the fundamental integer types, character type, or enumeration types.
  - Contains `bitsy::bit_iterator` `bitsy::bit_reference`, `bitsy::bit_pointer`, and `bitsy::bit_value` types as well.



# Using the Library

Each higher layer of this library builds on top of the lower layers. We will start at the top -- with wrapping, owning containers -- and progress steadily downward.

## Bit Sequence

`bitsy::bit_sequence<Container>` is an owning sequence container adaptor. It can be verbose to type out the whole container, so instead one can use the alias `dynamic_bitset<Type>`, where `Type` is the underlying type put in some form of sequence container selected by the implementation (generally a `vector` or a `vector`-alike). It can be used like so:

```cpp
#include <itsy/bitsy.hpp>

#include <cassert>

int main () {
	// construct with initializer list
	bitsy::bit_sequence<std::vector<std::size_t>> bits{
		false, true, true, false, false
	};
	// construct from iterators just like other containers
	bitsy::bit_sequence<std::vector<std::size_t>> other_bits(
		bits.cbegin(), bits.cend();
	);

	// can compare
	assert(bits == other_bits);
	assert(!(bits != other_bits));

	// insertion
	bits.push_back(false);
	bits.insert(bits.begin() + 2, {true, true});
	assert(bits.size() == 8);
	assert(bits.count(true) == 4);

	// erasure
	bits.erase(bits.begin() + 1, bits.begin() + 3);
	assert(bits.size() == 6);
	assert(bits.popcount() == 2);

	// comparison works exactly the same
	assert(bits != other_bits);
	assert(!(bits == other_bits));

	return 0;
}
```

There is a convenience alias -- `bitsy::dynamic_bitset<T, Allocator>`, which defaults to some `std::vector<T, Allocator>`-alike storage. See the below section on future work for additional containers for the hope of what the default choice of container for this convenience alias should use:

```cpp
#include <itsy/bitsy.hpp>

int main () {
	bitsy::dynamic_bitset<std::size_t> bits{false, true, true, false, false};

	/* bit work here! */

	return 0;
}
```

Additionally, one can move storage directly into the bit sequence by using the `std::in_place` constructors:

```cpp
#include <itsy/bitsy.hpp>

#include <cstdint>
#include <cassert>

int main () {
	std::vector<std::uint32_t> words{ 0xff00ff00, 0xff00ff00 };
	bitsy::bit_sequence<std::vector<std::uint32_t>> bits(std::in_place, std::move(words));

	const std::size_t bits_size = bits.size();
	
	// size of the container is 2 words
	assert(bits_size == bitsy::binary_digits_v<std::uint32_t> * 2);
	assert(bits_size == 64);

	// assert 16-bit pattern
	for (std::size_t index = 0; index < bits_size; ++index) {
		if ((index % 32) < 16) {
			assert(!bits[index]);
		}
		else {
			assert(!bits[index]);
		}
	}

	return 0;
}
```

## Bit View

The types at this layer sit below `bit_sequence` in terms of abstraction power. `bit_view<Range, Bounds>` is the type which views a set of bits and provides a potentially mutable view of those bits. It cannot `insert`/`erase` into the underlying range, but supports in-place modifications and mutability. For example, if the `Range` is a `std::span<T>`, then the type is mutable:

```cpp
#include <itsy/bitsy.hpp>

#include <string>
#include <span>
#include <cassert>

int main () {
	std::u8string str = u8"Howdy!";
	// arguments get forwarded directly
	// to underlying range constructor
	bit_view<std::span<char8_t>> str_bits(str);

	// iterators
	auto bits_it = bits.begin();
	assert(bits_it.position() == 0);
	assert(*bits_it == bitsy::bit0);
	++bits_it;
	assert(bits_it.position() == 1);
	assert(*bits_it == bitsy::bit1);
	bits_it += 3;
	assert(bits_it.position() == 4);
	assert(*bits_it == bitsy::bit0);
	// flip a single bit
	// pointed to by `bits_it`
	bits_it->flip();
	assert(*bits_it == bitsy::bit1);

	return 0;
}
```

But if the `Range` is something like a `std::string_view` or a `std::span<const T>`, whose iterators and interface is immutable, `bit_view` becomes immutable as well:

```cpp
#include <itsy/bitsy.hpp>

#include <span>
#include <cassert>

int main () {
	std::vector<std::size_t> storage{ 0, 1 };
	bitsy::bit_view<std::span<const std::size_t>> b(storage);

	// compiler error!
	(*b.begin()) = true;

	return 0;
}
```

For `bit_view<Range, Bounds>`, the optional `Bounds` template parameter can be used to specify very specific extents:

```cpp
#include <itsy/bitsy.hpp>

#include <cassert>

int main () {
	std::array<std::uint32_t, 2> storage{
		// 0xFBFF;
		// (MSB) 0b‭1111101111111111‬ (LSB)
		0x0000FBFF, 
		0xFFFFFFFF 
	};
	using range_t = std::span<std::uint32_t>;
	using bounds_t = bitsy::bit_bounds<10, 22>;
	bitsy::bit_view<span_t, bounds_t> view_specific_bits(
		storage.data(), storage.size()
	);

	assert(view_specific_bits.size() == 12);
	// 0th bit of biew is 10th bit,
	// 10th bit of 0xFBFF is false
	assert(view_specific_bits[0] == bitsy::bit0);

	return 0;
}
```

And, as previously stated, it can be used at compile-time and in constant-evaluated contexts:

```cpp
#include <itsy/bitsy.hpp>

#include <string_view>
#include <cassert>

int main () {
	static constexpr unsigned data[] = { 0b0001, 0b0010 };
	static constexpr bitsy::bit_view<std::basic_string_view<unsigned>> data_bits(&data[0], 2);

	static_assert(data_bits[0], "First bit is not true (expected: true)!");
	static_assert(!data_bits.test(1), "Second bit is true  (expected: false)!");
	static_assert(*(data_bits.begin() + bitsy::binary_digits_v<unsigned> + 1),
	  "Second bit in second word is not true (expected: true)!");
	static_assert(data_bits.size() == (sizeof(unsigned) * CHAR_BIT * 2),
	  "The size of the bit view is not 2 x unsigned");
	static_assert(data_bits.size() == (bitsy::binary_digits_v<unsigned> * 2),
	  "The size of the bit view is not 2 x unsigned");
	static_assert(!data_bits[3].value(), "The bit is true (expected: false)!");

	return 0;
}
```

# Future Work

There are quite a lot of optimizations, additional underlying data structures, general improvements, and other things to do here.


### MSVC is not constexpr friendly

MSVC has issues with `constexpr` and their intrinsics, and they do not yet have `std::is_constant_evaluated`. As such, the `bitsy::first(l/r)_(zero/one)`, `bitsy::count(l/r)_(zero/one)` and `bitsy::popcount` intrinsic functions -- while `constexpr` -- are also implemented in some of the most braindead and plain manners possible. It would be nice to add `if constexpr()` blocks for implementations in the `__basic_X` version of these functions that use smarter bit twiddling tricks. This is done for one of the intrinsics, but should be extended to the others.

GCC and Clang only use the `__basic_X` loop versions if the type is too big to fit in one of their `unsigned`, `unsigned long`, or `unsigned long long` intrinsics.


### Putting It Directly in libc++ Too

The 2019 Google Summer of Code saw this library having an implementation placed towards libstdc++. The patch is out, and progress will hopefully be made over the coming months to get a version of it firmly in libstdc++ and fully integrated.

It would be nice to make much of the same available in libc++ as well, with the goal of improving the bit iterator situation there. There is no prior art for doing such a thing; libc++ is not one for many extensions, unlike libstdc++ which features quite a few extended features. Perhaps performance data can persuade them that having a concrete `bit_iterator` exposed by this library would be highly beneficial to them.


### Strong Exception Safety

Currently, `basic_bit_sequence` does not exhibit strong exception safety (not because the library tries and fails, it just doesn't `try`). This is something that should probably fixed soon, to make sure this is usable in exception-heavy code.

Likewise, the code should also be usable in a `-fno-exceptions` situation.


### Small Bit Buffer, Small Buffer

It has been a long time coming, and this bit library makes it all the more apparent and useful. There needs to be two additional container types implemented (and, perhaps in the future, proposed to the standard):

- `template <typename T, std::size_t BufferWords, typename Allocator> small_bit_buffer;`
  - This class provides the "small buffer optimization" with a customizable buffer size to be stored with the container, with the exception that this keeps track of its size by-the-bit and prevents a `value_type` of `bitsy::bit_value`.
  - `small_bit_buffer<T, 0, Allocator>` is morally and functionally equivalent in iterator guarantees and storage requirements as `std::vector<bool>`, just without the ugly specialization of `vector`.
  - Otherwise, `small_bit_buffer<T, N, Allocator>` produces a type which buffers up to `N` elements of type `T` in some implementation-defined manner while maintaining a `.size()` internally as the number of bits rather than the number of words. Iterator invalidation rules change and become similar to `std::basic_string`'s iterator invalidation rules.
- `template <typename T, std::size_t BufferWords, typename Allocator> small_buffer;`
  - This class provides the "small buffer optimization" with a customizable buffer size to be stored with the container.
  - `small_buffer<T, 0, Allocator>` is morally and functionally equivalent in iterator guarantees and storage requirements as `std::vector<T>`.
  - Otherwise, `small_buffer<T, N, Allocator>` produces a type which buffers up to `N` elements of type `T` in some implementation-defined manner. Iterator invalidation rules change and become similar to `std::basic_string`'s iterator invalidation rules.

Once these types exist, they can be used as the default backing storage of 


### Optimization Work

- There is a need to make the `bit_equal` and `std::equal` algorithms perform just as fast as their `memcmp` counterparts. The answer why it does not optimize out as cleanly will likely lie in an analysis of both the output assembly and any intermediate representation available from the compiler (LLVM and GCC can help obtain this kind of information). See the benchmarks for more details.
- Optimizations for `bit_iterator<T>`s that have different underlying `It` types is very much pertinent to what is happening here. The optimizations are very much done plainly and only work on homogenous iterators; it would be great to work on `bit_iterator`s that do not view the same `value_type` in the slightest.



# Acknowledgements

A huge thanks to Dr. Vincent Reverdy for sponsoring and helping with this work. An enormous thank you to Jonathan Wakely, Thomas Rodgers, and Ville Voutilainen for watching over my work during the Summer of Code 2019 through the Free Software Foundation and GNU Compiler Collection project.

Many thanks to the Blessed Guardian, Morwenn, for watching over my commits and cautioning me of my occasional derps.

Thank you to Corentin Jabot for changing the name "Extents" to "Bounds" to better represent the begin/end type for `bit_view`.
