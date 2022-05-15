#include "gbafe-chax.h"


// Blow Skills
extern const struct SkillInfo SkillInfo_BlowDarting, SkillInfo_BlowDeath, SkillInfo_BlowArmored, SkillInfo_BlowFiendish, SkillInfo_BlowWarding, SkillInfo_BlowDuelist, SkillInfo_BlowUncanny;


// Battle-Order Skills
extern const struct SkillInfo SkillInfo_Vantage, SkillInfo_VantageBat, SkillInfo_Desperation, SkillInfo_DesperationBat, SkillInfo_QuickRiposte;

// Battle-Triangle Skills
extern const struct SkillInfo SkillInfo_SwordBreaker, SkillInfo_AxeBreaker, SkillInfo_LanceBreaker, SkillInfo_BowBreaker, SkillInfo_TomeBreaker, SkillInfo_FistBreaker;

// Post-Action Skills
extern const struct SkillInfo SkillInfo_Canto, SkillInfo_AlertStance, SkillInfo_AlertStancePlus;



// Info Table
struct SkillInfo const* const SkillInfoTable[0x100] = {
	
	[SID_BlowDarting] = &SkillInfo_BlowDarting,
	[SID_BlowDeath] = &SkillInfo_BlowDeath,
	[SID_BlowArmored] = &SkillInfo_BlowArmored,
	[SID_BlowFiendish] = &SkillInfo_BlowFiendish,
	[SID_BlowWarding] = &SkillInfo_BlowWarding,
	[SID_BlowDuelist] = &SkillInfo_BlowDuelist,
	[SID_BlowUncanny] = &SkillInfo_BlowUncanny,
	
	
	[SID_Vantage] = &SkillInfo_Vantage,
	[SID_VantageBat] = &SkillInfo_VantageBat,
	[SID_Desperation] = &SkillInfo_Desperation,
	[SID_DesperationBat] = &SkillInfo_DesperationBat,
	[SID_QuickRiposte] = &SkillInfo_QuickRiposte,

	
	[SID_SwordBreaker] = &SkillInfo_SwordBreaker,
	[SID_AxeBreaker] = &SkillInfo_AxeBreaker,
	[SID_LanceBreaker] = &SkillInfo_LanceBreaker,
	[SID_BowBreaker] = &SkillInfo_BowBreaker,
	[SID_TomeBreaker] = &SkillInfo_TomeBreaker,
	[SID_FistBreaker] = &SkillInfo_FistBreaker,
	
	[SID_Canto] = &SkillInfo_Canto,
	[SID_AlertStance] = &SkillInfo_AlertStance,
	[SID_AlertStancePlus] = &SkillInfo_AlertStancePlus,
};











