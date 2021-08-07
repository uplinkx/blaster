/***************************************************************************
 * FILENAME:    enemy.c
 * DESCRIPTION: Handles the slime
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 15Jun2021
***************************************************************************/

#include "main.h"

void		slime_cyan_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_cyan", SLIMES, 1, slime_cyan_update);
	dst->sprite._dst.x = loc.x - (dst->sprite._dst.w / 2);
	dst->sprite._dst.y = loc.y - (dst->sprite._dst.h / 2);
	dst->meta1 = (void *)4;
}

void		slime_spiny_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_spiny", SLIMES, 1, slime_spiny_update);
	dst->sprite._dst.x = loc.x - (dst->sprite._dst.w / 2);
	dst->sprite._dst.y = loc.y - (dst->sprite._dst.h / 2);
	dst->meta1 = (void *)4;
}

void		slime_inv_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_inv", SLIMES_INV, 1, slime_blue_update);
	dst->sprite._dst.x = loc.x - (dst->sprite._dst.w / 2);
	dst->sprite._dst.y = loc.y - (dst->sprite._dst.h / 2);
	dst->meta1 = (void *)4;
}

void		slime_blue_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_blue", SLIMES, 1, slime_blue_update);
	dst->sprite._dst.x = loc.x - (dst->sprite._dst.w / 2);
	dst->sprite._dst.y = loc.y - (dst->sprite._dst.h / 2);
	dst->meta1 = (void *)4;
}

void		slime_green_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_green", SLIMES, 2, slime_blue_update);
	dst->sprite._dst.x = loc.x;
	dst->sprite._dst.y = loc.y;
	dst->meta1 = (void *)4;
}

void		slime_yellow_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_yellow", SLIMES_YELLOW, 2, slime_yellow_update);
	dst->sprite._dst.x = loc.x - (dst->sprite._dst.w / 2);
	dst->sprite._dst.y = loc.y - (dst->sprite._dst.h / 2);

	dst->meta1 = (void *)4;
	dst->meta2 = (void *)0;
}

void		slime_purple_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_purple", SLIMES, 3, slime_purple_update);
	dst->sprite._dst.x = loc.x - (dst->sprite._dst.w / 2);
	dst->sprite._dst.y = loc.y - (dst->sprite._dst.h / 2);
	dst->meta2 = 0;
}

void		slime_pink_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_pink", SLIMES, 10, slime_pink_update);
	dst->sprite._dst.x = loc.x - (dst->sprite._dst.w / 2);
	dst->sprite._dst.y = loc.y - (dst->sprite._dst.h / 2);
	dst->meta2 = 0;
}

void		*slime_collide(void *self, void *with, SDL_UNUSED void *meta1, SDL_UNUSED void *meta2)
{
	t_enemy			*slime;
	SDLX_collision	*hurtbox;

	slime = self;
	slime->hp -= 1;

	hurtbox = with;
	if (hurtbox->type == C_PLAYER)
		slime->hp = 0;

	return (NULL);
}

void	slime_cyan_update(t_enemy *slime, SDL_UNUSED void *meta)
{
	int			dx;
	int			dy;
	size_t		*score;
	int move = rand() % 9;

	dx = 0;
	dy = 0;
	if (move % 3 == 1)
		dx++;
	else if (move % 3 == 2)
		dx--;

	if (move / 3 == 1)
		dy++;
	else if (move / 3 == 2)
		dy--;

	int x = slime->sprite._dst.x - MID_PLAY_WIDTH + 16;
	int y = slime->sprite._dst.y - MID_PLAY_HEIGHT + 16;

	if (x * x + y * y > (x + dx) * (x + dx) + y * y)
		slime->sprite._dst.x += dx * (int)(slime->meta1);

	if (x * x + y * y > x * x + (y + dy) * (y + dy))
		slime->sprite._dst.y += dy * (int)(slime->meta1);

	if (slime->hp <= 0)
	{
		slime->isActive = SDL_FALSE;
		score = slime->score_ptr;
		(*score)++;
	}
	else
	{
		SDLX_RenderQueue_Add(NULL, &(slime->sprite));
		SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
	}

	// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(slime->sprite._dst));
}

