#include "gbafe-chax.h"

int CheckSkillDoubleLion(struct BattleUnit*);
int CheckSkillRuinedBladePlus(struct BattleUnit*);

// For DoubleLion: BattleOrder/HitCountCalc
int HitCountCalc_OrderSkills(struct BattleUnit* actor, int cur){
	
	// attacker cannot use brave if use combat-art
	if( CheckSkillDoubleLion(actor) )
		cur++;

	
	if( CheckSkillRuinedBladePlus(actor) )
		cur++;
		
	return cur;
	
}


int CheckSkillDoubleLion(struct BattleUnit* actor){
	
	struct Unit* unit_act = GetUnit(actor->unit.index);
	
	// attacker cannot use brave if use combat-art
	if( &gBattleActor == actor )
		if( (*SkillTester)(unit_act, SID_DoubleLion) )
			if( GetUnitCurrentHp(unit_act) == GetUnitMaxHp(unit_act) )
				return 1;
	
	return 0;
}
int CheckSkillRuinedBladePlus(struct BattleUnit* actor){
	return (*SkillTester)(&actor->unit, SID_RuinedBladePlus);
}


// Pre-Battle
void BC_SetDouleLionFlag(struct BattleUnit* actor, struct BattleUnit* target){
	
	if( CheckSkillDoubleLion(actor) )
		gpBattleFlagExt->doubleLion_activited = 1;
			
}