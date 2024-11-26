#include "logger.h"
#include "utils/string.h"

#include <Arduino.h>

namespace Logger
{
static logMessageWriterFunction writerFunction = [](const char * message){Serial.println(message);};

void setLogMessageWriterFunction(const logMessageWriterFunction function)
{
    writerFunction = function;
}

void logMessage(const Data::string_literal level, const Data::string_literal fileAndLine, const char *message)
{
    char buffer[64] = {0};

    if(Utils::appendStrings(buffer, 64, "[", level.string(), "]", fileAndLine.string(), message))
    {
        writerFunction(buffer);
    }
}
};