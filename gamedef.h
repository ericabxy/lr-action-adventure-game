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

#ifndef __GAMEDEF__
#define __GAMEDEF__

#define GAMEDEF_RAM_SIZE 64
#define GAMEDEF_SCREENWIDTH 160
#define GAMEDEF_SCREENHEIGHT 112

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

struct objinfo_t {
   uint16_t dynamics;  // Dynamic information.
   uint16_t stateval;  // State value.
   uint16_t state;  // State information.
   uint32_t color;  // Three-byte color value.
   uint8_t bwcolor;  // Store8.
   uint8_t size;  // Store9.
};

// Random Access Memory structure.
struct game_state_t {
   uint16_t room_graphics;  // 0x80 0x81.
   uint16_t object1_graphics;  // 0x82 0x83.
   uint16_t object2_graphics;  // 0x84 0x85.
   uint8_t object1_x;  // 0x86.
   uint8_t object1_y;  // 0x87.
   uint8_t object2_x;  // 0x88.
   uint8_t object2_y;  // 0x89.
   uint8_t current_room_number;  // 0x8A.
   uint8_t man_xcoord;  // 0x8B.
   uint8_t man_ycoord;  // 0x8C.
   uint8_t man_centerx;  // 0x8D.
   uint8_t current_scan_line;  // 0x8E.
   uint8_t roomdef_i;  // 0x8F.
   uint8_t object1def_i;  // 0x90.
   uint8_t object2def_i;  // 0x91.
   uint8_t current_console_switches;  // 0x92.
   uint16_t objinfo;  // 0x93 0x94.
   uint8_t object1_type;  // 0x95.
   uint8_t object2_type;  // 0x96.
   uint8_t object_collision;  // 0x97.
   // 0x98.
   uint8_t joysticks;  // 0x99.
};

struct object_t {
   uint16_t dynamicinfo;  // Store1 and Store2.
   uint16_t statevalue;  // Store3 and Store4.
   uint16_t stateinfo;  // Store5 and Store6.
   uint32_t color;  // Store7.
   uint8_t bwcolor;  // Store8.
   uint8_t size;  // Store9.
};

struct roomrow_t {
};

#endif
