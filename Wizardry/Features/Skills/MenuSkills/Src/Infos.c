#include "gbafe-chax.h"

// icons
extern const u16 SI_Dance[], SI_LockTouch[], SI_Summon[], SI_Supply[], SI_Steal[];


const struct SkillInfo SkillInfo_Dance = {
	
	.msg_desc = ENUM_msg_SD_Dance,
	.msg_name = ENUM_msg_SN_Dance,
	.icon = SI_Dance,
};


const struct SkillInfo SkillInfo_LockTouch = {
	
	.msg_desc = ENUM_msg_SD_LockTouch,
	.msg_name = ENUM_msg_SN_LockTouch,
	.icon = SI_LockTouch,
};


const struct SkillInfo SkillInfo_Summon = {
	
	.msg_desc = ENUM_msg_SD_Summon,
	.msg_name = ENUM_msg_SN_Summon,
	.icon = SI_Summon,
};


const struct SkillInfo SkillInfo_Supply = {
	
	.msg_desc = ENUM_msg_SD_Supply,
	.msg_name = ENUM_msg_SN_Supply,
	.icon = SI_Supply,
};


const struct SkillInfo SkillInfo_Steal = {
	
	.msg_desc = ENUM_msg_SD_Steal,
	.msg_name = ENUM_msg_SN_Steal,
	.icon = SI_Steal,
};
