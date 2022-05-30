#include "gbafe-chax.h"

// icons
extern const u16 SI_Lethality[], SI_Crit[], SI_WatchfulEye[], SI_CritSword[], SI_CritAxe[], SI_CritLance[], SI_CritBow[], SI_CritBMag[], SI_CritWMag[], SI_FaireSword[], SI_FaireLance[], SI_FaireAxe[], SI_FaireBow[], SI_FaireBMag[], SI_Avoid[], SI_AvoidSword[], SI_DefiantCrit[], SI_DefiantAvoid[], SI_RuinedBlade[], SI_RuinedBladePlus[], SI_InfinityEdge[], SI_LunaAttack[];







const struct SkillInfo SkillInfo_Lethality = {
	
	.msg_desc = ENUM_msg_SD_Lethality,
	.msg_name = ENUM_msg_SN_Lethality,
	.icon = SI_Lethality,
	
};


const struct SkillInfo SkillInfo_Crit = {
	
	.msg_desc = ENUM_msg_SD_Crit,
	// .msg_name = ENUM_msg_SN_Crit,
	.icon = SI_Crit,
	
};


const struct SkillInfo SkillInfo_WatchfulEye = {
	
	.msg_desc = ENUM_msg_SD_WatchfulEye,
	// .msg_name = ENUM_msg_SN_WatchfulEye,
	.icon = SI_WatchfulEye,
	
};



// Crit
const struct SkillInfo SkillInfo_CritSword = {
	
	.msg_desc = ENUM_msg_SD_CritSword,
	// .msg_name = ENUM_msg_SN_CritSword,
	.icon = SI_CritSword,
	
};


const struct SkillInfo SkillInfo_CritAxe = {
	
	.msg_desc = ENUM_msg_SD_CritAxe,
	// .msg_name = ENUM_msg_SN_CritAxe,
	.icon = SI_CritAxe,
	
};


const struct SkillInfo SkillInfo_CritLance = {
	
	.msg_desc = ENUM_msg_SD_CritLance,
	// .msg_name = ENUM_msg_SN_CritLance,
	.icon = SI_CritLance,
	
};


const struct SkillInfo SkillInfo_CritBow = {
	
	.msg_desc = ENUM_msg_SD_CritBow,
	// .msg_name = ENUM_msg_SN_CritBow,
	.icon = SI_CritBow,
	
};


const struct SkillInfo SkillInfo_CritBMag = {
	
	.msg_desc = ENUM_msg_SD_CritBMag,
	// .msg_name = ENUM_msg_SN_CritBMag,
	.icon = SI_CritBMag,
	
};


const struct SkillInfo SkillInfo_CritWMag = {
	
	.msg_desc = ENUM_msg_SD_CritWMag,
	// .msg_name = ENUM_msg_SN_CritWMag,
	.icon = SI_CritWMag,
	
};











// Faire

const struct SkillInfo SkillInfo_FaireSword = {
	
	.msg_desc = ENUM_msg_SD_FaireSword,
	// .msg_name = ENUM_msg_SN_FaireSword,
	.icon = SI_FaireSword,
	
};

const struct SkillInfo SkillInfo_FaireLance = {
	
	.msg_desc = ENUM_msg_SD_FaireLance,
	// .msg_name = ENUM_msg_SN_FaireLance,
	.icon = SI_FaireLance,
	
};

const struct SkillInfo SkillInfo_FaireAxe = {
	
	.msg_desc = ENUM_msg_SD_FaireAxe,
	// .msg_name = ENUM_msg_SN_FaireAxe,
	.icon = SI_FaireAxe,
	
};

const struct SkillInfo SkillInfo_FaireBow = {
	
	.msg_desc = ENUM_msg_SD_FaireBow,
	// .msg_name = ENUM_msg_SN_FaireBow,
	.icon = SI_FaireBow,
	
};

