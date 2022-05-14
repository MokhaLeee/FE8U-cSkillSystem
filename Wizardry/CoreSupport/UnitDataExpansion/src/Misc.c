#include "gbafe-chax.h"

void MSa_SaveUnitExpa(void* dest, unsigned size){
	
	int read_size = (UNIT_EXPA_SIZE * UNIT_EXPA_MAX) > size
		? size
		: UNIT_EXPA_SIZE * UNIT_EXPA_MAX;
	
	WriteAndVerifySramFast( (const void*)gpUnitExpaData, dest, read_size);
}

void MSa_LoadUnitExpa(const void* src, unsigned size){
	
	int read_size = (UNIT_EXPA_SIZE * UNIT_EXPA_MAX) > size
		? size
		: UNIT_EXPA_SIZE * UNIT_EXPA_MAX;
	
	(*ReadSramFast)(src, (void*)gpUnitExpaData, read_size);
}

