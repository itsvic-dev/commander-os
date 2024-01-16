#ifndef DRIVERS_FB_FBDRIVER_H
#define DRIVERS_FB_FBDRIVER_H

#include <cstddef>
#include <cstdint>

class Framebuffer {
public:
  size_t width;
  size_t height;
  size_t scanline;

  virtual uint32_t *getRawData() = 0;
  virtual uint32_t getPixel(size_t x, size_t y) = 0;
  virtual void setPixel(size_t x, size_t y, uint32_t pixel) = 0;
};

#endif
