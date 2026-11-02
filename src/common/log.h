/**
 * @file log.h
 * @author Lubrin, Clarence, U.
 * @details Declares leveled emulator logging.
 */
#ifndef EMU_COMMON_LOG_H
#define EMU_COMMON_LOG_H

#include "common/types.h"

typedef enum {
    LOG_ERROR = 0, LOG_WARN, LOG_INFO, LOG_DEBUG, LOG_TRACE
} LogLevel;

void log_set_level(LogLevel level);
void log_message(LogLevel level, const char *file, int line, const char *fmt, ...);

#define LOGE(...) log_message(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOGW(...) log_message(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOGI(...) log_message(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOGD(...) log_message(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOGT(...) log_message(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)

#endif
