/***************************************************************************
 * FILENAME:    waves.c
 * DESCRIPTION: Handles spawning of entities per level basis.
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

// void	wave_init(t_wave *dst, int level_id)
// {
// 	char	*str;

// 	str = NULL;
// 	convert_file_to_str(&str, level_id);
// 	SDL_Log("CONT:\n%s", str);

// 	SDL_free(str);
// 	dst->size = 0;
// }

SDL_bool	begin_wave(t_wave *wave, size_t i)
{
	SDL_bool	result;

	result = SDL_FALSE;
	if (wave->waves[i].condition_type == WAVE_TICKS)
	{
		if (wave->waves[i - 1].tick >= wave->waves[i].condition_info)
			result = SDL_TRUE;
	}

	if (wave->waves[i].condition_type == WAVE_PREV_DEFEAT)
	{
		if (wave->waves[i - 1].complete == SDL_TRUE)
			result = SDL_TRUE;
	}

	wave->waves[i].active = result;
	return (result);
}

int		do_wave(t_wave_m *wave, t_enemy_m *enemy_man)
{
	size_t	i;
	t_enemy	*spawn_addr;

	i = 0;
	while (i < wave->size)
	{
		if (wave->tick == wave->wave_array[i].spawn_tick)
		{
			spawn_addr = spawn_enemy_addr(enemy_man);
			slime_init(spawn_addr, wave->wave_array[i].spawn_location, wave->wave_array[i].modifier);
			if (wave->wave_array[i].count == SDL_TRUE)
				spawn_addr->enemy_hurtbox.engage_meta2 = &(wave->finished_no);
		}
		i++;
	}

	wave->tick++;

	if (wave->finished_no >= wave->size)
	{
		wave->complete = SDL_TRUE;
		return (1);
	}
	return (0);

}

SDL_bool	wave_method(t_wave *wave, t_enemy_m *enemy_man)
{
	size_t	i;
	size_t		completed;
	size_t		killed;

	i = 0;
	completed = 0;
	killed = 0;
	while (i < wave->size)
	{
		if (wave->waves[i].complete == SDL_FALSE && (wave->waves[i].active || begin_wave(wave, i)))
			completed += do_wave(&(wave->waves[i]), enemy_man);
		killed += wave->waves[i].finished_no;
		i++;
	}

	if (completed >= wave->win_wave_no && killed >= wave->win_kill_count)
	{
		if (wave->win_wave == -1)
			return (SDL_TRUE);
		else if (wave->waves[wave->win_wave].complete == SDL_TRUE)
			return (SDL_TRUE);
	}
	return (SDL_FALSE);
}