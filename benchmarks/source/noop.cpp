#include <benchmark/benchmark.h>

static void
noop(benchmark::State& state)
{
	for (auto _ : state)
		{
		}
}

BENCHMARK(noop);
