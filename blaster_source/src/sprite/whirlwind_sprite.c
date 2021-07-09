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

SDLX_Sprite_Data *carve_whirl_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(11, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"whirlwind.png");

	i = 0;
	while (i < 11)
	{
		result[i].texture = texture;
		result[i]._src = (SDL_Rect){35 * i, 0, 35, 35};
		result[i].src = &(result[i]._src);
		result[i].cycle = 11;
		// result[i].skip = 1;
		i++;
	}

	return (result);
}

int		fetch_whirl_sprite(SDLX_Sprite_Data **dst, SDL_UNUSED int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_whirl_sprite();

	*dst = &(sprite_arr[0]);

	return (EXIT_SUCCESS);
}