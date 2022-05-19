#include "gbafe-chax.h"

extern char gCurrentTextString[];

static char* GetRangeStringCore(int min, int max);

// This is just for item, so we don't care about 
char* _GetItemDisplayRangeString(int item) {
	
	int min, max;
	
	if( 0 == ITEM_ID(item) )
		return "\0";
	
	max = GetItemMaxRange(item);
	min = GetItemMinRange(item);
	
	return GetRangeStringCore(min, max);
}




// This is for StatScreen Page2
char* _GetUnitRangeString(struct Unit* unit) {
	
	u16 item;
	int max, min;
	
	if( NULL == unit ) {
		if( NULL == gStatScreen.unit )
			return "ERROR";
		else
			unit = gStatScreen.unit;
	} // if( NULL == unit )
	
	item = GetUnitEquippedWeapon(unit);
	
	if( 0 == ITEM_ID(item) )
		return "\0";
	
	max = RangeMaxGetter(item, unit);
	min = RangeMinGetter(item, unit);
	
	return GetRangeStringCore(min, max);
	
}



static char* GetRangeStringCore(int min, int max){
	
	int len;
	char str[5];
	
	if( 0 == max )
		return GetStringFromIndex(0x522); // Mag/2
	
	if( min > max )
		return "--\0";
	
	if( min > 19 )
		min = 19;
	
	if( max > 20 )
		max = 19;
	
	
	// on get
	len = 0;
	
	if( min < 9 )
		str[len++] = '0' + min;
	else {
		
		str[len++] = '1';
		str[len++] = '0' + min - 10;
	
	} // if( min < 9 )
	

	if( min == max ) 
		goto goto_return;
	
	// -
	str[len++] = '-';
	
	if( max < 9 )
		str[len++] = '0' + max;
	else {
		
		str[len++] = '1';
		str[len++] = '0' + max - 10;
	
	} // if( max < 9 )
		
	
	goto_return:
	
	gCurrentTextString[5] = '\0';
	
	for ( int i = 0; i < 5; i++ ){
		
		if ( (i + len) < 5 )
			gCurrentTextString[i] = ' ';
		else
			gCurrentTextString[i] = str[i+len-5];
		
	}
	
	return gCurrentTextString;
}