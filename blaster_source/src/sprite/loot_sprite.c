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

SDLX_Sprite_Data *carve_loot_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(9, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"loot_scene.png");

	i = 0;
	/* The Menu Button */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 0, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){16, 0, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Back Button */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 16, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){16, 16, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Next Button */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 32, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){16, 32, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Inventory Button */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 48, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){16, 48, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Background */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 64, 64, 64};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	return (result);
}

int		fetch_loot_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_loot_sprite();

	if (no == LMENU_NORM)		{ (*dst) = &(sprite_arr[0]); return (EXIT_SUCCESS); }
	else if (no == LMENU_HOVER)	{ (*dst) = &(sprite_arr[1]); return (EXIT_SUCCESS); }
	else if (no == LREDO_NORM)	{ (*dst) = &(sprite_arr[2]); return (EXIT_SUCCESS); }
	else if (no == LREDO_HOVER)	{ (*dst) = &(sprite_arr[3]); return (EXIT_SUCCESS); }
	else if (no == LNEXT_NORM)	{ (*dst) = &(sprite_arr[4]); return (EXIT_SUCCESS); }
	else if (no == LNEXT_HOVER)	{ (*dst) = &(sprite_arr[5]); return (EXIT_SUCCESS); }
	else if (no == LINVT_NORM)	{ (*dst) = &(sprite_arr[6]); return (EXIT_SUCCESS); }
	else if (no == LINVT_HOVER)	{ (*dst) = &(sprite_arr[7]); return (EXIT_SUCCESS); }
	else if (no == LBACK)		{ (*dst) = &(sprite_arr[8]); return (EXIT_SUCCESS); }
	else { return (EXIT_FAILURE); }
}