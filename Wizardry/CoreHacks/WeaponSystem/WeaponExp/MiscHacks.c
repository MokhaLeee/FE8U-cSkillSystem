#include "gbafe-chax.h"



// ==============================================
//                 For U2B and B2U
// ==============================================

// No need for U2B

void B2U_WRanks(struct Unit* unit, struct BattleUnit* bu){
	
	SetWExp(
		unit,
		bu->weaponType,
		NewGetBattleUnitUpdatedWeaponExp(bu, bu->weaponType) );
	
	SetWExp(
		unit,
		MASTERY_ICON_RIDE,
		NewGetBattleUnitUpdatedWeaponExp(bu, MASTERY_ICON_RIDE) );
	
	SetWExp(
		unit,
		MASTERY_ICON_FLY,
		NewGetBattleUnitUpdatedWeaponExp(bu, MASTERY_ICON_FLY) );
	
	SetWExp(
		unit,
		MASTERY_ICON_HEAVY,
		NewGetBattleUnitUpdatedWeaponExp(bu, MASTERY_ICON_HEAVY) );
	

}


// ==============================================
//                 For Load Unit
// ==============================================

void LoadUnit_WRanks(struct Unit* unit){
	
	inline u8 GetMax(u8 a0, u8 a1, u8 a2, u8 a3, u8 a4, u8 a5){
	
		u8 max;
		
		max = a0 > a1 ? a0 : a1;
		max = max > a2 ? max : a2;
		max = max > a3 ? max : a3;
		max = max > a4 ? max : a4;
		max = max > a5 ? max : a5;
		
		return max;
	}
	
	u8 charID = unit->pCharacterData->number;
	u8 classID = unit->pClassData->number;
	
	for (int i = 0; i <= ITYPE_STAFF; ++i) {
		
		if( 0 != unit->pCharacterData->baseRanks[i] )
			SetWExp(unit, i, unit->pCharacterData->baseRanks[i]);
		else
			SetWExp(unit, i, unit->pClassData->baseRanks[i]);
		

    }
	
	
	SetWExp(unit, 
		ITYPE_ANIMA, 
		GetMax(
			unit->pCharacterData->baseRanks[ITYPE_ANIMA], 
			unit->pClassData->baseRanks[ITYPE_ANIMA], 
			unit->pCharacterData->baseRanks[ITYPE_LIGHT],
			unit->pClassData->baseRanks[ITYPE_LIGHT],
			unit->pCharacterData->baseRanks[ITYPE_DARK],
			unit->pClassData->baseRanks[ITYPE_DARK]
			) );
	
	// Ride
	SetWExp(unit, 
		MASTERY_ICON_RIDE, 
		0 != CharWRanksTable[charID].rank_ride
			? CharWRanksTable[charID].rank_ride
			: ClassWRanksTable[classID].rank_ride);
	
	// Fly
	SetWExp(unit, 
		MASTERY_ICON_FLY, 
		0 != CharWRanksTable[charID].rank_fly
			? CharWRanksTable[charID].rank_fly
			: ClassWRanksTable[classID].rank_fly);
	
	// Heavy
	SetWExp(unit, 
		MASTERY_ICON_HEAVY, 
		0 != CharWRanksTable[charID].rank_heavy
			? CharWRanksTable[charID].rank_heavy
			: ClassWRanksTable[classID].rank_heavy);
			
}
