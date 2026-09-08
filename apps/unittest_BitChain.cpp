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

TEST(BitChain, CreatePartialSums2)
{
    std::vector<float> weights = {1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F};
    std::vector<float> expected_partial_sums = {1.0F, 2.0F, 3.0F,
                                                3.0F, 4.0F, 7.0F,
                                                5.0F, 6.0F, 11.0F};

    const std::vector<float> partial_sums = BitChain::createPartialSums(weights, 2);

    EXPECT_EQ(partial_sums.size(), expected_partial_sums.size());
    for (std::size_t index = 0; index < expected_partial_sums.size(); ++index) {
        EXPECT_FLOAT_EQ(partial_sums[index], expected_partial_sums[index]);
    }
}

TEST(BitChain, CreatePartialSums4)
{
    //                            1     2     4     8     1     2     4     8
    std::vector<float> weights = {1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F};
    std::vector<float> expected_partial_sums = {1.0F, 2.0F, 3.0F, 3.0F, 4.0F, 5.0F, 6.0F, 4.0F, 5.0F, 6.0F, 7.0F, 7.0F, 8.0F, 9.0F, 10.0F,
                                                5.0F, 6.0F, 11.0F, 7.0F, 12.0F, 13.0F, 18.0F, 8.0F, 13.0F, 14.0F, 19.0F, 15.0F, 20.0F, 21.0F, 26.0F};

    const std::vector<float> partial_sums = BitChain::createPartialSums(weights, 4);

    EXPECT_EQ(partial_sums.size(), expected_partial_sums.size());
    for (std::size_t index = 0; index < expected_partial_sums.size(); ++index) {
        EXPECT_FLOAT_EQ(partial_sums[index], expected_partial_sums[index]);
    }
}

TEST(BitChain, SumsWeightsUsingPartialSums)
{
    BitChain chain;
    chain.push_back(true);
    chain.push_back(false);
    chain.push_back(true);
    chain.push_back(true);
    chain.push_back(false);
    chain.push_back(false);
    chain.push_back(false);
    chain.push_back(true);

    std::vector<float> weights = {1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F};
    std::vector<float> partial_sums2 = BitChain::createPartialSums(weights, 2);
    std::vector<float> partial_sums4 = BitChain::createPartialSums(weights, 4);
    std::vector<float> partial_sums8 = BitChain::createPartialSums(weights, 8);

    EXPECT_EQ(partial_sums2.size(), 3 * 4); // 3 possible combinations for 2 bits, 4 blocks
    EXPECT_EQ(partial_sums4.size(), 15 * 2); // 15 possible combinations for 4 bits, 2 blocks
    EXPECT_EQ(partial_sums8.size(), 255 * 1); // 255 possible combinations for 8 bits, 1 block
    EXPECT_DOUBLE_EQ(chain.sum(weights), 16.0);
    EXPECT_DOUBLE_EQ(chain.sum(partial_sums2, 2), 16.0);
    EXPECT_DOUBLE_EQ(chain.sum(partial_sums4, 4), 16.0);
    EXPECT_DOUBLE_EQ(chain.sum(partial_sums8, 8), 16.0);
}
