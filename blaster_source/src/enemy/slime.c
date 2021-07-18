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

void		slime_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_blue", SLIMES, 1, slime_update);
	dst->sprite._dst.x = loc.x - (dst->sprite._dst.w / 2);
	dst->sprite._dst.y = loc.y - (dst->sprite._dst.h / 2);
	dst->meta1 = (void *)4;
}

void		slime_green_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_green", SLIMES, 2, slime_update);
	dst->sprite._dst.x = loc.x;
	dst->sprite._dst.y = loc.y;
	dst->meta1 = (void *)4;
}

void		slime_yellow_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_yellow", SLIMES_YELLOW, 2, slime_yellow_update);
	dst->sprite._dst.x = loc.x;
	dst->sprite._dst.y = loc.y;

	dst->meta1 = (void *)4;
	dst->meta2 = (void *)0;
}

void		slime_purple_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_purple", SLIMES, 3, slime_purple_update);
	dst->sprite._dst.x = loc.x;
	dst->sprite._dst.y = loc.y;
	dst->meta2 = 0;
}

void		slime_pink_init(t_enemy *dst, SDL_Point loc, SDL_UNUSED int mod)
{
	slime_default_init(dst, "slime_pink", SLIMES, 10, slime_pink_update);
	dst->sprite._dst.x = loc.x;
	dst->sprite._dst.y = loc.y;
	dst->meta2 = 0;
}

SDL_bool	slime_detect_collision(void *self, void *with, SDL_UNUSED void *meta1, SDL_UNUSED void *meta2)
{
	SDLX_collision	*hitbox;
	t_enemy			*slime;

	slime = self;
	hitbox = with;

	if (hitbox->type == BULLETS || hitbox->type == PLAYER || hitbox->type == WHIRLWIND)
	{
		if (SDL_HasIntersection(&(slime->sprite._dst), hitbox->detect_meta1))
			return (SDL_TRUE);
	}

	if (hitbox->type == LUNGE)
	{
		SDL_Point	lt;
		SDL_Point	rt;
		SDL_Point	lb;
		SDL_Point	rb;
		SDL_Rect	*box;
		double		angle;

		box = hitbox->detect_meta1;
		box = &(hitbox->hitbox);
		lt = (SDL_Point){box->x + 0		 - (PLAY_WIDTH / 2), box->y + 0 - (PLAY_HEIGHT / 2)};
		rt = (SDL_Point){box->x + box->w - (PLAY_WIDTH / 2), box->y + 0 - (PLAY_HEIGHT / 2)};
		lb = (SDL_Point){box->x + 0		 - (PLAY_WIDTH / 2), box->y + box->h - (PLAY_HEIGHT / 2)};
		rb = (SDL_Point){box->x + box->w - (PLAY_WIDTH / 2), box->y + box->h - (PLAY_HEIGHT / 2)};

		angle = hitbox->angle;

		lt = SDLX_RotatePoint(&lt, angle);
		rt = SDLX_RotatePoint(&rt, angle);
		lb = SDLX_RotatePoint(&lb, angle);
		rb = SDLX_RotatePoint(&rb, angle);

		lt.x += PLAY_WIDTH / 2;
		rt.x += PLAY_WIDTH / 2;
		lb.x += PLAY_WIDTH / 2;
		rb.x += PLAY_WIDTH / 2;

		lt.y += PLAY_HEIGHT / 2;
		rt.y += PLAY_HEIGHT / 2;
		lb.y += PLAY_HEIGHT / 2;
		rb.y += PLAY_HEIGHT / 2;

		// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lb.x, lb.y, lt.x, lt.y);
		// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lt.x, lt.y, rt.x, rt.y);
		// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lb.x, lb.y, rb.x, rb.y);
		// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, rt.x, rt.y, rb.x, rb.y);

		// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, box);

		if (
			SDL_IntersectRectAndLine(&(slime->sprite._dst), &(lb.x), &(lb.y), &(lt.x), &(lt.y)) ||
			SDL_IntersectRectAndLine(&(slime->sprite._dst), &(lt.x), &(lt.y), &(rt.x), &(rt.y)) ||
			SDL_IntersectRectAndLine(&(slime->sprite._dst), &(lb.x), &(lb.y), &(rb.x), &(rb.y)) ||
			SDL_IntersectRectAndLine(&(slime->sprite._dst), &(rt.x), &(rt.y), &(rb.x), &(rb.y)) ||
			SDL_IntersectRectAndLine(&(slime->sprite._dst), &(rt.x), &(rt.y), &(lb.x), &(lb.y)) //This one checks if a slime is within the space.
		)
			return (SDL_TRUE);
	}
	// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(slime->sprite._dst));

	return (SDL_FALSE);
}

