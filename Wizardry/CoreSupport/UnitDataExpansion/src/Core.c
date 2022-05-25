#include "gbafe-chax.h"

int UnitHasExpaData(struct Unit* unit){
	
	u8 char_id = unit->pCharacterData->number;
	
	return (char_id < UNIT_EXPA_MAX) && GetCharacterData(char_id)->affinity;
}

struct UnitExpa* GetUnitExpa(struct Unit* unit){
	
	if( !UnitHasExpaData(unit) )
		return NULL;
	else
		return &gpUnitExpaData[unit->pCharacterData->number];
}


void ClearUnitsExpa(){
	
	CpuFill16(0, gpUnitExpaData, UNIT_EXPA_SIZE * UNIT_EXPA_MAX);
}
