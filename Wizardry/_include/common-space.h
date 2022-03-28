#pragma once

struct BattleFlagExt{
	/* 00 */u8 isCombat:1;
	/* 00 */ u8 pad00:7;
	
	/* 01 */ u8 ActorId;
	/* 02 */ u8 artId;
	
	/* 03 */ u8 free[0x10 - 0x03];
};

extern struct BattleFlagExt* gpBattleFlagExt;	// 0x10 long



enum{
	MAX_SIZE_COMMON_SAPCE = 0x40,
};


//extern void* gpCommonSpace;
void Reset_CommonSpace(void);

/*************** Useage: *******************
a common space and will save in Suspend data, which defined as "gpCommonSaveSu" in _Val_Global.event

However, here we does not make a direct definition. If you want to use it, you need:


// ================================
#include "gbafe-chax.h"
extern u8* gpCommonSpace;
// ================================

You can also define it as any struct as you need.

Tips:
1. Don't forget use function "Reset_CommonSpace()" if you want to make your own system!
2. Don't forget to check out whether Common-Space is used on current timing!
3. Don't forget to add notes as below anytime you use common space!



Notes urrent usage with time node of occupation and release:
	
	
	
********************************************/ 