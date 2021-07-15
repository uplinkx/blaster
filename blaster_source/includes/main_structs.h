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

struct s_context;
struct s_bullet;

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

typedef struct	s_context
{
	SDL_bool	exit;
	SDL_bool	scene;

	int			ticks;

	void		*meta;

	SDL_Texture	*capture_texture;
	t_scene_fn	*redo_init_fn;
	t_scene_fn	*next_init_fn;
	t_loot		loot;

	t_level_progress	levels[5][5];

	SDLX_Sprite	background;

	t_scene_fn	*init_fn;
	t_scene_fn	*update_fn;
	t_scene_fn	*close_fn;

	struct s_weapon	mainhand;
	struct s_weapon	shield;
	struct s_weapon	heal;
	struct s_weapon	special;

}				t_context;

enum	BLASTER_UI_SPRITES
{
	LOCK_NORM,
	LOCK_HOVER,
	BACK_NORM,
	BACK_HOVER,

	PLAY_NORM,
	PLAY_HOVER,
	CREDIT_NORM,
	CREDIT_HOVER,
	PAUSE_NORM,

	MMENU_NORM,
	MMENU_HOVER,
	MREDO_NORM,
	MREDO_HOVER,
	MPLAY_NORM,
	MPLAY_HOVER,
	MBACK,

	IMENU_NORM,
	IMENU_HOVER,
	IPREV_NORM,
	IPREV_HOVER,
	INEXT_NORM,
	INEXT_HOVER,
	IINFO_NORM,
	IINFO_HOVER,
	IBACK_NORM,
	IBACK_HOVER,

	LMENU_NORM,
	LMENU_HOVER,
	LREDO_NORM,
	LREDO_HOVER,
	LNEXT_NORM,
	LNEXT_HOVER,
	LINVT_NORM,
	LINVT_HOVER,
	LBACK,
	DBACK,

	ABILITY,
	ABILITY_SEL,

	EMPTY_UI,
};

enum	BLASTER_COLLISION_TYPES
{
	E_NONE,
	E_DEAD,
	BULLETS,
	WHIRLWIND,
	LUNGE,
	SLIMES,
	SLIMES_YELLOW,
	PLAYER,
	HEAL,
	GOO,
};

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
	SDLX_Sprite		sprite;
	SDLX_collision	enemy_hurtbox;

	int				hp;
	int				max_hp;

	void			*meta1;
	void			*meta2;

	void			(*update)(struct s_enemy *, void *);
}				t_enemy;

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

#endif