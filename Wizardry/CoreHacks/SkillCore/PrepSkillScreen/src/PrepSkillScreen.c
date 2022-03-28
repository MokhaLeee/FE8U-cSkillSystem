#include "gbafe-chax.h"

extern void NewFadeIn(int step);
extern int FadeInExists();

// OAM Misc
static void (*PrepDrawHand)(int x, int y, int, int) = (const void*) 0x80AD51D;
extern void ResetPrepScreenHandCursor(ProcPtr);
static void (*PrepScreen_DrawHandGfxMaybe)(int, int) = (const void*) 0x80AD4A1;
extern void sub_80AD4E4(int); // also update hand

// BG Scroll
extern int NewFadeOut(ProcPtr);
static void (*PrepStartScroll)(ProcPtr, int, int, int, int) = (const void*) 0x8097749;
extern void RestartScreenMenuScrollingBg();
// static void (*PrepMenu_UpdateTsaScroll)(int) = (const void*) 0x809A645;



// static void * (struct Proc_PrepUnit* proc);
static void PrepSkill_OnEnd (struct Proc_PrepUnit* proc);
static void PrepSkill_InitScreen (struct Proc_PrepUnit* proc);
static void PrepSkill_UnitSelectLoop (struct Proc_PrepUnit* proc);
static void PrepSkill_HandleUnitListScrollLoop(struct Proc_PrepUnit* proc);
static void PrepSkill_UpdateUnitMenuTexts(struct Proc_PrepUnit* proc);


// On Draw
static void PrepSkill_InitTexts();
static void PrepSkill_DrawPickTotalBar(struct Unit* unit, int config); // config: 0->init, 1->update
static void PrepSkill_DrawWindowGfx(void);
static void PrepSkill_DrawLeftSkillsIcon(struct Unit* unit);
static void PrepSkill_UpdateSMSsAndObjs(struct Proc_PrepUnit* proc);








enum{
	// Proc: Prep-SkillScreen's label
	LABEL_PREPSKILL_ONINIT = 0,
	LABEL_PREPSKILL_UNITLOOP,
	LABEL_PREPSKILL_END,
};







const static struct ProcCmd ProcCmd_PrepSkillScreen[] = {
	
	PROC_NAME	("PREP_NEW_SKILLSCREEN"),
	
	PROC_SET_END_CB (PrepSkill_OnEnd),

PROC_LABEL (LABEL_PREPSKILL_ONINIT),
	PROC_YIELD,
	PROC_CALL	(PrepSkill_InitScreen),
	PROC_YIELD,
	PROC_CALL_ARG (NewFadeIn, 0x10),
	PROC_WHILE	(FadeInExists),
	PROC_REPEAT	(PrepSkill_UnitSelectLoop),
	



PROC_LABEL	(LABEL_PREPSKILL_END),
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),
	PROC_END
}; 








static void PrepSkill_OnEnd (struct Proc_PrepUnit* proc){
	
	static void (*SetPrepScreenUnitListCharID)(int index) = (const void*) 0x80953C1;
	extern void EndBG3Slider_();
	
	struct Proc_AtMenu* parent;
	
	parent = (struct Proc_AtMenu*)proc->proc_parent;
	
	parent->yDiff = proc->yDiff_cur;
	
	SetPrepScreenUnitListCharID(
		GetPrepScreenUnitListEntry(proc->list_num_cur)->pCharacterData->number);
	
	EndBG3Slider_();
	
}











