#include "gbafe-chax.h"

// icons
extern const u16 SI_CloseCounter[], SI_CounterAttack[];


const struct SkillInfo SkillInfo_CloseCounter = {
	
	.msg_desc = ENUM_msg_SD_CloseCounter,
	.msg_name = ENUM_msg_SN_CloseCounter,
	.icon = SI_CloseCounter,
	
};


const struct SkillInfo SkillInfo_CounterAttack = {
	
	.msg_desc = ENUM_msg_SD_CounterAttack,
	.msg_name = ENUM_msg_SN_CounterAttack,
	.icon = SI_CounterAttack,
	
};