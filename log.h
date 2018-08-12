#ifndef _LOG_H_
#define _LOG_H_

#define LOG_BUFFER_SIZE 64

void p(char const * const fmt, ...);
void pln(char const * const fmt, ...);

void p_P(char const * const fmt, ...);
void pln_P(char const * const fmt, ...);

#endif