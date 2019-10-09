#include <benchmark/benchmark.h>

#include <itsy/bitsy.hpp>

#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>

static void
is_sorted_until_by_hand(benchmark::State& state)
{
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C = std::array<std::size_t, (100032 + size_bits - 1) / (size_bits)>;
	C c;
	c.fill(0);
	{
		std::lldiv_t rem         = std::lldiv(static_cast<std::size_t>(100032 - 1), size_bits);
		std::size_t& target_word = c[static_cast<std::size_t>(rem.quot)];
		target_word |= (static_cast<std::size_t>(1) << static_cast<std::size_t>(rem.rem));
	}

	bool result = true;
	for (auto _ : state)
		{
			auto end_it    = c.cend();
			auto it        = c.cbegin();
			bool seen_true = false;
			for (; it != end_it; ++it)
				{
					const std::size_t& target_word = *it;
					if (!seen_true)
						{
							std::size_t bs = bitsy::firstr_one(target_word);
							if (bs != 0)
								{
									seen_true          = true;
									bool found_anamoly = false;
									for (std::size_t i = bs - 1; i < size_bits; ++i)
										{
											std::size_t mask =
											     (static_cast<std::size_t>(1) << i);
											if ((target_word & mask) == 0)
												{
													// found bad one
													found_anamoly = true;
													break;
												}
										}
									if (found_anamoly)
										{
											break;
										}
								}
						}
					else
						{
							std::size_t bs = bitsy::firstr_zero(target_word);
							if (bs != 0)
								{
									break;
								}
						}
				}
			result &= (it == end_it);
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
is_sorted_until_base(benchmark::State& state)
{
	using C = std::array<bool, 100032>;
	C c;
	c.fill(false);
	c[c.size() - 1] = true;

	bool result = true;
	for (auto _ : state)
		{
			bool is_sorted = std::is_sorted_until(c.cbegin(), c.cend()) == c.cend();
			result &= is_sorted;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
is_sorted_until_vector_bool(benchmark::State& state)
{
	using C = std::vector<bool>;
	C c(100032, false);
	c[c.size() - 1] = true;

	bool result = true;
	for (auto _ : state)
		{
			bool is_sorted = std::is_sorted_until(c.cbegin(), c.cend()) == c.cend();
			result &= is_sorted;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
is_sorted_until_bitset(benchmark::State& state)
{
	using C = std::bitset<100032>;
	C c;
	c.reset();
	c[c.size() - 1] = true;

	bool result = true;
	for (auto _ : state)
		{
			std::size_t i    = 0;
			std::size_t last = c.size();
			std::size_t next = i;
			while (++next != last)
				{
					bool next_val = c[next];
					bool i_val    = c[i];
					if (next_val < i_val)
						break;
					i = next;
				}
			result &= (next == last);
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
is_sorted_until_itsy_bitsy(benchmark::State& state)
{
	using C = bitsy::bit_vector<std::size_t>;
	C c(100032, false);
	c[c.size() - 1] = true;

	bool result = true;
	for (auto _ : state)
		{
			bool is_sorted = bitsy::bit_is_sorted_until(c.cbegin(), c.cend()) == c.cend();
			result &= is_sorted;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

static void
is_sorted_until_itsy_bitsy_sbv(benchmark::State& state)
{
	using C = bitsy::small_bit_vector<std::size_t>;
	C c(100032, false);
	c[c.size() - 1] = true;

	bool result = true;
	for (auto _ : state)
		{
			bool is_sorted = bitsy::bit_is_sorted_until(c.cbegin(), c.cend()) == c.cend();
			result &= is_sorted;
		}
	if (!result)
		{
			state.SkipWithError("bad benchmark result");
		}
}

BENCHMARK(is_sorted_until_by_hand);
BENCHMARK(is_sorted_until_base);
BENCHMARK(is_sorted_until_vector_bool);
BENCHMARK(is_sorted_until_bitset);
BENCHMARK(is_sorted_until_itsy_bitsy);
BENCHMARK(is_sorted_until_itsy_bitsy_sbv);
