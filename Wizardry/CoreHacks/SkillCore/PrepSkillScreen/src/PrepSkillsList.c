#include "gbafe-chax.h"
#include "PrepSkillsList.h"

void InitPrepSkillsList(void){
	ResetCommonSpace();
}


// W.I.P.
struct PrepSkillsList* MakeUnitPrepSkillsList(struct Unit* unit){
	
	gpCommonSpace->unit_index = unit->index;
	gpCommonSpace->total = 5;
	
	for( int i = 0; i < 5; i++ )
		gpCommonSpace->skills[i] = 0x13 + i;
	
	return gpCommonSpace;
}


struct PrepSkillsList* GetUnitPrepSkillsList(struct Unit* unit){
	
	if( unit->index == gpCommonSpace->unit_index )
		return gpCommonSpace;
	
	else
		return MakeUnitPrepSkillsList(unit);
	
}


int PrepSkillAddRamSkillFromList(struct Unit* unit, u8 skill_id){
	
	// 两种失败的情况:
	// 1. Unit RAM有五个
	// 2. Unit 已经有这个技能了
	// 3. List 中不存在
	
	struct PrepSkillsList* list;
	
	if( 0 != (*SkillTester)(unit, skill_id) )
		return 0;
	
	if( !(GetUnitRamSkillCount(unit) < UNIT_SKILL_COUNT) )
		return 0;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < list->total; i++ )
		if( skill_id == list->skills[i] )
			return AddSkill(unit, skill_id);

	return 0;


}


