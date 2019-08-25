#include <itsy/benchmarks/bit_intrinsics.hpp>

#include <benchmark/benchmark.h>
#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>

static void
count_by_hand(benchmark::State& state)
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

	std::size_t result = 0;
	for (auto _ : state)
		{
			auto end_it = c.cend();
			for (auto it = c.cbegin(); it != end_it; ++it)
				{
					result += itsy_bitsy::bit_count(*it);
				}
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
count_base(benchmark::State& state)
{
	using C = std::array<bool, 100000>;
	C c;
	c.fill(false);
	c[95000] = true;

	std::size_t result = 0;
	for (auto _ : state)
		{
			result += std::count(c.cbegin(), c.cend(), true);
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
count_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100000, false);
	c[95000] = true;

	std::size_t result = 0;
	for (auto _ : state)
		{
			result += std::count(c.cbegin(), c.cend(), true);
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
count_bitset(benchmark::State& state)
{
	using C = std::bitset<100000>;
	C c;
	c[95000] = true;

	std::size_t result = 0;
	for (auto _ : state)
		{
			for (std::size_t i = 0; i < c.size(); ++i)
				{
					if (c.test(i))
						{
							result += 1;
						}
				}
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
count_bitset_smart(benchmark::State& state)
{
	using C = std::bitset<100000>;
	C c;
	c[95000] = true;

	std::size_t result = 0;
	for (auto _ : state)
		{
			result += c.count();
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
count_bit_iterators_p0237(benchmark::State& state)
{
	for (auto _ : state)
		{
			state.SkipWithError("Not implemented");
			return;
		}
}

BENCHMARK(count_by_hand);
BENCHMARK(count_base);
BENCHMARK(count_vector_bool);
BENCHMARK(count_bitset);
BENCHMARK(count_bitset_smart);
BENCHMARK(count_bit_iterators_p0237);
