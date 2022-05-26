#include "gbafe-chax.h"

typedef int (*PAL_Fun) (ProcPtr);
extern PAL_Fun PostActionLoopTable[];


struct Proc_PostAction{
	
	PROC_HEADER;
	PAL_Fun* fun_cur;
};


static void PostAction_OnInit(struct Proc_PostAction* proc){
	
	if( gRAMChapterData.chapterVisionRange ) // Fog
	{
		RenderBmMapOnBg2();
		MoveActiveUnit(gActionData.xMove, gActionData.yMove);
		RefreshEntityBmMaps();
		RenderBmMap();
		NewBMXFADE(0);
		SMS_UpdateFromGameData();
	}
	else
	{
		MoveActiveUnit(gActionData.xMove, gActionData.yMove);
		RefreshEntityBmMaps();
		RenderBmMap();
	}
	
	SetCursorMapPosition(gActiveUnit->xPos, gActiveUnit->yPos);
	
	gGameState.cameraPrevious = gGameState.playerCursor;
	
	proc->fun_cur = &PostActionLoopTable[0];
}



static void PostAction_ExecNext(struct Proc_PostAction* proc){
	
	if( 0 == *proc->fun_cur )
	{
		Proc_Goto(proc, 1);
		return;
	}
	
	
	(*proc->fun_cur++)(proc);
}



static void PostAction_Canto(struct Proc* proc){
	
	extern int TryMakeCantoUnit(ProcPtr);
	
	if( TryMakeCantoUnit(proc->proc_parent) )
		Proc_End(proc);
	
}


static void PostAction_CallEndEvent(struct Proc* proc){
	
	extern int ShouldCallEndEvent();
	extern void MaybeCallEndEvent_();
	
	if( !ShouldCallEndEvent() )
		return;
	

	RefreshEntityBmMaps();
	RenderBmMap();
	SMS_UpdateFromGameData();
	MaybeCallEndEvent_();
	Proc_End(proc);
	Proc_Goto(proc->proc_parent, 0x8);
}



// ==================================================
//      This Proc will be inserted as blocking
// ==================================================

const struct ProcCmd ProcCmd_PostActionHook[] = {
	
	PROC_CALL (PostAction_OnInit),
	
PROC_LABEL(0),	
	PROC_CALL (PostAction_ExecNext),
	PROC_YIELD,
	PROC_GOTO(0),
	
	
PROC_LABEL(1),		
	PROC_CALL (MU_EndAll),
	
	PROC_CALL (PostAction_Canto),
	PROC_CALL (PostAction_CallEndEvent),
	PROC_END,
};









