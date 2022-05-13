#include "gbafe-chax.h"

void MSa_SaveUnitExt(void* dest, unsigned size){
	
	int read_size = (UNIT_EXT_SIZE * UNIT_EXT_MAX) > size
		? size
		: UNIT_EXT_SIZE * UNIT_EXT_MAX;
	
	WriteAndVerifySramFast( (const void*)gpUnitExtData, dest, read_size);
}

void MSa_LoadUnitExt(const void* src, unsigned size){
	
	int read_size = (UNIT_EXT_SIZE * UNIT_EXT_MAX) > size
		? size
		: UNIT_EXT_SIZE * UNIT_EXT_MAX;
	
	(*ReadSramFast)(src, (void*)gpUnitExtData, read_size);
}

