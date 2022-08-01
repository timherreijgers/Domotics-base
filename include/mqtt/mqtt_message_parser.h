#ifndef __MQTT_MESSAGE_PARSER_H__
#define __MQTT_MESSAGE_PARSER_H__

#include "data/array.h"
#include "utils/compile_time_checks.h"

#include <string.h>
#include <stdlib.h>

using MessageParserParseFunction = int(*)(const char * str, char * buffer);

namespace ParsingFunctions {

int parseInt(const char * str, char * buffer);
int parseFloat(const char * str, char * buffer);

} // namespace ParsingFunctions

template<typename T, size_t ElementCount>
class MqttMessageParser
{
public:
    template<typename ...Args>
    MqttMessageParser(char delimiter, Args... args)
    {
        static_assert(ElementCount == sizeof...(args), "Number of parsing functions doesn't equal the ElementCount");
        m_delimiter[0] = delimiter;
        m_delimiter[1] = 0x00;

        size_t index = 0;
        ((m_parsingFunctions[index++] = args), ...);
    }

    void parse(char * data, T & holder)
    {
        char buffer[sizeof(T)] = {0x00};
        size_t index = 0;
        size_t arrayIndex = 0;
        char * token = strtok(data, &m_delimiter);

        while(token != nullptr)
        {
            index += m_parsingFunctions[arrayIndex++](token, buffer + index);
            token = strtok(nullptr, &m_delimiter);
        }

        memcpy(&holder, buffer, sizeof(holder));
    }

private:
    friend class Factory;

    Data::Array<char, 2> m_delimiter;
    Data::Array<MessageParserParseFunction, ElementCount> m_parsingFunctions;
};

template <typename... Args>
MqttMessageParser(char delimiter, Args... args) -> MqttMessageParser<Args...>;

#endif // __MQTT_MESSAGE_PARSER_H__
