#ifndef __MQTT_MESSAGE_PARSER_H__
#define __MQTT_MESSAGE_PARSER_H__

#include "data/array.h"

#include <string.h>
#include <stdlib.h>

template<typename T>
class MqttMessageParser
{
public:

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

    MqttMessageParser(char delimiter)
    {
        m_delimiter[0] = delimiter;
        m_delimiter[1] = 0x00;
    }

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

#endif // __MQTT_MESSAGE_PARSER_H__
