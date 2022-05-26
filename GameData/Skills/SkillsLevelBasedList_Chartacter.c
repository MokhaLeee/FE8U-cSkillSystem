#include "gbafe-chax.h"

const struct LevelBasedSkillList_t LevelSkillSword_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = 0,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = SID_CritSword,
		.A[1] = 0,
		.S[0] = SID_FaireSword,
		.S[1] = 0,
	},
}; 


const struct LevelBasedSkillList_t LevelSkillLance_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = 0,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = SID_CritLance,
		.A[1] = 0,
		.S[0] = SID_FaireLance,
		.S[1] = 0,
	},
	
};
const struct LevelBasedSkillList_t LevelSkillAxe_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = 0,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = SID_CritAxe,
		.A[1] = 0,
		.S[0] = SID_FaireAxe,
		.S[1] = 0,
	},
};

const struct LevelBasedSkillList_t LevelSkillBow_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = 0,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = SID_CritBow,
		.A[1] = SID_RangeBonusBow1,
		.S[0] = SID_FaireBow,
		.S[1] = 0,
	},
};
const struct LevelBasedSkillList_t LevelSkillBMag_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = 0,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = SID_CritBMag,
		.A[1] = SID_RangeBonusBMag1,
		.S[0] = SID_FaireBMag,
		.S[1] = 0,
	},
};
const struct LevelBasedSkillList_t LevelSkillWMag_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = SID_Renewal,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = SID_DefiantAvoid,
		.S[0] = 0,
		.S[1] = 0,
	},
}; 

const struct LevelBasedSkillList_t LevelSkillRide_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = 0,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = 0,
		.S[0] = 0,
		.S[1] = 0,
	},
};

const struct LevelBasedSkillList_t LevelSkillFly_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = 0,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = 0,
		.S[0] = 0,
		.S[1] = 0,
	},
};

const struct LevelBasedSkillList_t LevelSkillHeavy_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = 0,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = 0,
		.S[0] = 0,
		.S[1] = 0,
	},
};