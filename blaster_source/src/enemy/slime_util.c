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

	SDL_memset(&(slime->effects), 0, sizeof(slime->effects));
	slime->enemy_hurtbox.originator = slime;

	slime->enemy_hurtbox.hitbox_ptr = &(slime->sprite._dst);
	slime->enemy_hurtbox.type = type;
	slime->enemy_hurtbox.response_amount = C_PROJECTILE | C_PLAYER | C_MELEE;
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
	SDL_bool		result;
	SDL_bool		(*collide_fn)(SDLX_collision *, SDLX_collision *);

	result = SDL_FALSE;
	slime = self;
	hitbox = with;

	collide_fn = SDLX_Collide_RectToRect;
	if (hitbox->type & C_ARECT)
		collide_fn = SDLX_Collide_RectToARect;
	else if (hitbox->type & C_CIRCLE)
		collide_fn = SDLX_Collide_RectToCircle;

	if (hitbox->type & slime->enemy_hurtbox.response_amount)
	{
		if (collide_fn(&(slime->enemy_hurtbox), hitbox) == SDL_TRUE)
			result = SDL_TRUE;
	}

	if (hitbox->type & C_FIELD && collide_fn(&(slime->enemy_hurtbox), hitbox) == SDL_TRUE)
		slime->effects[(size_t)hitbox->engage_meta1].info++;

	if (slime->effects[RUNIC_SHIELD].info >= 22)
	{
		slime->effects[RUNIC_SHIELD].info = 0;
			result = SDL_TRUE;
	}

	if (slime->effects[EMP_FIELD].info == 1)
	{
		slime->effects[(size_t)hitbox->engage_meta1].record = slime->speed;
		slime->speed = 0;
	}

	return (result);
}

SDL_bool	slime_detect_collision_once(void *self, void *with, SDL_UNUSED void *meta1, SDL_UNUSED void *meta2)
{
	SDLX_collision	*hitbox;
	t_enemy			*slime;
	t_bullet		*bullet;
	SDL_bool		(*collide_fn)(SDLX_collision *, SDLX_collision *);

	slime = self;
	hitbox = with;

	if (hitbox->type & C_PROJECTILE)
	{
		bullet = hitbox->originator;
		if (bullet->isActive == SDL_FALSE)
			return (SDL_FALSE);
	}

	if (hitbox->type & slime->enemy_hurtbox.response_amount)
	{
		collide_fn = SDLX_Collide_RectToRect;
		if (hitbox->type & C_ARECT)
			collide_fn = SDLX_Collide_RectToARect;

		if (collide_fn(&(slime->enemy_hurtbox), hitbox) == SDL_TRUE)
		{
			if (hitbox->type & C_PROJECTILE)
				bullet->isActive = SDL_FALSE;
			return (SDL_TRUE);
		}
	}

	if (hitbox->type & C_FIELD && SDLX_Collide_RectToRect(&(slime->enemy_hurtbox), hitbox) == SDL_TRUE)
		slime->effects[(size_t)hitbox->engage_meta1].info++;

	if (slime->effects[EMP_FIELD].info == 1)
	{
		slime->effects[(size_t)hitbox->engage_meta1].record = slime->speed;
		slime->speed = 0;
	}

	return (SDL_FALSE);
}