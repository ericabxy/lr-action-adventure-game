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
#include "r_shape.h"

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
#define TILEWIDTH 4
#define TILEHEIGHT 8
#define BACKGROUND_LINES 14

struct game_state_t game_state;
struct joystick_t joystick1;
struct playfield_t playfield;
struct rectangle_t avatar;
struct rectangle_t hud_rect;
struct rectangle_t radar_rect;
struct rectangle_t blip_rect;
static int joystick_x;
static int joystick_y;
static char current_room_number;
static char game_state_array[GAMEDEF_RAM_SIZE];

void game_initialize(void)
{
   current_room_number = WORLD_LENGTH / 2 - WORLD_WIDTH / 2;
   joystick_x = 0;
   joystick_y = 0;
   avatar.xcoord = AVATAR_INIT_X;
   avatar.ycoord = AVATAR_INIT_Y;
   avatar.width = AVATAR_SIZE;
   avatar.height = AVATAR_SIZE;
   avatar.color = CGA_COLOR_YELLOW;
   hud_rect.xcoord = 0;
   hud_rect.ycoord = 0;
   hud_rect.width = GAMEDEF_SCREENWIDTH;
   hud_rect.height = GAMEDEF_SCREENHEIGHT / 7;
   hud_rect.color = CGA_COLOR_BLACK;
   radar_rect.xcoord = LEFT + 4;
   radar_rect.ycoord = TOP;
   radar_rect.width = WORLD_WIDTH * GAMEDEF_SCREENWIDTH / 80;
   radar_rect.height = WORLD_LENGTH / WORLD_WIDTH * GAMEDEF_SCREENHEIGHT / 112;
   radar_rect.color = CGA_COLOR_BLUE;
   blip_rect.width = GAMEDEF_SCREENWIDTH / 80;
   blip_rect.height = GAMEDEF_SCREENHEIGHT / 112;
   blip_rect.color = CGA_COLOR_LIGHT_BLUE;
   playfield.xorigin = SCENE_LEFT_EDGE;
   playfield.yorigin = SCENE_TOP_EDGE;
   playfield.tilewidth = TILEWIDTH;
   playfield.tileheight = TILEHEIGHT;
   playfield.nlines = 14;
   playfield.ntiles = 40;
}

void game_advance_frame(void)
{
   //avatar.x += joystick_x;
   //avatar.y += joystick_y;
   // PlayerCollision.
   if (joystick1.right)
      avatar.xcoord ++;
   if (joystick1.left)
      avatar.xcoord --;
   if (joystick1.up)
      avatar.ycoord --;
   if (joystick1.down)
      avatar.ycoord ++;
   // TODO: Handle opening doors here.
   if (avatar.xcoord < SCENE_LEFT_EDGE) {
      avatar.xcoord = SCENE_RIGHT_EDGE - avatar.width;
      current_room_number--;
   } else if (avatar.xcoord + avatar.width > SCENE_RIGHT_EDGE) {
      avatar.xcoord = SCENE_LEFT_EDGE;
      current_room_number++;
   }

   if (avatar.ycoord < SCENE_TOP_EDGE) {
      avatar.ycoord = SCENE_BOTTOM_EDGE - avatar.height;
      current_room_number -= WORLD_WIDTH;
   } else if (avatar.ycoord > SCENE_BOTTOM_EDGE - avatar.height) {
      avatar.ycoord = SCENE_TOP_EDGE;
      current_room_number += WORLD_WIDTH;
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
   uint64_t pattern[14] = {
      0b0000000000000000000000000000000000000000,
      0b0000000000000000000000000000000000000000,
      0b1111001100111111110000111111110011001111,
      0b0000001100000011110000111100000011000000,
      0b0000001100000011110000111100000011000000,
      0b1111111111110011110000111100111111111111,
      0b1111111111110011110000111100111111111111,
      0b0000000000110011110000111100110000000000,
      0b0000000000110011110000111100110000000000,
      0b1111001100110011110000111100110011001111,
      0b1111001100110011110000111100110011001111,
      0b0000001100110011000000001100110011000000,
      0b0000001100110011000000001100110011000000,
      0b1111111100110011000000001100110011111111
   };
   playfield.pattern = pattern;
   // Draw background.
   R_DrawPlayfield(buf, stride, pixels, playfield);
   // Draw radars.
   R_DrawRectangle(buf, stride, pixels, radar_rect);
}

void game_render_characters(uint32_t *buf, unsigned stride, unsigned pixels)
{
   blip_rect.xcoord = (current_room_number % WORLD_WIDTH) * GAMEDEF_SCREENWIDTH / 80 + 4;
   blip_rect.ycoord = current_room_number / WORLD_WIDTH;
   // Draw the Man.
   R_DrawRectangle(buf, stride, pixels, avatar);
   // Draw radar blips.
   R_DrawRectangle(buf, stride, pixels, blip_rect);
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
