
#include <itsy/bit_view.hpp>

#include <vector>
#include <cstdint>
#include <cstddef>
#include <span>

int
main()
{
	std::vector<std::size_t> storage{ 0, 1 };
	bitsy::bit_view<std::span<const std::size_t>> b(storage);
	(*b.begin()) = true;

	return 0;
}