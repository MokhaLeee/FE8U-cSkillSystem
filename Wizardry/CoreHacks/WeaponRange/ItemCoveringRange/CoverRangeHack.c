#include "gbafe-chax.h"


// 0x8016B8D
int new_IsItemCoveringRange(int item, int range, struct Unit* unit) {
    int min, max;
	
	if ( !UNIT_VAILD_MOKHA_JUDGE(unit) ) {
		min = GetItemMinRange(item);
		max = GetItemMaxRange(item);
	}
	else {
		min = RangeMinGetter(item, unit);
		max = RangeMaxGetter(item, unit);
	}
	
    if ((min <= range) && (range <= max))
        return 1;

    return 0;
}



// 
int CouldStationaryUnitBeInRangeHeuristic(struct Unit* actor, struct Unit* target, u16 item){
	
	return ( RangeMaxGetter(item, actor) + MovGetter(actor) )
		>= RECT_DISTANCE(actor->xPos, actor->yPos, target->xPos, target->yPos);
}