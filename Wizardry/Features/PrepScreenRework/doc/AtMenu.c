#include "prep-screen.h"

extern int CheckSomethingSomewhere();
void AtMenu_AutoCapDeployPrepScreenUnits(struct Proc_AtMenu*);
void AtMenu_InitPrepScreenMenu(struct Proc_AtMenu*);
extern void RestartScreenMenuScrollingBg();
extern void sub_8095A44(int, int);
extern void sub_80AD1D0(int);
extern int GetActivePrepScreenMenuItemId();
extern void DrawPrepScreenMenuHelpText(int);
extern int GetActivePrepScreenMenuItemHelpTextId();
extern void sub_80AD1AC(ProcPtr);
extern void AtMenu_AddPrepScreenSupportMenuItem();
extern void sub_8096BE0();
extern void sub_8096BC4();
extern void EndBG3Slider_();
extern void sub_8096C20();
extern void SetColorEffectsFirstTarget(int, int, int, int, int);
extern void SetColorEffectBackdropFirstTarget(int);
extern void PositionUnitsAccordingToDeployment();
void SetPrepScreenUnitListCharID(int index); // 80953C0

static void (*PrepOnDrawSpecialChar)(ProcPtr) = (const void*) 0x8096BFD;
// static void (*PrepSpecialChar_OnEnd)() = (const void*) 0x8096C21;
static void (*PrepSpecialChar_BlinkButtonStart)() = (const void*) 0x8096BC5;
static void (*PrepSpecialChar_BlinkButtonB)() = (const void*) 0x8096BE1;


extern u16 gBgConfig_8A181E8[];
extern struct TextHandle gPrepScreenMenuHelpTextArray[];









// 8096424
void AtMenu_LockGame(struct Proc_AtMenu* proc){
	
	// CheckGameLinkArenaBit
	if( 0 == CheckSomethingSomewhere() )
	{	
		AddSkipThread2();
		BMapDispSuspend();
	}
	
}

// 8095AD8
void AtMenu_OnInit(struct Proc_AtMenu* proc){
	
	SetPrepScreenUnitListCharID(0);
	
	proc->xDiff = 0;
	proc->yDiff = 0;
	
	if ( 0 == CheckSomethingSomewhere())
		proc->max_counter = GetChapterAllyUnitCount();
	else
		proc->max_counter = 5;
	
	proc->unk_30 = 0;
	proc->unk_31 = 0;
	proc->unk_32 = 0;
	proc->state = 0;
	proc->unk_34 = 0;
	proc->end_prep = 0;
	proc->cur_cmd = 0;
	proc->unk_2E = 0;
}



// 80953C0
void SetPrepScreenUnitListCharID(int index){
	
	extern void* gGMData;
	void sub_80C409C(u32);
	
	if ( 0 != (1 & *(u8*)gGMData) )
		sub_80C409C(index);
	else
		gPrepScreenUnitList.char_id = index;
		
	
}




