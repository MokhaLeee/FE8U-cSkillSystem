#include "gbafe-chax.h"

extern const u8 SI_SwordLv1[], SI_SwordLv2[], SI_SwordLv3[], SI_SwordLv4[], SI_SwordLv5[];
extern const u8 SI_LanceLv1[], SI_LanceLv2[], SI_LanceLv3[], SI_LanceLv4[], SI_LanceLv5[];
extern const u8 SI_AxeLv1[], SI_AxeLv2[], SI_AxeLv3[], SI_AxeLv4[], SI_AxeLv5[];
extern const u8 SI_BowLv1[], SI_BowLv2[], SI_BowLv3[], SI_BowLv4[], SI_BowLv5[];

extern const u8 SI_BMagLv1[], SI_BMagLv2[], SI_BMagLv3[], SI_BMagLv4[], SI_BMagLv5[];
extern const u8 SI_WMagLv1[], SI_WMagLv2[], SI_WMagLv3[], SI_WMagLv4[], SI_WMagLv5[];

// Weapon Lv

const struct SkillInfo SkillInfo_SwordLv1 = {
	
	.msg_desc = ENUM_msg_SD_SwordLv1,
	// .msg_name = ENUM_msg_SN_SwordLv1,
	.icon = SI_SwordLv1,
	
};

const struct SkillInfo SkillInfo_SwordLv2 = {
	
	.msg_desc = ENUM_msg_SD_SwordLv2,
	// .msg_name = ENUM_msg_SN_SwordLv2,
	.icon = SI_SwordLv2,
	
};

const struct SkillInfo SkillInfo_SwordLv3 = {
	
	.msg_desc = ENUM_msg_SD_SwordLv3,
	// .msg_name = ENUM_msg_SN_SwordLv3,
	.icon = SI_SwordLv3,
	
};

const struct SkillInfo SkillInfo_SwordLv4 = {
	
	.msg_desc = ENUM_msg_SD_SwordLv4,
	// .msg_name = ENUM_msg_SN_SwordLv4,
	.icon = SI_SwordLv4,
	
};

const struct SkillInfo SkillInfo_SwordLv5 = {
	
	.msg_desc = ENUM_msg_SD_SwordLv5,
	// .msg_name = ENUM_msg_SN_SwordLv5,
	.icon = SI_SwordLv5,
	
};



const struct SkillInfo SkillInfo_LanceLv1 = {
	
	.msg_desc = ENUM_msg_SD_LanceLv1,
	// .msg_name = ENUM_msg_SN_LanceLv1,
	.icon = SI_LanceLv1,
	
};

const struct SkillInfo SkillInfo_LanceLv2 = {
	
	.msg_desc = ENUM_msg_SD_LanceLv2,
	// .msg_name = ENUM_msg_SN_LanceLv2,
	.icon = SI_LanceLv2,
	
};

const struct SkillInfo SkillInfo_LanceLv3 = {
	
	.msg_desc = ENUM_msg_SD_LanceLv3,
	// .msg_name = ENUM_msg_SN_LanceLv3,
	.icon = SI_LanceLv3,
	
};

const struct SkillInfo SkillInfo_LanceLv4 = {
	
	.msg_desc = ENUM_msg_SD_LanceLv4,
	// .msg_name = ENUM_msg_SN_LanceLv4,
	.icon = SI_LanceLv4,
	
};

const struct SkillInfo SkillInfo_LanceLv5 = {
	
	.msg_desc = ENUM_msg_SD_LanceLv5,
	// .msg_name = ENUM_msg_SN_LanceLv5,
	.icon = SI_LanceLv5,
	
};




const struct SkillInfo SkillInfo_AxeLv1 = {
	
	.msg_desc = ENUM_msg_SD_AxeLv1,
	// .msg_name = ENUM_msg_SN_AxeLv1,
	.icon = SI_AxeLv1,
	
};

const struct SkillInfo SkillInfo_AxeLv2 = {
	
	.msg_desc = ENUM_msg_SD_AxeLv2,
	// .msg_name = ENUM_msg_SN_AxeLv2,
	.icon = SI_AxeLv2,
	
};

const struct SkillInfo SkillInfo_AxeLv3 = {
	
	.msg_desc = ENUM_msg_SD_AxeLv3,
	// .msg_name = ENUM_msg_SN_AxeLv3,
	.icon = SI_AxeLv3,
	
};