void	slime_blue_update(t_enemy *slime, SDL_UNUSED void *meta)
{
	size_t		*score;
	double		angle;
	int			dx, dy;

	angle = ptoa(slime->sprite._dst.x + 16, slime->sprite._dst.y + 16);

	dx = SDL_sin(angle) * 2;
	dy = SDL_cos(angle) * -2;

	SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, WIN_WIDTH / 2, WIN_HEIGHT / 2, WIN_WIDTH / 2 + dx, WIN_HEIGHT / 2 + dy);

	slime->sprite._dst.x -= dx;
	slime->sprite._dst.y -= dy;

	if (slime->hp <= 0)
	{
		slime->isActive = SDL_FALSE;
		score = slime->score_ptr;
		(*score)++;
	}
	else
	{
		SDLX_RenderQueue_Add(NULL, &(slime->sprite));
		SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
	}
}

void	slime_yellow_update(t_enemy *slime, SDL_UNUSED void *meta)
{
	SDL_bool	enraged;
	int			x, y;
	int			dx, dy;
	size_t		*score;

	enraged = SDL_FALSE;
	y = slime->sprite._dst.y;
	x = slime->sprite._dst.x;

	dx = x - ((PLAY_WIDTH - 16 * 3) / 2);
	dy = y - ((PLAY_WIDTH + 16 * 3) / 2);

	if ((dx * dx) + (dy * dy) < 130 * 130)
	{
		enraged = SDL_TRUE;
		slime->meta2++;
	}

	if (enraged)
	{
		if ((int)slime->meta2 > 15)
		{
			if (x < (PLAY_WIDTH - 32) / 2)	{ x += 7; }
			else							{ x -= 7; }
			if (y < (PLAY_WIDTH + 32) / 2)	{ y += 7; }
			else							{ y -= 7; }
		}
	}
	else
	{
		if (x < (PLAY_WIDTH - 32) / 2) x++;
		else x--;
		if (y < (PLAY_WIDTH + 32) / 2) y++;
		else y--;
	}

	slime->sprite._dst.x = x;
	slime->sprite._dst.y = y;

	if (slime->hp <= 0)
	{
		slime->isActive = SDL_FALSE;
		score = slime->score_ptr;
		(*score)++;
	}

	SDLX_RenderQueue_Add(NULL, &(slime->sprite));
	SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
}

SDL_bool	goo_detect_collision(void *self, void *with, SDL_UNUSED void *meta1, SDL_UNUSED void *meta2)
{
	SDLX_collision	*hitbox;
	t_bullet		*self_attack;

	hitbox = with;

	self_attack = self;
	if (hitbox->type == C_PLAYER || hitbox->type == BULLETS || hitbox->type == WHIRLWIND)
	{
		if (SDL_HasIntersection(self_attack->hitbox.hitbox_ptr, hitbox->hitbox_ptr))
			self_attack->isActive = SDL_FALSE;
	}
	return (SDL_FALSE);
}

void	goo_update(void *self, SDL_UNUSED void *meta)
{
	t_bullet	*bullet;
	SDL_Rect	play_area;

	bullet = self;

	if (bullet->isActive == SDL_FALSE)
		return ;

	play_area = (SDL_Rect){0, 0, PLAY_WIDTH, PLAY_HEIGHT};
	if (SDL_HasIntersection(&(bullet->sprite._dst), &(play_area)) == SDL_FALSE)
	{
		bullet->isActive = SDL_FALSE;
		SDL_free(bullet->sprite.sprite_data);
		return ;
	}

	double x, y;
	double angle;

	angle = ptoa(bullet->sprite._dst.x, bullet->sprite._dst.y);

	x = SDL_sin(angle) * 3;
	y = SDL_cos(angle) * -3;

	bullet->sprite._dst.x -= x;
	bullet->sprite._dst.y -= y;
	SDLX_RenderQueue_Add(NULL, &(bullet->sprite));
	SDLX_CollisionBucket_add(NULL, &(bullet->hitbox));
}

