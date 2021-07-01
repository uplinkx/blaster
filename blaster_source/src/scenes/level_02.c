/***************************************************************************
 * FILENAME:    second_level.c
 * DESCRIPTION: The second level.
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

typedef struct	s_second_level
{
	SDLX_Sprite			bottom_ui;

	SDLX_button			pause;
	SDL_bool			paused;

	t_pmenu				pause_menu;

	SDLX_Sprite			crosshair;

	t_player			player;

	SDLX_button			mainhand;
	SDLX_button			shield;
	SDLX_button			heal;
	SDLX_button			special;

	t_enemy				slime;
	t_enemy				slime2;
	t_enemy				slime3;
	int					score;

	SDL_Texture			*pbackground;
}				t_second_level;

void	*level_02_init(t_context *context, SDL_UNUSED void *vp_scene)
{
	t_second_level	*scene;

	scene = new_scene(sizeof(*scene), context, ASSETS"level_one.png", level_02_close, level_02_update);

	scene->pbackground = NULL;
	scene->score = 0;

	scene->bottom_ui = SDLX_Sprite_Static(ASSETS"bottom_ui.png");
	scene->bottom_ui.dst = SDLX_NULL_SELF;
	scene->bottom_ui._dst = (SDL_Rect){0, PLAY_HEIGHT, PLAY_WIDTH, 16 * 5};

	SDLX_Button_Init(&(scene->pause), fetch_ui_sprite, PAUSE_NORM, (SDL_Rect){256 - 24, 8, 16, 16}, NULL);
	scene->pause.trigger_fn = button_pause;
	scene->pause.meta = &(scene->paused);

	pause_menu_init(&(scene->pause_menu), &(scene->paused), &(scene->pbackground), context, context->init_fn);

	player_init(&(scene->player));
	scene->player.weapon_equip = &(context->mainhand);

	// context->heal.enabled = SDL_TRUE;
	// context->shield.enabled = SDL_TRUE;
	// context->special.enabled = SDL_TRUE;
	load_weapons(context, &(scene->player.weapon_equip), &(scene->mainhand), &(scene->shield), &(scene->heal), &(scene->special));

	crosshair_init(&(scene->crosshair));

	slime_init(&(scene->slime));
	scene->slime.enemy_hurtbox.engage_meta2 = &(scene->score);
	slime_init(&(scene->slime2));
	scene->slime2.enemy_hurtbox.engage_meta2 = &(scene->score);
	slime_init(&(scene->slime3));
	scene->slime3.enemy_hurtbox.engage_meta2 = &(scene->score);

	scene->paused = SDL_FALSE;
	return (NULL);
}

void	*level_02_close(t_context *context, void *vp_scene)
{
	t_second_level	*scene;

	scene = vp_scene;

	context->redo_init_fn = context->init_fn;
	if (scene->pbackground != NULL)
		SDL_DestroyTexture(scene->pbackground);

	if (scene->player.hp <= 0)
		context->init_fn = death_level_init;

	if (scene->score >= 21)
	{
		context->init_fn = loot_level_init;

		context->levels[0][2].unlocked = SDL_TRUE;
		context->heal = heal_cannon();
	}

	SDLX_RenderQueue_Flush(NULL, SDLX_GetDisplay()->renderer, SDL_FALSE);
	SDL_free(context->background.sprite_data);
	SDL_free(scene->bottom_ui.sprite_data);
	SDL_free(scene);

	(void)context;
	return (NULL);
}

void	*level_02_update(t_context *context, void *vp_scene)
{
	size_t	i;
	t_second_level	*scene;

	scene = vp_scene;

	if (scene->paused == SDL_FALSE)
	{
		SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 255, 0, 0, 255);
		SDL_Rect	playarea = {16, 220 * DISPLAY_SCALE, lerp32(scene->player.hp / 100.0, 0, 480), 10};

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

		slime_update(&(scene->slime));
		slime_update(&(scene->slime2));
		slime_update(&(scene->slime3));


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

	if (scene->paused == SDL_TRUE && scene->pbackground == NULL)
	{
		scene->pause.sprite_fn(&(scene->pause.sprite.sprite_data), EMPTY_UI);
		scene->pbackground = SDLX_CaptureScreen(NULL, 0, SDL_TRUE);
		scene->pause.sprite_fn(&(scene->pause.sprite.sprite_data), PAUSE_NORM);
	}

	if (scene->player.hp <= 0) { context->capture_texture = SDLX_CaptureScreen(NULL, 0, SDL_TRUE); context->scene = SDL_FALSE; }
	if (scene->score == 21) { context->capture_texture = SDLX_CaptureScreen(NULL, 0, SDL_TRUE); context->scene = SDL_FALSE; }

	return (NULL);
}