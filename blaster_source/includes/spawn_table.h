/***************************************************************************
 * FILENAME:    spawn_table.h
 * DESCRIPTION: Table for spawning enemy types based on id.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 16Jul2021
***************************************************************************/

#ifndef SPAWN_TABLE_H
# define SPAWN_TABLE_H

#include "main_structs.h"
#include "entity.h"

typedef struct	s_spawn_elem
{
	int			type;
	void		(*fn)(t_enemy *, SDL_Point, int);
}				t_spawn_elem;

t_spawn_elem	spawn_table[] =
{
	{E_SLIME_CYAN, slime_init},
	{E_SLIME_BLUE, slime_blue_init},
	{E_SLIME_GREEN, slime_green_init},
	{E_SLIME_YELLOW, slime_yellow_init},
	{E_SLIME_PURPLE, slime_purple_init},
	{E_SLIME_PINK, slime_pink_init},
	{E_NONE, NULL},
};

#endif