void PrepSkill_InitScreen (struct Proc_PrepUnit* proc){

	static void (*PrepUnit_InitSMS)(ProcPtr) = (const void*) 0x809A8F9;
	static void (*PrepUnit_DrawLeftUnitName)(struct Unit*) = (const void*) 0x809A931;
	static void (*PrepUnit_DrawUnitListNames)(struct Proc_PrepUnit*, int) = (const void*) 0x809A581;

	extern void Get6CDifferedLoop6C(void* func, ProcPtr);
	extern void sub_809ADC8(struct Proc_PrepUnit*); // Set proc+0x30?
	
	struct Unit* unit = GetPrepScreenUnitListEntry(proc->list_num_cur);
	
	u16 BgConfig[12] =
	{
		// tile offset	map offset	screen size
		0x0000,			0xE000,		0,			// BG 0
		0x0000,			0xE800,		0,			// BG 1
		0x0000,			0xF000,		0,			// BG 2
		0x8000,			0xF800,		0,			// BG 3
	};
	
	SetupBackgrounds(BgConfig);
	
	gLCDControlBuffer.dispcnt.bg0_on = 0;
	gLCDControlBuffer.dispcnt.bg1_on = 0;
	gLCDControlBuffer.dispcnt.bg2_on = 0;
	gLCDControlBuffer.dispcnt.bg3_on = 0;
	gLCDControlBuffer.dispcnt.obj_on = 0;
	
	// Set proc+0x30? a unit index in list?
	sub_809ADC8(proc); 
	
	BG_Fill(gBG0TilemapBuffer, 0);
	BG_Fill(gBG1TilemapBuffer, 0);
	BG_Fill(gBG2TilemapBuffer, 0);
	
	gLCDControlBuffer.bg0cnt.priority = 0b10;
	gLCDControlBuffer.bg1cnt.priority = 0b10;
	gLCDControlBuffer.bg2cnt.priority = 0b01;
	gLCDControlBuffer.bg3cnt.priority = 0b11;
	
	BG_SetPosition( 0, 0, 0);
	BG_SetPosition( 1, 0, 0);
	BG_SetPosition( 2, 0, proc->yDiff_cur - 0x18);
	BG_SetPosition( 3, 0, 0);
	
	// Init TextHandles
	PrepSkill_InitTexts();
	PrepSkill_DrawWindowGfx();
	
	BG_EnableSyncByMask(0b1111);
	SetDefaultColorEffects();
	
	// Init SMS
	PrepUnit_InitSMS(proc);
	Get6CDifferedLoop6C(PrepSkill_UpdateSMSsAndObjs, proc);
	
	// Hand
	ResetPrepScreenHandCursor(proc);
	PrepScreen_DrawHandGfxMaybe(0x600, 0x1);
	PrepDrawHand(
		(proc->list_num_cur % 2) * 56 + 0x70,
		(proc->list_num_cur / 2) * 16 - proc->yDiff_cur + 0x18,
		0x7, 0x800);
	
	// BG Scroll
	PrepStartScroll(proc, 0xE0, 0x20, 0x200, 2);
	
	// OAM: [R]:info
	// StartHelpPromptSprite(0x20, 0x8F, 9, (ProcPtr)proc);
	
	
	// Draw Texts
	for( int i = 0; i < 6; i++)
		PrepUnit_DrawUnitListNames(proc, proc->yDiff_cur / 16 + i);
	
	PrepUnit_DrawLeftUnitName(unit);
	PrepSkill_DrawPickTotalBar(unit, 0);
	PrepSkill_DrawLeftSkillsIcon(unit);
	
	
	NewGreenTextColorManager((ProcPtr)proc);
	LoadDialogueBoxGfx(BG_SCREEN_ADDR(0x29), 5);
	RestartScreenMenuScrollingBg();
	
}











// Unit Select Loop
void PrepSkill_UnitSelectLoop (struct Proc_PrepUnit* proc){
	
	// This is a loop function!
	
	u16 key;
	
	if( proc->list_num_cur != proc->list_num_pre )
	{
		PrepSkill_HandleUnitListScrollLoop(proc);
		return;
	}
	
	// Handle DPAD button
	key = gKeyStatusPtr->repeatedKeys;
	
	if( DPAD_LEFT & key )
	{
		if( 1 & proc->list_num_cur )
			proc->list_num_cur--;
	}
	else if( DPAD_RIGHT & key )
	{
		if( 0 == (1 & proc->list_num_cur) )
			if( (proc->list_num_cur + 1) < GetPrepScreenUnitListSize() )
				proc->list_num_cur++;
	}	
	else if( DPAD_UP & key )
	{
		if( (proc->list_num_cur - 2) >= 0 )
			proc->list_num_cur -= 2;
	}
	else if( DPAD_DOWN & key )
	{
		if( (proc->list_num_cur + 2) < GetPrepScreenUnitListSize() )
			proc->list_num_cur += 2;
	
	} // if key for DPAD
	
	
	if( proc->list_num_cur != proc->list_num_pre )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x65);
		
		PrepSkill_UpdateUnitMenuTexts(proc);
		
		// Return to scroll unit list
		return;
	}
	
	
	
	
	// Handle normal button
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		Proc_Goto(proc, LABEL_PREPSKILL_END);
		return;
	} // B_BUTTON

	
}

