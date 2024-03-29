#include <benchmark/benchmark.h>

#include <itsy/bitsy.hpp>

#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>

static void
find_by_hand(benchmark::State& state)
{
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C = std::array<std::size_t, (100032 + size_bits - 1) / (size_bits)>;
	C c;
	c.fill(0);
	{
		std::lldiv_t rem         = std::lldiv(static_cast<std::size_t>(95000), size_bits);
		std::size_t& target_word = c[static_cast<std::size_t>(rem.quot)];
		target_word |= (static_cast<std::size_t>(1) << static_cast<std::size_t>(rem.rem));
	}

	bool result = true;
	for (auto _ : state)
		{
			bool target_value = false;
			auto end_it       = c.cend();
			for (auto it = c.cbegin(); it != end_it; ++it)
				{
					std::size_t bs = bitsy::firstr_one(*it);
					if (bs != 0)
						{
							--bs;
							const std::size_t& target_word = *it;
							std::size_t mask = (static_cast<std::size_t>(1) << bs);
							target_value     = static_cast<bool>(target_word & mask);
							break;
						}
				}
			result &= target_value;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
find_base(benchmark::State& state)
{
	using C = std::array<bool, 100032>;
	C c;
	c.fill(false);
	c[95000] = true;

	bool result = true;
	for (auto _ : state)
		{
			auto it = std::find(c.cbegin(), c.cend(), true);
			result &= static_cast<bool>(*it);
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
find_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100032, false);
	c[95000] = true;

	bool result = true;
	for (auto _ : state)
		{
			auto it = std::find(c.cbegin(), c.cend(), true);
			result &= *it;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
find_bitset(benchmark::State& state)
{
	using C = std::bitset<100032>;
	C c;
	c[95000]    = true;
	bool result = true;

	for (auto _ : state)
		{
			bool test_value = false;
			for (std::size_t i = 0; i < c.size(); ++i)
				{
					if (c.test(i))
						{
							test_value = true;
							break;
						}
				}
			result &= test_value;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
find_itsy_bitsy(benchmark::State& state)
{
	using C = bitsy::bit_vector<std::size_t>;
	C c(100032, false);
	c[95000] = true;

	bool result = true;
	for (auto _ : state)
		{
			auto it = bitsy::bit_find(c.cbegin(), c.cend(), true);
			result &= *it;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
find_itsy_bitsy_sbv(benchmark::State& state)
{
	using C = bitsy::small_bit_vector<std::size_t>;
	C c(100032, false);
	c[95000] = true;

	bool result = true;
	for (auto _ : state)
		{
			auto it = bitsy::bit_find(c.cbegin(), c.cend(), true);
			result &= *it;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

BENCHMARK(find_by_hand);
BENCHMARK(find_base);
BENCHMARK(find_vector_bool);
BENCHMARK(find_bitset);
BENCHMARK(find_itsy_bitsy);
BENCHMARK(find_itsy_bitsy_sbv);
