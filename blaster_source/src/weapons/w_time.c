/***************************************************************************
 * FILENAME:    time.c
 * DESCRIPTION: Handles the time weapon
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.54.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 12Jun2021
***************************************************************************/

#include "main.h"

SDL_bool	time_fire(SDL_UNUSED t_weapon *weapon)
{
	SDL_bool	result;

	result = SDL_FALSE;
	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primleft) && weapon->curr >= weapon->cooldown)
	{
		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft);
		result = SDL_TRUE;
	}

	if (weapon->curr >= weapon->cooldown && weapon->meta_int == 0)
	{
		result = SDL_TRUE;
		weapon->meta_int++;
	}
	return (result);
}

void	time_update(void *self, SDL_UNUSED void *meta)
{
	t_bullet	*bullet;

	bullet = self;

	bullet->isActive = SDL_FALSE;
	return ;
}

void	time_factory(t_bullet *dst, SDL_UNUSED SDL_Point spawn_point, SDL_UNUSED double angle, SDL_UNUSED void *meta)
{
	dst->sprite = SDLX_Sprite_Static(ASSETS"weapons/heal.png");
	dst->sprite.dst = SDLX_NULL_SELF;
	dst->sprite._dst = (SDL_Rect){16, 16, 0, 0};
	dst->sprite.center = NULL;
	dst->sprite.angle = 0;

	dst->isActive = SDL_FALSE;

	dst->update = time_update;

	dst->hitbox.originator = dst;

	dst->hitbox.detect = NULL;

	t_player	*player;
	SDL_bool	*slow;

	player = meta;
	slow = player->meta;
	*slow = SDL_TRUE;
}

#define time_COOLDOWN (270)

t_weapon	time_cannon(void)
{
	t_weapon	time_cannon;

	time_cannon.start = 0;
	time_cannon.cooldown = time_COOLDOWN;

	time_cannon.curr = time_COOLDOWN;

	time_cannon.isEnabled = SDL_TRUE;

	time_cannon.factory = time_factory;
	time_cannon.trigger = time_fire;

	time_cannon.meta = 0;

	return (time_cannon);
}