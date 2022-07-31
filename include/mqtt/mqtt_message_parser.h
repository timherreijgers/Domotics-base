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
        char * token = strtok(data, ",");

        while(token != nullptr)
        {
            const auto value = atoi(token);
            memcpy(buffer + index, &value, sizeof(value));
            index += sizeof(value);

            token = strtok(nullptr, ",");
        }

        memcpy(&holder, buffer, sizeof(holder));
    }

private:
    friend class Factory;

    MqttMessageParser()
    {
    }

public:
    class Factory
    {
    public:
        [[nodiscard]] Factory& delimiter(char delimiter)
        {
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

            return MqttMessageParser<T>();
        }

    private:
        bool m_throw = true;
    };
};

#endif // __MQTT_MESSAGE_PARSER_H__
