#include "gbafe-chax.h"

void SetUnitStatus(struct Unit* unit, int status) {
	
	struct UnitStatus* status_at = GetUnitStatusAt(unit);
	
	if (status == 0) 
	{
		status_at->status_index	= 0;
		status_at->status_dura	= 0;
	} 
	else 
	{
		status_at->status_index	= status;
		
		const struct UnitStatusInfo* info = GetStatusInfo(status);
		
		status_at->status_dura	= 
			0 == info->duration
			? 4 - 1
			: info->duration - 1;
	}
}

void SetUnitStatusExt(struct Unit* unit, int status, int duration) {
	
	struct UnitStatus* status_at = GetUnitStatusAt(unit);
	
	status_at->status_index	= status;
	status_at->status_dura	= 
		duration > 1
		? duration - 1
		: 0;
}


void HbPopulate_SSStatus(struct HelpBoxProc* proc)
{
	u8 status_index = GetUnitStatusIndex(gStatScreen.unit);
	
	proc->mid = GetStatusInfo( status_index )->msg_desc;

}

char* GetUnitRescueName(struct Unit* unit) {
	if (unit->rescueOtherUnit)
		return GetStringFromIndex(GetUnit(unit->rescueOtherUnit)->pCharacterData->nameTextId);
	
	return GetStringFromIndex(GetStatusInfo(UNIT_STATUS_NONE)->msg_name);

	
}


char* GetUnitStatusName(struct Unit* unit) {
	u8 index = GetUnitStatusIndex(unit);
	u16 msg = GetStatusInfo(index)->msg_name;
	return GetStringFromIndex(msg);
}
