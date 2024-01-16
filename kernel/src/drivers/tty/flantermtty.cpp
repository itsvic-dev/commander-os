#include "drivers/tty/flantermtty.h"
#include "backends/fb.h" // Flanterm FB backend
#include "drivers/fb/fbdriver.h"
#include "flanterm.h"

namespace Drivers {

FlantermTTY::FlantermTTY(Framebuffer *fb) {
  ftContext = flanterm_fb_simple_init(fb->getRawData(), fb->width, fb->height,
                                      fb->scanline * 4);
}

void FlantermTTY::putchar(const char c) { flanterm_write(ftContext, &c, 1); }

} // namespace Drivers
