/***************************************************************************
 * FILENAME:    ui.c
 * DESCRIPTION: Handles the level to level ui
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 02Jul2021
***************************************************************************/

#include "main.h"

void	level_ui_init(SDLX_button *pause, SDLX_Sprite *bottom)
{
	*bottom = SDLX_Sprite_Static(ASSETS"bottom_ui.png");
	bottom->dst = SDLX_NULL_SELF;
	bottom->_dst = (SDL_Rect){0, PLAY_HEIGHT, PLAY_WIDTH, BOTTOM_UI};

	SDLX_Button_Init(pause, fetch_ui_sprite, PAUSE_NORM, (SDL_Rect){PLAY_WIDTH - 35, 6, 32, 32}, NULL);
	pause->trigger_fn = button_pause;
}