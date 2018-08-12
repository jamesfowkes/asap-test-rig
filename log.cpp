#include <stdio.h>
#include <stdarg.h>

#include "log.h"

#ifndef ARDUINO
#include <iostream>
#define platform_print(l) std::cout << l
#define platform_println(l) std::cout << l << std::endl
#else
#include <Arduino.h>
#define platform_print(l) Serial.print(l)
#define platform_println(l) Serial.println(l)
#endif

static char s_log_buffer[LOG_BUFFER_SIZE];
static char s_fmt_buffer[LOG_BUFFER_SIZE];

void p(char const * const fmt, ...)
{
    va_list args;
    va_start (args, fmt); vsnprintf(s_log_buffer, LOG_BUFFER_SIZE, fmt, args); va_end (args);
    platform_print(s_log_buffer);
}

void pln(char const * const fmt, ...)
{
    va_list args;
    va_start (args, fmt); vsnprintf(s_log_buffer, LOG_BUFFER_SIZE, fmt, args); va_end (args);
    platform_println(s_log_buffer);
}

void p_P(char const * const fmt, ...)
{
   	strcpy_P(s_fmt_buffer, fmt);
   	va_list args;
    va_start (args, fmt); vsnprintf(s_log_buffer, LOG_BUFFER_SIZE, s_fmt_buffer, args); va_end (args);
    platform_print(s_log_buffer);
}

void pln_P(char const * const fmt, ...)
{
   	strcpy_P(s_fmt_buffer, fmt);
   	va_list args;
    va_start (args, fmt); vsnprintf(s_log_buffer, LOG_BUFFER_SIZE, s_fmt_buffer, args); va_end (args);
    platform_println(s_log_buffer);
}
