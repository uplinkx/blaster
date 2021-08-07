/***************************************************************************
 * FILENAME:    slime_util.c
 * DESCRIPTION: Common Functions for Slimes
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 07Jul2021
***************************************************************************/

#include "main.h"

void	slime_default_init(t_enemy *slime, char *kind, int type, int max_hp, void (*update_fn)(t_enemy *, void *))
{
	char buff[30] = { 0 };

	SDL_snprintf(buff, 100, ASSETS"enemy/%s.png", kind);
	slime->isActive = SDL_TRUE;
	slime->sprite = SDLX_Sprite_Static(buff);

	slime->sprite.dst = SDLX_NULL_SELF;
	slime->sprite._dst = (SDL_Rect){10, 10, 32, 32};

	slime->enemy_hurtbox.originator = slime;
	slime->enemy_hurtbox.hitbox_ptr = &(slime->sprite._dst);
	slime->enemy_hurtbox.type = type;
	slime->enemy_hurtbox.detect = slime_detect_collision;
	slime->enemy_hurtbox.engage = slime_collide;

	slime->max_hp = max_hp;
	slime->hp = slime->max_hp;

	slime->update = update_fn;
}

SDL_bool	slime_detect_collision(void *self, void *with, SDL_UNUSED void *meta1, SDL_UNUSED void *meta2)
{
	SDLX_collision	*hitbox;
	t_enemy			*slime;

	slime = self;
	hitbox = with;

	if (hitbox->type == BULLETS || hitbox->type == C_PLAYER || hitbox->type == WHIRLWIND || hitbox->type == SPINE)
	{
		if (SDL_HasIntersection(&(slime->sprite._dst), hitbox->hitbox_ptr))
			return (SDL_TRUE);
	}

	if (hitbox->type == LUNGE)
		return (SDLX_Collide_RectToARect(&(slime->enemy_hurtbox), hitbox));

	return (SDL_FALSE);
}