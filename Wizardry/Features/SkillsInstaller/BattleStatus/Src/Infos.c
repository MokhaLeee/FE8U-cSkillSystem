#include "gbafe-chax.h"

// icons
extern const u16 SI_Lethality[], SI_Crit[], SI_WatchfulEye[];


const struct SkillInfo SkillInfo_Lethality = {
	
	.msg_desc = ENUM_msg_SD_Lethality,
	.msg_name = ENUM_msg_SN_Lethality,
	.icon = SI_Lethality,
	
};


const struct SkillInfo SkillInfo_Crit = {
	
	.msg_desc = ENUM_msg_SD_Crit,
	.msg_name = ENUM_msg_SN_Crit,
	.icon = SI_Crit,
	
};


const struct SkillInfo SkillInfo_WatchfulEye = {
	
	.msg_desc = ENUM_msg_SD_WatchfulEye,
	.msg_name = ENUM_msg_SN_WatchfulEye,
	.icon = SI_WatchfulEye,
	
};