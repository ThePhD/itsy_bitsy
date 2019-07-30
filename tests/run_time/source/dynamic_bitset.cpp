#include <bitsy_tests/constants.hpp>
#include <bitsy_tests/generic_tests.hpp>

#include <catch2/catch.hpp>

#include <itsy/dynamic_bitset.hpp>

#include <range/v3/view/subrange.hpp>

#include <cstddef>
#include <cstdint>
#include <span>
#include <iterator>

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <string>


template<typename BitSequence>
void
bit_sequence_test_clear(BitSequence& sequence)
{
	sequence.clear();
	REQUIRE(sequence.size() == 0);
	REQUIRE(sequence.count() == 0);
}

template<typename TestType, typename BitSequence, typename SizeType>
void
bit_sequence_test_insertion_erase_range(BitSequence& sequence, SizeType starting_size)
{
	using difference_type = typename BitSequence::difference_type;
	using reference       = typename BitSequence::reference;
	REQUIRE(sequence.size() == starting_size);
	std::array<TestType, 2> word_data = { static_cast<TestType>(0xFFFFFFFFFFFFFFFF),
		static_cast<TestType>(0) };
	std::size_t expected_size = starting_size + (word_data.size() * bitsy::binary_digits_v<TestType>);
	bitsy::bit_view<decltype(word_data)> word_insertion_view(word_data);
	sequence.insert(
	  std::cend(sequence), std::cbegin(word_insertion_view), std::cend(word_insertion_view));
	REQUIRE(sequence.size() != starting_size);
	REQUIRE(sequence.size() == expected_size);
	for (difference_type bit_index = static_cast<difference_type>(starting_size);
	     bit_index < static_cast<difference_type>(sequence.size()); ++bit_index)
		{
			reference r = sequence[bit_index];
			REQUIRE(r == word_insertion_view[bit_index - starting_size]);
		}
}

template<typename TestType, typename BitSequence, typename SizeType>
void
bit_sequence_test_insertion_erase_initializer_list(BitSequence& sequence, SizeType starting_size)
{
	REQUIRE(sequence.size() == starting_size);
}

template<typename TestType, typename BitSequence, typename SizeType>
void
bit_sequence_test_insertion_erase_single(BitSequence& sequence, SizeType starting_size)
{
	REQUIRE(sequence.size() == starting_size);
}

template<typename TestType, typename BitSequence, typename SizeType>
void
bit_sequence_test_insertion_erase(BitSequence& sequence, SizeType starting_size)
{
	bit_sequence_test_insertion_erase_range<TestType>(sequence, starting_size);
	SizeType init_list_starting_size = sequence.size();
	bit_sequence_test_insertion_erase_initializer_list<TestType>(sequence, init_list_starting_size);
	SizeType single_starting_size = sequence.size();
	bit_sequence_test_insertion_erase_single<TestType>(sequence, single_starting_size);
}

TEMPLATE_TEST_CASE("dynamic_bitset functionality with ranges", "[dynamic_bitset][ranges]",
  std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, std::int64_t, std::int32_t,
  std::int16_t, std::int8_t, char32_t, char16_t, unsigned char, signed char, std::size_t,
  std::ptrdiff_t)
{
	// non-exhaustive
	constexpr std::ptrdiff_t off_indices[] = { 0, 1, 2, 3, 4, 5, 6,
		5 + 2 * bitsy::binary_digits_v<TestType>, 3 + 8 * bitsy::binary_digits_v<TestType>,
		3 + 12 * bitsy::binary_digits_v<TestType>, 7 + 17 * bitsy::binary_digits_v<TestType>,
		4 + 23 * bitsy::binary_digits_v<TestType> };
	// exhaustive
	constexpr std::ptrdiff_t on_indices[] = { 0, 0 + 2 * bitsy::binary_digits_v<TestType>,
		0 + 7 * bitsy::binary_digits_v<TestType>, 0 + 12 * bitsy::binary_digits_v<TestType>,
		0 + 17 * bitsy::binary_digits_v<TestType>, 0 + 22 * bitsy::binary_digits_v<TestType>,
		0 + 27 * bitsy::binary_digits_v<TestType>, 1 + 29 * bitsy::binary_digits_v<TestType> };

	constexpr std::size_t expected_bits = expected_words * bitsy::binary_digits_v<TestType>;

	constexpr TestType b00 = static_cast<TestType>(0x00);
	constexpr TestType b01 = static_cast<TestType>(0x01);
	constexpr TestType b10 = static_cast<TestType>(0x02);

	SECTION("span")
	{
		auto storage_test = [&](auto&& storage) {
			using R = std::remove_reference_t<decltype(storage)>;
			bitsy::basic_dynamic_bitset<R> view_bits(std::in_place, std::forward<R>(storage));
			REQUIRE(view_bits.size() == expected_bits);
			REQUIRE(view_bits.count() == static_cast<std::ptrdiff_t>(expected_bits));

			bit_view_test_mixed_any_all_none(view_bits);
			bit_view_test_iteration<TestType>(view_bits, on_indices, off_indices);
			bit_sequence_test_clear(view_bits);
			bit_sequence_test_insertion_erase<TestType>(view_bits, view_bits.size());
		};
		SECTION("vector")
		{
			std::vector<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00,
				b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
			storage_test(storage);
		}
		SECTION("std::basic_string")
		{
			std::basic_string<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
				b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
				b10 };
			storage_test(storage);
		}
		SECTION("deque")
		{
			std::deque<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
				b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
			storage_test(storage);
		}
		SECTION("list")
		{
			std::list<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01,
				b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b10 };
			storage_test(storage);
		}
#if BITSY_TEST_FORWARD_LIST
		SECTION("forward_list")
		{
			std::forward_list<TestType> storage{ b01, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00,
				b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00, b00, b00, b00, b01, b00,
				b10 };
			storage_test(storage);
		}
#endif
	}
}
