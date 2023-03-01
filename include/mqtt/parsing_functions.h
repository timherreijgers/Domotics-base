#ifndef __PARSING_FUNCTIONS_H__
#define __PARSING_FUNCTIONS_H__

#include <string.h>
#include <inttypes.h>

/**
 * Namespace containing predefined parsing functions for the \ref MqttMessageParser
 */
namespace ParsingFunctions {

template <typename T>
int addToBuffer(const T& value, uint8_t * buffer);

int32_t parseUint8(const char * str, uint8_t * buffer);
int32_t parseUint16(const char * str, uint8_t * buffer);
int32_t parseUint32(const char * str, uint8_t * buffer);
int32_t parseInt8(const char * str, uint8_t * buffer);
int32_t parseInt16(const char * str, uint8_t * buffer);
int32_t parseInt32(const char * str, uint8_t * buffer);
int32_t parseFloat(const char * str, uint8_t * buffer);

inline int32_t parseInt(const char * str, uint8_t * buffer)
{
    return parseInt32(str, buffer);
}

inline int32_t parseChar(const char * str, uint8_t * buffer)
{
    return parseInt8(str, buffer);
}

template<typename T, T(* ParsingFunction)(const char * str)>
int parseCustom(const char * str, uint8_t * buffer)
{
    const auto value = ParsingFunction(str);
    return ParsingFunctions::addToBuffer(value, buffer);
}

template <typename T>
int addToBuffer(const T& value, uint8_t * buffer)
{
    memcpy(buffer, &value, sizeof(value));
    return sizeof(value);
}

} // namespace ParsingFunctions

#endif // __PARSING_FUNCTIONS_H__
