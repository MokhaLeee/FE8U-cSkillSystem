#include "gbafe-chax.h"

void BC_BlowBonus (struct BattleUnit* act, struct BattleUnit* tar){
	
	if( &gBattleActor != act )
		return;
	
	// Str & Mag
	if( !CheckMagAttack(act) )
	{
		// Phys Atk
		if( (*SkillTester)(&act->unit, SID_BlowDeath) )
			act->battleAttack += 6;
	}
	else
	{
		if( (*SkillTester)(&act->unit, SID_BlowFiendish) )
			act->battleAttack += 6;
	}
	
	
	// AS
	if( (*SkillTester)(&act->unit, SID_BlowDarting) )
		act->battleSpeed += 6;
	
	// Hit
	if( (*SkillTester)(&act->unit, SID_BlowUncanny) )
		act->battleHitRate += 30;
	
	// Avo
	if( (*SkillTester)(&act->unit, SID_BlowDuelist) )
		act->battleAvoidRate += 20;
	
	// Def or Res
	if( !CheckMagAttack(tar) )
	{
		// Phys Atk
		if( (*SkillTester)(&act->unit, SID_BlowArmored) )
			act->battleDefense += 6;
	}
	else
	{
		if( (*SkillTester)(&act->unit, SID_BlowWarding) )
			act->battleDefense += 6;
	}
}