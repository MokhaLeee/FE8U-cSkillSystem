#include "gbafe-chax.h"

int GetCombatArt_WeaponRangeMaxBonus(struct Unit* unit, u16 item){
	
	// sine the flag is set for both attacker and defender
	if( 1 == gpBattleFlagExt->isCombat )
		if( unit->index == gBattleActor.unit.index )
			return 1;
	
	return 0;
}
