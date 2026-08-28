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

#include "cga_color.h"
#include "game.h"
#include "pattern.h"
#include "rectangle.h"

#define SCENE_LEFT_EDGE 0
#define SCENE_TOP_EDGE 16
#define SCENE_RIGHT_EDGE GAME_VIDEO_WIDTH
#define SCENE_BOTTOM_EDGE GAME_VIDEO_HEIGHT
#define AVATAR_SIZE 4
#define AVATAR_INIT_X (SCENE_RIGHT_EDGE / 2) - (AVATAR_SIZE / 2)
#define AVATAR_INIT_Y (SCENE_BOTTOM_EDGE / 2) - (AVATAR_SIZE / 2)
#define WORLD_LENGTH 256
#define WORLD_WIDTH 16

static int joystick_x;
static int joystick_y;
static int avatar_x;
static int avatar_y;
static char avatar_loc;

void game_initialize(int x, int y)
{
   avatar_x = AVATAR_INIT_X;
   avatar_y = AVATAR_INIT_Y;
   avatar_loc = WORLD_LENGTH / 2 - WORLD_WIDTH / 2;
   joystick_x = 0;
   joystick_y = 0;
}

void game_step(void)
{
   avatar_x += joystick_x;
   avatar_y += joystick_y;

   if (avatar_x < SCENE_LEFT_EDGE) {
      avatar_x = SCENE_RIGHT_EDGE - AVATAR_SIZE;
      avatar_loc--;
   } else if (avatar_x + AVATAR_SIZE > SCENE_RIGHT_EDGE) {
      avatar_x = SCENE_LEFT_EDGE;
      avatar_loc++;
   }

   if (avatar_y < SCENE_TOP_EDGE) {
      avatar_y = SCENE_BOTTOM_EDGE - AVATAR_SIZE;
      avatar_loc -= WORLD_WIDTH;
   } else if (avatar_y > SCENE_BOTTOM_EDGE - AVATAR_SIZE) {
      avatar_y = SCENE_TOP_EDGE;
      avatar_loc += WORLD_WIDTH;
   }
}

void game_joystick_update(unsigned int up, unsigned int down, unsigned int left, unsigned int right)
{
   joystick_y = -up + down;
   joystick_x = -left + right;
}

void game_render_background(uint32_t *buf, unsigned stride, unsigned pixels)
{
   int minimap_x = avatar_loc % WORLD_WIDTH;
   int minimap_y = avatar_loc / WORLD_WIDTH;

   // Draw background.
   pattern_render_check(buf, stride, pixels);
   // Draw user interface.
   rectangle_render(buf, stride, pixels, GAME_UI_LEFT, GAME_UI_TOP, GAME_UI_WIDTH, GAME_UI_HEIGHT, CGA_COLOR_BLACK);
   rectangle_render(buf, stride, pixels, GAME_UI_LEFT, GAME_UI_TOP, WORLD_WIDTH * GAME_UI_BLIP_WIDTH, WORLD_LENGTH / WORLD_WIDTH * GAME_UI_BLIP_HEIGHT, CGA_COLOR_BLUE);
   rectangle_render(buf, stride, pixels, minimap_x * GAME_UI_BLIP_WIDTH, minimap_y, GAME_UI_BLIP_WIDTH, GAME_UI_BLIP_HEIGHT, CGA_COLOR_LIGHT_BLUE);
}

void game_render_characters(uint32_t *buf, unsigned stride, unsigned pixels)
{
   rectangle_render(buf, stride, pixels, avatar_x, avatar_y, AVATAR_SIZE, AVATAR_SIZE, CGA_COLOR_YELLOW);
}
