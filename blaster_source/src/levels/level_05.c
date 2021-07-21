#include "main.h"
#include "entity.h"

t_wave	level_05(void)
{
	t_wave level_05 = {
		.wave_id = 4,
		.tick = 0,

		.win_kill_count = 0,
		.win_wave_no = 0,
		.win_wave = 3,

		.size = 4,
	};

	level_05.waves = SDL_malloc(sizeof(*(level_05.waves)) * level_05.size);

	level_05.waves[0] = (t_wave_m){0, WAVE_TICKS, 0, SDL_FALSE, SDL_TRUE, 4, SDL_FALSE, NULL};
	level_05.waves[0].wave_array = SDL_malloc(sizeof(*(level_05.waves[0].wave_array)) * level_05.waves[0].size);

	level_05.waves[0].wave_array[0] = (t_wave_elem){E_SLIME_INV, 0, 0, SDL_TRUE, {152, 0}, 0};
	level_05.waves[0].wave_array[1] = (t_wave_elem){E_SLIME_INV, 0, 0, SDL_TRUE, {152, 352}, 0};

	level_05.waves[0].wave_array[2] = (t_wave_elem){E_SLIME_INV, 0, 50, SDL_TRUE, {152, 0}, 0};
	level_05.waves[0].wave_array[3] = (t_wave_elem){E_SLIME_INV, 0, 50, SDL_TRUE, {152, 352}, 0};


	level_05.waves[1] = (t_wave_m){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 9, SDL_FALSE, NULL};
	level_05.waves[1].wave_array = SDL_malloc(sizeof(*(level_05.waves[1].wave_array)) * level_05.waves[1].size);

	level_05.waves[1].wave_array[0] = (t_wave_elem){E_SLIME_SPINY, 0, 0, SDL_TRUE, {152, 0}, 0};
	level_05.waves[1].wave_array[1] = (t_wave_elem){E_SLIME_SPINY, 0, 0, SDL_TRUE, {0, 352}, 0};
	level_05.waves[1].wave_array[2] = (t_wave_elem){E_SLIME_SPINY, 0, 0, SDL_TRUE, {304, 352}, 0};

	level_05.waves[1].wave_array[3] = (t_wave_elem){E_SLIME_SPINY, 0, 60, SDL_TRUE, {152, 0}, 0};
	level_05.waves[1].wave_array[4] = (t_wave_elem){E_SLIME_SPINY, 0, 60, SDL_TRUE, {0, 352}, 0};
	level_05.waves[1].wave_array[5] = (t_wave_elem){E_SLIME_SPINY, 0, 60, SDL_TRUE, {304, 352}, 0};

	level_05.waves[1].wave_array[6] = (t_wave_elem){E_SLIME_SPINY, 0, 120, SDL_TRUE, {152, 0}, 0};
	level_05.waves[1].wave_array[7] = (t_wave_elem){E_SLIME_SPINY, 0, 120, SDL_TRUE, {0, 352}, 0};
	level_05.waves[1].wave_array[8] = (t_wave_elem){E_SLIME_SPINY, 0, 120, SDL_TRUE, {304, 352}, 0};

	level_05.waves[2] = (t_wave_m){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 9, SDL_FALSE, NULL};
	level_05.waves[2].wave_array = SDL_malloc(sizeof(*(level_05.waves[2].wave_array)) * level_05.waves[2].size);

	level_05.waves[2].wave_array[0] = (t_wave_elem){E_SLIME_SPINY, 0, 0, SDL_TRUE, {152, 0}, 0};
	level_05.waves[2].wave_array[1] = (t_wave_elem){E_SLIME_SPINY, 0, 50, SDL_TRUE, {0, 0}, 0};
	level_05.waves[2].wave_array[2] = (t_wave_elem){E_SLIME_SPINY, 0, 50, SDL_TRUE, {304, 0}, 0};
	level_05.waves[2].wave_array[3] = (t_wave_elem){E_SLIME_SPINY, 0, 50, SDL_TRUE, {0, 352}, 0};
	level_05.waves[2].wave_array[4] = (t_wave_elem){E_SLIME_SPINY, 0, 50, SDL_TRUE, {304, 352}, 0};
	level_05.waves[2].wave_array[5] = (t_wave_elem){E_SLIME_SPINY, 0, 110, SDL_TRUE, {152, 0}, 0};
	level_05.waves[2].wave_array[6] = (t_wave_elem){E_SLIME_SPINY, 0, 110, SDL_TRUE, {0, 176}, 0};
	level_05.waves[2].wave_array[7] = (t_wave_elem){E_SLIME_SPINY, 0, 110, SDL_TRUE, {304, 176}, 0};
	level_05.waves[2].wave_array[8] = (t_wave_elem){E_SLIME_SPINY, 0, 110, SDL_TRUE, {152, 352}, 0};

	level_05.waves[3] = (t_wave_m){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 16, SDL_FALSE, NULL};
	level_05.waves[3].wave_array = SDL_malloc(sizeof(*(level_05.waves[3].wave_array)) * level_05.waves[3].size);

	level_05.waves[3].wave_array[0] = (t_wave_elem){E_SLIME_SPINY, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_05.waves[3].wave_array[1] = (t_wave_elem){E_SLIME_SPINY, 0, 20, SDL_TRUE, {101, 0}, 0};
	level_05.waves[3].wave_array[2] = (t_wave_elem){E_SLIME_SPINY, 0, 40, SDL_TRUE, {203, 0}, 0};
	level_05.waves[3].wave_array[3] = (t_wave_elem){E_SLIME_SPINY, 0, 60, SDL_TRUE, {304, 0}, 0};
	level_05.waves[3].wave_array[4] = (t_wave_elem){E_SLIME_SPINY, 0, 80, SDL_TRUE, {304, 117}, 0};
	level_05.waves[3].wave_array[5] = (t_wave_elem){E_SLIME_SPINY, 0, 100, SDL_TRUE, {304, 234}, 0};
	level_05.waves[3].wave_array[6] = (t_wave_elem){E_SLIME_SPINY, 0, 120, SDL_TRUE, {304, 352}, 0};
	level_05.waves[3].wave_array[7] = (t_wave_elem){E_SLIME_SPINY, 0, 140, SDL_TRUE, {203, 352}, 0};
	level_05.waves[3].wave_array[8] = (t_wave_elem){E_SLIME_SPINY, 0, 160, SDL_TRUE, {101, 352}, 0};
	level_05.waves[3].wave_array[9] = (t_wave_elem){E_SLIME_SPINY, 0, 180, SDL_TRUE, {0, 352}, 0};
	level_05.waves[3].wave_array[10] = (t_wave_elem){E_SLIME_SPINY, 0, 200, SDL_TRUE, {0, 234}, 0};
	level_05.waves[3].wave_array[11] = (t_wave_elem){E_SLIME_SPINY, 0, 220, SDL_TRUE, {0, 117}, 0};
	level_05.waves[3].wave_array[12] = (t_wave_elem){E_SLIME_SPINY, 0, 240, SDL_TRUE, {0, 0}, 0};
	level_05.waves[3].wave_array[13] = (t_wave_elem){E_SLIME_SPINY, 0, 260, SDL_TRUE, {101, 0}, 0};
	level_05.waves[3].wave_array[14] = (t_wave_elem){E_SLIME_SPINY, 0, 280, SDL_TRUE, {203, 0}, 0};
	level_05.waves[3].wave_array[15] = (t_wave_elem){E_SLIME_SPINY, 0, 300, SDL_TRUE, {304, 0}, 0};


	return level_05;
}