// 0x8095C84
void AtMenu_Reinitialize(struct Proc_AtMenu* proc) {
	
	extern u16 gUnknown_08A181E8[]; // BG Config
	extern u16 gUnknown_08A1A4C8[]; // maybe gfx
	extern u16 gUnknown_08A1D510[]; // maybe tsa
	extern u16 gPal_SmolBrownNameBox[]; // gPal_SmolBrownNameBox
	
	extern u16 gUnknown_08A1AC88[]; // should be tsa
	extern u16 gUnknown_08A1B174[]; // pal
	extern u16 gUnknown_08A1D4C8[]; // pal
	// extern u16 gUiFramePaletteB[];
	
	extern u16 gUnknown_08A1B658[]; // tsa
	extern u16 gUnknown_08A1B698[]; // tsa
	
	
	
	SetupBackgrounds(gUnknown_08A181E8);
	Font_InitForUIDefault();
	LoadUiFrameGraphics();
	
	LoadDialogueBoxGfx(0, 0xE);
	
	gLCDControlBuffer.dispcnt.bg0_on = 0;
	gLCDControlBuffer.dispcnt.bg1_on = 0;
	gLCDControlBuffer.dispcnt.bg2_on = 0;
	gLCDControlBuffer.dispcnt.bg3_on = 0;
	gLCDControlBuffer.dispcnt.obj_on = 0;
	
	LoadObjUIGfx();
	SMS_ClearUsageTable();
	InitPrepScreenUnitList();
	AtMenu_AutoCapDeployPrepScreenUnits(proc);
	ReorderPlayerUnitsBasedOnDeployment();
	
	BG_Fill(gBG0TilemapBuffer, 0);
	BG_Fill(gBG1TilemapBuffer, 0);
	BG_Fill(gBG2TilemapBuffer, 0);
	
	
	for( int i = 0; i < 5; i++)
		Text_Init(&gPrepTexts[i + 5], 0xE);
	
	for( int i = 0; i < 4; i++)
		Text_Init(&gPrepTexts[i + 1], 0x8);
	
	Text_Init(&gPrepTexts[0], 0xA);
	
	// "Preparations"
	CopyDataWithPossibleUncomp(
		gUnknown_08A1A4C8,
		OBJ_VRAM0 + 0x4800 );
	
	// "Menu", "Start" button
	CopyDataWithPossibleUncomp(
		gUnknown_08A1D510,
		OBJ_VRAM0 + 0x6000 );
	
	CopyToPaletteBuffer(gPal_SmolBrownNameBox, 0x320, 0x40);
	
	// "Cahpter 0", "Infomaion"
	CopyDataWithPossibleUncomp(
		gUnknown_08A1AC88,
		OBJ_VRAM0 + 0x7000 );
	
	CopyToPaletteBuffer( gUnknown_08A1B174, 0x2C0, 0x20);
	CopyToPaletteBuffer( gUnknown_08A1D4C8, 0x280, 0x20);
	EnablePaletteSync();
	
	gLCDControlBuffer.bg0cnt.priority = 0;
	gLCDControlBuffer.bg1cnt.priority = 0b10;
	gLCDControlBuffer.bg2cnt.priority = 0b01;
	gLCDControlBuffer.bg3cnt.priority = 0b11;
	gLCDControlBuffer.dispcnt.win0_on = 0;
	gLCDControlBuffer.dispcnt.win1_on = 0;
	gLCDControlBuffer.dispcnt.objWin_on = 0;
	
	BG_SetPosition( 0, 0, 0);
	BG_SetPosition( 1, 0, 0);
	BG_SetPosition( 2, 0, 0);
	
	// <!>
	AtMenu_InitPrepScreenMenu(proc);
	
	BG_EnableSyncByMask(0b1111);
	SetDefaultColorEffects();
	
	// Draw special character
	PrepOnDrawSpecialChar(proc);
	
	// BG scrolling
	RestartScreenMenuScrollingBg();
	
	CopyToPaletteBuffer( gUiFramePaletteB, 0x40, 0x60);
	
	// Main menu window
	CopyDataWithPossibleUncomp(
		gUnknown_08A1B658,
		gGenericBuffer );
	
	CallARM_FillTileRect(
		TILEMAP_LOCATED(gBG1TilemapBuffer, 0x10, 2),
		gGenericBuffer, 0x1000 );
		
	CopyDataWithPossibleUncomp(
		gUnknown_08A1B698,
		gGenericBuffer );
	
	CallARM_FillTileRect(
		TILEMAP_LOCATED(gBG1TilemapBuffer, 1, 6),
		gGenericBuffer, 0x1000 );
	
	
	// chapter name
	sub_8095A44(0x5800, 0xB);
	
	sub_80AD1AC(proc);
	sub_80AD1D0(0x6800);
	
	proc->unk_35 = GetActivePrepScreenMenuItemId();
	
	// Draw infomation text
	DrawPrepScreenMenuHelpText( GetActivePrepScreenMenuItemHelpTextId() );
	DisplayPrepScreenMenuHelpText();
}




// 8095524
void AtMenu_InitPrepScreenMenu(struct Proc_AtMenu* proc) {
	
	// <!>
	StartPrepScreenMenu(proc);
	
	// here neglect Arena case
	SetPrepScreenMenuItem(
		PREP_MAINMENU_UNIT, 
		PrepScreenMenu_OnPickUnits, 
		TEXT_COLOR_NORMAL, 
		0x574, 0);
		
	SetPrepScreenMenuItem(
		PREP_MAINMENU_ITEM, 
		PrepScreenMenu_OnItems, 
		TEXT_COLOR_NORMAL, 
		0x576, 0);
		
	AtMenu_AddPrepScreenSupportMenuItem(proc);
	
	SetPrepScreenMenuItem(
		PREP_MAINMENU_CHECKMAP, 
		PrepScreenMenu_OnCheckMap,
		0 == CanPrepScreenCheckMap()
			? TEXT_COLOR_GRAY
			: TEXT_COLOR_NORMAL,
		0x578, // Check Map[.][X]
		0
	);
	
	SetPrepScreenMenuItem(
		PREP_MAINMENU_SAVE, 
		PrepScreenMenu_OnSave,
		0 == CanPrepScreenSave()
			? TEXT_COLOR_GRAY
			: TEXT_COLOR_NORMAL,
		0x579, // Save[X]
		0 
	);
	
	SetPrepScreenMenuOnBPress(PrepScreenMenu_OnBPress);
	SetPrepScreenMenuOnStartPress(PrepScreenMenu_OnStartPress);
	
	TileMap_FillRect(gBG0TilemapBuffer, 0xC, 0x13, 0);
	TileMap_FillRect(gBG1TilemapBuffer, 0xC, 0x13, 0);
	
	SetPrepScreenMenuPosition(1, 6);
	SetPrepScreenMenuSelectedItem(proc->cur_cmd);
}