void PrepSkill_UpdateUnitMenuTexts(struct Proc_PrepUnit* proc){
	
	static void (*PrepUnit_DrawLeftUnitName)(struct Unit*) = (const void*) 0x809A931;
	static void (*PrepUnit_DrawUnitListNames)(struct Proc_PrepUnit*, int) = (const void*) 0x809A581;
	extern int sub_809AD90(struct Proc_PrepUnit*);
	
	struct Unit* unit;
	
	unit = GetPrepScreenUnitListEntry(proc->list_num_cur);
	
	// ==========  On Draw Left ==========
	if( proc->list_num_pre != proc->list_num_cur )
	{
		PrepUnit_DrawLeftUnitName(unit);
		PrepSkill_DrawPickTotalBar(unit, 1);
		PrepSkill_DrawLeftSkillsIcon(unit);
	}
	
	
	// ==========  Judge whether menu should scroll ==========
	if( 0 == sub_809AD90(proc) )
	{
		
		proc->list_num_pre = proc->list_num_cur; // Important!!
		
		PrepDrawHand(
			(proc->list_num_pre % 2) * 56 + 0x70,
			(proc->list_num_cur / 2) * 16 - proc->yDiff_cur + 0x18,
			0x7, 0x800);
			
	}
	else
	{
		if( proc->list_num_cur < proc->list_num_pre )
			PrepUnit_DrawUnitListNames(proc, proc->yDiff_cur / 16 - 1);
		
		if( proc->list_num_cur > proc->list_num_pre )
			PrepUnit_DrawUnitListNames(proc, proc->yDiff_cur / 16 + 6);
		
		sub_80AD4E4( (proc->list_num_pre % 2) * 56 + 0x70 );
	}
	
}



void PrepSkill_HandleUnitListScrollLoop(struct Proc_PrepUnit* proc){
	
	static void (*PrepMenu_UpdateTsaScroll)(int) = (const void*) 0x809A645;
	extern void sub_809AE10(struct Proc_PrepUnit*);
	
	
	
	if( proc->list_num_cur == proc->list_num_pre )
		return;
	
	
	// ========== On Menu scroll ==========
	
	// If L pressed, menu scrolls faster (well...)
	proc->scroll_val = 
		0 == (L_BUTTON & gKeyStatusPtr->heldKeys)
			? 4
			: 8;

	
	if( proc->list_num_cur < proc->list_num_pre )
		proc->yDiff_cur -= proc->scroll_val;
	
	else if( proc->list_num_cur > proc->list_num_pre )
		proc->yDiff_cur += proc->scroll_val;
	
	if( 0 == (proc->yDiff_cur & 0xF) )
	{
		PrepMenu_UpdateTsaScroll( proc->yDiff_cur / 16 - 1 );
		PrepMenu_UpdateTsaScroll( proc->yDiff_cur / 16 + 6 );
		sub_809AE10(proc);
		
		// <!>
		proc->list_num_pre = proc->list_num_cur;
	}
	
	BG_SetPosition(2,0, proc->yDiff_cur - 0x18);
	
	
	// In fact there also need update SMSs' position,
	// But it was set in function-PrepSkill_UpdateSMSsAndObjs 
	// by Parallel Worker
	
	return;
}





// =======================================================
// ====================== On Draw ========================
// =======================================================

void PrepSkill_InitTexts(){
	
	// 0x809A815
	// gPrepUnitTexts = 2013598
	
	Font_InitForUIDefault();
	
	// 0x0 ~ 0xD: (total 14) unit name
	for( int i = 0; i < 0xE; i++ )
		Text_Init(&gPrepUnitTexts[i], 5);
	
	// 0xE ~ 0x12: (total 5) item name
	for( int i = 0; i < 0x5; i++ )
		Text_Init(&gPrepUnitTexts[i + 0xE], 0xF);
	
	Text_Init(&gPrepUnitTexts[0x13], 7);
	Text_Init(&gPrepUnitTexts[0x14], 10);
	Text_Init(&gPrepUnitTexts[0x15], 15);
	
	// Borrow from StatScreen's TextHandle!
	
	// Two for right-upper bar
	Text_Init(&gStatScreen.text[0], 10);
	Text_Init(&gStatScreen.text[1], 10);
	
	// Two for left skill text
	Text_Init(&gStatScreen.text[2], 10);
	Text_Init(&gStatScreen.text[3], 10);
}




