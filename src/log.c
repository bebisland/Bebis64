#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

typedef struct {
  LogLevel level;
  FILE *file;
} LogState;

static LogState log_state = {LOG_LEVEL_INFO, NULL};

static const char *level_strings[] = {"INFO", "WARN", "ERROR", "FATAL"};

void log_init(void) {
  log_state.level = LOG_LEVEL_INFO;
  log_state.file = NULL;
}

void log_shutdown(void) {
  if (log_state.file) {
    fclose(log_state.file);
    log_state.file = NULL;
  }
}

void log_set_level(LogLevel level) { log_state.level = level; }

void log_set_file(const char *path) {
  if (log_state.file)
    fclose(log_state.file);

  log_state.file = fopen(path, "a");
  if (!log_state.file)
    fprintf(stderr, "LOG: could not open file: %s\n", path);
}

void log_write(LogLevel level, const char *file, int line, const char *fmt,
               ...) {
  if (level < log_state.level)
    return;

  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char timebuf[20];
  strftime(timebuf, sizeof(timebuf), "%H:%M:%S", tm);

  fprintf(stdout, "[%s] [%s] %s:%d: ", timebuf, level_strings[level], file,
          line);

  va_list args;
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);

  fprintf(stdout, "\n");
  fflush(stdout);

  if (log_state.file) {
    fprintf(log_state.file, "[%s] [%s] %s:%d: ", timebuf, level_strings[level],
            file, line);

    va_start(args, fmt);
    vfprintf(log_state.file, fmt, args);
    va_end(args);

    fprintf(log_state.file, "\n");
    fflush(log_state.file);
  }
}
