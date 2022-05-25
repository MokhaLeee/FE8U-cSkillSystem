#include "gbafe-chax.h"

int GetBattleUnitUpdatedWeaponExp(struct BattleUnit* bu);


s8 HasBattleUnitGainedWeaponLevel(struct BattleUnit* bu) {

	/*
	 * BattleUnit_ShouldDisplayWRankUp -> HasBattleUnitGainedWeaponLevel
	 * if true, then SetPopupItem(wType)
	 */
	
	if( bu->unit.ranks[bu->weaponType] >= WPN_EXP_S )
		return FALSE;
	
	
	int oldWexp = bu->unit.ranks[bu->weaponType];
	int newWexp = NewGetBattleUnitUpdatedWeaponExp(bu, bu->weaponType);

	if (newWexp < 0)
		return FALSE;
	
	// Makes it so that you cannot gain weapon ranks for weapons you don't have a rank in
	if( oldWexp <= 0 )
		return FALSE;
	
	return GetWeaponLevelFromExp(oldWexp) != GetWeaponLevelFromExp(newWexp);
}



// We will neglect this function finally
int GetBattleUnitUpdatedWeaponExp(struct BattleUnit* bu) {
	int i, result, exp;

	if (UNIT_FACTION(&bu->unit) != FACTION_BLUE)
		return -1;

	if (bu->unit.curHP == 0)
		return -1;

	if (gRAMChapterData.chapterStateBits & CHAPTER_FLAG_7)
		return -1;

	if (gGameState.gameStateBits & 0x40) // TODO: GAME STATE BITS CONSTANTS
		return -1;

	if (!(gBattleStats.config & BATTLE_CONFIG_ARENA)) {
		if (!bu->canCounter)
			return -1;

		if (!(bu->weaponAttributes & IA_REQUIRES_WEXP))
            return -1;

		if (bu->weaponAttributes & (IA_MAGICDAMAGE | IA_LOCK_3))
			return -1;
	}
	
	exp = GetItemAwardedExp(bu->weapon) * bu->wexpMultiplier;
	
	// Todo: make a calc loop
	if( (*SkillTester)(&bu->unit, SID_Discipline) )
		exp = exp * 2;	
	
	result = bu->unit.ranks[bu->weaponType];
	result += exp;
	
	
	for (i = 0; i < 8; ++i) {
		if (i == bu->weaponType)
			continue;

		if (bu->unit.pClassData->baseRanks[i] == WPN_EXP_S)
			continue;

		if (bu->unit.ranks[i] < WPN_EXP_S)
			continue;

		if (result >= WPN_EXP_S)
			result = (WPN_EXP_S - 1);

		break;
	}

	if (UNIT_CATTRIBUTES(&bu->unit) & CA_PROMOTED) {
		if (result > WPN_EXP_S)
			result = WPN_EXP_S;
	} 
	else if (UNIT_CATTRIBUTES(&bu->unit) & CA_MAXLEVEL10) {

		if (result > WPN_EXP_A)
			result = WPN_EXP_A;
	}

	return result;
}














/*
 *
 * New:
 *
 */
 
int NewGetBattleUnitUpdatedWeaponExp(struct BattleUnit* bu, u8 WType){
	
	int exp = 0;
	
	if (UNIT_FACTION(&bu->unit) != FACTION_BLUE)
		return -1;

	if (bu->unit.curHP == 0)
		return -1;

	if (gRAMChapterData.chapterStateBits & CHAPTER_FLAG_7)
		return -1;

	if (gGameState.gameStateBits & 0x40) // TODO: GAME STATE BITS CONSTANTS
		return -1;

	if (!(gBattleStats.config & BATTLE_CONFIG_ARENA)) {
		if (!bu->canCounter)
			return -1;

		if (!(bu->weaponAttributes & IA_REQUIRES_WEXP))
            return -1;

		if (bu->weaponAttributes & (IA_MAGICDAMAGE | IA_LOCK_3))
			return -1;
	}
	
	exp = GetItemAwardedExp(bu->weapon) * bu->wexpMultiplier;
	
	// Todo: make a calc loop
	if( (*SkillTester)(&bu->unit, SID_Discipline) )
		exp = exp * 2;	
	
	return (GetWExp(&bu->unit, WType) + exp) >= WPN_EXP_S
		? WPN_EXP_S
		: GetWExp(&bu->unit, WType) + exp;
	

}