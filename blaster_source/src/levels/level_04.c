#include "main.h"
#include "entity.h"

t_wave	level_04(void)
{
	t_wave level_04 = {
		.wave_id = 3,
		.tick = 0,

		.win_kill_count = 0,
		.win_wave_no = 0,
		.win_wave = 2,

		.size = 3,
	};

	level_04.waves = SDL_malloc(sizeof(*(level_04.waves)) * level_04.size);


	level_04.waves[0] = (t_wave_m){0, WAVE_TICKS, 0, SDL_FALSE, SDL_TRUE, 9, SDL_FALSE, NULL};
	level_04.waves[0].wave_array = SDL_malloc(sizeof(*(level_04.waves[0].wave_array)) * level_04.waves[0].size);

	level_04.waves[0].wave_array[0] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {152, 0}, 0};
	level_04.waves[0].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 352}, 0};
	level_04.waves[0].wave_array[2] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 352}, 0};

	level_04.waves[0].wave_array[3] = (t_wave_elem){E_SLIME_YELLOW, 0, 50, SDL_TRUE, {152, 0}, 0};
	level_04.waves[0].wave_array[4] = (t_wave_elem){E_SLIME_BLUE, 0, 50, SDL_TRUE, {0, 352}, 0};
	level_04.waves[0].wave_array[5] = (t_wave_elem){E_SLIME_BLUE, 0, 50, SDL_TRUE, {304, 352}, 0};

	level_04.waves[0].wave_array[6] = (t_wave_elem){E_SLIME_BLUE, 0, 100, SDL_TRUE, {152, 0}, 0};
	level_04.waves[0].wave_array[7] = (t_wave_elem){E_SLIME_BLUE, 0, 100, SDL_TRUE, {0, 352}, 0};
	level_04.waves[0].wave_array[8] = (t_wave_elem){E_SLIME_BLUE, 0, 100, SDL_TRUE, {304, 352}, 0};

	level_04.waves[1] = (t_wave_m){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 12, SDL_FALSE, NULL};
	level_04.waves[1].wave_array = SDL_malloc(sizeof(*(level_04.waves[1].wave_array)) * level_04.waves[1].size);

	level_04.waves[1].wave_array[0] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_04.waves[1].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 0}, 0};
	level_04.waves[1].wave_array[2] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 352}, 0};
	level_04.waves[1].wave_array[3] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 352}, 0};

	level_04.waves[1].wave_array[4] = (t_wave_elem){E_SLIME_YELLOW, 0, 80, SDL_TRUE, {0, 0}, 0};
	level_04.waves[1].wave_array[5] = (t_wave_elem){E_SLIME_BLUE, 0, 80, SDL_TRUE, {304, 0}, 0};
	level_04.waves[1].wave_array[6] = (t_wave_elem){E_SLIME_BLUE, 0, 80, SDL_TRUE, {0, 352}, 0};
	level_04.waves[1].wave_array[7] = (t_wave_elem){E_SLIME_YELLOW, 0, 80, SDL_TRUE, {304, 352}, 0};

	level_04.waves[1].wave_array[8] = (t_wave_elem){E_SLIME_BLUE, 0, 140, SDL_TRUE, {0, 0}, 0};
	level_04.waves[1].wave_array[9] = (t_wave_elem){E_SLIME_BLUE, 0, 140, SDL_TRUE, {304, 0}, 0};
	level_04.waves[1].wave_array[10] = (t_wave_elem){E_SLIME_BLUE, 0, 140, SDL_TRUE, {0, 352}, 0};
	level_04.waves[1].wave_array[11] = (t_wave_elem){E_SLIME_BLUE, 0, 140, SDL_TRUE, {304, 352}, 0};


	level_04.waves[2] = (t_wave_m){0, WAVE_PREV_DEFEAT, 0, SDL_FALSE, SDL_FALSE, 9, SDL_FALSE, NULL};
	level_04.waves[2].wave_array = SDL_malloc(sizeof(*(level_04.waves[2].wave_array)) * level_04.waves[2].size);

	level_04.waves[2].wave_array[0] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {0, 0}, 0};
	level_04.waves[2].wave_array[1] = (t_wave_elem){E_SLIME_BLUE, 0, 0, SDL_TRUE, {304, 0}, 0};
	level_04.waves[2].wave_array[2] = (t_wave_elem){E_SLIME_YELLOW, 0, 0, SDL_TRUE, {152, 352}, 0};

	level_04.waves[2].wave_array[3] = (t_wave_elem){E_SLIME_BLUE, 0, 70, SDL_TRUE, {152, 0}, 0};
	level_04.waves[2].wave_array[4] = (t_wave_elem){E_SLIME_YELLOW, 0, 70, SDL_TRUE, {0, 352}, 0};
	level_04.waves[2].wave_array[5] = (t_wave_elem){E_SLIME_YELLOW, 0, 70, SDL_TRUE, {304, 352}, 0};

	level_04.waves[2].wave_array[6] = (t_wave_elem){E_SLIME_YELLOW, 0, 150, SDL_TRUE, {0, 0}, 0};
	level_04.waves[2].wave_array[7] = (t_wave_elem){E_SLIME_YELLOW, 0, 150, SDL_TRUE, {304, 0}, 0};
	level_04.waves[2].wave_array[8] = (t_wave_elem){E_SLIME_YELLOW, 0, 150, SDL_TRUE, {152, 352}, 0};

	return level_04;
}