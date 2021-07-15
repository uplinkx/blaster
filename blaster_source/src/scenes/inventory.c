/***************************************************************************
 * FILENAME:    inventory.c
 * DESCRIPTION: Scene for equiping things
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

typedef struct	s_inv_scene
{
	SDLX_Sprite background;

	SDLX_button	level_select;

	SDLX_button	next_weapon;

	SDLX_button	equip_weapon;
	SDLX_button	weapon_info;

	SDLX_button	prev_weapon;

	// SDL_Texture	*level_capture;
}				t_inv_scene;

void	*inventory_init(t_context *context, SDL_UNUSED void *vp_scene)
{
	t_inv_scene *scene;

	scene = new_scene(sizeof(*scene), context, ASSETS"inventory.png", inventory_close, inventory_update);

	SDLX_Button_Init(&(scene->level_select), fetch_inventory_sprite, IBACK_NORM, (SDL_Rect){PLAY_WIDTH - 48 - 8, 8, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->level_select), IBACK_NORM, IBACK_HOVER);
	scene->level_select.trigger_fn = button_trigger_scene_switch;
	scene->level_select.meta = context;
	scene->level_select.meta1 = level_select_init;

	SDLX_Button_Init(&(scene->prev_weapon), fetch_inventory_sprite, IPREV_NORM, (SDL_Rect){0, 380, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->prev_weapon), IPREV_NORM, IPREV_HOVER);

	SDLX_Button_Init(&(scene->next_weapon), fetch_inventory_sprite, INEXT_NORM, (SDL_Rect){PLAY_WIDTH - 48, 380, 48, 48}, NULL);
	SDLX_Style_Button(&(scene->next_weapon), INEXT_NORM, INEXT_HOVER);

	return (NULL);
}

void	*inventory_close(SDL_UNUSED t_context *context, SDL_UNUSED void *vp_scene)
{
	t_inv_scene	*scene;

	scene = vp_scene;
	SDLX_RenderQueue_Flush(NULL, NULL, SDL_FALSE);
	SDL_free(context->background.sprite_data);
	SDL_free(scene);

	return (NULL);
}

void	*inventory_update(SDL_UNUSED t_context *context, void *vp_scene)
{
	t_inv_scene	*scene;

	scene = vp_scene;

	SDLX_Button_Update(&(scene->level_select));
	SDLX_Button_Update(&(scene->prev_weapon));
	SDLX_Button_Update(&(scene->next_weapon));

	return (NULL);
}