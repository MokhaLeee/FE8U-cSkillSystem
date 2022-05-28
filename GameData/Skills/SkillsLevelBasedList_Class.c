#include "gbafe-chax.h"

const struct LevelBasedSkillList_t LevelSkillSword_ClassList[0x100] = {
	[CLASS_FALCON_KNIGHT] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = 0,
		.D[1] = 0,
		.C[0] = SID_AvoidSword,
		.C[1] = 0,
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = 0,
		.S[0] = 0,
		.S[1] = 0,
	},
}; 
const struct LevelBasedSkillList_t LevelSkillLance_ClassList[0x100] = {0}; 
const struct LevelBasedSkillList_t LevelSkillAxe_ClassList[0x100] = {0}; 
const struct LevelBasedSkillList_t LevelSkillBow_ClassList[0x100] = {0}; 
const struct LevelBasedSkillList_t LevelSkillBMag_ClassList[0x100] = {0}; 
const struct LevelBasedSkillList_t LevelSkillWMag_ClassList[0x100] = {0}; 

const struct LevelBasedSkillList_t LevelSkillRide_ClassList[0x100] = {
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

const struct LevelBasedSkillList_t LevelSkillFly_ClassList[0x100] = {
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

const struct LevelBasedSkillList_t LevelSkillHeavy_ClassList[0x100] = {
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