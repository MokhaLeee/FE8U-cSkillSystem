#include "gbafe-chax.h"


// We will neglect this function finally
int GetBattleUnitUpdatedWeaponExp(struct BattleUnit* bu) {
	
	return 0;
	
/* 	int i, result, exp;

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

	return result; */
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

	if (!(gBattleStats.config & BATTLE_CONFIG_ARENA) && (ITYPE_CLASS != WType)) {
		if (!bu->canCounter)
			return -1;

		if (!(bu->weaponAttributes & IA_REQUIRES_WEXP))
            return -1;

		if (bu->weaponAttributes & (IA_MAGICDAMAGE | IA_LOCK_3))
			return -1;
	}

	// Ride
	if( ITYPE_RIDE == WType )
		if( 0 == (CA_MOUNTED & UNIT_CATTRIBUTES(&bu->unit)) )
			return -1;
	
	// Fly
	if( ITYPE_FLY == WType )
		if( 0 == ((CA_PEGASUS | CA_WYVERN) & UNIT_CATTRIBUTES(&bu->unit)) )
			return -1;
	
	// Heavy
	if( ITYPE_HEAVY == WType ){
		
		const u8* effList = GetItemEffectiveness(ITEM_SWORD_ARMORSLAYER);
		u8 classId = bu->unit.pClassData->number;
		
		while(1){
			 if (*effList == classId)
				 break;
			 
			 if( 0 == *(++effList) )
				 return -1;
		}
				
	}

		
		

	// this is for class
	if( ITYPE_CLASS == WType )
		exp = GetClassRankExpGain(bu->unit.pClassData->number);
	else
		exp = GetItemAwardedExp(bu->weapon) * bu->wexpMultiplier;
	
	// Todo: make a calc loop
	if( (*SkillTester)(&bu->unit, SID_Discipline) )
		exp = exp * 2;
	
	return (GetWExp(&bu->unit, WType) + exp) >= WPN_EXP_S
		? WPN_EXP_S
		: GetWExp(&bu->unit, WType) + exp;
	

}



s8 NewHasBattleUnitGainedWeaponLevel(struct BattleUnit* bu, u8 WType) {

	/*
	 * BattleUnit_ShouldDisplayWRankUp -> HasBattleUnitGainedWeaponLevel
	 * if true, then SetPopupItem(wType)
	 */
	
	if( GetWExp(&bu->unit, WType) >= WPN_EXP_S )
		return FALSE;
	
	
	int oldWexp = GetWExp(&bu->unit, WType);
	int newWexp = NewGetBattleUnitUpdatedWeaponExp(bu, WType);

	if (newWexp < 0)
		return FALSE;
	

	if( ITYPE_CLASS == WType )
		return (oldWexp < WPN_EXP_S) && (newWexp >= WPN_EXP_S);
	
	return GetWeaponLevelFromExp(oldWexp) != GetWeaponLevelFromExp(newWexp);
}




s8 NewBattleUnit_ShouldDisplayWRankUp(struct BattleUnit *bu, u8 WType) {
	
	if ( FACTION_BLUE != UNIT_FACTION(&bu->unit) )
		return 0;
	
	else
		return NewHasBattleUnitGainedWeaponLevel(bu, WType);
}



/*********************************************************
 *
 *                    Hacked Function
 *
 *********************************************************/


void UpdateUnitDuringBattle(struct Unit* unit, struct BattleUnit* bu) {
	
	extern void B2U_WRanks(struct Unit*, struct BattleUnit*);

	unit->curHP = bu->unit.curHP;
	
	B2U_WRanks(unit, bu);
	
}



int GetWeaponLevelFromExp(int wexp) {
	
	if (wexp < WPN_EXP_D){
		if( 0 == gCanUnitUseAllTypeWeapon )
			if( wexp < WPN_LEVEL_E )
				return WPN_LEVEL_0;
	
		return WPN_LEVEL_E;
	}
	
	if (wexp < WPN_EXP_C)
		return WPN_LEVEL_D;

	if (wexp < WPN_EXP_B)
		return WPN_LEVEL_C;

	if (wexp < WPN_EXP_A)
		return WPN_LEVEL_B;

	if (wexp < WPN_EXP_S)
		return WPN_LEVEL_A;

	return WPN_LEVEL_S;
}



void GetWeaponExpProgressState(int wexp, int* outValue, int* outMax) {
	switch (GetWeaponLevelFromExp(wexp)) {

	case WPN_LEVEL_0:
		*outValue = 0;
		*outMax = 0;
		return;

	case WPN_LEVEL_E:
		*outValue = wexp;
		*outMax   = WPN_EXP_D;
		return;

	case WPN_LEVEL_D:
		*outValue = wexp      - WPN_EXP_D;
		*outMax   = WPN_EXP_C - WPN_EXP_D;
		return;

	case WPN_LEVEL_C:
		*outValue = wexp      - WPN_EXP_C;
		*outMax   = WPN_EXP_B - WPN_EXP_C;
		return;

	case WPN_LEVEL_B:
		*outValue = wexp      - WPN_EXP_B;
		*outMax   = WPN_EXP_A - WPN_EXP_B;
		return;

	case WPN_LEVEL_A:
		*outValue = wexp      - WPN_EXP_A;
		*outMax   = WPN_EXP_S - WPN_EXP_A;
		return;

	case WPN_LEVEL_S:
		*outValue = 0;
		*outMax = 0;
		return;

	} // switch (GetWeaponLevelFromExp(wexp))
}