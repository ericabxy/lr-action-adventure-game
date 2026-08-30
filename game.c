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

#include "game.h"
#include "gamedef.h"
#include "pattern.h"
#include "rectangle.h"

#define LEFT 0
#define TOP 0
#define RIGHT GAMEDEF_SCREENWIDTH
#define BOTTOM GAMEDEF_SCREENHEIGHT
#define SCENE_LEFT_EDGE 0
#define SCENE_TOP_EDGE GAMEDEF_SCREENHEIGHT / 7
#define SCENE_RIGHT_EDGE GAMEDEF_SCREENWIDTH
#define SCENE_BOTTOM_EDGE GAMEDEF_SCREENHEIGHT
#define AVATAR_SIZE GAMEDEF_SCREENHEIGHT / 28
#define AVATAR_INIT_X (SCENE_RIGHT_EDGE / 2) - (AVATAR_SIZE / 2)
#define AVATAR_INIT_Y (SCENE_BOTTOM_EDGE / 2) - (AVATAR_SIZE / 2)
#define WORLD_LENGTH 256
#define WORLD_WIDTH 16

struct game_state_t game_state;
struct joystick_t joystick1;
static int joystick_x;
static int joystick_y;
static int avatar_x;
static int avatar_y;
static char avatar_loc;
static char game_state_array[GAMEDEF_RAM_SIZE];

void game_initialize(void)
{
   avatar_x = AVATAR_INIT_X;
   avatar_y = AVATAR_INIT_Y;
   avatar_loc = WORLD_LENGTH / 2 - WORLD_WIDTH / 2;
   joystick_x = 0;
   joystick_y = 0;
}

void game_advance_frame(void)
{
   //avatar_x += joystick_x;
   //avatar_y += joystick_y;
   // PlayerCollision.
   if (joystick1.right)
      avatar_x ++;
   if (joystick1.left)
      avatar_x --;
   if (joystick1.up)
      avatar_y --;
   if (joystick1.down)
      avatar_y ++;
   // TODO: Handle opening doors here.
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
   joystick1.right = right;
   joystick1.left = left;
   joystick1.up = up;
   joystick1.down = down;
}

void game_render_background(uint32_t *buf, unsigned stride, unsigned pixels)
{
   int minimap_x = avatar_loc % WORLD_WIDTH;
   int minimap_y = avatar_loc / WORLD_WIDTH;

   // Draw background.
   pattern_render_check(buf, stride, pixels);
   // Draw user interface.
   rectangle_render(buf, stride, pixels, LEFT, TOP, GAMEDEF_SCREENWIDTH, GAMEDEF_SCREENHEIGHT / 7, CGA_COLOR_BLACK);
   // Draw radars.
   rectangle_render(buf, stride, pixels, LEFT + 4, TOP, WORLD_WIDTH * GAMEDEF_SCREENWIDTH / 80, WORLD_LENGTH / WORLD_WIDTH * GAMEDEF_SCREENHEIGHT / 112, CGA_COLOR_BLUE);
   // Draw radar blips.
   rectangle_render(buf, stride, pixels, minimap_x * GAMEDEF_SCREENWIDTH / 80 + 4, minimap_y, GAMEDEF_SCREENWIDTH / 80, GAMEDEF_SCREENHEIGHT / 112, CGA_COLOR_LIGHT_BLUE);
}

void game_render_characters(uint32_t *buf, unsigned stride, unsigned pixels)
{
   rectangle_render(buf, stride, pixels, avatar_x, avatar_y, AVATAR_SIZE, AVATAR_SIZE, CGA_COLOR_YELLOW);
}

void game_save_data(uint8_t *data)
{
   for (unsigned int x = 0; x < GAMEDEF_RAM_SIZE; x++) {
      data[x] = game_state_array[x];
   }
}

void game_load_data(uint8_t *data)
{
   for (unsigned int x = 0; x < GAMEDEF_RAM_SIZE; x++) {
      game_state_array[x] = data[x];
   }
}
