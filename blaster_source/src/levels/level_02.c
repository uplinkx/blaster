#include "main.h"
#include "entity.h"

t_wave_m	level_02(void)
{
	t_wave_m level_02 = {
		.wave_id = 1,
		.tick = 0,

		.win_kill_count = 0,
		.win_wave_no = 0,
		.win_wave = 3,

		.size = 4,
	};

	level_02.waves = SDL_malloc(sizeof(*(level_02.waves)) * level_02.size);


	level_02.waves[0] = (t_wave){0, WAVE_TICKS, 0, SDL_FALSE, SDL_TRUE, 9, SDL_FALSE, NULL};
	level_02.waves[0].wave_array = SDL_malloc(sizeof(*(level_02.waves[0].wave_array)) * level_02.waves[0].size);

	level_02.waves[0].wave_array[0] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {152, 0}, 0};
	level_02.waves[0].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 352}, 0};
	level_02.waves[0].wave_array[2] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 352}, 0};

	level_02.waves[0].wave_array[3] = (t_wave_elem){E_SLIME_GREEN, 0, 60, SDL_TRUE, {152, 0}, 0};
	level_02.waves[0].wave_array[4] = (t_wave_elem){E_SLIME_BLUE, 0, 70, SDL_TRUE, {0, 352}, 0};
	level_02.waves[0].wave_array[5] = (t_wave_elem){E_SLIME_BLUE, 0, 70, SDL_TRUE, {304, 352}, 0};

	level_02.waves[0].wave_array[6] = (t_wave_elem){E_SLIME_BLUE, 0, 150, SDL_TRUE, {152, 0}, 0};
	level_02.waves[0].wave_array[7] = (t_wave_elem){E_SLIME_GREEN, 0, 160, SDL_TRUE, {0, 352}, 0};
	level_02.waves[0].wave_array[8] = (t_wave_elem){E_SLIME_GREEN, 0, 160, SDL_TRUE, {304, 352}, 0};

	level_02.waves[1] = (t_wave){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 8, SDL_FALSE, NULL};
	level_02.waves[1].wave_array = SDL_malloc(sizeof(*(level_02.waves[1].wave_array)) * level_02.waves[1].size);

	level_02.waves[1].wave_array[0] = (t_wave_elem){E_SLIME_GREEN, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_02.waves[1].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 0}, 0};
	level_02.waves[1].wave_array[2] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 352}, 0};
	level_02.waves[1].wave_array[3] = (t_wave_elem){E_SLIME_GREEN, 0, 0, SDL_TRUE, {304, 352}, 0};

	level_02.waves[1].wave_array[4] = (t_wave_elem){E_SLIME_BLUE, 0, 60, SDL_TRUE, {0, 0}, 0};
	level_02.waves[1].wave_array[5] = (t_wave_elem){E_SLIME_GREEN, 0, 60, SDL_TRUE, {304, 0}, 0};
	level_02.waves[1].wave_array[6] = (t_wave_elem){E_SLIME_GREEN, 0, 60, SDL_TRUE, {0, 352}, 0};
	level_02.waves[1].wave_array[7] = (t_wave_elem){E_SLIME_BLUE, 0, 60, SDL_TRUE, {304, 352}, 0};


	level_02.waves[2] = (t_wave){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 9, SDL_FALSE, NULL};
	level_02.waves[2].wave_array = SDL_malloc(sizeof(*(level_02.waves[2].wave_array)) * level_02.waves[2].size);

	level_02.waves[2].wave_array[0] = (t_wave_elem){E_SLIME_GREEN, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_02.waves[2].wave_array[1] = (t_wave_elem){E_SLIME_GREEN, 0, 0, SDL_TRUE, {304, 0}, 0};
	level_02.waves[2].wave_array[2] = (t_wave_elem){E_SLIME_GREEN, 0, 0, SDL_TRUE, {152, 352}, 0};

	level_02.waves[2].wave_array[3] = (t_wave_elem){E_SLIME_BLUE, 0, 60, SDL_TRUE, {152, 0}, 0};
	level_02.waves[2].wave_array[4] = (t_wave_elem){E_SLIME_BLUE, 0, 60, SDL_TRUE, {0, 352}, 0};
	level_02.waves[2].wave_array[5] = (t_wave_elem){E_SLIME_BLUE, 0, 60, SDL_TRUE, {304, 352}, 0};

	level_02.waves[2].wave_array[6] = (t_wave_elem){E_SLIME_GREEN, 0, 140, SDL_TRUE, {0, 0}, 0};
	level_02.waves[2].wave_array[7] = (t_wave_elem){E_SLIME_GREEN, 0, 140, SDL_TRUE, {304, 0}, 0};
	level_02.waves[2].wave_array[8] = (t_wave_elem){E_SLIME_GREEN, 0, 140, SDL_TRUE, {152, 352}, 0};

	level_02.waves[3] = (t_wave){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 16, SDL_FALSE, NULL};
	level_02.waves[3].wave_array = SDL_malloc(sizeof(*(level_02.waves[3].wave_array)) * level_02.waves[3].size);

	level_02.waves[3].wave_array[0] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_02.waves[3].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 20, SDL_TRUE, {101, 0}, 0};
	level_02.waves[3].wave_array[2] = (t_wave_elem){E_SLIME_BLUE, 0, 40, SDL_TRUE, {203, 0}, 0};
	level_02.waves[3].wave_array[3] = (t_wave_elem){E_SLIME_BLUE, 0, 60, SDL_TRUE, {304, 0}, 0};
	level_02.waves[3].wave_array[4] = (t_wave_elem){E_SLIME_BLUE, 0, 80, SDL_TRUE, {304, 117}, 0};
	level_02.waves[3].wave_array[5] = (t_wave_elem){E_SLIME_BLUE, 0, 100, SDL_TRUE, {304, 234}, 0};
	level_02.waves[3].wave_array[6] = (t_wave_elem){E_SLIME_BLUE, 0, 120, SDL_TRUE, {304, 352}, 0};
	level_02.waves[3].wave_array[7] = (t_wave_elem){E_SLIME_BLUE, 0, 140, SDL_TRUE, {203, 352}, 0};
	level_02.waves[3].wave_array[8] = (t_wave_elem){E_SLIME_BLUE, 0, 160, SDL_TRUE, {101, 352}, 0};
	level_02.waves[3].wave_array[9] = (t_wave_elem){E_SLIME_BLUE, 0, 180, SDL_TRUE, {0, 352}, 0};
	level_02.waves[3].wave_array[10] = (t_wave_elem){E_SLIME_BLUE, 0, 200, SDL_TRUE, {0, 234}, 0};
	level_02.waves[3].wave_array[11] = (t_wave_elem){E_SLIME_BLUE, 0, 220, SDL_TRUE, {0, 117}, 0};
	level_02.waves[3].wave_array[12] = (t_wave_elem){E_SLIME_BLUE, 0, 240, SDL_TRUE, {0, 0}, 0};
	level_02.waves[3].wave_array[13] = (t_wave_elem){E_SLIME_BLUE, 0, 260, SDL_TRUE, {101, 0}, 0};
	level_02.waves[3].wave_array[14] = (t_wave_elem){E_SLIME_BLUE, 0, 280, SDL_TRUE, {203, 0}, 0};
	level_02.waves[3].wave_array[15] = (t_wave_elem){E_SLIME_BLUE, 0, 300, SDL_TRUE, {304, 0}, 0};

	return level_02;
}