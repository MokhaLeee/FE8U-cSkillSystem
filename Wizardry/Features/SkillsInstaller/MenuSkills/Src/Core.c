#include "gbafe-chax.h"

u8 DanceCommandUsability(const struct MenuItemDef* menu_item, int number){
	
	static u8 (*JudgeDanceUsabilityInternal)(const struct MenuItemDef*) = (const void*) 0x80230F1;
	
	if( !(*SkillTester)(gActiveUnit, SID_Dance) )
		return MENU_NOTSHOWN;
	
	gGameState.itemUnk2C = ITEM_DANCE;
	
	return JudgeDanceUsabilityInternal(menu_item);
}


u8 SupplyUsability(const struct MenuItemDef* menu_item, int number){
	
	if( 0 == HasConvoyAccess() )
		return MENU_NOTSHOWN;
	
	if( UNIT_IS_PHANTOM(gActiveUnit) )
		return MENU_NOTSHOWN;
	
	if( (*SkillTester)(gActiveUnit, SID_Supply) )
		return MENU_ENABLED;
	
	struct Vec2 vecs[4] = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
	};
	
	for( short i = 0; i < 4; i++ ){
		
		int unit_id = gBmMapUnit
			[gActiveUnit->yPos + vecs[i].y]
			[gActiveUnit->xPos + vecs[i].x];
		
		if( 0 == unit_id )
			continue;
		
		struct Unit* unit = GetUnit(unit_id);
		
		if( UNIT_FACTION(unit) != UNIT_FACTION(gActiveUnit) )
			continue;
		
		if( (*SkillTester)(unit, SID_Supply) )
			return MENU_ENABLED;
		
	}
	
	return MENU_NOTSHOWN;
}



int CheckSummonUsabilityCore(){
	
	// hacked function, SummonUsability
	// ORG 80243DC
	if( !(*SkillTester)(gActiveUnit, SID_Summon) )
		return 0;
	
	if( US_CANTOING & gActiveUnit->state )
		return 0;
	
	return 1;
}
	

int CheckStealUsabilityCore(){
	
	// hacked function, StealCommandUsability
	// ORG 8024190
	
	if( !(*SkillTester)(gActiveUnit, SID_Steal) )
		return 0;
	
	if( US_CANTOING & gActiveUnit->state )
		return 0;
	
	return 1;
}


int CheckPickUsabilityCore(){
	
	// hacked function, StealCommandUsability
	// ORG 8024190
	
	if( !(*SkillTester)(gActiveUnit, SID_LockTouch) )
		return 0;
	
	if( US_CANTOING & gActiveUnit->state )
		return 0;
	
	return 1;
}

