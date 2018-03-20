#ifndef ARCH_LIB_LOG_H
#define ARCH_LIB_LOG_H

#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>

#define LOG_OFF 0
#define LOG_ERROR 1
#define LOG_INFO 2
#define LOG_DEBUG 3
#define LOG_TRACE 4
#define LOG_TRACE_DETAIL 5

int log_write(const char * info, int level);
int log_wdebug(const char * info);
int log_winfo(const char * info);
int log_werror(const char * error);
int log_trace(const char * file_name, const char * function_name, int line, int level);
int log_trace_msg(const char * file_name, const char * function_name, int line, int level, const char * message);
void log_setlevel(int level);

char * sformat(const char * format, ...);
char * sconcat(const char * first, const char * second);
const char * srepresent(const char * string);
const char * stoupper(const char * string);
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define vtrace log_trace(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, LOG_TRACE_DETAIL)
#define trace log_trace(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, LOG_TRACE)
#define log_error(...) log_trace_msg(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, LOG_ERROR, __VA_ARGS__)
#define log_info(...) log_trace_msg(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, LOG_INFO, __VA_ARGS__)
#define log_debug(...) log_trace_msg(__FILENAME__, __PRETTY_FUNCTION__, __LINE__, LOG_DEBUG, __VA_ARGS__)

#endif
