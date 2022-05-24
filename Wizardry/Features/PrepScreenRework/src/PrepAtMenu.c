#include "gbafe-chax.h"

extern void PrepScreenProc_StartDimMap(ProcPtr);
extern int MapBrightnessFadeExists(ProcPtr);
static int (*InitChapterDeployedUnitAndGetCount)(void) = (const void*) 0x8095971;
extern void AtMenu_AutoCapDeployPrepScreenUnits(struct Proc_AtMenu*);
extern int NewFadeOut(ProcPtr);
extern void InitPrepScreenCursorPosition(void);
extern void PrepScreenProc_DimMapImmediate(ProcPtr);
static void (*PrepSpecialChar_BlinkButtonStart)() = (const void*) 0x8096BC5;
static void (*PrepSpecialChar_BlinkButtonB)() = (const void*) 0x8096BE1;
static void (*StartProc_PrepMapDrawButtonObj)(ProcPtr) = (const void*) 0x8033621;

// static void * (struct Proc_AtMenu* proc);
static void newPrepMenu_StartMenuAndDrawText (struct Proc_AtMenu* proc);
static void newPrepMenu_OnEnd (struct Proc_AtMenu* proc);
static void newPrepMenu_OnInit(struct Proc_AtMenu* proc);
static void newPrepMenuEffect_PickUnits(struct Proc_AtMenu* proc);
static void newPrepMenuEffect_Items(struct Proc_AtMenu* proc);
static void newPrepMenuEffect_Supports(struct Proc_AtMenu* proc);
static void newPrepMenuEffect_Save(struct Proc_AtMenu* proc);
static void newPrepMenuEffect_Formation(struct Proc_AtMenu* proc);
static void newPrepMenuEffect_Options(struct Proc_AtMenu* proc);
static int newPrepMenuEffect_BPress(struct Proc_AtMenu* proc);
static int newPrepMenuEffect_StartPress(struct Proc_AtMenu* proc);
static void newPrepMenuEffect_OnEnd(struct Proc_AtMenu* proc);
static void AtMenu_OnEnd_8096294(struct Proc_AtMenu* proc);
static void AtMenu_OnEnd_80962E0(struct Proc_AtMenu* proc);
static void newPrepMenu_StartSubMenu(struct Proc_AtMenu* proc);
static void newPrepMenu_OnSubMenuEnd(struct Proc_AtMenu* proc);

static void newPrepMenuEffect_Skills(struct Proc_AtMenu* proc);




enum{
	// Proc: Prep-AtMenu's label
	LABEL_PREPMENU_ONINIT = 0,
	LABEL_PREPMENU_STARTMENU = 1,
	
	LABEL_PREPMENU_SUBMENU_FADEIN = 0xA,
	LABEL_PREPMENU_SUBMENU = 0x2,
	
	LABEL_PREPMENU_END_FADE = 0x5,
	LABEL_PREPMENU_END = 0x6,
};



const static struct ProcCmd newProcCmd_PrepAtMenu[] = {
	
	PROC_NAME	("PREP_NEW_ATMENU"),
	PROC_CALL	(newPrepMenu_OnInit),
	PROC_YIELD,

PROC_LABEL (LABEL_PREPMENU_ONINIT),	

	// On init
	// copy from Sally-Cursor PrepMapMenu
	PROC_CALL	(InitPrepScreenCursorPosition),
	PROC_CALL	(RefreshBMapGraphics),
	PROC_CALL	(RefreshEntityBmMaps),
	PROC_CALL	(RenderBmMap),
	PROC_CALL 	(SMS_ClearUsageTable),
	PROC_CALL	(SMS_UpdateFromGameData),
	PROC_CALL	(PrepScreenProc_DimMapImmediate),
	PROC_REPEAT	(ContinueUntilSomeTransistion6CExists), // WaitForFade
	

// Start Menu
PROC_LABEL (LABEL_PREPMENU_STARTMENU),	
	
	PROC_CALL	(newPrepMenu_StartMenuAndDrawText),
	PROC_YIELD,
	
	PROC_CALL	(PrepScreenProc_StartDimMap),
	PROC_WHILE	(MapBrightnessFadeExists),
	
	PROC_YIELD,
	PROC_CALL	(EnablePrepScreenMenu),
	PROC_YIELD,
	PROC_WHILE	(PrepScreenMenuExists),
	
	PROC_YIELD,
	PROC_GOTO	(LABEL_PREPMENU_END_FADE),



// Fade in and start sub-menu
PROC_LABEL (LABEL_PREPMENU_SUBMENU_FADEIN),
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),
	PROC_GOTO	(LABEL_PREPMENU_SUBMENU),
	
