#include "gbafe-chax.h"

void BC_BattleStatusSkills(struct BattleUnit* act, struct BattleUnit*){
	
	struct Unit* unit_act = GetUnit(act->unit.index);
	
	// Lethality
	if( (*SkillTester)(unit_act, SID_Lethality) )
		act->battleSilencerRate += GetUnitSkill(unit_act);
	
	// Crit
	if( (*SkillTester)(unit_act, SID_Crit) )
		act->battleCritRate += 15;
	
	// WatchfulEye
	if( (*SkillTester)(unit_act, SID_WatchfulEye) )
		act->battleHitRate += 20;
	
	// Avoid
	if( (*SkillTester)(unit_act, SID_Avoid) )
		act->battleAvoidRate += 10;
	
	
	// Weapon Type Based Skills
	if( ITYPE_SWORD == act->weaponType ){
		
		if( (*SkillTester)(unit_act, SID_AvoidSword) )
			act->battleAvoidRate += 20;
		
		if( (*SkillTester)(unit_act, SID_CritSword) )
			act->battleCritRate += 10;
		
		if( (*SkillTester)(unit_act, SID_FaireSword) )
			act->battleAttack += 5;
	}
	
	
	else if( ITYPE_AXE == act->weaponType ){
		if( (*SkillTester)(unit_act, SID_CritAxe) )
			act->battleCritRate += 10;
		
		if( (*SkillTester)(unit_act, SID_FaireAxe) )
			act->battleAttack += 5;
	}
	
		
	else if( ITYPE_LANCE == act->weaponType ){
		if( (*SkillTester)(unit_act, SID_CritLance) )
			act->battleCritRate += 10;
		
		if( (*SkillTester)(unit_act, SID_FaireLance) )
			act->battleAttack += 5;
	}
	
		
			
	
	else if( ITYPE_BOW == act->weaponType ){
		if( (*SkillTester)(unit_act, SID_CritBow) )
			act->battleCritRate += 10;
		
		if( (*SkillTester)(unit_act, SID_FaireBow) )
			act->battleAttack += 5;
	}
	

	
	else if( (ITYPE_ANIMA == act->weaponType) || (ITYPE_LIGHT == act->weaponType) || (ITYPE_DARK == act->weaponType) ){
		if( (*SkillTester)(unit_act, SID_CritBMag) )
			act->battleCritRate += 10;
		
		if( (*SkillTester)(unit_act, SID_FaireBMag) )
			act->battleAttack += 5;
		
		
	}
	
		
			
	
}



