#include <gtest/gtest.h>

#include "Chain.h"

TEST(Chain, HasZeroSizeByDefault)
{
    Chain chain;

    EXPECT_EQ(chain.size(), 0);
}
