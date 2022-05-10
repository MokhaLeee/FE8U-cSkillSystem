#include "gbafe-chax.h"
#include "PrepSkill.h"

// =========================================================
//                        Static
// =========================================================


static void MakeTotalListSkill(struct Unit* unit, struct PrepSkillsList* list){
	
	const struct SkillROMList* char_rom_list = &CharSkillRomList[unit->pCharacterData->number]; 
	const struct SkillROMList* class_rom_list = &ClassSkillRomList[unit->pClassData->number];
	
	// Total Skills: add rom-skills
	// Character
	for( int i = 0; i < 4; i++ )
	{	
		if( SKILL_VALID(char_rom_list->default_ram_skill[i]) )
			list->skills_all[list->total[PREP_SKLSUB_RIGHT]++] 
				= char_rom_list->default_ram_skill[i];
		
		if( list->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
			break;
	}
	
	if( unit->level >= 10 )
		for( int i = 0; i < 4; i++ )
		{
			
			if( SKILL_VALID(char_rom_list->master_ram_skill[i]) )
				list->skills_all[list->total[PREP_SKLSUB_RIGHT]++] 
					= char_rom_list->master_ram_skill[i];
			
			if( list->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
				break;
		}
		
	// Class
	for( int i = 0; i < 4; i++ )
	{	
		if( SKILL_VALID(class_rom_list->default_ram_skill[i]) )
			list->skills_all[list->total[PREP_SKLSUB_RIGHT]++] 
				= class_rom_list->default_ram_skill[i];
		
		if( list->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
			break;
	}
	
	if( unit->level >= 10 )
		for( int i = 0; i < 4; i++ )
		{			
			if( SKILL_VALID(class_rom_list->master_ram_skill[i]) )
				list->skills_all[list->total[PREP_SKLSUB_RIGHT]++] 
					= class_rom_list->master_ram_skill[i];
			
			if( list->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
				break;
		}
}

static void MakeTotalListCombatArt(struct Unit* unit, struct PrepSkillsList* list){
	
	const u8 tmp_calist[18] = {
		CA_Grounder,
		CA_Soulblade,
		CA_BaneOfMonsters,
		CA_Sunder,
		CA_Hexblade,
		CA_HazeSlice,
		CA_FinesseBlade,
		CA_Windsweep,
		CA_Assassinate,
		CA_Subdue,
		CA_FoudroyantStrike,
		CA_SublimeHeaven,
		CA_RupturedHeaven,
		CA_HeavensFall,
		CA_TempestLance,
		CA_Knightkneeler,
		CA_CurvedShot,
		CA_HeavyDraw,
	};
	
	for( int i = 0; i < 18; i++ )
	{
		list->skills_all[ list->total[PREP_SKLSUB_RIGHT]++ ] = tmp_calist[i];
	
		if( list->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
			break;
	}
	
}




static void MakeLeftLists(struct Unit* unit, struct PrepSkillsList* prepList){
	
	const u8 * combatArt_list = GetCombatArtList(unit);
	struct SkillFastTesterList* skill_list = GetOrMakeSklFastList(unit);
	
	InitPrepSkillsList();
	
	prepList->unit_index = unit->index;
	prepList->total[PREP_SKLSUB_LEFT_RAM] = 0;
	prepList->total[PREP_SKLSUB_LEFT_ROM] = 0;
	prepList->total[PREP_SKLSUB_LEFT_CA] = 0;
	prepList->total[PREP_SKLSUB_RIGHT] = 0;
	
	
	// RAM Skills
	for( int i = 0; i < UNIT_SKILL_COUNT; i++ )
	{
		if( SKILL_VALID( unit->supports[i] ) )
		{
			int count = prepList->total[PREP_SKLSUB_LEFT_RAM];
			
			if( count >= PREPSKILL_LISTLEN_RAM )
				break;
			
			prepList->skills_ram[count] = unit->supports[i];
			prepList->total[PREP_SKLSUB_LEFT_RAM]++;
			
		}
	}
	
	
	// ROM Skills
	for( int i = 0; i < skill_list->cnt; i++ )
	{
		if( !isPrepSkillEquippedRAM(unit, skill_list->skills[i]) )
		{
			int count = prepList->total[PREP_SKLSUB_LEFT_ROM];
			
			if( count >= PREPSKILL_LISTLEN_ROM )
				break;
			
			prepList->skills_rom[count] = skill_list->skills[i];
			
			prepList->total[PREP_SKLSUB_LEFT_ROM]++;
		}
	}
	
	
	
	// Combat Arts
	if( NULL == combatArt_list )
	{
		prepList->total[PREP_SKLSUB_LEFT_CA] = 0;
	}
	else
		for( int i = 0; i < PREPSKILL_LISTLEN_CA; i++ )
			if( SKILL_VALID(combatArt_list[i]) )
				prepList->skills_CombatArt[ prepList->total[PREP_SKLSUB_LEFT_CA]++ ]
					= combatArt_list[i];

	
	
	// Battalion
	prepList->skills_battalion = 1;
}




// =========================================================
//                        Global
// =========================================================

void InitPrepSkillsList(void){
	ResetCommonSpace();
}



// W.I.P.
struct PrepSkillsList* MakeUnitPrepSkillsList(struct Unit* unit){
	
	MakeLeftLists(unit, gpCommonSpace);
	MakeTotalListSkill(unit, gpCommonSpace);
	return gpCommonSpace;
}


struct PrepSkillsList* GetUnitPrepSkillsList(struct Unit* unit){
	
	if( unit->index == gpCommonSpace->unit_index )
		return gpCommonSpace;
	
	else
		return MakeUnitPrepSkillsList(unit);
	
}


// W.I.P.
struct PrepSkillsList* MakeUnitPrepCombatArtsList(struct Unit* unit){
	
	MakeLeftLists(unit, gpCommonSpace);
	MakeTotalListCombatArt(unit, gpCommonSpace);
	return gpCommonSpace;
}


struct PrepSkillsList* GetUnitPrepCombatArtsList(struct Unit* unit){
	
	if( unit->index == gpCommonSpace->unit_index )
		return gpCommonSpace;
	
	else
		return MakeUnitPrepCombatArtsList(unit);
	
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



int isPrepCombatArtRAM(struct Unit* unit, u8 combatArt_id){
	
	struct PrepSkillsList* list;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_CA]; i++ )
		if( combatArt_id == list->skills_CombatArt[i] )
			return 1;
	
	return 0;
}













