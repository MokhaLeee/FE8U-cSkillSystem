#include "gbafe-chax.h"

int RangeMaxGetter_SkillBonus(struct Unit* unit, u16 item, int cur){
	
	const int type = GetItemType(item);
	
	if( ITYPE_BOW == type )
	{
		if( (*SkillTester)(unit, SID_RangeBonusBow1) )
			cur += 1;
		
		if( (*SkillTester)(unit, SID_RangeBonusBow2) )
			cur += 2;
	}
	
	
	if( (ITYPE_ANIMA==type) || (ITYPE_LIGHT==type) || (ITYPE_DARK==type) )
	{
		if( (*SkillTester)(unit, SID_RangeBonusBMag1) )
			cur += 1;
		
		if( (*SkillTester)(unit, SID_RangeBonusBMag2) )
			cur += 2;
	}
	
	return cur;
}