#include "gbafe-chax.h"
#include "PrepSkill.h"

// =========================================================
//                        Static
// =========================================================


static int AddPrepSkilTotalList(struct PrepSkillsList* list, const int index){
	
	if( list->total[PREP_SKLSUB_RIGHT] >= PREPSKILL_LISTLEN_ALL )
		return 0;
	
	for( int i = 0; i < list->total[PREP_SKLSUB_RIGHT]; i++ )
		if( index == list->skills_all[i] )
			return 1;
	
	list->skills_all[ list->total[PREP_SKLSUB_RIGHT]++ ] = index;
	return 1;
}


static void MakeTotalListSkill(struct Unit* unit, struct PrepSkillsList* list){
	
	#define ADD_SKILL(aSkill)								\
		if( SKILL_VALID(aSkill) )							\
			if( 0 == AddPrepSkilTotalList(list, aSkill) )	\
				return;
	
	int WeaponRanks[8];
	const int num_clas = unit->pClassData->number;
	const int num_char = unit->pCharacterData->number;
	
	const struct SkillClassList_t* ListClass = 
		&ClassSkillRomList[num_clas];
	
	list->total[PREP_SKLSUB_RIGHT] = 0;
	
	// Class Normal List
	for( int i = 0; i < 2; i++ ){
		
		ADD_SKILL(ListClass->default_ram_skill[i]);
		
		if( unit->level >= 10 )
			ADD_SKILL(ListClass->master_ram_skill[i]);

	}
	
	
	
	for( int i = 0; i < 8; i++ )
		WeaponRanks[i] = GetWeaponLevelFromExp(unit->ranks[i]);
	
	switch( WeaponRanks[ITYPE_SWORD] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].S[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].A[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].B[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].C[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].D[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].E[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	
	switch( WeaponRanks[ITYPE_LANCE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].S[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].A[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].B[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].C[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].D[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].D[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].D[1]);
		
		default:
			break;
	}
	
	
	switch( WeaponRanks[ITYPE_AXE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].S[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].A[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].B[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].C[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].D[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].D[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].D[1]);
		
		default:
			break;
	}
	
	
	
	
	switch( WeaponRanks[ITYPE_BOW] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].S[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].A[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].B[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].C[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].D[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].E[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].E[1]);
		
		default:
			break;
	}
	
	int max = WeaponRanks[ITYPE_ANIMA];
	max = (max < WeaponRanks[ITYPE_LIGHT]) ? max : WeaponRanks[ITYPE_LIGHT];
	max = (max < WeaponRanks[ITYPE_DARK]) ? max : WeaponRanks[ITYPE_DARK];

	
	switch( max ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].S[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].A[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].B[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].C[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].D[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].E[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	
	switch( WeaponRanks[ITYPE_STAFF] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].S[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].A[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].B[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].C[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].D[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].E[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].E[1]);
		
		default:
			break;
	}
	
	#undef ADD_SKILL
}

static void MakeTotalListCombatArt(struct Unit* unit, struct PrepSkillsList* list){
	#define ADD_SKILL(aSkill)								\
		if( SKILL_VALID(aSkill) )							\
			if( 0 == AddPrepSkilTotalList(list, aSkill) )	\
				return;
	
	int WeaponRanks[7];
	const int num_clas = unit->pClassData->number;
	const int num_char = unit->pCharacterData->number;
	
	list->total[PREP_SKLSUB_RIGHT] = 0;

	
	for( int i = 0; i < 7; i++ )
		WeaponRanks[i] = GetWeaponLevelFromExp(unit->ranks[i]);
	
	switch( WeaponRanks[ITYPE_SWORD] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelCASword_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].S[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].S[1]);
			ADD_SKILL(LevelCASword_CharList[0].S[0]);
			ADD_SKILL(LevelCASword_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelCASword_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].A[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].A[1]);
			ADD_SKILL(LevelCASword_CharList[0].A[0]);
			ADD_SKILL(LevelCASword_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelCASword_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].B[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].B[1]);
			ADD_SKILL(LevelCASword_CharList[0].B[0]);
			ADD_SKILL(LevelCASword_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelCASword_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].C[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].C[1]);
			ADD_SKILL(LevelCASword_CharList[0].C[0]);
			ADD_SKILL(LevelCASword_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelCASword_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].D[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].D[1]);
			ADD_SKILL(LevelCASword_CharList[0].D[0]);
			ADD_SKILL(LevelCASword_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelCASword_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].E[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].E[1]);
			ADD_SKILL(LevelCASword_CharList[0].E[0]);
			ADD_SKILL(LevelCASword_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	
	switch( WeaponRanks[ITYPE_LANCE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelCALance_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].S[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].S[1]);
			ADD_SKILL(LevelCALance_CharList[0].S[0]);
			ADD_SKILL(LevelCALance_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelCALance_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].A[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].A[1]);
			ADD_SKILL(LevelCALance_CharList[0].A[0]);
			ADD_SKILL(LevelCALance_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelCALance_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].B[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].B[1]);
			ADD_SKILL(LevelCALance_CharList[0].B[0]);
			ADD_SKILL(LevelCALance_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelCALance_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].C[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].C[1]);
			ADD_SKILL(LevelCALance_CharList[0].C[0]);
			ADD_SKILL(LevelCALance_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelCALance_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].D[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].D[1]);
			ADD_SKILL(LevelCALance_CharList[0].D[0]);
			ADD_SKILL(LevelCALance_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelCALance_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].E[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].E[1]);
			ADD_SKILL(LevelCALance_CharList[0].D[0]);
			ADD_SKILL(LevelCALance_CharList[0].D[1]);
		
		default:
			break;
	}
	
	
	switch( WeaponRanks[ITYPE_AXE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].S[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].S[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].S[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].A[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].A[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].A[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].B[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].B[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].B[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].C[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].C[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].C[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].D[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].D[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].D[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].E[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].E[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].D[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].D[1]);
		
		default:
			break;
	}
	
	
	
	
	switch( WeaponRanks[ITYPE_BOW] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelCABow_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].S[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].S[1]);
			ADD_SKILL(LevelCABow_CharList[0].S[0]);
			ADD_SKILL(LevelCABow_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelCABow_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].A[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].A[1]);
			ADD_SKILL(LevelCABow_CharList[0].A[0]);
			ADD_SKILL(LevelCABow_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelCABow_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].B[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].B[1]);
			ADD_SKILL(LevelCABow_CharList[0].B[0]);
			ADD_SKILL(LevelCABow_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelCABow_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].C[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].C[1]);
			ADD_SKILL(LevelCABow_CharList[0].C[0]);
			ADD_SKILL(LevelCABow_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelCABow_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].D[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].D[1]);
			ADD_SKILL(LevelCABow_CharList[0].D[0]);
			ADD_SKILL(LevelCABow_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelCABow_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].E[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].E[1]);
			ADD_SKILL(LevelCABow_CharList[0].E[0]);
			ADD_SKILL(LevelCABow_CharList[0].E[1]);
		
		default:
			break;
	}
	
	#undef ADD_SKILL
	
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













