#include "gbafe-chax.h"

s8 PowGetter_UnitStatus(struct Unit* unit, s8 cur){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return cur + info->pow_bonus;
}


s8 MagGetter_UnitStatus(struct Unit* unit, s8 cur){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return cur + info->mag_bonus;
}


s8 SklGetter_UnitStatus(struct Unit* unit, s8 cur){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return cur + info->skl_bonus;
}


s8 SpdGetter_UnitStatus(struct Unit* unit, s8 cur){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return cur + info->spd_bonus;
}


s8 DefGetter_UnitStatus(struct Unit* unit, s8 cur){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return cur + info->def_bonus;
}


s8 ResGetter_UnitStatus(struct Unit* unit, s8 cur){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return cur + info->res_bonus;
}


s8 LckGetter_UnitStatus(struct Unit* unit, s8 cur){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return cur + info->lck_bonus;
}


s8 MovGetter_UnitStatus(struct Unit* unit, s8 cur){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	// For Status
	if( info->is_gravity )
		return 0;
	else
		return cur + info->mov_bonus;
}
