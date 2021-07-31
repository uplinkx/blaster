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
void		empty_weapon_factory(SDL_UNUSED t_bullet *loc, SDL_UNUSED SDL_Point spawn, SDL_UNUSED double angle, SDL_UNUSED void *meta) { return ; }

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

void	load_weapon_default_values(t_weapon *weapon, SDL_Rect cooldown_loc)
{
	/* The top two have to be reset because they may contain values
	from the previous level since they are level persistent */
	weapon->meta_int = 0;
	weapon->curr = weapon->cooldown;

	weapon->cooldown_sprite.dst = SDLX_NULL_SELF;
	weapon->cooldown_sprite.center = SDLX_NULL_SELF;

	weapon->cooldown_sprite._dst = cooldown_loc;
}

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
	}

	i = 0;
	ability_bar_width = 304 - ABILITY_LEFT_PADDING - ABILITY_LEFT_PADDING;
	ability_space = (ability_bar_width - (mainhand->sprite._dst.w * count)) / (count);
	while (i < count)
	{
		line[i]->sprite._dst.x = ABILITY_LEFT_PADDING + (i * (ability_space + 48)) + (ability_space / 2);
		line[i]->trigger_box = line[i]->sprite._dst;
		i++;
	}

	load_weapon_default_values(&(context->mainhand), mainhand->sprite._dst);
	load_weapon_default_values(&(context->special), special->sprite._dst);
	load_weapon_default_values(&(context->shield), shield->sprite._dst);
	load_weapon_default_values(&(context->heal), heal->sprite._dst);

	if (context->mainhand.isEnabled) { *player_weapon_addr = &(context->mainhand); }
	else if (context->shield.isEnabled) { *player_weapon_addr = &(context->shield); }
	else if (context->heal.isEnabled) { *player_weapon_addr = &(context->heal); }
	else { *player_weapon_addr = &(context->special); }
}

void	update_cooldown(t_weapon *weapon)
{
	weapon->curr++;

	SDL_assert(weapon->cooldown > 0);

	/* If (curr) is equal to (cooldown + 1) undo the (curr++) */
	weapon->curr -= (weapon->curr / (weapon->cooldown + 1));

	weapon->cooldown_sprite._dst.w = 48 - lerp32((double)(weapon->curr) / (weapon->cooldown), 0, 48);

	SDLX_RenderQueue_Add(NULL, &(weapon->cooldown_sprite));
}

void	update_cooldowns(t_weapon *mainhand, t_weapon *shield, t_weapon *heal, t_weapon *special)
{
	if (mainhand->isEnabled) { update_cooldown(mainhand); }
	if (shield->isEnabled) { update_cooldown(shield); }
	if (heal->isEnabled) { update_cooldown(heal); }
	if (special->isEnabled) { update_cooldown(special); }
}
