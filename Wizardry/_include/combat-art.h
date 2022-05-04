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


enum{
	COMBATART_LIST_MAXNUM = 0x20,
};
 
struct CombatArtList{
	// temperary ram list
	u8 unit_id;
	u8 count;
	u8 list[COMBATART_LIST_MAXNUM];
	
};


struct CombatArtMasteryList{
	u8 combat_E[2];
	u8 combat_D[2];
	u8 combat_C[2];
	u8 combat_B[2];
	u8 combat_A[2];
	u8 combat_S[2];
};
struct RomCombatArtList{
	struct CombatArtMasteryList CA_Sword, CA_Axe, CA_Bow, CA_Fist, CA_Misc;
};
extern const struct RomCombatArtList CharCombatArtList[0x100];


struct WpnCombatArtList{
	u8 ca[3];
};
extern const struct WpnCombatArtList WeaponCombatArtList[0x100];



// Core
struct CombatArtList* BuildCombatArtList(struct Unit* unit);
struct CombatArtList* GetCombatArtList(struct Unit* unit);
int UnitHasCombatArt(struct Unit*);
int CanUnitUseCombatArt(struct Unit*, u8 index);
const struct CombatArtInfo* GetCombatArtInfo(u8 index);
