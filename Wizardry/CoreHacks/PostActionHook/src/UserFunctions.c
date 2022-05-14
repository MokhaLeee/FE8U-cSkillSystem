#include "gbafe-chax.h"




int PostAction_Template(ProcPtr proc){
	
	extern void StartStatusClearFx(struct Unit*, ProcPtr);
	
	MU_EndAll();
	StartStatusClearFx(gActiveUnit, proc);
	return 1;
}



