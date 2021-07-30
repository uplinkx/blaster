/***************************************************************************
 * FILENAME:    input.c
 * DESCRIPTION: Keyboard input for game.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 07Jul2021
***************************************************************************/

#include "main.h"

void	set_levels(t_level_progress (*levels)[5])
{
	levels[0][0].isUnlocked = SDL_TRUE;

	levels[0][0].init_fn = level_01_init;
	levels[0][1].init_fn = level_02_init;
	levels[0][2].init_fn = level_03_init;
	levels[0][3].init_fn = level_04_init;
	levels[0][4].init_fn = level_05_init;
	levels[1][0].init_fn = level_06_init;
	levels[1][1].init_fn = level_07_init;
	levels[1][2].init_fn = level_08_init;
	levels[1][3].init_fn = level_09_init;
	levels[1][4].init_fn = level_10_init;
	levels[2][0].init_fn = level_11_init;
	levels[2][1].init_fn = level_12_init;
	levels[2][2].init_fn = level_13_init;
	levels[2][3].init_fn = level_14_init;
	levels[2][4].init_fn = level_15_init;
	levels[3][0].init_fn = level_16_init;
	levels[3][1].init_fn = level_17_init;
	levels[3][2].init_fn = level_18_init;
	levels[3][3].init_fn = level_19_init;
	levels[3][4].init_fn = level_20_init;
	levels[4][0].init_fn = level_21_init;
	levels[4][1].init_fn = level_22_init;
	levels[4][2].init_fn = level_23_init;
	levels[4][3].init_fn = level_24_init;
	levels[4][4].init_fn = level_25_init;

	fetch_lunge_sprite(&(levels[0][0].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[0][1].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[0][2].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[0][3].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[0][4].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[1][0].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[1][1].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[1][2].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[1][3].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[1][4].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[2][0].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[2][1].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[2][2].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[2][3].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[2][4].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[3][0].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[3][1].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[3][2].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[3][3].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[3][4].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[4][0].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[4][1].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[4][2].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[4][3].treasure.sprite_data), 1);
	fetch_yellow_sprite(&(levels[4][4].treasure.sprite_data), 1);

	levels[0][0].treasure_w = heal_cannon();
	levels[0][1].treasure_w = lunge_cannon();
	levels[0][2].treasure_w = whirl_cannon();
	levels[0][3].treasure_w = laser_yellow_cannon();
	levels[0][4].treasure_w = laser_cannon();
	levels[1][0].treasure_w = laser_cannon();
	levels[1][1].treasure_w = laser_cannon();
	levels[1][2].treasure_w = laser_cannon();
	levels[1][3].treasure_w = laser_cannon();
	levels[1][4].treasure_w = laser_cannon();
	levels[2][0].treasure_w = laser_cannon();
	levels[2][1].treasure_w = laser_cannon();
	levels[2][2].treasure_w = laser_cannon();
	levels[2][3].treasure_w = laser_cannon();
	levels[2][4].treasure_w = laser_cannon();
	levels[3][0].treasure_w = laser_cannon();
	levels[3][1].treasure_w = laser_cannon();
	levels[3][2].treasure_w = laser_cannon();
	levels[3][3].treasure_w = laser_cannon();
	levels[3][4].treasure_w = laser_cannon();
	levels[4][0].treasure_w = laser_cannon();
	levels[4][1].treasure_w = laser_cannon();
	levels[4][2].treasure_w = laser_cannon();
	levels[4][3].treasure_w = laser_cannon();
	levels[4][4].treasure_w = laser_cannon();
}

SDLX_iMap	*blaster_key_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_primleft),	1, SDL_SCANCODE_SPACE},
		(SDLX_iMap){&BMAP(button_primleft),	1, SDL_SCANCODE_KP_ENTER},

		(SDLX_iMap){&BMAP(button_num1),	1, SDL_SCANCODE_1},
		(SDLX_iMap){&BMAP(button_num2),	1, SDL_SCANCODE_2},
		(SDLX_iMap){&BMAP(button_num3),	1, SDL_SCANCODE_3},
		(SDLX_iMap){&BMAP(button_num4),	1, SDL_SCANCODE_4},

		(SDLX_iMap){&BMAP(button_num1),	1, SDL_SCANCODE_A},
		(SDLX_iMap){&BMAP(button_num2),	1, SDL_SCANCODE_S},
		(SDLX_iMap){&BMAP(button_num3),	1, SDL_SCANCODE_D},
		(SDLX_iMap){&BMAP(button_num4),	1, SDL_SCANCODE_F},

		(SDLX_iMap){&BMAP(button_primleft),	2, SDL_SCANCODE_1},
		(SDLX_iMap){&BMAP(button_primleft),	2, SDL_SCANCODE_2},
		(SDLX_iMap){&BMAP(button_primleft),	2, SDL_SCANCODE_3},
		(SDLX_iMap){&BMAP(button_primleft),	2, SDL_SCANCODE_4},

		(SDLX_iMap){&BMAP(button_primleft),	2, SDL_SCANCODE_A},
		(SDLX_iMap){&BMAP(button_primleft),	2, SDL_SCANCODE_S},
		(SDLX_iMap){&BMAP(button_primleft),	2, SDL_SCANCODE_D},
		(SDLX_iMap){&BMAP(button_primleft),	2, SDL_SCANCODE_F},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}