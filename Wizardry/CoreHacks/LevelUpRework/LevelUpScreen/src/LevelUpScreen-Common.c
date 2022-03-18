#include "gbafe.h"
#include "common.h"
#include "level-up.h"
#include "level-up-rework.h"
#include "str-mag.h"

typedef s8 (*Get) (struct BattleUnit*);
static s8 LevelUp_GetLvBase (struct BattleUnit* bu){ return bu->levelPrevious;}
static s8 LevelUp_GetHpBase (struct BattleUnit* bu){ return bu->unit.maxHP;}
static s8 LevelUp_GetPowBase(struct BattleUnit* bu){ return bu->unit.pow;}
static s8 LevelUp_GetMagBase(struct BattleUnit* bu){ 
	return *GetMagAt(&bu->unit);
}
static s8 LevelUp_GetSklBase(struct BattleUnit* bu){ return bu->unit.skl;}
static s8 LevelUp_GetSpdBase(struct BattleUnit* bu){ return bu->unit.spd;}
static s8 LevelUp_GetLckBase(struct BattleUnit* bu){ return bu->unit.lck;}
static s8 LevelUp_GetDefBase(struct BattleUnit* bu){ return bu->unit.def;}
static s8 LevelUp_GetResBase(struct BattleUnit* bu){ return bu->unit.res;}
static s8 LevelUp_GetConBase(struct BattleUnit* bu){ return bu->unit.pCharacterData->baseCon + bu->unit.pClassData->baseCon;}
static s8 LevelUp_GetMovBase(struct BattleUnit* bu){ 
	return bu->unit.pClassData->baseMov;
}


// Anime-On
const LU_tableUnit_t LevelUpTable[] = {
	[LU_HP]  = {			// 0
		0x4E9, 2, 9,
		LevelUp_GetHpBase
	},
	
	[LU_STR] = {			// 1
		0x4FE, 2, 11,
		LevelUp_GetPowBase
	},
	
	[LU_MAG]{				// 2
		0x4FF, 2, 13,
		LevelUp_GetMagBase
	},
	
	[LU_SKL] = {			// 3
		0x4EC, 2, 15,
		LevelUp_GetSklBase
	},
	
	[LU_SPD] = {			// 4
		0x4ED, 2, 17,
		LevelUp_GetSpdBase
	},
	
	[LU_LCK] = {
		0x4EE, 10, 9,
		LevelUp_GetLckBase
	},
	
	[LU_DEF] = {
		0x4EF, 10, 11,
		LevelUp_GetDefBase
	},
	
	[LU_RES] = {
		0x4F0, 10, 13,
		LevelUp_GetResBase
	},
	
	[LU_CON] = {
		0x4F7, 10, 15,
		LevelUp_GetConBase
	},
	
	[LU_MOV] = {
		0x4F6, 10, 17,
		LevelUp_GetMovBase
	}
};


// Anim-Off
const LU_tableUnit_t LevelUpTable_Off[] = {
	[0] = {						// lv
		0x4E7, 9, 0,
		LevelUp_GetLvBase
	},
	
	[LU_HP + 1]  = {			// 0+1
		0x4E9, 1, 4,
		LevelUp_GetHpBase
	},
	
	[LU_STR + 1] = {			// 1+1
		0x4FE, 1, 6,
		LevelUp_GetPowBase
	},
	
	[LU_MAG + 1]{				// 2+1
		0x4FF, 1, 8,
		LevelUp_GetMagBase
	},
	
	[LU_SKL + 1] = {			// 3+1
		0x4EC, 1, 10,
		LevelUp_GetSklBase
	},
	
	[LU_SPD + 1] = {			// 4+1
		0x4ED, 1, 12,
		LevelUp_GetSpdBase
	},
	
	[LU_LCK + 1] = {
		0x4EE, 9, 4,
		LevelUp_GetLckBase
	},
	
	[LU_DEF + 1] = {
		0x4EF, 9, 6,
		LevelUp_GetDefBase
	},
	
	[LU_RES + 1] = {
		0x4F0, 9, 8,
		LevelUp_GetResBase
	},
	
	[LU_CON + 1] = {
		0x4F7, 9, 10,
		LevelUp_GetConBase
	},
	
	[LU_MOV + 1] = {
		0x4F6, 9, 12,
		LevelUp_GetMovBase
	}

};