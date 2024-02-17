#include <gtest/gtest.h>

TEST(SimpleTestcases, OnePlusOneEqualsTwo) {
    int one = 1;
    EXPECT_EQ(2, one + one);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}