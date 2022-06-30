#include"main.h"
#include <gtest/gtest.h>

TEST(libTest, ReturnPositiveNumber) {
EXPECT_EQ(3, function(3));
}

TEST(indexTest, ReturnOne) {
EXPECT_EQ(1, returnOne());
}
