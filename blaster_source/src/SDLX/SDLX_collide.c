/***************************************************************************
 * FILENAME:    SDLX_collide.c
 * DESCRIPTION: Does object to object collisions and returns true
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 06Aug2021
***************************************************************************/

#include "SDLX.h"

SDL_bool	SDLX_Collide_RectToRect(SDLX_collision *hitbox1, SDLX_collision *hitbox2)
{
	SDL_bool	res;

	res = SDL_FALSE;
	SDL_assert(hitbox1->hitbox_ptr != NULL);
	SDL_assert(hitbox2->hitbox_ptr != NULL);
	if (SDL_HasIntersection(hitbox1->hitbox_ptr, hitbox2->hitbox_ptr) == SDL_TRUE)
		res = SDL_TRUE;

	return (res);
}

SDL_bool	SDLX_Collide_RectToARect(SDLX_collision *hitbox1, SDLX_collision *angle_box)
{
	double					angle;
	SDL_bool				res;

	SDL_Point	lt;
	SDL_Point	rt;
	SDL_Point	lb;
	SDL_Point	rb;
	SDL_Rect	*box;
	SDL_Point	norm;

	res = SDL_FALSE;
	angle = angle_box->angle + M_PI;
	box = angle_box->hitbox_ptr;

	norm.x = 0;
	norm.y = 0;
	if (angle_box->center != NULL)
	{
		norm.x = angle_box->center->x - (box->w / 2);
		norm.y = angle_box->center->y - (box->h / 2);
	}

	lt = (SDL_Point){norm.x - (box->w / 2), norm.y + (box->h / 2)};
	rt = (SDL_Point){norm.x + (box->w / 2), norm.y + (box->h / 2)};
	lb = (SDL_Point){norm.x - (box->w / 2), norm.y - (box->h / 2)};
	rb = (SDL_Point){norm.x + (box->w / 2), norm.y - (box->h / 2)};

	lt = SDLX_RotatePoint(&lt, angle);
	rt = SDLX_RotatePoint(&rt, angle);
	lb = SDLX_RotatePoint(&lb, angle);
	rb = SDLX_RotatePoint(&rb, angle);

	lt.x += (box->x + (angle_box->center->x));
	rt.x += (box->x + (angle_box->center->x));
	lb.x += (box->x + (angle_box->center->x));
	rb.x += (box->x + (angle_box->center->x));

	lt.y += (box->y + (angle_box->center->y));
	rt.y += (box->y + (angle_box->center->y));
	lb.y += (box->y + (angle_box->center->y));
	rb.y += (box->y + (angle_box->center->y));
	// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lt.x, lt.y, rt.x, rt.y);
	// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lt.x, lt.y, lb.x, lb.y);
	// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, rt.x, rt.y, rb.x, rb.y);
	// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lb.x, lb.y, rb.x, rb.y);

	if (
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(lb.x), &(lb.y), &(lt.x), &(lt.y)) ||
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(lt.x), &(lt.y), &(rt.x), &(rt.y)) ||
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(lb.x), &(lb.y), &(rb.x), &(rb.y)) ||
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(rt.x), &(rt.y), &(rb.x), &(rb.y)) ||

		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(rt.x), &(rt.y), &(lb.x), &(lb.y)) || //This one checks if a hitbox is within the larger one.
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(rb.x), &(rb.y), &(lt.x), &(lt.y)) //This one checks if a hitbox is within the larger one.
		)
		res = SDL_TRUE;

	return (res);
}

SDL_bool	SDLX_Collide_ARectToRect(SDLX_collision *angle_box, SDLX_collision *hitbox1)
{
	return (SDLX_Collide_RectToARect(hitbox1, angle_box));
}