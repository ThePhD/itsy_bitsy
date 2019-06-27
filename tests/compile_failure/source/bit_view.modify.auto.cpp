
#include <bitsy/bit_view.hpp>

#include <vector>
#include <cstdint>
#include <cstddef>

int
main()
{
  std::vector<std::size_t> storage{ 0, 1 };
  bitsy::bit_view<std::span<std::size_t>> b(storage);
  auto ref = *b.begin();
  ref      = true;

  return 0;
}