void	slime_goo(t_bullet *goo, int x, int y)
{
	goo->sprite = SDLX_Sprite_Static(ASSETS"goo.png");
	goo->sprite.dst = SDLX_NULL_SELF;
	goo->sprite._dst = (SDL_Rect){x + 8, y + 8, 16, 16};
	goo->sprite.center = NULL;
	goo->sprite.angle = 0;
	goo->isActive = SDL_TRUE;

	double	angle;

	angle = ptoa(x + 8, y + 8);
	goo->sprite.angle = (angle * 180 / M_PI) + 180.0;

	goo->vel.x = SDL_sin(angle) * 3;
	goo->vel.y = SDL_cos(angle) * -3;

	goo->update = goo_update;

	goo->hitbox.type = GOO;
	goo->hitbox.originator = goo;

	goo->hitbox.detect = goo_detect_collision;
}

void	slime_purple_update(t_enemy *slime, SDL_UNUSED void *meta)
{
	SDL_bool	fire_range;
	int			x, y;
	int			dx, dy;
	size_t		*score;

	fire_range = SDL_FALSE;
	y = slime->sprite._dst.y;
	x = slime->sprite._dst.x;

	dx = x - ((PLAY_WIDTH - 16 * 3) / 2);
	dy = y - ((PLAY_WIDTH + 16 * 3) / 2);

	if ((dx * dx) + (dy * dy) < 100 * 100)
	{
		fire_range = SDL_TRUE;
		slime->meta2++;
	}

	t_bullet	*goo;

	if (fire_range == SDL_TRUE)
	{
		if ((int)slime->meta2 >= 30)
		{
			goo = spawn_projectile_addr(slime->projectile_spawn);
			slime_goo(goo, x, y);
			slime->meta2 = (void *)10;
		}
	}
	else
	{
		if (x < (PLAY_WIDTH - 32) / 2) x++;
		else x--;
		if (y < (PLAY_WIDTH + 32) / 2) y++;
		else y--;
	}

	slime->sprite._dst.x = x;
	slime->sprite._dst.y = y;

	if (slime->hp <= 0)
	{
		slime->isActive = SDL_FALSE;
		score = slime->score_ptr;
		(*score)++;
	}

	SDLX_RenderQueue_Add(NULL, &(slime->sprite));
	SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
}

void	slime_pink_update(t_enemy *slime, SDL_UNUSED void *meta)
{
	SDL_bool	fire_range;
	int			x, y;
	int			dx, dy;
	size_t		*score;

	fire_range = SDL_FALSE;
	y = slime->sprite._dst.y;
	x = slime->sprite._dst.x;

	dx = x - ((PLAY_WIDTH - 16 * 3) / 2);
	dy = y - ((PLAY_WIDTH + 16 * 3) / 2);

	if ((dx * dx) + (dy * dy) < 120 * 120)
	{
		fire_range = SDL_TRUE;
		slime->meta2++;
	}

	t_bullet	*goo;

	if (fire_range == SDL_TRUE)
	{
		if ((int)slime->meta2 >= 30)
		{
			goo = spawn_projectile_addr(slime->meta1);
			slime_goo(goo, x, y);
			slime->meta2 = (void *)20;
		}
	}
	else
	{
		if (x < (PLAY_WIDTH - 32) / 2) x++;
		else x--;
		if (y < (PLAY_WIDTH + 32) / 2) y++;
		else y--;
	}

	slime->sprite._dst.x = x;
	slime->sprite._dst.y = y;

	if (slime->hp <= 0)
	{
		slime->isActive = SDL_FALSE;
		score = slime->score_ptr;
		(*score)++;
	}

	SDLX_RenderQueue_Add(NULL, &(slime->sprite));
	SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
}

