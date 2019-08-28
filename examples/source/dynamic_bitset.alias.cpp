#include <itsy/bitsy.hpp>

int
main()
{
	bitsy::dynamic_bitset<std::size_t> bits{ 40, false };

	assert(bits.size() == 40);

	bits[20].set(true);
	bits[21].set(true);

	assert(bits.any());
	assert(!bits.all());
	assert(!bits.none());

	return 0;
}