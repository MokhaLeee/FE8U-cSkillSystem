#pragma once

enum{
	
	// attributes for BattleHitExt.attr
	ATTR_HITEXT_NONE = 0,
	ATTR_HITEXT_SKILLACT_ATK = 1 << 1,
	ATTR_HITEXT_SKILLACT_DEF = 1 << 2,
	ATTR_HITEXT_COMBAT_ART = 1 << 3,
	
	
	// return value for battle-can-counter modular check
	NORMAL_COUNTER = 0,
	NULL_COUNTER = 1,
	FORCE_COUNTER = -1,
};

struct BattleHitExt{
	
	u8 attr;
	u8 atk_skills[3];
	u8 def_skills[3];
	
	u8 pad[0x10 - 0x7];
};

extern struct BattleHitExt *BattleHitExtArray;
extern struct BattleHitExt **BattleHitExtCur;


// Expand for vanilla array
enum{
	BATTLE_HIT_MAX_EXPANSION = 0x20,
};

extern struct BattleHit *gBattleHitArrayReAt;



// New Flag

struct BattleFlagExt{
			// judge for combat-art
	/* 00 */ u8 isCombat : 1;
	
			// if combat-art atk hitted, set this bit
			// for post-action debuff
			 u8 combatArt_hitted : 1;
			 
			 // for DoubleLion self-dmg
			 u8 doubleLion_activited : 1;

	/* 01 */ u8 combatArt_id;
	/* 02 */ u8 combat_unit;	// unit index of combat art actor 
	/* 03 */ u8 hit_count;
	/* 04 */ u8 pad_04[0x10 - 0x04];
};

extern struct BattleFlagExt* gpBattleFlagExt;	// 0x10 long



// Battle Forcast rework
struct Proc_BKSEL{
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 pad[0x2C - 0x29];
	/* 2C */ int32_t timer;
	/* 30 */ u8 unk_30;
	/* 31 */ u8 unk_31;
	/* 32 */ u8 mode;		// 1 = Standard, 2 = Detailed
	/* 33 */ u8 stat;		// maybe 1 when gfx are ready
	/* 34 */ u8 wake_up;	// if 0, main loop goto idle mode
	/* 35 */ s8 pos;		// left = 1, middle = 0, right = -1
	/* 36 */ u8 unk_36[0x38 - 0x36];
	/* 38 */ struct TextHandle texts[3];
	/* 50 */ u8 act_hit;
	/* 51 */ u8 tar_hit;
	/* 52 */ u8 act_eff;	// bool
	/* 53 */ u8 tar_eff;	// bool
	
	/* 54 */ u8 pad_54[0x68 - 0x54];
	/* 68 */ u8 caIcon_xPos;
	/* 69 */ u8 caIcon_yPos;
	/* 6A */ u8 obj_arrow_timer;
};



// functions
void ResetBattleFlagExt(void);
void ClearBattleHitExt(void);

void BattleHitExt_SetAttr(int attr);
int SetBattleHitExt_AtkSkill(u8 skill_id);
int SetBattleHitExt_DefSkill(u8 skill_id);

int CheckCanDouble(struct BattleUnit* actor, struct BattleUnit* target);
