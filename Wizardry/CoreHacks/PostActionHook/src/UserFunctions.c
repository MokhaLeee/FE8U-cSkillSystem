#include "gbafe-chax.h"




int PostAction_Template(ProcPtr proc){
	
	extern void StartStatusClearFx(struct Unit*, ProcPtr);
	
	// MU_EndAll();
	// HideUnitSMS(gActiveUnit);
	// StartStatusClearFx(gActiveUnit, proc);
	
	SMS_UpdateFromGameData();
	StartMapAnim_Gravity(gActiveUnit, proc);
	return 1;
}



