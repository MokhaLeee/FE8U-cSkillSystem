#pragma once

enum{
	// On draw config
	
	ON_DRAW_CONFIG_INIT = 0,
	ON_DRAW_CONFIG_UPDATE = 1,
};

enum{
	// Proc: Prep-SkillScreen's label
	LABEL_PREPSKILL_INIT = 0,
	LABEL_PREPSKILL_UNITLOOP,
	LABEL_PREPSKILL_STATSCREEN,
	LABEL_PREPSKILL_SUBMENU,
	LABEL_PREPSKILL_SUBMENU_END,
	LABEL_PREPSKILL_SUBLIST,
	
	LABEL_PREPSKILL_END,
};


enum{
	// Sub-menu items
	
	MENUITEM_PREPSKILL_SKILL = 0,
	MENUITEM_PREPSKILL_COMBAT,
	MENUITEM_PREPSKILL_BATTALION,
	
	MENUITEM_PREPSKILL_NULL = 0xFF,
};

enum{
	// list length
	PREPSKILL_LISTLEN_RAM = 5,
	PREPSKILL_LISTLEN_ROM = 10,
	PREPSKILL_LISTLEN_ALL = 15,
	PREPSKILL_LISTLEN_CA = 5,
	
};


enum{
	// Proc: Proc_PrepSkillSubList's label
	LABEL_PREPSLILLSLIST_INIT = 0,
	LABEL_PREPSLILLSLIST_IDLE,
	LABEL_PREPSLILLSLIST_REMOVE,
	LABEL_PREPSLILLSLIST_POST_REMOVE,
	LABEL_PREPSLILLSLIST_ADD,
	LABEL_PREPSLILLSLIST_POST_ADD,
	
	LABEL_PREPSLILLSLIST_END,
};


enum{
	
	// list type for proc-skill-sublist + 0x29
	PREP_SKLSUB_RIGHT = 0,
	PREP_SKLSUB_LEFT_RAM,
	PREP_SKLSUB_LEFT_ROM,
	PREP_SKLSUB_LEFT_CA,
	
	PREP_SKLSUB_MAXLIST,
	
	// state for Proc_PrepSkillSubList + 0x29
	STATE_PREPSUB_NORMAL,
	STATE_PREPSUB_REPLACE_INRIGHT,
	STATE_PREPSUB_REPLACE_INLEFT,
};

struct PrepSkillsList{
	/* 00 */ u8 unit_index;
	/* 01 */ u8 total[PREP_SKLSUB_MAXLIST];
	
	/* 05 */ 
	u8 skills_ram[PREPSKILL_LISTLEN_RAM];
	u8 skills_rom[PREPSKILL_LISTLEN_ROM];
	u8 skills_CombatArt[PREPSKILL_LISTLEN_CA];
	u8 skills_battalion;
	u8 skills_all[PREPSKILL_LISTLEN_ALL];
	
};


struct Proc_PrepSkillSubList{
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 state;
	
	/* 2C */ struct Unit* unit;
	/* 30 */ u8 skill_id_pre;	// only update on 
	/* 31 */ u8 list_index; // current index for skill list
	/* 32 */ u8 list_index_pre;
	/* 33 */ u8 list_type;
	/* 34 */ u8 list_type_pre;
};

// need gpCommonSpace!
extern struct PrepSkillsList* gpCommonSpace;




// On Draw
void PrepSkill_DrawWindowGfx(void);
void PrepSkill_DrawPickTotalBar(struct Unit* unit, int config); // config: 0->init, 1->update
void PrepSkill_DrawLeftSkillsIcon(struct Unit* unit, int config);
void PrepSkill_DrawBattalionBar(struct Unit* unit, int config);


// Skills List
void InitPrepSkillsList(void);
struct PrepSkillsList* MakeUnitPrepSkillsList(struct Unit* unit);
struct PrepSkillsList* GetUnitPrepSkillsList(struct Unit* unit);

int PrepSkillAddRamSkillFromList(struct Unit* unit, u8 skill_id);




// Global functions
// void StartPrepScreenSkillsMenu(struct Proc_AtMenu* proc); // in skill-system.h
void PrepSkill_StartPickSkillScreen(struct Proc_PrepUnit*);

