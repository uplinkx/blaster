/***************************************************************************
 * FILENAME:    weapon_manager.c
 * DESCRIPTION: Manager for the weapon system.
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

void	init_attack_array(t_attacks *manager)
{
	manager->capacity = 1;
	manager->attacks = SDL_calloc(manager->capacity, sizeof(*(manager->attacks)));
}

void	projectile_update(t_attacks *attacks)
{
	size_t	ix;

	ix = 0;
	while (ix < attacks->capacity)
	{
		if (attacks->attacks[ix].active)
		{
			attacks->attacks[ix].update(&(attacks->attacks[ix]), NULL);
		}
		ix++;
	}
}

void		yellow_realloc(t_bullet *laser, SDL_UNUSED t_bullet *old)
{
	laser->hitbox.originator = laser;

	laser->hitbox.detect_meta1 = &(laser->sprite._dst);
	laser->hitbox.detect_meta2 = laser;
}

void		projectile_realloc(t_bullet *projectiles, t_bullet *old, size_t size)
{
	size_t	ix;

	ix = 0;
	while (ix < size)
	{
		if (projectiles[ix].active)
			yellow_realloc(&(projectiles[ix]), &(old[ix]));
		ix++;
	}
}

t_bullet	*spawn_projectile_addr(t_attacks *dst)
{
	size_t		ix;
	t_bullet	*old;

	ix = 0;
	while (ix < dst->capacity && dst->attacks[ix].active == SDL_TRUE)
		ix++;

	if (ix == dst->capacity)
	{
		old = SDL_calloc(dst->capacity * 2, sizeof(*(old)));
		SDL_memcpy(old, dst->attacks, sizeof(*(dst->attacks)) * dst->capacity);

		projectile_realloc(old, dst->attacks, dst->capacity);

		dst->attacks = old;
		dst->capacity = dst->capacity * 2;
	}

	return (&(dst->attacks[ix]));

}
