//
// Created by Tim on 29/07/2022.
//

#ifndef __MQTT_MESSAGE_PARSER_H__
#define __MQTT_MESSAGE_PARSER_H__

template<typename T>
class MqttMessageParser
{
public:

    void parse(const char * data, T & holder)
    {
        holder = 100;
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
