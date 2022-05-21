#include "gbafe-chax.h"

void RNE_SaveSu(void* dest, unsigned size){
	WriteAndVerifySramFast( (const void*)gpRneState, dest, 0xC /*size*/ );
	return;
}

void RNE_LoadSu(const void* src, unsigned size){
	(*ReadSramFast)(src, (void*)gpRneState, 0xC /*size*/ );
	return;
}

