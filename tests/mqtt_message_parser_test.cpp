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

test_enum parseTestEnum(const char * str)
{
    if (strcmp(str, "enum_value_1") == 0)
        return test_enum::enum_value_1;
    if (strcmp(str, "enum_value_2") == 0)
        return test_enum::enum_value_2;
    if (strcmp(str, "enum_value_3") == 0)
        return test_enum::enum_value_3;
    return test_enum::invalid;
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
    MqttMessageParser<int, 1> parser(',', ParsingFunctions::parseInt);

    const auto result = parser.parse("100");

    ASSERT_EQ(result, 100);
}

TEST_F(MqttMessageParserTest, messageConsistingOfTwoIntsWithCommaDelimiterStructContainingCorrectInts)
{
    using DataType = TestStruct<int, int>;

    MqttMessageParser<DataType, 2> parser(',',
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

    MqttMessageParser<DataType, 2> parser(':',
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

    MqttMessageParser<DataType, 2> parser(',',
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

    MqttMessageParser<DataType, 2> parser(',',
                                          ParsingFunctions::parseInt,
                                          ParsingFunctions::parseCustom<test_enum, parseTestEnum>);

    char buffer[] = "100,enum_value_1";
    const auto data = parser.parse(buffer);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, test_enum::enum_value_1);
}

TEST_F(MqttMessageParserTest, messageConsistingOfOneIntAndOneUnknownEnumWithCommaDelimiterStructContainingCorrectValues)
{
    using DataType = TestStruct<int, test_enum>;

    MqttMessageParser<DataType, 2> parser(',',
                                          ParsingFunctions::parseInt,
                                          ParsingFunctions::parseCustom<test_enum, parseTestEnum>);

    char buffer[] = "100,enum_value_10";
    const auto data = parser.parse(buffer);

    ASSERT_EQ(data.value1, 100);
    ASSERT_EQ(data.value2, test_enum::invalid);
}

TEST_F(MqttMessageParserTest, parsingFunctionUint8WorksCorrectly)
{
    MqttMessageParser<uint8_t, 1> parser(',', ParsingFunctions::parseUint8);

    ASSERT_EQ(10, parser.parse("10"));
    ASSERT_EQ(255, parser.parse("356"));
    ASSERT_EQ(0, parser.parse("-100"));
}

TEST_F(MqttMessageParserTest, parsingFunctionUint16WorksCorrectly)
{
    MqttMessageParser<uint16_t, 1> parser(',', ParsingFunctions::parseUint16);

    ASSERT_EQ(2784, parser.parse("2784"));
    ASSERT_EQ(65535, parser.parse("75536"));
    ASSERT_EQ(0, parser.parse("-75536"));
}

TEST_F(MqttMessageParserTest, parsingFunctionUint32WorksCorrectly)
{
    MqttMessageParser<uint32_t, 1> parser(',', ParsingFunctions::parseUint32);

    ASSERT_EQ(75536, parser.parse("75536"));
    ASSERT_EQ(4294967295, parser.parse("5294977296"));
    ASSERT_EQ(0, parser.parse("-5294977296"));
}

TEST_F(MqttMessageParserTest, parsingFunctionInt8WorksCorrectly)
{
    MqttMessageParser<int8_t, 1> parser(',', ParsingFunctions::parseInt8);

    ASSERT_EQ(10, parser.parse("10"));
    ASSERT_EQ(127, parser.parse("356"));
    ASSERT_EQ(-128, parser.parse("-356"));
}

TEST_F(MqttMessageParserTest, parsingFunctionInt16WorksCorrectly)
{
    MqttMessageParser<int16_t, 1> parser(',', ParsingFunctions::parseInt16);

    ASSERT_EQ(2784, parser.parse("2784"));
    ASSERT_EQ(32767, parser.parse("75536"));
    ASSERT_EQ(-32768, parser.parse("-75536"));
}


TEST_F(MqttMessageParserTest, parsingFunctionInt32WorksCorrectly)
{
    MqttMessageParser<int32_t, 1> parser(',', ParsingFunctions::parseInt32);

    ASSERT_EQ(75536, parser.parse("75536"));
    ASSERT_EQ(2147483647, parser.parse("8294977296"));
    ASSERT_EQ(-2147483648, parser.parse("-8294977296"));
}
