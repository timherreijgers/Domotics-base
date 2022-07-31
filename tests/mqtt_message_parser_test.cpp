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

TEST_F(MqttMessageParserTest, messageConsistingOfTwoIntsWithCommaDelimiterStructContainingCorrectInts)
{
    using DataType = TestStruct<int, int>;

    MqttMessageParser parser = MqttMessageParser<DataType>::Factory().delimiter(',').parseAsInt().parseAsInt().build();
    DataType data;

    parser.parse("100,200", data);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, 200);
}