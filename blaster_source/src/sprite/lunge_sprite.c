/***************************************************************************
 * FILENAME:    level_sprite.c
 * DESCRIPTION: Handles the Sprites for Coins
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 22Jun2021
***************************************************************************/

#include "main.h"

SDLX_Sprite_Data *carve_lunge_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(14, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"weapons/lunge.png");

	i = 0;
	/* The Cooldown Icon */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 0, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	/* The Treasure Icon */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){32, 0, 32, 32};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	while (i < 14)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){26 * i, 32, 26, 36};
		result[i].src = &(result[i]._src);
		result[i].cycle = 11;
		// result[i].skip = 1;
		i++;
	}

	return (result);
}

int		fetch_lunge_sprite(SDLX_Sprite_Data **dst, SDL_UNUSED int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_lunge_sprite();

	if (no == 0) { *dst = &(sprite_arr[0]); }
	else if (no == 1) { *dst = &(sprite_arr[1]); }
	else { *dst = &(sprite_arr[2]); }

	return (EXIT_SUCCESS);
}