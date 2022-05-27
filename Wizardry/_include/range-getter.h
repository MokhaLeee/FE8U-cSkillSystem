#pragma once

#include "gbafe.h"
#include "map-master.h"


// Range Getter
int RangeMaxGetter(u16 item, struct Unit* unit);
int RangeMinGetter(u16 item, struct Unit* unit);

// UI
char* _GetUnitRangeString(struct Unit* unit);



// Fill Map Misc
u32 ItemRange2Mask(u16 item, struct Unit* unit);
void FillMapForSingleItem(struct Unit*, u16 item);	// Don't forget BmMapFill

/************************
Example:
BmMapFill(gBmMapMovement, NU_MOVE_MAP);
AddMapMaster(x, y, mask, NU_MOVE_MAP);
************************/
void AddMapMaster(int x, int y, u32 mask, int null_vall);
void ForEachUnitMaster( void(*func)(struct Unit*), u8*** work_map, int null_val);



// Is item covering range
int new_IsItemCoveringRange(int item, int range, struct Unit*);


