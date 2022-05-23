#include "gbafe-chax.h"

int HitCountCalc_BraveWeapon(struct BattleUnit* actor, int cur){
	
	// Target cannot double attack with brave weapon
	if( actor->weaponAttributes & IA_BRAVE )
		if( &gBattleActor == actor )
			return cur + 1;
	
	return cur;
}


u8 *SortHitActivitionSkills(struct BattleUnit* actor, struct Unit* target, u8 arr[10]){
	
	extern int CheckSkillDoubleLion(struct BattleUnit*);
	extern int CheckSkillRuinedBladePlus(struct BattleUnit*);
	
	int i = 1;	// 0 is always zero !!!
	
	if( 0 != HitCountCalc_BraveWeapon(actor, 0) )
		arr[i++] = 0;
	
	if( CheckSkillDoubleLion(actor) )
		arr[i++] = SID_DoubleLion;
	
	if( CheckSkillRuinedBladePlus(actor) )
		arr[i++] = SID_RuinedBladePlus;
	
	return arr;
}