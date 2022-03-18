#include "gbafe.h"
#include "str-mag.h"




s8* GetMagAt(struct Unit* unit){
	return (s8*)unit + MAG_OFFSET;
}

s8* GetBu_ChangeMagAt(struct BattleUnit* bu){
	return (s8*)bu + MAG_UP_OFFSET;
}

// Get Mag Unit Base
int GetUnitMagBase(u8 charId){
	return UnitMagicTable[charId].base;
}

// Get Mag class Base
int GetClassMagBase(u8 classId){
	return ClassMagicTable[classId].base;
}

int GetClassMagCap(u8 classId){
	return ClassMagicTable[classId].cap;
}

int GetClassPromoBonusMag(u8 classId){
	return ClassMagicTable[classId].promo_bonus;
}

int GetClassMagicGrowth(u8 classId){
	return ClassMagicTable[classId].growth;
}

int GetUnitMagGrowth(struct Unit* unit){
	return UnitMagicTable[unit->pCharacterData->number].growth;
}