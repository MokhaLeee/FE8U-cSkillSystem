#include "gbafe.h"
#include "str-mag.h"

void U2B_Mag(struct BattleUnit* bu, struct Unit* unit){
	*GetMagAt(&bu->unit) = *GetMagAt(unit);
}

void B2U_Mag(struct Unit* unit, struct BattleUnit* bu){
	
	*GetMagAt(unit) += *GetBu_ChangeMagAt(bu);
	
	// here, clear bu->changeMag
	*GetBu_ChangeMagAt(bu) = 0;
}
