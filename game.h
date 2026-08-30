#ifndef __GAME__
#define __GAME__

struct joystick_t {
   unsigned int up : 1;
   unsigned int down : 1;
   unsigned int left : 1;
   unsigned int right : 1;
   unsigned int fire : 1;
   unsigned int strafe : 1;
   unsigned int use : 1;
   unsigned int speed : 1;
};

void game_advance_frame(void);
void game_initialize(void);
void game_joystick_update(unsigned int up, unsigned int down, unsigned int left, unsigned int right);
void game_render_background(uint32_t *buf, unsigned stride, unsigned pixels);
void game_render_characters(uint32_t *buf, unsigned stride, unsigned pixels);
void game_save_data(uint8_t *data);
void game_load_data(uint8_t *data);

#endif
