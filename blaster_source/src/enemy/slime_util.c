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
	slime->active = SDL_TRUE;
	slime->sprite = SDLX_Sprite_Static(buff);

	slime->sprite.dst = SDLX_NULL_SELF;
	slime->sprite._dst = (SDL_Rect){10, 10, 32, 32};

	slime->enemy_hurtbox.originator = slime;
	slime->enemy_hurtbox.detect_meta1 = &(slime->sprite._dst);
	slime->enemy_hurtbox.engage_meta1 = slime;
	slime->enemy_hurtbox.type = type;
	slime->enemy_hurtbox.detect = slime_detect_collision;
	slime->enemy_hurtbox.engage = slime_collide;

	slime->max_hp = max_hp;
	slime->hp = slime->max_hp;

	slime->update = update_fn;
}

void	slime_respawn(t_enemy *slime)
{
	// SDL_Log("Slime down, red chopper slime down!");
	int *score;

	score = slime->enemy_hurtbox.engage_meta2;
	*score += 1;
	if (rand() % 2 == 1)
	{
		slime->sprite.dst->x = rand() % PLAY_WIDTH;
		slime->sprite.dst->y = PLAY_HEIGHT * (rand() % 2);
	}
	else
	{
		slime->sprite.dst->y = (rand() - 16) % (PLAY_HEIGHT + 32);
		slime->sprite.dst->x = PLAY_WIDTH * (rand() % 2);
	}

	slime->hp = slime->max_hp;
	// slime->enemy_hurtbox.type = SLIMES;
}