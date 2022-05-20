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
	
/* 	
 * this is too slow
 
	for ( int i = 1; i < SKILL_MAX_COUNT; i++ ) {
		
		if ( 0 == JudgeSkill(unit,i) )
			continue;
		
		list->skills[list->cnt] = i;
		list->cnt++;
	
	} // for */

		
	const struct SkillCharacterList_t* list_char = 
		&CharacterSkillRomList[unit->pCharacterData->number]; 
	
	const struct SkillClassList_t* list_class = 
		&ClassSkillRomList[unit->pClassData->number];
	
	// Character
	for( int i = 0; i < 2; i++ ){
		
		int skill_index = list_char->rom_skill[i];
		
		if( SKILL_VALID(skill_index) )	
			list->skills[list->cnt++] = skill_index;
	}

	
	// Class
	for( int i = 0; i < 2; i++ ){
		
		int skill_index = list_class->default_rom_skill[i];
		
		if( SKILL_VALID(skill_index) )	
			list->skills[list->cnt++] = skill_index;
	}
	
	if( unit->level >= 10 )
		for( int i = 0; i < 2; i++ ){
		
		int skill_index = list_class->master_rom_skill[i];
		
		if( SKILL_VALID(skill_index) )	
			list->skills[list->cnt++] = skill_index;
		}

	
	// RAM
	for ( int i = 0; i < UNIT_SKILL_COUNT; i++ )
	{
		int skill_index = unit->supports[i];
		
		if( SKILL_VALID(skill_index) )
			list->skills[list->cnt++] = skill_index;
	}

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