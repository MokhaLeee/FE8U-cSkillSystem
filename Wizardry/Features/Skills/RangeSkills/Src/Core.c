#include "gbafe-chax.h"

int RangeMaxGetter_SkillBonus(struct Unit* unit, u16 item, int cur){
	
	const int wtype = GetItemType(item);
	
	switch(wtype){
		
		case ITYPE_BOW:
			if( (*SkillTester)(unit, SID_RangeBonusBow1) )
				cur += 1;
			
			if( (*SkillTester)(unit, SID_RangeBonusBow1_ext) )
				cur += 1;
			
			if( (*SkillTester)(unit, SID_RangeBonusBow2) )
				cur += 2;
			
			break;
		
		case ITYPE_ANIMA:
		case ITYPE_LIGHT:
		case ITYPE_DARK:
			if( (*SkillTester)(unit, SID_RangeBonusBMag1) )
				cur += 1;
			
			if( (*SkillTester)(unit, SID_RangeBonusBMag1_ext) )
				cur += 1;
			
			if( (*SkillTester)(unit, SID_RangeBonusBMag2) )
				cur += 2;
			
			break;
		
		default:
			break;
	}
	
	
	
	return cur;
}