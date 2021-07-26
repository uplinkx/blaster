/***************************************************************************
 * FILENAME:    weapon_manager.c
 * DESCRIPTION: Manager for the projectiles and enemy systems.
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

#define DEFAULT_E_SIZE (100)
#define DEFAULT_P_SIZE (1)

void	init_enemy_array(t_enemy_m *manager) { manager->capacity = DEFAULT_E_SIZE; SDLX_CALLOC_M(manager->entity_array, manager->capacity); }
void	init_attack_array(t_attacks *manager) { manager->capacity = DEFAULT_P_SIZE; SDLX_CALLOC_M(manager->attacks, manager->capacity); }

void	enemy_apply_fn(void *ptr) {t_enemy *enemy = ptr; if (enemy->isActive) { enemy->update(enemy, NULL); } }
void	projectile_apply_fn(void *ptr) {t_bullet *projectile = ptr; if (projectile->isActive) { projectile->update(projectile, NULL); } }

void	projectile_update(t_attacks *attacks) { SDLX_xIter(attacks->attacks, attacks->capacity, sizeof(*(attacks->attacks)), projectile_apply_fn); }
void	iter_enemies(t_enemy_m *enemies) { SDLX_xIter(enemies->entity_array, enemies->capacity, sizeof(*(enemies->entity_array)), enemy_apply_fn); }

#define SELF_REF_REISSUE(new, old, lower, upper, name) 	\
	{													\
		if (lower <= old->name && old->name < upper)	\
		{ new->name = (new + (old->name - lower)); }	\
	}

void	reissue_projectile_references(t_bullet *new, t_bullet *old)
{
	void	*ptr_low_addr;
	void	*ptr_hi_addr;

	if (new->isActive == SDL_TRUE)
	{
		ptr_low_addr = old;
		ptr_hi_addr = old + sizeof(*old);
		/* Might need to check the sprite center and dst pointers too. */

		SELF_REF_REISSUE(new, old, ptr_low_addr, ptr_hi_addr, meta)
		SELF_REF_REISSUE(new, old, ptr_low_addr, ptr_hi_addr, hitbox.originator)
		SELF_REF_REISSUE(new, old, ptr_low_addr, ptr_hi_addr, hitbox.detect_meta1)
		SELF_REF_REISSUE(new, old, ptr_low_addr, ptr_hi_addr, hitbox.detect_meta2)
		SELF_REF_REISSUE(new, old, ptr_low_addr, ptr_hi_addr, hitbox.engage_meta1)
		SELF_REF_REISSUE(new, old, ptr_low_addr, ptr_hi_addr, hitbox.engage_meta2)
	}
}

void		projectile_realloc(t_bullet *projectiles, t_bullet *old, size_t size)
{
	size_t	ix;

	ix = 0;
	while (ix < size)
	{
		reissue_projectile_references(&(projectiles[ix]), &(old[ix]));
		ix++;
	}
}

t_bullet	*spawn_projectile_addr(t_attacks *dst)
{
	size_t		ix;
	t_bullet	*new;

	ix = 0;
	while (ix < dst->capacity && dst->attacks[ix].isActive == SDL_TRUE)
		ix++;

	if (ix == dst->capacity)
	{
		new = SDL_calloc(dst->capacity * 2, sizeof(*(new)));
		SDL_memcpy(new, dst->attacks, sizeof(*(dst->attacks)) * dst->capacity);

		projectile_realloc(new, dst->attacks, dst->capacity);

		SDL_free(dst->attacks);
		dst->attacks = new;
		dst->capacity = dst->capacity * 2;
	}

	return (&(dst->attacks[ix]));

}

t_enemy *spawn_enemy_addr(t_enemy_m *manager)
{
	size_t	ix;

	ix = 0;
	while (ix < manager->capacity && manager->entity_array[ix].isActive == SDL_TRUE)
		ix++;

	if (ix >= manager->capacity)
	{
		manager->capacity *= 2;
		manager->entity_array = SDL_realloc(manager->entity_array, manager->capacity * 2);
	}

	return (&(manager->entity_array[ix]));
}
