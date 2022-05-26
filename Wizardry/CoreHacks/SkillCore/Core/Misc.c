
#include "gbafe-chax.h"

// For Icon Display
const void* GetSkillIconGfx(int skill_id){
	
	const struct SkillInfo* info = SkillInfoTable[skill_id];
	
	if( !SKILL_VALID(skill_id) || (0 == info) || (0 == info->icon) )
		return SkillIcon_WIP;
	
	else
		return info->icon;
	
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





// For Load Unit Hook
void LoadUnit_LoadSkill(struct Unit* unit){
	
	#define ADD_SKILL(aSkill) 				\
		if( SKILL_VALID(aSkill) )			\
			if( 0 == AddSkill(unit, aSkill) )	\
				return;
	
	const int num_clas = unit->pClassData->number;
	const int num_char = unit->pCharacterData->number;
	
	const struct SkillClassList_t* ListClass = 
		&ClassSkillRomList[num_clas];
	
	ResetUnitRamSkillsList(unit);
	
	
	// Class Normal List
	for( int i = 0; i < 2; i++ ){
		
		ADD_SKILL(ListClass->default_ram_skill[i]);
		
		if( unit->level >= 10 )
			ADD_SKILL(ListClass->master_ram_skill[i]);

	}
	
	u8 WeaponRanks[0x12];
	
	#define SET_WTYPE_RANK(wtype){		\
		WeaponRanks[wtype] = 			\
			GetWeaponLevelFromExp( GetWExp(unit, wtype) );	\
	}
	
	SET_WTYPE_RANK(ITYPE_SWORD);
	SET_WTYPE_RANK(ITYPE_LANCE);
	SET_WTYPE_RANK(ITYPE_AXE);
	SET_WTYPE_RANK(ITYPE_BOW);
	
	SET_WTYPE_RANK(ITYPE_BMAG);
	SET_WTYPE_RANK(ITYPE_WMAG);
	
	SET_WTYPE_RANK(ITYPE_RIDE);
	SET_WTYPE_RANK(ITYPE_FLY);
	SET_WTYPE_RANK(ITYPE_HEAVY);

	#undef SET_WTYPE_RANK
	
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
	

	switch( WeaponRanks[ITYPE_BMAG] ){
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
	
	
	
	switch( WeaponRanks[ITYPE_WMAG] ){
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





