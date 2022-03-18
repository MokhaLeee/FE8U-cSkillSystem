
#include "prep-screen.h"

extern int sub_8095970();
static void (*StartProc_PrepMapDrawButtonObj)(ProcPtr) = (const void*) 0x8033621;
static int (*InitChapterDeployedUnitAndGetCount)(void) = (const void*) 0x8095971;
static void (*MovCursorToNextUnit)(short x, short y) = (const void*) 0x801DB4D;
void PrepScreenProc_StartMapMenu(struct Proc_SALLYCURSOR*);
extern const struct ProcCmd gProc_MaybeMapView[];








void InitPrepScreenCursorPosition(struct Proc_SALLYCURSOR* proc_prep){
	
	struct Unit* unit;
	u8 x, y;
	
	unit = GetUnitFromCharId( GetPlayerLeaderUnitId() );
	
	if( (NULL != unit) && (InitChapterDeployedUnitAndGetCount() != 0) )
		SetCursorMapPosition(unit->xPos, unit->yPos);
	
	else
	{
		GetPreferredPositionForUNIT(
			CountForceDeployedUnits() + GetChapterAllyUnitDataPointer(),
			&x, &y, 0);
		
		SetCursorMapPosition(x,y);
	}
	
	gGameState.camera.x = sub_8015A40(gGameState.playerCursor.x * 16);
	gGameState.camera.y = sub_8015A6C(gGameState.playerCursor.y * 16);
}



// =======================================================
// ================== Prep-map-menu ======================
// =======================================================

void PrepScreenProc_InitMapMenu(struct Proc_SALLYCURSOR* proc){
	
	proc->menuCmd_index = PREP_MAPMENU_VIEWMAP;
	PrepScreenProc_StartMapMenu(proc);
}



// 8033648
void PrepScreenProc_StartMapMenu(struct Proc_SALLYCURSOR* proc_prep){
	
	LoadDialogueBoxGfx(0, -1);
	Font_InitForUIDefault();
	DeletePlayerPhaseInterface6Cs();
	HideMoveRangeGraphics();
	
	// <!>
	StartPrepScreenMenu(proc_prep);
	
	SetPrepScreenMenuItem(
		PREP_MAPMENU_VIEWMAP,
		PrepScreenMapMenu_OnViewMap,
		TEXT_COLOR_NORMAL,
		0x590, // View Map[X]
		0x5BB  // View maps to battle on or[.][NL]
	);
	
	SetPrepScreenMenuItem(
		PREP_MAPMENU_FORMATION,
		PrepScreenMapMenu_OnFormation,
		0 == sub_8095970()
			? TEXT_COLOR_GRAY
			: TEXT_COLOR_NORMAL,
		0x591, // Formation[.][X]
		0x5BC  // Rearrange the starting[NL] formation of your units.[X]
	);

	SetPrepScreenMenuItem(
		PREP_MAPMENU_OPTION,
		PrepScreenMapMenu_OnOptions,
		TEXT_COLOR_NORMAL,
		0x592, // Options[.][X]
		0x5BD  // et game speed and[NL] window options.[.][X]
	);

	SetPrepScreenMenuItem(
		PREP_MAPMENU_SAVE,
		PrepScreenMapMenu_OnSave,
		0 == CanPrepScreenSave()
			? TEXT_COLOR_GRAY
			: TEXT_COLOR_NORMAL,
		0x579, // Save[X]
		0x5BE  // Save the current campaign.[X]
	);
	
	StartProc_PrepMapDrawButtonObj(proc_prep);
	
	SetPrepScreenMenuOnBPress(PrepScreenMapMenu_OnBPress);
	SetPrepScreenMenuOnStartPress(PrepScreenMapMenu_OnStartPress);
	SetPrepScreenMenuOnEnd(PrepScreenMapMenu_OnEnd);
	
	// <!>
	DrawPrepScreenMenuFrameAt(0xA, 0x2);
	
	SetPrepScreenMenuSelectedItem(proc_prep->menuCmd_index);
	BG_EnableSyncByMask(0b11);
}



// =======================================================
// ================ Prep-map-menu cmd ====================
// =======================================================

// Map Menu Label 0x32 -> 0x3D

void PrepScreenMapMenu_OnViewMap(struct Proc_SALLYCURSOR* proc_prep){
	
	proc_prep->menuCmd_index = PREP_MAPMENU_VIEWMAP;
	
	Proc_Break(proc_prep);
	ClosePrepScreenMapMenu();
	
}

void PrepScreenMapMenu_OnFormation(struct Proc_SALLYCURSOR* proc){
	
	proc->menuCmd_index = PREP_MAPMENU_FORMATION;
	
	MovCursorToNextUnit(
		gGameState.playerCursor.x,
		gGameState.playerCursor.y);
	
	DisplayCursor(
		gGameState.playerCursorDisplay.x,
		gGameState.playerCursorDisplay.y,
		0 );
	
	Proc_Break(proc);
	ClosePrepScreenMapMenu();
}

