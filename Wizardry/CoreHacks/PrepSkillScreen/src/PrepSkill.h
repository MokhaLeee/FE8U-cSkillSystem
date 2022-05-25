#pragma once

enum{
	// On draw config
	ON_DRAW_CONFIG_INIT = 0,
	ON_DRAW_CONFIG_UPDATE = 1,

	
	// for Objs
	// Real VRAM Offset to uncompress: OBJ_VRAM0 + _VOBJ
	// Real Palette index: 0x10 + _PAL
	SKILLOBJ_VOBJ = 0x3000, 
	SKILLOBJ_PAL = 0x3,
	
	OBJWINDOW_VOBJ = 0x4000,
	OBJWINDOW_PAL = 0x6,
	
	// Skill Icons
	VOBJ_SKILL_ICONS = 0x4400,




	// Sub-menu items	
	MENUITEM_PREPSKILL_SKILL = 0,
	MENUITEM_PREPSKILL_COMBAT,
	MENUITEM_PREPSKILL_BATTALION,
	
	MENUITEM_PREPSKILL_NULL = 0xFF,
	

	// list-type for proc-skill-sublist + 0x29
	PREP_SKLSUB_RIGHT = 0,
	PREP_SKLSUB_LEFT_RAM,
	PREP_SKLSUB_LEFT_ROM,
	PREP_SKLSUB_LEFT_CA,
	PREP_SKLSUB_MAXLIST,
	
	
	// list length
	PREPSKILL_LISTLEN_RAM = 5,
	PREPSKILL_LISTLEN_ROM = 5,
	PREPSKILL_LISTLEN_ALL = 0x100,
	PREPSKILL_LISTLEN_CA = 5,
	
	// Scroll
	PREP_SCROLL_NOPE = 0,
	PREP_SCROLL_UP = 1,
	PREP_SCROLL_DOWN = 2,
	
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


struct Proc_PrepPickSkill{
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 state;
	
	/* 2C */ struct Unit* unit;
	/* 30 */ u8 skill_id_pre;	// only update on 
	/* 31 */ u8 list_index; // current index for skill list
	/* 32 */ u8 list_index_pre;
	/* 33 */ u8 list_type;
	/* 34 */ u8 list_type_pre;
	/* 35 */ u8 list_index_replace;
	/* 36 */ u8 yeah;
	/* 37 */ u8 head_line;
	/* 38 */ u8 scroll_type;	// 0 = none, 1 = up, 2 = down
	/* 39 */ u8 scroll_diffCur;
	/* 3A */ u8 scroll_step;	// 0x4 or 0x8
	/* 3B */ u8 displaying_count;	// number of current displaying icons
	/* 3C */ u8 right_disp_reset;	// if set, reload total list icon obj
};

extern const struct ProcCmd gProc_PrepSkillPickSkillList[];
extern const struct ProcCmd gProc_PrepSkillPickCombatArtList[];

// need gpPrepSkillList!
extern struct PrepSkillsList* gpPrepSkillList;




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
int IsPrepSkillListValid();
int IsPrepSkillRom(struct Unit* unit, u8 skill_id);
int isPrepSkillEquippedRAM(struct Unit* unit, u8 skill_id);

struct PrepSkillsList* MakeUnitPrepCombatArtsList(struct Unit*);
struct PrepSkillsList* GetUnitPrepCombatArtsList(struct Unit*);
int isPrepCombatArtRAM(struct Unit*, u8 id);


// Objs
void StartProc_PrepSkillObj(ProcPtr);
void EndProc_PrepSkillObj();
void StartProc_PrepCombatArtObj(ProcPtr);
void EndProc_PrepCombatArtObj();


void PrepSkill_InitObjWindowGfx();
void PrepSkill_UpdateObjWindow(int x, int y, int length, int height);




// Global functions
// void StartPrepScreenSkillsMenu(struct Proc_AtMenu* proc); // in skill-system.h
void PrepSkill_StartPickSkillScreen(struct Proc_PrepUnit*);
void PrepSkill_StartPickCombatArtScreen(struct Proc_PrepUnit*);

