#ifndef KERNEL_LOG_H
#define KERNEL_LOG_H

#define LOG_TYPE_INFO    0
#define LOG_TYPE_ERROR   1
#define LOG_TYPE_WARNING 2
#define LOG_TYPE_SUCCESS 3

void log_write(const char *buffer, ...);

#endif
