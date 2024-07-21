#include <gtest/gtest.h>

#include "square.h"

TEST(Squaretest, BasicSquareTest)
{
    constexpr int to_be_squared(2);
    constexpr int expected(to_be_squared * to_be_squared);

    // Expect equality.
    EXPECT_EQ(square(to_be_squared), expected);
}