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

SDLX_Sprite_Data *carve_chest_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(20, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"chest.png");

	i = 0;
	while (i < 19)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){32 * i, 0, 32, 32};
		result[i].src = &(result[i]._src);
		result[i].cycle = 12;
		// result[i].skip = 1;
		i++;
	}
	result[0].cycle = 6;
	result[7].cycle = 1;

	result[13 + 5].skip = -6;

	return (result);
}

int		fetch_chest_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_chest_sprite();

	if (no == 0)
		*dst = &(sprite_arr[0]);
	else if (no == 1)
		*dst = &(sprite_arr[7]);
	else
		*dst = &(sprite_arr[2 + 6]);

	return (EXIT_SUCCESS);
}