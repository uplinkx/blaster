/***************************************************************************
 * FILENAME:    player.c
 * DESCRIPTION: Player struct file.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.54.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 12Jun2021
***************************************************************************/

#include "main.h"

void	player_init(t_player *player)
{
	player->sprite = SDLX_Sprite_Static(ASSETS"bunny.png");
	player->sprite.dst = &(player->sprite._dst);
	player->sprite._dst = (SDL_Rect){(PLAY_WIDTH - 48) / 2, (PLAY_HEIGHT - 48) / 2, 48, 48};

	SDLX_new_Sprite(&(player->hp_s));
	fetch_hp_sprite(&(player->hp_s.sprite_data), 1);
	player->hp_s._dst = (SDL_Rect){20, 375, 0, 8};

	SDLX_new_Sprite(&(player->hpl_s));
	fetch_hp_sprite(&(player->hpl_s.sprite_data), -1);
	player->hpl_s._dst = (SDL_Rect){20, 375, 50, 8};

	SDLX_new_Sprite(&(player->heart));
	fetch_hp_sprite(&(player->heart.sprite_data), 3);
	player->heart._dst = (SDL_Rect){4, 364, 32, 32};

	player->hp = 100;
	player->max_hp = 100;

	player->player_hurtbox.originator = player;
	player->player_hurtbox.detect = player_hit;
	player->player_hurtbox.engage = player_collide;
	player->player_hurtbox.type = PLAYER;
	player->hurtbox.x = player->sprite._dst.x + 5;
	player->hurtbox.y = player->sprite._dst.y + 5;
	player->hurtbox.h = player->sprite._dst.h - 10;
	player->hurtbox.w = player->sprite._dst.w - 10;

	player->player_hurtbox.detect_meta1 = &(player->hurtbox);

	projectile_queue(&(player->attacks));
}

SDL_bool	player_hit(SDL_UNUSED void *self, void *with, SDL_UNUSED void *meta, SDL_UNUSED void *meta1)
{
	SDLX_collision	*hitbox;
	t_player		*player;

	player = self;
	hitbox = with;
	if (hitbox->type == SLIMES || hitbox->type == GOO || hitbox->type == SLIMES_YELLOW)
	{
		if (SDL_HasIntersection(&(player->hurtbox), hitbox->detect_meta1) == SDL_TRUE)
			return (SDL_TRUE);
	}
	return (SDL_FALSE);
}

void		*player_collide(void *self, SDL_UNUSED void *with, SDL_UNUSED void *meta, SDL_UNUSED void *meta1)
{
	t_player	*player;
	SDLX_collision	*object;

	player = self;

	object = with;
	if (object->type == SLIMES)
		player->hp -= 10;
	if (object->type == SLIMES_YELLOW)
		player->hp -= 15;
	if (object->type == GOO)
		player->hp -= 15;
	return (NULL);
}

void	player_update(t_player *self)
{
	t_weapon	*weapon;
	t_bullet	attack;

	weapon = self->weapon_equip;

	if (weapon->trigger(weapon) == SDL_TRUE)
	{
		weapon->curr = weapon->start;
		weapon->factory(&(attack), (SDL_Point){0, 0}, 0, self);
		projectile_add(&(self->attacks), attack);
	}

	if (self->hp > self->max_hp) { self->hp = self->max_hp; }

	self->hp_s._dst.w = lerp32(((double)self->hp) / self->max_hp, 16, PLAY_WIDTH - 16);

	if (self->hpl_s._dst.w > self->hp_s._dst.w)
	{
		self->hpl_s._dst.w--;
	}
	else if (self->hpl_s._dst.w < self->hp_s._dst.w)
		self->hpl_s._dst.w = self->hp_s._dst.w;

	SDLX_RenderQueue_Add(NULL, &(self->heart));
	self->heart.current++;
	SDLX_RenderQueue_Add(NULL, &(self->hp_s));
	SDLX_RenderQueue_Add(NULL, &(self->hpl_s));

	SDLX_RenderQueue_Add(NULL, &(self->sprite));
	SDLX_CollisionBucket_add(NULL, &(self->player_hurtbox));

	SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, 0, 0, self->sprite._dst.x * 3, self->sprite._dst.y * 3);
}