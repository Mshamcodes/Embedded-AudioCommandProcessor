/**
    * @file logger.h
    * @brief Logging functionality for the audio command processor.
    *
    * This file provides the interface for the logging functionality in the audio command processor,
    * allowing messages to be logged at different levels: INFO, WARNING, ERROR, and INPUT.
 */

#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_INPUT,
} log_level_t;

// Function prototype for the actual logger
void log_message(log_level_t level, const char *format, ...);

// Logging macros for convenience
#define LOG_INFO(fmt, ...)    log_message(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) log_message(LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)   log_message(LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define LOG_INPUT(fmt, ...)   log_message(LOG_LEVEL_INPUT, fmt, ##__VA_ARGS__)



#endif // LOGGER_H