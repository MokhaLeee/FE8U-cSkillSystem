#pragma once



enum{
	MAX_SIZE_COMMON_SAPCE = 0x40,
};


//extern void* gpCommonSpace;
void ResetCommonSpace(void);


/*************** Useage: *******************
a common space and will save in Suspend data, which defined as "gpCommonSaveSu" in _Val_Global.event

However, here we does not make a direct definition. If you want to use it, you need:


// ================================
#include "gbafe-chax.h"
extern u8* gpCommonSpace;
// ================================

You can also define it as any struct as you need.

Tips:
1. Don't forget use function "ResetCommonSpace()" if you want to make your own system!
2. Don't forget to check out whether Common-Space is used on current timing!
3. Don't forget to add notes as below anytime you use common space!



Notes urrent usage with time node of occupation and release:
	
	
	
********************************************/ 