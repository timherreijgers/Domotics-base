#include "mqtt/mqtt_message_parser.h"

#include <gtest/gtest.h>

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
    int result = 0;

    parser.parse("100", result);

    ASSERT_EQ(result, 100);
}

TEST_F(MqttMessageParserTest, messageConsistingOfTwoIntsWithCommaDelimiterStructContainingCorrectInts)
{
    using DataType = TestStruct<int, int>;

    MqttMessageParser parser = MqttMessageParser<DataType, 2>(',',
                                                              ParsingFunctions::parseInt,
                                                              ParsingFunctions::parseInt);
    DataType data;

    char buffer[] = "100,200";
    parser.parse(buffer, data);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, 200);
}

TEST_F(MqttMessageParserTest, messageConsistingOfTwoIntsWithColonDelimiterStructContainingCorrectInts)
{
    using DataType = TestStruct<int, int>;

    MqttMessageParser parser = MqttMessageParser<DataType, 2>(':',
                                                              ParsingFunctions::parseInt,
                                                              ParsingFunctions::parseInt);    DataType data;

    char buffer[] = "100:200";
    parser.parse(buffer, data);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, 200);
}

TEST_F(MqttMessageParserTest, messageConsistingOfOneIntAndOneFloatWithCommaDelimiterStructContainingCorrectInts)
{
    using DataType = TestStruct<int, float>;

    MqttMessageParser parser = MqttMessageParser<DataType, 2>(',',
                                                              ParsingFunctions::parseInt,
                                                              ParsingFunctions::parseFloat);
    DataType data;

    char buffer[] = "100,3.14";
    parser.parse(buffer, data);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, 3.14f);
}
