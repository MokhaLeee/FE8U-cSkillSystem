#include "gbafe-chax.h"

extern void PrepScreenProc_StartDimMap(ProcPtr);
extern void PrepScreenProc_StartBrightenMap(ProcPtr);
extern int MapBrightnessFadeExists();
extern int IsBottomHelpTextActive();
extern void StartPlayerPhaseSideWindows(ProcPtr);
static void(*DisplayBlueTileForPrepFormation)(void) = (const void*) 0x80332D1;
static void (*MovCursorToNextUnit)(short x, short y) = (const void*) 0x801DB4D;
extern const struct ProcCmd gProc_MaybeMapView[];
extern void StartFadeInBlackMedium();
extern const struct ProcCmd gProc_ADJUSTFROMXI[];
extern void sub_8034090(ProcPtr);
extern const struct ProcCmd gProc_CameraMovement[];
extern void PrepScreen_UnitSwapIdle(struct newProc_PrepMapView* proc);
extern void PrepScreen_StartUnitSwapAnim(ProcPtr);
extern int UnitSwapAnimationExists();
extern void InitMapChangeGraphicsIfFog();
extern void DisplayMapChangeIfFog();
static const u32 ResetCameraOnActiveUnit = 0x8033DD9;
extern void PrepScreenProc_StartShopScreen(ProcPtr);

// static void newPrepMap_ (struct newProc_PrepMapView* proc);
static void newPrepMap_OnInit (struct newProc_PrepMapView* proc);
static void newPrepMap_WaitFadeAndDisplayRange (struct newProc_PrepMapView* proc);
static void newPrepMap_MapViewLoop (struct newProc_PrepMapView* proc);
static void newPrepMap_MapMovementLoop (struct newProc_PrepMapView* proc);


enum{
	// Proc: Prep-MapView's label
	LABEL_PREPMAP_INIT = 0x0,
	LABEL_PREPMAP_MAPVIEW = 0x9,
	LABEL_PREPMAP_POST_STAT = 0x5,
	LABEL_PREPMAP_POST_STAT_MOVEDISP = 0x6,
	LABEL_PREPMAP_SHOP = 0x3C,
	LABEL_PREPMAP_FORMATION = 0x3,
	LABEL_PREPMAP_FORMATION_CANCEL = 0x4,
	LABEL_PREPMAP_DISPMOVEMENT = 0x1,
	LABEL_PREPMAP_END = 0xFF,
	LABEL_PREPMAP_GAMESTART = 0x37,
};



