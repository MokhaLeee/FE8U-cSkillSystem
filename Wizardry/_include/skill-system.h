#pragma once

#include "gbafe.h"

/********************
we use unit support data in unit struct as skill list
unit->supports (+0x32) +6
and leave unit+0x38 as pad (for skill learning?)
********************/

// #define SKILL_ICON(aSkillId) ((1 << 8) + (aSkillId))
#define SKILL_VALID(aSkillId) ( (aSkillId > 0) && (aSkillId < 0xFF) )

enum{
	// unit skill list length
	UNIT_SKILL_COUNT = 5, // tip: max support = 7, 2 Bytes free
	
	// skill id range ( 1 ~ 0xFF )
	SKILL_MAX_COUNT = 0x100,
	
	// max count of skill fast tester list
	MAX_CNT_FAST_LIST = 0x1E,
};


// for ROM skill
struct SkillClassList_t{
	
	/* 00 */ u8 default_rom_skill[2];
	/* 04 */ u8 master_rom_skill[2];
	/* 08 */ u8 default_ram_skill[2];
	/* 0C */ u8 master_ram_skill[4];
	/* 10 */
};

extern const struct SkillClassList_t ClassSkillRomList[];

struct SkillCharacterList_t{
	u8 rom_skill[2];
};

extern const struct SkillCharacterList_t CharacterSkillRomList[];





struct LevelBasedSkillList_t{

	/* 00 */ u8 E[3];
	/* 02 */ u8 D[3];
	/* 04 */ u8 C[3];
	/* 06 */ u8 B[3];
	/* 08 */ u8 A[3];
	/* 0A */ u8 S[3];
	/* 0C */
};

// Level-based class skills
extern const struct LevelBasedSkillList_t LevelSkillSword_ClassList[], LevelSkillLance_ClassList[], LevelSkillAxe_ClassList[], LevelSkillBow_ClassList[], LevelSkillBMag_ClassList[], LevelSkillWMag_ClassList[], LevelSkillRide_ClassList[], LevelSkillFly_ClassList[], LevelSkillHeavy_ClassList[];

// Level-based unit skills
extern const struct LevelBasedSkillList_t LevelSkillSword_CharList[], LevelSkillLance_CharList[], LevelSkillAxe_CharList[], LevelSkillBow_CharList[], LevelSkillBMag_CharList[], LevelSkillWMag_CharList[], LevelSkillRide_CharList[], LevelSkillFly_CharList[], LevelSkillHeavy_CharList[];







// For make skill information list (main list)
struct SkillInfo {
	/* 00 */ u16 msg_desc;			// description text id
	/* 02 */ u16 msg_name;
	/* 04 */ const void* icon;		// icon gfx pointer	
};

extern struct SkillInfo const* const SkillInfoTable[];


// WIP common icon
extern const u16 SkillIcon_WIP[];


/**
 * Checks whether a unit has a given skill
 * 
 * @param unit the unit
 * @param skillId the id of the skill to check for
 * @return non-zero if the unit has the given skill
 */
extern int (*SkillTester) (struct Unit*, const u8 skill_id);
int JudgeSkill(struct Unit*, const u8 skill_id);
int JudgeSkillFast(struct Unit*, const u8 skill_id);



// a RAM list to store unit total skill id list temporarily
struct SkillFastTesterList{
	/* 00 */ u8 unit_id;
	/* 01 */ u8 cnt;
	/* 02 */ u8 skills[MAX_CNT_FAST_LIST];
	/* End up to 0x20 */
};

extern struct SkillFastTesterList *gpSkillFastList0, *gpSkillFastList1;

struct SkillFastTesterList* GetOrMakeSklFastList(struct Unit*);
int GetSklFastListLen(struct Unit*);
void ResetSkillFastList(void);
void NullUnitSkills(struct Unit*);



// Misc
void ResetUnitRamSkillsList(struct Unit*);
int AddSkill(struct Unit*, int skill_id);
int RemoveSkill(struct Unit*, int skill_id);
const void* GetSkillIconGfx(int skill_id);
int GetSkillDescMsg(int skill_id);
int GetSkillNameMsg(int skill_id);
int GetUnitRamSkillCount(struct Unit*);

