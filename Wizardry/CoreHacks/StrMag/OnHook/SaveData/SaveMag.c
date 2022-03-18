#include "gbafe.h"
#include "str-mag.h"


void MSa_SaveUnitMag(void* dest, unsigned size){
	u8* DestCur = dest;
	int count = 1;
	
	for( u8 i = 0; i < 0x3E; i++  )
	{
		struct Unit* unit = GetUnit(i + 1 + FACTION_BLUE);
		if( NULL == unit )
			continue;
		
		WriteAndVerifySramFast( (const void*)GetMagAt(unit), DestCur++, 1);
		
		// avoid over-flow
		if( ++count > size )
			return;
	}

}


void MSa_LoadUnitMag(void* src, unsigned size){
	u8* SrcCur = src;
	int count = 1;
	
	for( u8 i = 0; i < 0x3E; i++  )
	{
		struct Unit* unit = GetUnit(i + 1 + FACTION_BLUE);
		if( NULL == unit )
			continue;
		
		(*ReadSramFast)(SrcCur++, (void*)GetMagAt(unit), 1);
		
		// avoid over-flow
		if( ++count > size )
			return;
	}

}



void MSu_SaveUnitMag(void* dest, unsigned size){
	u8* DestCur = dest;
	int count = 1;
	
	for( int i=0; i < FACTION_PURPLE + 4; i++ ){
		
		struct Unit* unit = GetUnit(i+1);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		WriteAndVerifySramFast( (const void*)GetMagAt(unit), DestCur++, 1);
		
		// avoid over-flow
		if( ++count > size )
			return;
	}
	
}



void MSu_LoadUnitMag(void* src, unsigned size){
	
	u8* SrcCur = src;
	int count = 1;
	
	for( int i = 0; i < FACTION_PURPLE +4; i++  ){
		struct Unit* unit = GetUnit(i + 1);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		(*ReadSramFast)(SrcCur++, (void*)GetMagAt(unit), 1);
		
		// avoid over-flow
		if( ++count > size )
			return;
	}
}