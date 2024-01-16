#include "drivers/fb/liminefb.h"
#include "drivers/tty/flantermtty.h"
#include "hal/basic.h"
#include "logging.h"
#include <cstddef>
#include <cstdint>
#include <limine.h>

// Set the base revision to 1, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.
LIMINE_BASE_REVISION(1)

struct limine_framebuffer_request fbRequest = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0,
};

extern "C" void _start(void) {
  // Ensure the bootloader actually understands our base revision.
  if (LIMINE_BASE_REVISION_SUPPORTED == false) {
    HAL::halt();
  }

  if (fbRequest.response == NULL || fbRequest.response->framebuffer_count < 1) {
    HAL::halt();
  }

  // TODO: should be dynamic once we have MM
  Drivers::LimineFB fb(fbRequest.response->framebuffers[0]);
  Drivers::FlantermTTY tty(&fb);

  Logger::setTTY(&tty);
  Logger logger("start");
  logger.info("Hello, world!");

  // we're done for now
  HAL::halt();
}
