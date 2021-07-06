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
	SDLX_Sprite			bottom_ui;

	SDLX_button			pause;
	t_pmenu				pause_menu;

	SDLX_Sprite			crosshair;

	t_player			player;

	SDLX_button			mainhand;
	SDLX_button			shield;
	SDLX_button			heal;
	SDLX_button			special;

	t_enemy				slime;
	int					score;

	SDL_Texture			*pbackground;
}				t_first_level;

void	*level_06_init(t_context *context, SDL_UNUSED void *vp_scene)
{
	t_first_level	*scene;

	scene = new_scene(sizeof(*scene), context, ASSETS"level_one.png", level_06_close, level_06_update);

	scene->pbackground = NULL;
	scene->score = 0;

	level_ui_init(&(scene->pause), &(scene->bottom_ui));

	pause_menu_init(&(scene->pause_menu), &(scene->pause.triggered), &(scene->pbackground), context, context->init_fn);

	player_init(&(scene->player));
	scene->player.weapon_equip = &(context->mainhand);

	// context->heal.enabled = SDL_TRUE;
	// context->shield.enabled = SDL_TRUE;
	// context->special.enabled = SDL_TRUE;
	load_weapons(context, &(scene->player.weapon_equip), &(scene->mainhand), &(scene->shield), &(scene->heal), &(scene->special));

	crosshair_init(&(scene->crosshair));

	slime_pink_init(&(scene->slime));
	scene->slime.meta1 = &(scene->player.attacks);
	scene->slime.enemy_hurtbox.engage_meta2 = &(scene->score);


	scene->player.hp = 1000000;

	return (NULL);
}

void	*level_06_close(t_context *context, void *vp_scene)
{
	t_first_level	*scene;

	scene = vp_scene;

	context->redo_init_fn = context->init_fn;
	if (scene->pbackground != NULL)
		SDL_DestroyTexture(scene->pbackground);

	if (scene->player.hp <= 0)
		context->init_fn = death_level_init;

	if (scene->score >= 1000)
	{
		context->init_fn = loot_level_init;

		context->levels[0][1].unlocked = SDL_TRUE;
		context->shield = laser_green_cannon();
	}

	SDLX_RenderQueue_Flush(NULL, SDLX_GetDisplay()->renderer, SDL_FALSE);
	SDL_free(context->background.sprite_data);
	SDL_free(scene->bottom_ui.sprite_data);
	SDL_free(scene);

	(void)context;
	return (NULL);
}

void	*level_06_update(t_context *context, void *vp_scene)
{
	size_t	i;
	t_first_level	*scene;

	scene = vp_scene;

	if (scene->pause.triggered == SDL_FALSE)
	{
		SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 255, 0, 0, 255);
		SDL_Rect	playarea = {32, 340 * DISPLAY_SCALE, lerp32(scene->player.hp / 100.0, 0, 480), 10};

		SDL_RenderFillRect(SDLX_GetDisplay()->renderer, &(playarea));

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

		slime_pink_update(&(scene->slime), NULL);


		i = 0;
		while (i < default_CollisionBucket.index)
		{
			SDLX_attempt_CollisionBucket(default_CollisionBucket.content[i], &(default_CollisionBucket));
			i++;
		}
		default_CollisionBucket.index = 0;
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
	if (scene->score == 1000) { context->capture_texture = SDLX_CaptureScreen(NULL, 0, SDL_TRUE); context->scene = SDL_FALSE; }


	return (NULL);
}
