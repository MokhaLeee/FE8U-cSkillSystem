#include "gbafe-chax.h"

// int GetItemReachBits(int item) 
// now defined as 
// u32 ItemRange2Mask(u16 item, struct Unit* unit);


int GetUnitWeaponReachBits(struct Unit* unit, int itemSlot) {
	int i, item, result = 0;

	if (itemSlot >= 0)
		return ItemRange2Mask(unit->items[itemSlot], unit);

	for (i = 0; (i < UNIT_ITEM_COUNT) && (item = unit->items[i]); ++i)
		if (CanUnitUseWeapon(unit, item))
			result |= ItemRange2Mask(item, unit);

	return result;
}


int GetUnitItemUseReachBits(struct Unit* unit, int itemSlot) {

	u32 mask = 0;
	
	if( itemSlot >= 0 ) {
		
		u16 item = unit->items[itemSlot];
		
		if ( !CanUnitUseItem(unit, item) )
			return REACH_NONE;
		
		mask = ItemRange2Mask(item, unit);
		
	}
		
	else {
		
		for( int i = 0; (i < UNIT_ITEM_COUNT) && unit->items[i]; i++ ) {
			
			u16 item = unit->items[i];
			
			if ( !CanUnitUseItem(unit, item) )
				continue;
			
			mask |= ItemRange2Mask(item, unit);
			
		} // for
		
	} // else
		
	return (int)mask;
}



int GetUnitStaffReachBits(struct Unit* unit) {
	
	u32 mask = 0;
	
	for( int i = 0; (i < UNIT_ITEM_COUNT) && unit->items[i]; i++ ) {
		
		u16 item = unit->items[i];
		
		if ( !CanUnitUseStaff(unit, item) )
			continue;
		
		mask = ItemRange2Mask(item, unit);
	}
	
	return (int)mask;
}






