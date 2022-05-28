#include "gbafe-chax.h"

// Icons
extern const u16 CombatArtIcon_DebuffBow[], CombatArtIcon_AtkBow[], CombatArtIcon_MagBow[], CombatArtIcon_CritBow[];

// =================================================
//                       Bow
// =================================================

const struct CombatArtInfo CAInfo_CurvedShot = {
	
	.msg_name = ENUM_msg_CAN_CurvedShot,
	.msg_desc = ENUM_msg_CAD_CurvedShot,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 3,
	.mt = 1,
	.hit = 30,
	.avo = 0,
	.crit = 0,
	.range_bouns = 1,
};


const struct CombatArtInfo CAInfo_Deadeye = {
	
	.msg_name = ENUM_msg_CAN_Deadeye,
	.msg_desc = ENUM_msg_CAD_Deadeye,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 5,
	.mt = 6,
	.hit = 0,
	.avo = 0,
	.crit = 0,
	.range_bouns = 3,
};

const struct CombatArtInfo CAInfo_Encloser = {
	
	.msg_name = ENUM_msg_CAN_Encloser,
	.msg_desc = ENUM_msg_CAD_Encloser,
	.icon = CombatArtIcon_DebuffBow,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 5,
	.mt = 0,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 1,
	.is_gravity = 1,
	.icon = CombatArtIcon_DebuffBow,
};

const struct CombatArtInfo CAInfo_HeavyDraw = {
	
	.msg_name = ENUM_msg_CAN_HeavyDraw,
	.msg_desc = ENUM_msg_CAD_HeavyDraw,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 5,
	.mt = 8,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
};


const struct CombatArtInfo CAInfo_MonsterBlast = {
	
	.msg_name = ENUM_msg_CAN_MonsterBlast,
	.msg_desc = ENUM_msg_CAD_MonsterBlast,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_monster = 1,
	.eff_fly = 1,
	.cost = 4,
	.mt = 5,
	.hit = 0,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
	.icon = CombatArtIcon_AtkBow,
};


const struct CombatArtInfo CAInfo_SchismShot = {
	
	.msg_name = ENUM_msg_CAN_SchismShot,
	.msg_desc = ENUM_msg_CAD_SchismShot,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 1,
	.eff_fly = 1,
	.cost = 3,
	.mt = 4,
	.hit = 15,
	.avo = 0,
	.crit = 0,
	.range_bouns = 1,
	.debuff_res = 1,
	.icon = CombatArtIcon_MagBow,
};


const struct CombatArtInfo CAInfo_BreakShot = {
	
	.msg_name = ENUM_msg_CAN_BreakShot,
	.msg_desc = ENUM_msg_CAD_BreakShot,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 3,
	.mt = 4,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 1,
	.debuff_def = 1,
	.icon = CombatArtIcon_DebuffBow,
};


const struct CombatArtInfo CAInfo_WaningShot = {
	
	.msg_name = ENUM_msg_CAN_WaningShot,
	.msg_desc = ENUM_msg_CAD_WaningShot,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 3,
	.mt = 4,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.debuff_atk = 1,
	.range_bouns = 1,
	.icon = CombatArtIcon_DebuffBow,
};


const struct CombatArtInfo CAInfo_PointBlankVolley = {
	
	.msg_name = ENUM_msg_CAN_PointBlankVolley,
	.msg_desc = ENUM_msg_CAD_PointBlankVolley,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 2,
	.mt = 1,
	.hit = 15,
	.avo = 0,
	.crit = 10,
	.double_attack = 1,
	.range_bouns = 0,
	.unnormal_range = 1,
	.icon = CombatArtIcon_AtkBow,
};


const struct CombatArtInfo CAInfo_WardArrow = {
	
	.msg_name = ENUM_msg_CAN_WardArrow,
	.msg_desc = ENUM_msg_CAD_WardArrow,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 3,
	.mt = 4,
	.hit = 15,
	.avo = 0,
	.crit = 0,
	.debuff_Silence = 1,
	.range_bouns = 1,
	.icon = CombatArtIcon_DebuffBow,
};


const struct CombatArtInfo CAInfo_HuntersVolley = {
	
	.msg_name = ENUM_msg_CAN_HuntersVolley,
	.msg_desc = ENUM_msg_CAD_HuntersVolley,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 2,
	.mt = 1,
	.hit = 15,
	.avo = 0,
	.crit = 10,
	.double_attack = 1,
	.range_bouns = 1,
	.icon = CombatArtIcon_AtkBow,
};
















const struct CombatArtInfo CAInfo_EncloserPlus = {
	
	.msg_name = ENUM_msg_CAN_EncloserPlus,
	.msg_desc = ENUM_msg_CAD_EncloserPlus,
	.icon = CombatArtIcon_DebuffBow,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 7,
	.mt = 0,
	.hit = 20,
	.avo = 0,
	.crit = 0,
	.range_bouns = 2,
	.is_gravity = 1,
	.AOE_Debuff = 1,
};



const struct CombatArtInfo CAInfo_WaningShotPlus = {
	
	.msg_name = ENUM_msg_CAN_WaningShotPlus,
	.msg_desc = ENUM_msg_CAD_WaningShotPlus,
	.icon = CombatArtIcon_DebuffBow,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 5,
	.mt = 0,
	.hit = 20,
	.avo = 0,
	.crit = 0,
	.range_bouns = 2,
	.debuff_atk = 1,
	.AOE_Debuff = 1,
};



const struct CombatArtInfo CAInfo_BreakShotPlus = {
	
	.msg_name = ENUM_msg_CAN_BreakShotPlus,
	.msg_desc = ENUM_msg_CAD_BreakShotPlus,
	.icon = CombatArtIcon_DebuffBow,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 5,
	.mt = 0,
	.hit = 20,
	.avo = 0,
	.crit = 0,
	.range_bouns = 2,
	.debuff_def = 1,
	.AOE_Debuff = 1,
};


const struct CombatArtInfo CAInfo_WardArrowPlus = {
	
	.msg_name = ENUM_msg_CAN_WardArrowPlus,
	.msg_desc = ENUM_msg_CAD_WardArrowPlus,
	.icon = CombatArtIcon_DebuffBow,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_fly = 1,
	.cost = 5,
	.mt = 0,
	.hit = 20,
	.avo = 0,
	.crit = 0,
	.range_bouns = 2,
	.debuff_Silence = 1,
	.AOE_Debuff = 1,
};



