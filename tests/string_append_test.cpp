#include "utils/string.h"

#include <gtest/gtest.h>

TEST(StringAppendTest, StringAppendUnsafe_OneInputString_GeneratesOutputString)
{
    char buffer[32];
    const auto result = Utils::appendStrings(buffer, 32, "test");

    ASSERT_TRUE(strcmp(buffer, "test"));
    ASSERT_EQ(result, true);
}

TEST(StringAppendUnsafeTest, StringAppend_TwoInputString_GeneratesOutputString)
{
    char buffer[32];
    const auto result = Utils::appendStrings(buffer, 32, "test", "Tset");

    ASSERT_TRUE(strcmp(buffer, "testTset"));
    ASSERT_EQ(result, true);
}

TEST(StringAppendUnsafeTest, StringAppend_ThreeInputString_GeneratesOutputString)
{
    char buffer[32];
    const auto result = Utils::appendStrings(buffer, 32, "test", "Tset", "bla");

    ASSERT_TRUE(strcmp(buffer, "testTsetbla"));
    ASSERT_EQ(result, true);
}

TEST(StringAppendUnsafeTest, StringAppend_MultipleInputStringOverflowingBuffer_GeneratesPartialOutputStringAndReturnsFalse)
{
    char buffer[32];
    const auto result = Utils::appendStrings(buffer, 32, "This string is long",
                                             ". This string makes it longer then 32 bytes, which should not be possible to add");

    ASSERT_TRUE(strcmp(buffer, "This string is long"));
    ASSERT_EQ(result, false);
}