#include "gbafe-chax.h"

void BC_BattleStatusSkills(struct BattleUnit* act, struct BattleUnit* tar){
	
	struct Unit* unit_act = GetUnit(act->unit.index);
	struct Unit* unit_tar = GetUnit(tar->unit.index);
	
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
	
	// Defainty
	if( HpCurGetter(unit_act) < (HpMaxGetter(unit_act)/4) ){
		
		if( (*SkillTester)(unit_act, SID_DefiantCrit) )
			act->battleCritRate += 50;
	
		if( (*SkillTester)(unit_act, SID_DefiantAvoid) )
			act->battleAvoidRate += 30;
	}
	
	// 刚柔剑
	if( act->battleAttack > tar->battleAttack ){
		
		if( (*SkillTester)(unit_act, SID_HeavyBlade) )
			act->battleCritRate += 15;
		
		if( (*SkillTester)(unit_act, SID_HeavyBladePlus) )
			act->battleCritRate += 25;
	}
	
	if( act->battleSpeed > tar->battleSpeed ){
		
		if( (*SkillTester)(unit_act, SID_FlashingBlade) )
			act->battleCritRate += 15;
		
		if( (*SkillTester)(unit_act, SID_FlashingBladePlus) )
			act->battleCritRate += 25;
	}
	
	// LunaAttack
	if( (*SkillTester)(unit_act, SID_LunaAttack) )
		act->battleAttack +=
			CheckMagAttack(act)
			? GetUnitResistance(unit_tar) / 4
			: GetUnitDefense(unit_tar) / 4;
	
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








