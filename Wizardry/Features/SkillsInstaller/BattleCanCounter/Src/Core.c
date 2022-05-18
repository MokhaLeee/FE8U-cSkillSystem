#include "gbafe-chax.h"

int BCanCounter_CheckSkill(){
	
	if( (*SkillTester)(&gBattleTarget.unit, SID_CounterAttack) )
		return FORCE_COUNTER;
	
	
	if( 1 == gBattleStats.range )
		if( (*SkillTester)(&gBattleTarget.unit, SID_CloseCounter) )
			return FORCE_COUNTER;
	
	return NORMAL_COUNTER;
	
}