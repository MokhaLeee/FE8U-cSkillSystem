#include "gbafe-chax.h"


// =================================================
//                      Sword
// =================================================

static const struct CombatArtInfo CAInfo_WrathStrike = {
	
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


static const struct CombatArtInfo CAInfo_Grounder = {
	
	.msg_name = ENUM_msg_CAN_Grounder,
	.msg_desc = ENUM_msg_CAD_Grounder,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 4,
	.mt = 3,
	.hit = 20,
	.avo = 0,
	.crit = 5,
	.range_bouns = 0,
};


static const struct CombatArtInfo CAInfo_BaneOfMonsters = {
	
	.msg_name = ENUM_msg_CAN_BaneOfMonsters,
	.msg_desc = ENUM_msg_CAD_BaneOfMonsters,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_dragon = 1,
	.cost = 4,
	.mt = 6,
	.hit = 0,
	.avo = 0,
	.crit = 10,
	.range_bouns = 0,
};


static const struct CombatArtInfo CAInfo_Assassinate = {
	
	.msg_name = ENUM_msg_CAN_Assassinate,
	.msg_desc = ENUM_msg_CAD_Assassinate,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_dragon = 0,
	.cost = 4,
	.mt = 0,
	.hit = 15,
	.avo = 15,
	.crit = 10,
	.range_bouns = 0,
};








// =================================================
//                      Lance
// =================================================

static const struct CombatArtInfo CAInfo_TempestLance = {
	
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


static const struct CombatArtInfo CAInfo_Knightkneeler = {
	
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
};




// =================================================
//                       Axe
// =================================================




// =================================================
//                       Bow
// =================================================

static const struct CombatArtInfo CAInfo_CurvedShot = {
	
	.msg_name = ENUM_msg_CAN_CurvedShot,
	.msg_desc = ENUM_msg_CAD_CurvedShot,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_dragon = 1,
	.cost = 3,
	.mt = 1,
	.hit = 30,
	.avo = 0,
	.crit = 0,
	.range_bouns = 1,
};


static const struct CombatArtInfo CAInfo_HeavyDraw = {
	
	.msg_name = ENUM_msg_CAN_HeavyDraw,
	.msg_desc = ENUM_msg_CAD_HeavyDraw,
	.weapon_type = ITYPE_BOW,
	.is_lengency = 0,
	.is_magic = 0,
	.eff_dragon = 1,
	.cost = 5,
	.mt = 8,
	.hit = 10,
	.avo = 0,
	.crit = 0,
	.range_bouns = 0,
};



// =================================================
//                       Fist
// =================================================


// =================================================
//                 Info pointer table
// =================================================

struct CombatArtInfo const* const CombatArtInfoTable[0x100] = {
	
	// sword
	[CA_WrathStrike] = &CAInfo_WrathStrike,
	[CA_Grounder] = &CAInfo_Grounder,
	[CA_BaneOfMonsters] = &CAInfo_BaneOfMonsters,
	[CA_Assassinate] = &CAInfo_Assassinate,
	
	
	// lance
	[CA_TempestLance] = &CAInfo_TempestLance,
	[CA_Knightkneeler] = &CAInfo_Knightkneeler,
	
	
	// Axe
	
	
	
	// Bow
	[CA_CurvedShot] = &CAInfo_CurvedShot,
	[CA_HeavyDraw] = &CAInfo_HeavyDraw,
	
	
	// Fist
	
	
	
};

