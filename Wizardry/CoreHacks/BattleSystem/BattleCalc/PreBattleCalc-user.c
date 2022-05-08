#include "gbafe-chax.h"

void BC_Lethality(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	struct Unit* unit_act = GetUnit(attacker->unit.index);

	
	// CA_Assassinate
	if( gpBattleFlagExt->isCombat && (&gBattleActor == attacker) )
		if( CA_Assassinate == gpBattleFlagExt->combatArt_id )
			attacker->battleSilencerRate += GetUnitSkill(unit_act) + GetUnitLuck(unit_act);

	// Skill: SID_Lethality
	if( (*SkillTester)(unit_act, SID_Lethality) )
		attacker->battleSilencerRate += GetUnitSkill(unit_act);
	
	// BOSS
	if (UNIT_CATTRIBUTES(&defender->unit) & CA_BOSS)
		attacker->battleSilencerRate -= 30;
	
	
	// Asigned
	if( attacker->battleSilencerRate < 0 )
		attacker->battleSilencerRate  = 0;
	
	if( attacker->battleSilencerRate > 100 )
		attacker->battleSilencerRate = 100;
}