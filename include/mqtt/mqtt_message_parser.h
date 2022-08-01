#ifndef __MQTT_MESSAGE_PARSER_H__
#define __MQTT_MESSAGE_PARSER_H__

#include "data/array.h"
#include "utils/compile_time_checks.h"

#include <string.h>
#include <stdlib.h>

using MessageParserParseFunction = void(*)();

template<typename T, typename ...Args>
class MqttMessageParser
{
public:

    MqttMessageParser(char delimiter, Args... args)
    {
        m_delimiter[0] = delimiter;
        m_delimiter[1] = 0x00;

        size_t index = 0;
        [[maybe_unused]] const auto size = m_parsingFunctions.size();
        ((m_parsingFunctions[index++] = args), ...);
    }

    void parse(char * data, T & holder)
    {
        char buffer[sizeof(T)] = {0x00};
        size_t index = 0;
        char * token = strtok(data, &m_delimiter);

        while(token != nullptr)
        {
            const auto value = atoi(token);
            memcpy(buffer + index, &value, sizeof(value));
            index += sizeof(value);

            token = strtok(nullptr, &m_delimiter);
        }

        memcpy(&holder, buffer, sizeof(holder));
    }

private:
    friend class Factory;

    Data::Array<char, 2> m_delimiter;
    Data::Array<MessageParserParseFunction, sizeof...(Args)> m_parsingFunctions;

public:
    class Factory
    {
    public:
        [[nodiscard]] Factory& delimiter(char delimiter)
        {
            m_delimiter = delimiter;
            return *this;
        }

        [[nodiscard]] Factory& parseAsInt()
        {
            m_throw = false;
            return *this;
        }

        [[nodiscard]] MqttMessageParser<T> build()
        {
            if(m_throw)
                throw "Why would you even try to build a parser without any data in it? :(";

            return MqttMessageParser<T>(m_delimiter);
        }

    private:
        bool m_throw = true;
        char m_delimiter = ',';
    };
};

template <typename... Args>
MqttMessageParser(char delimiter, Args... args) -> MqttMessageParser<Args...>;

#endif // __MQTT_MESSAGE_PARSER_H__
