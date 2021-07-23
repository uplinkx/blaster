/***************************************************************************
 * FILENAME:    enemy_manager.c
 * DESCRIPTION: Manages the enemy array.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 16Jul2021
***************************************************************************/

#include "main.h"

#define DEFAULT_E_SIZE (100)

void	init_enemy_array(t_enemy_m *manager)
{
	manager->capacity = DEFAULT_E_SIZE;
	manager->entity_array = SDL_calloc(manager->capacity, sizeof(*(manager->entity_array)));
}

t_enemy *spawn_enemy_addr(t_enemy_m *manager)
{
	size_t	i;

	i = 0;
	while (i < manager->capacity && manager->entity_array[i].active == SDL_TRUE)
		i++;

	if (i >= manager->capacity)
	{
		manager->capacity *= 2;
		manager->entity_array = SDL_realloc(manager->entity_array, manager->capacity * 2);
	}

	return (&(manager->entity_array[i]));
}

void	iter_enemies(t_enemy_m *enemies)
{
	size_t	i;

	i = 0;
	while (i < enemies->capacity)
	{
		if (enemies->entity_array[i].active)
			enemies->entity_array[i].update(&(enemies->entity_array[i]), NULL);
		i++;
	}
}