void PrepScreenMapMenu_OnOptions(struct Proc_SALLYCURSOR* proc){
	
	proc->menuCmd_index = PREP_MAPMENU_OPTION;
	
	Proc_Goto(proc, 0x39);
}

void PrepScreenMapMenu_OnSave(struct Proc_SALLYCURSOR* proc){
	
	proc->menuCmd_index = PREP_MAPMENU_SAVE;
	
	Proc_Goto(proc, 0x3B);
}

int PrepScreenMapMenu_OnBPress(struct Proc_SALLYCURSOR* proc){
	
	Proc_Goto(proc, 0x33);
	
	return 1;
}

int PrepScreenMapMenu_OnStartPress(struct Proc_SALLYCURSOR* proc){
	
	if( 0 == InitChapterDeployedUnitAndGetCount() )
		return 0;
	
	Proc_Goto(proc, 0x37);
	return 1;
}

void PrepScreenMapMenu_OnEnd(struct Proc_SALLYCURSOR* proc){
	
	//extern void sub_8089570(); // end some proc
	extern struct ProcCmd gProc_859DBA4[];
	
	EndHelpPromptSprite();
	Proc_EndEach(gProc_859DBA4);
	
}





// =======================================================
// =================== Prep On End =======================
// =======================================================

void EndPrepScreen(){
	
	for( int i = 1; i < FACTION_GREEN; i++ )
	{
		struct Unit* unit = GetUnit(i);
		
		if( !UNIT_IS_VALID(unit) )
			continue;
		
		unit->state = unit->state &~ (US_UNSELECTABLE);
		
		// here are Some Useless BWL operations
		
	} // for unit index
	
	ShrinkPlayerUnitList();
	Proc_EndEach(gProc_PrepScreen);
	
	gGameState.gameStateBits &= 0b11101111;
	gRAMChapterData.chapterStateBits &= 0b11101111;
	gRAMChapterData.unk4A_1 = 1; // nextTutorialEventParams
}




// =======================================================
// ================ View Map: Label 9 ====================
// Label: 0x32 -> 0x3D (Menu) -> (end menu) -> 0x9
// Here both Formation and View-Map is effect here
// =======================================================


// 8033978
void PrepScreenProc_MapIdle(struct Proc_SALLYCURSOR* proc){
	
	HandlePlayerCursorMovement();
	
	if( 0 != DoesBMXFADEExist() )
		goto goto_Finish;
	
	
	
	
	// Handle KeyPress
	
	if( L_BUTTON & gKeyStatusPtr->newKeys )
	{
		MovCursorToNextUnit(
			gGameState.playerCursor.x,
			gGameState.playerCursor.y);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		goto goto_Finish;
	
	} // L_BUTTON
	
	
	
	else if( (R_BUTTON & gKeyStatusPtr->newKeys) && 
		(0 != gBmMapUnit[gGameState.playerCursor.y][gGameState.playerCursor.x]) && 
		(0 != CanShowUnitStatScreen(GetUnit(gBmMapUnit[gGameState.playerCursor.y][gGameState.playerCursor.x]))) 
	)
	{
		MU_EndAll();
		DeletePlayerPhaseInterface6Cs(); // EndPlayerPhaseSideWindows
		SetStatScreenConfig(0x1F);
		StartStatScreen( GetUnit(gBmMapUnit[gGameState.playerCursor.y][gGameState.playerCursor.x]), (ProcPtr)proc );
		
		Proc_Goto(proc, 0x5);
		return;
	} // R_BUTTON
	
	
	
	else if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		DeletePlayerPhaseInterface6Cs();
		
		gRAMChapterData.xCursor = gGameState.playerCursor.x;
		gRAMChapterData.yCursor = gGameState.playerCursor.y;
		
		Proc_Goto(proc, 0x0);
		
		if( 0 == gRAMChapterData.unk41_1 )
			m4aSongNumStart(0x6B);
		
		return;
		
	} // B_BUTTON
	
	
	
	else if( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		struct Unit* unit = GetUnit(gBmMapUnit[gGameState.playerCursor.y][gGameState.playerCursor.x]);
		
		switch( GetUnitSelectionValueThing(unit) )
		{
			case 0:
			case 1:
				// Not Unit or Non-selectable
				DeletePlayerPhaseInterface6Cs();
				
				gRAMChapterData.xCursor = gGameState.playerCursor.x;
				gRAMChapterData.yCursor = gGameState.playerCursor.y;
				
				if( 
					(TERRAIN_VENDOR == gBmMapTerrain[gRAMChapterData.yCursor][gRAMChapterData.xCursor]) ||
					(TERRAIN_ARMORY == gBmMapTerrain[gRAMChapterData.yCursor][gRAMChapterData.xCursor])
				)
				{
					// Shop
					if( 0 == gRAMChapterData.unk41_1 )
						m4aSongNumStart(0x6A);
					
					Proc_Goto(proc, 0x3C);
					return;
				}
				else
				{
					Proc_Goto(proc, 0x0);
					
					if( 0 == gRAMChapterData.unk41_1 )
						m4aSongNumStart(0x69);
					
					return;
					
				}
				break;
			
			case 2:
				// Controllale
				UnitBeginAction(unit);
				gActiveUnit->state = gActiveUnit->state & (~US_HIDDEN);
				
				if( PREP_MAPMENU_FORMATION == proc->menuCmd_index )
				{
					Proc_Goto(proc, 0x3); // change formation
					return;
				}
				else
					goto goto_display_mapmovement;
				break;
			
			case 4:
				// Cannot move
				if( PREP_MAPMENU_FORMATION == proc->menuCmd_index )
				{
					if( 0 == gRAMChapterData.unk41_1 )
						m4aSongNumStart(0x6C);
					return;
				}
				// if FORMATION state, then remind you nope
				// else, if view map, same as case 3
				// here no break!
				
			case 3:
				// Uncontrollable
				UnitBeginAction(unit);
				gActiveUnit->state = gActiveUnit->state & (~US_HIDDEN);
				goto goto_display_mapmovement;
				break;
				
			default:
				break;
		} // switch
		
	} // A_BUTTON

	
	else if( START_BUTTON & gKeyStatusPtr->newKeys )
	{
		DeletePlayerPhaseInterface6Cs();
		Proc_StartBlocking(gProc_MaybeMapView, proc);
		Proc_Goto(proc, 0x9);
		return;
		
	} // START_BUTTON
	
	else
		goto goto_Finish;
	
	
