#include "gbafe-chax.h"

int _IsPointer(u32 it){
	
	return 0 != (0x08000000 & it);
	
}