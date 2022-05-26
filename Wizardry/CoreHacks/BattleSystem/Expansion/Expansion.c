#include "gbafe-chax.h"

void ClearBattleHitExt(){

	for( int i = 0; i < (BATTLE_HIT_MAX * 0x10 / 4); i++ )
		*(i + (u32*)BattleHitExtArray) = 0;

	*BattleHitExtCur = BattleHitExtArray;
	
	// Hit counter
	// add inside function: BattleGenerateHit
	gpBattleFlagExt->hit_count = 0;
}


void ResetBattleFlagExt(void){
	// At the end of Post-Action
	gpBattleFlagExt->isCombat = 0;
	gpBattleFlagExt->combatArt_hitted = 0;
	gpBattleFlagExt->combatArt_id = 0;
	gpBattleFlagExt->combat_unit = 0;
	gpBattleFlagExt->hit_count = 0;
	gpBattleFlagExt->doubleLion_activited = 0;

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
	
	// struct BattleHit *arr = gBattleHitArray;
	struct BattleHit *arr = gBattleHitArrayReAt;
	
	for (int i = 0; i < BATTLE_HIT_MAX_EXPANSION; ++i) {
		arr[i].attributes = 0;
		arr[i].info = 0;
		arr[i].hpChange = 0;
	}

	gBattleHitIterator = arr;
	
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

	// Make a counter
	gpBattleFlagExt->hit_count++;
	
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
			(*BattleHitExtCur)++;
			return TRUE;
		}

		gBattleHitIterator->info |= BATTLE_HIT_INFO_KILLS_TARGET;

		gBattleHitIterator++;
		(*BattleHitExtCur)++;
		return TRUE;
		
	} 
	else if (defender->statusOut == UNIT_STATUS_PETRIFY || defender->statusOut == UNIT_STATUS_13) 
	{
		gBattleHitIterator->info |= BATTLE_HIT_INFO_FINISHES;

		gBattleHitIterator++;
		(*BattleHitExtCur)++;
		return TRUE;
	}

	// hack
	(*BattleHitExtCur)++;
	gBattleHitIterator++;
	return FALSE;
}
