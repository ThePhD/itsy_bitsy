#include <itsy/benchmarks/bit_intrinsics.hpp>

#include <benchmark/benchmark.h>
#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>
#include <limits>

static void
sized_fill_by_hand(benchmark::State& state)
{
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100000 + size_bits - 1) / (size_bits)>;
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
sized_fill_base(benchmark::State& state)
{
	using C = std::array<bool, 100000>;
	C c;
	c.fill(false);

	bool result = true;
	for (auto _ : state)
		{
			std::fill_n(c.begin(), c.size(), true);
		}
	if (std::find(c.cbegin(), c.cend(), false) != c.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
sized_fill_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100000, false);

	for (auto _ : state)
		{
			std::fill_n(c.begin(), c.size(), true);
		}
	if (std::find(c.cbegin(), c.cend(), false) != c.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
sized_fill_bitset(benchmark::State& state)
{
	using C = std::bitset<100000>;
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
sized_fill_bitset_smart(benchmark::State& state)
{
	using C = std::bitset<100000>;
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
sized_fill_bit_iterators_p0237(benchmark::State& state)
{
	for (auto _ : state)
		{
			state.SkipWithError("Not implemented");
			return;
		}
}

BENCHMARK(sized_fill_by_hand);
BENCHMARK(sized_fill_base);
BENCHMARK(sized_fill_vector_bool);
BENCHMARK(sized_fill_bitset);
BENCHMARK(sized_fill_bitset_smart);
BENCHMARK(sized_fill_bit_iterators_p0237);
