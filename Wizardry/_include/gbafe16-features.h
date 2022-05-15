#pragma once

#define SKILL_ICON(aSkillId) ((1 << 8) + (aSkillId))
#define MASTERY_ICON(aSkillId) ((2 << 8) + (aSkillId))
#define COMBAT_ART_ICON(aSkillId) ((3 << 8) + (aSkillId))

enum{
	MASTERY_ICON_SWORD = 0,
	MASTERY_ICON_LANCE = 1,
	MASTERY_ICON_AXE = 2,
	MASTERY_ICON_BOW = 3,
	MASTERY_ICON_FAITH = 4,
	
	MASTERY_ICON_REASON = 5,
	MASTERY_ICON_AUTH = 8,
	MASTERY_ICON_RIDE = 9,
	MASTERY_ICON_FLY = 10,
	MASTERY_ICON_HEAVY = 11,
	MASTERY_ICON_BRAWL = 12,
	
	MASTERY_ICON_MONSTER = 13,
	MASTERY_ICON_DRAGON = 14,
	
	MASTERY_ICON_MAX,
	MASTERY_ICON_NULL = 0xFF,
};




// Map Anims
void StartMapAnim_Gravity(struct Unit*, ProcPtr);