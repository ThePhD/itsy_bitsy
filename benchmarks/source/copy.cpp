#include <itsy/benchmarks/bit_intrinsics.hpp>

#include <benchmark/benchmark.h>
#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>
#include <limits>
#include <algorithm>

static void
copy_by_hand(benchmark::State& state)
{
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100000 + size_bits - 1) / (size_bits)>;
	C c;
	C c2;
	c.fill(std::numeric_limits<std::size_t>::max());
	c2.fill(0);

	for (auto _ : state)
		{
			auto it2    = c2.begin();
			auto end_it = c.cend();
			for (auto it = c.cbegin(); it != end_it; ++it, ++it2)
				{
					*it2 = *it;
				}
		}
	if (std::find(c.cbegin(), c.cend(), static_cast<std::size_t>(0)) != c.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_base(benchmark::State& state)
{
	using C = std::array<bool, 100000>;
	C c;
	C c2;
	c.fill(true);
	c2.fill(false);

	for (auto _ : state)
		{
			std::copy(c.cbegin(), c.cend(), c2.begin());
		}
	if (std::find(c.cbegin(), c.cend(), false) != c.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100000, true);
	C c2(100000, false);

	for (auto _ : state)
		{
			std::copy(c.cbegin(), c.cend(), c2.begin());
		}
	if (std::find(c.cbegin(), c.cend(), false) != c.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_bitset(benchmark::State& state)
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
copy_bit_iterators_p0237(benchmark::State& state)
{
	for (auto _ : state)
		{
			state.SkipWithError("Not implemented");
			return;
		}
}

BENCHMARK(copy_by_hand);
BENCHMARK(copy_base);
BENCHMARK(copy_vector_bool);
BENCHMARK(copy_bitset);
BENCHMARK(copy_bit_iterators_p0237);
