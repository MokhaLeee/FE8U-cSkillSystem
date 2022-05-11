#include "gbafe-chax.h"

void BC_BattleStatusSkills(struct BattleUnit* act, struct BattleUnit*){
	
	struct Unit* unit_act = GetUnit(act->unit.index);
	
	// Skill: SID_Lethality
	if( (*SkillTester)(unit_act, SID_Lethality) )
		act->battleSilencerRate += GetUnitSkill(unit_act);
	
	// Skill: SID_Crit
	if( (*SkillTester)(unit_act, SID_Crit) )
		act->battleCritRate += 15;
}



