/***************************************************************************
 * FILENAME:    main_enums.h
 * DESCRIPTION: File with the enums used in blaster.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 16Jul2021
***************************************************************************/

#ifndef MAIN_ENUMS_H
# define MAIN_ENUMS_H

# define ABILITY_CHANGED (2)

enum	BLASTER_UI_SPRITES
{
	LOCK_NORM,
	LOCK_HOVER,
	BACK_NORM,
	BACK_HOVER,

	PLAY_NORM,
	PLAY_HOVER,
	CREDIT_NORM,
	CREDIT_HOVER,
	PAUSE_NORM,

	MMENU_NORM,
	MMENU_HOVER,
	MREDO_NORM,
	MREDO_HOVER,
	MPLAY_NORM,
	MPLAY_HOVER,
	MBACK,

	IMENU_NORM,
	IMENU_HOVER,
	IPREV_NORM,
	IPREV_HOVER,
	INEXT_NORM,
	INEXT_HOVER,
	IINFO_NORM,
	IINFO_HOVER,
	IBACK_NORM,
	IBACK_HOVER,

	LMENU_NORM,
	LMENU_HOVER,
	LREDO_NORM,
	LREDO_HOVER,
	LNEXT_NORM,
	LNEXT_HOVER,
	LINVT_NORM,
	LINVT_HOVER,
	LBACK,
	DBACK,

	ABILITY,
	ABILITY_SEL,

	EMPTY_UI,
};

enum	e_weapon_types
{
	B_NONE		= 0b00000,
	B_MAINHAND	= 0b00001,
	B_SHIELD	= 0b00010,
	B_HEAL		= 0b00100,
	B_SPECIAL	= 0b01000,
	B_HEART		= 0b10000,
};

enum	BLASTER_COLLISION_TYPES
{
	E_NONE,
	E_DEAD,
	BULLETS,
	WHIRLWIND,
	LUNGE,
	SLIMES,
	SLIMES_YELLOW,
	SLIMES_INV,
	PLAYER,
	HEAL,

	GOO,
	SPINE,
};

#endif