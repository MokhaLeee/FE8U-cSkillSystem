
#include "gbafe-chax.h"

const void* GetSkillIconGfx(int skill_id){
	
	if( !SKILL_VALID(skill_id) || (NULL == SkillInfoTable[skill_id]) )
		return 0;
	else
		return SkillInfoTable[skill_id]->icon;
	
}



int GetSkillNameMsg(int skill_id){
	
	if( !SKILL_VALID(skill_id) || (NULL == SkillInfoTable[skill_id]) )
		return 0;
	else
		return SkillInfoTable[skill_id]->msg_name;
	
}


int GetSkillDescMsg(int skill_id){
	
	if( !SKILL_VALID(skill_id) || (NULL == SkillInfoTable[skill_id]) )
		return 0;
	else
		return SkillInfoTable[skill_id]->msg_desc;
	
}




// Add skill misc
void ResetUnitRamSkillsList(struct Unit* unit){
	
	for( int i = 0; i < UNIT_SKILL_COUNT; i++ )
		unit->supports[i] = 0;
	
}

int AddSkill(struct Unit* unit, int skill_id){
	
	int i;
	
	if( 1 == (*SkillTester)(unit, skill_id) )
		return 0;
	
	if( !SKILL_VALID(skill_id) )
		return 0;
	
	for( i = 0; i < UNIT_SKILL_COUNT; i++ )
	{
		if( 0 == unit->supports[i] )
		{
			unit->supports[i] = skill_id;
			return 1;
		}
	}

	return 0;
}

int RemoveSkill(struct Unit* unit, int skill_id){
	
	if( !SKILL_VALID(skill_id) )
		return 0;
	
	for( int i = 0; i < UNIT_SKILL_COUNT; i++ )
		if( skill_id == unit->supports[i] )
			unit->supports[i] = 0;
	
	// To ensure skill not to be ROM skill
	return 0 == (*SkillTester)(unit, skill_id);
}

int GetUnitRamSkillCount(struct Unit* unit){
	
	int counter = 0;
	
	for ( int i = 0; i < UNIT_SKILL_COUNT; i++ )
		if ( SKILL_VALID(unit->supports[i]) )
			counter++;
	
	return counter;
}
