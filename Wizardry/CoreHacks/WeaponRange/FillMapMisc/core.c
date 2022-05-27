#include "gbafe-chax.h"

static int MaxRangeFilter(struct Unit* unit, u16 item){
	
	int rngMax; 
	
	rngMax = RangeMaxGetter(item,unit);
	
	if( 0 == rngMax )
		rngMax = GetUnitMagBy2Range(unit);
	
	return rngMax;
}




/*
BmMapFill(gMapMovement,-1);
BmMapFill(gMapRange,0);
FillMapForSingleItem(gActiveUnit,item);	// Now Fill map = gMapRange
DisplayMoveRangeGraphics(4); 		// staff=4; Wpn=2
*/
void FillMapForSingleItem(struct Unit* unit, u16 item){
	const u8 x = unit->xPos;
	const u8 y = unit->yPos;
	
	int rngMin = RangeMinGetter(item,unit);
	int rngMax = MaxRangeFilter(unit,item);

	MapAddInRange(x,y,rngMax,1);
	
	if( 0!=rngMin )
		MapAddInRange(x,y,rngMin-1,-1);
	
	return;
}

// GetItemReachBits
u32 ItemRange2Mask(u16 item, struct Unit* unit){
	
	u32 mask, diff, min, max;
	
	if( UNIT_VAILD_MOKHA_JUDGE(unit) ) { 
		
		// if no unit
		
		min = GetItemMinRange(item);
		max = GetItemMaxRange(item);
		
	}
	
	else {
		
		min = RangeMinGetter(item, unit);
		max = RangeMaxGetter(item, unit);
		
	}
	
	if( max < min )
		return 0;
	
	mask = 0;
	diff = max - min;
	
	for(int i=0; i <= max; i++)
	{
		if( i <= diff )
			mask = (mask << 1) |1;
		else
			mask = (mask << 1);
	}
	return mask;

}


void AddMapMaster(int x, int y, u32 mask, int null_vall) {
	
	// On Init
	int start, end, cur, pre, val_on, val_off;
	
	val_on = 1;
	val_off = null_vall - 1;
	
	// 先把0位置画上
	if( 0 == mask )
		return;
	else if ( 0b10 == (0b11 & mask) )
		MapAddInRange(x, y, 0, val_off);
	
	
	// start
	start = 0;
	
	for( int i = 0; i <= 32; i++ ) {
			
			pre = mask & 1;
			mask /= 2;
			cur = mask & 1;
			
			if ( cur == pre )
				continue;
			
			else if ( 1 == cur )
				start = i;
			
			else if ( 0 == cur ) {
				
				end = i;
				MapAddInRange(x, y, end, val_on);
				
				if ( 0 != start )
					MapAddInRange(x, y, start, val_off);
				
			}
			
			if ( 0 == mask )
				break;
			
	}
	
}





void ForEachUnitMaster( void(*func)(struct Unit*), u8*** work_map, int null_val) {
	
	if ( (gBmMapSize.x < 0) || (gBmMapSize.y < 0) )
		return;
	
	for( int y = 0; y < gBmMapSize.y; y++ )
		for( int x = 0; x < gBmMapSize.x; x++ ){
			
			if( null_val == (*work_map)[y][x] )
				continue;

			if( gBmMapUnit[y][x] )
				func( GetUnit(gBmMapUnit[y][x]) );
		}
	return;
	
}
