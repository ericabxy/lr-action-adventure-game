void game_step(void);
void game_initialize(int x, int y);
void game_joystick_update(unsigned int up, unsigned int down, unsigned int left, unsigned int right);
void game_render_background(uint32_t *buf, unsigned stride, unsigned pixels);
void game_render_characters(uint32_t *buf, unsigned stride, unsigned pixels);
