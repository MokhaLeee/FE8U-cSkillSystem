#include "gbafe-chax.h"


typedef s8(*Getter)(struct Unit* unit, u16 item);
extern Getter RangeMaxModify[];
extern Getter RangeMinModify[];
static s8 Get(struct Unit*, u16 item, Getter*);

int RangeMinGetter(u16 item, struct Unit* unit){
	
	int rng = GetItemMinRange(item);
	
	return rng;
}

int RangeMaxGetter(u16 item, struct Unit* unit){
	
	int rng = GetItemMaxRange(item);
	
	// to judge for unit mag when using staff
	if ( 0 == rng )
		return 0;
	
	rng += Get(unit, item, RangeMaxModify);
	
	if ( rng > 0xF )
		rng = 0xF;
	
	if ( rng < 0 )
		rng = 0;
	
	return rng;
}


int GetUnitMagBy2Range(struct Unit* unit){
	
	if (unit->pCharacterData->number == CHARACTER_FOMORTIIS)
		return GetItemMaxRange(ITEM_NIGHTMARE);
	
	else {
		int max = MagGetter(unit) / 2;
		
		// W.I.P. just give a magic weapon
		max += Get(unit, ITEM_ANIMA_FIRE, RangeMaxModify);
		
		if ( max > 0xF )
			max = 0xF;
		
		if ( max < 5 )
			max = 5;

		return max;
	}
}




static s8 Get(struct Unit* unit, u16 item, Getter funcs[]){
	
	s8 status = 0;
	Getter *it = &funcs[0];
	
	while( *it )
		status += (*it++)(unit, item);
	
	return status;
}
