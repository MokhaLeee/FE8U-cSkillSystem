#include "gbafe-chax.h"

void AiFillUnitStandingRangeWithWeapon(struct Unit* unit, u16 item){
	
	BmMapFill(gBmMapRange,NU_RANGE_MAP);
	
	// <!> not unit! here is target! we should judge for AI!
	AddMapMaster(unit->xPos, unit->yPos, ItemRange2Mask(item, gActiveUnit), NU_RANGE_MAP);
}



int AiGetUnitReachWeightWithEquippedWeapon(s8 x, s8 y, struct Unit* unit){
	
	int distance = RECT_DISTANCE(x, y, unit->xPos, unit->yPos);
	u16 weapon = GetUnitEquippedWeapon(unit);
	
	if( distance <= RangeMaxGetter(weapon, unit) )
		if( distance >= RangeMinGetter(weapon, unit) )
			return 50;
	
	return 0;
}