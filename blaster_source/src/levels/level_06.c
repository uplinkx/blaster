#include "main.h"
#include "entity.h"

t_wave_m	level_06(void)
{
	t_wave_m level_06 = {
		.wave_id = 0,
		.tick = 0,

		.win_kill_count = 0,
		.win_wave_no = 0,
		.win_wave = 1,

		.size = 2,
	};

	level_06.waves = SDL_malloc(sizeof(*(level_06.waves)) * level_06.size);

	level_06.waves[0] = (t_wave){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_TRUE, 12, SDL_FALSE, NULL};
	level_06.waves[0].wave_array = SDL_malloc(sizeof(*(level_06.waves[0].wave_array)) * level_06.waves[0].size);

	level_06.waves[0].wave_array[0] =  (t_wave_elem){E_SLIME_CYAN, 0, 25, SDL_TRUE, {0, 8}, 0};
	level_06.waves[0].wave_array[1] =  (t_wave_elem){E_SLIME_CYAN, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_06.waves[0].wave_array[2] =  (t_wave_elem){E_SLIME_CYAN, 0, 25, SDL_TRUE, {0, -8}, 0};
	level_06.waves[0].wave_array[3] =  (t_wave_elem){E_SLIME_BLUE, (4 << 8), 40, SDL_TRUE, {0, 0}, 0};

	level_06.waves[0].wave_array[4] =  (t_wave_elem){E_SLIME_CYAN, 0, 25 + 110, SDL_TRUE, {0, 180 + 8}, 0};
	level_06.waves[0].wave_array[5] =  (t_wave_elem){E_SLIME_CYAN, 0, 0 + 110, SDL_TRUE, {0, 180 + 0}, 0};
	level_06.waves[0].wave_array[6] =  (t_wave_elem){E_SLIME_CYAN, 0, 25 + 110, SDL_TRUE, {0, 180 + -8}, 0};
	level_06.waves[0].wave_array[7] =  (t_wave_elem){E_SLIME_BLUE, (4 << 8), 40 + 110, SDL_TRUE, {0, 180 + 0}, 0};

	level_06.waves[0].wave_array[8] =  (t_wave_elem){E_SLIME_CYAN, 0, 25 + 250, SDL_TRUE, {0, 12}, 0};
	level_06.waves[0].wave_array[9] =  (t_wave_elem){E_SLIME_CYAN, 0, 0 + 250, SDL_TRUE, {0, 0}, 0};
	level_06.waves[0].wave_array[10] = (t_wave_elem){E_SLIME_CYAN, 0, 25 + 250, SDL_TRUE, {0, -12}, 0};
	level_06.waves[0].wave_array[11] = (t_wave_elem){E_SLIME_BLUE, (4 << 8), 40 + 250, SDL_TRUE, {0, 0}, 0};


	return level_06;
}