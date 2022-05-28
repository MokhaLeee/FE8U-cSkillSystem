#include "gbafe-chax.h"

extern const u16 CombatArtIcon_DebuffAxe[], CombatArtIcon_AtkAxe[], CombatArtIcon_MagAxe[], CombatArtIcon_CritAxe[];

const struct CombatArtInfo CAInfo_Smash = {
	
	.msg_name = ENUM_msg_CAN_Smash,
	.msg_desc = ENUM_msg_CAD_Smash,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 5,
	.mt = 3,
	.hit = 20,
	.avo = 0,
	.crit = 20,
	.range_bouns = 0,
	.icon = CombatArtIcon_CritAxe,
};


const struct CombatArtInfo CAInfo_HelmSplitter = {
	
	.msg_name = ENUM_msg_CAN_HelmSplitter,
	.msg_desc = ENUM_msg_CAD_HelmSplitter,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_heavy = 1,
	.cost = 5,
	.mt = 7,
	.hit = 0,
	.avo = 0,
	.crit = 5,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkAxe,
};


const struct CombatArtInfo CAInfo_MonsterBreaker = {
	
	.msg_name = ENUM_msg_CAN_MonsterBreaker,
	.msg_desc = ENUM_msg_CAD_MonsterBreaker,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_monster = 1,
	.cost = 5,
	.mt = 9,
	.hit = 0,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkAxe,
};


const struct CombatArtInfo CAInfo_FocusedStrike = {
	
	.msg_name = ENUM_msg_CAN_FocusedStrike,
	.msg_desc = ENUM_msg_CAD_FocusedStrike,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 3,
	.mt = 0,
	.hit = 30,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkAxe,
};


const struct CombatArtInfo CAInfo_WildAbandon = {
	
	.msg_name = ENUM_msg_CAN_WildAbandon,
	.msg_desc = ENUM_msg_CAD_WildAbandon,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 5,
	.mt = 10,
	.hit = -30,
	.avo = 0,
	.crit = 30,
	.range_bouns = 0,
	.icon = CombatArtIcon_CritAxe,
};


const struct CombatArtInfo CAInfo_Spike = {
	
	.msg_name = ENUM_msg_CAN_Spike,
	.msg_desc = ENUM_msg_CAD_Spike,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 5,
	.mt = 5,
	.hit = 15,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
};


const struct CombatArtInfo CAInfo_DiamondAxe = {
	
	.msg_name = ENUM_msg_CAN_DiamondAxe,
	.msg_desc = ENUM_msg_CAD_DiamondAxe,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 7,
	.mt = 14,
	.hit = -20,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkAxe,
};


const struct CombatArtInfo CAInfo_LightningAxe = {
	
	.msg_name = ENUM_msg_CAN_LightningAxe,
	.msg_desc = ENUM_msg_CAD_LightningAxe,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.atk_bonus = 1,
	.is_magic = 1,
	.cost = 3,
	.mt = 4,
	.hit = 0,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_MagAxe,
};


const struct CombatArtInfo CAInfo_ArmoredStrike = {
	
	.msg_name = ENUM_msg_CAN_ArmoredStrike,
	.msg_desc = ENUM_msg_CAD_ArmoredStrike,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.atk_bonus = 1,
	.cost = 4,
	.mt = 3,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkAxe,
};


const struct CombatArtInfo CAInfo_WarMasterStrike = {
	
	.msg_name = ENUM_msg_CAN_WarMasterStrike,
	.msg_desc = ENUM_msg_CAD_WarMasterStrike,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_all = 1,
	.cost = 5,
	.mt = 3,
	.hit = 30,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkAxe,
};


const struct CombatArtInfo CAInfo_FlickeringFlower = {
	
	.msg_name = ENUM_msg_CAN_FlickeringFlower,
	.msg_desc = ENUM_msg_CAD_FlickeringFlower,
	.weapon_type = ITYPE_AXE,
	.is_lengency = 0,
	.is_magic = 0,
	.is_gravity = 1,
	.cost = 3,
	.mt = 10,
	.hit = 10,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_DebuffAxe,
};


