#include "gbafe-chax.h"

// icons
extern const u16 SI_Canto[], SI_AlertStance[], SI_AlertStancePlus[];


const struct SkillInfo SkillInfo_Canto = {
	
	.msg_desc = ENUM_msg_SD_Canto,
	.msg_name = ENUM_msg_SN_Canto,
	.icon = SI_Canto,
	
};


const struct SkillInfo SkillInfo_AlertStance = {
	
	.msg_desc = ENUM_msg_SD_AlertStance,
	.msg_name = ENUM_msg_SN_AlertStance,
	.icon = SI_AlertStance,
	
};


const struct SkillInfo SkillInfo_AlertStancePlus = {
	
	.msg_desc = ENUM_msg_SD_AlertStancePlus,
	.msg_name = ENUM_msg_SN_AlertStancePlus,
	.icon = SI_AlertStancePlus,
	
};

