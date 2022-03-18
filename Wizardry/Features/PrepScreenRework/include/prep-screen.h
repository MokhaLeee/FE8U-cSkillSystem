#pragma once

// ====================================================

// C-Lib version: FE-CLib-Mokha
// https://github.com/MokhaLeee/FE-CLib-Mokha.git

#include "gbafe.h"
// ====================================================

enum{
	
	// menu_item of proc: (Proc_SALLYCURSOR + 0x58)
	
	PREP_MAPMENU_VIEWMAP = 1,
	PREP_MAPMENU_FORMATION = 2,
	PREP_MAPMENU_OPTION = 8,
	PREP_MAPMENU_SAVE = 9,
	
	
	
	// menu item of proc: Proc_AtMenu
	PREP_MAINMENU_UNIT = 0,
	PREP_MAINMENU_ITEM = 1,
	PREP_MAINMENU_SAVE = 2,
	PREP_MAINMENU_SUPPORT = 4,
	PREP_MAINMENU_CHECKMAP = 7,
};


struct Proc_SALLYCURSOR {
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 pad_29[0x58 - 0x29];
	/* 58 */ u32 menuCmd_index; // Prep-Menu cmd index!!!
	/* 5C */
};


struct Proc_AtMenu {
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 unit_count;
	/* 2A */ u8 max_counter; // Total unit number can be on battle
	/* 2B */ u8 cur_counter; // Total unit number to be on battle
	/* 2C */ u8 unk_2C;
	/* 2D */ u8 cur_cmd;
	/* 2E */ u8 unk_2E;
	/* 2F */ u8 unk_2F;
	/* 30 */ u8 unk_30;
	/* 31 */ u8 unk_31;
	/* 32 */ u8 unk_32;
	/* 33 */ u8 state;
	/* 34 */ u8 unk_34;
	/* 35 */ u8 unk_35;
	/* 36 */ bool8 end_prep;
	/* 38 */ u8 unk_38[0x3C - 0x38];
	/* 3C */ u32 yDiff; // y Pos offset of Unit SMS
	/* 40 */ u32 xDiff;
};


struct Proc_PrepMainMenuCmd;

struct Proc_PrepMainMenu {
	
	/* 00 */ PROC_HEADER;
	/* 29 */ s8 rtext_on;
	/* 2A */ u8 cur_index;
	/* 2B */ u8 max_index;
	/* 2C */ u8 unk_2C[0x33 - 0x2C];
	/* 33 */ u8 end_state;
	/* 34 */ s16 xPos;
	/* 36 */ s16 yPos;
	/* 38 */ struct Proc_PrepMainMenuCmd* cmds[0x8];
	/* 58 */ int (*on_bPress)(ProcPtr);
	/* 5C */ int (*on_startPress)(ProcPtr);
	/* 60 */ void (*on_end)(ProcPtr parent);
};


struct Proc_PrepMainMenuCmd {
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 pad_29[0x2C - 0x29];
	/* 2C */ void (*effect)(ProcPtr);
	/* 30 */ int msg_rtext;
	/* 34 */ u32 msg;
	/* 38 */ u8 color;
	/* 39 */ u8 index;
	/* 3A */ u8 pad_3A[0x3C - 0x3A];
	/* 3C */ struct TextHandle text;
};


struct Proc_PrepUnit {
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 cur_counter; // Total unit number to be on battle
	/* 2A */ u8 max_counter; // Total unit number can be on battle
	/* 2B */ u8 unk_2B;
	/* 2C */ u16 list_num_pre; // pre unit index in prep-list(for scroll)
	/* 2E */ u16 list_num_cur; // current unit index in prep-list
	/* 30 */ u16 yDiff_cur; // y Pos offset of Unit SMS (current)
	/* 32 */ u16 unk_32;
	/* 34 */ u8 pad_34[0x36 - 0x34];
	/* 36 */ u8 scroll_val; // each px to scroll at each frame
	/* 37 */ u8 unk_37;
	/* 38 */ u8 pad_38[0x3C - 0x38];
	/* 3C */ u16 unk_3C;
};


struct PrepScreenUnitList {
	struct Unit* units[0x40];
	s32 size;
	u32 char_id;
};




