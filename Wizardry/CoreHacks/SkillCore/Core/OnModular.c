#include "gbafe-chax.h"

void LoadUnit_LoadSkill(struct Unit* unit){
	
	const struct SkillROMList* char_rom_list = &CharSkillRomList[unit->pCharacterData->number]; 
	const struct SkillROMList* class_rom_list = &ClassSkillRomList[unit->pClassData->number];
	
	ResetUnitRamSkillsList(unit);
	
	// default
	for( int i = 0; i < 4; i++ )
	{
		if( SKILL_VALID(char_rom_list->default_ram_skill[i]) )
			if( 0 == AddSkill(unit, char_rom_list->default_ram_skill[i]) )
				return;
		
		if( SKILL_VALID(class_rom_list->default_ram_skill[i]) )
			if( 0 == AddSkill(unit, class_rom_list->default_ram_skill[i]) )
				return;
	}
	
	// master
	if( unit->level < 10 )
		return;
	
	for( int i = 0; i < 4; i++ )
	{
		if( SKILL_VALID(char_rom_list->master_rom_skill[i]) )
			if( 0 == AddSkill(unit, char_rom_list->master_rom_skill[i]) )
				return;
		
		if( SKILL_VALID(class_rom_list->master_rom_skill[i]) )
			if( 0 == AddSkill(unit, class_rom_list->master_rom_skill[i]) )
				return;
	}
	
	
}