void AtMenu_AutoCapDeployPrepScreenUnits(struct Proc_AtMenu* proc){
	
	proc->cur_counter = 0;
	proc->unit_count = 0;
	
	// 函数GetPrepScreenUnitListSize可以用于读取保存玩家设定的出战人数
	for( int i = 0; i < GetPrepScreenUnitListSize(); i++){
		
		struct Unit* unit = GetPrepScreenUnitListEntry(i);
		
		if( unit->state & US_NOT_DEPLOYED ){
			proc->unit_count++;
			continue;
		}
		
		if( proc->max_counter < proc->cur_counter ){
			unit->state = US_NOT_DEPLOYED;
			proc->unit_count++;
			continue;
		}
		
		proc->cur_counter++;
		proc->unit_count++;
		
	} // for
	
	if( proc->max_counter < proc->cur_counter )
		proc->max_counter = proc->cur_counter;
		
}






// =======================================================
// ====================== On End =========================
// =======================================================
// Label 5 & 6

void AtMenu_OnEnd_8096294(struct Proc_AtMenu* proc){
	
	EndBG3Slider_();
	sub_8096C20();
	SetupBackgrounds(0);
	SetSpecialColorEffectsParameters(3,0,0,0x10);
	SetColorEffectsFirstTarget(1,1,1,1,1);
	SetColorEffectBackdropFirstTarget(1);
}


void AtMenu_OnEnd_80962E0(struct Proc_AtMenu* proc){
	
	extern void sub_8042EA8();
	
	ReorderPlayerUnitsBasedOnDeployment();
	
	if( 1 == proc->end_prep )
		EndPrepScreen();
	
	else if( 0 != CheckSomethingSomewhere() )
		sub_8042EA8(); // maybe arena
	
	PositionUnitsAccordingToDeployment();
	SMS_ClearUsageTable();
	RefreshEntityBmMaps();
	SMS_UpdateFromGameData();
		
}

void AtMenu_OnEnd_809643C(struct Proc_AtMenu* proc){
	
	if( 0 != CheckSomethingSomewhere() )
		return;
	
	BMapDispResume();
	SubSkipThread2();
	
}

// =======================================================
// ================ Sub menu routine =====================
// =======================================================

// Label 2

void AtMenu_StartSubmenu(struct Proc_AtMenu* proc){
	
	extern void sub_8095C2C(ProcPtr);
	extern void sub_808E79C(ProcPtr);
	
	sub_8095C2C(proc); // end scroll and some procs, etc
	
	switch( proc->state )
	{
		case 5:
			sub_808E79C(proc);
			break;
			
		case 2: // Item
			StartPrepScreenItemsMenu(proc);
			break;
			
		case 1: // Pick Units
			Proc_StartBlocking(gProc_PrepScreenPickUnitsMenu, proc);
			break;
			
		case 4: // Support
			StartPrepScreenSupportMenu(2, proc);
			break;
		
		case 3: // Save
			StartPrepScreenSaveMenu(proc);
			break;
			
		default:
			break;
	}
	
	Proc_Break(proc);
	
}


void AtMenu_OnSubmenuEnd(struct Proc_AtMenu* proc){
	
	extern void StartSongVolumeTransitionB(int,int,int,int);
	
	if( 3 == proc->state )
		StartSongVolumeTransitionB(0x80, 0x100, 0x20, 0);
	
	switch( proc->state )
	{
		case 4:
			Proc_Goto(proc, 0x9);
			break;
			
		case 3: // Save
			Proc_Goto(proc, 0x7);
			break;
			
		case 1:
		case 2:
		case 5:
			Proc_Goto(proc, 0x9);
			break;
			
		default:
			break;
	}
	
	proc->state = 0;
	
}



// =======================================================
// ========== Prep-main-menu effect routine ==============
// =======================================================

void PrepScreenMenu_OnPickUnits(struct Proc_AtMenu* proc){
	
	proc->state = 1;
	Proc_Goto(proc, 0xA);
	
}

void PrepScreenMenu_OnItems(struct Proc_AtMenu* proc){
	
	proc->state = 2;
	Proc_Goto(proc, 0xA);
}

void PrepScreenMenu_OnCheckMap(struct Proc_AtMenu* proc){
	
	Proc_Goto(proc, 0x5);
	
}
void PrepScreenMenu_OnSave(struct Proc_AtMenu* proc){
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x6A);
	
	proc->state = 3;
	Proc_Goto(proc, 0x8);
}

int PrepScreenMenu_OnBPress(struct Proc_AtMenu* proc){
	
	// CheckGameLinkArenaBit
	if( 0 == CheckSomethingSomewhere() ){
		if( 0 == CanPrepScreenCheckMap() )
			return 0;
		else
			PrepSpecialChar_BlinkButtonB();
	}
	
	Proc_Goto(proc, 0x5);
	return 1;
}

int PrepScreenMenu_OnStartPress(struct Proc_AtMenu* proc){
	
	if( 0 == proc->cur_counter )
		return 0;
	
	PrepSpecialChar_BlinkButtonStart();
	Proc_Goto(proc, 0xB);
	return 1;
	
}

int PrepScreenMenu_OnSupport(struct Proc_AtMenu* proc){
	
	extern void sub_80029E8(int, int, int, int, int); // related to song
	
	proc->state = 4;
	
	sub_80029E8(0x37, 0x100, 0x100, 0x20, 0);
	
	Proc_Goto(proc, 0xA);
	
	return 1;
}





