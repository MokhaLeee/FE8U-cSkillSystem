#include "gbafe-chax.h"

// ===================================================
//                    Vanilla
//====================================================

void BattleApplyWeaponTriangleEffect(struct BattleUnit* attacker, struct BattleUnit* defender) {
	
	/*
	 * Idea:
	 * Since vanilla WTA bonus can only get hit & dmg bonus.
	 * So here we null the vanilla WTA bonus
	 * But just calculate in Pre-Battle calc
	 * now WTA-bonus in BattleUnit struct is just for BkSel UI.
	 */
	
	return;
	
}




void BC_WTA_Bonus(struct BattleUnit* attacker, struct BattleUnit* defender) {
	
	// inside Pre-Battle Calc
	
	typedef void (*BC_Fun) (struct BattleUnit*, struct BattleUnit*);
	extern BC_Fun BattleTriangleBonusCalcLoopTable[];
	
	BC_Fun *it = &BattleTriangleBonusCalcLoopTable[0];
	
	while( *it )
		(*it++)(attacker, defender);
}









