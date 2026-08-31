/* Copyright 2026 Eric Abides
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdint.h>

#include "r_defs.h"
#include "r_shape.h"

void R_DrawChecks(uint32_t *buf, unsigned stride, unsigned pixels)
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

void R_DrawPlayfield(uint32_t *buf, unsigned stride, unsigned pixels, uint64_t *pattern)
{
   uint32_t *line   = buf;
   line += stride * 16;

   for (unsigned y = 16; y < pixels / stride; y++, line += stride)
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

void R_DrawRectangle(uint32_t *buf, unsigned stride, unsigned pixels, struct rectangle_t rectangle)
{
   for (unsigned y = rectangle.ycoord; y < rectangle.ycoord + rectangle.height; y++)
      for (unsigned x = rectangle.xcoord; x < rectangle.xcoord + rectangle.width; x++)
         if (y * stride + x <= pixels && y * stride + x >= 0)
            buf[y * stride + x] = rectangle.color;
}

/* EOF */
