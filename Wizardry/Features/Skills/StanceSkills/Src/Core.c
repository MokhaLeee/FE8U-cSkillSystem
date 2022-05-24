#include "gbafe-chax.h"

void BC_StanceBonus (struct BattleUnit* act, struct BattleUnit* tar){
	
	if( &gBattleTarget != act )
		return;
	
	
	if( (*SkillTester)(&act->unit, SID_StanceBracing) )
		act->battleDefense += 4;
	
	if( (*SkillTester)(&act->unit, SID_StanceFierce) )
		act->battleAttack += 6;
	
	if( (*SkillTester)(&act->unit, SID_StanceDarting) )
		act->battleSpeed += 6;
	
	if( (*SkillTester)(&act->unit, SID_StanceKestrel) ){
		act->battleAttack += 4;
		act->battleSpeed += 4;
	}
	
	if( (*SkillTester)(&act->unit, SID_StanceMirror) ){
		act->battleAttack += 4;
		act->battleDefense += CheckMagAttack(tar)
			? 4
			: 0;
	}
	
	if( (*SkillTester)(&act->unit, SID_StanceReady) ){
		act->battleSpeed += 4;
		act->battleDefense += !CheckMagAttack(tar)
			? 4
			: 0;
	}
	
	if( (*SkillTester)(&act->unit, SID_StanceSteady) )
		act->battleDefense += !CheckMagAttack(tar)
			? 6
			: 0;
	
	if( (*SkillTester)(&act->unit, SID_StanceSturdy) ){
		act->battleAttack += 4;
		act->battleDefense += !CheckMagAttack(tar)
			? 4
			: 0;
	}
	
	if( (*SkillTester)(&act->unit, SID_StanceSwift) ){
		act->battleSpeed += 4;
		act->battleDefense += CheckMagAttack(tar)
			? 4
			: 0;
	}
	
	if( (*SkillTester)(&act->unit, SID_StanceWarding) )
		act->battleDefense += CheckMagAttack(tar)
			? 6
			: 0;

}