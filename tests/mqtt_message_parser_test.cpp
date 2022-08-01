#include "mqtt/mqtt_message_parser.h"

#include <gtest/gtest.h>
#include <string.h>

enum class test_enum
{
    enum_value_1,
    enum_value_2,
    enum_value_3,
    invalid
};

int parseTestEnum(const char * str, char * buffer)
{
    const auto value = [](const char * str) {
        if(strcmp(str, "enum_value_1") == 0) return test_enum::enum_value_1;
        if(strcmp(str, "enum_value_2") == 0) return test_enum::enum_value_2;
        if(strcmp(str, "enum_value_3") == 0) return test_enum::enum_value_3;
        return test_enum::invalid;
    }(str);

    memcpy(buffer, &value, sizeof(value));
    return sizeof(value);
}

template <typename FirstType, typename SecondType>
struct TestStruct
{
    FirstType value1;
    SecondType value2;
};

class MqttMessageParserTest : public ::testing::Test
{

};

TEST_F(MqttMessageParserTest, messageConsistingOfOneIntParsesReturnsInt)
{
    MqttMessageParser parser = MqttMessageParser<int, 1>('j', ParsingFunctions::parseInt);

    const auto result = parser.parse("100");

    ASSERT_EQ(result, 100);
}

TEST_F(MqttMessageParserTest, messageConsistingOfTwoIntsWithCommaDelimiterStructContainingCorrectInts)
{
    using DataType = TestStruct<int, int>;

    MqttMessageParser parser = MqttMessageParser<DataType, 2>(',',
                                                              ParsingFunctions::parseInt,
                                                              ParsingFunctions::parseInt);

    char buffer[] = "100,200";
    const auto data = parser.parse(buffer);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, 200);
}

TEST_F(MqttMessageParserTest, messageConsistingOfTwoIntsWithColonDelimiterStructContainingCorrectInts)
{
    using DataType = TestStruct<int, int>;

    MqttMessageParser parser = MqttMessageParser<DataType, 2>(':',
                                                              ParsingFunctions::parseInt,
                                                              ParsingFunctions::parseInt);

    char buffer[] = "100:200";
    const auto data = parser.parse(buffer);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, 200);
}

TEST_F(MqttMessageParserTest, messageConsistingOfOneIntAndOneFloatWithCommaDelimiterStructContainingCorrectValues)
{
    using DataType = TestStruct<int, float>;

    MqttMessageParser parser = MqttMessageParser<DataType, 2>(',',
                                                              ParsingFunctions::parseInt,
                                                              ParsingFunctions::parseFloat);

    char buffer[] = "100,3.14";
    const auto data = parser.parse(buffer);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, 3.14f);
}

TEST_F(MqttMessageParserTest, messageConsistingOfOneIntAndOneEnumWithCommaDelimiterStructContainingCorrectValues)
{
    using DataType = TestStruct<int, test_enum>;

    MqttMessageParser parser = MqttMessageParser<DataType, 2>(',',
                                                              ParsingFunctions::parseInt,
                                                              parseTestEnum);

    char buffer[] = "100,enum_value_1";
    const auto data = parser.parse(buffer);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, test_enum::enum_value_1);
}

TEST_F(MqttMessageParserTest, messageConsistingOfOneIntAndOneUnknownEnumWithCommaDelimiterStructContainingCorrectValues)
{
    using DataType = TestStruct<int, test_enum>;

    MqttMessageParser parser = MqttMessageParser<DataType, 2>(',',
                                                              ParsingFunctions::parseInt,
                                                              parseTestEnum);

    char buffer[] = "100,enum_value_10";
    const auto data = parser.parse(buffer);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, test_enum::invalid);
}
