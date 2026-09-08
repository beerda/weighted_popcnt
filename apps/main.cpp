#include <benchmark/benchmark.h>

#include "Chain.h"

static void BM_ChainSize(benchmark::State& state)
{
    Chain chain;

    for (auto _ : state) {
        benchmark::DoNotOptimize(chain.size());
    }
}

BENCHMARK(BM_ChainSize);

BENCHMARK_MAIN();