// Start sub-menu
PROC_LABEL (LABEL_PREPMENU_SUBMENU),
	PROC_CALL	(BMapDispSuspend), 			// LockGameGraphicsLogic
	PROC_CALL	(PrepScreenMapMenu_OnEnd),
	PROC_YIELD,
	PROC_CALL	(newPrepMenu_StartSubMenu),
	PROC_YIELD,
	PROC_CALL	(newPrepMenu_OnSubMenuEnd),
	PROC_YIELD,
	PROC_CALL	((void*)0x8033621), 		// (StartProc_PrepMapDrawButtonObj),
	PROC_CALL	(BMapDispResume), 			// UnlockGameGraphicsLogic
	PROC_GOTO	(LABEL_PREPMENU_ONINIT), 	// Go back on init map




// Fade out and end
PROC_LABEL (LABEL_PREPMENU_END_FADE),
	PROC_YIELD,
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),


// End	
PROC_LABEL (LABEL_PREPMENU_END),
	PROC_YIELD,
	PROC_CALL	(BMapDispResume), 			// UnlockGameGraphicsLogic
	PROC_CALL	(newPrepMenu_OnEnd),
	PROC_CALL	(AtMenu_OnEnd_8096294),
	PROC_YIELD,
	PROC_CALL	(AtMenu_OnEnd_80962E0),
	PROC_YIELD,
	PROC_CALL	(MU_EndAll),
	PROC_CALL	(EndAllProcChildren),
	PROC_END
}; 




// =======================================================
// =================== Inside Proc =======================
// =======================================================
void newPrepMenu_OnInit(struct Proc_AtMenu* proc){
	
	extern void sub_80953C0(int); // SetPrepScreenUnitListCharID
	
	sub_80953C0(0);
	
	proc->xDiff = 0;
	proc->yDiff = 0;

	proc->max_counter = GetChapterAllyUnitCount();
	
	proc->unk_30 = 0;
	proc->unk_31 = 0;
	proc->unk_32 = 0;
	proc->state = 0;
	proc->unk_34 = 0;
	proc->end_prep = 0;
	proc->cur_cmd = 0;
	proc->unk_2E = 0;
}



