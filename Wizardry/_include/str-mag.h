#pragma once
#include "gba/types.h"

enum{
	MAG_OFFSET = 0x3A,		// for unit, use as unit->_u3A
	MAG_UP_OFFSET = 0x7F	// for level-up/promo, bu+0x7F
};

struct Stat_CharTable{
	s8 base;
	s8 growth;
};

typedef struct Stat_CharTable Stat_CharTable_t;
extern Stat_CharTable_t UnitMagicTable[];

struct Stat_ClassTable{
	s8 base;
	s8 growth;
	s8 cap;
	s8 promo_bonus;
};

typedef struct Stat_ClassTable Stat_ClassTable_t;
extern Stat_ClassTable_t ClassMagicTable[];

extern u8 ITEM_MAG_BOOSTER_ID; // 0xBC

// =========================
// ======= Get-funcs =======
// =========================

// Check For battle
int CheckMagAttack(struct BattleUnit*);

// Get unit mag pointer, you can use as *GetMagAt(unit) to get unit magic power
s8* GetMagAt(struct Unit*);

// Get BattleUnit mag up, for level up and promotion
s8* GetBu_ChangeMagAt(struct BattleUnit*);

// Get Mag Unit Base
int GetUnitMagBase(u8 charId);

// Get Mag class Base
int GetClassMagBase(u8 classId);

// Get Mag cap
int GetClassMagCap(u8 classId);

// Get Mag class promo bonus
int GetClassPromoBonusMag(u8 classId);

// Get Mag class growth for auto-level
int GetClassMagicGrowth(u8 classId);

// Get Mag unit growth
int GetUnitMagGrowth(struct Unit*);
