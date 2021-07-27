/***************************************************************************
 * FILENAME:    entity_structs.h
 * DESCRIPTION: Header file for structs of entities, bullets, projectiles,
 * players, enemies.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 21Jul2021
***************************************************************************/

#ifndef ENITY_STRUCTS_H
# define ENITY_STRUCTS_H

# include "SDLX/SDLX.h"

struct s_bullet;
struct s_enemy_m;

typedef struct	s_weapon
{
	SDLX_Sprite		cooldown_sprite;

	unsigned int	start;
	unsigned int	cooldown;

	unsigned int	curr;

	SDL_bool		isEnabled;

	int				meta_int;
	void			*meta;

	SDL_bool	(*trigger)(struct s_weapon *);
	void		(*factory)(struct s_bullet *, SDL_Point, double , void *);
}				t_weapon;

typedef struct	s_bullet
{
	SDLX_Sprite		sprite;

	SDL_Point		vel;
	SDL_bool		isActive;

	void			*meta;
	void			(*update)(void *, void *);

	// void			(*realloc_fn)(t_bullet *, t_bullet *);

	SDLX_collision	hitbox;
}				t_bullet;

typedef struct	s_attacks
{
	size_t		capacity;

	t_bullet	*attacks;

	t_bullet	*delayed_free;

}				t_attacks;

typedef struct	s_enemy
{
	SDL_bool		isActive;

	SDLX_Sprite		sprite;
	SDLX_collision	enemy_hurtbox;

	int				hp;
	int				max_hp;

	void			*meta1;
	void			*meta2;

	struct s_enemy_m	*spawn_pool;
	t_attacks			*projectile_spawn;

	void			(*update)(struct s_enemy *, void *);
}				t_enemy;

typedef struct	s_enemy_m
{
	size_t		capacity;

	t_enemy		*entity_array;
}				t_enemy_m;

typedef struct	s_player
{
	SDLX_Sprite		sprite;
	SDL_Rect		hurtbox;

	SDLX_Sprite		hp_s;
	SDLX_Sprite		hpl_s;
	SDLX_Sprite		heart;

	int				hp;
	int				max_hp;

	t_weapon		*weapon_equip;

	SDLX_collision	player_hurtbox;

	//These are not permanent.
	t_attacks			attacks;
	void				*meta;
}				t_player;

#endif