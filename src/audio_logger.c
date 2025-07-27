/**
     * @brief Logs a message at the specified log level.
     *
     * This function formats the log message and prints it to the standard output.
     *
     * @param level The log level (INFO, WARNING, ERROR, INPUT).
     * @param format The format string for the log message.
     * @param ... Additional arguments for the format string.
 */

#include <stdarg.h>
#include <stdio.h>
#include "audio_logger.h"

void log_message(log_level_t level, const char *format, ...) 
{
    const char *level_str;
    switch (level) {
        case LOG_LEVEL_INFO:    level_str = "[INFO] "; break;
        case LOG_LEVEL_WARNING: level_str = "[WARNING] "; break;
        case LOG_LEVEL_ERROR:   level_str = "[ERROR] "; break;
        case LOG_LEVEL_INPUT:   level_str = "[INPUT] "; break;
        default:                level_str = "[LOG] "; break;
    }

    printf("%s", level_str);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n");
}
