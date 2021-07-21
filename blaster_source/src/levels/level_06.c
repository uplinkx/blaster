#include "main.h"
#include "entity.h"

t_wave_m	level_06(void)
{
	t_wave_m level_06 = {
		.wave_id = 0,
		.tick = 0,

		.win_kill_count = 0,
		.win_wave_no = 0,
		.win_wave = 2,

		.size = 3,
	};

	level_06.waves = SDL_malloc(sizeof(*(level_06.waves)) * level_06.size);

	level_06.waves[0] = (t_wave){0, WAVE_TICKS, 0, SDL_FALSE, SDL_TRUE, 18, SDL_FALSE, NULL};
	level_06.waves[0].wave_array = SDL_malloc(sizeof(*(level_06.waves[0].wave_array)) * level_06.waves[0].size);

	level_06.waves[0].wave_array[0] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {152, 0}, 0};
	level_06.waves[0].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 352}, 0};
	level_06.waves[0].wave_array[2] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 352}, 0};
	level_06.waves[0].wave_array[3] = (t_wave_elem){E_SLIME_INV, 0, 5, SDL_TRUE, {152, 0}, 0};

	level_06.waves[0].wave_array[4] = (t_wave_elem){E_SLIME_INV, 0, 55, SDL_TRUE, {0, 352}, 0};
	level_06.waves[0].wave_array[5] = (t_wave_elem){E_SLIME_BLUE, 0, 50, SDL_TRUE, {152, 0}, 0};
	level_06.waves[0].wave_array[6] = (t_wave_elem){E_SLIME_BLUE, 0, 50, SDL_TRUE, {0, 352}, 0};
	level_06.waves[0].wave_array[7] = (t_wave_elem){E_SLIME_BLUE, 0, 50, SDL_TRUE, {304, 352}, 0};
	level_06.waves[0].wave_array[8] = (t_wave_elem){E_SLIME_INV, 0, 52, SDL_TRUE, {0, 0}, 0};

	level_06.waves[0].wave_array[9] = (t_wave_elem){E_SLIME_BLUE, 0, 100, SDL_TRUE, {152, 0}, 0};
	level_06.waves[0].wave_array[10] = (t_wave_elem){E_SLIME_BLUE, 0, 100, SDL_TRUE, {0, 352}, 0};
	level_06.waves[0].wave_array[11] = (t_wave_elem){E_SLIME_BLUE, 0, 100, SDL_TRUE, {304, 352}, 0};

	level_06.waves[0].wave_array[12] = (t_wave_elem){E_SLIME_INV, 0, 105, SDL_TRUE, {0, 352}, 0};
	level_06.waves[0].wave_array[13] = (t_wave_elem){E_SLIME_INV, 0, 90, SDL_TRUE, {304, 352}, 0};

	level_06.waves[0].wave_array[14] = (t_wave_elem){E_SLIME_INV, 0, 120, SDL_TRUE, {0, 0}, 0};
	level_06.waves[0].wave_array[15] = (t_wave_elem){E_SLIME_INV, 0, 120, SDL_TRUE, {304, 0}, 0};
	level_06.waves[0].wave_array[16] = (t_wave_elem){E_SLIME_INV, 0, 8, SDL_TRUE, {0, 352}, 0};
	level_06.waves[0].wave_array[17] = (t_wave_elem){E_SLIME_INV, 0, 55, SDL_TRUE, {304, 352}, 0};


	level_06.waves[1] = (t_wave){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 22, SDL_FALSE, NULL};
	level_06.waves[1].wave_array = SDL_malloc(sizeof(*(level_06.waves[1].wave_array)) * level_06.waves[1].size);

	level_06.waves[1].wave_array[0] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_06.waves[1].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 0}, 0};
	level_06.waves[1].wave_array[2] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 352}, 0};
	level_06.waves[1].wave_array[3] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 352}, 0};

	level_06.waves[1].wave_array[4] = (t_wave_elem){E_SLIME_INV, 0, 5, SDL_TRUE, {304, 352}, 0};
	level_06.waves[1].wave_array[5] = (t_wave_elem){E_SLIME_INV, 0, 10, SDL_TRUE, {152, 0}, 0};
	level_06.waves[1].wave_array[6] = (t_wave_elem){E_SLIME_INV, 0, 23, SDL_TRUE, {0, 352}, 0};

	level_06.waves[1].wave_array[7] = (t_wave_elem){E_SLIME_BLUE, 0, 40, SDL_TRUE, {0, 0}, 0};
	level_06.waves[1].wave_array[8] = (t_wave_elem){E_SLIME_BLUE, 0, 40, SDL_TRUE, {304, 0}, 0};
	level_06.waves[1].wave_array[9] = (t_wave_elem){E_SLIME_BLUE, 0, 40, SDL_TRUE, {0, 352}, 0};
	level_06.waves[1].wave_array[10] = (t_wave_elem){E_SLIME_BLUE, 0, 40, SDL_TRUE, {304, 352}, 0};
	level_06.waves[1].wave_array[11] = (t_wave_elem){E_SLIME_INV, 0, 30, SDL_TRUE, {0, 0}, 0};
	level_06.waves[1].wave_array[12] = (t_wave_elem){E_SLIME_INV, 0, 50, SDL_TRUE, {152, 352}, 0};

	level_06.waves[1].wave_array[13] = (t_wave_elem){E_SLIME_BLUE, 0, 80, SDL_TRUE, {0, 0}, 0};
	level_06.waves[1].wave_array[14] = (t_wave_elem){E_SLIME_BLUE, 0, 80, SDL_TRUE, {304, 0}, 0};
	level_06.waves[1].wave_array[15] = (t_wave_elem){E_SLIME_BLUE, 0, 80, SDL_TRUE, {0, 352}, 0};
	level_06.waves[1].wave_array[16] = (t_wave_elem){E_SLIME_BLUE, 0, 80, SDL_TRUE, {304, 352}, 0};

	level_06.waves[1].wave_array[17] = (t_wave_elem){E_SLIME_BLUE, 0, 70, SDL_TRUE, {152, 0}, 0};
	level_06.waves[1].wave_array[18] = (t_wave_elem){E_SLIME_BLUE, 0, 90, SDL_TRUE, {0, 352}, 0};
	level_06.waves[1].wave_array[19] = (t_wave_elem){E_SLIME_BLUE, 0, 60, SDL_TRUE, {304, 352}, 0};

	level_06.waves[1].wave_array[20] = (t_wave_elem){E_SLIME_INV, 0, 100, SDL_TRUE, {152, 0}, 0};
	level_06.waves[1].wave_array[21] = (t_wave_elem){E_SLIME_INV, 0, 100, SDL_TRUE, {0, 352}, 0};

	level_06.waves[2] = (t_wave){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 17, SDL_FALSE, NULL};
	level_06.waves[2].wave_array = SDL_malloc(sizeof(*(level_06.waves[2].wave_array)) * level_06.waves[2].size);

	level_06.waves[2].wave_array[0] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {152, 0}, 0};
	level_06.waves[2].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 352}, 0};
	level_06.waves[2].wave_array[2] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 352}, 0};

	level_06.waves[2].wave_array[3] = (t_wave_elem){E_SLIME_BLUE, 0, 15, SDL_TRUE, {152, 0}, 0};
	level_06.waves[2].wave_array[4] = (t_wave_elem){E_SLIME_BLUE, 0, 15, SDL_TRUE, {0, 352}, 0};
	level_06.waves[2].wave_array[5] = (t_wave_elem){E_SLIME_BLUE, 0, 15, SDL_TRUE, {304, 352}, 0};

	level_06.waves[2].wave_array[6] = (t_wave_elem){E_SLIME_BLUE, 0, 30, SDL_TRUE, {152, 0}, 0};
	level_06.waves[2].wave_array[7] = (t_wave_elem){E_SLIME_BLUE, 0, 30, SDL_TRUE, {0, 352}, 0};
	level_06.waves[2].wave_array[8] = (t_wave_elem){E_SLIME_BLUE, 0, 30, SDL_TRUE, {304, 352}, 0};

	level_06.waves[2].wave_array[9] = (t_wave_elem){E_SLIME_INV, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_06.waves[2].wave_array[10] = (t_wave_elem){E_SLIME_INV, 0, 5, SDL_TRUE, {304, 0}, 0};
	level_06.waves[2].wave_array[11] = (t_wave_elem){E_SLIME_INV, 0, 12, SDL_TRUE, {0, 352}, 0};
	level_06.waves[2].wave_array[12] = (t_wave_elem){E_SLIME_INV, 0, 24, SDL_TRUE, {304, 352}, 0};
	level_06.waves[2].wave_array[13] = (t_wave_elem){E_SLIME_INV, 0, 28, SDL_TRUE, {0, 0}, 0};
	level_06.waves[2].wave_array[14] = (t_wave_elem){E_SLIME_INV, 0, 30, SDL_TRUE, {304, 0}, 0};
	level_06.waves[2].wave_array[15] = (t_wave_elem){E_SLIME_INV, 0, 30, SDL_TRUE, {0, 352}, 0};
	level_06.waves[2].wave_array[16] = (t_wave_elem){E_SLIME_INV, 0, 40, SDL_TRUE, {304, 352}, 0};

	return level_06;
}