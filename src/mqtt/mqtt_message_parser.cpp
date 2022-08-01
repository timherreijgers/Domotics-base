#include "mqtt/mqtt_message_parser.h"

namespace ParsingFunctions {

int parseInt(const char * str, char * buffer)
{
    const auto value = atoi(str);
    return addToBuffer(value, buffer);
}

int parseFloat(const char * str, char * buffer)
{
    const auto value = strtof(str, nullptr);
    return addToBuffer(value, buffer);
}

} // namespace ParsingFunctions