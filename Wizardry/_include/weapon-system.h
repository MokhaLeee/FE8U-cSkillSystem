#pragma once

enum{
	ITYPE_BMAG = ITYPE_ANIMA,
	ITYPE_WMAG = ITYPE_STAFF,
	ITYPE_RIDE = 0x0D,
	ITYPE_FLY = 0x0E,
	ITYPE_HEAVY = 0x0F,
	ITYPE_CLASS = 0x10,
};

extern const u8 gCanUnitUseAllTypeWeapon;

u8 GetWExp(struct Unit* unit, const u8 wType);
int GetClassBaseWExp(u8 class_id, const u8 wType);
void SetWExp(struct Unit* unit, const u8 wType, u8 exp);
void AddWExp(struct Unit* unit, const u8 wType, u8 exp);
u16 GetWTypeMokhaIconIndex(u8 wType);



int NewGetBattleUnitUpdatedWeaponExp(struct BattleUnit* bu, u8 WType);
s8 NewHasBattleUnitGainedWeaponLevel(struct BattleUnit* bu, u8 WType);
s8 NewBattleUnit_ShouldDisplayWRankUp(struct BattleUnit *bu, u8 WType);


// Class Rank
void SetUnitMasterClass(struct Unit* unit, u8 class_id);
int IsClassMastered(struct Unit* unit, u8 class_id);
u8 GetClassRankExpGain(u8 class_id);

