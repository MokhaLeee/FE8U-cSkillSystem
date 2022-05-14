#include "gbafe-chax.h"

void MSu_SaveUnitStatus(void* dest, const unsigned size){
	
	int count = 0;
	
	for( int i = 0; i < FACTION_PURPLE + 4; i++ ){
		
		struct Unit* unit = GetUnit(i+1);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		gGenericBuffer[count] = *(0x30 + (u8*)unit);
		
		// avoid over-flow
		if( ++count > size )
			return;
	}
	
	WriteAndVerifySramFast( (void*)gGenericBuffer, dest, size);
}

void MSu_LoadUnitStatus(const void* src, const unsigned size){
	
	int count = 0;
	
	(*ReadSramFast)(src, (void*)gGenericBuffer, size);
	
	for( int i = 0; i < FACTION_PURPLE + 4; i++ ){
		
		struct Unit* unit = GetUnit(i+1);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		*(0x30 + (u8*)unit) = gGenericBuffer[count];
		
		// avoid over-flow
		if( ++count > size )
			return;
	}
}