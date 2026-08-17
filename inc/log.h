#ifndef BEBIS64_LOG_H
#define BEBIS64_LOG_H

typedef enum {
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL
} LogLevel;

void log_init(void);
void log_shutdown(void);
void log_set_level(LogLevel level);
void log_set_file(const char *path);
void log_write(LogLevel level, const char *file, int line, const char *fmt,
               ...);

#define log_info(...) log_write(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_write(LOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)                                                         \
  log_write(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...)                                                         \
  log_write(LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#endif // BEBIS64_LOG_H
