#include "mqtt/mqtt_message_parser.h"
#include "utils/compile_time_checks.h"

namespace ParsingFunctions {

template<typename T>
inline constexpr bool isSigned()
{
    return static_cast<T>(T{} - 1) < T{};
}

template<typename T>
inline constexpr T getMaximumValue()
{
    return isSigned<T>() ? ~static_cast<T>(1 << sizeof(T) * 8 - 1) : ~T{};
}

template<typename T>
inline constexpr T getMinimumValue()
{
    return isSigned<T>() ? static_cast<T>(1 << sizeof(T) * 8 - 1) : 0;
}

template<typename T>
inline int32_t genericSignedIntParsingFunction(const char *str, uint8_t * buffer)
{
    static_assert(Utils::CompileTimeChecks::is_same<T, int8_t>::value ||
                      Utils::CompileTimeChecks::is_same<T, int16_t>::value ||
                      Utils::CompileTimeChecks::is_same<T, int32_t>::value,
                  "T should be either int8_t, int16_t, or int32_t");

    static constexpr T maximumValue = getMaximumValue<T>();
    static constexpr T minimumValue = getMinimumValue<T>();

    const auto value = strtol(str, NULL, 10);

    if(value > maximumValue)
        return Internal::addToBuffer(maximumValue, buffer);

    if(value < minimumValue)
        return Internal::addToBuffer(minimumValue, buffer);

    return Internal::addToBuffer(static_cast<T>(value), buffer);
}

template<typename T>
inline int32_t genericUnsignedIntParsingFunction(const char *str, uint8_t * buffer)
{
    static_assert(Utils::CompileTimeChecks::is_same<T, uint8_t>::value ||
                      Utils::CompileTimeChecks::is_same<T, uint16_t>::value ||
                      Utils::CompileTimeChecks::is_same<T, uint32_t>::value,
                  "T should be either uint8_t, uint16_t, or uint32_t");

    static constexpr T maximumValue = getMaximumValue<T>();

    const auto isValueNegative = str[0] == '-';
    const auto value = isValueNegative ? 0 : strtoul(str, NULL, 10);

    if(value > maximumValue)
        return Internal::addToBuffer(maximumValue, buffer);

    return Internal::addToBuffer(static_cast<T>(value), buffer);
}

int32_t parseUint8(const char * str, uint8_t * buffer)
{
    return genericUnsignedIntParsingFunction<uint8_t>(str, buffer);
}

int32_t parseUint16(const char * str, uint8_t * buffer)
{
    return genericUnsignedIntParsingFunction<uint16_t>(str, buffer);
}

int32_t parseUint32(const char * str, uint8_t * buffer)
{
    return genericUnsignedIntParsingFunction<uint32_t>(str, buffer);
}

int32_t parseInt8(const char * str, uint8_t * buffer)
{
    return genericSignedIntParsingFunction<int8_t>(str, buffer);
}

int32_t parseInt16(const char * str, uint8_t * buffer)
{
    return genericSignedIntParsingFunction<int16_t>(str, buffer);
}

int32_t parseInt32(const char * str, uint8_t * buffer)
{
    return genericSignedIntParsingFunction<int32_t>(str, buffer);
}

int32_t parseFloat(const char * str, uint8_t * buffer)
{
    const auto value = (float)atof(str);
    return Internal::addToBuffer(value, buffer);
}

} // namespace ParsingFunctions