#include <benchmark/benchmark.h>

#include <cstddef>
#include <random>
#include <vector>

#include "SparseChain.h"
#include "VectorChain.h"

#define CHAIN_SIZE 1000000


class SparseChainBenchmark : public benchmark::Fixture {
public:
    void SetUp(const benchmark::State&) override
    {
        std::mt19937 generator(42);
        std::bernoulli_distribution value_distribution(0.5);
        std::uniform_real_distribution<float> weight_distribution(1.0F, 10.0F);

        chain1_ = SparseChain{};
        chain2_ = SparseChain{};
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
        chain1_ = SparseChain{};
        chain2_ = SparseChain{};
        weights_.clear();
    }

protected:
    std::vector<float> weights_;
    SparseChain chain1_;
    SparseChain chain2_;
    SparseChain chain3_;
    double sum_result_ = 0.0;
};

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

class VectorChainBenchmark : public benchmark::Fixture {
public:
    void SetUp(const benchmark::State&) override
    {
        std::mt19937 generator(42);
        std::bernoulli_distribution value_distribution(0.5);
        std::uniform_real_distribution<float> weight_distribution(1.0F, 10.0F);

        chain1_ = VectorChain{};
        chain2_ = VectorChain{};
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
        chain1_ = VectorChain{};
        chain2_ = VectorChain{};
        weights_.clear();
    }

protected:
    std::vector<float> weights_;
    VectorChain chain1_;
    VectorChain chain2_;
    VectorChain chain3_;
    double sum_result_ = 0.0;
};

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

BENCHMARK_MAIN();
