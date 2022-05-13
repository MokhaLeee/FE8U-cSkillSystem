#include "gbafe-chax.h"

int UnitHasExtData(struct Unit* unit){
	
	u8 char_id = unit->pCharacterData->number;
	
	return (char_id < UNIT_EXT_MAX) && GetCharacterData(char_id)->affinity;
}

struct UnitExt* GetUnitExt(struct Unit* unit){
	
	if( !UnitHasExtData(unit) )
		return NULL;
	else
		return &gpUnitExtData[unit->pCharacterData->number];
}


void ClearUnitsExt(){
	
	CpuFill16(0, gpUnitExtData, UNIT_EXT_SIZE * UNIT_EXT_MAX);
}
