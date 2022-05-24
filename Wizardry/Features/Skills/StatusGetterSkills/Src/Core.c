#include "gbafe-chax.h"

s8 PowGetter_Skills(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantStr) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur += 5;
	
	if( (*SkillTester)(unit, SID_RuinedBlade) )
		cur -= 5;
	
	if( (*SkillTester)(unit, SID_FortressDef) )
		cur -= 3;
	
	if( (*SkillTester)(unit, SID_FortressRes) )
		cur -= 3;
	
	if( (*SkillTester)(unit, SID_Fury) )
		cur += 3;
	
	if( (*SkillTester)(unit, SID_FuryPlus) )
		cur += 4;
	
	if( (*SkillTester)(unit, SID_HeavyBladePlus) )
		cur += 5;
	
	return cur;
	
}

s8 MagGetter_Skills(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantMag) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur += 5;
	
	if( (*SkillTester)(unit, SID_RuinedBlade) )
		cur -= 5;
	
	if( (*SkillTester)(unit, SID_FortressDef) )
		cur -= 3;
	
	if( (*SkillTester)(unit, SID_FortressRes) )
		cur -= 3;
	
	if( (*SkillTester)(unit, SID_Fury) )
		cur += 3;
	
	if( (*SkillTester)(unit, SID_FuryPlus) )
		cur += 4;
	
	return cur;
}


s8 SklGetter_Skills(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantSkl) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_Fury) )
		cur += 3;
	
	if( (*SkillTester)(unit, SID_FuryPlus) )
		cur += 4;
	
	return cur;
}

s8 SpdGetter_Skills(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantSpd) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur += 5;
	
	if( (*SkillTester)(unit, SID_RuinedBlade) )
		cur += 5;
	
	if( (*SkillTester)(unit, SID_RuinedBladePlus) )
		cur += 5;
	
	if( (*SkillTester)(unit, SID_Fury) )
		cur += 3;
	
	if( (*SkillTester)(unit, SID_FuryPlus) )
		cur += 4;
	
	return cur;
}

s8 LckGetter_Skills(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantLck) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_Fury) )
		cur += 3;
	
	if( (*SkillTester)(unit, SID_FuryPlus) )
		cur += 4;
	
	return cur;
}

s8 DefGetter_Skills(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantDef) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur -= 5;
	
	if( (*SkillTester)(unit, SID_FortressDef) )
		cur += 5;
	
	if( (*SkillTester)(unit, SID_Fury) )
		cur += 3;
	
	if( (*SkillTester)(unit, SID_FuryPlus) )
		cur += 4;
	
	return cur;
}

s8 ResGetter_Skills(struct Unit* unit, s8 cur){
	
	if( HpCurGetter(unit) < (HpMaxGetter(unit)/4) )
		if( (*SkillTester)(unit, SID_DefiantRes) )
			cur += 7;
	
	if( (*SkillTester)(unit, SID_LifeAndDeath) )
		cur -= 5;
	
	if( (*SkillTester)(unit, SID_FortressRes) )
		cur += 5;
	
	if( (*SkillTester)(unit, SID_Fury) )
		cur += 3;
	
	if( (*SkillTester)(unit, SID_FuryPlus) )
		cur += 4;
	
	return cur;
}