void PrepSkill_DrawPickTotalBar(struct Unit* unit, int config){
	
	// 0x809AAF1
	// config: 0->init, 1->update
	
	if( 0 == config )
	{
		Text_Clear(&gStatScreen.text[0]);
		Text_Clear(&gStatScreen.text[1]);
		
		DrawTextInline(
			&gStatScreen.text[0],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xE, 0x1),
			TEXT_COLOR_NORMAL, 0, 0,
			"Pick" );
		
		DrawTextInline(
			&gStatScreen.text[1],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0x14, 0x1),
			TEXT_COLOR_NORMAL, 0, 0,
			"Total Skills" );
		
	} // if config
	
	
	// W.I.P.
	// Draw Numbers
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x11, 0x2),
		1, 1, 0 );
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1B, 0x2),
		1, 1, 0 );
	
	DrawDecNumber(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x11, 0x1),
		TEXT_COLOR_BLUE,
		2 );
	
	DrawDecNumber(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1B, 0x1),
		TEXT_COLOR_BLUE,
		5 );
		
	
	// On End
	BG_EnableSyncByMask(0b01);
}


void PrepSkill_DrawLeftSkillsIcon(struct Unit* unit){
	
	struct SkillFastTesterList* list;
	
	
	ResetIconGraphics_();
	
	Text_Clear( &gPrepUnitTexts[0xE] );
	Text_Clear( &gPrepUnitTexts[0xF] );
	Text_Clear( &gPrepUnitTexts[0x10] );
	Text_Clear( &gPrepUnitTexts[0x11] );
	Text_Clear( &gPrepUnitTexts[0x12] );
	Text_Clear( &gStatScreen.text[2] );
	Text_Clear( &gStatScreen.text[3] );
	
	
	
	// Clear exiting Texts and Icons
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 5),
		0xB, 0xA, 0);
	
	
	// Draw Texts
	DrawTextInline(
		&gPrepUnitTexts[0xE],
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 5),
		TEXT_COLOR_GOLD,
		0, 0, 
		"Equippable Skills");
	
	DrawTextInline(
		&gPrepUnitTexts[0xF],
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 9),
		TEXT_COLOR_GOLD,
		0, 0, 
		"Class & Unit Skills");
	
	
	// Draw Handleable Skills' Icon
	list = GetOrMakeSklFastList(unit);
	
	if ( list->cnt == 0 ) 
	{
		DrawTextInline(
			&gPrepUnitTexts[0x10],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 2, 7),
			TEXT_COLOR_GRAY,
			0, 0, 
			"None");
	} 
	else
	{
		for( int i = 0; i < list->cnt; i++ )
		{
			DrawIcon(
				TILEMAP_LOCATED( gBG0TilemapBuffer, 2 + i * 2, 7 ),
				SKILL_ICON(list->skills[i]), 
				TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
			
			if( i >= UNIT_SKILL_COUNT )
				break;
			
		} // for skill cnt
	} // if ( list->cnt == 0 ) 
	
	
	for( int i = 0; i < 2; i++ )
		DrawIcon(
			TILEMAP_LOCATED( gBG0TilemapBuffer, 2 + i * 2, 11 ),
			SKILL_ICON(0x17+i), 
			TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	
	
	
	
	
	
	// Combat Arts
	DrawTextInline(
		&gPrepUnitTexts[0x11],
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 0xF),
		TEXT_COLOR_GOLD,
		0, 0, 
		"Combat Arts");
	
	for( int i = 0; i < 2; i++ )
		DrawIcon(
			TILEMAP_LOCATED( gBG0TilemapBuffer, 2 + i * 2, 17 ),
			MASTERY_ICON(0x1+i), 
			TILEREF(0, STATSCREEN_BGPAL_EXTICONS) );
	
	
	// Battalion
	DrawTextInline(
		&gStatScreen.text[2],
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0xF, 0x11),
		TEXT_COLOR_GOLD,
		0, 0, 
		"Battalion");
	
	DrawIcon(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x16, 0x11 ),
		MASTERY_ICON(MASTERY_ICON_REASON), 
		TILEREF(0, STATSCREEN_BGPAL_EXTICONS) );
}






