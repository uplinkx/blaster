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
	size_t		duration;

	bullet = self;
	duration = bullet->vel.x;

	if (bullet->isActive == SDL_FALSE) { return ; }
	if (bullet->sprite.current >= duration) { bullet->isActive = SDL_FALSE; return ; }

	bullet->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(bullet->sprite));
	SDLX_CollisionBucket_add(NULL, &(bullet->hitbox));
}

void	lunge_factory(t_bullet *dst, SDL_UNUSED SDL_Point spawn_point, SDL_UNUSED double angle, void *meta)
{
	t_player	*player;

	player = meta;

	SDLX_new_Sprite(&(dst->sprite));
	fetch_lunge_sprite(&(dst->sprite.sprite_data), 2);
	dst->sprite.dst = SDLX_NULL_SELF;
	dst->sprite._dst = (SDL_Rect){(PLAY_WIDTH - (17 * 3)) / 2, (PLAY_HEIGHT) / 2 - 42 * 3, (17 * 3), (42 * 3)};

	dst->sprite.center = SDLX_NULL_SELF;
	dst->sprite._center = (SDL_Point){(17 * 3) / 2, (42 * 3)};

	angle = ptoa(g_GameInput.GameInput.primary.x, g_GameInput.GameInput.primary.y);
	dst->sprite.angle = (angle * 180 / M_PI);

	dst->isActive = SDL_TRUE;

	dst->update = lunge_update;

	dst->hitbox.type = C_MELEE | C_ARECT;
	dst->hitbox.response_amount = C_E_BODY | C_E_PROJECTILE;
	dst->hitbox.originator = dst;

	dst->hitbox.angle = angle;
	dst->hitbox.hitbox = dst->sprite._dst;
	dst->hitbox.hitbox_ptr = &(dst->hitbox.hitbox);
	dst->hitbox.center = dst->sprite._center;
	dst->hitbox.center_ptr = &(dst->hitbox.center);

	dst->hitbox.hitbox.x += 10;
	// dst->hitbox.hitbox.y += 10;
	// dst->hitbox.hitbox.h -= 10;
	dst->hitbox.hitbox.w -= 20;
	dst->hitbox.center_ptr->x -= 10;

	dst->hitbox.detect = NULL;
	dst->vel.x = 5;

	dst->hitbox.engage_meta2 = &(player->weapon_equip->combo);
}

#define LUNGE_COOLDOWN (12)

t_weapon	lunge_cannon(void)
{
	t_weapon	lunge_cannon;

	lunge_cannon.type = B_OFFHAND;
	SDLX_new_Sprite(&(lunge_cannon.ability_icon));
	fetch_lunge_sprite(&(lunge_cannon.ability_icon.sprite_data), 0);

	SDLX_new_Sprite(&(lunge_cannon.treasure_sprite));
	fetch_lunge_sprite(&(lunge_cannon.treasure_sprite.sprite_data), 1);

	lunge_cannon.start = 0;
	lunge_cannon.cooldown = LUNGE_COOLDOWN;

	lunge_cannon.curr = LUNGE_COOLDOWN;

	lunge_cannon.isEnabled = SDL_TRUE;
	lunge_cannon.meta_int = 0;

	lunge_cannon.factory = lunge_factory;
	lunge_cannon.trigger = lunge_fire;

	combo_init(&(lunge_cannon.combo));

	return (lunge_cannon);
}