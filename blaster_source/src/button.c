/***************************************************************************
 * FILENAME:    button.c
 * DESCRIPTION: Buttons for blaster.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 21Jun2021
***************************************************************************/

#include "main.h"

void	*button_chest_update(SDLX_button *self, SDL_UNUSED void *vp_context, SDL_UNUSED size_t length)
{
	if (self->focus_no == -1 && self->norm_no == -1)
	{
		if (self->sprite.dst->y >= 40)
		{
			self->sprite.dst->y -= 2;
			self->sprite.dst->w -= 1;
			self->sprite.dst->h -= 1;

			self->sprite.dst->x = (PLAY_WIDTH - self->sprite.dst->w) / 2;
		}
	}
	return (NULL);
}

void	*button_chest(SDLX_button *self, SDL_UNUSED void *vp_context, SDL_UNUSED size_t length)
{
	if (SDL_PointInRect(&(g_GameInput.GameInput.primary), &(self->sprite._dst)) == SDL_FALSE && self->focus_no != -1)
		self->sprite_fn(&(self->sprite.sprite_data), self->norm_no);
	else if (SDL_PointInRect(&(g_GameInput.GameInput.primary), &(self->sprite._dst)))
		self->sprite_fn(&(self->sprite.sprite_data), self->focus_no);


	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
	{
		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft)

		self->norm_no = -1;
		self->focus_no = -1;

		self->sprite_fn(&(self->sprite.sprite_data), 2);
		self->sprite.current = 0;
		self->trigger_fn = SDLX_Button_NULL_fn;
	}

	return (NULL);
}

void	*button_trigger_scene_switch(SDLX_button *self, void *vp_context, SDL_UNUSED size_t length)
{
	t_context *context;

	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primleft))
	{
		context = vp_context;
		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft)

		context->init_fn = self->meta1;
		context->scene = SDL_FALSE;
	}

	return (NULL);
}

void	*button_pause(SDLX_button *self, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
	{
		self->triggered = SDL_TRUE;

		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft)
		self->focused = SDL_FALSE;
		self->sprite_fn(&(self->sprite.sprite_data), self->norm_no);
	}

	return (NULL);
}

void	*button_resume(SDLX_button *self, void *pause_addr, SDL_UNUSED size_t length)
{
	SDL_bool	*pause;
	SDLX_button	*button;
	SDL_Texture	**pbackground;

	button = self;
	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primleft))
	{
		pause = pause_addr;
		*pause = SDL_FALSE;

		self->focused = SDL_FALSE;
		self->sprite_fn(&(self->sprite.sprite_data), self->norm_no);

		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft)

		pbackground = self->meta1;
		SDL_DestroyTexture(*pbackground);
		*pbackground = NULL;
	}

	return (NULL);
}

void	*change_ability(SDLX_button *self, void *weapon_addr, SDL_UNUSED size_t length)
{
	t_weapon	**player_spot;
	t_weapon	*from_weapon;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
	{
		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft)
		from_weapon = self->meta1;
		player_spot = weapon_addr;

		(*player_spot)->meta_int = 0;
		*player_spot = from_weapon;
	}

	return (NULL);
}

void	*ability_button_update(SDLX_button *self, void *weapon_addr, SDL_UNUSED size_t length)
{
	t_weapon	**player_spot;
	t_weapon	*from_weapon;
	int			*keymap;

	from_weapon = self->meta1;
	player_spot = weapon_addr;

	keymap = self->down;
	if (*keymap == 1 && *player_spot != self->meta1)
	{
		g_GameInput_prev.GameInput.button_primleft = 0;
		g_GameInput.GameInput.button_primleft = 1;

		self->trigger_fn(self, self->meta, 0);
	}

	if (*player_spot == self->meta1)
		self->sprite_fn(&(self->sprite.sprite_data), ABILITY_SEL);
	else
		self->sprite_fn(&(self->sprite.sprite_data), ABILITY);


	return (NULL);
}


void	ability_button_init(SDLX_button *dst, t_weapon **player_equip_addr, t_weapon *to)
{
	SDLX_Button_Init(dst, fetch_ui_sprite, ABILITY, (SDL_Rect){0, 400, 48, 48}, NULL);
	// SDLX_Style_Button(dst, ABILITY, ABILITY_SEL);

	dst->disabled = SDL_TRUE;
	if (to->enabled == SDL_TRUE) {dst->disabled = SDL_FALSE; dst->trigger_fn = change_ability; dst->update_fn = ability_button_update;}

	dst->meta = player_equip_addr;
	dst->meta1 = to;
}

