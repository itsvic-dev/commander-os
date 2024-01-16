#include "logging.h"
#include "drivers/tty/tty.h"
#include <cstdarg>
#include <cstdint>

static Drivers::TTY *currentTTY;
static Logger::LogLevel currentLevel = Logger::DEBUG;

void Logger::setTTY(Drivers::TTY *tty) { currentTTY = tty; }
void Logger::setLogLevel(LogLevel level) { currentLevel = level; }

Logger::Logger(const char *component) { m_component = component; }

#define LOGFUNC_IMPL(name, level)                                              \
  void Logger::name(const char *fmt, ...) {                                    \
    va_list args;                                                              \
    va_start(args, fmt);                                                       \
    log(level, fmt, args);                                                     \
    va_end(args);                                                              \
  }

LOGFUNC_IMPL(debug, DEBUG)
LOGFUNC_IMPL(info, INFO)
LOGFUNC_IMPL(warn, WARN)
LOGFUNC_IMPL(error, ERROR)

static void puts(const char *s) {
  while (*s) {
    currentTTY->putchar(*s++);
  }
}

#define GREEN "\033[32m"
#define WHITE "\033[37m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_WHITE "\033[97m"

void Logger::log(LogLevel level, const char *fmt, va_list arguments) {
  if (level < currentLevel) {
    return;
  }

  switch (level) {
  case DEBUG:
    puts(GREEN "DEBUG");
    break;
  case INFO:
    puts(BRIGHT_BLUE " INFO");
    break;
  case WARN:
    puts(BRIGHT_YELLOW " WARN");
    break;
  case ERROR:
    puts(BRIGHT_RED "ERROR");
    break;
  default:
    puts(BRIGHT_WHITE " WHAT");
  }

  currentTTY->putchar(' ');

  if (m_component != nullptr) {
    puts(WHITE);
    puts(m_component);
    puts(": ");
  }

  puts(BRIGHT_WHITE);

  while (*fmt) {
    if (*fmt == '%') {
      // printf format sequence
      bool hexStartsWith0x = false;
    whitespaceIgnore:
      fmt++;
      if (*fmt == ' ')
        goto whitespaceIgnore;
      else if (*fmt == 's') {
        // %s - print a string
        const char *str = va_arg(arguments, const char *);
        puts(str);
      } else if (*fmt == '#') {
        hexStartsWith0x = true;
        goto whitespaceIgnore;
      } else if (*fmt == 'p') {
        // %p - print a uintptr_t
        uintptr_t ptr = va_arg(arguments, uintptr_t);
#define HEX_SIZE (16) // assuming 64-bit
        char ptrInHex[HEX_SIZE] = {'0'};
        currentTTY->putchar('0');
        currentTTY->putchar('x');
        int i = HEX_SIZE - 1;
        do {
          ptrInHex[i] = "0123456789abcdef"[ptr % 16];
          i--;
          ptr = ptr / 16;
        } while (ptr > 0);
        for (i = 0; i < HEX_SIZE; i++) {
          currentTTY->putchar(ptrInHex[i]);
        }
#undef HEX_SIZE
      } else if (*fmt == '%') {
        currentTTY->putchar('%');
      } else {
        currentTTY->putchar('%');
        currentTTY->putchar(*fmt);
      }
    } else {
      // print char as normal
      currentTTY->putchar(*fmt);
    }
    fmt++;
  }

  currentTTY->putchar('\n');
}
