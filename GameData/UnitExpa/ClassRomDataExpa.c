#include "gbafe-chax.h"

const struct ClassRomDataExpa ClassRomDataExpaTable[0x100] = {
	[CLASS_MAGE_F] = {
		.rank_ride = 0,
		.rank_fly = 0,
		.rank_heavy = 0,
		.RankExp = 8,
	},
	
	
	// 飞行
	[CLASS_PEGASUS_KNIGHT] = {
		.rank_fly = WPN_EXP_E,
	},
	[CLASS_WYVERN_RIDER] = {
		.rank_fly = WPN_EXP_E,
	},
	[CLASS_WYVERN_RIDER_F] = {
		.rank_fly = WPN_EXP_E,
	},
	
	[CLASS_FALCON_KNIGHT] = {
		.rank_fly = WPN_EXP_B,
	},
	[CLASS_WYVERN_LORD] = {
		.rank_fly = WPN_EXP_B,
	},
	[CLASS_WYVERN_LORD_F] = {
		.rank_fly = WPN_EXP_B,
	},
	[CLASS_WYVERN_KNIGHT] = {
		.rank_fly = WPN_EXP_B,
	},
	[CLASS_WYVERN_KNIGHT_F] = {
		.rank_fly = WPN_EXP_B,
	},
	
	
	// 骑士
	[CLASS_CAVALIER] = {
		.rank_ride = WPN_EXP_E,
	},
	[CLASS_CAVALIER_F] = {
		.rank_ride = WPN_EXP_E,
	},
	[CLASS_PALADIN] = {
		.rank_ride = WPN_EXP_B,
	},
	[CLASS_PALADIN_F] = {
		.rank_ride = WPN_EXP_B,
	},
	[CLASS_GREAT_KNIGHT] = {
		.rank_ride = WPN_EXP_C,
		.rank_heavy = WPN_EXP_C,
	},
	[CLASS_GREAT_KNIGHT_F] = {
		.rank_ride = WPN_EXP_C,
		.rank_heavy = WPN_EXP_C,
	},
	
	
	
	
	// 重装
	[CLASS_ARMOR_KNIGHT] = {
		.rank_heavy = WPN_EXP_E,
	},
	[CLASS_ARMOR_KNIGHT_F] = {
		.rank_heavy = WPN_EXP_E,
	},
	[CLASS_GENERAL] = {
		.rank_heavy = WPN_EXP_B,
	},
	[CLASS_GENERAL_F] = {
		.rank_heavy = WPN_EXP_B,
	},
};

