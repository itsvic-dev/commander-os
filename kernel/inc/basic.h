#ifndef BASIC_H
#define BASIC_H

#include <cstddef>

extern "C" {
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
}

#endif // BASIC_H
