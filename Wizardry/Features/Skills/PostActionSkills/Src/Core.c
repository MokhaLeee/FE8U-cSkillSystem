#include "gbafe-chax.h"

int CantoHackCore(ProcPtr proc, struct Unit* unit){
	
	
	if( !(*SkillTester)(unit, SID_Canto) )
		return 0;
	
	int stat_select = (US_DEAD | US_CANTOING | US_HAS_MOVED_AI) & unit->state;

	if( 0 != stat_select )
		return 0;
	
	// if wait
	if( 1 == gActionData.unitActionType )
		return 0;
	
	if( MovGetter(unit) <= gActionData.moveCount )
		return 0;
	
	if( 0 == CanUnitMove() )
		return 0;
	
	return 1;
}

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