void newPrepMenu_StartMenuAndDrawText (struct Proc_AtMenu* proc){

	
	BG_Fill(gBG0TilemapBuffer, 0);
	BG_Fill(gBG1TilemapBuffer, 0);
	
	LoadDialogueBoxGfx(0, -1);
	Font_InitForUIDefault();
	DeletePlayerPhaseInterface6Cs();
	HideMoveRangeGraphics();
	LoadObjUIGfx();
	SMS_ClearUsageTable();
	
	InitPrepScreenUnitList();
	AtMenu_AutoCapDeployPrepScreenUnits(proc);
	ReorderPlayerUnitsBasedOnDeployment();
	
	StartProc_PrepMapDrawButtonObj(proc);
	
	StartPrepScreenMenu(proc);
	
	SetPrepScreenMenuItem(
		CMD_PREPMENU_PICKUNIT, 
		newPrepMenuEffect_PickUnits, 
		TEXT_COLOR_NORMAL, 
		0x574, // Pick Units[X]
		0x57A // Select which units to@001[N]field this battle. The[N]number is restricted.[X]
	);
	
	// Pick Units
	SetPrepScreenMenuItem(
		CMD_PREPMENU_SKILLS,
		newPrepMenuEffect_Skills,
		TEXT_COLOR_NORMAL,
		ENUM_msg_PrepPickSkillName,
		ENUM_msg_PrepPickSkillDesc
	);
	
	SetPrepScreenMenuItem(
		CMD_PREPMENU_ITEM, 
		newPrepMenuEffect_Items, 
		TEXT_COLOR_NORMAL, 
		0x576, // Items[X]
		0X57C // Manage your units' items.[X]
	);
	
	SetPrepScreenMenuItem(
		CMD_PREPMENU_SAVE,
		newPrepMenuEffect_Save,
		0 == CanPrepScreenSave()
			? TEXT_COLOR_GRAY
			: TEXT_COLOR_NORMAL,
		0x579, // Save[X]
		0x5BE  // Save the current campaign.[X]
	);
	
	SetPrepScreenMenuItem(
		CMD_PREPMENU_SUPPORT, 
		newPrepMenuEffect_Supports, 
		TEXT_COLOR_NORMAL, 
		0x577, // Support[X]
		0x57F // Check the compatibility[N]of your units.[X] 
	);
	
	SetPrepScreenMenuItem(
		CMD_PREPMENU_OPTION,
		newPrepMenuEffect_Options,
		TEXT_COLOR_NORMAL,
		0x592, // Options[.][X]
		0x5BD  // et game speed and[NL] window options.[.][X]
	);
	
	SetPrepScreenMenuItem(
		CMD_PREPMENU_FORMATION,
		newPrepMenuEffect_Formation,
		TEXT_COLOR_NORMAL,
		0x591, // Formation[.][X]
		0x5BC  // Rearrange the starting[NL] formation of your units.[X]
	);
	
	

	SetPrepScreenMenuOnBPress(newPrepMenuEffect_BPress);
	SetPrepScreenMenuOnStartPress(newPrepMenuEffect_StartPress);
	SetPrepScreenMenuOnEnd(newPrepMenuEffect_OnEnd);
	
	SetPrepScreenMenuSelectedItem(proc->cur_cmd);
	
	DrawPrepScreenMenuFrameAt(0xA, 0x2);
}





// =======================================================
// ===================== Sub-Menu ========================
// =======================================================

void newPrepMenu_StartSubMenu(struct Proc_AtMenu* proc){
	
	extern void sub_8095C2C(ProcPtr);  // end scroll, end menu <!>, etc.
	
	sub_8095C2C(proc);
	
	
	switch( proc->cur_cmd )
	{
		case CMD_PREPMENU_PICKUNIT:
			Proc_StartBlocking(gProc_PrepScreenPickUnitsMenu, proc);
			
			// If not end AtMenu, SMS on map will display non-deployed unit
			// Currently no idea but directly goto view map
			Proc_Goto(proc, LABEL_PREPMENU_END);
			break;
		
		case CMD_PREPMENU_SAVE:
			ClosePrepScreenMapMenu();
			StartPrepScreenSaveMenu(proc);
			break;
			
		case CMD_PREPMENU_ITEM:
			StartPrepScreenItemsMenu(proc);
			break;
		
		case CMD_PREPMENU_SUPPORT:
			StartPrepScreenSupportMenu(2, proc);
			break;

		case CMD_PREPMENU_OPTION:
			PrepScreenProc_StartConfigMenu(proc);
			break;
			
		case CMD_PREPMENU_SKILLS: // new hack for pick skills:
			StartPrepScreenSkillsMenu(proc);
			break;
		
		default:
			break;
	}
	
	return;
	
}

void newPrepMenu_OnSubMenuEnd(struct Proc_AtMenu* proc){
	
	proc->state = 0;
}





// =======================================================
// =================== Button Press ======================
// =======================================================

void newPrepMenuEffect_Skills(struct Proc_AtMenu* proc){
	
	proc->cur_cmd = CMD_PREPMENU_SKILLS;
	proc->state = 1;
	Proc_Goto(proc, LABEL_PREPMENU_SUBMENU_FADEIN);
}


void newPrepMenuEffect_PickUnits(struct Proc_AtMenu* proc){
	
	proc->cur_cmd = CMD_PREPMENU_PICKUNIT;
	proc->state = 1;
	Proc_Goto(proc, LABEL_PREPMENU_SUBMENU_FADEIN);
}

