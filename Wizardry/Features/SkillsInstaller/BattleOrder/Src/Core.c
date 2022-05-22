#include "gbafe-chax.h"

// For DoubleLion: BattleOrder/HitCountCalc
int HitCountCalc_SkillDoubleLion(struct BattleUnit* actor, int cur){
	
	struct Unit* unit_act = GetUnit(actor->unit.index);
	
	// attacker cannot use brave if use combat-art
	if( &gBattleActor == actor )
		if( (*SkillTester)(unit_act, SID_DoubleLion) )
			if( GetUnitCurrentHp(unit_act) == GetUnitMaxHp(unit_act) )
				return cur + 1;
	
	return cur;
	
}