/***************************************************************************
 * FILENAME:    level_sprite.c
 * DESCRIPTION: Handles the Sprites for level buttons
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

SDLX_Sprite_Data *carve_heal_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(8, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"heal.png");

	i = 0;
	while (i < 8)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){i * 48, 0, 48, 48};
		result[i].src = &(result[i]._src);
		result[i].cycle = 8;
		i++;
	}

	return (result);
}

int		fetch_heal_sprite(SDLX_Sprite_Data **dst, SDL_UNUSED int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_heal_sprite();

	// if (no == 1)		{ (*dst) = &(sprite_arr[0]); return (EXIT_SUCCESS); }
	// else { return (EXIT_FAILURE); }

	(*dst) = &(sprite_arr[0]);

	return (EXIT_SUCCESS);
}