#include <itsy/bitsy.hpp>

#include <cassert>

int
main()
{
	// construct with initializer list
	bitsy::bit_sequence<std::vector<std::size_t>> bits{ false, true, true, false, false };
	// construct from iterators just like other containers
	bitsy::bit_sequence<std::vector<std::size_t>> other_bits(bits.cbegin(), bits.cend());

	// can compare
	assert(bits == other_bits);
	assert(!(bits != other_bits));

	// insertion
	bits.push_back(false);
	bits.insert(bits.begin() + 2, { true, true });
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
