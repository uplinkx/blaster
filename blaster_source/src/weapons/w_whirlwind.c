/***************************************************************************
 * FILENAME:    whirldwind.c
 * DESCRIPTION: Whirlwind attack
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

SDL_bool	whirl_fire(SDL_UNUSED t_weapon *weapon)
{
	SDL_bool	result;

	result = SDL_FALSE;
	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primleft) && weapon->curr >= weapon->cooldown)
	{
		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft);
		result = SDL_TRUE;
	}

	if (g_GameInput.GameInput.button_primleft != 0 && weapon->curr >= weapon->cooldown)
		weapon->meta_int++;

	return (result);
}

void	whirl_update(void *self, SDL_UNUSED void *meta)
{
	t_bullet	*bullet;

	bullet = self;
	if (bullet->isActive == SDL_FALSE)
		return ;

	if (bullet->sprite.current >= (size_t)bullet->vel.x)
	{
		bullet->isActive = SDL_FALSE;
		return ;
	}

	bullet->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(bullet->sprite));
	SDLX_CollisionBucket_add(NULL, &(bullet->hitbox));
}

void	whirl_factory(t_bullet *dst, SDL_UNUSED SDL_Point spawn_point, SDL_UNUSED double angle, void *meta)
{
	t_player	*player;
	int			*charge;

	player = meta;

	charge = &(player->weapon_equip->meta_int);

	SDLX_new_Sprite(&(dst->sprite));
	fetch_whirl_sprite(&(dst->sprite.sprite_data), 2);
	dst->sprite.dst = SDLX_NULL_SELF;
	dst->sprite._dst = (SDL_Rect){(PLAY_WIDTH - (32 * 3)) / 2, (PLAY_HEIGHT -  (32 * 3)) / 2 + 5, (32 * 3), (32 * 3)};

	dst->isActive = SDL_TRUE;

	dst->update = whirl_update;

	dst->hitbox.type = C_MELEE | C_RECT;
	dst->hitbox.response_amount = C_E_BODY | C_E_PROJECTILE;
	dst->hitbox.originator = dst;
	dst->hitbox.hitbox_ptr = &(dst->sprite._dst);

	dst->hitbox.detect = NULL;
	dst->vel.x = *charge + 10;
	*charge = 0;
}

#define WHIRL_COOLDOWN (90)

t_weapon	whirl_cannon(void)
{
	t_weapon	whirl_cannon;

	whirl_cannon.type = B_SHIELD;
	SDLX_new_Sprite(&(whirl_cannon.ability_icon));
	fetch_whirl_sprite(&(whirl_cannon.ability_icon.sprite_data), 0);

	SDLX_new_Sprite(&(whirl_cannon.treasure_sprite));
	fetch_whirl_sprite(&(whirl_cannon.treasure_sprite.sprite_data), 1);

	whirl_cannon.start = 0;
	whirl_cannon.cooldown = WHIRL_COOLDOWN;

	whirl_cannon.curr = WHIRL_COOLDOWN;

	whirl_cannon.isEnabled = SDL_TRUE;
	whirl_cannon.meta_int = 0;

	whirl_cannon.factory = whirl_factory;
	whirl_cannon.trigger = whirl_fire;

	return (whirl_cannon);
}