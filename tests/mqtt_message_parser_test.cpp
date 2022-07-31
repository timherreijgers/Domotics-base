#include "mqtt/mqtt_message_parser.h"

#include <gtest/gtest.h>

struct TestInt
{
    int value1;
    int value2;
    int value3;
};

class MqttMessageParserTest : public ::testing::Test
{

};

TEST_F(MqttMessageParserTest, messageConsistingOfNoDataThrowsError)
{
    EXPECT_ANY_THROW(MqttMessageParser parser = MqttMessageParser<int>::Factory().build());
}

TEST_F(MqttMessageParserTest, messageConsistingOfOneIntParsesReturnsInt)
{
    MqttMessageParser parser = MqttMessageParser<int>::Factory().parseAsInt().build();
    int result = 0;

    parser.parse("100", result);

    ASSERT_EQ(result, 100);
}

//TEST_F(MqttMessageParserTest, messageConsistingOfTwoIntsWithCommaDelimiterStructContainingCorrectInts)
//{
//    MqttMessageParser parser = MqttMessageParser<int>::Factory().parseAsInt().build();
//    const auto result = parser.parse("100");
//
//    ASSERT_EQ(result, 100);
//}