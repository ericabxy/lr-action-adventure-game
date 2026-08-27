/*
   Copyright 2026 Eric Abides

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/	   
#include <stdint.h>

#include "game.h"

#define BASE_WIDTH 160
#define BASE_HEIGHT 120
#define BASE_LEFT 0
#define BASE_TOP 0
#define BASE_RIGHT (BASE_LEFT + BASE_WIDTH)
#define BASE_BOTTOM (BASE_TOP + BASE_HEIGHT)
#define AVATAR_SIZE 8
#define AVATAR_INIT_X (BASE_WIDTH / 2) - (AVATAR_SIZE / 2)
#define AVATAR_INIT_Y (BASE_HEIGHT / 2) - (AVATAR_SIZE / 2)
#define CGA_BLACK 0x00000
#define CGA_DARK_GRAY 0x555555
#define CGA_LIGHT_GRAY 0xaaaaaa
#define CGA_YELLOW 0xffff55
#define CGA_WHITE 0xffffff

static int joystick_x;
static int joystick_y;
static int avatar_x;
static int avatar_y;

void game_initialize(int x, int y)
{
   avatar_x = AVATAR_INIT_X;
   avatar_y = AVATAR_INIT_Y;
   joystick_x = 0;
   joystick_y = 0;
}

void game_step(void)
{
   avatar_x += joystick_x;
   avatar_y += joystick_y;

   if (avatar_x < BASE_LEFT) {
      avatar_x = BASE_RIGHT - (BASE_LEFT - avatar_x);
   } else if (avatar_x > BASE_RIGHT) {
      avatar_x = BASE_LEFT + (avatar_x - BASE_RIGHT);
   }

   if (avatar_y < BASE_TOP) {
      avatar_y = BASE_BOTTOM - (BASE_TOP - avatar_y);
   } else if (avatar_y > BASE_BOTTOM) {
      avatar_y = BASE_TOP + (avatar_y - BASE_BOTTOM);
   }
}

void game_joystick_update(unsigned int up, unsigned int down, unsigned int left, unsigned int right)
{
   joystick_y = up ? -1 : 0;
   joystick_y = down ? 1 : joystick_y;
   joystick_x = left ? -1 : 0;
   joystick_x = right ? 1 : joystick_x;
}

void game_render_screen(uint32_t *buf, unsigned stride, unsigned pixels)
{
   uint32_t *line   = buf;

   for (unsigned y = 0; y < pixels / stride; y++, line += stride)
   {
      unsigned index_y = (y >> 4) & 1;
      for (unsigned x = 0; x < stride; x++)
      {
         unsigned index_x = (x >> 4) & 1;
         line[x] = (index_y ^ index_x) ? CGA_DARK_GRAY : CGA_LIGHT_GRAY;
      }
   }

   for (unsigned y = avatar_y; y <= avatar_y + AVATAR_SIZE; y++)
      for (unsigned x = avatar_x; x <= avatar_x + AVATAR_SIZE; x++)
         if (y * stride + x <= pixels && y * stride + x >= 0)
            buf[y * stride + x] = CGA_YELLOW;
}
