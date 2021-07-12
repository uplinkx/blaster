/***************************************************************************
 * FILENAME:    entity.h
 * DESCRIPTION: Header file for the functions of Entities.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 21Jun2021
***************************************************************************/

#ifndef ENTITY_H
# define ENTITY_H

# include "main_structs.h"

/*
**Player
*/

void		player_init(t_player *dst);
SDL_bool	player_hit(SDL_UNUSED void *self, void *with, SDL_UNUSED void *meta, SDL_UNUSED void *meta1);
void		*player_collide(void *self, void *with, SDL_UNUSED void *meta, SDL_UNUSED void *meta1);
void		player_update(t_player *self);

/*
**Weapons
*/

t_weapon		laser_cannon(void);
t_weapon		laser_green_cannon(void);
t_weapon		laser_yellow_cannon(void);

t_weapon		time_cannon(void);

t_weapon		heal_cannon(void);

t_weapon		whirl_cannon(void);
t_weapon		lunge_cannon(void);


/*
**Enemy
*/

void			slime_default_init(t_enemy *slime, char *kind, int type, int max_hp, void (*update_fn)(t_enemy *, void *));
void			slime_respawn(t_enemy *slime);

void			slime_init(t_enemy *dst);
void			slime_update(t_enemy *self, void *);
SDL_bool		slime_detect_collision(void *self, void *with, void *meta1, void *meta2);
void			*slime_collide(void *self, void *with, void *meta1, void *meta2);

void			slime_green_init(t_enemy *dst);

void			slime_yellow_init(t_enemy *dst);
void			slime_yellow_update(t_enemy *slime, SDL_UNUSED void *meta);

void			slime_purple_init(t_enemy *dst);
void			slime_purple_update(t_enemy *slime, SDL_UNUSED void *meta);

void			slime_pink_init(t_enemy *dst);
void			slime_pink_update(t_enemy *slime, SDL_UNUSED void *meta);

#endif