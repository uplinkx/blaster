/***************************************************************************
 * FILENAME:    main_structs.h
 * DESCRIPTION: Struts used in Blaster.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 21Jun2021
***************************************************************************/

#ifndef MAIN_STRUCTS_H
# define MAIN_STRUCTS_H

# include "SDLX/SDLX.h"
# include "waves.h"

struct s_context;
struct s_bullet;
struct s_enemy_m;

typedef void *(t_scene_fn)(struct s_context *, void *);

typedef	struct	s_loot
{
	size_t		type;
	void		*data;
}				t_loot;

typedef struct	s_level_progress
{
	SDL_bool	unlocked;
	t_scene_fn	*init_fn;
}				t_level_progress;

typedef struct	s_weapon
{
	SDLX_Sprite		cooldown_sprite;

	unsigned int	start;
	unsigned int	cooldown;

	unsigned int	curr;

	SDL_bool		enabled;

	int				meta_int;
	void			*meta;

	SDL_bool	(*trigger)(struct s_weapon *);
	void		(*factory)(struct s_bullet *, SDL_Point, double , void *);
}				t_weapon;

typedef struct	s_weapon_list
{
	SDL_bool	unlocked;
	int			weapon_type;
	t_weapon	weapon;
	char		*name;
}				t_weapon_list;

typedef struct	s_context
{
	SDL_bool	exit;
	SDL_bool	scene;

	void		*meta;

	SDLX_Sprite	background;
	SDL_Texture	*capture_texture;
	t_scene_fn	*redo_init_fn;
	t_scene_fn	*next_init_fn;
	t_loot		loot;

	t_scene_fn	*init_fn;
	t_scene_fn	*update_fn;
	t_scene_fn	*close_fn;

	struct s_weapon	mainhand;
	struct s_weapon	shield;
	struct s_weapon	heal;
	struct s_weapon	special;

	t_level_progress	levels[5][5];

}				t_context;

typedef struct	s_bullet
{
	SDLX_Sprite		sprite;

	SDL_Point		vel;
	SDL_bool		active;

	void			*meta;
	void			(*update)(void *, void *);

	SDLX_collision	hitbox;
}				t_bullet;

typedef struct	s_attacks
{
	size_t		index;
	size_t		capacity;

	t_bullet	*attacks;

}				t_attacks;

typedef struct	s_enemy
{
	SDL_bool		active;

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

typedef struct	s_pmenu
{
	SDLX_Sprite	background;

	SDLX_button	resume;
	SDLX_button	redo;
	SDLX_button	menu;
}				t_pmenu;

typedef struct	s_level
{
	SDLX_button			pause;
	t_pmenu				pause_menu;

	t_player			player;
	SDLX_Sprite			crosshair;

	SDLX_Sprite			bottom_ui;
	SDLX_button			mainhand, shield, heal, special;

	t_wave				stage;
	t_enemy_m			enemies;

	SDL_Texture			*pbackground;
}				t_level;

#endif