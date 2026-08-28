#include <stdint.h>

#include "rectangle.h"
#include "cga_color.h"

void rectangle_render(uint32_t *buf, unsigned stride, unsigned pixels, int origin_x, int origin_y, int width, int height, int color)
{
   for (unsigned y = origin_y; y < origin_y + height; y++)
      for (unsigned x = origin_x; x < origin_x + width; x++)
         if (y * stride + x <= pixels && y * stride + x >= 0)
            buf[y * stride + x] = color;
}

void rellipse_render(uint32_t *buf, unsigned stride, unsigned pixels, int center_x, int center_y, int radius_x, int radius_y, int color)
{
   for (unsigned y = center_y - radius_y; y <= center_y + radius_y; y++)
      for (unsigned x = center_x - radius_x; x <= center_x + radius_x; x++)
         if (y * stride + x <= pixels && y * stride + x >= 0)
            buf[y * stride + x] = color;
}
