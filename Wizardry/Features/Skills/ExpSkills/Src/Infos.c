#include "gbafe-chax.h"

// icons
extern const u16 SI_Discipline[], SI_RoyalLineage[];


const struct SkillInfo SkillInfo_Discipline = {
	
	.msg_desc = ENUM_msg_SD_Discipline,
	// .msg_name = ENUM_msg_SN_Discipline,
	.icon = SI_Discipline,
	
};


const struct SkillInfo SkillInfo_RoyalLineage = {
	
	.msg_desc = ENUM_msg_SD_RoyalLineage,
	// .msg_name = ENUM_msg_SN_RoyalLineage,
	.icon = SI_RoyalLineage,
	
};