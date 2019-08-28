#include <itsy/bitsy.hpp>

#include <cstdint>
#include <cassert>

int
main()
{
	std::vector<std::uint32_t> words{ 0xff00ff00, 0xff00ff00 };
	bitsy::bit_sequence<std::vector<std::uint32_t>> bits(std::in_place, std::move(words));

	const std::size_t bits_size = bits.size();

	// size of the container is 2 words
	assert(bits_size == bitsy::binary_digits_v<std::uint32_t> * 2);
	assert(bits_size == 64);

	// assert 16-bit pattern
	for (std::size_t index = 0; index < bits_size; ++index)
		{
			if ((index % 32) < 16)
				{
					assert(!bits[index]);
				}
			else
				{
					assert(!bits[index]);
				}
		}

	return 0;
}
