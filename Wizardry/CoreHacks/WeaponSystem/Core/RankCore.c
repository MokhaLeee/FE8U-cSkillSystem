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
		
		case MASTERY_ICON_RIDE:
			return &unit->ranks[ITYPE_LIGHT];
			break;
			
		case MASTERY_ICON_FLY:
			return &unit->ranks[ITYPE_DARK];
			break;
			
		case MASTERY_ICON_HEAVY:
			// for support list, since we have put them to bwl
			// so we get 7 byte free space
			// meanwhile, since skill-ram-list occupy 5 byte
			// so +5 and +6 is currently free
			// we catch support[5] as another rank
			return &unit->supports[5];
		
		default:
			return NULL;
	}
}

u8 GetWExp(struct Unit* unit, const u8 wType){
	return *GetWRankAt(unit, wType);
}


void SetWExp(struct Unit* unit, const u8 wType, u8 exp){
	if(exp < WPN_EXP_S)
		*GetWRankAt(unit, wType) = exp;
	else
		*GetWRankAt(unit, wType) = WPN_EXP_S;
}