const struct ProcCmd newProcCmd_PrepMapView[] = {
	
	PROC_NAME	("PREP_NEW_MAPVIEW"),
	PROC_YIELD,
	
	
PROC_LABEL (LABEL_PREPMAP_INIT),

	// On Init
	PROC_CALL	(newPrepMap_OnInit),
	PROC_CALL	(RefreshBMapGraphics),
	PROC_CALL	(StartFadeOutBlackMedium),
	PROC_REPEAT	(ContinueUntilSomeTransistion6CExists), // WaitForFade



PROC_LABEL (LABEL_PREPMAP_MAPVIEW),
	
	// Map View
	PROC_YIELD,
	PROC_WHILE	(IsBottomHelpTextActive),
	PROC_CALL	(RefreshEntityBmMaps),
	PROC_CALL	(RenderBmMap),
	PROC_CALL	(SMS_UpdateFromGameData),
	PROC_CALL	(StartPlayerPhaseSideWindows),
	PROC_REPEAT	(newPrepMap_WaitFadeAndDisplayRange),
	PROC_REPEAT	(newPrepMap_MapViewLoop),
	


PROC_LABEL	(LABEL_PREPMAP_POST_STAT),
	
	// Post StatScreen
	PROC_CALL	(RefreshBMapGraphics),
	PROC_START_CHILD_BLOCKING( gProc_ADJUSTFROMXI ),
	PROC_GOTO	(LABEL_PREPMAP_MAPVIEW),

PROC_LABEL	(LABEL_PREPMAP_POST_STAT_MOVEDISP),

	// Post StatScreen on MapMovement display
	PROC_CALL 	(sub_8034090),
	PROC_GOTO	(LABEL_PREPMAP_DISPMOVEMENT),

PROC_LABEL	(LABEL_PREPMAP_SHOP),	

	// Shop
	PROC_CALL	(StartFadeInBlackMedium),
	PROC_REPEAT	(ContinueUntilSomeTransistion6CExists),
	PROC_CALL	(HideMoveRangeGraphics),
	PROC_CALL	(BMapDispSuspend),
	PROC_CALL	(PrepScreenProc_StartShopScreen),
	PROC_YIELD,
	PROC_CALL	(BMapDispResume),
	PROC_CALL	(RefreshBMapGraphics),
	PROC_CALL	(RefreshEntityBmMaps),
	PROC_CALL	(RenderBmMap),
	PROC_CALL	(SMS_UpdateFromGameData),
	PROC_CALL	(sub_8034194),
	PROC_CALL	(sub_8033608),
	PROC_CALL	(StartFadeOutBlackMedium),
	PROC_REPEAT	(ContinueUntilSomeTransistion6CExists),
	PROC_GOTO	(LABEL_PREPMAP_MAPVIEW),



PROC_LABEL	(LABEL_PREPMAP_FORMATION),	

	// Change Formation
	PROC_CALL	(DeletePlayerPhaseInterface6Cs),
	PROC_CALL	(SALLYCURSOR6C_StartUnitSwap),
	PROC_WHILE_EXISTS( gProc_CameraMovement ),
	PROC_REPEAT	(PrepScreen_UnitSwapIdle),
	
	PROC_CALL	(HideMoveRangeGraphics),
	PROC_CALL	(PrepScreen_StartUnitSwapAnim),
	PROC_WHILE_EXISTS( gProc_CameraMovement ),
	PROC_WHILE	(UnitSwapAnimationExists),
	PROC_CALL	(InitMapChangeGraphicsIfFog),
	PROC_CALL	(RefreshEntityBmMaps),
	PROC_CALL	(SMS_UpdateFromGameData),
	PROC_YIELD,
	PROC_CALL	(DisplayMapChangeIfFog),
	PROC_GOTO	(LABEL_PREPMAP_MAPVIEW),




PROC_LABEL 	(LABEL_PREPMAP_FORMATION_CANCEL),
	
	// in Formation and cancel when you have chosen one unit
	PROC_CALL	(HideMoveRangeGraphics),
	PROC_WHILE_EXISTS( gProc_CameraMovement ),
	PROC_CALL	((void*)ResetCameraOnActiveUnit),
	PROC_YIELD,
	PROC_GOTO	(LABEL_PREPMAP_MAPVIEW),
	

PROC_LABEL	(LABEL_PREPMAP_DISPMOVEMENT),
	
	// Dispaly Movement
	PROC_YIELD,
	PROC_CALL	(HideMoveRangeGraphics),
	PROC_CALL	(DeletePlayerPhaseInterface6Cs),
	PROC_CALL	(DisplayActiveUnitEffectRange),
	PROC_REPEAT	(newPrepMap_MapMovementLoop),
	PROC_GOTO	(LABEL_PREPMAP_MAPVIEW),
	
	


PROC_LABEL (LABEL_PREPMAP_END),	
	
	// On End
	PROC_END
}; 





// =======================================================
// =================== Inside Proc =======================
// =======================================================


void newPrepMap_OnInit (struct newProc_PrepMapView* proc){
	
	extern u16 Pal_PrepHelpButton[];
	
	ApplyPalettes(Pal_PrepHelpButton, 0x12, 1);
	
	proc->yDiff = 0;
	proc->xDiff = 0;
	proc->unk_4A = 0;
	proc->maybe_ap = 0;
	
	
	
	if( CMD_PREPMENU_FORMATION == proc->cur_cmd )
	{
			MovCursorToNextUnit(
				gGameState.playerCursor.x,
				gGameState.playerCursor.y);
			
	} // FORMATION
	
}

// 8033940
void newPrepMap_WaitFadeAndDisplayRange (struct newProc_PrepMapView* proc){
	
	if( 0 == DoesBMXFADEExist() )
	{
		if( CMD_PREPMENU_FORMATION == proc->cur_cmd )
		{
				
			DisplayBlueTileForPrepFormation();
			
		} // FORMATION
				
		Proc_Break(proc);
	
	} // DoesBMXFADEExist

	
	DisplayCursor(
		gGameState.playerCursorDisplay.x,
		gGameState.playerCursorDisplay.y,
		0 );
}




