/***************************************************************************
 * FILENAME:    first_level.c
 * DESCRIPTION: The first level.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.54.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 11Jun2021
***************************************************************************/

#include "main.h"

typedef struct	s_first_level
{
	SDLX_button			pause;
	t_pmenu				pause_menu;

	t_player			player;
	SDLX_Sprite			crosshair;

	SDLX_Sprite			bottom_ui;
	SDLX_button			mainhand, shield, heal, special;

	t_enemy				slime, slime2;
	int					score;

	SDL_Texture			*pbackground;
}				t_first_level;

void	*level_01_init(t_context *context, SDL_UNUSED void *vp_scene)
{
	t_first_level	*scene;

	scene = new_scene(sizeof(*scene), context, ASSETS"level_one.png", level_01_close, level_01_update);

	scene->score = 0;
	scene->pbackground = NULL;

	level_ui_init(&(scene->pause), &(scene->bottom_ui));
	pause_menu_init(&(scene->pause_menu), &(scene->pause.triggered), &(scene->pbackground), context, context->init_fn);

	player_init(&(scene->player));
	crosshair_init(&(scene->crosshair));
	scene->player.weapon_equip = &(context->mainhand);
	load_weapons(context, &(scene->player.weapon_equip), &(scene->mainhand), &(scene->shield), &(scene->heal), &(scene->special));

	slime_init(&(scene->slime)); scene->slime.enemy_hurtbox.engage_meta2 = &(scene->score);
	slime_init(&(scene->slime2)); scene->slime2.enemy_hurtbox.engage_meta2 = &(scene->score);

	return (NULL);
}

void	*level_01_close(t_context *context, void *vp_scene)
{
	t_first_level	*scene;

	scene = vp_scene;
	context->redo_init_fn = context->init_fn;

	if (scene->score >= 12)
	{
		context->init_fn = loot_level_init;

		context->levels[0][1].unlocked = SDL_TRUE;
		context->shield = whirl_cannon();
		context->next_init_fn = context->levels[0][1].init_fn;
	}

	if (scene->player.hp <= 0) { context->init_fn = death_level_init; }

	if (scene->pbackground != NULL) { SDL_DestroyTexture(scene->pbackground); }

	SDL_free(context->background.sprite_data);
	SDL_free(scene->bottom_ui.sprite_data);
	SDL_free(scene);

	return (NULL);
}

void	*level_01_update(t_context *context, void *vp_scene)
{
	t_first_level	*scene;

	scene = vp_scene;

	if (scene->pause.triggered == SDL_FALSE)
	{
		update_cooldowns(&(context->mainhand), &(context->shield), &(context->heal), &(context->special));

		SDLX_Button_Update(&(scene->pause));

		SDLX_Button_Update(&(scene->mainhand));
		SDLX_Button_Update(&(scene->special));
		SDLX_Button_Update(&(scene->shield));
		SDLX_Button_Update(&(scene->heal));

		SDLX_CollisionBucket_Flush(NULL);

		update_crosshair(&(scene->crosshair));
		player_update(&(scene->player));

		SDLX_RenderQueue_Add(NULL, &(scene->bottom_ui));
		projectile_update(&(scene->player.attacks));

		slime_update(&(scene->slime), NULL);
		slime_update(&(scene->slime2), NULL);
	}
	else
		update_pause_menu(&(scene->pause_menu), scene->pbackground);

	if (scene->pause.triggered == SDL_TRUE && scene->pbackground == NULL)
	{
		scene->pause.sprite_fn(&(scene->pause.sprite.sprite_data), EMPTY_UI);
		scene->pbackground = SDLX_CaptureScreen(NULL, 0, SDL_TRUE);
		scene->pause.sprite_fn(&(scene->pause.sprite.sprite_data), PAUSE_NORM);
	}

	if (scene->player.hp <= 0) { end_scene(context, &(scene->pause)); }
	if (scene->score == 12) { end_scene(context, &(scene->pause)); }

	return (NULL);
}
