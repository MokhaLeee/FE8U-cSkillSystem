#include "gbafe-chax.h"

inline int GetMax(int a0, int a1, int a2){
	int max = a0 > a1 ? a0 : a1;
	max = max > a2 ? max : a2;
	
	return max;
}

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


int GetClassBaseWExp(u8 class_id, const u8 wType){
	
	const struct ClassRomDataExpa *ClassExpa = GetClassRomDataExpa(class_id);
	
	switch(wType){
		
		case ITYPE_SWORD:
		case ITYPE_LANCE:
		case ITYPE_AXE:
		case ITYPE_BOW:
		case ITYPE_WMAG:
			return gClassData[class_id].baseRanks[wType];
			break;
			
		case ITYPE_BMAG:
			return GetMax(
				gClassData[class_id].baseRanks[ITYPE_ANIMA],
				gClassData[class_id].baseRanks[ITYPE_LIGHT],
				gClassData[class_id].baseRanks[ITYPE_DARK]
				);
			break;
		
		case ITYPE_RIDE:
			return ClassExpa->rank_ride;
			break;
			
		case ITYPE_FLY:
			return ClassExpa->rank_fly;
			break;
			
		case ITYPE_HEAVY:
			return ClassExpa->rank_heavy;
			break;
			
		default:
			return 0;
			break;
	}
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
	
	int new_exp = exp + GetWExp(unit, wType);
	
	SetWExp(unit, wType, 
		new_exp > 0
			? new_exp
			: 0
	);
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
			return  MASTERY_ICON( MASTERY_ICON_AUTH); // MASTERY_ICON_STAR );
			break;
			
		default:
			return 0;
			break;
	}
		
}


