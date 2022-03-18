#include "gbafe.h"

typedef void (*HookFunc_t0)(struct Unit* unit, u8 classId);
typedef void (*HookFunc_t1)(struct BattleUnit*, struct Unit*);

extern HookFunc_t0 OnPromoteFuncList[];
extern HookFunc_t1 MakePromoteGainsFuncList[];

// 802BD50
void ApplyUnitPromotion(struct Unit* unit, u8 classId){
	
	HookFunc_t0* it = &OnPromoteFuncList[0];
	
	while( *it )
		(*it++)(unit, classId);
}


void GenerateBattleUnitStatGainsComparatively(struct BattleUnit* bu, struct Unit* unit) {
	
	HookFunc_t1 *it = &MakePromoteGainsFuncList[0];
	
	while( *it )
		(*it++)(bu, unit);
}


void ApplyUnitDefaultPromotion(struct Unit* unit) {	
	ApplyUnitPromotion(unit, unit->pClassData->promotion);
}