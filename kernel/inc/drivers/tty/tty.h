#ifndef DRIVERS_TTY_TTY_H
#define DRIVERS_TTY_TTY_H

namespace Drivers {

class TTY {
public:
  virtual void putchar(const char c) = 0;
};

} // namespace Drivers

#endif
