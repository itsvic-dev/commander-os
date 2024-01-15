#include "hal/basic.h"
#include <cstddef>
#include <cstdint>
#include <limine.h>

// Set the base revision to 1, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.
LIMINE_BASE_REVISION(1)

struct limine_framebuffer_request framebuffer_request = {
    LIMINE_FRAMEBUFFER_REQUEST,
    0,
    nullptr,
};

extern "C" void _start(void) {
  // Ensure the bootloader actually understands our base revision (see spec).
  if (LIMINE_BASE_REVISION_SUPPORTED == false) {
    HAL::halt();
  }

  // Ensure we got a framebuffer.
  if (framebuffer_request.response == NULL ||
      framebuffer_request.response->framebuffer_count < 1) {
    HAL::halt();
  }

  // Fetch the first framebuffer.
  struct limine_framebuffer *framebuffer =
      framebuffer_request.response->framebuffers[0];

  // Note: we assume the framebuffer model is RGB with 32-bit pixels.
  for (size_t i = 0; i < 100; i++) {
    uint32_t *fb_ptr = (uint32_t *)framebuffer->address;
    fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
  }

  // We're done, just hang...
  HAL::halt();
}
