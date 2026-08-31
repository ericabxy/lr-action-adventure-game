#include <stdint.h>

#include "gamedef.h"
#include "pattern.h"

void pattern_render_check(uint32_t *buf, unsigned stride, unsigned pixels)
{
   uint32_t *line   = buf;

   for (unsigned y = 0; y < pixels / stride; y++, line += stride)
   {
      unsigned index_y = (y >> 3) & 1;
      for (unsigned x = 0; x < stride; x++)
      {
         unsigned index_x = (x >> 3) & 1;
         line[x] = (index_y ^ index_x) ? CGA_COLOR_DARK_GRAY : CGA_COLOR_LIGHT_GRAY;
      }
   }
}

void pattern_render_playfield(uint32_t *buf, unsigned stride, unsigned pixels, uint64_t *pattern)
{
   uint32_t *line   = buf;
   line += stride * PLAYFIELD_Y;

   for (unsigned y = PLAYFIELD_Y; y < pixels / stride; y++, line += stride)
   {
      unsigned index_y = y / 8;
      for (unsigned x = 0; x < stride; x++)
      {
         unsigned index_x = x / 4;
         uint64_t mask = 0x8000000000 >> index_x;
         line[x] = (mask & pattern[index_y % 14]) ? CGA_COLOR_LIGHT_GREEN : CGA_COLOR_LIGHT_GRAY;
      }
   }
}