void		*slime_collide(void *self, void *with, SDL_UNUSED void *meta1, SDL_UNUSED void *meta2)
{
	t_enemy			*slime;
	SDLX_collision	*hurtbox;

	slime = self;
	slime->hp -= 1;

	hurtbox = with;
	if (hurtbox->type == PLAYER)
	{
		slime->hp = 0;
	}

	if (hurtbox->type == LUNGE)
	{
		slime->hp -= 5;
		// slime->enemy_hurtbox.type = E_DEAD;
	}
	// if (hurtbox->type == WHIRLWIND)
	// 	slime->hp -= 5;

	(void)with;
	return (NULL);
}

void	slime_update(t_enemy *slime, SDL_UNUSED void *meta)
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
		slime->active = SDL_FALSE;
		score = slime->enemy_hurtbox.engage_meta2;
		(*score)++;
		// slime_respawn(slime);
	}
	else
	{
		SDLX_RenderQueue_Add(NULL, &(slime->sprite));
		SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
	}

	// SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &(slime->sprite._dst));
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
		slime->active = SDL_FALSE;
		score = slime->enemy_hurtbox.engage_meta2;
		(*score)++;
	}

	SDLX_RenderQueue_Add(NULL, &(slime->sprite));
	SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
}

SDL_bool	goo_detect_collision(void *self, void *with, void *meta1, void *meta2)
{
	SDLX_collision	*self_box;
	SDLX_collision	*hitbox;
	t_bullet		*self_attack;

	self_box = self;
	hitbox = with;

	self_attack = meta2;
	if (hitbox->type == PLAYER || hitbox->type == BULLETS)
	{
		if (SDL_HasIntersection(meta1, hitbox->detect_meta1))
			self_attack->active = SDL_FALSE;
	}


	(void)meta1;

	return (SDL_FALSE);
}

void	goo_update(void *self, SDL_UNUSED void *meta)
{
	t_bullet	*bullet;
	SDL_Rect	play_area;

	bullet = self;

	if (bullet->active == SDL_FALSE)
		return ;

	play_area = (SDL_Rect){0, 0, PLAY_WIDTH, PLAY_HEIGHT};
	if (SDL_HasIntersection(&(bullet->sprite._dst), &(play_area)) == SDL_FALSE)
	{
		bullet->active = SDL_FALSE;
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
	goo->active = SDL_TRUE;

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

	t_bullet	goo;

	if (fire_range == SDL_TRUE)
	{
		if ((int)slime->meta2 >= 30)
		{
			slime_goo(&goo, x, y);
			projectile_add(slime->meta1, goo);
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
		slime->active = SDL_FALSE;
		score = slime->enemy_hurtbox.engage_meta2;
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

	t_bullet	goo;

	if (fire_range == SDL_TRUE)
	{
		if ((int)slime->meta2 >= 30)
		{
			slime_goo(&goo, x, y);
			projectile_add(slime->meta1, goo);
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
		slime->active = SDL_FALSE;
		score = slime->enemy_hurtbox.engage_meta2;
		(*score)++;
	}

	SDLX_RenderQueue_Add(NULL, &(slime->sprite));
	SDLX_CollisionBucket_add(NULL, &(slime->enemy_hurtbox));
}