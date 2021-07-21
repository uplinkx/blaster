/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 02:38:32 by home              #+#    #+#             */
/*   Updated: 2021/05/21 00:54:05 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "SDL2/SDL_image.h"

# include "SDLX/SDLX.h"

# include "main_structs.h"
# include "main_enums.h"
# include "entity.h"
# include "scenes.h"
# include "waves.h"

# define ASSETS "assets/"

//PLAY WINDOW is {304x352}
# define PLAY_WIDTH (WIN_WIDTH / DISPLAY_SCALE)
# define BOTTOM_UI (16 * 7)
# define PLAY_HEIGHT ((WIN_HEIGHT / DISPLAY_SCALE) - BOTTOM_UI)

# define MID_PLAY_WIDTH (PLAY_WIDTH / 2)
# define MID_PLAY_HEIGHT (PLAY_HEIGHT / 2)

/*
** Sprite Handlers
*/

int		fetch_chest_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_coin_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_ui_sprite(SDLX_Sprite_Data **dst, int sprite_id);
int		fetch_level_select_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_pause_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_loot_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_hp_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_heal_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_whirl_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_lunge_sprite(SDLX_Sprite_Data **dst, int no);
int		fetch_inventory_sprite(SDLX_Sprite_Data **dst, int no);

/*
** Attack/Projectile Functions
*/

void	projectile_update(t_attacks *queue);
void	projectile_queue(t_attacks *attacks);
void	projectile_add(t_attacks *dst, t_bullet src);

void	unequip_weapon(t_weapon *dst);
void	load_weapons(t_context *context, t_weapon **player_weapon_addr, SDLX_button *mainhand, SDLX_button *shield, SDLX_button *heal, SDLX_button *special);
void	update_cooldowns(t_weapon *mainhand, t_weapon *shield, t_weapon *heal, t_weapon *special);

void	crosshair_init(SDLX_Sprite *crosshair);
void	update_crosshair(SDLX_Sprite *crosshair);

/*
** Button Functions
*/

void	*button_trigger_scene_switch(SDLX_button *self, void *meta, SDL_UNUSED size_t length);
void	*button_pause(SDLX_button *self, void *vp_context, SDL_UNUSED size_t length);
void	*button_resume(SDLX_button *self, void *pause_addr, SDL_UNUSED size_t length);

void	*button_chest(SDLX_button *self, SDL_UNUSED void *vp_context, SDL_UNUSED size_t length);
void	*button_chest_update(SDLX_button *self, SDL_UNUSED void *vp_context, SDL_UNUSED size_t length);

void	*button_carousel_weapon(SDLX_button *self, SDL_UNUSED void *addr, SDL_UNUSED size_t length);
void	*button_equip_weapon(SDLX_button *self, SDL_UNUSED void *addr, SDL_UNUSED size_t length);
void	*button_unequip_weapon(SDLX_button *self, SDL_UNUSED void *addr, SDL_UNUSED size_t length);

void	ability_button_init(SDLX_button *dst, t_weapon **player_equip_addr, t_weapon *to);

void	*new_scene(size_t size, t_context *context, char *background_path, t_scene_fn close, t_scene_fn update);
void	end_scene(t_context *context, SDLX_button *pause);

/*
** Wave Functions
*/

t_enemy	*spawn_enemy_addr(t_enemy_m *manager);
void	init_enemy_array(t_enemy_m *manager);
void	iter_enemies(t_enemy_m *enemies);

SDL_bool	wave_method(t_wave *wave, t_enemy_m *enemy_man, t_attacks *projectiles);

/*
** Misc. Functions
*/

uint32_t	lerp32(double percent, uint32_t start, uint32_t end);
double		ptoa(int x, int y);

SDLX_iMap	*blaster_key_map(size_t *size);

/*
** UI Functions
*/

void	pause_menu_init(t_pmenu *menu, void *pause_addr, void *pbackground, void *context, void *restart_fn);
void	update_pause_menu(t_pmenu *menu, SDL_Texture *pbackground);
void	level_ui_init(SDLX_button *pause, SDLX_Sprite *bottom);

#endif

