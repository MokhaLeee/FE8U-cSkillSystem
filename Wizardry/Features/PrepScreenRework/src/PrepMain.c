#include "gbafe-chax.h"

// static void * (struct newProc_PrepMain* proc);
static const struct ProcCmd newProcCmd_PrepMainOnInit[];
static void newPrepMain_OnInit(struct newProc_PrepMain* proc);
static void newProcPrep_AtMenuEnd0 (void);
static void newProcPrep_AtMenuEnd1 (void);

extern int PrepScreenProc_AddPostgameUnits(ProcPtr);
extern void PrepScreenProc_HideEverythingAndUnlockGame(ProcPtr);
extern void InitPrepScreenCursorPosition(void);
static const u32 SetPrepScreenUnitListCharID = 0x80953C1;
extern void PositionUnitsAccordingToDeployment();
extern void PrepScreenProc_DimMapImmediate(ProcPtr);


enum{
	
	NEWLABEL_PREPMAIN_ATMENU = 1,
	NEWLABEL_PREPMAIN_MAPVIEW = 2,
	NEWLABEL_PREPMAIN_ONEND = 3,
	
};



const struct ProcCmd newProcCmd_PrepMain[] = {
	
	PROC_NAME	("SALLY_CURSOR"),
	
	// On Init
	PROC_YIELD,
	PROC_CALL	(newPrepMain_OnInit),
	PROC_YIELD,
	PROC_GOTO	(NEWLABEL_PREPMAIN_ATMENU),
	
	
PROC_LABEL (NEWLABEL_PREPMAIN_ATMENU),
	
	// At Menu
	PROC_YIELD,
	PROC_CALL	(StartNewPrepAtMenu),
	PROC_YIELD,
	PROC_GOTO	(NEWLABEL_PREPMAIN_MAPVIEW),
	
	
PROC_LABEL (NEWLABEL_PREPMAIN_MAPVIEW),

	// Map View
	PROC_YIELD,
	PROC_CALL	(StartNewPrepMapView),
	PROC_YIELD,
	PROC_GOTO	(NEWLABEL_PREPMAIN_ATMENU),
	
	
PROC_LABEL (NEWLABEL_PREPMAIN_ONEND),

	// On End
	PROC_END
};









static const struct ProcCmd newProcCmd_PrepMainOnInit[] = {
	
	PROC_NAME	("PREPMAIN_ONINIT"),
	PROC_YIELD,
	
	// copy from SALLY-CURSOR
	PROC_WHILE	(PrepScreenProc_AddPostgameUnits),
	PROC_SLEEP	(0x1),
	PROC_CALL	(PrepScreenProc_HideEverythingAndUnlockGame),
	PROC_CALL	(InitPrepScreenUnitsAndCamera),
	PROC_SLEEP	(0x1),
	PROC_CALL	(sub_8034194),
	PROC_SLEEP	(0x8),
	
	// copy from AtMenu On-Init
	PROC_CALL_ARG((void*)SetPrepScreenUnitListCharID, 0),
	PROC_SLEEP	(0x2),
	
	// copy frin AtMenu On-End
	PROC_CALL	(newProcPrep_AtMenuEnd0),
	PROC_YIELD,
	PROC_CALL	(newProcPrep_AtMenuEnd1),
	PROC_YIELD,
	PROC_CALL	(MU_EndAll),
	PROC_YIELD,

	PROC_END,
};










// =======================================================
// =================== Inside Proc =======================
// =======================================================


void newPrepMain_OnInit(struct newProc_PrepMain* proc){
	
	AddSkipThread2();
	BMapDispSuspend();
	
	gLCDControlBuffer.dispcnt.bg0_on = 1;
	gLCDControlBuffer.dispcnt.bg1_on = 1;
	gLCDControlBuffer.dispcnt.bg2_on = 0;
	gLCDControlBuffer.dispcnt.bg3_on = 0;
	gLCDControlBuffer.dispcnt.obj_on = 0;
	
	
	InitPrepScreenUnitList();
	// AtMenu_AutoCapDeployPrepScreenUnits(proc);
	ReorderPlayerUnitsBasedOnDeployment();
	
	proc->cur_cmd = 0;
	
	Proc_StartBlocking(newProcCmd_PrepMainOnInit, proc);
}


void newProcPrep_AtMenuEnd0 (void){
	
	extern void sub_8096C20();
	extern void SetColorEffectsFirstTarget(int, int, int, int, int);
	extern void SetColorEffectBackdropFirstTarget(int);
	
	sub_8096C20();
	SetupBackgrounds(0);
	SetSpecialColorEffectsParameters(3,0,0,0x10);
	SetColorEffectsFirstTarget(1,1,1,1,1);
	SetColorEffectBackdropFirstTarget(1);
	
}

void newProcPrep_AtMenuEnd1 (void){
	
	PositionUnitsAccordingToDeployment();
	SMS_ClearUsageTable();
	RefreshEntityBmMaps();
	SMS_UpdateFromGameData();
	
}



/* 
// Misc
int Event3E_PrepScreenCall(ProcPtr proc){
	
	HideAllUnits();
	UnsetEventId(0x84);
	Proc_StartBlocking(newProcCmd_PrepMain, proc);
	return 2;
}
 */

