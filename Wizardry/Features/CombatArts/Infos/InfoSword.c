#include "gbafe-chax.h"

extern const u16 CombatArtIcon_DebuffSword[], CombatArtIcon_AtkSword[], CombatArtIcon_MagSword[], CombatArtIcon_CritSword[];

// =================================================
//                      Sword
// =================================================

const struct CombatArtInfo CAInfo_WrathStrike = {
	
	.msg_name = ENUM_msg_CAN_WrathStrike,
	.msg_desc = ENUM_msg_CAD_WrathStrike,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 3,
	.mt = 5,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
};


const struct CombatArtInfo CAInfo_Grounder = {
	
	.msg_name = ENUM_msg_CAN_Grounder,
	.msg_desc = ENUM_msg_CAD_Grounder,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 4,
	.mt = 5,
	.hit = 20,
	.avo = 0,
	.crit = 5,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkSword,
};


const struct CombatArtInfo CAInfo_Soulblade = {
	
	.msg_name = ENUM_msg_CAN_Soulblade,
	.msg_desc = ENUM_msg_CAD_Soulblade,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.atk_bonus = 1,
	.is_magic = 1,
	.eff_monster = 0,
	.cost = 4,
	.mt = 2,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_MagSword,
};


const struct CombatArtInfo CAInfo_BaneOfMonsters = {
	
	.msg_name = ENUM_msg_CAN_BaneOfMonsters,
	.msg_desc = ENUM_msg_CAD_BaneOfMonsters,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_monster = 1,
	.cost = 4,
	.mt = 6,
	.hit = 0,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkSword,
};


const struct CombatArtInfo CAInfo_Sunder = {
	
	.msg_name = ENUM_msg_CAN_Sunder,
	.msg_desc = ENUM_msg_CAD_Sunder,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_monster = 0,
	.cost = 3,
	.mt = 4,
	.hit = 0,
	.avo = 0,
	.crit = 15,
	.range_bouns = 0,
	.icon = CombatArtIcon_CritSword,
};



const struct CombatArtInfo CAInfo_HazeSlice = {
	
	.msg_name = ENUM_msg_CAN_HazeSlice,
	.msg_desc = ENUM_msg_CAD_HazeSlice,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_monster = 0,
	.cost = 5,
	.mt = 2,
	.hit = 0,
	.avo = 30,
	.crit = 0,
	.range_bouns = 0,
};


const struct CombatArtInfo CAInfo_Hexblade = {
	
	.msg_name = ENUM_msg_CAN_Hexblade,
	.msg_desc = ENUM_msg_CAD_Hexblade,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 1,
	.eff_monster = 0,
	.cost = 3,
	.mt = 7,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_MagSword,
};


const struct CombatArtInfo CAInfo_FinesseBlade = {
	
	.msg_name = ENUM_msg_CAN_FinesseBlade,
	.msg_desc = ENUM_msg_CAD_FinesseBlade,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.atk_bonus = 1,
	.is_magic = 0,
	.eff_monster = 0,
	.cost = 4,
	.mt = 2,
	.hit = 0,
	.avo = 10,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkSword,
};


const struct CombatArtInfo CAInfo_Windsweep = {
	
	.msg_name = ENUM_msg_CAN_Windsweep,
	.msg_desc = ENUM_msg_CAD_Windsweep,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.atk_bonus = 0,
	.is_magic = 0,
	.eff_monster = 0,
	.special_eff = 1,
	.cost = 5,
	.mt = 3,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
};


const struct CombatArtInfo CAInfo_SwordDance = {
	
	.msg_name = ENUM_msg_CAN_SwordDance,
	.msg_desc = ENUM_msg_CAD_SwordDance,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.atk_bonus = 1,
	.is_magic = 0,
	.eff_monster = 0,
	.cost = 2,
	.mt = 1,
	.hit = 0,
	.avo = 20,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkSword,
};



const struct CombatArtInfo CAInfo_Assassinate = {
	
	.msg_name = ENUM_msg_CAN_Assassinate,
	.msg_desc = ENUM_msg_CAD_Assassinate,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.atk_bonus = 1,
	.is_magic = 0,
	.eff_dragon = 0,
	.cost = 4,
	.mt = 0,
	.hit = 15,
	.avo = 10,
	.crit = 15,
	.range_bouns = 0,
	.icon = CombatArtIcon_CritSword,
};


const struct CombatArtInfo CAInfo_Subdue = {
	
	.msg_name = ENUM_msg_CAN_Subdue,
	.msg_desc = ENUM_msg_CAD_Subdue,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.atk_bonus = 0,
	.is_magic = 0,
	.eff_dragon = 0,
	.special_eff = 1,
	.cost = 3,
	.mt = 0,
	.hit = 20,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	
};


const struct CombatArtInfo CAInfo_FoudroyantStrike = {
	
	.msg_name = ENUM_msg_CAN_FoudroyantStrike,
	.msg_desc = ENUM_msg_CAD_FoudroyantStrike,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.atk_bonus = 0,
	.is_magic = 0,
	.eff_heavy = 1,
	.eff_dragon = 0,
	.special_eff = 0,
	.cost = 3,
	.mt = 6,
	.hit = 30,
	.avo = 0,
	.crit = 30,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkSword,
};


const struct CombatArtInfo CAInfo_SublimeHeaven = {
	
	.msg_name = ENUM_msg_CAN_SublimeHeaven,
	.msg_desc = ENUM_msg_CAD_SublimeHeaven,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 1,
	.atk_bonus = 1,
	.is_magic = 0,
	.eff_dragon = 1,
	.cost = 3,
	.mt = 10,
	.hit = 10,
	.avo = 0,
	.crit = 20,
	.range_bouns = 1,
	.icon = CombatArtIcon_AtkSword,
};


const struct CombatArtInfo CAInfo_RupturedHeaven = {
	
	.msg_name = ENUM_msg_CAN_RupturedHeaven,
	.msg_desc = ENUM_msg_CAD_RupturedHeaven,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 1,
	.atk_bonus = 1,
	.is_magic = 0,
	.eff_dragon = 1,
	.cost = 3,
	.mt = 7,
	.hit = 10,
	.avo = 0,
	.crit = 10,
	.range_bouns = 1,
	.icon = CombatArtIcon_AtkSword,
};


const struct CombatArtInfo CAInfo_HeavensFall = {
	
	.msg_name = ENUM_msg_CAN_HeavensFall,
	.msg_desc = ENUM_msg_CAD_HeavensFall,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 1,
	.atk_bonus = 1,
	.is_magic = 0,
	.eff_dragon = 1,
	.cost = 3,
	.mt = 10,
	.hit = 10,
	.avo = 0,
	.crit = 10,
	.range_bouns = 1,
	.icon = CombatArtIcon_AtkSword,
};
