#include "gbafe-chax.h"


// 0x801CB70+1
void DisplayUnitEffectRange(struct Unit* unit){
	
	extern struct Struct0202BCB0 gGameState;
	
	enum{
		FLAG_RANGE_RED = 1 << 0,
		FLAG_RANGE_GREEN = 1 << 1,
	};
	
	u8 useFlag;
	
	BmMapFill(gBmMapMovement,NU_MOVE_MAP);
	BmMapFill(gBmMapOther,NU_MOVE2_MAP);
	BmMapFill(gBmMapRange,NU_RANGE_MAP);
	
	GenerateUnitMovementMapExt(
		gActiveUnit, 
		MovGetter(gActiveUnit) - gActionData.moveCount 
	);
	
	if( unit->state & US_CANTOING ){
		DisplayMoveRangeGraphics(MOV_BLUE);
		return;
	}
	
	
	
	useFlag = GetUnitWeaponUsabilityBits(unit);
	
	if( FACTION_BLUE == UNIT_FACTION(gActiveUnit) )
	{
	/* 	if( MCA_NONUSABLE != BMag_Usability() )
			useFlag |= FLAG_RANGE_RED;
		
		if( MCA_NONUSABLE != WMag_Usability() )
			useFlag |= FLAG_RANGE_GREEN; */
		
	} // if( FACTION_BLUE == UNIT_FACTION(gActiveUnit) )
	

	if( useFlag == (FLAG_RANGE_RED + FLAG_RANGE_GREEN) )
	{
		if( gGameState.unk3E & 0b01 ) // MapDisplayBit
			useFlag = FLAG_RANGE_GREEN;
		else
			useFlag = FLAG_RANGE_RED;
		
	} // if( useFlag == (FLAG_RANGE_RED + FLAG_RANGE_GREEN) )
		
	if( FLAG_RANGE_RED == useFlag )
	{
		GenerateUnitCompleteAttackRange(unit);
		DisplayMoveRangeGraphics(RNG_RED + MOV_BLUE);
	}
	else if( FLAG_RANGE_GREEN == useFlag )
	{
		GenerateUnitCompleteStaffRange(unit);
		DisplayMoveRangeGraphics(RNG_GREEN + MOV_BLUE);
	}
	else
		DisplayMoveRangeGraphics(MOV_BLUE);
}



void GenerateUnitMovementMap(struct Unit* unit)
{
	SetWorkingMoveCosts(GetUnitMovementCost(unit));
	SetWorkingBmMap(gBmMapMovement);

	GenerateMovementMap(unit->xPos, unit->yPos, MovGetter(unit), unit->index);
}




void GenerateUnitCompleteAttackRange(struct Unit* unit)
{
	int mask;
	
	// make mask
	mask = GetUnitWeaponReachBits(unit, -1);
	
	if (UNIT_CATTRIBUTES(unit) & CA_BALLISTAE) {
		
		int item = GetBallistaItemAt(unit->xPos, unit->yPos);
		
		if( 0 != item )
			mask |= ItemRange2Mask(item, unit);
	}
            
	// Fill map
	BmMapFill(gBmMapRange,NU_RANGE_MAP);
	
	for( int y = 0; y < gBmMapSize.y; y++ )
		for( int x = 0; x < gBmMapSize.x; x++ ) {
			
			if (gBmMapMovement[y][x] > MAP_MOVEMENT_MAX)
				continue;
			if (gBmMapUnit[y][x])
				continue;
			if (gBmMapOther[y][x])
				continue;
			
			AddMapMaster(x,y,mask,NU_RANGE_MAP);
		}
	
	 SetWorkingBmMap(gBmMapMovement);

}



void GenerateUnitStandingReachRange(struct Unit* unit, int mask) {
	
	BmMapFill(gBmMapRange, NU_RANGE_MAP);
	AddMapMaster(unit->xPos, unit->yPos, mask, NU_RANGE_MAP);
	
}



void GenerateUnitCompleteStaffRange(struct Unit* unit) {
	
	int mask = GetUnitStaffReachBits(unit);
	BmMapFill(gBmMapRange,NU_RANGE_MAP);
	
	for( int y = 0; y < gBmMapSize.y; y++ )
		for( int x = 0; x < gBmMapSize.x; x++ ) {
			
			if (gBmMapMovement[y][x] > MAP_MOVEMENT_MAX)
				continue;
			if (gBmMapUnit[y][x])
				continue;
			if (gBmMapOther[y][x])
				continue;
			
			AddMapMaster(x,y,mask,NU_RANGE_MAP);
		}
}



void GenerateDangerZoneRange(s8 boolDisplayStaffRange)
{
	static int (*GetNonActiveFaction)(void) = (void*)0x8024DD1;
	
    int i, enemyFaction;
    int hasMagicRank, prevHasMagicRank;
    u8 savedUnitId;

    prevHasMagicRank = -1;

    BmMapFill(gBmMapRange, 0);

    enemyFaction = GetNonActiveFaction();

    for (i = enemyFaction + 1; i < enemyFaction + 0x80; ++i)
    {
        struct Unit* unit = GetUnit(i);

        if (!UNIT_IS_VALID(unit))
            continue; // not a unit

        if (boolDisplayStaffRange && !UnitHasMagicRank(unit))
            continue; // no magic in magic range mode

        if (gRAMChapterData.chapterVisionRange && (gBmMapFog[unit->yPos][unit->xPos] == 0))
            continue; // in the fog

        if (unit->state & US_UNDER_A_ROOF)
            continue; // under a roof

        // Fill movement map for unit
        GenerateUnitMovementMapExt(unit, MovGetter(unit));

        savedUnitId = gBmMapUnit[unit->yPos][unit->xPos];
        gBmMapUnit[unit->yPos][unit->xPos] = 0;

        hasMagicRank = UnitHasMagicRank(unit);

        if (prevHasMagicRank != hasMagicRank)
        {
            BmMapFill(gBmMapOther, 0);

            if (hasMagicRank)
                GenerateMagicSealMap(1);

            prevHasMagicRank = hasMagicRank;
        }

        SetWorkingBmMap(gBmMapRange);

        // Apply unit's range to range map

        if (boolDisplayStaffRange)
            GenerateUnitCompleteStaffRange(unit);
        else
            GenerateUnitCompleteAttackRange(unit);

        gBmMapUnit[unit->yPos][unit->xPos] = savedUnitId;
    }
}



