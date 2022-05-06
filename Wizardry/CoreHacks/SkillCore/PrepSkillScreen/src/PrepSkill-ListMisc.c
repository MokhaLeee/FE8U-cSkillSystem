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
	gpCommonSpace->total[PREP_SKLSUB_RIGHT] = 0;
	
	// RAM Skills
	for( int i = 0; i < UNIT_SKILL_COUNT; i++ )
	{
		if( SKILL_VALID( unit->supports[i] ) )
		{
			int count = gpCommonSpace->total[PREP_SKLSUB_LEFT_RAM];
			
			if( count >= PREPSKILL_LISTLEN_RAM )
				break;
			
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
			
			if( count >= PREPSKILL_LISTLEN_ROM )
				break;
			
			gpCommonSpace->skills_rom[count] = list->skills[i];
			
			gpCommonSpace->total[PREP_SKLSUB_LEFT_ROM]++;
		}
	}
	
	
	
	// Combat Arts
	gpCommonSpace->skills_CombatArt[0] = CA_WrathStrike;
	gpCommonSpace->skills_CombatArt[1] = CA_BaneOfMonsters;
	gpCommonSpace->skills_CombatArt[2] = CA_TempestLance;
	
	
	// Battalion
	gpCommonSpace->skills_battalion = 1;
	
	
	// Total Skills: add rom-skills
	// Character
	for( int i = 0; i < 4; i++ )
	{	
		if( SKILL_VALID(char_rom_list->default_ram_skill[i]) )
			gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] 
				= char_rom_list->default_ram_skill[i];
		
		if( gpCommonSpace->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
			break;
	}
	
	if( unit->level >= 10 )
		for( int i = 0; i < 4; i++ )
		{
			
			if( SKILL_VALID(char_rom_list->master_ram_skill[i]) )
				gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] 
					= char_rom_list->master_ram_skill[i];
			
			if( gpCommonSpace->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
				break;
		}
		
	// Class
	for( int i = 0; i < 4; i++ )
	{	
		if( SKILL_VALID(class_rom_list->default_ram_skill[i]) )
			gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] 
				= class_rom_list->default_ram_skill[i];
		
		if( gpCommonSpace->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
			break;
	}
	
	if( unit->level >= 10 )
		for( int i = 0; i < 4; i++ )
		{			
			if( SKILL_VALID(class_rom_list->master_ram_skill[i]) )
				gpCommonSpace->skills_all[gpCommonSpace->total[PREP_SKLSUB_RIGHT]++] 
					= class_rom_list->master_ram_skill[i];
			
			if( gpCommonSpace->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
				break;
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






// ===========================================================
//                     Combat Art
// ===========================================================


// W.I.P.
struct PrepSkillsList* MakeUnitPrepCombatArtsList(struct Unit* unit){
	
	struct PrepSkillsList* list = gpCommonSpace;
	
	InitPrepSkillsList();
	
	list->unit_index = unit->index;
	list->total[PREP_SKLSUB_LEFT_CA] = 0;
	list->total[PREP_SKLSUB_RIGHT] = 0;
	
	
	// Combat Arts
	list->total[PREP_SKLSUB_LEFT_CA] = 3;
	list->skills_CombatArt[0] = CA_WrathStrike;
	list->skills_CombatArt[1] = CA_BaneOfMonsters;
	list->skills_CombatArt[2] = CA_TempestLance;
	
	const u8 tmp_calist[7] = {
		CA_WrathStrike,
		CA_Grounder,
		CA_BaneOfMonsters,
		CA_TempestLance,
		CA_Knightkneeler,
		CA_CurvedShot,
		CA_HeavyDraw,
	};
	
	for( int i = 0; i < 7; i++ )
	{
		list->skills_all[ list->total[PREP_SKLSUB_RIGHT]++ ] = tmp_calist[i];
	
		if( list->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
			break;
	}
	

	
	return list;
}


struct PrepSkillsList* GetUnitPrepCombatArtsList(struct Unit* unit){
	
	if( unit->index == gpCommonSpace->unit_index )
		return gpCommonSpace;
	
	else
		return MakeUnitPrepCombatArtsList(unit);
	
}






int isPrepCombatArtRAM(struct Unit* unit, u8 combatArt_id){
	
	struct PrepSkillsList* list;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_CA]; i++ )
		if( combatArt_id == list->skills_CombatArt[i] )
			return 1;
	
	return 0;
}


