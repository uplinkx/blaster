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