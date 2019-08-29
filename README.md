> 🎵 And the itsy-bitsy spider,  
> 🎶 climbed up the spout again...

# 🕸️ itsy.bitsy 🕸️

`itsy.bitsy` is a library for working with and manipulating bits. It comes with 3 different pertinent abstraction layers:

- Bit Sequences
  - A family of types contained in the `bitsy::bit_sequence<Container>` class template.
  - Supports having reference wrapped containers as well, such as `bitsy::bit_sequence<std::reference_wrapper<Container>>`.
- Bit Ranges
  - A family of types contained in the `bitsy::bit_view<Range, Bounds>` class template.
  - `Range` can be any range type. For the class to work efficiently and keep with the ideals set out in `std::ranges`, it should be a non-owning range.
  - `Bounds` can be any type that provides a `begin_position(const R&)` and `end_position(const R&)` functions, or just one of the default ones contained in the library such as `bitsy::bit_bounds<FirstN, LastN>`, `bitsy::word_bit_bounds`, or `bitsy::dynamic_bit_bounds`.
- Bit Iterators
  - An iterator over a bits of a `word` type. A `word` type is one of the fundamental integer types, character type, or enumeration types.
  - Contains `bitsy::bit_iterator` `bitsy::bit_reference`, `bitsy::bit_pointer`, and `bitsy::bit_value` types as well.



# Using the Library

