#include <cstdio>
#include <cstdlib>

#include "PNGLib.h"
#include "kiError.h"
#include "kiTypes.h"
#include "kiUtil.h"
#include "zlib.h"

#define PNG_IHDR 0x49484452
#define PNG_IDAT 0x49444154
#define PNG_IEND 0x49454E44

u8 PNG_MAGIC[8] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };

typedef struct
{
  u32 dataLength;
  u32 type;
  void* data;
  u32 crc;
} PNGChunk;

typedef struct
{
  i32 width, height;
  u8 bitDepth;
  u8 colorType;
  u8 compressionMethod;
  u8 filterMethod;
  u8 interlaceMethod;
} PNGIHDR;

typedef struct ChunkNode_s
{
  PNGChunk* chunk;
  struct ChunkNode_s* next;
} ChunkNode;

typedef struct
{
  PNGIHDR* IHDR; // Pointer to header data within the the IHDR chunk
  ChunkNode* chunks;
} PNGFile;

// TODO: Better error handling. (Should they really be fatal?)
// TODO: Free *ALL* allocated data
// NOTE: This does not currently perform CRC checks on the chunks
// TODO: This is big and messy; refactor
kiTexture*
LoadTexturePNG(std::string const& path)
{
  int width, height;
  char errbuf[256];
  char sChunkType[5];
  size_t totalDataLength;

  memset(sChunkType, 0, 5);

  // TODO: Implement a platform-independent file loader
  FILE* fp = nullptr;
  errno_t err = fopen_s(&fp, path.c_str(), "rb");
  if (err) {
    kiFatal("no file?");
  }

  // Check magic number
  u8 buf[sizeof(PNG_MAGIC)];
  fread(buf, 1, 8, fp);
  if (SDL_memcmp(PNG_MAGIC, buf, sizeof(PNG_MAGIC)) != 0) {
    kiFatal("ain't no magic here, bro");
  }

  // Read one chunk at a time, building list
  // NOTE: fp cursor should be at beginning of IHDR in a valid PNG file
  PNGFile png = {};

  // printf("\nLoading PNG texture (%s):\n", path.c_str());

  totalDataLength = 0;
  for (;;) {
    PNGChunk* chunk = new PNGChunk;
    // Read chunk header & flip from big endian
    fread(chunk, sizeof(u32), 2, fp);
    chunk->dataLength = SWAP_ENDIAN_32(chunk->dataLength);
    memcpy(sChunkType, &chunk->type, 4);
    chunk->type = SWAP_ENDIAN_32(chunk->type);

    puts("");
    puts("Chunk:");
    printf("type:  (%s) %#x\n", sChunkType, chunk->type);
    printf("len:   %d\n", chunk->dataLength);

    if (chunk->type == PNG_IHDR) {
      if (png.IHDR) {
        kiFatal("WUT 2 HEADERS");
      }

      // Read IHDR chunk; convert DWORDs from big-endian
      chunk->data = new PNGIHDR;
      png.IHDR = (PNGIHDR*)chunk->data;
      fread(&png.IHDR->width, sizeof(u32), 1, fp);
      png.IHDR->width = SWAP_ENDIAN_32(png.IHDR->width);
      fread(&png.IHDR->height, sizeof(u32), 1, fp);
      png.IHDR->height = SWAP_ENDIAN_32(png.IHDR->height);
      fread(&png.IHDR->bitDepth, 1, 1, fp);
      fread(&png.IHDR->colorType, 1, 1, fp);
      fread(&png.IHDR->compressionMethod, 1, 1, fp);
      fread(&png.IHDR->filterMethod, 1, 1, fp);
      fread(&png.IHDR->interlaceMethod, 1, 1, fp);

      puts("");
      printf("IHDR:\n");
      printf("width:             %d\n", png.IHDR->width);
      printf("height:            %d\n", png.IHDR->height);
      printf("colorType:         %d\n", png.IHDR->colorType);
      printf("compressionMethod: %d\n", png.IHDR->compressionMethod);
      printf("filterMethod:      %d\n", png.IHDR->filterMethod);
      printf("interlaceMethod:   %d\n", png.IHDR->interlaceMethod);
      puts("");

      // A little validation

      // At least for now, restrict to PNGs with RGBA pixels
      if (png.IHDR->colorType != 6) {
        kiFatal("we need RGBA PNGs, buddy");
      }
      // PNG only supports the `0` compression method as of now
      if (png.IHDR->compressionMethod != 0) {
        sprintf(errbuf,
                "Invalid compression method: %#x\n",
                png.IHDR->compressionMethod);
        kiFatal(errbuf);
      }
      if (png.IHDR->filterMethod != 0) {
        sprintf(
          errbuf, "Invalid filter method: %#x\n", png.IHDR->compressionMethod);
        kiFatal(errbuf);
      }
    } else if (chunk->type == PNG_IDAT) {
      totalDataLength += chunk->dataLength;
      chunk->data = new u8[chunk->dataLength];
      fread(chunk->data, 1, chunk->dataLength, fp);
    } else if (chunk->type == PNG_IEND) {
      // NADA
    } else {
      // Unsupported chunk type; log and skip
      fprintf(
        stderr, "Ignoring PNG chunk type: %s (%#x)\n", sChunkType, chunk->type);
      fseek(fp, chunk->dataLength, SEEK_CUR);
    }

    // TODO: For now, ignoring CRC
    fread(&chunk->crc, sizeof(u32), 1, fp);

    ChunkNode* node = new ChunkNode;
    ChunkNode* prev = png.chunks;
    memset(node, 0, sizeof(ChunkNode));
    node->chunk = chunk;
    if (!prev) {
      png.chunks = node;
    } else {
      while (prev->next) {
        prev = prev->next;
      }
      prev->next = node;
    }

    if (chunk->type == PNG_IEND)
      break;
  }

  fclose(fp);
  fp = NULL;

  width = png.IHDR->width;
  height = png.IHDR->height;

  // We now have the chunks mapped out. Copy data into buffer
  u8* compressedData = new u8[totalDataLength];
  ChunkNode* node = png.chunks;
  size_t totalCopied = 0;
  while (node) {
    if (node->chunk->type == PNG_IDAT) {
      memcpy(compressedData + totalCopied,
             (u8*)node->chunk->data,
             node->chunk->dataLength);
      totalCopied += node->chunk->dataLength;
    }
    printf("totalCopied: %lu\n", totalCopied);
    node = node->next;
  }

  // for (int i = 0; i < totalDataLength; ++i) {
  //   printf("%02x%c", compressedData[i], (i % 0x10 == 0) ? '\n' : ' ');
  // }

  // Clean up our list
  // TODO: Can we merge the cleanup code with the data extraction code above?
  ChunkNode* prev = nullptr;
  node = png.chunks;
  while (node) {
    if (node->chunk) {
      if (node->chunk->data) {
        if (node->chunk->type == PNG_IHDR) {
          delete (PNGIHDR*)node->chunk->data;
        } else if (node->chunk->type == PNG_IDAT) {
          delete[](u8*) node->chunk->data;
        }
      }
      delete node->chunk;
    }

    prev = node;
    node = node->next;
    delete prev;
  }

  // printf("totalDataLength: %d\n", totalDataLength);

  // Dump compressed data to file for testing
  fp = fopen("data.bin", "wb");
  fwrite(compressedData, 1, totalDataLength, fp);
  fclose(fp);
  fp = nullptr;

  // We have the zlib compressed data; uncompress to filtered data
  // NOTE: Don't forget the filter byte preceeding each scanline
  u8* filtered = new u8[width * height + height];
  zlibDeflate(filtered, compressedData);
  if (filtered) {
    kiWarning("well you ain't no Tom Brady");
  }

  // Handle filtering
  // TODO: is png.IHDR still valid at this point? Didn't we free it earlier?
  kiTexture* texture = new kiTexture(width, height);

  delete[] filtered;

  return texture;
}
