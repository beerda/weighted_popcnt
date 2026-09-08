#include <gtest/gtest.h>

#include "SparseChain.h"

TEST(SparseChain, StoresIndicesOfTrueValues)
{
    SparseChain chain;

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

TEST(SparseChain, ConjunctsTrueIndices)
{
    SparseChain left;
    left.push_back(true);
    left.push_back(false);
    left.push_back(true);
    left.push_back(true);

    SparseChain right;
    right.push_back(false);
    right.push_back(true);
    right.push_back(true);
    right.push_back(false);

    const SparseChain result = left.conjunctWith(right);

    EXPECT_EQ(result.size(), 4);
    EXPECT_FALSE(result.contains(0));
    EXPECT_FALSE(result.contains(1));
    EXPECT_TRUE(result.contains(2));
    EXPECT_FALSE(result.contains(3));
}