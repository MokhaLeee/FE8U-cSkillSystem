#include "gbafe-chax.h"
#include "PrepSkill.h"


void InitPrepSkillsList(void){
	ResetCommonSpace();
}


// W.I.P.
struct PrepSkillsList* MakeUnitPrepSkillsList(struct Unit* unit){
	
	const struct SkillROMList* char_rom_list = &CharSkillRomList[unit->pCharacterData->number]; 
	const struct SkillROMList* class_rom_list = &ClassSkillRomList[unit->pClassData->number];
	struct SkillFastTesterList* list;
	
	InitPrepSkillsList();
	list = GetOrMakeSklFastList(unit);
	
	gpCommonSpace->unit_index = unit->index;
	gpCommonSpace->total[PREP_SKLSUB_LEFT_RAM] = 0;
	gpCommonSpace->total[PREP_SKLSUB_LEFT_ROM] = 0;
	gpCommonSpace->total[PREP_SKLSUB_LEFT_CA] = 0;
	
	// RAM Skills
	for( int i = 0; i < UNIT_SKILL_COUNT; i++ )
	{
		if( SKILL_VALID( unit->supports[i] ) )
		{
			int count = gpCommonSpace->total[PREP_SKLSUB_LEFT_RAM];
			
			gpCommonSpace->skills_ram[count] = unit->supports[i];
			gpCommonSpace->total[PREP_SKLSUB_LEFT_RAM]++;
			
		}
	}
	
	
	// ROM Skills
	for( int i = 0; i < list->cnt; i++ )
	{
		if( !isPrepSkillEquippedRAM(unit, list->skills[i]) )
		{
			int count = gpCommonSpace->total[PREP_SKLSUB_LEFT_ROM];
			gpCommonSpace->skills_rom[count] = list->skills[i];
			gpCommonSpace->total[PREP_SKLSUB_LEFT_ROM]++;
		}
	}
	
	
	
	// Combat Arts
	gpCommonSpace->skills_CombatArt[0] = 1;
	gpCommonSpace->skills_CombatArt[1] = 1;
	gpCommonSpace->skills_CombatArt[2] = 2;
	
	
	// Battalion
	gpCommonSpace->skills_battalion = 1;
	
	
	// Total Skills: add rom-skills
	// Character
	for( int i = 0; i < 4; i++ )
	{
		if( gpCommonSpace->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
			break;
		
		if( SKILL_VALID(char_rom_list->default_rom_skill[i]) )
			gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] = char_rom_list->default_rom_skill[i];
		
		if( SKILL_VALID(char_rom_list->default_ram_skill[i]) )
			gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] = char_rom_list->default_ram_skill[i];
	}
	
	if( unit->level >= 10 )
		for( int i = 0; i < 4; i++ )
		{
			if( gpCommonSpace->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
				break;
		
			if( SKILL_VALID(char_rom_list->master_rom_skill[i]) )
				gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] = char_rom_list->master_rom_skill[i];
			
			if( SKILL_VALID(char_rom_list->master_ram_skill[i]) )
				gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] = char_rom_list->master_ram_skill[i];
		}
		
	// Class
	for( int i = 0; i < 4; i++ )
	{
		if( gpCommonSpace->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
			break;
		
		if( SKILL_VALID(class_rom_list->default_rom_skill[i]) )
			gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] = class_rom_list->default_rom_skill[i];
		
		if( SKILL_VALID(class_rom_list->default_ram_skill[i]) )
			gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] = class_rom_list->default_ram_skill[i];
	}
	
	if( unit->level >= 10 )
		for( int i = 0; i < 4; i++ )
		{
			if( gpCommonSpace->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
				break;
		
			if( SKILL_VALID(class_rom_list->master_rom_skill[i]) )
				gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] = class_rom_list->master_rom_skill[i];
			
			if( SKILL_VALID(class_rom_list->master_ram_skill[i]) )
				gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] = class_rom_list->master_ram_skill[i];
		}
	
	
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
	
	for( int i = 0; i < 24; i++ )
		if( skill_id == list->skills_all[i] )
			return AddSkill(unit, skill_id);

	return 0;


}











// Misc judgement
int IsPrepSkillListValid(){
	
	return !(0 == gpCommonSpace->unit_index);
}


int IsPrepSkillRom(struct Unit* unit, const u8 skill_id){
	
	struct PrepSkillsList* list;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_ROM]; i++ )
		if( skill_id == list->skills_rom[i] )
			return 1;
	
	return 0;
}

int isPrepSkillEquippedRAM(struct Unit* unit, u8 skill_id){
	
	struct PrepSkillsList* list;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_RAM]; i++ )
		if( skill_id == list->skills_ram[i] )
			return 1;
	
	return 0;
}

