#include "gbafe-chax.h"

extern const u16 CombatArtIcon_DebuffLance[], CombatArtIcon_AtkLance[], CombatArtIcon_MagLance[], CombatArtIcon_CritLance[];

// =================================================
//                      Lance
// =================================================

const struct CombatArtInfo CAInfo_TempestLance = {
	
	.msg_name = ENUM_msg_CAN_TempestLance,
	.msg_desc = ENUM_msg_CAD_TempestLance,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 5,
	.mt = 8,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
};


const struct CombatArtInfo CAInfo_Knightkneeler = {
	
	.msg_name = ENUM_msg_CAN_Knightkneeler,
	.msg_desc = ENUM_msg_CAD_Knightkneeler,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_ride = 1,
	.cost = 4,
	.mt = 5,
	.hit = 15,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkLance,
};


const struct CombatArtInfo CAInfo_ShatterSlash = {
	
	.msg_name = ENUM_msg_CAN_ShatterSlash,
	.msg_desc = ENUM_msg_CAD_ShatterSlash,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.debuff_def = 1,
	.cost = 3,
	.mt = 4,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_DebuffLance,
};


const struct CombatArtInfo CAInfo_MonsterPiercer = {
	
	.msg_name = ENUM_msg_CAN_MonsterPiercer,
	.msg_desc = ENUM_msg_CAD_MonsterPiercer,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_monster = 1,
	.cost = 4,
	.mt = 7,
	.hit = 0,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkLance,
};


const struct CombatArtInfo CAInfo_HitAndRun = {
	
	.msg_name = ENUM_msg_CAN_HitAndRun,
	.msg_desc = ENUM_msg_CAD_HitAndRun,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 4,
	.mt = 4,
	.hit = 10,
	.avo = 0,
	.crit = 20,
	.range_bouns = 0,
};


const struct CombatArtInfo CAInfo_SwiftStrikes = {
	
	.msg_name = ENUM_msg_CAN_SwiftStrikes,
	.msg_desc = ENUM_msg_CAD_SwiftStrikes,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.double_attack = 1,
	.cost = 2,
	.mt = 2,
	.hit = 0,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkLance,
};


const struct CombatArtInfo CAInfo_FrozenLance = {
	
	.msg_name = ENUM_msg_CAN_FrozenLance,
	.msg_desc = ENUM_msg_CAD_FrozenLance,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 1,
	.atk_bonus = 1,
	.cost = 4,
	.mt = 3,
	.hit = 5,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
	.icon = CombatArtIcon_MagLance,
};


const struct CombatArtInfo CAInfo_GlowingEmber = {
	
	.msg_name = ENUM_msg_CAN_GlowingEmber,
	.msg_desc = ENUM_msg_CAD_GlowingEmber,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.atk_bonus = 1,
	.cost = 4,
	.mt = 2,
	.hit = 0,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkLance,
};


const struct CombatArtInfo CAInfo_Vengeance = {
	
	.msg_name = ENUM_msg_CAN_Vengeance,
	.msg_desc = ENUM_msg_CAD_Vengeance,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.atk_bonus = 1,
	.cost = 4,
	.mt = 2,
	.hit = 0,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkLance,
};


const struct CombatArtInfo CAInfo_LanceJab = {
	
	.msg_name = ENUM_msg_CAN_LanceJab,
	.msg_desc = ENUM_msg_CAD_LanceJab,
	.weapon_type = ITYPE_LANCE,
	.is_lengency = 0,
	.is_magic = 0,
	.atk_bonus = 1,
	.cost = 5,
	.mt = 3,
	.hit = 0,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkLance,
};