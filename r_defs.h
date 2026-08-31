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


#ifndef __R_DEFS__
#define __R_DEFS__

// Color Graphics Adapter color palette.
#define CGA_COLOR_BLACK 0x000000
#define CGA_COLOR_BLUE 0x0000aa
#define CGA_COLOR_GREEN 0x00aa00
#define CGA_COLOR_CYAN 0x00aaaa
#define CGA_COLOR_RED 0xaa0000
#define CGA_COLOR_MAGENTA 0xaa00aa
#define CGA_COLOR_BROWN 0xaa5500
#define CGA_COLOR_DARK_YELLOW 0xaaaa00
#define CGA_COLOR_LIGHT_GRAY 0xaaaaaa
#define CGA_COLOR_DARK_GRAY 0x555555
#define CGA_COLOR_LIGHT_BLUE 0x5555ff
#define CGA_COLOR_LIGHT_GREEN 0x55ff55
#define CGA_COLOR_LIGHT_CYAN 0x55ffff
#define CGA_COLOR_LIGHT_RED 0xff5555
#define CGA_COLOR_LIGHT_MAGENTA 0xff55ff
#define CGA_COLOR_YELLOW 0xffff55
#define CGA_COLOR_WHITE 0xffffff

struct pattern_t {
   int tilewidth;
   int tileheight;
   uint8_t *pattern;
};

struct rectangle_t {
   char mode[4];
   int xcoord;
   int ycoord;
   int width;
   int height;
   uint32_t color;
};

#endif
/* EOF */
