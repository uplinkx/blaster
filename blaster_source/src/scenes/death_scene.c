/***************************************************************************
 * FILENAME:    death_scene.c
 * DESCRIPTION: Scene that displays upon player death.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 24Jun2021
***************************************************************************/

#include "main.h"

typedef struct	s_death_scene
{
	SDLX_button		restart;
	SDLX_button		level_select;
	SDLX_button		inventory;

	SDLX_Sprite		background;

	SDL_Texture		*death_capture;
}				t_death_scene;

void	*death_level_init(t_context *context, SDL_UNUSED void *vp_scene)
{
	t_death_scene	*scene;

	scene = new_scene(sizeof(*scene), context, NULL, death_level_close, death_level_update);

	SDLX_Button_Init(&(scene->level_select), fetch_loot_sprite, LMENU_NORM, (SDL_Rect){(PLAY_WIDTH - 48) / 2 - 50, 232, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->level_select), LMENU_NORM, LMENU_HOVER);
	scene->level_select.trigger_fn = button_trigger_scene_switch;
	scene->level_select.meta = context;
	scene->level_select.meta1 = level_select_init;

	SDLX_Button_Init(&(scene->restart), fetch_loot_sprite, LREDO_NORM, (SDL_Rect){(PLAY_WIDTH - 48) / 2, 232, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->restart), LREDO_NORM, LREDO_HOVER);
	scene->restart.trigger_fn = button_trigger_scene_switch;
	scene->restart.meta = context;
	scene->restart.meta1 = context->redo_init_fn;

	SDLX_Button_Init(&(scene->inventory), fetch_loot_sprite, LINVT_NORM, (SDL_Rect){(PLAY_WIDTH - 48) / 2 + 50, 232, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->inventory), LINVT_NORM, LINVT_HOVER);
	scene->inventory.trigger_fn = button_trigger_scene_switch;
	scene->inventory.meta = context;
	scene->inventory.meta1 = inventory_init;

	SDLX_new_Sprite(&(scene->background));
	fetch_loot_sprite(&(scene->background.sprite_data), DBACK);
	scene->background._dst = (SDL_Rect){(PLAY_WIDTH - 64 * 3) / 2, 80 - (16 * 3), 64 * 3, 80 * 3};
	scene->background.dst = SDLX_NULL_SELF;

	return (NULL);
}

void	*death_level_close(t_context *context, SDL_UNUSED void *vp_scene)
{
	// t_death_scene	*scene;

	// scene = vp_scene;
	SDLX_RenderQueue_Flush(NULL, NULL, SDL_FALSE);

	SDL_RenderCopy(SDLX_GetDisplay()->renderer, context->capture_texture, NULL, NULL);
	SDL_DestroyTexture(context->capture_texture);
	context->capture_texture = NULL;
	context->redo_init_fn = NULL;

	return (NULL);
}

void	*death_level_update(SDL_UNUSED t_context *context, void *vp_scene)
{
	t_death_scene	*scene;

	scene = vp_scene;

	SDL_RenderCopy(SDLX_GetDisplay()->renderer, context->capture_texture, NULL, NULL);

	SDLX_Button_Update(&(scene->restart));
	SDLX_Button_Update(&(scene->level_select));
	SDLX_Button_Update(&(scene->inventory));

	SDLX_RenderQueue_Add(NULL, &(scene->background));

	return (NULL);
}