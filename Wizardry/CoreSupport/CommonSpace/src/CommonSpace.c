// ================================
#include "gbafe-chax.h"
extern u8* gpCommonSpace;
// ================================


// For ChapterInitHook
void ResetCommonSpace(void){
	
	for( int i = 0; i < MAX_SIZE_COMMON_SAPCE; i++ )
		gpCommonSpace[i] = 0;
	
}




// For ExpModularSave
void MSu_SaveCommonSpace(void* dest, unsigned size){
	WriteAndVerifySramFast( (const void*)gpCommonSpace, dest, size );
}

void MSu_SaveBattleFlagExt(void* dest, unsigned size){
	WriteAndVerifySramFast( (const void*)gpBattleFlagExt, dest, /* size */ 0x10 );
}


void MSu_LoadCommonSpace(const void* src, unsigned size){
	(*ReadSramFast)(src, (void*)gpCommonSpace, size);
}

void MSu_LoadBattleFlagExt(const void* src, unsigned size){
	(*ReadSramFast)(src, (void*)gpBattleFlagExt, /* size */ 0x10 );
}

