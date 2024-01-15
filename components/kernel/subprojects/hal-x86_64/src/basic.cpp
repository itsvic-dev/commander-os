#include "hal/basic.h"

void HAL::halt() {
  asm("cli");
  while (true) {
    asm("hlt");
  }
}
