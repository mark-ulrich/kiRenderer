#include <SDL2/SDL.h>

#include <sstream>

#include "kiError.h"
#include "types.h"
#include "zlib.h"

// TODO: I really should use zlib first, then come back to this implementation

// Deflate compressed data in `compressed` into `destBuffer`.
void
zlibDeflate(void* destBuffer, void* compressed)
{
  byte_t* src = (byte_t*)compressed;
  byte_t* dst = (byte_t*)destBuffer;

  byte_t cmf = src[0];
  // Verify deflate compression with 32K window
  if (cmf != 0x78) {
    kiFatal("zlibDeflate: bad compression method/window size");
  }

  // FCHECK:
  //   The FCHECK value must be such that CMF and FLG, when viewed as
  //   a 16-bit unsigned integer stored in MSB order (CMF*256 + FLG),
  //   is a multiple of 31.
  byte_t flg = src[1];
  if (((cmf << 8) + flg) % 31 != 0) {
    kiFatal("zlibDeflate: FCHECK check failed");
  }

  if (flg & 0b00100000) {
    kiFatal("FDICT should not be set");
  }

  // From RFC1950:
  // The information in FLEVEL is not needed for decompression; it
  // is there to indicate if recompression might be worthwhile.
  // u8 flevel = (flg & 0b11000000) >> 6;
  // std::stringstream ss;
  // ss << "Compression level: " << flevel;
  // kiInfo(ss.str());

  // Decompress data
  // for each block:
  //   read header bits   (NOT NECESSARILY ON BYTE BOUNDARY)
  //   ...

  u32 byteNeedle = 2;
  u32 bitNeedle = 0;
  u32 destNeedle = 0;
  for (;;) { // Forever, forever

    // Read header
    // TODO: Since the header bits are not necessarily on a byte boundary, we
    // will need to use a `bitNeedle` instead of hardcoding the bitmasks
    // bool isFinalBlock = src[byteNeedle] & 0x80;
    bool isFinalBlock = src[byteNeedle] & 0x01;
    if (isFinalBlock) {
      kiInfo("zlibDeflate: FINAL BLOCK");
    }

    // TODO: No reason to log any of this (except 3) in a production build
    bool isCompressedBlock = true;
    bool isDynamicHuffman = false;
    u32 blockType = (src[byteNeedle] & 0x2) | ((src[byteNeedle] & 0x4) >> 2);
    switch (blockType) {
      case 0:
        kiInfo("zlibDeflate: NO COMPRESSION");
        isCompressedBlock = false;
        break;
      case 1:
        kiInfo("zlibDeflate: FIXED CODES");
        break;
      case 2:
        kiInfo("zlibDeflate: DYNAMIC CODES");
        isDynamicHuffman = true;
        break;
      case 3: // Reserved (ERROR)
        kiWarning("zlibDeflate: What kind of DEFLATE is this?");
        return;
        break;
      default:
        kiFatal("zlibDeflate: How did I even get here?");
        break;
    }

    if (!isCompressedBlock) {
      // Skip to next byte boundary
      bitNeedle = 0;
      ++byteNeedle;

      u16 blockLen = src[byteNeedle];
      printf("blockLen: %u\n", blockLen);
      byteNeedle += 2;
      // TODO: Check NLEN

      ++byteNeedle += 2;
      SDL_memcpy(dst + destNeedle, src + byteNeedle, blockLen);
      destNeedle += blockLen;
      byteNeedle += blockLen;

      continue;
    }

    // TODO: Handle compressed block
    kiFatal("zlibDeflate: COMPRESSED BLOCK DECOMPRESSION NOT YET IMPLEMENTED");

    if (isFinalBlock)
      break;
  }

  // TODO: Remember the ADLER32 checksum
}
