/***************************************************************************
 * FILENAME:    scenes.h
 * DESCRIPTION: Header file with all the scenes in the game.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 26Jun2021
***************************************************************************/

#ifndef SCENES_H
# define SCENES_H

#include "main_structs.h"
#include "waves.h"

void	*main_menu_init(t_context *context, void *vp_scene);
void	*main_menu_close(t_context *context, void *vp_scene);
void	*main_menu_update(t_context *context, void *vp_scene);

void	*level_select_init(t_context *context, void *vp_scene);
void	*level_select_close(t_context *context, void *vp_scene);
void	*level_select_update(t_context *context, void *vp_scene);

void	*loot_level_init(t_context *context, SDL_UNUSED void *vp_scene);
void	*loot_level_close(t_context *context, SDL_UNUSED void *vp_scene);
void	*loot_level_update(t_context *context, SDL_UNUSED void *vp_scene);

void	*death_level_init(t_context *context, void *vp_scene);
void	*death_level_close(t_context *context, void *vp_scene);
void	*death_level_update(t_context *context, void *vp_scene);

void	*inventory_init(t_context *context, void *vp_scene);
void	*inventory_close(t_context *context, void *vp_scene);
void	*inventory_update(t_context *context, void *vp_scene);

t_level	*level_init(t_context *context, SDL_UNUSED void *vp_scene);

t_wave	level_01(void);
void	*level_01_init(t_context *context, void *vp_scene);
t_wave	level_02(void);
void	*level_02_init(t_context *context, void *vp_scene);
t_wave	level_03(void);
void	*level_03_init(t_context *context, void *vp_scene);
t_wave	level_04(void);
void	*level_04_init(t_context *context, void *vp_scene);
t_wave	level_05(void);
void	*level_05_init(t_context *context, void *vp_scene);
t_wave	level_06(void);
void	*level_06_init(t_context *context, void *vp_scene);
t_wave	level_07(void);
void	*level_07_init(t_context *context, void *vp_scene);
t_wave	level_08(void);
void	*level_08_init(t_context *context, void *vp_scene);
t_wave	level_09(void);
void	*level_09_init(t_context *context, void *vp_scene);
t_wave	level_10(void);
void	*level_10_init(t_context *context, void *vp_scene);
t_wave	level_11(void);
void	*level_11_init(t_context *context, void *vp_scene);
t_wave	level_12(void);
void	*level_12_init(t_context *context, void *vp_scene);
t_wave	level_13(void);
void	*level_13_init(t_context *context, void *vp_scene);
t_wave	level_14(void);
void	*level_14_init(t_context *context, void *vp_scene);
t_wave	level_15(void);
void	*level_15_init(t_context *context, void *vp_scene);
t_wave	level_16(void);
void	*level_16_init(t_context *context, void *vp_scene);
t_wave	level_17(void);
void	*level_17_init(t_context *context, void *vp_scene);
t_wave	level_18(void);
void	*level_18_init(t_context *context, void *vp_scene);
t_wave	level_19(void);
void	*level_19_init(t_context *context, void *vp_scene);
t_wave	level_20(void);
void	*level_20_init(t_context *context, void *vp_scene);
t_wave	level_21(void);
void	*level_21_init(t_context *context, void *vp_scene);
t_wave	level_22(void);
void	*level_22_init(t_context *context, void *vp_scene);
t_wave	level_23(void);
void	*level_23_init(t_context *context, void *vp_scene);
t_wave	level_24(void);
void	*level_24_init(t_context *context, void *vp_scene);
t_wave	level_25(void);
void	*level_25_init(t_context *context, void *vp_scene);

void	*level_close(t_context *context, void *vp_scene);
void	*level_update(t_context *context, void *vp_scene);


#endif