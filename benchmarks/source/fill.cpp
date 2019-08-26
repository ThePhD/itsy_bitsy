#include <benchmark/benchmark.h>

#include <itsy/bitsy.hpp>

#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>
#include <limits>

static void
fill_by_hand(benchmark::State& state)
{
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100032 + size_bits - 1) / (size_bits)>;
	C c;
	c.fill(0);

	for (auto _ : state)
		{
			auto end_it = c.end();
			for (auto it = c.begin(); it != end_it; ++it)
				{
					*it = std::numeric_limits<std::size_t>::max();
				}
		}
	if (std::find(c.cbegin(), c.cend(), static_cast<std::size_t>(0)) != c.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
fill_base(benchmark::State& state)
{
	using C = std::array<bool, 100032>;
	C c;
	c.fill(false);

	for (auto _ : state)
		{
			std::fill(c.begin(), c.end(), true);
		}
	if (std::find(c.cbegin(), c.cend(), false) != c.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
fill_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100032, false);

	for (auto _ : state)
		{
			std::fill(c.begin(), c.end(), true);
		}
	if (std::find(c.cbegin(), c.cend(), false) != c.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
fill_bitset(benchmark::State& state)
{
	using C = std::bitset<100032>;
	C c;

	for (auto _ : state)
		{
			for (std::size_t i = 0; i < c.size(); ++i)
				{
					c.set(i, true);
				}
		}
	if (!c.all())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
fill_bitset_smart(benchmark::State& state)
{
	using C = std::bitset<100032>;
	C c;

	for (auto _ : state)
		{
			c.set();
		}
	if (!c.all())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
fill_itsy_bitsy(benchmark::State& state)
{
	bitsy::dynamic_bitset<std::size_t> c(100032, false);
	for (auto _ : state)
		{
			bitsy::bit_fill(c.begin(), c.end(), true);
		}
	if (!c.all())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
fill_itsy_bitsy_smart(benchmark::State& state)
{
	bitsy::dynamic_bitset<std::size_t> c(100032, false);
	for (auto _ : state)
		{
			c.set();
		}
	if (!c.all())
		{
			state.SkipWithError("bad benchmark result");
		}
}

BENCHMARK(fill_by_hand);
BENCHMARK(fill_base);
BENCHMARK(fill_vector_bool);
BENCHMARK(fill_bitset);
BENCHMARK(fill_bitset_smart);
BENCHMARK(fill_itsy_bitsy);
BENCHMARK(fill_itsy_bitsy_smart);
