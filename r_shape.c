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

void R_DrawRectangle(uint32_t *buf, unsigned stride, unsigned pixels, struct rectangle_t rectangle)
{
   for (unsigned y = rectangle.ycoord; y < rectangle.ycoord + rectangle.height; y++)
      for (unsigned x = rectangle.xcoord; x < rectangle.xcoord + rectangle.width; x++)
         if (y * stride + x <= pixels && y * stride + x >= 0)
            buf[y * stride + x] = rectangle.color;
}

/* EOF */
