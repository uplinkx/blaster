/***************************************************************************
 * FILENAME:    weapn_utils.c
 * DESCRIPTION: Utility functions for weapon struct.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 26Jun2021
***************************************************************************/

#include "main.h"

SDL_bool	empty_weapon_trigger(SDL_UNUSED t_weapon *self) { return (SDL_FALSE); }

void	empty_weapon_factory(SDL_UNUSED t_bullet *loc, SDL_UNUSED SDL_Point spawn, SDL_UNUSED double angle, SDL_UNUSED void *meta)
{ return ; }

void	unequip_weapon(t_weapon *dst)
{
	dst->start = 0;
	dst->cooldown = 1;

	dst->curr = 0;

	dst->isEnabled = SDL_FALSE;
	dst->factory = empty_weapon_factory;
	dst->trigger = empty_weapon_trigger;
}

t_weapon	default_cannon(void)
{
	t_weapon	default_cannon;

	default_cannon = laser_cannon();
	return (default_cannon);
}

#define ABILITY_LEFT_PADDING (16)

void	load_weapons(t_context *context, t_weapon **player_weapon_addr, SDLX_button *mainhand, SDLX_button *shield, SDLX_button *heal, SDLX_button *special)
{
	size_t		i;
	size_t		ability_bar_width;
	size_t		ability_space;
	size_t		count;
	SDLX_button	*line[4];
	int			*keys[4] = {&(BMAP(button_num1)), &(BMAP(button_num2)), &(BMAP(button_num3)), &(BMAP(button_num4))};

	ability_button_init(mainhand, player_weapon_addr, &(context->mainhand));
	ability_button_init(special, player_weapon_addr, &(context->special));
	ability_button_init(shield, player_weapon_addr, &(context->shield));
	ability_button_init(heal, player_weapon_addr, &(context->heal));

	fetch_ui_sprite(&(context->mainhand.cooldown_sprite.sprite_data), EMPTY_UI);
	fetch_ui_sprite(&(context->special.cooldown_sprite.sprite_data), EMPTY_UI);
	fetch_ui_sprite(&(context->shield.cooldown_sprite.sprite_data), EMPTY_UI);
	fetch_ui_sprite(&(context->heal.cooldown_sprite.sprite_data), EMPTY_UI);

	context->mainhand.curr = context->mainhand.cooldown;
	context->special.curr = context->special.cooldown;
	context->shield.curr = context->shield.cooldown;
	context->heal.curr = context->heal.cooldown;

	context->mainhand.meta_int = 0;
	context->special.meta_int = 0;
	context->shield.meta_int = 0;
	context->heal.meta_int = 0;

	count = 0;
	if (context->mainhand.isEnabled == SDL_TRUE) { line[count] = mainhand; context->mainhand.cooldown_sprite = SDLX_Sprite_Static(ASSETS"cooldown.png"); mainhand->down = keys[count]; count++; }
	if (context->shield.isEnabled == SDL_TRUE) { line[count] = shield; context->shield.cooldown_sprite = SDLX_Sprite_Static(ASSETS"cooldown.png"); shield->down = keys[count]; count++; }
	if (context->heal.isEnabled == SDL_TRUE) { line[count] = heal; context->heal.cooldown_sprite = SDLX_Sprite_Static(ASSETS"cooldown.png"); heal->down = keys[count]; count++; }
	if (context->special.isEnabled == SDL_TRUE) { line[count] = special; context->special.cooldown_sprite = SDLX_Sprite_Static(ASSETS"cooldown.png"); special->down = keys[count]; count++; }

	if (count == 0)
	{
		context->mainhand = default_cannon();

		line[count] = mainhand;
		context->mainhand.cooldown_sprite = SDLX_Sprite_Static(ASSETS"cooldown.png");
		mainhand->down = keys[count];
		count++;

		ability_button_init(mainhand, player_weapon_addr, &(context->mainhand));
		context->mainhand.curr = context->mainhand.cooldown;
		context->mainhand.meta_int = 0;
	}

	i = 0;
	SDL_assert(count != 0);
	ability_bar_width = 304 - ABILITY_LEFT_PADDING - ABILITY_LEFT_PADDING;
	ability_space = (ability_bar_width - (mainhand->sprite._dst.w * count)) / (count);
	while (i < count)
	{
		line[i]->sprite._dst.x = ABILITY_LEFT_PADDING + (i * (ability_space + 48)) + (ability_space / 2);
		line[i]->trigger_box = line[i]->sprite._dst;
		i++;
	}

	context->mainhand.cooldown_sprite.dst = SDLX_NULL_SELF;
	context->special.cooldown_sprite.dst = SDLX_NULL_SELF;
	context->shield.cooldown_sprite.dst = SDLX_NULL_SELF;
	context->heal.cooldown_sprite.dst = SDLX_NULL_SELF;

	context->mainhand.cooldown_sprite.center = SDLX_NULL_SELF;
	context->special.cooldown_sprite.center = SDLX_NULL_SELF;
	context->shield.cooldown_sprite.center = SDLX_NULL_SELF;
	context->heal.cooldown_sprite.center = SDLX_NULL_SELF;

	context->mainhand.cooldown_sprite._dst = mainhand->sprite._dst;
	context->special.cooldown_sprite._dst = special->sprite._dst;
	context->shield.cooldown_sprite._dst = shield->sprite._dst;
	context->heal.cooldown_sprite._dst = heal->sprite._dst;

	if (context->mainhand.isEnabled) { *player_weapon_addr = &(context->mainhand); }
	else if (context->shield.isEnabled) { *player_weapon_addr = &(context->shield); }
	else if (context->heal.isEnabled) { *player_weapon_addr = &(context->heal); }
	else { *player_weapon_addr = &(context->special); }
}

void	update_cooldowns(t_weapon *mainhand, t_weapon *shield, t_weapon *heal, t_weapon *special)
{
	mainhand->curr++;
	special->curr++;
	shield->curr++;
	heal->curr++;

	SDL_assert(mainhand->cooldown != 0);
	SDL_assert(special->cooldown != 0);
	SDL_assert(shield->cooldown != 0);
	SDL_assert(heal->cooldown != 0);

	/* If (curr) is equal to (cooldown + 1) undo the (curr++) */
	mainhand->curr -= (mainhand->curr / (mainhand->cooldown + 1));
	special->curr -= (special->curr / (special->cooldown + 1));
	shield->curr -= (shield->curr / (shield->cooldown + 1));
	heal->curr -= (heal->curr / (heal->cooldown + 1));

	mainhand->cooldown_sprite._dst.w = 48 - lerp32((double)(mainhand->curr) / (mainhand->cooldown), 0, 48);
	special->cooldown_sprite._dst.w = 48 - lerp32((double)(special->curr) / (special->cooldown), 0, 48);
	shield->cooldown_sprite._dst.w = 48 - lerp32((double)(shield->curr) / (shield->cooldown), 0, 48);
	heal->cooldown_sprite._dst.w = 48 - lerp32((double)(heal->curr) / (heal->cooldown), 0, 48);

	SDLX_RenderQueue_Add(NULL, &(mainhand->cooldown_sprite));
	SDLX_RenderQueue_Add(NULL, &(special->cooldown_sprite));
	SDLX_RenderQueue_Add(NULL, &(shield->cooldown_sprite));
	SDLX_RenderQueue_Add(NULL, &(heal->cooldown_sprite));
}