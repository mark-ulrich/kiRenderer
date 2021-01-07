#ifndef __UTIL_H__
#define __UTIL_H__

#define SWAP_ENDIAN_32(x)                                                      \
  ((x >> 24) & 0xff) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) |           \
    ((x << 24) & 0xff000000)

#endif // __UTIL_H__
