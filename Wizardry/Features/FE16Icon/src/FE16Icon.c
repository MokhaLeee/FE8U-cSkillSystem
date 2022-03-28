#include "gbafe-chax.h"

extern u16 const* const IconSheet_FE16Mastery[];

const void* GetFE16MasteryIconGfx(int index){
	
	if( index < MASTERY_ICON_MAX )
		return IconSheet_FE16Mastery[index];
	
	else
		return NULL;
	
}