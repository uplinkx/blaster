/***************************************************************************
 * FILENAME:    lunge.c
 * DESCRIPTION: lunge attack
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 08Jul2021
***************************************************************************/

#include "main.h"

SDL_bool	lunge_fire(SDL_UNUSED t_weapon *weapon)
{
	SDL_bool	result;

	result = SDL_FALSE;
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft) && weapon->curr >= weapon->cooldown)
	{
		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft);
		result = SDL_TRUE;
	}

	if (g_GameInput.GameInput.button_primleft != 0)
		weapon->meta_int++;

	return (result);
}

void	lunge_update(void *self, SDL_UNUSED void *meta)
{
	t_bullet	*bullet;

	bullet = self;

	if (bullet->active == SDL_FALSE)
		return ;


	if (bullet->sprite.current >= (size_t)bullet->vel.x)
	{
		bullet->active = SDL_FALSE;
		return ;
	}

	bullet->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(bullet->sprite));
	SDLX_CollisionBucket_add(NULL, &(bullet->hitbox));
}

void	lunge_factory(t_bullet *dst, SDL_UNUSED SDL_Point spawn_point, SDL_UNUSED double angle, void *meta)
{
	t_player	*player;
	int			*charge;

	player = meta;

	charge = &(player->weapon_equip->meta_int);

	SDLX_new_Sprite(&(dst->sprite));
	fetch_lunge_sprite(&(dst->sprite.sprite_data), 1);
	dst->sprite.dst = SDLX_NULL_SELF;
	dst->sprite._dst = (SDL_Rect){(PLAY_WIDTH - (26 * 3)) / 2, (PLAY_HEIGHT) / 2 - 36 * 3, (26 * 3), (36 * 3)};

	dst->sprite.center = SDLX_NULL_SELF;
	dst->sprite._center = (SDL_Point){26 * 3, 36 * 3 * 2};
	angle = ptoa(g_GameInput.GameInput.primary.x, g_GameInput.GameInput.primary.y);
	dst->sprite.angle = (angle * 180 / M_PI);

	dst->active = SDL_TRUE;

	dst->update = lunge_update;

	dst->hitbox.type = LUNGE;
	dst->hitbox.originator = dst;
	SDL_Log("Start %lf", dst->sprite.angle);
	dst->hitbox.angle = angle - M_PI_2;

	dst->hitbox.detect = NULL;
	dst->vel.x = 50;
	*charge = 0;
}

#define LUNGE_COOLDOWN (15)

t_weapon	lunge_cannon(void)
{
	t_weapon	lunge_cannon;

	lunge_cannon.start = 0;
	lunge_cannon.cooldown = LUNGE_COOLDOWN;

	lunge_cannon.curr = LUNGE_COOLDOWN;

	lunge_cannon.enabled = SDL_TRUE;

	lunge_cannon.factory = lunge_factory;
	lunge_cannon.trigger = lunge_fire;

	return (lunge_cannon);
}