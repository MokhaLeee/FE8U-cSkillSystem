#include "gbafe.h"
#include "str-mag.h"

void UnitAutolevelCore(struct Unit* unit, u8 classId, int levelCount) {
	if ( !levelCount)
		return;
	unit->maxHP += 
		GetAutoleveledStatIncrease(unit->pClassData->growthHP,  levelCount);
	unit->pow   += 
		GetAutoleveledStatIncrease(unit->pClassData->growthPow, levelCount);
	unit->skl   += 
		GetAutoleveledStatIncrease(unit->pClassData->growthSkl, levelCount);
	unit->spd   += 
		GetAutoleveledStatIncrease(unit->pClassData->growthSpd, levelCount);
	unit->def   += 
		GetAutoleveledStatIncrease(unit->pClassData->growthDef, levelCount);
	unit->res   += 
		GetAutoleveledStatIncrease(unit->pClassData->growthRes, levelCount);
	unit->lck   += 
		GetAutoleveledStatIncrease(unit->pClassData->growthLck, levelCount);
	
	// for unit magic
	*GetMagAt(unit) += 
		GetAutoleveledStatIncrease(GetClassMagicGrowth(unit->pClassData->number), levelCount);
}

void UnitAutolevelPenalty(struct Unit* unit, u8 classId, int levelCount) {
	int level = unit->level;

	if (levelCount && level > unit->pCharacterData->baseLevel) {
		levelCount = level - levelCount;

		unit->maxHP = unit->pCharacterData->baseHP  + unit->pClassData->baseHP;
		unit->pow   = unit->pCharacterData->basePow + unit->pClassData->basePow;
		unit->skl   = unit->pCharacterData->baseSkl + unit->pClassData->baseSkl;
		unit->spd   = unit->pCharacterData->baseSpd + unit->pClassData->baseSpd;
		unit->def   = unit->pCharacterData->baseDef + unit->pClassData->baseDef;
		unit->res   = unit->pCharacterData->baseRes + unit->pClassData->baseRes;
		unit->lck   = unit->pCharacterData->baseLck;
		
		// Magic
		*GetMagAt(unit) = 
			GetClassMagBase(unit->pClassData->number) +
			GetUnitMagBase(unit->pCharacterData->number);
		
		if (levelCount > unit->pCharacterData->baseLevel) {
			unit->level = levelCount;
			UnitAutolevel(unit);
			unit->level = level;
		}
    }
}