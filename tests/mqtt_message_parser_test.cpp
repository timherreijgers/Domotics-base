#include "mqtt/mqtt_message_parser.h"

#include <gtest/gtest.h>

class MqttMessageParserTest : public ::testing::Test
{

};

TEST_F(MqttMessageParserTest, test)
{
    MqttMessageParser parser();
    ASSERT_TRUE(true);
}