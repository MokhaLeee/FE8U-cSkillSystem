#pragma once

struct PrepSkillsList{
	/* 00 */ u8 unit_index;
	/* 01 */ u8 total;
	/* 02 */ u8 skills[0x40 - 0x2];
};

// need gpCommonSpace!
extern struct PrepSkillsList* gpCommonSpace;


void InitPrepSkillsList(void);
struct PrepSkillsList* MakeUnitPrepSkillsList(struct Unit* unit);
struct PrepSkillsList* GetUnitPrepSkillsList(struct Unit* unit);

int PrepSkillAddRamSkillFromList(struct Unit* unit, u8 skill_id);