void newPrepMenuEffect_Items(struct Proc_AtMenu* proc){
	
	proc->cur_cmd = CMD_PREPMENU_ITEM;
	proc->state = 1;
	Proc_Goto(proc, LABEL_PREPMENU_SUBMENU_FADEIN);
}

void newPrepMenuEffect_Supports(struct Proc_AtMenu* proc){
	
	
	proc->cur_cmd = CMD_PREPMENU_SUPPORT;
	proc->state = 4;
	
	sub_80029E8(0x37, 0x100, 0x100, 0x20, 0);
	
	Proc_Goto(proc, LABEL_PREPMENU_SUBMENU_FADEIN);
}

void newPrepMenuEffect_Save(struct Proc_AtMenu* proc){
	
	proc->cur_cmd = CMD_PREPMENU_SAVE;
	
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x6A);
	
	proc->state = 3;
	Proc_Goto(proc, LABEL_PREPMENU_SUBMENU_FADEIN);
	
}


void newPrepMenuEffect_Formation(struct Proc_AtMenu* proc){
	
	proc->cur_cmd = CMD_PREPMENU_FORMATION;
	Proc_Goto(proc, LABEL_PREPMENU_END_FADE);
	
}

void newPrepMenuEffect_Options(struct Proc_AtMenu* proc){
	
	proc->cur_cmd = CMD_PREPMENU_OPTION;
	Proc_Goto(proc, LABEL_PREPMENU_SUBMENU_FADEIN);
}

int newPrepMenuEffect_BPress(struct Proc_AtMenu* proc){
	
	Proc_Goto(proc, LABEL_PREPMENU_END_FADE);
	PrepSpecialChar_BlinkButtonB();
	
	if( CMD_PREPMENU_FORMATION == proc->cur_cmd )
		proc->cur_cmd = 0;
	
	return 1;
}

int newPrepMenuEffect_StartPress(struct Proc_AtMenu* proc){
	
	if( 0 == InitChapterDeployedUnitAndGetCount() )
		return 0;
	
	proc->end_prep = 1;
	Proc_Goto(proc, LABEL_PREPMENU_END_FADE);
	PrepSpecialChar_BlinkButtonStart();
	
	return 1;
	
}

void newPrepMenuEffect_OnEnd(struct Proc_AtMenu* proc){
	
	EndHelpPromptSprite();
}















// =======================================================
// ====================== On End =========================
// =======================================================

void newPrepMenu_OnEnd (struct Proc_AtMenu* proc){
	
	struct newProc_PrepMain* proc_prep;
	
	proc_prep = (struct newProc_PrepMain*) proc->proc_parent;
	
	proc_prep->cur_cmd = proc->cur_cmd;
	
}


void AtMenu_OnEnd_8096294(struct Proc_AtMenu* proc){
	
	extern void sub_8096C20();
	extern void SetColorEffectsFirstTarget(int, int, int, int, int);
	extern void SetColorEffectBackdropFirstTarget(int);
	
	sub_8096C20();
	SetupBackgrounds(0);
	SetSpecialColorEffectsParameters(3,0,0,0x10);
	SetColorEffectsFirstTarget(1,1,1,1,1);
	SetColorEffectBackdropFirstTarget(1);
}


void AtMenu_OnEnd_80962E0(struct Proc_AtMenu* proc){
	
	extern void sub_8042EA8();
	extern void PositionUnitsAccordingToDeployment();
	
	ReorderPlayerUnitsBasedOnDeployment();
	
	if( 1 == proc->end_prep )
		EndPrepScreen();
	
	PositionUnitsAccordingToDeployment();
	SMS_ClearUsageTable();
	RefreshEntityBmMaps();
	SMS_UpdateFromGameData();
		
}



// =======================================================
// ======================= Misc ==========================
// =======================================================

void StartNewPrepAtMenu(struct newProc_PrepMain* proc_prep){
	
	struct Proc_AtMenu* child = 
		Proc_StartBlocking(newProcCmd_PrepAtMenu, proc_prep);
		
	child->cur_cmd = proc_prep->cur_cmd;
	
}




