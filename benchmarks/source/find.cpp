#include <itsy/benchmarks/bit_intrinsics.hpp>

#include <benchmark/benchmark.h>
#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>

static void
find_by_hand(benchmark::State& state)
{
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100000 + size_bits - 1) / (size_bits)>;
	C c;
	c.fill(0);
	{
		std::lldiv_t rem         = std::lldiv(static_cast<std::size_t>(95000), size_bits);
		std::size_t& target_word = c[rem.quot];
		target_word |= (static_cast<std::size_t>(1) << static_cast<std::size_t>(rem.rem));
	}

	bool result = true;
	for (auto _ : state)
		{
			bool target_value = false;
			auto end_it       = c.cend();
			for (auto it = c.cbegin(); it != end_it; ++it)
				{
					std::size_t bs = itsy_bitsy::bit_scan(*it);
					if (bs < size_bits)
						{
							const std::size_t& target_word = *it;
							std::size_t mask               = (static_cast<std::size_t>(1) << bs);
							target_value                   = static_cast<bool>(target_word & mask);
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
	using C = std::array<bool, 100000>;
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
	C c(100000, false);
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
	using C = std::bitset<100000>;
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
find_bit_iterators_p0237(benchmark::State& state)
{
	for (auto _ : state)
		{
			state.SkipWithError("Not implemented");
			return;
		}
}

BENCHMARK(find_by_hand);
BENCHMARK(find_base);
BENCHMARK(find_vector_bool);
BENCHMARK(find_bitset);
BENCHMARK(find_bit_iterators_p0237);
