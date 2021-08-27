/***************************************************************************
 * FILENAME:    loot_scene.c
 * DESCRIPTION: Scene that displays upon winning a level.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 26Jun2021
***************************************************************************/

#include "main.h"

typedef struct	s_loot_scene
{
	SDLX_button	restart;
	SDLX_button	level_select;
	SDLX_button	next;
	SDLX_button	inventory;

	SDLX_button	chest;

	SDLX_Sprite background;
	SDL_Texture	*level_capture;

	t_level_progress	*won;
}				t_loot_scene;

void	*loot_level_init(t_context *context, SDL_UNUSED void *vp_scene)
{
	t_loot_scene	*scene;
	size_t			y_offset;

	y_offset = 25;
	scene = new_scene(sizeof(*scene), context, NULL, loot_level_close, loot_level_update);

	SDLX_Button_Init(&(scene->level_select), fetch_loot_sprite, LMENU_NORM, (SDL_Rect){(PLAY_WIDTH - 48) / 2 - 60, 232 + y_offset, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->level_select), LMENU_NORM, LMENU_HOVER);
	scene->level_select.trigger_fn = button_trigger_scene_switch;
	scene->level_select.meta = context;
	scene->level_select.meta1 = level_select_init;

	SDLX_Button_Init(&(scene->restart), fetch_loot_sprite, LREDO_NORM, (SDL_Rect){(PLAY_WIDTH - 48) / 2 - 20, 232 + y_offset, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->restart), LREDO_NORM, LREDO_HOVER);
	scene->restart.trigger_fn = button_trigger_scene_switch;
	scene->restart.meta = context;
	scene->restart.meta1 = context->redo_init_fn;

	SDLX_Button_Init(&(scene->next), fetch_loot_sprite, LNEXT_NORM, (SDL_Rect){(PLAY_WIDTH - 48) / 2 + 60, 232 + y_offset, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->next), LNEXT_NORM, LNEXT_HOVER);
	scene->next.trigger_fn = button_trigger_scene_switch;
	scene->next.meta = context;
	scene->next.meta1 = context->next_init_fn;

	SDLX_Button_Init(&(scene->inventory), fetch_loot_sprite, LINVT_NORM, (SDL_Rect){(PLAY_WIDTH - 48) / 2 + 20, 232 + y_offset, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->inventory), LINVT_NORM, LINVT_HOVER);
	scene->inventory.trigger_fn = button_trigger_scene_switch;
	scene->inventory.meta = context;
	scene->inventory.meta1 = inventory_init;

	SDLX_new_Sprite(&(scene->background));
	fetch_loot_sprite(&(scene->background.sprite_data), LBACK);
	scene->background._dst = (SDL_Rect){(PLAY_WIDTH - 64 * 3) / 2, 80 + y_offset, 64 * 3, 64 * 3};
	scene->background.dst = SDLX_NULL_SELF;

	SDLX_Button_Init(&(scene->chest), fetch_chest_sprite, 0, (SDL_Rect){(PLAY_WIDTH - 124) / 2, 80 + y_offset, 124, 124}, NULL);
	SDLX_Style_Button(&(scene->chest), 0, 1);
	scene->chest.trigger_fn = button_chest;
	scene->chest.update_fn = button_chest_update;
	scene->chest.trigger_box = scene->background._dst;

	SDLX_Sprite		*treasure;
	size_t	wave_id;

	wave_id = context->wave_id;

	treasure = &(context->levels[wave_id / 5][wave_id % 5].treasure_w.treasure_sprite);
	treasure->dst = SDLX_NULL_SELF;
	treasure->_dst = (SDL_Rect){(PLAY_WIDTH - 80) / 2, 80, 32, 32};
	scene->chest.meta = treasure;

	if (context->next_init_fn == NULL)
	{
		scene->next.isDisabled = SDL_TRUE;
		fetch_ui_sprite(&(scene->next.sprite.sprite_data), EMPTY_UI);
		scene->level_select.sprite._dst.x =	(PLAY_WIDTH - 48) / 2 - 50;
		scene->restart.sprite._dst.x =		(PLAY_WIDTH - 48) / 2;
		scene->inventory.sprite._dst.x =	(PLAY_WIDTH - 48) / 2 + 50;
	}

	if (context->levels[wave_id / 5][wave_id % 5].wasReceived == SDL_TRUE)
		scene->chest.meta = NULL;
	else
		context->levels[wave_id / 5][wave_id % 5].wasReceived = SDL_TRUE;

	context->wave_id = 0;



		 if (context->mainhand.factory == NULL && context->levels[wave_id / 5][wave_id % 5].treasure_w.type & B_MAINHAND) { context->mainhand = context->levels[wave_id / 5][wave_id % 5].treasure_w; }
	else if (context->defense.factory == NULL && context->levels[wave_id / 5][wave_id % 5].treasure_w.type & B_DEFENSE) { context->defense = context->levels[wave_id / 5][wave_id % 5].treasure_w; }
	else if (context->offhand.factory == NULL && context->levels[wave_id / 5][wave_id % 5].treasure_w.type & B_OFFHAND) { context->offhand = context->levels[wave_id / 5][wave_id % 5].treasure_w; }
	else if (context->special.factory == NULL && context->levels[wave_id / 5][wave_id % 5].treasure_w.type & B_SPECIAL) { context->special = context->levels[wave_id / 5][wave_id % 5].treasure_w; }



	return (NULL);
}

void	*loot_level_close(SDL_UNUSED t_context *context, SDL_UNUSED void *vp_scene)
{
	t_loot_scene	*scene;

	scene = vp_scene;
	SDLX_RenderQueue_Flush(NULL, NULL, SDL_FALSE);

	SDL_RenderCopy(SDLX_GetDisplay()->renderer, context->capture_texture, NULL, NULL);
	SDL_DestroyTexture(context->capture_texture);
	context->capture_texture = NULL;
	context->redo_init_fn = NULL;

	return (NULL);
}

void	*loot_level_update(SDL_UNUSED t_context *context, SDL_UNUSED void *vp_scene)
{
	t_loot_scene	*scene;

	scene = vp_scene;

	SDL_RenderCopy(SDLX_GetDisplay()->renderer, context->capture_texture, NULL, NULL);
	SDLX_Button_Update(&(scene->chest));

	if (scene->chest.sprite.dst->y <= 50 + 25)
	{
		SDLX_Button_Update(&(scene->restart));
		SDLX_Button_Update(&(scene->level_select));
		SDLX_Button_Update(&(scene->next));
		SDLX_Button_Update(&(scene->inventory));
	}
	else
	{
		SDLX_RenderQueue_Add(NULL, &(scene->restart.sprite));
		SDLX_RenderQueue_Add(NULL, &(scene->level_select.sprite));
		SDLX_RenderQueue_Add(NULL, &(scene->next.sprite));
		SDLX_RenderQueue_Add(NULL, &(scene->inventory.sprite));
	}

	SDLX_RenderQueue_Add(NULL, &(scene->background));

	return (NULL);
}
