#include "data/array.h"

#include <gtest/gtest.h>

class ArrayTest : public ::testing::Test
{
public:
    void SetUp() override
    {
    }

    Data::Array<int, 5> m_array{};
};

TEST_F(ArrayTest, ArrayWithSize10ReturnsSize10)
{
    ASSERT_EQ(m_array.size(), 5);
}

TEST_F(ArrayTest, AddingToArrayAddToArrayCorrectly)
{
    m_array[1] = 100;
    ASSERT_EQ(m_array[1], 100);
}

TEST_F(ArrayTest, AddingTwoItemsToArrayAddToArrayCorrectly)
{
    m_array[1] = 200;
    m_array[2] = 1000000;
    ASSERT_EQ(m_array[1], 200);
    ASSERT_EQ(m_array[2], 1000000);
}

TEST_F(ArrayTest, AccessingItemUsingAtWorksCorrectly)
{
    m_array[2] = 1000000;
    ASSERT_EQ(m_array[2], m_array.at(2));
}

TEST_F(ArrayTest, AccessingFirstElementUsingDataFunctionWorksCorrectly)
{
    m_array[2] = 1000000;
    ASSERT_EQ(m_array[2], *((m_array.data()) + 2));
}

TEST_F(ArrayTest, ArraySupportsRangeBasedForLoop)
{
    for (const auto & _ : m_array)
    {
    }
}

TEST_F(ArrayTest, ConstArraySupportsRangeBasedForLoop)
{
    const Data::Array<int, 5> array{};

    for (const auto & _ : array)
    {
    }
}