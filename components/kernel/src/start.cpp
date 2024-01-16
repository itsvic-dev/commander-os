#include "drivers/fb/liminefb.h"
#include "hal/basic.h"
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

  // test: draw a 200x100 rectangle as a sanity test
  for (int y = 0; y < 100; y++) {
    for (int x = 0; x < 200; x++) {
      fb.setPixel(x, y, 0xFFFFFF);
    }
  }

  // we're done for now
  HAL::halt();
}
