#include <itsy/bitsy.hpp>

#include <string_view>

int
main()
{
	static constexpr char32_t data[] = { 0b0001, 0b0010 };
	static constexpr bitsy::bit_view<std::basic_string_view<char32_t>> data_bits(&data[0], 2);

	static_assert(data_bits[0], "First bit is not true (expected: true)!");
	static_assert(!data_bits.test(1), "Second bit is true  (expected: false)!");
	static_assert(*(data_bits.begin() + bitsy::binary_digits_v<char32_t> + 1),
	  "Second bit in second word is not true (expected: true)!");
	static_assert(data_bits.size() == (sizeof(char32_t) * CHAR_BIT * 2),
	  "The size of the bit view is not 2 x unsigned");
	static_assert(data_bits.size() == (bitsy::binary_digits_v<char32_t> * 2),
	  "The size of the bit view is not 2 x unsigned");
	static_assert(!data_bits[3].value(), "The bit is true (expected: false)!");

	return 0;
}