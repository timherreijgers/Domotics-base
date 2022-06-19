#include "utils/string.h"

#include <gtest/gtest.h>

TEST(StringAppendUnsafeTest, StringAppendUnsafe_OneInputString_GeneratesOutputString)
{
    char buffer[32] = {0};
    Utils::appendStringsUnsafe(buffer, "test");

    ASSERT_STREQ(buffer, "test");
}

TEST(StringAppendUnsafeTest, StringAppendUnsafe_TwoInputString_GeneratesOutputString)
{
    char buffer[32] = {0};
    Utils::appendStringsUnsafe(buffer, "test", "Tset");

    ASSERT_STREQ(buffer, "testTset");
}

TEST(StringAppendUnsafeTest, StringAppendUnsafe_ThreeInputString_GeneratesOutputString)
{
    char buffer[32] = {0};
    Utils::appendStringsUnsafe(buffer, "test", "Tset", "bla");

    ASSERT_STREQ(buffer, "testTsetbla");
}