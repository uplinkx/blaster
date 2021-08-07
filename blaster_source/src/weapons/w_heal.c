/***************************************************************************
 * FILENAME:    heal.c
 * DESCRIPTION: Handles the heal weapon
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

SDL_bool	heal_fire(SDL_UNUSED t_weapon *weapon)
{
	SDL_bool	result;

	result = SDL_FALSE;

	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primleft) && weapon->curr >= weapon->cooldown)
	{
		SDLX_INPUT_CONSUME(g_GameInput, g_GameInput_prev, primleft);
		result = SDL_TRUE;
	}

	return (result);
}

void	heal_update(void *self, SDL_UNUSED void *meta)
{
	t_bullet	*bullet;

	bullet = self;

	if (bullet->isActive == SDL_FALSE) { return ; }
	if (bullet->sprite.current == 8) { bullet->isActive = SDL_FALSE; return ; }

	bullet->sprite.current++;
	SDLX_RenderQueue_Add(NULL, &(bullet->sprite));
}

void	heal_factory(t_bullet *dst, SDL_UNUSED SDL_Point spawn_point, SDL_UNUSED double angle, SDL_UNUSED void *meta)
{
	SDLX_new_Sprite(&(dst->sprite));
	fetch_heal_sprite(&(dst->sprite.sprite_data), 2);
	dst->sprite.dst = SDLX_NULL_SELF;
	dst->sprite._dst = (SDL_Rect){(PLAY_WIDTH - 64) / 2, 9 * 16 + 2, 64, 64};

	dst->isActive = SDL_TRUE;

	dst->update = heal_update;

	dst->hitbox.type = C_NONE | C_RECT;
	dst->hitbox.originator = dst;

	dst->hitbox.detect = NULL;

	t_player *player;
	player = meta;
	player->hp += 30;
}

#define HEAL_COOLDOWN (80)

t_weapon	heal_cannon(void)
{
	t_weapon	heal_cannon;

	heal_cannon.type = B_HEAL;

	SDLX_new_Sprite(&(heal_cannon.ability_icon));
	fetch_heal_sprite(&(heal_cannon.ability_icon.sprite_data), 0);

	SDLX_new_Sprite(&(heal_cannon.treasure_sprite));
	fetch_heal_sprite(&(heal_cannon.treasure_sprite.sprite_data), 1);

	heal_cannon.start = 0;
	heal_cannon.cooldown = HEAL_COOLDOWN;

	heal_cannon.curr = HEAL_COOLDOWN;

	heal_cannon.isEnabled = SDL_TRUE;
	heal_cannon.meta_int = 0;

	heal_cannon.factory = heal_factory;
	heal_cannon.trigger = heal_fire;

	return (heal_cannon);
}