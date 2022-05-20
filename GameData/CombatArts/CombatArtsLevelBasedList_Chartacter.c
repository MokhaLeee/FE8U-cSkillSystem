#include "gbafe-chax.h"

const struct LevelBasedSkillList_t LevelCASword_CharList[0x100] = {
	[0] = {
		.E[0] = CA_WrathStrike,
		.E[1] = CA_Subdue,
		.D[0] = CA_Grounder,
		.D[1] = CA_Windsweep,
		.C[0] = CA_HazeSlice,
		.C[1] = CA_FinesseBlade,
		.B[0] = CA_FoudroyantStrike,
		.B[1] = 0,
		.A[0] = 0,
		.A[1] = 0,
		.S[0] = 0,
		.S[1] = 0,
	},
}; 

const struct LevelBasedSkillList_t LevelCALance_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = CA_TempestLance,
		.D[1] = CA_ShatterSlash,
		.C[0] = CA_Knightkneeler,
		.C[1] = CA_MonsterPiercer,
		.B[0] = CA_Vengeance,
		.B[1] = 0,
		.A[0] = CA_SwiftStrikes,
		.A[1] = 0,
		.S[0] = 0,
		.S[1] = 0,
	},
};
 
const struct LevelBasedSkillList_t LevelCAAxe_CharList[0x100] = {
	[0] = {
		.E[0] = CA_Smash,
		.E[1] = 0,
		.D[0] = CA_HelmSplitter,
		.D[1] = CA_DiamondAxe,
		.C[0] = CA_MonsterBreaker,
		.C[1] = 0,
		.B[0] = CA_LightningAxe,
		.B[1] = CA_ArmoredStrike,
		.A[0] = 0,
		.A[1] = CA_FlickeringFlower,
		.S[0] = CA_WarMasterStrike,
		.S[1] = 0,
	},
};

const struct LevelBasedSkillList_t LevelCABow_CharList[0x100] = {
	[0] = {
		.E[0] = CA_CurvedShot,
		.E[1] = CA_HeavyDraw,
		.D[0] = CA_WaningShot,
		.D[1] = CA_BreakShot,
		.C[0] = CA_WardArrow,
		.C[1] = 0,
		.B[0] = CA_Encloser,
		.B[1] = 0,
		.A[0] = 0,
		.A[1] = CA_HuntersVolley,
		.S[0] = CA_EncloserPlus,
		.S[1] = 0,
	},
}; 