void newPrepMap_MapViewLoop (struct newProc_PrepMapView* proc){
	
	struct Unit* unit = GetUnit(gBmMapUnit[gGameState.playerCursor.y][gGameState.playerCursor.x]);
	const int terrain = gBmMapTerrain[gRAMChapterData.yCursor][gRAMChapterData.xCursor];
	
	HandlePlayerCursorMovement();

	
	if( 0 != DoesBMXFADEExist() )
		goto goto_End;
	
	

	if( L_BUTTON & gKeyStatusPtr->newKeys )
	{
		MovCursorToNextUnit(
			gGameState.playerCursor.x,
			gGameState.playerCursor.y);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		goto goto_End;
	
	} // L_BUTTON
	
	
	else if( (R_BUTTON & gKeyStatusPtr->newKeys) && UNIT_IS_VALID(unit) )
	{
		MU_EndAll();
		DeletePlayerPhaseInterface6Cs(); // EndPlayerPhaseSideWindows
		SetStatScreenConfig(0x1F);
		StartStatScreen(unit, (ProcPtr)proc);
		Proc_Goto(proc, LABEL_PREPMAP_POST_STAT);
		return;
		
	} // R_BUTTON

	
	else if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		DeletePlayerPhaseInterface6Cs();
		
		gRAMChapterData.xCursor = gGameState.playerCursor.x;
		gRAMChapterData.yCursor = gGameState.playerCursor.y;
		
		Proc_Goto(proc, LABEL_PREPMAP_END); // Directly End map
		
		if( 0 == gRAMChapterData.unk41_1 )
			m4aSongNumStart(0x6B);
		
		return;
		
	} // B_BUTTON
	
	
	else if( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		switch( GetUnitSelectionValueThing(unit) )
		{
			case 0:
			case 1:
				// Not Unit or Non-selectable
				DeletePlayerPhaseInterface6Cs();
				
				gRAMChapterData.xCursor = gGameState.playerCursor.x;
				gRAMChapterData.yCursor = gGameState.playerCursor.y;
				
				if( (TERRAIN_VENDOR == terrain) || (TERRAIN_ARMORY == terrain) )
				{
					// Shop
					if( 0 == gRAMChapterData.unk41_1 )
						m4aSongNumStart(0x6A);
					
					Proc_Goto(proc, LABEL_PREPMAP_SHOP);
					return;
				}
				else
				{
					Proc_Goto(proc, LABEL_PREPMAP_END); // Directly End map
					
					if( 0 == gRAMChapterData.unk41_1 )
						m4aSongNumStart(0x69);
					
					return;
					
				}
				break;	
				
			case 2:
				// Controllale
				UnitBeginAction(unit);
				gActiveUnit->state = gActiveUnit->state & (~US_HIDDEN);
				
				if( CMD_PREPMENU_FORMATION == proc->cur_cmd )
				{
					Proc_Goto(proc, LABEL_PREPMAP_FORMATION); // change formation
					return;
					
				} // CMD_PREPMENU_FORMATION
				
				else
					goto goto_display_mapmovement;
				break;
				
			case 4:
				// Cannot move
				if( CMD_PREPMENU_FORMATION == proc->cur_cmd )
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
		Proc_Goto(proc, LABEL_PREPMAP_MAPVIEW);
		return;
		
	} // START_BUTTON
	
	else
		goto goto_End;
	

	
	
goto_End:

	DisplayCursor(
		gGameState.playerCursorDisplay.x,
		gGameState.playerCursorDisplay.y,
		0 );
	
	return;



goto_display_mapmovement:

	Proc_Goto(proc, LABEL_PREPMAP_DISPMOVEMENT);
	return;
}




// 8033F34
void newPrepMap_MapMovementLoop (struct newProc_PrepMapView* proc){
	
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
		
		Proc_Goto(proc, LABEL_PREPMAP_MAPVIEW);
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
			Proc_Goto(proc, LABEL_PREPMAP_POST_STAT_MOVEDISP);
			
		} // Draw Stat-Screen
		
	} // R_BUTTON
	
	
	else if( (L_BUTTON == gKeyStatusPtr->newKeys) && (NULL != gActiveUnit) )
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





// =======================================================
// ======================= Misc ==========================
// =======================================================

void StartNewPrepMapView(struct newProc_PrepMain* proc_prep){
	
	struct newProc_PrepMapView* child = 
		Proc_StartBlocking(newProcCmd_PrepMapView, proc_prep);
		
	child->cur_cmd = proc_prep->cur_cmd;
	
}


