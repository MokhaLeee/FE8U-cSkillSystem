#include "gbafe-chax.h"




void PostAction_Template(ProcPtr proc){
	
	// System Anim:
	// Status Cre
	extern void StartStatusClearFx(struct Unit*, ProcPtr);
	MU_EndAll();
	HideUnitSMS(gActiveUnit);
	StartStatusClearFx(gActiveUnit, proc);
	
	
	// Mokha Anim:
	// Gravity debuff
	SMS_UpdateFromGameData();
	StartMapAnim_Gravity(gActiveUnit, proc);

}



