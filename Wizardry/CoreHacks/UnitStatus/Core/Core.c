#include "gbafe-chax.h"

struct UnitStatus* GetUnitStatusAt(struct Unit* unit){
	return (struct UnitStatus*)(0x30 + (u8*)unit);
}

u8 GetUnitStatusIndex(struct Unit* unit){

	return GetUnitStatusAt(unit)->status_index;
	
}
u8 GetUnitStatusDura(struct Unit* unit){
	
	int dura = GetUnitStatusAt(unit)->status_dura;
	
	// to make 4 turns by 2 bits
	if( 0 != GetUnitStatusIndex(unit) )
		return dura + 1;
	else
		return 0;

}

int TryDecUnitStatusDura(struct Unit* unit){
	
	if( 0 == GetUnitStatusDura(unit) )
		return 0;
	
	struct UnitStatus* status = GetUnitStatusAt(unit);
	
	// to make 4 turns by 2 bits
	if( 0 == status->status_dura )
		status->status_index = 0;
	else
		status->status_dura--;
	
	return 1;
}

const void* GetStatusMiniBoxGfx(const u8 status_index){
	return GetStatusInfo(status_index)->mini_gfx;
}

const struct UnitStatusInfo* GetStatusInfo(u8 index){
	return UnitStatusInfoTable[index];
}