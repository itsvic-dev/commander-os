#ifndef DRIVERS_FB_LIMINE_H
#define DRIVERS_FB_LIMINE_H

#include "drivers/fb/fbdriver.h"
#include "limine.h"
#include <cstddef>

namespace Drivers {

class LimineFB : public Framebuffer {
public:
  LimineFB(struct limine_framebuffer *fb);

  uint32_t *getRawData() override;
  uint32_t getPixel(size_t x, size_t y) override;
  void setPixel(size_t x, size_t y, uint32_t pixel) override;

private:
  uint32_t *m_fbAddress;
};

}; // namespace Drivers

#endif
