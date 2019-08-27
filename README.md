> And the itsy-bitsy spider
> Climbed up the spout again

# 🕸️ itsy.bitsy 🕸️

`itsy.bitsy` is a library for working with and manipulating bits. It comes with 3 different pertinent abstraction layers:

- Bit Iterators
  - An iterator over a bits of a `word` type. A `word` type is one of the fundamental integer types, character type, or enumeration types. Contains`bitsy::bit_iterator` `bitsy::bit_reference`, `bitsy::bit_pointer`, and `bitsy::bit_value` types as well.
- Bit Ranges
  - A family of types contained in the `bitsy::bit_view<Range, Bounds>` class template. `Bounds` can be any type that provides a `begin_position(const R&)` and `end_position(const R&)` functions, or just one of the default ones contained in the library such as `bitsy::bit_bounds<FirstN, LastN>`, `bitsy::word_bit_bounds`, or `bitsy::dynamic_bit_bounds`.
- Bit Sequences
  - A family of types contained in the `bitsy::bit_sequence<Container>` class template. Supports having reference wrapped containers as well, such as `bitsy::bit_sequence<std::reference_wrapper<Container>>`.


