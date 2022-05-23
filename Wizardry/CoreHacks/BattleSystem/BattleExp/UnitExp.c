#include "gbafe-chax.h"


int GetUnitExpLevel(struct Unit* unit);
int GetUnitKillExpBonus(struct Unit* actor, struct Unit* target);
void ModifyUnitSpecialExp(struct Unit* actor, struct Unit* target, int* exp);


int GetUnitRoundExp(struct Unit* actor, struct Unit* target) {
	int expLevel;

	expLevel = GetUnitExpLevel(actor);
	expLevel = expLevel - GetUnitExpLevel(target);
	expLevel = 31 - expLevel;

	if (expLevel < 0)
		expLevel = 0;

	return expLevel / actor->pClassData->classRelativePower;
}


int GetBattleUnitExpGain(struct BattleUnit* actor, struct BattleUnit* target) {
	int result;

	if (!CanBattleUnitGainLevels(actor) || (actor->unit.curHP == 0) || UNIT_CATTRIBUTES(&target->unit) & CA_NEGATE_LETHALITY)
		return 0;

	if (!actor->nonZeroDamage)
		return 1;

	result = GetUnitRoundExp(&actor->unit, &target->unit);
	result += GetUnitKillExpBonus(&actor->unit, &target->unit);

	if (result > 100)
		result = 100;

	if (result < 1)
		result = 1;

	ModifyUnitSpecialExp(&actor->unit, &target->unit, &result);
	
	
	// To do: make a modular calc loop
	if( (*SkillTester)(&actor->unit, SID_RoyalLineage) )
		result += result / 4;	
	
	return result;
}



void BattleApplyExpGains(void) {
	if ((UNIT_FACTION(&gBattleActor.unit) != FACTION_BLUE) || (UNIT_FACTION(&gBattleTarget.unit) != FACTION_BLUE)) {
		if (!(gRAMChapterData.chapterStateBits & CHAPTER_FLAG_7)) {
			gBattleActor.expGain  = GetBattleUnitExpGain(&gBattleActor, &gBattleTarget);
			gBattleTarget.expGain = GetBattleUnitExpGain(&gBattleTarget, &gBattleActor);

			gBattleActor.unit.exp  += gBattleActor.expGain;
			gBattleTarget.unit.exp += gBattleTarget.expGain;

			CheckBattleUnitLevelUp(&gBattleActor);
			CheckBattleUnitLevelUp(&gBattleTarget);
		}
	}
}
