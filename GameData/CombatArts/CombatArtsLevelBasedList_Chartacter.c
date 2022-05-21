#include "gbafe-chax.h"

const struct LevelBasedSkillList_t LevelCASword_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = CA_WrathStrike,
		.D[1] = 0,
		.C[0] = CA_Grounder,
		.C[1] = CA_BaneOfMonsters,
		.B[0] = CA_Windsweep,
		.B[1] = CA_Subdue,
		.A[0] = CA_FoudroyantStrike,
		.A[1] = 0,
		.S[0] = CA_HeavensFall,
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
		.B[0] = 0,
		.B[1] = 0,
		.A[0] = CA_SwiftStrikes,
		.A[1] = 0,
		.S[0] = 0,
		.S[1] = 0,
	},
};
 
const struct LevelBasedSkillList_t LevelCAAxe_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = CA_Smash,
		.D[1] = 0,
		.C[0] = CA_HelmSplitter,
		.C[1] = CA_MonsterBreaker,
		.B[0] = CA_FocusedStrike,
		.B[1] = CA_DiamondAxe,
		.A[0] = CA_WarMasterStrike,
		.A[1] = 0,
		.S[0] = CA_FlickeringFlower,
		.S[1] = 0,
	},
};

const struct LevelBasedSkillList_t LevelCABow_CharList[0x100] = {
	[0] = {
		.E[0] = 0,
		.E[1] = 0,
		.D[0] = CA_CurvedShot,
		.D[1] = CA_BreakShot,
		.C[0] = CA_Encloser,
		.C[1] = CA_Deadeye,
		.B[0] = CA_BreakShot,
		.B[1] = CA_WaningShot,
		.A[0] = CA_EncloserPlus,
		.A[1] = CA_HuntersVolley,
		.S[0] = 0,
		.S[1] = 0,
	},
}; 
