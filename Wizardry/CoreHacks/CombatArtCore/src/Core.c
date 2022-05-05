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
	
	const struct CombatArtInfo *info = GetCombatArtInfo(index);
	
	u8* list = GetCombatArtList(unit);
	
	if( NULL == list )
		return 0;
	
	for( int i = 0; i < 5; i++ )
		if( index == list[i] )
			for( int i = 0; i < UNIT_ITEM_COUNT; i++ )
			{
				u16 item = unit->items[i];
				
				if( 0 == (IA_WEAPON & GetItemAttributes(item)) )
					continue;
				
				if( info->weapon_type != GetItemType(item) )
					continue;
				
				if( ITEM_USES(item) >= info->cost )
					return 1;
			}
	
	return 0;
}

