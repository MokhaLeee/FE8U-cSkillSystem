#include "gbafe-chax.h"

/*******************************

	Handle Skill Fast List

*******************************/


struct SkillFastTesterList* GetOrMakeSklFastList(struct Unit* unit) {
	
	struct SkillFastTesterList* list;
	
	if ( ! UNIT_IS_VALID(unit) )
		return NULL;
	
	if ( gpSkillFastList0->unit_id == unit->index )
		return gpSkillFastList0;
	
	if ( gpSkillFastList1->unit_id == unit->index )
		return gpSkillFastList1;
	
	
	// Get List
	if ( &gBattleTarget.unit == unit )
		list = gpSkillFastList1;
	else
		list = gpSkillFastList0;
	
	
	// Make list
	list->unit_id = unit->index;
	list->cnt = 0;
	
	for ( int i = 1; i < SKILL_MAX_COUNT; i++ ) {
		
		if ( 0 == JudgeSkill(unit,i) )
			continue;
		
		list->skills[list->cnt] = i;
		list->cnt++;
	
	} // for
	
	return list;
}


int GetSklFastListLen(struct Unit* unit) {
	
	return GetOrMakeSklFastList(unit)->cnt;
	
}


// On Chapter Init
void ResetSkillFastList(void){
	
	gpSkillFastList0->unit_id = 0;
	gpSkillFastList0->cnt = 0;
	
	gpSkillFastList1->unit_id = 0;
	gpSkillFastList1->cnt = 0;
	
}


void NullUnitSkills(struct Unit* unit) {
	
	GetOrMakeSklFastList(unit)->cnt = 0;
	
}