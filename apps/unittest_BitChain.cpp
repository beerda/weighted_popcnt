#include <gtest/gtest.h>

#include "BitChain.h"

TEST(BitChain, StoresValuesAcrossWordBoundaries)
{
    BitChain chain;

    for (std::size_t index = 0; index < 66; ++index) {
        chain.push_back(index == 0 || index == 63 || index == 64 || index == 65);
    }

    EXPECT_EQ(chain.size(), 66);
    EXPECT_TRUE(chain.contains(0));
    EXPECT_TRUE(chain.contains(63));
    EXPECT_TRUE(chain.contains(64));
    EXPECT_TRUE(chain.contains(65));
    EXPECT_FALSE(chain.contains(1));
    EXPECT_FALSE(chain.contains(62));
    EXPECT_FALSE(chain.contains(66));
}

TEST(BitChain, ConjunctsPackedWords)
{
    BitChain left;
    BitChain right;
    for (std::size_t index = 0; index < 66; ++index) {
        left.push_back(index == 0 || index == 63 || index == 64);
        right.push_back(index == 1 || index == 63 || index == 65);
    }

    const BitChain result = left.conjunctWith(right);

    EXPECT_EQ(result.size(), 66);
    EXPECT_TRUE(result.contains(63));
    EXPECT_FALSE(result.contains(0));
    EXPECT_FALSE(result.contains(64));
}

TEST(BitChain, SumsWeightsForTrueValues)
{
    BitChain chain;
    chain.push_back(true);
    chain.push_back(false);
    chain.push_back(true);

    EXPECT_DOUBLE_EQ(chain.sum({1.5F, 2.5F, 3.5F}), 5.0);
}