#include <itsy/benchmarks/bit_intrinsics.hpp>

#include <benchmark/benchmark.h>
#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>
#include <cstring>

static void
equal_by_hand(benchmark::State& state)
{
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100000 + size_bits - 1) / (size_bits)>;
	C c;
	C c2;
	c.fill(0);
	c2.fill(0);

	bool result = true;
	for (auto _ : state)
		{
			auto end_it = c.cend();
			for (auto it = c.cbegin(), it2 = c2.cbegin(); it != end_it; ++it, ++it2)
				{
					if (*it != *it2)
						{
							result = false;
							break;
						}
				}
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
equal_memcmp(benchmark::State& state)
{
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100000 + size_bits - 1) / (size_bits)>;
	C c;
	C c2;
	c.fill(0);
	c2.fill(0);

	bool result = true;
	for (auto _ : state)
		{
			auto it  = c.data();
			auto it2 = c2.data();
			result &= (std::memcmp(it, it2, c.size() * sizeof(std::size_t)) == 0);
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
equal_base(benchmark::State& state)
{
	using C = std::array<bool, 100000>;
	C c;
	C c2;
	c.fill(false);
	c2.fill(false);

	bool result = true;
	for (auto _ : state)
		{
			result &= std::equal(c.cbegin(), c.cend(), c2.cbegin());
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
equal_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100000, false);
	C c2(100000, false);

	bool result = true;
	for (auto _ : state)
		{
			result &= std::equal(c.cbegin(), c.cend(), c2.cbegin());
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
equal_vector_bool_operator(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100000, false);
	C c2(100000, false);

	bool result = true;
	for (auto _ : state)
		{
			result &= (c == c2);
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
equal_bitset(benchmark::State& state)
{
	using C = std::bitset<100000>;
	C c;
	C c2;
	c.reset();
	c2.reset();

	bool result = true;
	for (auto _ : state)
		{
			for (std::size_t i = 0; i < c.size(); ++i)
				{
					if (c.test(i) != c2.test(i))
						{
							result = false;
							break;
						}
				}
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
equal_bitset_operator(benchmark::State& state)
{
	using C = std::bitset<100000>;
	C c;
	C c2;
	c.reset();
	c2.reset();

	bool result = true;
	for (auto _ : state)
		{
			result &= (c == c2);
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
equal_bit_iterators_p0237(benchmark::State& state)
{
	for (auto _ : state)
		{
			state.SkipWithError("Not implemented");
			return;
		}
}

BENCHMARK(equal_by_hand);
BENCHMARK(equal_memcmp);
BENCHMARK(equal_base);
BENCHMARK(equal_vector_bool);
BENCHMARK(equal_vector_bool_operator);
BENCHMARK(equal_bitset);
BENCHMARK(equal_bitset_operator);
BENCHMARK(equal_bit_iterators_p0237);
