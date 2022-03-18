#include "gbafe.h"

typedef void (*HookFunc_u2b)(struct BattleUnit* bu, struct Unit* unit);
extern HookFunc_u2b Unit2BattleFuncList[];


typedef void (*HookFunc_b2u)(struct Unit* unit, struct BattleUnit* bu);
extern HookFunc_b2u Battle2UnitFuncList[];



// 802A584
void InitBattleUnit(struct BattleUnit* bu, struct Unit* unit){
	
	HookFunc_u2b *it = &Unit2BattleFuncList[0];
	
	while( *it )
		(*it++)(bu, unit);
}


// 802C1EC 
void UpdateUnitFromBattle(struct Unit* unit, struct BattleUnit* bu){
	
	HookFunc_b2u *it = &Battle2UnitFuncList[0];
	
	while( *it )
		(*it++)(unit, bu);
}


