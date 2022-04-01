#pragma once

enum{
	// On draw config
	
	ON_DRAW_CONFIG_INIT = 0,
	ON_DRAW_CONFIG_UPDATE = 1,
};



enum{
	// Sub-menu items
	
	MENUITEM_PREPSKILL_SKILL = 0,
	MENUITEM_PREPSKILL_COMBAT,
	MENUITEM_PREPSKILL_BATTALION,
	
	MENUITEM_PREPSKILL_NULL = 0xFF,
	
};

enum{
	// list type for proc-skill-sublist + 0x29
	PREP_SKLSUB_RIGHT = 0,
	PREP_SKLSUB_LEFT_RAM,
	PREP_SKLSUB_LEFT_ROM,
	PREP_SKLSUB_LEFT_CA,
	PREP_SKLSUB_MAXLIST,
	
	
	// list length
	PREPSKILL_LISTLEN_RAM = 5,
	PREPSKILL_LISTLEN_ROM = 10,
	PREPSKILL_LISTLEN_ALL = 24,
	PREPSKILL_LISTLEN_CA = 5,
	
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
void PrepUnit_DrawUnitListNames(struct Proc_PrepUnit*, int);
int ShouldPrepUnitMenuScroll(struct Proc_PrepUnit*);


// Skills List
void InitPrepSkillsList(void);
struct PrepSkillsList* MakeUnitPrepSkillsList(struct Unit* unit);
struct PrepSkillsList* GetUnitPrepSkillsList(struct Unit* unit);

int PrepSkillAddRamSkillFromList(struct Unit* unit, u8 skill_id);


// Objs
void StartProc_PrepSkillObj(ProcPtr parent);
void EndProc_PrepSkillObj(ProcPtr parent);




// Global functions
// void StartPrepScreenSkillsMenu(struct Proc_AtMenu* proc); // in skill-system.h
void PrepSkill_StartPickSkillScreen(struct Proc_PrepUnit*);

