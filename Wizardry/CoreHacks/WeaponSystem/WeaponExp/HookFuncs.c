#include "gbafe-chax.h"



// ==============================================
//                 For U2B and B2U
// ==============================================

// No need for U2B

void B2U_WRanks(struct Unit* unit, struct BattleUnit* bu){
	
	#define SET_NEW_EXP(wtype){									\
		newWExp = NewGetBattleUnitUpdatedWeaponExp(bu, wtype);	\
																\
		if( newWExp > 0 )										\
			SetWExp(unit, wtype, newWExp);						\
	}
	
	int newWExp;

	SET_NEW_EXP(bu->weaponType);
	SET_NEW_EXP(ITYPE_RIDE);
	SET_NEW_EXP(ITYPE_FLY);
	SET_NEW_EXP(ITYPE_HEAVY);
	
	
	#undef SET_NEW_EXP
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
	
	u8 char_id = unit->pCharacterData->number;
	u8 class_id = unit->pClassData->number;
	
	const struct UnitRomDataExpa *unit_expa = GetUnitRomDataExpa(char_id);
	const struct ClassRomDataExpa *class_expa = GetClassRomDataExpa(class_id);
	
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
		ITYPE_RIDE, 
		0 != unit_expa->rank_ride
			? unit_expa->rank_ride
			: class_expa->rank_ride);
	
	// Fly
	SetWExp(unit, 
		ITYPE_FLY, 
		0 != unit_expa->rank_fly
			? unit_expa->rank_fly
			: class_expa->rank_fly);
	
	// Heavy
	SetWExp(unit, 
		ITYPE_HEAVY, 
		0 != unit_expa->rank_heavy
			? unit_expa->rank_heavy
			: class_expa->rank_heavy);
	
	// Class
	SetWExp(unit, 
		ITYPE_CLASS, 
		0);
}


// ==============================================
//              For ModLU Promotion
// ==============================================

void MLU_PromoGain_WExp(struct Unit* unit, u8 promClassId){
	
	#define SET_WXEP(wtype){							\
		wexp = GetWExp(unit, wtype)						\
			+ GetClassBaseWExp(promClassId, wtype)		\
			- GetClassBaseWExp(baseClassId, wtype);		\
		wexp = wexp > 0 ? wexp : 0;						\
		wexp = wexp > WPN_EXP_S ? WPN_EXP_S : wexp;		\
		SetWExp(unit, wtype, wexp);						\
	}
	
	int wexp;
	int baseClassId = unit->pClassData->number;
	const struct ClassData* promotedClass = GetClassData(promClassId);

	// Remove base class' base wexp from unit wexp
	SET_WXEP(ITYPE_SWORD);
	SET_WXEP(ITYPE_LANCE);
	SET_WXEP(ITYPE_AXE);
	SET_WXEP(ITYPE_BOW);
	
	SET_WXEP(ITYPE_BMAG);
	SET_WXEP(ITYPE_WMAG);
	SET_WXEP(ITYPE_RIDE);
	SET_WXEP(ITYPE_FLY);
	SET_WXEP(ITYPE_HEAVY);
	
	SetWExp(unit, ITYPE_CLASS, 0);
    unit->pClassData = promotedClass;
	
	#undef SET_WXEP

}



// ==============================================
//                   For PopR
// ==============================================

int PopR_InitWRankUp(void) {
	// Check Active Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleActor, gBattleActor.weaponType)) {
		SetPopupWType(gBattleActor.weaponType);
		return TRUE;
	}

	// Check Target Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleTarget, gBattleTarget.weaponType)) {
		SetPopupWType(gBattleTarget.weaponType);
		return TRUE;
	}

	return FALSE;
}


int PopR_InitWRankUpRide(void) {
	// Check Active Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleActor, ITYPE_RIDE)) {
		SetPopupWType(ITYPE_RIDE);
		return TRUE;
	}

	// Check Target Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleTarget, ITYPE_RIDE)) {
		SetPopupWType(ITYPE_RIDE);
		return TRUE;
	}

	return FALSE;
}


int PopR_InitWRankUpFly(void) {
	// Check Active Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleActor, ITYPE_FLY)) {
		SetPopupWType(ITYPE_FLY);
		return TRUE;
	}

	// Check Target Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleTarget, ITYPE_FLY)) {
		SetPopupWType(ITYPE_FLY);
		return TRUE;
	}
	
	return FALSE;
}


int PopR_InitWRankUpHeavy(void) {
	// Check Active Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleActor, ITYPE_HEAVY)) {
		SetPopupWType(ITYPE_HEAVY);
		return TRUE;
	}

	// Check Target Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleTarget, ITYPE_HEAVY)) {
		SetPopupWType(ITYPE_HEAVY);
		return TRUE;
	}

	return FALSE;
}



int PopR_InitWRankUpClass(void) {
	// Check Active Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleActor, ITYPE_CLASS)) {
		SetPopupWType(ITYPE_CLASS);
		return TRUE;
	}

	// Check Target Unit
	if (NewBattleUnit_ShouldDisplayWRankUp(&gBattleTarget, ITYPE_CLASS)) {
		SetPopupWType(ITYPE_CLASS);
		return TRUE;
	}

	return FALSE;
}