Each higher layer of this library builds on top of the lower layers. We will start at the top -- with wrapping, owning containers -- and progress steadily downward. The library is also a header-only, linker-hassle free library. It is straightforward to either add the include paths [include/](https://github.com/ThePhD/itsy_bitsy/tree/master/include), or include the CMake of the top-level directory by using `add_subdirectory`.


## Bit Sequence

`bitsy::bit_sequence<Container>` is an owning sequence container adaptor. It can be used like so:

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

There is a convenience alias -- `bitsy::dynamic_bitset<T, Allocator>`, which defaults to some `std::vector<T, Allocator>`-alike storage. See the below section on [future work with small buffers](#small-buffer) for additional containers for the hope of what the default choice of container for this convenience alias should use:

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
		if ((index % 16) < 8) {
			assert(!bits[index]);
		}
		else {
			assert(bits[index]);
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
	std::string str = "Howdy!";
	std::cout << str << std::endl;
	// arguments get forwarded directly
	// to underlying range constructor
	bitsy::bit_view<std::span<char>> str_bits(str);

	// iterators
	auto bits_it = str_bits.begin();
	assert(bits_it.position() == 0);
	assert(*bits_it == bitsy::bit0);
	++bits_it;
	assert(bits_it.position() == 1);
	assert(*bits_it == bitsy::bit0);
	bits_it += 4;
	assert(bits_it.position() == 5);
	assert(*bits_it == bitsy::bit0);
	// flip a single bit
	// pointed to by `bits_it`
	bits_it->flip();
	assert(*bits_it == bitsy::bit1);

	// we flipped the ASCII bit
	// for a capital letter!
	std::cout << str << std::endl;
	assert(str == "howdy!");

	return 0;
}
```

But if the `Range` is something like a `std::string_view` or a `std::span<const T>`, whose iterators and interface is immutable, `bit_view` becomes immutable as well:

```cpp
#include <itsy/bitsy.hpp>

#include <cassert>

#include <span>
#include <cstdint>

int main() {
	std::vector<std::uint16_t> storage{ 0, 0, 0 };
	bitsy::bit_view<std::span<const std::uint16_t>> bits(storage);

	assert(bits.size() == 48);

	// the below will trigger a compiler error,
	// thus preserving const-safety
	(*bits.begin()) = true;
	bits[16] = bitsy::bit1;
	bits.begin()->flip();

	// can use auto, just showing the actual type
	for (bitsy::bit_reference<const std::uint16_t&> bit_ref : bits) {
		bit_value value = bit_ref;
		assert(value.value()); // returns the `bool` value
		// cannot use mutable methods: 
		// compiler will error below!
		bit_ref.flip();
		bit_ref.set();
		bit_ref.reset();
	}

	return 0;
}
```

For `bit_view`, the optional second `Bounds` template parameter can be used to specify very specific extents:

```cpp
#include <itsy/bitsy.hpp>

#include <string_view>
#include <cassert>

int main () {
	std::array<std::uint32_t, 2> storage{
		// 0xFBFF;
		// (MSB) 0b‭1111101111111111‬ (LSB)
		0x0000FBFF, 
		0xFFFFFFFF 
	};
	using range_t = std::basic_string_view<std::uint32_t>;
	using bounds_t = bitsy::bit_bounds<10, 22>;
	bitsy::bit_view<range_t, bounds_t> view_specific_bits(
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

All methods found on a `bit_view` also exist on all variants of `bit_sequence`.


## Bit Iterator

`bitsy::bit_iterator<Iterator>` is a class template. It is considered the "low level" portion of this library. It takes an iterator to increment when it iterates from `[ 0, bitsy::binary_digits_v<underlying_value_type> )`. Generally, what that means is that a `std::uint32_t` will iterate from 0 to 31 inclusive, an `unsigned long long` (depending on platform specifics) might go from 0 to 63 inclusive, and so on and so forth. This can be inspected with the `.position()` and `.mask()` properties:

```cpp
#include <itsy/bitsy.hpp>

#include <random>
#include <limits>
#include <algorithm>
#include <iostream>

int main() {
	using sequence = std::list<int>;
	sequence seq{ 100, 0 };
	std::random_device rd{};
	std::default_random_engine rand_engine(rd());
	std::uniform_int_distribution<int> rand_distribution(
	  std::numeric_limits<int>::max() - 32, std::numeric_limits<int>::max());
	std::generate_n(seq.begin(), seq.size(), [&]() { return rand_distribution(rand_engine); });

	bitsy::bit_iterator<typename sequence::const_iterator> first(seq.cbegin(), 0);
	bitsy::bit_iterator<typename sequence::const_iterator> last(seq.cend(), 0);

	if (auto it = std::find(first, last, bitsy::bit0); it != last) {
		bitsy::bit_reference<typename sequence::const_reference> ref = *it;
		std::cout << "Found a 0 bit at the " << std::distance(it, last) << " element in the "
							<< seq.size() << ", at bit position" << ref.position() << "( mask: " << ref.mask()
							<< " | applied to value: " << *it.base() << ")" << std::endl;
	}

	return 0;
}
```


Its `value_type` is a `bit_value`, and its reference type is a `bit_reference<WordType, MaskType>`. `bit_reference` keeps on the reference and the position/mask value. `bit_value` discards the reference and mask type, and only represents a single bit value. As seen from the above example, using the basic `bit_iterator` API is verbose. Use of the top-level ranges API or similar when possible is **highly** encouraged. This layer is generally only useful for catching function overloads, or for creating your own ranges/containers that iterate over bits.


# Testing

Testing can be turned on by using `ITSY_BITSY_TESTS`, and examples will also be tested if `ITSY_BITSY_EXAMPLES` is turned on. The tests do not take long to run at all on both Debug or Release. The tests also have dependencies, which can be automatically obtained with `git submodule update --init`.



# Benchmarks

There is an extensive benchmarking suite contained in this repository. It can be turned on by setting `ITSY_BITSY_BENCHMARKS` when building the library. It requires a few dependencies to run, which can be obtained by making sure the repository has its dependencies set with `git submodule update --init` in the cloned directory.


## GCC

libstdc++ with GCC 9.0 has the following numbers:

```
----------------------------------------------------------------------
Benchmark                            Time             CPU   Iterations
----------------------------------------------------------------------
noop                             0.000 ns        0.000 ns   1000000000
is_sorted_by_hand                 2842 ns         2888 ns       248889
is_sorted_base                   56290 ns        57199 ns        11200
is_sorted_vector_bool           273079 ns       278308 ns         2358
is_sorted_bitset                192486 ns       194972 ns         3446
is_sorted_itsy_bitsy               817 ns          820 ns       896000
is_sorted_until_by_hand           2812 ns         2825 ns       248889
is_sorted_until_base             48404 ns        48652 ns        14452
is_sorted_until_vector_bool     251334 ns       251116 ns         2800
is_sorted_until_bitset          187284 ns       185904 ns         3446
is_sorted_until_itsy_bitsy         679 ns          680 ns       896000
find_by_hand                      2443 ns         2455 ns       280000
find_base                        22696 ns        22949 ns        32000
find_vector_bool                 84364 ns        85449 ns         8960
find_bitset                      90512 ns        89979 ns         7467
find_itsy_bitsy                   2422 ns         2400 ns       280000
fill_by_hand                       256 ns          255 ns      2635294
fill_base                         2533 ns         2511 ns       280000
fill_vector_bool                   254 ns          257 ns      2800000
fill_bitset                     126316 ns       125552 ns         4978
fill_bitset_smart                  255 ns          257 ns      2800000
fill_itsy_bitsy                    259 ns          262 ns      2800000
fill_itsy_bitsy_smart              254 ns          255 ns      2635294
sized_fill_by_hand                 252 ns          251 ns      2800000
sized_fill_base                   2567 ns         2567 ns       280000
sized_fill_vector_bool          113136 ns       112305 ns         6400
sized_fill_bitset               124528 ns       125558 ns         5600
sized_fill_bitset_smart            254 ns          251 ns      2800000
sized_fill_itsy_bitsy              257 ns          257 ns      2800000
sized_fill_itsy_bitsy_smart        256 ns          257 ns      2800000
equal_by_hand                     1020 ns         1025 ns       640000
equal_memcmp                     0.321 ns        0.312 ns   1000000000
equal_base                       0.323 ns        0.328 ns   1000000000
equal_vector_bool               242796 ns       239955 ns         2800
equal_vector_bool_operator      256364 ns       254981 ns         2635
equal_bitset                     0.000 ns        0.000 ns   1000000000
equal_bitset_operator            0.000 ns        0.000 ns   1000000000
equal_itsy_bitsy                   518 ns          516 ns      1000000
equal_itsy_bitsy_operator          513 ns          516 ns      1120000
count_by_hand                     5606 ns         5625 ns       100000
count_base                       46712 ns        46490 ns        14452
count_vector_bool                98263 ns        97656 ns         6400
count_bitset                    111041 ns       109863 ns         6400
count_bitset_smart               11085 ns        10986 ns        64000
count_itsy_bitsy                  5509 ns         5580 ns       112000
count_itsy_bitsy_smart            5500 ns         5625 ns       100000
copy_by_hand                       259 ns          255 ns      2635294
copy_base                         3202 ns         3209 ns       224000
copy_vector_bool                192254 ns       192540 ns         3733
copy_bitset                     146175 ns       146484 ns         4480
copy_bitset_operator               262 ns          261 ns      2635294
copy_itsy_bitsy                    258 ns          262 ns      2800000
copy_itsy_bitsy_operator           259 ns          255 ns      2635294
sized_copy_by_hand                 259 ns          255 ns      2635294
sized_copy_base                   3258 ns         3278 ns       224000
sized_copy_vector_bool          220069 ns       219727 ns         3200
sized_copy_bitset               151193 ns       149972 ns         4480
sized_copy_itsy_bitsy              269 ns          267 ns      2635294
```


## Visual C++

These are the numbers using Visual C++ (Visual Studio 16.2.3). Note that the performance here might not be as great. In order to preserve constexpr, we could not use intrinsics in VC++ because none of their intrinsics are constexpr. Their compiler does not have `std::is_constant_evaluated()` in any form, which makes it impossible to use low-level, fast functions in MSVC for the algorithms and other places without giving constexpr the guillotine. Hopefully, the situation on that front will improve and we will get better constexpr-related goodies in the releases to come.

```
----------------------------------------------------------------------
Benchmark                            Time             CPU   Iterations
----------------------------------------------------------------------
sized_copy_by_hand                 554 ns          558 ns      1120000
sized_copy_base                   2670 ns         2668 ns       263529
sized_copy_vector_bool          201823 ns       204041 ns         3446
sized_copy_bitset               189604 ns       188354 ns         3733
sized_copy_itsy_bitsy              190 ns          188 ns      3733333
copy_by_hand                       606 ns          614 ns      1120000
copy_base                         2431 ns         2431 ns       263529
copy_vector_bool                244844 ns       245857 ns         2987
copy_bitset                     171791 ns       172631 ns         4073
copy_bitset_operator               147 ns          146 ns      4480000
copy_itsy_bitsy                    170 ns          167 ns      3733333
copy_itsy_bitsy_operator           145 ns          148 ns      4977778
count_by_hand                     2728 ns         2727 ns       263529
count_base                       67899 ns        65569 ns        11200
count_vector_bool               132797 ns       131830 ns         4978
count_bitset                     98924 ns        97656 ns         6400
count_bitset_smart                5299 ns         5301 ns       112000
count_itsy_bitsy                  2563 ns         2550 ns       263529
count_itsy_bitsy_smart            2601 ns         2609 ns       263529
equal_by_hand                     1023 ns         1001 ns       640000
equal_memcmp                       518 ns          516 ns      1120000
equal_base                       65633 ns        65569 ns        11200
equal_vector_bool               230969 ns       230164 ns         2987
equal_vector_bool_operator         525 ns          531 ns      1000000
equal_bitset                    146907 ns       146484 ns         4480
equal_bitset_operator              528 ns          531 ns      1000000
equal_itsy_bitsy                   532 ns          531 ns      1000000
equal_itsy_bitsy_operator          527 ns          516 ns      1120000
sized_fill_by_hand                 515 ns          516 ns      1120000
sized_fill_base                   1805 ns         1800 ns       373333
sized_fill_vector_bool          113288 ns       111607 ns         5600
sized_fill_bitset               145251 ns       144385 ns         4978
sized_fill_bitset_smart            138 ns          138 ns      4977778
sized_fill_itsy_bitsy              162 ns          164 ns      4480000
sized_fill_itsy_bitsy_smart        167 ns          167 ns      3733333
fill_by_hand                       504 ns          502 ns      1120000
fill_base                         1824 ns         1842 ns       407273
fill_vector_bool                149444 ns       149613 ns         4073
fill_bitset                     145098 ns       147524 ns         4978
fill_bitset_smart                  147 ns          148 ns      4977778
fill_itsy_bitsy                    566 ns          572 ns      1120000
fill_itsy_bitsy_smart              163 ns          161 ns      4072727
find_by_hand                     64005 ns        64174 ns        11200
find_base                        45115 ns        45516 ns        15448
find_vector_bool                114227 ns       114397 ns         5600
find_bitset                      78854 ns        77424 ns         7467
find_itsy_bitsy                  64992 ns        64523 ns         8960
is_sorted_until_by_hand          49151 ns        48828 ns        11200
is_sorted_until_base             65651 ns        65569 ns        11200
is_sorted_until_vector_bool     231133 ns       234375 ns         3200
is_sorted_until_bitset          161046 ns       163923 ns         4480
is_sorted_until_itsy_bitsy        1459 ns         1475 ns       497778
is_sorted_by_hand                52399 ns        51618 ns        11200
is_sorted_base                   68395 ns        68011 ns         8960
is_sorted_vector_bool           236765 ns       235395 ns         2987
is_sorted_bitset                162437 ns       163923 ns         4480
is_sorted_itsy_bitsy              1420 ns         1444 ns       497778
noop                             0.325 ns        0.328 ns   1000000000
```



# Future Work

There are quite a lot of optimizations, additional underlying data structures, general improvements, and other things to do here.


## Better non-constexpr bit intrinsic calculations

MSVC has issues with `constexpr` and their intrinsics, and they do not yet have `std::is_constant_evaluated`. As such, the `bitsy::first(l/r)_(zero/one)`, `bitsy::count(l/r)_(zero/one)` and `bitsy::popcount` intrinsic functions -- while `constexpr` -- are also implemented in some of the most braindead and plain manners possible. It would be nice to add `if constexpr()` blocks for implementations in the `__basic_X` version of these functions that use smarter bit twiddling tricks. This is done for one of the intrinsics, but should be extended to the others.

GCC and Clang only use the `__basic_X` loop versions if the type is too big to fit in one of their `unsigned`, `unsigned long`, or `unsigned long long` intrinsics.


## Putting It Directly in libc++ Too

The 2019 Google Summer of Code saw this library having an implementation placed towards libstdc++. The patch is out, and progress will hopefully be made over the coming months to get a version of it firmly in libstdc++ and fully integrated.

It would be nice to make much of the same available in libc++ as well, with the goal of improving the bit iterator situation there. There is no prior art for doing such a thing; libc++ is not one for many extensions, unlike libstdc++ which features quite a few extended features. Perhaps performance data can persuade them that having a concrete `bit_iterator` exposed by this library would be highly beneficial to them.


## Strong Exception Safety

Currently, `basic_bit_sequence` does not exhibit strong exception safety (not because the library tries and fails, it just doesn't `try`). This is something that should probably fixed soon, to make sure this is usable in exception-heavy code.

Likewise, the code should also be usable in a `-fno-exceptions` situation. It likely currently is (because of the lack of `try` or `catch` employed), but it should be explicitly checked over.


## Small Buffer

It has been a long time coming, and this bit library makes it all the more apparent and useful. There needs to be two additional container types implemented (and, perhaps in the future, proposed to the standard):

- `template <typename T, std::size_t BufferWords, typename Allocator> small_bit_buffer;`
  - This class provides the "small buffer optimization" with a customizable buffer size to be stored with the container, with the exception that this keeps track of its size by-the-bit and prevents a `value_type` of `bitsy::bit_value`.
  - `small_bit_buffer<T, 0, Allocator>` is morally and functionally equivalent in iterator guarantees and storage requirements as `std::vector<bool>`, just without the ugly specialization of `vector`.
  - Otherwise, `small_bit_buffer<T, N, Allocator>` produces a type which buffers up to `N` elements of type `T` in some implementation-defined manner while maintaining a `.size()` internally as the number of bits rather than the number of words. Iterator invalidation rules change and become similar to `std::basic_string`'s iterator invalidation rules.
- `template <typename T, std::size_t BufferWords, typename Allocator> small_buffer;`
  - This class provides the "small buffer optimization" with a customizable buffer size to be stored with the container.
  - `small_buffer<T, 0, Allocator>` is morally and functionally equivalent in iterator guarantees and storage requirements as `std::vector<T>`.
  - Otherwise, `small_buffer<T, N, Allocator>` produces a type which buffers up to `N` elements of type `T` in some implementation-defined manner. Iterator invalidation rules change and become similar to `std::basic_string`'s iterator invalidation rules.

Once these types exist, they can be used as the default backing storage of `bit_sequence`/`dynamic_bitset<T>`.


## Optimization Work

- There is a need to make the `bit_equal` and `std::equal` algorithms perform just as fast as their `memcmp` counterparts. The answer why it does not optimize out as cleanly will likely lie in an analysis of both the output assembly and any intermediate representation available from the compiler (LLVM and GCC can help obtain this kind of information). See the benchmarks for more details.
- Optimizations for `bit_iterator<T>`s that have different underlying `It` types is very much pertinent to what is happening here. The optimizations are very much done plainly and only work on homogenous iterators; it would be great to work on `bit_iterator`s that do not view the same `value_type` in the slightest.



# Acknowledgements

A huge thanks to Dr. Vincent Reverdy for sponsoring and helping with this work. An enormous thank you to Jonathan Wakely, Thomas Rodgers, and Ville Voutilainen for watching over my work during the Summer of Code 2019 through the Free Software Foundation and GNU Compiler Collection project.

Many thanks to the Blessed Guardian, Morwenn, for watching over my commits and cautioning me of my occasional derps.

Thank you to Corentin Jabot for changing the name "Extents" to "Bounds" to better represent the begin/end type for `bit_view`.
