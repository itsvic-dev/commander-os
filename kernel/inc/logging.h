#ifndef LOGGING_H
#define LOGGING_H

#include "drivers/tty/tty.h"
#include <cstdarg>

#define GET_LOGGER(component) static Logger logger(component)

class Logger {
public:
  enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
  };

  Logger(const char *component);
#define LOGFUNC(name)                                                          \
  void name(const char *fmt, ...) __attribute__((format(printf, 2, 3)))
  LOGFUNC(debug);
  LOGFUNC(info);
  LOGFUNC(warn);
  LOGFUNC(error);
#undef LOGFUNC

  /** Changes the TTY currenly in use for logging. */
  static void setTTY(Drivers::TTY *tty);
  static void setLogLevel(LogLevel level);

private:
  void log(LogLevel level, const char *fmt, va_list arguments);

  const char *m_component;
};

#endif
