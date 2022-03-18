#include "gbafe.h"

typedef void (*HookFunc_t)(struct BattleUnit*);
extern HookFunc_t OnLevelUpFuncList[];

void CheckBattleUnitLevelUp(struct BattleUnit* bu) {
	
	// if not level up, do nothing
	if (CanBattleUnitGainLevels(bu) && bu->unit.exp < 100)
		return;

	bu->unit.exp -= 100;
	bu->unit.level++;

	if (UNIT_CATTRIBUTES(&bu->unit) & CA_MAXLEVEL10) 
	{
		if (bu->unit.level == 10) 
		{
			bu->expGain -= bu->unit.exp;
			bu->unit.exp = UNIT_EXP_DISABLED;
		}
	} 
	else if (bu->unit.level == 20) 
	{
		bu->expGain -= bu->unit.exp;
		bu->unit.exp = UNIT_EXP_DISABLED;
	}

	HookFunc_t *it = &OnLevelUpFuncList[0];
	
	while( *it )
		(*it++)(bu);
	
	CheckBattleUnitStatCaps(GetUnit(bu->unit.index), bu);
}