#include "mqtt/mqtt_message_parser.h"
#include "utils/compile_time_checks.h"

namespace ParsingFunctions {

template<typename T>
inline constexpr bool isSigned()
{
    T t{};
    return static_cast<T>(t - 1) < t;
}

template<typename T>
inline constexpr T getMaximumValue()
{
    if(isSigned<T>())
        return ~static_cast<T>(1 << sizeof(T) * 8 - 1);

    constexpr T t{};
    return ~t;
}

template<typename T>
inline constexpr T getMinimumValue()
{
    if(isSigned<T>())
        return static_cast<T>(1 << sizeof(T) * 8 - 1);

    return 0;
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
        return addToBuffer(maximumValue, buffer);

    if(value < minimumValue)
        return addToBuffer(minimumValue, buffer);

    return addToBuffer(static_cast<T>(value), buffer);
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
        return addToBuffer(maximumValue, buffer);

    return addToBuffer(static_cast<T>(value), buffer);
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

int parseInt32(const char * str, uint8_t * buffer)
{
    return genericSignedIntParsingFunction<int32_t>(str, buffer);
}

int parseFloat(const char * str, uint8_t * buffer)
{
    const auto value = (float)atof(str);
    return addToBuffer(value, buffer);
}

} // namespace ParsingFunctions