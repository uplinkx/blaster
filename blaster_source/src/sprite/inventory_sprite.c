/***************************************************************************
 * FILENAME:    inventory_sprite.c
 * DESCRIPTION: Return the buttons used in the inventory scene.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 15Jul2021
***************************************************************************/

#include "main.h"

SDLX_Sprite_Data *carve_inventory_sprite(void)
{
	size_t				i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(10, sizeof(*result));
	texture = SDLX_LoadTexture(ASSETS"inventory_ui.png");

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

	/* The Prev Weapon Button */
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

	/* The Next Weapon Button */
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){32, 16, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){48, 16, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;
	i++;

	/* The Info Button */
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

	/* The Back Button */
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

	return (result);
}

int		fetch_inventory_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_inventory_sprite();

	if		(no == IMENU_NORM)	{ (*dst) = &(sprite_arr[0]); return (EXIT_SUCCESS); }
	else if (no == IMENU_HOVER)	{ (*dst) = &(sprite_arr[1]); return (EXIT_SUCCESS); }
	else if (no == IPREV_NORM)	{ (*dst) = &(sprite_arr[2]); return (EXIT_SUCCESS); }
	else if (no == IPREV_HOVER)	{ (*dst) = &(sprite_arr[3]); return (EXIT_SUCCESS); }
	else if (no == INEXT_NORM)	{ (*dst) = &(sprite_arr[4]); return (EXIT_SUCCESS); }
	else if (no == INEXT_HOVER)	{ (*dst) = &(sprite_arr[5]); return (EXIT_SUCCESS); }
	else if (no == IINFO_NORM)	{ (*dst) = &(sprite_arr[6]); return (EXIT_SUCCESS); }
	else if (no == IINFO_HOVER)	{ (*dst) = &(sprite_arr[7]); return (EXIT_SUCCESS); }
	else if (no == IBACK_NORM)	{ (*dst) = &(sprite_arr[8]); return (EXIT_SUCCESS); }
	else if (no == IBACK_HOVER)	{ (*dst) = &(sprite_arr[9]); return (EXIT_SUCCESS); }
	else { return (EXIT_FAILURE); }
}