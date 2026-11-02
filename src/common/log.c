/**
 * @file log.c
 * @author Lubrin, Clarence, U.
 * @details Implements leveled emulator logging.
 */
#include "common/log.h"
#include <stdarg.h>
#include <stdio.h>

static LogLevel current_level = LOG_INFO;

void log_set_level(LogLevel level) { current_level = level; }

void log_message(LogLevel level, const char *file, int line, const char *fmt, ...)
{
    static const char *names[] = {"ERROR", "WARN", "INFO", "DEBUG", "TRACE"};
    if (level > current_level) return;
    fprintf(stderr, "[%s] %s:%d: ", names[level], file, line);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}