void PrepSkill_DrawWindowGfx(void){
	
	// 0x809A874
	extern u16 Gfx_PrepSkillScreen[]; // gfx
	extern u16 Gfx_PrepSkillScreen2[]; // gfx2
	extern u16 Pal_PrepSkillScreen[]; // pal
	extern u16 Tsa_PrepSkillScreen[]; // tsa
	
	ResetIconGraphics_();
	LoadUiFrameGraphics();
	LoadObjUIGfx();
	
	LoadIconPalettes(4); // item icon
	
	CopyDataWithPossibleUncomp(Gfx_PrepSkillScreen2, (void*)0x06006000);
	CopyDataWithPossibleUncomp(Gfx_PrepSkillScreen, (void*)0x06000440);
	
	CopyDataWithPossibleUncomp(Tsa_PrepSkillScreen, gGenericBuffer);
	CallARM_FillTileRect(gBG1TilemapBuffer, gGenericBuffer, 0x1000);
	
	CopyToPaletteBuffer(Pal_PrepSkillScreen, 0x1E0, 0x20);
	CopyToPaletteBuffer(Pal_PrepSkillScreen, 0x320, 0x20);
	EnablePaletteSync();
	
}



void PrepSkill_UpdateSMSsAndObjs(struct Proc_PrepUnit* proc){
	
	static void (*DrawUnitSMS)(int root_node, int xPos, int yPos, struct Unit* unit) = (const void*) 0x8027B61;
	
	for( int i = 0; i < GetPrepScreenUnitListSize(); i++ )
	{
		int yoff = (i >> 1) << 4;
		yoff -= proc->yDiff_cur;
		
		if( yoff < 0 )
			continue;
		
		if( (yoff + 0xF) > 0x5F )
			continue;
		
		DrawUnitSMS(
			0, 
			(i & 1)* 56 + 0x70,
			yoff + 0x18,
			GetPrepScreenUnitListEntry(i) );
		
	} // for
	
	
	if( 0 == (proc->yDiff_cur & 0xF) )
	{
		gLCDControlBuffer.dispcnt.win0_on = 0;
		gLCDControlBuffer.dispcnt.win1_on = 0;
		gLCDControlBuffer.dispcnt.objWin_on = 0;
	}
	else
	{
		
		gLCDControlBuffer.dispcnt.win0_on = 1;
		gLCDControlBuffer.dispcnt.win1_on = 1;
		gLCDControlBuffer.dispcnt.objWin_on = 1;
		
		gLCDControlBuffer.win0_left = 0;
		gLCDControlBuffer.win0_top = 0;
		gLCDControlBuffer.win0_right = 0xF0;
		gLCDControlBuffer.win0_bottom = 0x1A;
		
		gLCDControlBuffer.win1_left = 0;
		gLCDControlBuffer.win1_top = 0x78;
		gLCDControlBuffer.win1_right = 0xF0;
		gLCDControlBuffer.win1_bottom = 0xA0;
		
		gLCDControlBuffer.wincnt.win0_enableBg0 = 1;
		gLCDControlBuffer.wincnt.win0_enableBg1 = 1;
		gLCDControlBuffer.wincnt.win0_enableBg2 = 0;
		gLCDControlBuffer.wincnt.win0_enableBg3 = 1;
		gLCDControlBuffer.wincnt.win0_enableObj = 0;
		
		gLCDControlBuffer.wincnt.win1_enableBg0 = 1;
		gLCDControlBuffer.wincnt.win1_enableBg1 = 1;
		gLCDControlBuffer.wincnt.win1_enableBg2 = 0;
		gLCDControlBuffer.wincnt.win1_enableBg3 = 1;
		gLCDControlBuffer.wincnt.win1_enableObj = 1;
		
		gLCDControlBuffer.wincnt.wout_enableBg0 = 1;
		gLCDControlBuffer.wincnt.wout_enableBg1 = 1;
		gLCDControlBuffer.wincnt.wout_enableBg2 = 1;
		gLCDControlBuffer.wincnt.wout_enableBg3 = 1;
		gLCDControlBuffer.wincnt.wout_enableObj = 1;
		
	}
	
	SMS_FlushDirect();
	
}




// =======================================================
// ====================== GLOBAL =========================
// =======================================================
void StartPrepScreenSkillsMenu(struct Proc_AtMenu* proc){
	
	extern struct Unit* sub_8095394(); // maybe get leader?
	extern int sub_80958FC(struct Unit*); // Get index in Prep-Unit-List
	
	struct Proc_PrepUnit* child;
	
	child = (struct Proc_PrepUnit*)
		Proc_StartBlocking(ProcCmd_PrepSkillScreen, proc);
	
	child->list_num_cur = sub_80958FC( sub_8095394() );
	child->list_num_pre = child->list_num_cur;
	child->max_counter = proc->max_counter;
	child->yDiff_cur = proc->yDiff;
	
	return;
	
}




