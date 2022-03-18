#pragma once
#include "gbafe.h"

#define MAKE_ITEM(id,use) (id&0xFF)|((use&0xFF)<<8)
#define ITEM_USE(item) ( (item>>8) & 0xFF )
#define ITEM_ID(item) (item & 0xFF) 



struct Proc_ItemSimple {
	
	/* 00 */ PROC_HEADER;
	/* 2C */ void (*effect)(struct Unit*, uint16_t item);
	/* 30 */ u32 item;
	/* 34 */ struct Unit* unit;
	/* 38 */ u32 timer;
	/* 4C */ u8 x, y, width, height;
	/* 50 */ char* str;
};


int IsItemEffectSimple(void* func);
const void* ItemSimpleEffectFilter(void* func);


extern const struct ProcCmd gProc_PrepItemSimpleEffect[];
extern const struct ProcCmd gProc_ActionItemSimpleEffect[];


typedef int (*func_t1)(struct Unit*, uint16_t item);
typedef void (*func_t2)(struct Proc_PrepItemUse*, uint16_t item);
typedef void (*func_t3)(struct Unit*, uint16_t item);
typedef void (*func_t4)(ProcPtr);

extern const func_t1 ItemPrepUsabilityTable[0xFF];
extern const func_t2 ItemPrepEffectTable[0xFF];
extern const func_t1 ItemMenuUsabilityTable[0xFF];
extern const func_t3 ItemMenuEffectTable[0xFF];
extern const func_t4 ItemActionEffectTable[0xFF];

#undef func_t1
#undef func_t2
#undef func_t3
#undef func_t4
