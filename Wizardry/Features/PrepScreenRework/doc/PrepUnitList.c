#include "prep-screen.h"

extern u8 gUnknown_020111CC[]; // Unit Stack Pool
extern int GetPrepScreenUnitListSize();
extern u8 GetSomeUnitId(); // Get Unit ID who must be attend
extern int IsUnitInCurrentRoster(struct Unit*);
extern int IsCharacterForceDeployed(int char_id);


// 8095674
int GetLeaderIndexInPrepUnitList(void){
	
	for (int i = 0; i < GetPrepScreenUnitListSize(); i++)
		if( GetSomeUnitId() == GetPrepScreenUnitListEntry(i)->index )
			return i;
	
	return 0;
}



// 80956A8
int sub_80956A8(void){
	
	extern u8 sub_8095394(); // Get some id of Unit List
	
	for (int i = 0; i < GetPrepScreenUnitListSize(); i++)
		if ( sub_8095394() == GetPrepScreenUnitListEntry(i)->index )
			return i;
	
	return 0;
}


// 80956D8
void ReorderPlayerUnitsBasedOnDeployment(){
	
	InitUnitStack(gUnknown_020111CC);
	
	
	// Deployed
	for( int i = 1; i < FACTION_GREEN; i++ ){
		
		struct Unit* unit = GetUnit(i);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		if( unit->state & (US_DEAD | US_NOT_DEPLOYED | US_BIT16) )
			continue;
		
		PushUnit(unit);
	}
	
	// non-deployed
	for( int i = 1; i < FACTION_GREEN; i++ ){
		
		struct Unit* unit = GetUnit(i);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		if( unit->state & (US_DEAD | US_NOT_DEPLOYED | US_BIT16) )
			PushUnit(unit);
	}
	
	LoadPlayerUnitsFromUnitStack();
}



void SortPlayerUnitsForPrepScreen(void){
	
	int list_len = 0;
	int max_unit_count = GetChapterAllyUnitCount();
	
	InitUnitStack(gUnknown_020111CC);
	
	// Force-deployed
	for( int i = 1; i < FACTION_GREEN; i++ ){
		
		struct Unit* unit = GetUnit(i);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		unit->state = unit->state & (~US_BIT25);
		
		if( 0 == IsUnitInCurrentRoster(unit) )
			continue;
		
		if( 0 == IsCharacterForceDeployed(unit->pCharacterData->number) )
			continue;
		
		PushUnit(unit);
	}
	
	
	// non-force-deployed
	for( int i = 1; i < FACTION_GREEN; i++ ){
		
		struct Unit* unit = GetUnit(i);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		if( 0 == IsUnitInCurrentRoster(unit) )
			continue;
		
		if( 0 == IsCharacterForceDeployed(unit->pCharacterData->number) )
			PushUnit(unit);
	}
	
	
	LoadPlayerUnitsFromUnitStack();
	
	
	for( int i = 1; i < FACTION_GREEN; i++ ){
		
		struct Unit* unit = GetUnit(i);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		if( 0 == IsUnitInCurrentRoster(unit) )
			continue;
		
		if( list_len > max_unit_count ){
			unit->state= unit->state | US_NOT_DEPLOYED;
			continue;
		}
		
		else{
			unit->state= unit->state & (~US_NOT_DEPLOYED);
			continue;
		}
		
	} // for
	
	
}




