#include "gbafe-chax.h"

void PostActionSkill_AlertStance(ProcPtr proc){
	
	extern void StartStatusClearFx(struct Unit*, ProcPtr);
	
	if( 0x1 != gActionData.unitActionType ) // actuon-wait
		return;
	
	if( (*SkillTester)(gActiveUnit, SID_AlertStancePlus) )
		SetUnitStatus(gActiveUnit, UNIT_NEW_STATUS_AvoidPlus);
	else if( (*SkillTester)(gActiveUnit, SID_AlertStance) )
		SetUnitStatus(gActiveUnit, UNIT_NEW_STATUS_Avoid);
	else
		return;
	
	MU_EndAll();
	StartStatusClearFx(gActiveUnit, proc);
}