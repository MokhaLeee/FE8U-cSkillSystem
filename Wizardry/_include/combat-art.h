#pragma once

struct CombatArtInfo {
	u16 msg_name;
	u16 msg_desc;
	u8 weapon_type;
	u8 is_lengency : 1;
	u8 is_magic : 1;
	s16 cost;
	s16 mt;
	s16 hit;
	s16 avo;
	s16 crit;
	s8 range_bouns;
};
extern struct CombatArtInfo const* const CombatArtInfoTable[0x100];



// Core
const struct CombatArtInfo* GetCombatArtInfo(u8 index);
u8* GetCombatArtList(struct Unit* unit);
int UnitHasCombatArt(struct Unit* unit);
int CanUnitUseCombatArt(struct Unit* unit, u8 index);



// Menu Panel
void StartMenuPanel_CombatArt(struct MenuProc*, struct Unit*, u8 x, u8 y);
void UpdateMenuPanel_CombatArt(const struct CombatArtInfo*);
void EndMenuPanel_CombatArt();
