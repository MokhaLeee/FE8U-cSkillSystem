#pragma once
#include "gbafe.h"

/*
ideas:
1. gLevelUpStats only save status-up, not save status-base
2. use status-screen TextHandle as here text struct
*/

// for stat id
enum{
	LU_HP  = 0,
	LU_STR = 1,
	LU_MAG = 2,
	LU_SKL = 3,
	LU_SPD = 4,
	
	LU_LCK = 5,
	LU_DEF = 6,
	LU_RES = 7,
	LU_CON = 8,
	LU_MOV = 9,
	LU_STAT_MAX = 10,
	
};

struct new_LevelUpStats{
	/* Total 0x24 */
	/* 00 */ struct BattleUnit* bu;
	s8 stat_up[LU_STAT_MAX];
};

extern struct new_LevelUpStats gLevelUpStatsBase; // 0x2020114



#ifndef gStatScreen
	extern struct StatScreenSt gStatScreen;	// 0x2003BFC in FE8U
#endif

#define LU_text(id) (&gStatScreen.text[id])

// For TextHandle entries
enum{
	LUTEXT_STR_HP  = LU_HP,		// 0
	LUTEXT_STR_STR = LU_STR, 	// 1
	LUTEXT_STR_MAG = LU_MAG,	// 2
	LUTEXT_STR_SKL = LU_SKL,	// 3
	LUTEXT_STR_SPD = LU_SPD,	// 4
	
	LUTEXT_STR_LCK = LU_LCK,	// 5
	LUTEXT_STR_DEF = LU_DEF,	// 6
	LUTEXT_STR_RES = LU_RES,	// 7
	LUTEXT_STR_CON = LU_CON,	// 8
	LUTEXT_STR_MOV = LU_MOV,	// 9
	
	// numbers
	LUTEXT_NUM_HP  = LU_STAT_MAX + LU_HP,	// 10
	LUTEXT_NUM_STR = LU_STAT_MAX + LU_STR,	// 11
	LUTEXT_NUM_MAG = LU_STAT_MAX + LU_MAG,	// 12
	LUTEXT_NUM_SKL = LU_STAT_MAX + LU_SKL,	// 13
	LUTEXT_NUM_SPD = LU_STAT_MAX + LU_SPD,	// 14
	
	LUTEXT_NUM_LCK = LU_STAT_MAX + LU_LCK,	// 15
	LUTEXT_NUM_DEF = LU_STAT_MAX + LU_DEF,	// 16
	LUTEXT_NUM_RES = LU_STAT_MAX + LU_RES,	// 17
	LUTEXT_NUM_CON = LU_STAT_MAX + LU_CON,	// 18
	LUTEXT_NUM_MOV = LU_STAT_MAX + LU_MOV,	// 19
	
	// misc
	LUTEXT_STR_CLASS = LUTEXT_NUM_MOV + 1,	// 20
	LUTEXT_STR_LEVEL = LUTEXT_STR_CLASS + 1,// 21
	LUTEXT_NUM_LEVEL = LUTEXT_STR_LEVEL + 1	// 22
};






// Level Up Table
struct LU_tableUnit{
	u16 text_id;
	u8 x;
	u8 y;
	s8 (*Get_Base) (struct BattleUnit*);
};

typedef struct LU_tableUnit LU_tableUnit_t;

#define TABLE_ON LevelUpTable
#define TABLE_OFF LevelUpTable_Off

extern const LU_tableUnit_t LevelUpTable[];
extern const LU_tableUnit_t LevelUpTable_Off[];

// tsa
extern u16 LU_table_TSA[];
