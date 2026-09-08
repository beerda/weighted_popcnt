#include <gtest/gtest.h>

#include "VectorChain.h"

TEST(VectorChain, StoresValues)
{
    VectorChain chain;

    chain.push_back(false);
    chain.push_back(true);
    chain.push_back(false);
    chain.push_back(true);

    EXPECT_EQ(chain.size(), 4);
    EXPECT_FALSE(chain.contains(0));
    EXPECT_TRUE(chain.contains(1));
    EXPECT_FALSE(chain.contains(2));
    EXPECT_TRUE(chain.contains(3));
}

TEST(VectorChain, ConjunctsValues)
{
    VectorChain left;
    left.push_back(true);
    left.push_back(false);
    left.push_back(true);
    left.push_back(true);

    VectorChain right;
    right.push_back(false);
    right.push_back(true);
    right.push_back(true);
    right.push_back(false);

    const VectorChain result = left.conjunctWith(right);

    EXPECT_EQ(result.size(), 4);
    EXPECT_FALSE(result.contains(0));
    EXPECT_FALSE(result.contains(1));
    EXPECT_TRUE(result.contains(2));
    EXPECT_FALSE(result.contains(3));
}

TEST(VectorChain, SumsWeightsForTrueValues)
{
    VectorChain chain;
    chain.push_back(true);
    chain.push_back(false);
    chain.push_back(true);

    EXPECT_DOUBLE_EQ(chain.sum({1.5F, 2.5F, 3.5F}), 5.0);
}