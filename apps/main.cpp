#include <benchmark/benchmark.h>

#include <cstddef>
#include <random>
#include <vector>

#include "BitChain.h"
#include "SparseChain.h"
#include "VectorChain.h"

#define CHAIN_SIZE 1000000

template <typename ChainType>
class ChainBenchmark : public benchmark::Fixture {
public:
    void SetUp(const benchmark::State&) override
    {
        std::mt19937 generator(42);
        std::bernoulli_distribution value_distribution(0.5);
        std::uniform_real_distribution<float> weight_distribution(1.0F, 10.0F);

        chain1_ = ChainType{};
        chain2_ = ChainType{};
        weights_.clear();
        weights_.reserve(CHAIN_SIZE);

        for (std::size_t index = 0; index < CHAIN_SIZE; ++index) {
            chain1_.push_back(value_distribution(generator));
            chain2_.push_back(value_distribution(generator));
            weights_.push_back(weight_distribution(generator));
        }
        chain3_ = chain1_.conjunctWith(chain2_);
    }

    void TearDown(const benchmark::State&) override
    {
        chain1_ = ChainType{};
        chain2_ = ChainType{};
        weights_.clear();
    }

protected:
    std::vector<float> weights_;
    ChainType chain1_;
    ChainType chain2_;
    ChainType chain3_;
    double sum_result_ = 0.0;
};

using SparseChainBenchmark = ChainBenchmark<SparseChain>;
using VectorChainBenchmark = ChainBenchmark<VectorChain>;
using BitChainBenchmark = ChainBenchmark<BitChain>;

BENCHMARK_F(SparseChainBenchmark, ConjunctWith)(benchmark::State& state)
{
    for (auto _ : state) {
        chain3_ = chain1_.conjunctWith(chain2_);
        benchmark::DoNotOptimize(chain3_);
    }
}

BENCHMARK_F(SparseChainBenchmark, Sum)(benchmark::State& state)
{
    for (auto _ : state) {
        sum_result_ = chain3_.sum(weights_);
        benchmark::DoNotOptimize(sum_result_);
    }
}

BENCHMARK_F(VectorChainBenchmark, ConjunctWith)(benchmark::State& state)
{
    for (auto _ : state) {
        chain3_ = chain1_.conjunctWith(chain2_);
        benchmark::DoNotOptimize(chain3_);
    }
}

BENCHMARK_F(VectorChainBenchmark, Sum)(benchmark::State& state)
{
    for (auto _ : state) {
        sum_result_ = chain3_.sum(weights_);
        benchmark::DoNotOptimize(sum_result_);
    }
}

BENCHMARK_F(BitChainBenchmark, ConjunctWith)(benchmark::State& state)
{
    for (auto _ : state) {
        chain3_ = chain1_.conjunctWith(chain2_);
        benchmark::DoNotOptimize(chain3_);
    }
}

BENCHMARK_F(BitChainBenchmark, Sum)(benchmark::State& state)
{
    for (auto _ : state) {
        sum_result_ = chain3_.sum(weights_);
        benchmark::DoNotOptimize(sum_result_);
    }
}

BENCHMARK_MAIN();
