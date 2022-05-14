#include "gbafe-chax.h"

s8 PowGetter_UnitStatus(struct Unit* unit){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return info->pow_bonus;
}


s8 MagGetter_UnitStatus(struct Unit* unit){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return info->mag_bonus;
}


s8 SklGetter_UnitStatus(struct Unit* unit){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return info->skl_bonus;
}


s8 SpdGetter_UnitStatus(struct Unit* unit){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return info->spd_bonus;
}


s8 DefGetter_UnitStatus(struct Unit* unit){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return info->def_bonus;
}


s8 ResGetter_UnitStatus(struct Unit* unit){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return info->res_bonus;
}


s8 LckGetter_UnitStatus(struct Unit* unit){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return info->lck_bonus;
}


s8 MovGetter_UnitStatus(struct Unit* unit){
	
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	return info->mov_bonus;
}
