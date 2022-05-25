#pragma once


// For ROM Table, see skill-system.h
// Level-based class combat-arts
extern const struct LevelBasedSkillList_t LevelCASword_ClassList[], LevelCALance_ClassList[], LevelCAAxe_ClassList[], LevelCABow_ClassList[], LevelCABMag_ClassList[], LevelCAWMag_ClassList[];

// Level-based unit combat-art
extern const struct LevelBasedSkillList_t LevelCASword_CharList[], LevelCALance_CharList[], LevelCAAxe_CharList[], LevelCABow_CharList[];


struct CombatArtInfo {
	/* 00 */ u16 msg_name;
	/* 02 */ u16 msg_desc;
	/* 04 */ const void* icon;
	
	/* 08 */ u32 is_lengency : 1;
	
			// need judge for art-varied atk bonus
			// this will get additional calc in Pre-Battle Calc
			 u32 atk_bonus : 1;	
			
			// If set, attack based on unit magic power
			 u32 is_magic : 1;
			 
			 // effect to class
			 u32 eff_heavy : 1;
			 u32 eff_ride : 1;
			 u32 eff_dragon : 1;
			 u32 eff_monster : 1;
			 u32 eff_fly : 1;
			 u32 eff_all : 1;
			 
			 // If set, mean as can-counter or battle-hit, etc. special calc
			 u32 special_eff : 1;
			 
			 // If set, unit will double attack.
			 u32 double_attack : 1;
			 
			 // If set, give enimy Gravity debuff
			 u32 is_gravity : 1;
			 
			 // If set, give debuff def
			 u32 debuff_def : 1;
			 u32 debuff_res : 1;
			 u32 debuff_atk : 1;
			 
			 u32 debuff_Silence : 1;
			 
			 // for 近距离连射, etc
			 u32 unnormal_range : 1;
			 
			 // if AOE debuff, then effect to 1x1 targets
			 u32 AOE_Debuff : 1;
			 
	/* 0C */ u8 weapon_type;
	/* 0D */ s8 range_bouns;
	/* 0E */ s16 cost;
	/* 10 */ s16 mt;
	/* 12 */ s16 hit;
	/* 14 */ s16 avo;
	/* 16 */ s16 crit;
	/* 18 */
	
};

extern struct CombatArtInfo const* const CombatArtInfoTable[0x100];



// Core
const struct CombatArtInfo* GetCombatArtInfo(u8 index);
u8* GetCombatArtList(struct Unit* unit);
int UnitHasCombatArt(struct Unit* unit);
int CanUnitUseCombatArt(struct Unit* unit, u8 index);
int CanUnitWithWeaponUseCombatArt(struct Unit* unit, u16 weapon, u8 index);

int RemoveCombatArt(struct Unit*, const u8 index);
int AddCombatArt(struct Unit*, const u8 index);

int GetUnitTotalCombatArtsCount(struct Unit* unit);
const void* GetCombatArtIconGfx(int index);

// For Battle-Ext-Flag
void EnableCombatArtFlag(struct Unit* unit, u8 combatArt_index);
void DisableCombatArtFlag();
int IsFlagCombatArt(struct Unit* unit, u8 combatArt_index);


// Menu Panel
void StartMenuPanel_CombatArt(struct MenuProc*, struct Unit*, u8 x, u8 y);
void UpdateMenuPanel_CombatArt(const struct CombatArtInfo*);
void EndMenuPanel_CombatArt();



// Target Select
ProcPtr StartCombatTargetSelection(const struct SelectInfo*);
