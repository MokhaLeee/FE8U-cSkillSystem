#pragma once
// level-up.h
#ifndef gMapAnimData
#define gMapAnimData gCurrentMapAnimState
#endif // gMapAnimData

#define MAX_STATUS_LEVELUP 0xA

enum{
	STAT_UP_LV  = 0,
	STAT_UP_HP, 	// 1
	STAT_UP_POW,	// 2
	
	// new
	STAT_UP_MAG,
	
	STAT_UP_SKL,	// 3 +1 as for below
	STAT_UP_SPD, 	// 4 +1
	STAT_UP_LCK,	// 5 +1
	STAT_UP_DEF, 	// 6 +1
	STAT_UP_RES, 	// 7 +1
	STAT_UP_CON,	// 8 +1
	
	// new
	STAT_UP_MOV,		// 10
	STAT_UP_STR_CLASS,	// 11
	STAT_UP_STR_LV,		// 12
	STAT_UP_STAT_LV		// 13
};

enum{
	STAT_NAME_LV  = 0,
	STAT_NAME_EXP = 1,
	STAT_NAME_HP  = 2,
	STAT_NAME_STR = 3,
	STAT_NAME_MAG = 4,
	STAT_NAME_SKL = 5,
	STAT_NAME_SPD = 6,
	STAT_NAME_DEF = 7,
	STAT_NAME_RES = 8,
	STAT_NAME_LCK = 9,
	STAT_NAME_CON = 10
};
extern const u16 StatNames[];


// =================
// === ANIME-OFF ===
// =================

struct Proc_MapAnimLevelUp{ // LevelUpScreen
	/* 00 */ PROC_HEADER;
	/* 2A */ u8 pad_2A[0x2E - 0x2A];
	/* 2E */ s16 actor_id;
	/* 30 */ u8 stat_cur;		// stat index
	/* 31 */ u8 time_delay;
	/* 32 */ u16 yPos;
	/* 34 */ u16 pad_34;
	/* 36 */ u16 unk_36;
	/* 38 */ u8 pad_38[0x6C - 0x38];
};

typedef struct Proc_MapAnimLevelUp Proc_MapAnimLevelUp_t;


struct WindowSet_AnimOff{
	/* 00 */ u8 x;
	/* 01 */ u8 y;
	/* 04 */ u32* str_id[2];
	/* Total: 0C */
};

extern const struct WindowSet_AnimOff gMapAnimLevelUpStatLabelLocationTable[];











// ================
// === ANIME-ON ===
// ================
struct Proc_EkrLevelUp{ // LevelUpScreen
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 pad_29;
	/* 2A */ u8 promo; // level up = 0, promo = 1
	/* 2B */ u8 pad_2B;
	/* 2C */ s16 cnt;	// a timer
	/* 2E */ s16 stat_id;
	/* 30 */ u8 pad_30[0x44 - 0x30];
	/* 44 */ int unk_44;
	/* 48 */ int unk_48;
	/* 4C */ int unk_4C;
	/* 50 */ int unk_50;
	/* 54 */ u8 pad_54[0x5C - 0x54];
	/* 5C */ void* gAISMain;
	/* 60 */ void* AIS_struct;
	
};
// ClassMagicTable[unit->pClassData->number]
typedef struct Proc_EkrLevelUp Proc_EkrLevelUp_t;





// TextHandle arr
extern struct TextHandle gUnknown_020176A0[]; 	// at least 10
extern struct TextHandle gSomeTextStruct[];		// at least 10