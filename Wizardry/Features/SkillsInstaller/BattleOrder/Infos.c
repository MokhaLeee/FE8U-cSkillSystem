#include "gbafe-chax.h"

// icons
extern const u16 SI_Vantage[], SI_VantageBat[], SI_Desperation[], SI_DesperationBat[], SI_QuickRiposte[];


const struct SkillInfo SkillInfo_Vantage = {
	
	.msg_desc = ENUM_msg_SD_Vantage,
	.msg_name = ENUM_msg_SN_Vantage,
	.icon = SI_Vantage,
	
};


const struct SkillInfo SkillInfo_VantageBat = {
	
	.msg_desc = ENUM_msg_SD_VantageBattalion,
	.msg_name = ENUM_msg_SN_VantageBattalion,
	.icon = SI_VantageBat,
	
};


const struct SkillInfo SkillInfo_Desperation = {
	
	.msg_desc = ENUM_msg_SD_Desperation,
	.msg_name = ENUM_msg_SN_Desperation,
	.icon = SI_Desperation,
	
};


const struct SkillInfo SkillInfo_DesperationBat = {
	
	.msg_desc = ENUM_msg_SD_DesperationBattalion,
	.msg_name = ENUM_msg_SN_DesperationBattalion,
	.icon = SI_DesperationBat,
	
};


const struct SkillInfo SkillInfo_QuickRiposte = {
	
	.msg_desc = ENUM_msg_SD_QuickRiposte,
	.msg_name = ENUM_msg_SN_QuickRiposte,
	.icon = SI_QuickRiposte,
	
};