/***************************************************************************
 * FILENAME:    third_level.c
 * DESCRIPTION: The third level.
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

typedef struct	s_third_level
{
	SDLX_button			pause;
	t_pmenu				pause_menu;

	t_player			player;
	SDLX_Sprite			crosshair;

	SDLX_Sprite			bottom_ui;
	SDLX_button			mainhand, shield, heal, special;

	t_enemy				slime;
	t_enemy				slime2;
	t_enemy				slime3;
	t_enemy				slime4;
	t_enemy				slime5;
	t_enemy				slime6;
	t_enemy				slime7;
	t_enemy				slime8;

	SDL_bool			slow;
	int					score;

	SDL_Texture			*pbackground;
}				t_third_level;

void	*level_05_init(t_context *context, SDL_UNUSED void *vp_scene)
{
	t_third_level	*scene;

	scene = new_scene(sizeof(*scene), context, ASSETS"level_one.png", level_05_close, level_05_update);

	scene->pbackground = NULL;
	scene->score = 0;

	level_ui_init(&(scene->pause), &(scene->bottom_ui));

	pause_menu_init(&(scene->pause_menu), &(scene->pause.triggered), &(scene->pbackground), context, context->init_fn);

	player_init(&(scene->player));
	scene->player.weapon_equip = &(context->mainhand);

	load_weapons(context, &(scene->player.weapon_equip), &(scene->mainhand), &(scene->shield), &(scene->heal), &(scene->special));

	crosshair_init(&(scene->crosshair));

	slime_green_init(&(scene->slime));
	scene->slime.enemy_hurtbox.engage_meta2 = &(scene->score);
	slime_green_init(&(scene->slime2));
	scene->slime2.enemy_hurtbox.engage_meta2 = &(scene->score);

	slime_init(&(scene->slime3));
	scene->slime3.enemy_hurtbox.engage_meta2 = &(scene->score);
	scene->slime3.meta1 = (void *)1;
	slime_init(&(scene->slime4));
	scene->slime4.enemy_hurtbox.engage_meta2 = &(scene->score);
	scene->slime4.meta1 = (void *)6;

	slime_green_init(&(scene->slime5));
	scene->slime5.enemy_hurtbox.engage_meta2 = &(scene->score);
	scene->slime5.meta1 = (void *)6;
	slime_init(&(scene->slime6));
	scene->slime6.enemy_hurtbox.engage_meta2 = &(scene->score);
	slime_init(&(scene->slime7));
	scene->slime7.meta1 = (void *)1;
	scene->slime7.enemy_hurtbox.engage_meta2 = &(scene->score);

	slime_init(&(scene->slime8));
	scene->slime8.enemy_hurtbox.engage_meta2 = &(scene->score);

	scene->slow = SDL_FALSE;
	scene->player.meta = &(scene->slow);
	return (NULL);
}

void	*level_05_close(t_context *context, void *vp_scene)
{
	t_third_level	*scene;

	scene = vp_scene;

	context->redo_init_fn = context->init_fn;
	if (scene->pbackground != NULL)
		SDL_DestroyTexture(scene->pbackground);

	if (scene->player.hp <= 0)
		context->init_fn = death_level_init;

	if (scene->score >= 124)
	{
		context->init_fn = loot_level_init;
		context->next_init_fn = NULL;
	}

	SDLX_RenderQueue_Flush(NULL, SDLX_GetDisplay()->renderer, SDL_FALSE);
	SDL_free(context->background.sprite_data);
	SDL_free(scene->bottom_ui.sprite_data);
	SDL_free(scene);

	(void)context;
	return (NULL);
}

void	*level_05_update(t_context *context, void *vp_scene)
{
	t_third_level	*scene;
	static int		slow;

	scene = vp_scene;

	if (scene->pause.triggered == SDL_FALSE)
	{
		SDLX_Button_Update(&(scene->pause));

		update_cooldowns(&(context->mainhand), &(context->shield), &(context->heal), &(context->special));
		SDLX_Button_Update(&(scene->mainhand));
		SDLX_Button_Update(&(scene->shield));
		SDLX_Button_Update(&(scene->heal));
		SDLX_Button_Update(&(scene->special));

		update_crosshair(&(scene->crosshair));

		player_update(&(scene->player));

		SDLX_RenderQueue_Add(NULL, &(scene->bottom_ui));
		projectile_update(&(scene->player.attacks));

		if (scene->slow == SDL_FALSE || context->ticks % 3 == 0)
		{
			slime_update(&(scene->slime), NULL);
			slime_update(&(scene->slime2), NULL);
			slime_update(&(scene->slime3), NULL);
			slime_update(&(scene->slime4), NULL);
			slime_update(&(scene->slime5), NULL);
			slime_update(&(scene->slime6), NULL);
			slime_update(&(scene->slime7), NULL);
			slime_update(&(scene->slime8), NULL);
		}
		else
		{
			SDLX_RenderQueue_Add(NULL, &(scene->slime.sprite));
			SDLX_RenderQueue_Add(NULL, &(scene->slime2.sprite));
			SDLX_RenderQueue_Add(NULL, &(scene->slime3.sprite));
			SDLX_RenderQueue_Add(NULL, &(scene->slime4.sprite));
			SDLX_RenderQueue_Add(NULL, &(scene->slime5.sprite));
			SDLX_RenderQueue_Add(NULL, &(scene->slime6.sprite));
			SDLX_RenderQueue_Add(NULL, &(scene->slime7.sprite));
			SDLX_RenderQueue_Add(NULL, &(scene->slime8.sprite));
			if (slow % 100 == 0)
				scene->slow = SDL_FALSE;
			slow++;
		}
		SDLX_CollisionBucket_Flush(NULL);
	}
	else
		update_pause_menu(&(scene->pause_menu), scene->pbackground);

	if (scene->pause.triggered == SDL_TRUE && scene->pbackground == NULL)
	{
		scene->pause.sprite_fn(&(scene->pause.sprite.sprite_data), EMPTY_UI);
		scene->pbackground = SDLX_CaptureScreen(NULL, 0, SDL_TRUE);
		scene->pause.sprite_fn(&(scene->pause.sprite.sprite_data), PAUSE_NORM);
	}

	if (scene->player.hp <= 0) { context->capture_texture = SDLX_CaptureScreen(NULL, 0, SDL_TRUE); context->scene = SDL_FALSE; }
	if (scene->score == 124) { context->capture_texture = SDLX_CaptureScreen(NULL, 0, SDL_TRUE); context->scene = SDL_FALSE; }

	return (NULL);
}