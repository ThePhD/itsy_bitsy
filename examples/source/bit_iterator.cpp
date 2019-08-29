// itsy.bitsy
//
//  Copyright ⓒ 2019-2019 ThePhD.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/out_ptr/ for documentation.

#include <itsy/bitsy.hpp>

#include <random>
#include <limits>
#include <algorithm>
#include <iostream>

int
main()
{
	using sequence = std::list<int>;
	sequence seq{ 100, 0 };
	std::random_device rd{};
	std::default_random_engine rand_engine(rd());
	std::uniform_int_distribution<int> rand_distribution(
	  std::numeric_limits<int>::max() - 32, std::numeric_limits<int>::max());
	std::generate_n(seq.begin(), seq.size(), [&]() { return rand_distribution(rand_engine); });

	bitsy::bit_iterator<typename sequence::const_iterator> first(seq.cbegin(), 0);
	bitsy::bit_iterator<typename sequence::const_iterator> last(seq.cend(), 0);

	if (auto it = std::find(first, last, bitsy::bit0); it != last)
		{
			bitsy::bit_reference<typename sequence::const_reference> ref = *it;
			std::cout << "Found a 0 bit at the " << std::distance(it, last) << " element in the "
			          << seq.size() << ", at bit position" << ref.position() << "( mask: " << ref.mask()
			          << " | applied to value: " << *it.base() << ")" << std::endl;
		}

	return 0;
}
