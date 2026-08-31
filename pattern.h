#define PLAYFIELD_Y 16

void pattern_render_check(uint32_t *buf, unsigned stride, unsigned pixels);
void pattern_render_playfield(uint32_t *buf, unsigned stride, unsigned pixels, uint64_t *pattern);