const struct SkillInfo SkillInfo_AxeLv4 = {
	
	.msg_desc = ENUM_msg_SD_AxeLv4,
	// .msg_name = ENUM_msg_SN_AxeLv4,
	.icon = SI_AxeLv4,
	
};

const struct SkillInfo SkillInfo_AxeLv5 = {
	
	.msg_desc = ENUM_msg_SD_AxeLv5,
	// .msg_name = ENUM_msg_SN_AxeLv5,
	.icon = SI_AxeLv5,
	
};


const struct SkillInfo SkillInfo_BowLv1 = {
	
	.msg_desc = ENUM_msg_SD_BowLv1,
	// .msg_name = ENUM_msg_SN_BowLv1,
	.icon = SI_BowLv1,
	
};

const struct SkillInfo SkillInfo_BowLv2 = {
	
	.msg_desc = ENUM_msg_SD_BowLv2,
	// .msg_name = ENUM_msg_SN_BowLv2,
	.icon = SI_BowLv2,
	
};

const struct SkillInfo SkillInfo_BowLv3 = {
	
	.msg_desc = ENUM_msg_SD_BowLv3,
	// .msg_name = ENUM_msg_SN_BowLv3,
	.icon = SI_BowLv3,
	
};

const struct SkillInfo SkillInfo_BowLv4 = {
	
	.msg_desc = ENUM_msg_SD_BowLv4,
	// .msg_name = ENUM_msg_SN_BowLv4,
	.icon = SI_BowLv4,
	
};

const struct SkillInfo SkillInfo_BowLv5 = {
	
	.msg_desc = ENUM_msg_SD_BowLv5,
	// .msg_name = ENUM_msg_SN_BowLv5,
	.icon = SI_BowLv5,
	
};


const struct SkillInfo SkillInfo_BMagLv1 = {
	
	.msg_desc = ENUM_msg_SD_BMagLv1,
	// .msg_name = ENUM_msg_SN_BMagLv1,
	.icon = SI_BMagLv1,
	
};

const struct SkillInfo SkillInfo_BMagLv2 = {
	
	.msg_desc = ENUM_msg_SD_BMagLv2,
	// .msg_name = ENUM_msg_SN_BMagLv2,
	.icon = SI_BMagLv2,
	
};

const struct SkillInfo SkillInfo_BMagLv3 = {
	
	.msg_desc = ENUM_msg_SD_BMagLv3,
	// .msg_name = ENUM_msg_SN_BMagLv3,
	.icon = SI_BMagLv3,
	
};

const struct SkillInfo SkillInfo_BMagLv4 = {
	
	.msg_desc = ENUM_msg_SD_BMagLv4,
	// .msg_name = ENUM_msg_SN_BMagLv4,
	.icon = SI_BMagLv4,
	
};

const struct SkillInfo SkillInfo_BMagLv5 = {
	
	.msg_desc = ENUM_msg_SD_BMagLv5,
	// .msg_name = ENUM_msg_SN_BMagLv5,
	.icon = SI_BMagLv5,
	
};




const struct SkillInfo SkillInfo_WMagLv1 = {
	
	.msg_desc = ENUM_msg_SD_WMagLv1,
	// .msg_name = ENUM_msg_SN_WMagLv1,
	.icon = SI_WMagLv1,
	
};

const struct SkillInfo SkillInfo_WMagLv2 = {
	
	.msg_desc = ENUM_msg_SD_WMagLv2,
	// .msg_name = ENUM_msg_SN_WMagLv2,
	.icon = SI_WMagLv2,
	
};

const struct SkillInfo SkillInfo_WMagLv3 = {
	
	.msg_desc = ENUM_msg_SD_WMagLv3,
	// .msg_name = ENUM_msg_SN_WMagLv3,
	.icon = SI_WMagLv3,
	
};

const struct SkillInfo SkillInfo_WMagLv4 = {
	
	.msg_desc = ENUM_msg_SD_WMagLv4,
	// .msg_name = ENUM_msg_SN_WMagLv4,
	.icon = SI_WMagLv4,
	
};

const struct SkillInfo SkillInfo_WMagLv5 = {
	
	.msg_desc = ENUM_msg_SD_WMagLv5,
	// .msg_name = ENUM_msg_SN_WMagLv5,
	.icon = SI_WMagLv5,
	
};