#include "gbafe-chax.h"

static u8* GetWRankAt(struct Unit* unit, u8 wType){
	
	switch (wType){
		
		case ITYPE_SWORD:
		case ITYPE_LANCE:
		case ITYPE_AXE:
		case ITYPE_BOW:
		case ITYPE_STAFF:
		case ITYPE_ANIMA:
			return &unit->ranks[wType];
			break;
			
		case ITYPE_LIGHT:
		case ITYPE_DARK:
			return &unit->ranks[ITYPE_ANIMA];
			break;
		
		case ITYPE_RIDE:
			return &unit->ranks[ITYPE_LIGHT];
			break;
			
		case ITYPE_FLY:
			return &unit->ranks[ITYPE_DARK];
			break;
			
		case ITYPE_HEAVY:
			// for support list, since we have put them to bwl
			// so we get 7 byte free space
			// meanwhile, since skill-ram-list occupy 5 byte
			// so +5 and +6 is currently free
			return &unit->supports[5];
		
		case ITYPE_CLASS:
			return &unit->supports[6];
		
		default:
			return NULL;
	}
}

u8 GetWExp(struct Unit* unit, const u8 wType){
	
	if( NULL == GetWRankAt(unit, wType) )
		return 0;
	else
		return *GetWRankAt(unit, wType);
}


void SetWExp(struct Unit* unit, const u8 wType, u8 exp){
	
	if( NULL == GetWRankAt(unit, wType) )
		return;
	
	if(exp < WPN_EXP_S)
		*GetWRankAt(unit, wType) = exp;
	else
		*GetWRankAt(unit, wType) = WPN_EXP_S;
}

void AddWExp(struct Unit* unit, const u8 wType, u8 exp){
	SetWExp(unit, wType, exp + GetWExp(unit, wType) );
}


u16 GetWTypeMokhaIconIndex(u8 wType){
	
	switch( wType ){
		case ITYPE_SWORD:
		case ITYPE_LANCE:
		case ITYPE_AXE:
		case ITYPE_BOW:
		case ITYPE_STAFF:
		case ITYPE_ANIMA:
			return MASTERY_ICON( wType );
			break;
		
		case ITYPE_LIGHT:
		case ITYPE_DARK:
			return MASTERY_ICON( ITYPE_ANIMA );
			break;
		
		case ITYPE_RIDE:
			return  MASTERY_ICON( MASTERY_ICON_RIDE );
			break;
			
		case ITYPE_FLY:
			return  MASTERY_ICON( MASTERY_ICON_FLY );
			break;
			
		case ITYPE_HEAVY:
			return  MASTERY_ICON( MASTERY_ICON_HEAVY );
			break;
		
		case ITYPE_CLASS:
			return  MASTERY_ICON( MASTERY_ICON_STAR );
			break;
			
		default:
			return 0;
			break;
	}
		
}


u8 GetClassRankExpGain(u8 class_id){
	
	u8 rank_exp = GetClassRomDataExpa(class_id)->RankExp;
	
	return rank_exp == 0
		? 0x20
		: rank_exp;

}