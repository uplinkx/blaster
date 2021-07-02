/***************************************************************************
 * FILENAME:    crosshair.c
 * DESCRIPTION: Crosshair Functions
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 30Jun2021
***************************************************************************/

#include "main.h"

void	crosshair_init(SDLX_Sprite *crosshair)
{
	*crosshair = SDLX_Sprite_Static(ASSETS"crosshair.png");

	crosshair->dst = &(crosshair->_dst);
	crosshair->_dst = (SDL_Rect){(PLAY_WIDTH) / 2 - 40, (PLAY_HEIGHT) / 2 - 40, 80, 80};
	crosshair->angle = 0;
}

void	update_crosshair(SDLX_Sprite *crosshair)
{
	crosshair->angle = SDLX_Radian_to_Degree(ptoa(g_GameInput.GameInput.primary.x, g_GameInput.GameInput.primary.y)) - 45;
	SDLX_RenderQueue_Add(NULL, crosshair);
}