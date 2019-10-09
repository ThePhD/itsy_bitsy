#include <itsy/benchmarks/opaque.hpp>

#include <benchmark/benchmark.h>

#include <itsy/bitsy.hpp>

#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>

static void
push_back_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c;
	c.reserve(state.iterations());

	for (auto _ : state)
		{
			c.push_back(bitsy::benchmarks::opaque_true());
		}
	if (std::find(c.begin(), c.end(), false) != c.end())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
push_back_itsy_bitsy(benchmark::State& state)
{
	using C = bitsy::bit_vector<std::size_t>;
	C c;
	c.reserve(state.iterations());

	for (auto _ : state)
		{
			c.push_back(bitsy::benchmarks::opaque_true());
		}
	if (std::find(c.begin(), c.end(), bitsy::bit0) != c.end())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
push_back_itsy_bitsy_sbv(benchmark::State& state)
{
	using C = bitsy::small_bit_vector<std::size_t>;
	C c;
	c.reserve(state.iterations());

	for (auto _ : state)
		{
			c.push_back(bitsy::benchmarks::opaque_true());
		}
	if (std::find(c.begin(), c.end(), bitsy::bit0) != c.end())
		{
			state.SkipWithError("bad benchmark result");
		}
}

BENCHMARK(push_back_vector_bool);
BENCHMARK(push_back_itsy_bitsy);
BENCHMARK(push_back_itsy_bitsy_sbv);
