#include <stdint.h>

#include "pattern.h"
#include "cga_color.h"

void pattern_render_check(uint32_t *buf, unsigned stride, unsigned pixels)
{
   uint32_t *line   = buf;

   for (unsigned y = 0; y < pixels / stride; y++, line += stride)
   {
      unsigned index_y = (y >> 4) & 1;
      for (unsigned x = 0; x < stride; x++)
      {
         unsigned index_x = (x >> 4) & 1;
         line[x] = (index_y ^ index_x) ? CGA_COLOR_DARK_GRAY : CGA_COLOR_LIGHT_GRAY;
      }
   }
}