goto_display_mapmovement:
	Proc_Goto(proc, 0x1);
	return;

goto_Finish:
	
	DisplayCursor(
		gGameState.playerCursorDisplay.x,
		gGameState.playerCursorDisplay.y,
		0 );
	
	return;
	
}



// 0x8033F34
void PrepScreenProc_MapMovementLoop(struct Proc_SALLYCURSOR* proc){
	
	u8 unit_id;
	
	HandlePlayerCursorMovement();
	
	if( (A_BUTTON | B_BUTTON) & gKeyStatusPtr->newKeys )
	{
		MU_EndAll();
		gActiveUnit->state &= ~US_HIDDEN;
		gGameState.gameStateBits &= 0b11110111;
		HideMoveRangeGraphics();
		RefreshEntityBmMaps();
		SMS_UpdateFromGameData();
		
		if( 0 == gRAMChapterData.unk41_1 )
			m4aSongNumStart(0x6B);
		
		Proc_Goto(proc, 0x9);
		return;
		
	} // A_BUTTON | B_BUTTON
	
	
	else if( R_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( (gActiveUnitMoveOrigin.x == gGameState.playerCursor.x) && (gActiveUnitMoveOrigin.y == gGameState.playerCursor.y) )
			unit_id = gActiveUnit->index;
		else
			unit_id = gBmMapUnit[gGameState.playerCursor.y][gGameState.playerCursor.x];			
		
		if( (0 != unit_id) && (CanShowUnitStatScreen(GetUnit(unit_id)) != 0) )
		{
			MU_EndAll();
			SetStatScreenConfig(0x1F);
			StartStatScreen(GetUnit(unit_id), (ProcPtr)proc);
			Proc_Goto(proc, 0x6);
			
		} // Draw Stat-Screen
		
	} // R_BUTTON
	
	
	// No idea why here to be "if" rather than "else if"
	if( (L_BUTTON == gKeyStatusPtr->newKeys) && (NULL != gActiveUnit) )
	{
		EnsureCameraOntoPosition(proc, gActiveUnitMoveOrigin.x, gActiveUnitMoveOrigin.y);
		SetCursorMapPosition(gActiveUnitMoveOrigin.x, gActiveUnitMoveOrigin.y);
		
		if( 0 == gRAMChapterData.unk41_1 )
			m4aSongNumStart(0x6B);
		
	} // L_BUTTON
	
	DisplayCursor(
		gGameState.playerCursorDisplay.x,
		gGameState.playerCursorDisplay.y,
		1 );
	
	
}



/* 
void PrepScreen_UnitSwapIdle(struct Proc_SALLYCURSOR* proc){
	
	// // Use gMapRange as judgement, interesting
	u8 CanMove = 
		4 == GetUnitSelectionValueThing(GetUnit(gBmMapUnit[gGameState.playerCursor.y][gGameState.playerCursor.x]))
			? 0
			: gBmMapRange[gGameState.playerCursor.y][gGameState.playerCursor.x]; 
	
	HandlePlayerCursorMovement();
	
	
	
}
 */


