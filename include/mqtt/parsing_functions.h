#ifndef __PARSING_FUNCTIONS_H__
#define __PARSING_FUNCTIONS_H__

#include <string.h>

/**
 * Namespace containing predefined parsing functions for the \ref MqttMessageParser
 */
namespace ParsingFunctions {

template <typename T>
int addToBuffer(const T& value, char * buffer);

int parseInt(const char * str, char * buffer);
int parseFloat(const char * str, char * buffer);

template<typename T, T(* ParsingFunction)(const char * str)>
int parseCustom(const char * str, char * buffer)
{
    const auto value = ParsingFunction(str);
    return ParsingFunctions::addToBuffer(value, buffer);
}

template <typename T>
int addToBuffer(const T& value, char * buffer)
{
    memcpy(buffer, &value, sizeof(value));
    return sizeof(value);
}

} // namespace ParsingFunctions

#endif // __PARSING_FUNCTIONS_H__
