#pragma once

#include "data/string_literal.h"

/**
* \brief The logger
*
* The logger provides an easy way to log message in multiple different log levels. The log level has to be chosen on compile time
* and is LOG_LEVEL_WARNING by default. The supported log levels are:
*
* - LOG_LEVEL_TRACE = 1
* - LOG_LEVEL_DEBUG = 2
* - LOG_LEVEL_INFO = 3
* - LOG_LEVEL_WARNING = 4
* - LOG_LEVEL_ERROR = 5
* - LOG_LEVEL_NONE = 6
*
* The log level can be set by defining LOG_LEVEL to a value on compile time. This can be done through platformio. If the
* value is defined the defined version will be used. If the value is not defined it will default to LOG_LEVEL_WARNING.
* LOG_LEVEL_NONE will disable all logging. To log a message one of the LOG_* macros should be used. The ones available are:
*
* - LOG_TRACE
* - LOG_DEBUG
* - LOG_INFO
* - LOG_WARNING
* - LOG_ERROR
*
* These macros will get the current file and line number and include them in your logs.
*/

namespace Logger
{

/**
 * \brief Log message writer callback function type.
 */
using logMessageWriterFunction = void(*)(const char*);

/**
 * \brief Set the used callback function for writing log messages
 *
 * The goal of this function is to allow the user to set the behaviour on writing of the logger.
 * By default it will write to Serial.println(). This functions allows to override this behaviour to,
 * for example, write to a mqtt server.
 */
void setLogMessageWriterFunction(const logMessageWriterFunction function);

/**
 * \brief This function construct the message and write it to the writer function
 *
 * This function construct the message and write it to the writer function. It should not
 * be called by the user directly. Instead one of the LOG_* macros should be called.
 */
void logMessage(const Data::string_literal level, const Data::string_literal fileAndLine, const char *message);
} // namespace Logger

#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)

#define LOG_LEVEL_TRACE 1
#define LOG_LEVEL_DEBUG 2
#define LOG_LEVEL_INFO 3
#define LOG_LEVEL_WARNING 4
#define LOG_LEVEL_ERROR 5
#define LOG_LEVEL_NONE 6

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_WARNING
#endif

#if LOG_LEVEL <= LOG_LEVEL_TRACE
#define LOG_TRACE(message) Logger::logMessage("TRACE", "[" __FILE__ ":" STRINGIZE(__LINE__) "] ", message)
#else
#define LOG_TRACE(message)
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_DEBUG(message) Logger::logMessage("DEBUG", "[" __FILE__ ":" STRINGIZE(__LINE__) "] ", message)
#else
#define LOG_DEBUG(message)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(message) Logger::logMessage("INFO", "[" __FILE__ ":" STRINGIZE(__LINE__) "] ", message)
#else
#define LOG_INFO(message)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARNING
#define LOG_WARNING(message) Logger::logMessage("WARNING", "[" __FILE__ ":" STRINGIZE(__LINE__) "] ", message)
#else
#define LOG_WARNING(message)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_ERROR(message) Logger::logMessage("ERROR", "[" __FILE__ ":" STRINGIZE(__LINE__) "] ", message)
#else
#define LOG_ERROR(message)
#endif