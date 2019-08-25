#include <benchmark/benchmark.h>
#include <bitset>
#include <vector>

static void swap_ranges_by_hand(benchmark::State& state) {
	for (auto _ : state) {
		state.SkipWithError("Not implemented");
		return;
	}
}

static void swap_ranges_vector_bool(benchmark::State& state) {
	for (auto _ : state) {
		state.SkipWithError("Not implemented");
		return;
	}
}

static void swap_ranges_bitset(benchmark::State& state) {
	for (auto _ : state) {
		state.SkipWithError("Not implemented");
		return;
	}
}

static void swap_ranges_bit_iterators_p0237(benchmark::State& state) {
	for (auto _ : state) {
		state.SkipWithError("Not implemented");
		return;
	}
}

BENCHMARK(swap_ranges_by_hand);
BENCHMARK(swap_ranges_vector_bool);
BENCHMARK(swap_ranges_bitset);
BENCHMARK(swap_ranges_bit_iterators_p0237);
