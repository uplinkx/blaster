/***************************************************************************
 * FILENAME:    combo.c
 * DESCRIPTION: Manages combo functionality in the game.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 02Sep2021
***************************************************************************/

#include "main.h"

void	update_combo_active(t_combo *self)
{
	SDL_bool	active;

	active = SDL_FALSE;
	if (self->no >= 2)
	{
		active = SDL_TRUE;
		fetch_combo_sprite(&(self->sprite.sprite_data), self->no);
	}

	if (self->lifetime < self->sprite.current)
	{
		active = SDL_FALSE;
		self->no = 0;
		self->sprite.current = 0;
	}
	self->active = active;
}

void	update_combos(t_combo *mainhand, t_combo *offhand, t_combo *defense, t_combo *special)
{
	mainhand->sprite.current++;
	offhand->sprite.current++;
	defense->sprite.current++;
	special->sprite.current++;

	update_combo_active(mainhand);
	update_combo_active(offhand);
	update_combo_active(defense);
	update_combo_active(special);

	if (mainhand->active == SDL_TRUE) { SDLX_RenderQueue_Add(NULL, &(mainhand->sprite)); }
	if (offhand->active == SDL_TRUE) { SDLX_RenderQueue_Add(NULL, &(offhand->sprite)); }
	if (defense->active == SDL_TRUE) { SDLX_RenderQueue_Add(NULL, &(defense->sprite)); }
	if (special->active == SDL_TRUE) { SDLX_RenderQueue_Add(NULL, &(special->sprite)); }
}

void	combo_increment(t_combo *combo, SDL_Rect *hit)
{
	combo->no++;
	combo->sprite.current = 0;

	combo->sprite._dst.x = hit->x;
	combo->sprite._dst.y = hit->y;

	combo->sprite._dst.x = SDL_min(combo->sprite._dst.x, PLAY_WIDTH);
	combo->sprite._dst.y = SDL_min(combo->sprite._dst.y, PLAY_HEIGHT);

	combo->sprite._dst.x = SDL_max(combo->sprite._dst.x, 0);
	combo->sprite._dst.y = SDL_max(combo->sprite._dst.y, 0);
}

void	combo_init(t_combo *self)
{
	SDLX_new_Sprite(&(self->sprite));
	fetch_combo_sprite(&(self->sprite.sprite_data), 2);
	self->active = SDL_FALSE;
	self->no = 0;
	self->lifetime = 200;
	self->sprite._dst = (SDL_Rect){0, 0, 32, 32};
	self->sprite.dst = SDLX_NULL_SELF;
}