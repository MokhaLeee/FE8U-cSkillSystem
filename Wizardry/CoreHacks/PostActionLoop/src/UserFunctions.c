#include "gbafe-chax.h"




int PostAction_Template(ProcPtr proc){
	
	extern void StartStatusClearFx(struct Unit*, ProcPtr);
	
	MU_EndAll();
	StartStatusClearFx(gActiveUnit, proc);
	return 1;
}

int PostAction_Canto(ProcPtr proc){
	
	extern int TryMakeCantoUnit(ProcPtr);
	
	if( TryMakeCantoUnit(proc) )
		return 1;

	
	return 0;
	
}


int PostAction_CallEndEvent(ProcPtr proc){
	
	extern int ShouldCallEndEvent();
	extern void MaybeCallEndEvent_();
	
	if( !ShouldCallEndEvent() )
		return 0;
	

	RefreshEntityBmMaps();
	RenderBmMap();
	SMS_UpdateFromGameData();
	MaybeCallEndEvent_();
	Proc_Goto(proc, 0x8);
	
	return 1;
}