const struct SkillInfo SkillInfo_FaireBMag = {
	
	.msg_desc = ENUM_msg_SD_FaireBMag,
	// .msg_name = ENUM_msg_SN_FaireBMag,
	.icon = SI_FaireBMag,
	
};


// Avoid

const struct SkillInfo SkillInfo_Avoid = {
	
	.msg_desc = ENUM_msg_SD_Avoid,
	// .msg_name = ENUM_msg_SN_Avoid,
	.icon = SI_Avoid,
	
};

const struct SkillInfo SkillInfo_AvoidSword = {
	
	.msg_desc = ENUM_msg_SD_AvoidSword,
	// .msg_name = ENUM_msg_SN_AvoidSword,
	.icon = SI_AvoidSword,
	
};





// Defiant Skills

const struct SkillInfo SkillInfo_DefiantCrit = {
	
	.msg_desc = ENUM_msg_SD_DefiantCrit,
	// .msg_name = ENUM_msg_SN_DefiantCrit,
	.icon = SI_DefiantCrit,
	
};


const struct SkillInfo SkillInfo_DefiantAvoid = {
	
	.msg_desc = ENUM_msg_SD_DefiantAvoid,
	// .msg_name = ENUM_msg_SN_DefiantAvoid,
	.icon = SI_DefiantAvoid,
	
};




// 无尽 & 破败


const struct SkillInfo SkillInfo_RuinedBlade = {
	
	.msg_desc = ENUM_msg_SD_RuinedBlade,
	// .msg_name = ENUM_msg_SN_RuinedBlade,
	.icon = SI_RuinedBlade,
	
};


const struct SkillInfo SkillInfo_RuinedBladePlus = {
	
	.msg_desc = ENUM_msg_SD_RuinedBladePlus,
	// .msg_name = ENUM_msg_SN_RuinedBladePlus,
	.icon = SI_RuinedBladePlus,
	
};


const struct SkillInfo SkillInfo_InfinityEdge = {
	
	.msg_desc = ENUM_msg_SD_InfinityEdge,
	// .msg_name = ENUM_msg_SN_InfinityEdge,
	.icon = SI_InfinityEdge,
	
};

extern const u16 SI_SorceryBlade[];
const struct SkillInfo SkillInfo_SorceryBlade = {
	
	.msg_desc = ENUM_msg_SD_SorceryBlade,
	// .msg_name = ENUM_msg_SN_SorceryBlade,
	.icon = SI_SorceryBlade,
	
};


const struct SkillInfo SkillInfo_LunaAttack = {
	
	.msg_desc = ENUM_msg_SD_LunaAttack,
	.msg_name = ENUM_msg_SN_LunaAttack,
	.icon = SI_LunaAttack,
	
};


// 刚柔剑
extern const u16 SI_HeavyBlade[];
const struct SkillInfo SkillInfo_HeavyBlade = {
	
	.msg_desc = ENUM_msg_SD_HeavyBlade,
	// .msg_name = ENUM_msg_SN_HeavyBlade,
	.icon = SI_HeavyBlade,
	
};

extern const u16 SI_HeavyBladePlus[];
const struct SkillInfo SkillInfo_HeavyBladePlus = {
	
	.msg_desc = ENUM_msg_SD_HeavyBladePlus,
	// .msg_name = ENUM_msg_SN_HeavyBladePlus,
	.icon = SI_HeavyBladePlus,
	
};

extern const u16 SI_FlashingBlade[];
const struct SkillInfo SkillInfo_FlashingBlade = {
	
	.msg_desc = ENUM_msg_SD_FlashingBlade,
	// .msg_name = ENUM_msg_SN_FlashingBlade,
	.icon = SI_FlashingBlade,
	
};

extern const u16 SI_FlashingBladePlus[];
const struct SkillInfo SkillInfo_FlashingBladePlus = {
	
	.msg_desc = ENUM_msg_SD_FlashingBladePlus,
	// .msg_name = ENUM_msg_SN_FlashingBladePlus,
	.icon = SI_FlashingBladePlus,
	
};




