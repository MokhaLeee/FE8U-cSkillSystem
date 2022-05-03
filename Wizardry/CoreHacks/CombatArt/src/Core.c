#include "gbafe-chax.h"

int UnitHasCombatArt(struct Unit* unit){
	return 1;
}

int CanUnitUseCombatArt(struct Unit* unit, u8 index){
	// 这个仅仅用于判定当下
	// 因为在已经有列表的情况下
	// 更多的是做武器判定
	return 1;
}