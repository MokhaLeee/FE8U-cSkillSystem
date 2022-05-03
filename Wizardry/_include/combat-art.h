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

struct CombatArtMasteryList{
	
	/* 00 */ u8 combat_E[2];
	/* 02 */ u8 combat_D[2];
	/* 04 */ u8 combat_C[2];
	/* 06 */ u8 combat_B[2];
	/* 08 */ u8 combat_A[2];
	/* 0A */ u8 combat_S[2];
	/* 0C */
	
};

extern struct CombatArtInfo const* const CombatArtInfoTable[0x100];
extern const struct CombatArtMasteryList CharCombatArtList[0x100], ClassCombatArtList[0x100];

// Core
int UnitHasCombatArt(struct Unit*);
int CanUnitUseCombatArt(struct Unit*, u8 index);

