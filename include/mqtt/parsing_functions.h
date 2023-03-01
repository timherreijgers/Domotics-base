#ifndef __PARSING_FUNCTIONS_H__
#define __PARSING_FUNCTIONS_H__

#include <string.h>
#include <inttypes.h>

/**
 * Namespace containing predefined parsing functions for the \ref MqttMessageParser
 */
namespace ParsingFunctions {

namespace Internal {

/**
 * Adds a value to the raw byte buffer containing the destination object. This functions returns the amount of bytes added to the buffer
 * so you can keep count of the required offset for the next value. The buffer pointer should point to the location where this specific
 * value must be added, thus adding the requirement to keep track of the offset.
 * @tparam T Input data type
 * @param value input value
 * @param buffer destination buffer
 * @return The amount of bytes added
 */
template <typename T>
int addToBuffer(const T & value, uint8_t * buffer)
{
    memcpy(buffer, &value, sizeof(value));
    return sizeof(value);
}

}

/**
 * Parses an uint8 from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
int32_t parseUint8(const char * str, uint8_t * buffer);

/**
 * Parses an uint16 from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 *
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
int32_t parseUint16(const char * str, uint8_t * buffer);

/**
 * Parses an uint32 from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 *
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
int32_t parseUint32(const char * str, uint8_t * buffer);

/**
 * Parses an int8 from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 *
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
int32_t parseInt8(const char * str, uint8_t * buffer);

/**
 * Parses an int16 from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 *
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
int32_t parseInt16(const char * str, uint8_t * buffer);

/**
 * Parses an int32 from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 *
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
int32_t parseInt32(const char * str, uint8_t * buffer);

/**
 * Parses an float from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 *
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
int32_t parseFloat(const char * str, uint8_t * buffer);

/**
 * Parses an int from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 *
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
inline int32_t parseInt(const char * str, uint8_t * buffer)
{
    return parseInt32(str, buffer);
}

/**
 * Parses a character from the input string and adds it to the buffer. It returns the amount of bytes added to the buffer
 *
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
inline int32_t parseChar(const char * str, uint8_t * buffer)
{
    return parseInt8(str, buffer);
}

/**
 * Parses a custom data structure (like an enum) from the input string using a specific parsing function and return the amount of bytes written
 * to the destination buffer. The parsing function must have the following prototype: T foo(const char * str). This parsing function must
 * initialize a variable of type T from the input string and return this.
 *
 * @tparam T The type to parse
 * @tparam ParsingFunction The function that parses type T
 * @param str The input string
 * @param buffer The destination buffer
 * @return The amount of bytes written
 */
template<typename T, T(* ParsingFunction)(const char * str)>
int parseCustom(const char * str, uint8_t * buffer)
{
    const auto value = ParsingFunction(str);
    return ParsingFunctions::Internal::addToBuffer(value, buffer);
}

} // namespace ParsingFunctions

#endif // __PARSING_FUNCTIONS_H__
