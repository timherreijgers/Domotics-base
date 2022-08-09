#ifndef __MQTT_MESSAGE_PARSER_H__
#define __MQTT_MESSAGE_PARSER_H__

#include "data/array.h"
#include "utils/compile_time_checks.h"
#include "parsing_functions.h"

#include <string.h>
#include <stdlib.h>

using MessageParserParseFunction = int(*)(const char * str, char * buffer);

/**
 * \brief MQTT message parser
 *
 * This class provides a generic interface to parse message received over MQTT, given that these messages follow this format:
 * [value][delimiter][value][delimiter][value]....
 *
 * In this message, the delimiter must be one character long, for example, a comma. The delimiter must also be consistent within
 * the message. A message following the format would be:
 * 100,3.14,ON
 *
 * The message parser is mostly constructed at compile time using templates, meaning that only messages can be used of which the
 * format is fully known at compile time. Using a lot of different messages formats might result in a big increase in binary size.
 *
 * \tparam T The type to parse
 * \tparam ElementCount The number of values in a message
 */
template<typename T, size_t ElementCount>
class MqttMessageParser
{
public:

    /**
	 * MqttMessageParser constructor initializing the mqtt message parser. It takes the delimiter and a list of parsing functions.
     * A few of these message parsing functions are declared within the namespace \ref ParsingFunctions. One of these functions
     * provides an interface for you to implement your own message parsing. The amount of parsing functions must equal
     * the ElementCount template argument. The first parsing function is used for the first value, the second parsing function
     * for the second value, and so on.
	 *
     * \tparam Args List of parsing function prototypes.
     *
	 * \param delimiter Delimiter separating values
     * \param args List of parsing functions
     */
    template<typename ...Args>
    MqttMessageParser(char delimiter, Args... args)
    {
        static_assert(ElementCount == sizeof...(args), "Number of parsing functions doesn't equal the ElementCount");
        m_delimiter[0] = delimiter;
        m_delimiter[1] = 0x00;

        size_t index = 0;
        ((m_parsingFunctions[index++] = args), ...);
    }

    /**
     * This function will actually parse a string into the object specified by T. The input string will be modified by
     * this functions, and thus will not be usable once this function is called.
     *
     * If parsing of the object fails, this function will always return an object of type T. This object can be partially
     * initialized. For the future it planned to provide better error handling for this function.
     *
     * \param data The input string to parse
     * \return The parsed object
     */
    T parse(char * data)
    {
        T holder{};
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
        return holder;
    }

private:
    Data::Array<char, 2> m_delimiter;
    Data::Array<MessageParserParseFunction, ElementCount> m_parsingFunctions;
};

template <typename... Args>
MqttMessageParser(char delimiter, Args... args) -> MqttMessageParser<Args...>;

#endif // __MQTT_MESSAGE_PARSER_H__
