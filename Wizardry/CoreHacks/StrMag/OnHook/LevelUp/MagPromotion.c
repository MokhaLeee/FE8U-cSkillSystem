#include "gbafe.h"
#include "str-mag.h"

void MLU_PromoGain_Mag(struct Unit* unit, u8 classId){
	*GetMagAt(unit) += GetClassPromoBonusMag(classId);
}


void MLU_PromoDiff_Mag(struct BattleUnit* bu, struct Unit* unit){
	*GetBu_ChangeMagAt(bu) = *GetMagAt(&bu->unit) - *GetMagAt(unit);
}