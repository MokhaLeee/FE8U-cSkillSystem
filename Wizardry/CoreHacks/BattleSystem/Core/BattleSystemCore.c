#include "gbafe-chax.h"

void ClearBattleHitExt(){

	for (int i = 0; i < BATTLE_HIT_MAX; ++i) 
	{
		// attributes
		BattleHitExtArray[i].attr = 0;
		
		// attacker skills
		BattleHitExtArray[i].atk_skills[0] = 0;
		BattleHitExtArray[i].atk_skills[1] = 0;
		BattleHitExtArray[i].atk_skills[2] = 0;
		
		// defender skills
		BattleHitExtArray[i].def_skills[0] = 0;
		BattleHitExtArray[i].def_skills[1] = 0;
		BattleHitExtArray[i].def_skills[2] = 0;
		
		// pad
		for( int j = 0; j < (0x10 - 0x7); j++  )
			BattleHitExtArray[i].pad[j] = 0;
    }

	*BattleHitExtCur = BattleHitExtArray;
	
}


void ResetBattleFlagExt(void){
	
	gpBattleFlagExt->isCombat = 0;
	gpBattleFlagExt->combatArt_id = 0;

}


void BattleHitExt_SetAttr(int attr){
	
	(*BattleHitExtCur)->attr |= attr;
	
}

int SetBattleHitExt_AtkSkill(u8 skill_id){
	
	for(int i = 0; i < 3; i++)
	{
		if( !SKILL_VALID( (*BattleHitExtCur)->atk_skills[i] ) )
		{
			(*BattleHitExtCur)->atk_skills[i] = skill_id;
			return 1;
		}
	}
	
	return 0;
}


int SetBattleHitExt_DefSkill(u8 skill_id){
	
	for(int i = 0; i < 3; i++)
	{
		if( !SKILL_VALID( (*BattleHitExtCur)->def_skills[i] ) )
		{
			(*BattleHitExtCur)->def_skills[i] = skill_id;
			return 1;
		}
	}
	
	return 0;
}










// ======================================================
//                          Hack
// ======================================================

void ClearBattleHits(void) {

	for (int i = 0; i < BATTLE_HIT_MAX; ++i) {
		gBattleHitArray[i].attributes = 0;
		gBattleHitArray[i].info = 0;
		gBattleHitArray[i].hpChange = 0;
	}

	gBattleHitIterator = gBattleHitArray;
	
	// hack
	ClearBattleHitExt();
}




s8 BattleGenerateHit(struct BattleUnit* attacker, struct BattleUnit* defender) {
	
	// function declear
	extern void BattleUpdateBattleStats(struct BattleUnit*, struct BattleUnit*);
	extern void BattleGenerateHitTriangleAttack(struct BattleUnit*, struct BattleUnit*);
	extern void BattleGenerateHitAttributes(struct BattleUnit*, struct BattleUnit*);
	extern void BattleGenerateHitEffects(struct BattleUnit*, struct BattleUnit*);
	
	
	// start
	if (attacker == &gBattleTarget)
		gBattleHitIterator->info |= BATTLE_HIT_INFO_RETALIATION;

	BattleUpdateBattleStats(attacker, defender);

	BattleGenerateHitTriangleAttack(attacker, defender);
	BattleGenerateHitAttributes(attacker, defender);
	BattleGenerateHitEffects(attacker, defender);

	if (attacker->unit.curHP == 0 || defender->unit.curHP == 0) {
		attacker->wexpMultiplier++;

		gBattleHitIterator->info |= BATTLE_HIT_INFO_FINISHES;

		if (gBattleTarget.unit.curHP != 0) {
			gBattleHitIterator++;
			
			// hack
			(*BattleHitExtCur)++;
			
			return TRUE;
		}

		gBattleHitIterator->info |= BATTLE_HIT_INFO_KILLS_TARGET;

		gBattleHitIterator++;
		
		// hack
		(*BattleHitExtCur)++;
		
		return TRUE;
		
	} else if (defender->statusOut == UNIT_STATUS_PETRIFY || defender->statusOut == UNIT_STATUS_13) {
		gBattleHitIterator->info |= BATTLE_HIT_INFO_FINISHES;

		gBattleHitIterator++;
		
		// hack
		(*BattleHitExtCur)++;
		
		return TRUE;
	}

	// hack
	(*BattleHitExtCur)++;
	
	gBattleHitIterator++;
	return FALSE;
}
