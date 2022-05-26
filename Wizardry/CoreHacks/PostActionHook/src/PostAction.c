#include "gbafe-chax.h"

typedef int (*PAL_Fun) (ProcPtr);
extern PAL_Fun PostActionLoopTable[];

struct Proc_PostAction{
	
	PROC_HEADER;
	PAL_Fun* fun_cur;
};



static void PostAction_ExecNext(struct Proc_PostAction* proc){
	
	if( 0 == *proc->fun_cur )
	{
		Proc_Goto(proc, 1);
		return;
	}
	
	
	(*proc->fun_cur++)(proc);
}


static const struct ProcCmd ProcCmd_PostActionHook[] = {
	
	PROC_YIELD,
	
PROC_LABEL(0),	
	PROC_CALL (PostAction_ExecNext),
	PROC_YIELD,
	PROC_GOTO(0),
	
	
PROC_LABEL(1),
	PROC_END,
};












// Hack

int HandlePostActionTraps(ProcPtr proc){
	
	// struct Unit* unit_act = gActiveUnit;
	// struct Unit* unit_tar = GetUnit(gActionData.targetIndex);
	
	// We take here as post-action
	
	struct Proc_PostAction *child = 
		Proc_StartBlocking(ProcCmd_PostActionHook, proc);
	
	child->fun_cur = &PostActionLoopTable[0];
	return 0;
}