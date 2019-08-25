#include <benchmark/benchmark.h>
#include <bitset>
#include <vector>

static void rotate_by_hand(benchmark::State& state) {
	for (auto _ : state) {
		state.SkipWithError("Not implemented");
		return;
	}
}

static void rotate_vector_bool(benchmark::State& state) {
	for (auto _ : state) {
		state.SkipWithError("Not implemented");
		return;
	}
}

static void rotate_bitset(benchmark::State& state) {
	for (auto _ : state) {
		state.SkipWithError("Not implemented");
		return;
	}
}

static void rotate_bit_iterators_p0237(benchmark::State& state) {
	for (auto _ : state) {
		state.SkipWithError("Not implemented");
		return;
	}
}

BENCHMARK(rotate_by_hand);
BENCHMARK(rotate_vector_bool);
BENCHMARK(rotate_bitset);
BENCHMARK(rotate_bit_iterators_p0237);
