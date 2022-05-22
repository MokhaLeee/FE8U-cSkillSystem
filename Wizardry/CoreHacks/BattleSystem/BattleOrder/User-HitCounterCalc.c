#include "gbafe-chax.h"

int HitCountCalc_BraveWeapon(struct BattleUnit* actor, int cur){
	
	// Target cannot double attack with brave weapon
	if( actor->weaponAttributes & IA_BRAVE )
		if( &gBattleActor == actor )
			return cur + 1;
	
	return cur;
}