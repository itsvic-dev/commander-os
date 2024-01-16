#include "drivers/fb/liminefb.h"

namespace Drivers {

LimineFB::LimineFB(struct limine_framebuffer *fb)
    : m_fbAddress((uint32_t *)fb->address) {
  width = fb->width;
  height = fb->height;
  scanline = fb->pitch / 4;
}

uint32_t *LimineFB::getRawData() { return m_fbAddress; }
uint32_t LimineFB::getPixel(size_t x, size_t y) {
  if (x > width || y > height)
    return 0;
  return m_fbAddress[y * scanline + x];
}
void LimineFB::setPixel(size_t x, size_t y, uint32_t pixel) {
  if (x > width || y > height)
    return;
  m_fbAddress[y * scanline + x] = pixel;
}

} // namespace Drivers
