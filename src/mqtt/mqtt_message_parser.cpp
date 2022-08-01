#include "mqtt/mqtt_message_parser.h"

namespace ParsingFunctions {

int parseInt(const char * str, char * buffer)
{
    const auto value = atoi(str);
    memcpy(buffer, &value, sizeof(value));
    return sizeof(value);
}

int parseFloat(const char * str, char * buffer)
{
    const auto value = strtof(str, nullptr);
    memcpy(buffer, &value, sizeof(value));
    return sizeof(value);
}

} // namespace ParsingFunctions