#pragma once

#include "gbafe.h"

/********************
we use unit support data in unit struct as skill list
unit->supports (+0x32) +6
and leave unit+0x38 as pad (for skill learning?)
********************/

#define SKILL_ICON(aSkillId) ((1 << 8) + (aSkillId))

enum{
	// unit skill list length
	UNIT_SKILL_COUNT = 6,
	
	// skill id range ( 1 ~ 0xFF )
	SKILL_MAX_COUNT = 100,
	
	// max count of skill fast tester list
	MAX_CNT_FAST_LIST = 0x1E,
};


// For make skill information list (main list)
struct SkillInfo {
	/* 00 */ u16 msg_desc;			// description text id
	/* 02 */ u8 pad_02[0x4 - 0x2];
	/* 04 */ const void* icon;		// icon gfx pointer	
};

extern struct SkillInfo const* const SkillInfoTable[];



/**
 * Checks whether a unit has a given skill
 * 
 * @param unit the unit
 * @param skillId the id of the skill to check for
 * @return non-zero if the unit has the given skill
 */
int (*SkillTester) (struct Unit*, u8 skill_id);
int JudgeSkill(struct Unit*, u8 skill_id);
int JudgeSkillFast(struct Unit*, u8 skill_id);



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



// Misc Getter
const void* GetSkillIconGfx(u8 skill_id);
int GetSkillDescMsg(u8 skill_id);
