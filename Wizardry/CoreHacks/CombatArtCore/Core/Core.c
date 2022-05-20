#include "gbafe-chax.h"

const struct CombatArtInfo* GetCombatArtInfo(u8 index){
	
	return CombatArtInfoTable[index];
	
};

u8* GetCombatArtList(struct Unit* unit){
	
	struct NewBwlData* bwl;
	u8 char_id = unit->pCharacterData->number;
	
	// we use bwl table!
	if( !NBwl_HasBwl(char_id) )
		return NULL;
	
	bwl = NBwl_GetBwlData(char_id);
	return bwl->combatArts;
}


int UnitHasCombatArt(struct Unit* unit){
	
	u8* list = GetCombatArtList(unit);
	
	if( NULL != list )
		for( int i = 0; i < 5; i++ )
			if( SKILL_VALID(list[i]) )
				return 1;
	
	return 0;
	
}

int CanUnitUseCombatArt(struct Unit* unit, u8 index){
	
	u8* list = GetCombatArtList(unit);
	
	if( NULL == list )
		return 0;

	int i = 0;
	
	while( index != list[i++] )
		if( i >= 5 )
			return 0;

	for( i = 0; i < UNIT_ITEM_COUNT; i++ )
		if( CanUnitWithWeaponUseCombatArt(unit, unit->items[i], index) )
			return 1;
		
	return 0;
}


int CanUnitWithWeaponUseCombatArt(struct Unit* unit, u16 weapon, u8 index){
	
	const struct CombatArtInfo *info = GetCombatArtInfo(index);
	
	if( NULL == info )
		return 0;
	
	if( 0 == (IA_WEAPON & GetItemAttributes(weapon)) )
		return 0;
	
	if( info->cost >= ITEM_USES(weapon) )
		return 0;
	
	return info->weapon_type == GetItemType(weapon);
	
}


// remove skill
int RemoveCombatArt(struct Unit* unit, const u8 index){
	
	u8* list = GetCombatArtList(unit);
	
	if( NULL == list )
		return 0;
	
	for( int i = 0; i < 5; i++ )
		if( index == list[i] )
		{
			list[i] = 0;
			return 1;
		}
	
	return 0;
}



// add skill
int AddCombatArt(struct Unit* unit, const u8 index){
	
	u8* list = GetCombatArtList(unit);
	
	if( NULL == list )
		return 0;
	
	for( int i = 0; i < 5; i++ ){
		
		if( index == list[i] )
			return 1;
		
		if( !SKILL_VALID(list[i]) ){
			list[i] = index;
			return 1;
		}
	}
	
	return 0;
}


// get total combat-arts count
int GetUnitTotalCombatArtsCount(struct Unit* unit){
	
	int count = 0;
	u8* list = GetCombatArtList(unit);
	
	if( NULL == list )
		return 0;
	
	for( int i = 0; i < 5; i++ )
		if( SKILL_VALID(list[i]) )
			count++;
	
	return count;
	
}



// For Battle-Flag-Ext
void EnableCombatArtFlag(struct Unit* unit, u8 combatArt_index){
	
	gpBattleFlagExt->isCombat = 1;
	gpBattleFlagExt->combatArt_id = combatArt_index;
	gpBattleFlagExt->combat_unit = unit->index;
}


void DisableCombatArtFlag(){
	
	gpBattleFlagExt->isCombat = 0;
	gpBattleFlagExt->combatArt_id = 0;
	gpBattleFlagExt->combat_unit = 0;
}


int IsFlagCombatArt(struct Unit* unit, u8 combatArt_index){
	
	if( 0 == gpBattleFlagExt->isCombat )
		return 0;
	
	if( 0 != combatArt_index )
		if( combatArt_index != gpBattleFlagExt->combatArt_id )
			return 0;
	
	if( unit->index != gpBattleFlagExt->combat_unit )
		return 0;
	
	return 1;
}