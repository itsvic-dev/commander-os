#ifndef DRIVERS_TTY_FLANTERMTTY_H
#define DRIVERS_TTY_FLANTERMTTY_H

#include "drivers/fb/fbdriver.h"
#include "drivers/tty/tty.h"
#include "flanterm.h"

namespace Drivers {

class FlantermTTY : public TTY {
public:
  FlantermTTY(Framebuffer *fb);
  void putchar(const char c) override;

private:
  struct flanterm_context *ftContext;
};

} // namespace Drivers

#endif
