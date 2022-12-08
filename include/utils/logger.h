//
// Created by Tim on 23/11/2022.
//

#ifndef DOMOTICSBASE_LOGGER_H
#define DOMOTICSBASE_LOGGER_H

#include <inttypes.h>
#include <string.h>

#define LOG_LEVEL_TRACE         0
#define LOG_LEVEL_DEBUG         1
#define LOG_LEVEL_INFO          2
#define LOG_LEVEL_WARNING       3
#define LOG_LEVEL_ERROR         4

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_TRACE
#endif

namespace Logger
{

    using LoggerCallbackFunction = void (*)(const char*);

    inline LoggerCallbackFunction s_callback = nullptr;
    extern char loggingBuffer[64];

    inline constexpr int logLevel = LOG_LEVEL;

    namespace Private
    {
        inline const char *prefix(const char *prefix, uint8_t size, const char *msg) {
            loggingBuffer[0] = 0x00;
            strcpy(loggingBuffer, prefix);
            strcpy(&(loggingBuffer[size]), msg);
            return loggingBuffer;
        }
    }

    inline void setLoggerCallback(LoggerCallbackFunction loggerCallback) noexcept
    {
        s_callback = loggerCallback;
    }

    inline void trace(const char * message)
    {
        if constexpr (logLevel <= LOG_LEVEL_TRACE)
        {
            s_callback(Logger::Private::prefix("[TRACE] ", sizeof("[TRACE] ") -1 ,message));
        }
    }

    inline void debug(const char *message) noexcept
    {
        if constexpr (logLevel <= LOG_LEVEL_INFO)
        {
            s_callback(Logger::Private::prefix("[DEBUG] ", sizeof("[DEBUG] ") -1 ,message));
        }
    }

    inline void info(const char *message) noexcept
    {
        if constexpr (logLevel <= LOG_LEVEL_DEBUG)
        {
            s_callback(Logger::Private::prefix("[INFO]  ", sizeof("[INFO]  ") -1 ,message));
        }
    }

    inline void warning(const char *message) noexcept
    {
        if constexpr (logLevel <= LOG_LEVEL_WARNING)
        {
            s_callback(Logger::Private::prefix("[WARN]  ", sizeof("[WARN]  ") -1 ,message));
        }
    }

    inline void error(const char *message) noexcept
    {
        if constexpr (logLevel <= LOG_LEVEL_ERROR)
        {
            s_callback(Logger::Private::prefix("[ERROR] ", sizeof("[ERROR] ") -1 ,message));
        }
    }
}

#endif //DOMOTICSBASE_LOGGER_H
