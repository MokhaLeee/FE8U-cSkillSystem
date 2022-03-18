#include "gbafe.h"
#include "gbafe-chax.h"


static int JudgeSkillRAM(struct Unit* unit, u8 skill_id){
	
	for ( int i = 0; i < UNIT_SKILL_COUNT; i++ )
		if ( skill_id == unit->supports[i] )
			return 1;
		
	return 0;
}


int JudgeSkill(struct Unit* unit, u8 skill_id) {
	
	// 0 = always true; 0xFF = always false
	if ( 0 == skill_id )
		return 1;
	
	if ( 0xFF == skill_id )
		return 0;
	
	
	// Judge RAM
	if ( 1 == JudgeSkillRAM(unit, skill_id) )
		return 1;
	
	return 0;
}





/*******************************

		Skill Tester Fast

*******************************/

int JudgeSkillFast(struct Unit* unit, u8 skill_id) {
	
	struct SkillFastTesterList* list;
	
	// 0 = always true; 0xFF = always false
	if ( 0 == skill_id )
		return 1;
	
	if ( 0xFF == skill_id )
		return 0;
	
	
	list = GetOrMakeSklFastList(unit);
	
	for ( int i = 0; i < list->cnt; i++){
		
		if ( skill_id == list->skills[i] )
			return 1;
	
	} // for
		
	return 0;
	
	
}


