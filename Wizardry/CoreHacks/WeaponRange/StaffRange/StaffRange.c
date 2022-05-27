#include "gbafe-chax.h"

extern void ForEachPosInRange(void*);

void MakeTargetListForAdjacentHeal(struct Unit* unit){
	
	extern void TryAddUnitToHealTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_HEAL);
	ForEachUnitMaster( TryAddUnitToHealTargetList, &gBmMapRange, NU_RANGE_MAP);
}



void MakeTargetListForRangedHeal(struct Unit* unit){
	
	extern void TryAddUnitToHealTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_PHYSIC);
	ForEachUnitMaster( TryAddUnitToHealTargetList, &gBmMapRange, NU_RANGE_MAP);
}




void MakeTargetListForRestore(struct Unit* unit){
	
	extern void TryAddUnitToRestoreTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_RESTORE);
	ForEachUnitMaster( TryAddUnitToRestoreTargetList, &gBmMapRange, NU_RANGE_MAP);
}




void MakeTargetListForRescueStaff(struct Unit* unit){
	
	extern void TryAddUnitToRescueStaffTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_RESCUE);
	ForEachUnitMaster( TryAddUnitToRescueStaffTargetList, &gBmMapRange, NU_RANGE_MAP);
}



void MakeTargetListForBarrier(struct Unit* unit){
	
	extern void TryAddUnitToBarrierTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_BARRIER);
	ForEachUnitMaster( TryAddUnitToBarrierTargetList, &gBmMapRange, NU_RANGE_MAP);
}


void MakeTargetListForSilence(struct Unit* unit){
	
	extern void TryAddUnitToSilenceTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_SILENCE);
	ForEachUnitMaster( TryAddUnitToSilenceTargetList, &gBmMapRange, NU_RANGE_MAP);
}


void MakeTargetListForSleep(struct Unit* unit){
	
	extern void TryAddUnitToSleepTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_SLEEP);
	ForEachUnitMaster( TryAddUnitToSleepTargetList, &gBmMapRange, NU_RANGE_MAP);
}




void MakeTargetListForBerserk(struct Unit* unit){
	
	extern void TryAddUnitToBerzerkTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_BERSERK);
	ForEachUnitMaster( TryAddUnitToBerzerkTargetList, &gBmMapRange, NU_RANGE_MAP);
}


void MakeTargetListForWarp(struct Unit* unit){
	
	extern void TryAddUnitToWarpTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_WARP);
	ForEachUnitMaster( TryAddUnitToWarpTargetList, &gBmMapRange, NU_RANGE_MAP);
}


void MakeTargetListForHammerne(struct Unit* unit){
	
	extern void TryAddUnitToHammerneTargetList();
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_REPAIR);
	ForEachUnitMaster( TryAddUnitToHammerneTargetList, &gBmMapRange, NU_RANGE_MAP);
}





void MakeTargetListForUnlock(struct Unit* unit){
	
	extern void TryAddClosedDoorToTargetList();
	
	gUnitSubject = unit;
	InitTargets(unit->xPos, unit->yPos);
	BmMapFill(gBmMapRange, 0);
	FillMapForSingleItem(unit, ITEM_STAFF_UNLOCK);
	ForEachPosInRange(TryAddClosedDoorToTargetList);

}



// void MakeTargetListForLatona(struct Unit* unit);
// void MakeTargetListForMine(struct Unit* unit);
// void MakeTargetListForLightRune(struct Unit* unit);



