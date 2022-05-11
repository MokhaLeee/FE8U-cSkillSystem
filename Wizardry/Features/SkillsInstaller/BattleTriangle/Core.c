#include "gbafe-chax.h"

// modular functions
void WTA_SwordBreaker(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	if( (ITYPE_LANCE != attacker->weaponType) || (ITYPE_SWORD != defender->weaponType) )
		return;
	
	
	if( (*SkillTester)(&attacker->unit, SID_SwordBreaker) )
	{
		attacker->battleHitRate += 20;
		attacker->battleAvoidRate += 20;
		
		// for BkSel
		attacker->wTriangleHitBonus += 1;
		attacker->wTriangleDmgBonus += 1;
		defender->wTriangleHitBonus -= 1;
		defender->wTriangleDmgBonus -= 1;
		return;
	}
	

}





void WTA_AxeBreaker(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	if( (ITYPE_SWORD != attacker->weaponType) || (ITYPE_AXE != defender->weaponType) )
		return;
	

	if( (*SkillTester)(&attacker->unit, SID_AxeBreaker) )
	{
		attacker->battleHitRate += 20;
		attacker->battleAvoidRate += 20;
		
		// for BkSel
		attacker->wTriangleHitBonus += 1;
		attacker->wTriangleDmgBonus += 1;
		defender->wTriangleHitBonus -= 1;
		defender->wTriangleDmgBonus -= 1;
		return;
	}


}



void WTA_LanceBreaker(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	if( (ITYPE_AXE != attacker->weaponType) || (ITYPE_LANCE != defender->weaponType) )
		return;
	

	if( (*SkillTester)(&attacker->unit, SID_LanceBreaker) )
	{
		attacker->battleHitRate += 20;
		attacker->battleAvoidRate += 20;
		
		// for BkSel
		attacker->wTriangleHitBonus += 1;
		attacker->wTriangleDmgBonus += 1;
		defender->wTriangleHitBonus -= 1;
		defender->wTriangleDmgBonus -= 1;
		return;
	}


}






void WTA_BowBreaker(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	if( ITYPE_ANIMA != attacker->weaponType )
		if( ITYPE_LIGHT != attacker->weaponType )
			if( ITYPE_DARK != attacker->weaponType )
				return;
	
	if( ITYPE_BOW != defender->weaponType )
		return;
	
	
	if( (*SkillTester)(&attacker->unit, SID_BowBreaker) )
	{
		attacker->battleHitRate += 20;
		attacker->battleAvoidRate += 20;
		
		// for BkSel
		attacker->wTriangleHitBonus += 1;
		attacker->wTriangleDmgBonus += 1;
		defender->wTriangleHitBonus -= 1;
		defender->wTriangleDmgBonus -= 1;
		return;
	}


}



void WTA_TomeBreaker(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	if( ITYPE_BOW != attacker->weaponType )
		return;
	
	if( ITYPE_ANIMA != defender->weaponType )
		if( ITYPE_LIGHT != defender->weaponType )
			if( ITYPE_DARK != defender->weaponType )
				return;
	
	if( (*SkillTester)(&attacker->unit, SID_TomeBreaker) )
	{
		attacker->battleHitRate += 20;
		attacker->battleAvoidRate += 20;
		
		// for BkSel
		attacker->wTriangleHitBonus += 1;
		attacker->wTriangleDmgBonus += 1;
		defender->wTriangleHitBonus -= 1;
		defender->wTriangleDmgBonus -= 1;
		return;
	}


}
