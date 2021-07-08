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

SDLX_iMap	*blaster_key_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_primleft),	1, SDL_SCANCODE_SPACE},

		(SDLX_iMap){&BMAP(button_num1),	1, SDL_SCANCODE_1},
		(SDLX_iMap){&BMAP(button_num2),	1, SDL_SCANCODE_2},
		(SDLX_iMap){&BMAP(button_num3),	1, SDL_SCANCODE_3},
		(SDLX_iMap){&BMAP(button_num4),	1, SDL_SCANCODE_4},

		(SDLX_iMap){&BMAP(button_num1),	1, SDL_SCANCODE_A},
		(SDLX_iMap){&BMAP(button_num2),	1, SDL_SCANCODE_S},
		(SDLX_iMap){&BMAP(button_num3),	1, SDL_SCANCODE_D},
		(SDLX_iMap){&BMAP(button_num4),	1, SDL_SCANCODE_F},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}