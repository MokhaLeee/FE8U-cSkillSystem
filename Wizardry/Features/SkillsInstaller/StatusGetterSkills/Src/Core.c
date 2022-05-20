#include "gbafe-chax.h"

s8 PowGetter_DefaintSkill(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantStr) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur += 5;
	
	return cur;
	
}

s8 MagGetter_DefaintSkill(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantMag) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur += 5;
	
	return cur;
}


s8 SklGetter_DefaintSkill(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantSkl) )
			cur += 7;
	
	return cur;
}

s8 SpdGetter_DefaintSkill(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantSpd) )
			cur += 7;
	
	return cur;
}

s8 LckGetter_DefaintSkill(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantLck) )
			cur += 7;
	
	return cur;
}

s8 DefGetter_DefaintSkill(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantDef) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur -= 5;
	
	return cur;
}

s8 ResGetter_DefaintSkill(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantRes) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur -= 5;
	
	return cur;
}