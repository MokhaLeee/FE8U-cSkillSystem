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
};


static const struct CombatArtInfo CAInfo_BaneOfMonsters = {
	
	.msg_name = ENUM_msg_CAN_BaneOfMonsters,
	.msg_desc = ENUM_msg_CAD_BaneOfMonsters,
	.weapon_type = ITYPE_SWORD,
	.is_lengency = 0,
	.is_magic = 0,
	.cost = 4,
	.mt = 6,
	.hit = 0,
	.avo = 0,
	.crit = 10,
};











// =================================================
//                 Info pointer table
// =================================================

const struct CombatArtInfo *CombatArtInfoTable[0x100] = {
	
	[CA_WrathStrike] = &CAInfo_WrathStrike,
	[CA_Grounder] = &CAInfo_Grounder,
	[CA_BaneOfMonsters] = &CAInfo_BaneOfMonsters,
};
