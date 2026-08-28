#define GAME_VIDEO_WIDTH 160
#define GAME_VIDEO_HEIGHT 128
#define GAME_UI_LEFT 0
#define GAME_UI_TOP 0
#define GAME_UI_WIDTH GAME_VIDEO_WIDTH
#define GAME_UI_HEIGHT 16
#define GAME_UI_BLIP_WIDTH 2
#define GAME_UI_BLIP_HEIGHT 1

void game_step(void);
void game_initialize(int x, int y);
void game_joystick_update(unsigned int up, unsigned int down, unsigned int left, unsigned int right);
void game_render_background(uint32_t *buf, unsigned stride, unsigned pixels);
void game_render_characters(uint32_t *buf, unsigned stride, unsigned pixels);
