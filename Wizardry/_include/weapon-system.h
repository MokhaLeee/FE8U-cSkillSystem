#pragma once

struct NewWRanksROM{
	u8 rank_ride;
	u8 rank_fly;
	u8 rank_heavy;
};


extern const struct NewWRanksROM CharWRanksTable[0x100]; 
extern const struct NewWRanksROM ClassWRanksTable[0x100]; 


u8 GetWExp(struct Unit* unit, const u8 wType);
void SetWExp(struct Unit* unit, const u8 wType, u8 exp);



int NewGetBattleUnitUpdatedWeaponExp(struct BattleUnit* bu, u8 WType);


