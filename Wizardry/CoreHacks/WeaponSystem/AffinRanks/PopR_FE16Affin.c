#include "gbafe-chax.h"

// For Level Up
int PopR_InitRankUpRide(void) {
	// Check Active Unit
	if (BattleUnit_ShouldDisplayWRankUp(&gBattleActor)) {
		SetPopupWType(gBattleActor.weaponType);
		return TRUE;
	}

	// Check Target Unit
	if (BattleUnit_ShouldDisplayWRankUp(&gBattleTarget)) {
		SetPopupWType(gBattleTarget.weaponType);
		return TRUE;
	}
	SetPopupWType(gBattleActor.weaponType);

	return FALSE;
}


int PopR_InitRankUpHeavy(void) {
	// Check Active Unit
	if (BattleUnit_ShouldDisplayWRankUp(&gBattleActor)) {
		SetPopupWType(gBattleActor.weaponType);
		return TRUE;
	}

	// Check Target Unit
	if (BattleUnit_ShouldDisplayWRankUp(&gBattleTarget)) {
		SetPopupWType(gBattleTarget.weaponType);
		return TRUE;
	}
	SetPopupWType(gBattleActor.weaponType);

	return FALSE;
}


int PopR_InitRankUpFly(void) {
	// Check Active Unit
	if (BattleUnit_ShouldDisplayWRankUp(&gBattleActor)) {
		SetPopupWType(gBattleActor.weaponType);
		return TRUE;
	}

	// Check Target Unit
	if (BattleUnit_ShouldDisplayWRankUp(&gBattleTarget)) {
		SetPopupWType(gBattleTarget.weaponType);
		return TRUE;
	}
	SetPopupWType(gBattleActor.weaponType);

	return FALSE;
}