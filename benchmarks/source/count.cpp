#include <benchmark/benchmark.h>

#include <itsy/bitsy.hpp>

#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>

static void
count_by_hand(benchmark::State& state)
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

	std::size_t result = 0;
	for (auto _ : state)
		{
			auto end_it = c.cend();
			for (auto it = c.cbegin(); it != end_it; ++it)
				{
					result += bitsy::popcount(*it);
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
	using C = std::array<bool, 100032>;
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
	C c(100032, false);
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
	using C = std::bitset<100032>;
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
	using C = std::bitset<100032>;
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
count_itsy_bitsy(benchmark::State& state)
{
	using C = bitsy::bit_vector<std::size_t>;
	C c(100032, false);
	c[95000] = true;

	std::size_t result = 0;
	for (auto _ : state)
		{
			result += bitsy::bit_count(c.cbegin(), c.cend(), true);
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
count_itsy_bitsy_smart(benchmark::State& state)
{
	using C = bitsy::bit_vector<std::size_t>;
	C c(100032, false);
	c[95000] = true;

	std::size_t result = 0;
	for (auto _ : state)
		{
			result += c.popcount();
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
count_itsy_bitsy_sbv(benchmark::State& state)
{
	using C = bitsy::small_bit_vector<std::size_t>;
	C c(100032, false);
	c[95000] = true;

	std::size_t result = 0;
	for (auto _ : state)
		{
			result += bitsy::bit_count(c.cbegin(), c.cend(), true);
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
count_itsy_bitsy_sbv_smart(benchmark::State& state)
{
	using C = bitsy::small_bit_vector<std::size_t>;
	C c(100032, false);
	c[95000] = true;

	std::size_t result = 0;
	for (auto _ : state)
		{
			result += c.popcount();
		}
	if (result != state.iterations())
		{
			state.SkipWithError("bad benchmark result");
		}
}

BENCHMARK(count_by_hand);
BENCHMARK(count_base);
BENCHMARK(count_vector_bool);
BENCHMARK(count_bitset);
BENCHMARK(count_bitset_smart);
BENCHMARK(count_itsy_bitsy);
BENCHMARK(count_itsy_bitsy_smart);
BENCHMARK(count_itsy_bitsy_sbv);
BENCHMARK(count_itsy_bitsy_sbv_smart);
