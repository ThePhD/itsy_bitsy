#include <benchmark/benchmark.h>

#include <itsy/bitsy.hpp>

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
	using C = std::array<std::size_t, (100032 + size_bits - 1) / (size_bits)>;
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
	if (std::find(c2.cbegin(), c2.cend(), static_cast<std::size_t>(0)) != c2.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_base(benchmark::State& state)
{
	using C = std::array<bool, 100032>;
	C c;
	C c2;
	c.fill(true);
	c2.fill(false);

	for (auto _ : state)
		{
			std::copy(c.cbegin(), c.cend(), c2.begin());
		}
	if (std::find(c2.cbegin(), c2.cend(), false) != c2.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100032, true);
	C c2(100032, false);

	for (auto _ : state)
		{
			std::copy(c.cbegin(), c.cend(), c2.begin());
		}
	if (std::find(c2.cbegin(), c2.cend(), false) != c2.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_bitset(benchmark::State& state)
{
	using C = std::bitset<100032>;
	C c;
	C c2;
	c.set();

	for (auto _ : state)
		{
			for (std::size_t i = 0; i < c.size(); ++i)
				{
					c2[i] = c[i];
				}
		}
	if (!c2.all())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_bitset_operator(benchmark::State& state)
{
	using C = std::bitset<100032>;
	C c;
	C c2;
	c.set();

	for (auto _ : state)
		{
			c2 = c;
		}
	if (!c2.all())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_itsy_bitsy(benchmark::State& state)
{
	using C = bitsy::bit_vector<std::size_t>;
	C c(100032, true);
	C c2(100032, false);

	for (auto _ : state)
		{
			bitsy::bit_copy(c.cbegin(), c.cend(), c2.begin());
		}
	if (std::find(c2.cbegin(), c2.cend(), false) != c2.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_itsy_bitsy_operator(benchmark::State& state)
{
	using C = bitsy::bit_vector<std::size_t>;
	C c(100032, true);
	C c2(100032, false);

	for (auto _ : state)
		{
			c2 = c;
		}
	if (std::find(c2.cbegin(), c2.cend(), false) != c2.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_itsy_bitsy_sbv(benchmark::State& state)
{
	using C = bitsy::small_bit_vector<std::size_t>;
	C c(100032, true);
	C c2(100032, false);

	for (auto _ : state)
		{
			bitsy::bit_copy(c.cbegin(), c.cend(), c2.begin());
		}
	if (std::find(c2.cbegin(), c2.cend(), false) != c2.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
copy_itsy_bitsy_sbv_operator(benchmark::State& state)
{
	using C = bitsy::small_bit_vector<std::size_t>;
	C c(100032, true);
	C c2(100032, false);

	for (auto _ : state)
		{
			c2 = c;
		}
	if (std::find(c2.cbegin(), c2.cend(), false) != c2.cend())
		{
			state.SkipWithError("bad benchmark result");
		}
}

BENCHMARK(copy_by_hand);
BENCHMARK(copy_base);
BENCHMARK(copy_vector_bool);
BENCHMARK(copy_bitset);
BENCHMARK(copy_bitset_operator);
BENCHMARK(copy_itsy_bitsy);
BENCHMARK(copy_itsy_bitsy_operator);
BENCHMARK(copy_itsy_bitsy_sbv);
BENCHMARK(copy_itsy_bitsy_sbv_operator);
