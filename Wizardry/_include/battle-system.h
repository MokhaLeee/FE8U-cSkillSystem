#pragma once

enum{
	
	// attributes for BattleHitExt.attr
	ATTR_HITEXT_NONE = 0,
	ATTR_HITEXT_SKILLACT_ATK = 1 << 1,
	ATTR_HITEXT_SKILLACT_DEF = 1 << 2,
	ATTR_HITEXT_COMBAT_ART = 1 << 3,
};

struct BattleHitExt{
	
	u8 attr;
	u8 atk_skills[3];
	u8 def_skills[3];
	
	u8 pad[0x10 - 0x7];
};

extern struct BattleHitExt *BattleHitExtArray;
extern struct BattleHitExt **BattleHitExtCur;



struct BattleFlagExt{
	/* 00 */u8 isCombat:1;
	/* 00 */ u8 pad00:7;

	/* 01 */ u8 combatArt_id;
	
	/* 02 */ u8 pad02[0x10 - 0x02];
};

extern struct BattleFlagExt* gpBattleFlagExt;	// 0x10 long




// functions
void ResetBattleFlagExt(void);
void ClearBattleHitExt(void);

void BattleHitExt_SetAttr(int attr);
int SetBattleHitExt_AtkSkill(u8 skill_id);
int SetBattleHitExt_DefSkill(u8 skill_id);
