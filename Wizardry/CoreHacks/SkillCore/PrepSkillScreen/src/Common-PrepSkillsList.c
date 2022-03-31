#include "gbafe-chax.h"
#include "PrepSkill.h"

static void EnsureSkillAllListHaveTotalSkill();

void InitPrepSkillsList(void){
	ResetCommonSpace();
}


// W.I.P.
struct PrepSkillsList* MakeUnitPrepSkillsList(struct Unit* unit){
	
	InitPrepSkillsList();
	
	gpCommonSpace->unit_index = unit->index;
	
	gpCommonSpace->total[PREP_SKLSUB_LEFT_RAM] = 2;
	gpCommonSpace->skills_ram[0] = 0x14;
	gpCommonSpace->skills_ram[1] = 0x13;
	
	gpCommonSpace->total[PREP_SKLSUB_LEFT_ROM] = 1;
	gpCommonSpace->skills_rom[0] = 0x17;
	
	gpCommonSpace->total[PREP_SKLSUB_LEFT_CA] = 3;
	gpCommonSpace->skills_CombatArt[0] = 1;
	gpCommonSpace->skills_CombatArt[1] = 1;
	gpCommonSpace->skills_CombatArt[2] = 2;
	
	gpCommonSpace->skills_battalion = 1;
	
	EnsureSkillAllListHaveTotalSkill();
	
	return gpCommonSpace;
}


struct PrepSkillsList* GetUnitPrepSkillsList(struct Unit* unit){
	
	if( unit->index == gpCommonSpace->unit_index )
		return gpCommonSpace;
	
	else
		return MakeUnitPrepSkillsList(unit);
	
}


void EnsureSkillAllListHaveTotalSkill(){
	
	int count = 0;
	
	
	// RAM
	for( int i = 0; i < PREPSKILL_LISTLEN_RAM; i++ )
	{
		if( 0 == gpCommonSpace->skills_ram[i] )
			continue;
		
		gpCommonSpace->skills_all[count++] = gpCommonSpace->skills_ram[i];
	}
	
	// ROM
	for( int i = 0; i < PREPSKILL_LISTLEN_ROM; i++ )
	{
		if( 0 == gpCommonSpace->skills_rom[i] )
			continue;
		
		gpCommonSpace->skills_all[count++] = gpCommonSpace->skills_rom[i];
	}
	
	// counter
	gpCommonSpace->total[PREP_SKLSUB_RIGHT] = count;
	
	// free others
	for( int i = count; i <= PREPSKILL_LISTLEN_ALL; i++ )
		gpCommonSpace->skills_all[i] = 0;
	
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


