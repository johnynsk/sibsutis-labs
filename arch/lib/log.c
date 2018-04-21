#include "log.h"

int LOG_LEVEL_DBG = 0;

int log_trace(const char * file_name, const char * function_name, int line, int level)
{
    char logline[255] = "\0";
    char * truncated_file_name = file_name + 40;
    sprintf(logline, "%s:%d > %s", file_name, line, function_name);
    log_write(logline, level);
    return 0;
}


int log_trace_msg(const char * file_name, const char * function_name, int line, int level, const char * message)
{
    char logline[255] = "\0";
    char * truncated_file_name = file_name + 40;
    sprintf(logline, "%s:%d > %s: %s", file_name, line, function_name, message);
    log_write(logline, level);
    return 0;
}


int log_wdebug(const char * info)
{
    return log_write(info, LOG_DEBUG);
}

int log_winfo(const char * info)
{
    return log_write(info, LOG_INFO);
}

char * log_str_level(int level)
{
    if (level == LOG_ERROR) {
        return "ERROR ";
    } else if (level == LOG_INFO) {
        return "INFO  ";
    } else if (level == LOG_DEBUG) {
        return "DEBUG ";
    } else if (level == LOG_TRACE) {
        return "TRACE ";
    } else if (level == LOG_TRACE_DETAIL) {
        return "DETAIL";
    }
    return "UNKNOW";
}

int log_write(const char * info, int level)
{
    if (level > LOG_LEVEL_DBG) {
        return -2;
    }

    char time_buf[255] = "\0";
    const time_t timer = time(NULL);
    struct tm * timeinfo;
    timeinfo = localtime (&timer);
    strftime(time_buf, 26, "%Y %a %d %b %H:%M:%S", timeinfo);

    char line_buf[1024] = "\0";
    sprintf(line_buf, "%s [%s] %s\n", time_buf, log_str_level(level), info);

    int fd = open("debug.log", O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    ssize_t len = strlen(line_buf) * sizeof(char);
    if (write(fd, line_buf, len) != len) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

const char * sformat(const char * format, ...)
{
    char buffer[2048];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    buffer[2047] = '\0';
    char * result = (char*) malloc (sizeof(char) * strlen(buffer));
    strcpy(result, buffer);
    return result;
}

char * sconcat(const char * first, const char * second)
{
    char * result = malloc((strlen(first) + strlen(second) + 1) * sizeof(char));
    strcpy(result, first);
    strcat(result, second);

    return result;
}

const char * srepresent(const char * string)
{
    char * result;
    result = "";
    for (size_t i = 0; i < strlen(string); i++) {
        sconcat(result, sformat("%d|", (int)string[i]));
    }
    return result;
}

const char * stoupper(const char * string)
{
    char * result = (char*) malloc(sizeof(char) * strlen(string));
    strcpy(result, string);
    for (size_t i = 0; i < strlen(result); i++) {
        result[i] = toupper(result[i]);
    }

    return result;
}

void log_setlevel(int level)
{
    LOG_LEVEL_DBG = level;
}
