#include "mqtt/mqtt_message_parser.h"

namespace ParsingFunctions {

int parseInt(const char * str, uint8_t * buffer)
{
    const auto value = atoi(str);
    return addToBuffer(value, buffer);
}

int parseFloat(const char * str, uint8_t * buffer)
{
    const auto value = (float)atof(str);
    return addToBuffer(value, buffer);
}

} // namespace ParsingFunctions