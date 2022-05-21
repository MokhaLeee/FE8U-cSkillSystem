#include "gbafe-chax.h"

const struct LevelBasedSkillList_t LevelCASword_ClassList[0x100] = {
	
	[CLASS_ASSASSIN] = {
		.D[0] = CA_Assassinate,
	},
	
	[CLASS_ASSASSIN_F] = {
		.D[0] = CA_Assassinate,
	},
}; 

const struct LevelBasedSkillList_t LevelCALance_ClassList[0x100] = {0}; 
const struct LevelBasedSkillList_t LevelCAAxe_ClassList[0x100] = {0}; 

const struct LevelBasedSkillList_t LevelCABow_ClassList[0x100] = {
	
	[CLASS_SNIPER] = {
		.D[0] = CA_HuntersVolley,
	},
	
	[CLASS_SNIPER_F] = {
		.D[0] = CA_HuntersVolley,
	},
	
	
	
	[CLASS_SAGE] = {
		.D[0] = CA_SchismShot,
	},
	
	[CLASS_SAGE_F] = {
		.D[0] = CA_SchismShot,
	},
	
	
	[CLASS_BISHOP] = {
		.D[0] = CA_SchismShot,
	},
	
	[CLASS_BISHOP_F] = {
		.D[0] = CA_SchismShot,
	},
	
	
	[CLASS_DRUID] = {
		.D[0] = CA_SchismShot,
	},
	
	[CLASS_DRUID_F] = {
		.D[0] = CA_SchismShot,
	},
	
	
	
	[CLASS_WARRIOR] = {
		.D[0] = CA_PointBlankVolley,
	},

}; 
