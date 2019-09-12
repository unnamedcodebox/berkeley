#include <gtest/gtest.h>

#include "../src/core/Storage.h"

TEST(StorageMaxValueTest, Positive)
{
    std::string string("11 0 1 2 9");
    auto storage = new berkeley::Storage(string);

    EXPECT_EQ(9, storage->maxValue());
}

TEST(StorageMinValueTest, Positive)
{
    auto string = std::string("3 4 6 9 2 1");
    auto storage = new berkeley::Storage(string);

    EXPECT_EQ(1, storage->minValue());
}

TEST(StorageSumTest, Positive)
{
    auto string = std::string("1,3,2,7,9");
    auto storage = new berkeley::Storage(string);

    EXPECT_EQ(22, storage->sum());
}

TEST(StorageSortedTest, Positive)
{
    auto string = std::string("1,3,2,7,9");
    auto storage = new berkeley::Storage(string);

    auto other = std::string("0,9,0,3,2,7,8");
    auto otherStorage = new berkeley::Storage(other);

    EXPECT_EQ(std::string("9 7 3 2 1"), storage->toSortedString());
    EXPECT_EQ(std::string("9 8 7 3 2 0 0"), otherStorage->toSortedString());
    EXPECT_EQ(std::string(),otherStorage->toString());
}