void	spine_update(void *self, SDL_UNUSED void *meta)
{
	t_bullet	*bullet;
	SDL_Rect	play_area;

	bullet = self;

	if (bullet->isActive == SDL_FALSE)
		return ;

	play_area = (SDL_Rect){0, 0, PLAY_WIDTH, PLAY_HEIGHT};
	if (SDL_HasIntersection(&(bullet->sprite._dst), &(play_area)) == SDL_FALSE)
	{
		bullet->isActive = SDL_FALSE;
		SDL_free(bullet->sprite.sprite_data);
		return ;
	}

	bullet->sprite._dst.x -= bullet->vel.x;
	bullet->sprite._dst.y -= bullet->vel.y;
	SDLX_RenderQueue_Add(NULL, &(bullet->sprite));
	SDLX_CollisionBucket_add(NULL, &(bullet->hitbox));
}

SDL_bool	spine_detect_collision(void *self, void *with, SDL_UNUSED void *meta1, SDL_UNUSED void *meta2)
{
	SDLX_collision	*hitbox;
	t_bullet		*self_attack;

	hitbox = with;

	self_attack = self;
	if (hitbox->type == C_PLAYER || hitbox->type == BULLETS || hitbox->type == SLIMES || hitbox->type == SLIMES_YELLOW || hitbox->type == WHIRLWIND || hitbox->type == SLIMES_INV)
	{
		if (SDL_HasIntersection(self_attack->hitbox.hitbox_ptr, hitbox->hitbox_ptr))
			self_attack->isActive = SDL_FALSE;
	}

	return (SDL_FALSE);
}

void	slime_spine(t_bullet *spine, int x, int y, double angle)
{
	spine->sprite = SDLX_Sprite_Static(ASSETS"spine.png");
	spine->sprite.dst = SDLX_NULL_SELF;
	spine->sprite._dst = (SDL_Rect){x + 8, y + 8, 16, 16};
	spine->sprite.center = NULL;
	spine->sprite.angle = (angle * 180 / M_PI) + 180;
	spine->isActive = SDL_TRUE;

	spine->vel.x = SDL_sin(angle) * 3;
	spine->vel.y = SDL_cos(angle) * -3;

	spine->update = spine_update;

	spine->hitbox.type = SPINE;
	spine->hitbox.originator = spine;

	/* Careful with setting pointers to internal pointers that may change */
	spine->hitbox.hitbox_ptr = &(spine->sprite._dst);
	// spine->hitbox.detect_meta2 = spine;
	spine->meta = &(spine->sprite._dst);

	spine->hitbox.detect = spine_detect_collision;
}

void	slime_spiny_update(t_enemy *slime, SDL_UNUSED void *meta)
{
	size_t		*score;
	double		angle;
	int			dx, dy;
	int			x, y;
	int			speed;
	t_bullet	*spine;

	x = slime->sprite._dst.x + 16 - (PLAY_WIDTH / 2);
	y = slime->sprite._dst.y + 16 - (PLAY_HEIGHT / 2);

	speed = 2;
	angle = ptoa(slime->sprite._dst.x + 16, slime->sprite._dst.y + 16);
	if (x * x + y * y < 100 * 100)
	{
		angle += M_PI_2;
		speed += 2;
	}

	dx = SDL_sin(angle) * (speed);
	dy = SDL_cos(angle) * -(speed);

	slime->sprite._dst.x -= dx;
	slime->sprite._dst.y -= dy;

	if (slime->hp <= 0)
	{
		slime->isActive = SDL_FALSE;
		score = slime->score_ptr;
		(*score)++;
		angle = M_PI_4;
		spine = spawn_projectile_addr(slime->projectile_spawn);
		slime_spine(spine, slime->sprite._dst.x, slime->sprite._dst.y, angle);
		angle += M_PI_2;
		spine = spawn_projectile_addr(slime->projectile_spawn);
		slime_spine(spine, slime->sprite._dst.x, slime->sprite._dst.y, angle);
		angle += M_PI_2;
		spine = spawn_projectile_addr(slime->projectile_spawn);
		slime_spine(spine, slime->sprite._dst.x, slime->sprite._dst.y, angle);
		angle += M_PI_2;
		spine = spawn_projectile_addr(slime->projectile_spawn);
		slime_spine(spine, slime->sprite._dst.x, slime->sprite._dst.y, angle);
	}
	else
	{
		SDLX_RenderQueue_Add(NULL, &(slime->sprite));
		SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
	}
}