// UI
#define gPrepTexts gUnknown_0201117C
extern struct TextHandle gPrepTexts[]; // 0201117C
extern void DisplayPrepScreenMenuHelpText();
void DrawPrepScreenMenuFrameAt(int x, int y);


// Prep Unit stack
void InitUnitStack(void* dest);
void PushUnit(struct Unit*);
void LoadPlayerUnitsFromUnitStack();

// Prep Unit List
extern struct PrepScreenUnitList gPrepScreenUnitList;
void InitPrepScreenUnitList();
int GetChapterAllyUnitCount();
struct Unit* GetPrepScreenUnitListEntry(int num);
void ReorderPlayerUnitsBasedOnDeployment();
int GetPrepScreenUnitListSize();
void ShrinkPlayerUnitList();
// static int (*InitChapterDeployedUnitAndGetCount)(void) = (const void*) 0x8095971;
// static void (*SetPrepScreenUnitListCharID)(int index) = (const void*) 0x80953C1;

// SallyCursor
extern const struct ProcCmd gProc_PrepScreen[];
void PrepScreenProc_StartConfigMenu(ProcPtr);


// AtMenu
void StartPrepScreenItemsMenu(struct Proc_AtMenu* proc);
void StartPrepScreenSupportMenu(int, struct Proc_AtMenu* proc);
void StartPrepScreenSaveMenu(struct Proc_AtMenu* proc);


// Unit menu
extern struct ProcCmd gProc_PrepScreenPickUnitsMenu[];


// prep menu
extern const struct ProcCmd gProc_PrepScreenMenu[]; // 8A186EC
extern const struct ProcCmd gProc_PrepScreenMenuDummyItem[]; // 8A186DC

void StartPrepScreenMenu(ProcPtr);
void ClosePrepScreenMapMenu(void);
void EnablePrepScreenMenu(void);
int PrepScreenMenuExists(void);
void EndPrepScreenMenu(void);
void SetPrepScreenMenuItem(int index, void* effect_routine, int color, int msg, int msg_rtext); // 8097024
void SetPrepScreenMenuOnBPress(void*);
void SetPrepScreenMenuOnStartPress(void*);
extern void SetPrepScreenMenuOnEnd(void*);
void SetPrepScreenMenuPosition(int, int);
void SetPrepScreenMenuSelectedItem(int);

// Prep-main-menu effect routine
void PrepScreenMenu_OnPickUnits(struct Proc_AtMenu*);
void PrepScreenMenu_OnItems(struct Proc_AtMenu*);
void PrepScreenMenu_OnCheckMap(struct Proc_AtMenu*);
void PrepScreenMenu_OnSave(struct Proc_AtMenu*);
int PrepScreenMenu_OnBPress(struct Proc_AtMenu*);
int PrepScreenMenu_OnStartPress(struct Proc_AtMenu*);

void PrepScreenMapMenu_OnViewMap(struct Proc_SALLYCURSOR*);
void PrepScreenMapMenu_OnFormation(struct Proc_SALLYCURSOR*);
void PrepScreenMapMenu_OnOptions(struct Proc_SALLYCURSOR*);
void PrepScreenMapMenu_OnSave(struct Proc_SALLYCURSOR*);
int PrepScreenMapMenu_OnBPress(struct Proc_SALLYCURSOR*);
int PrepScreenMapMenu_OnStartPress(struct Proc_SALLYCURSOR*);
void PrepScreenMapMenu_OnEnd(struct Proc_SALLYCURSOR*);


// Button Obj
// static void (*StartProc_PrepMapDrawButtonObj)(ProcPtr) = (const void*) 0x8033621;
// static void (*PrepOnDrawSpecialChar)(ProcPtr) = (const void*) 0x8096BFD;
// static void (*PrepSpecialChar_OnEnd)() = (const void*) 0x8096C21;
// static void (*PrepSpecialChar_BlinkButtonStart)() = (const void*) 0x8096BC5;
// static void (*PrepSpecialChar_BlinkButtonB)() = (const void*) 0x8096BE1;

// others
void EndPrepScreen();
int CanPrepScreenSave();
int CanPrepScreenCheckMap();








