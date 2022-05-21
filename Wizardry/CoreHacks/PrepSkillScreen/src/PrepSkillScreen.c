#include "gbafe-chax.h"
#include "PrepSkill.h"


enum{
	// Proc: Prep-SkillScreen's label
	LABEL_PREPSKILL_INIT = 0,
	LABEL_PREPSKILL_UNITLOOP,
	LABEL_PREPSKILL_STATSCREEN,
	LABEL_PREPSKILL_SUBMENU,
	LABEL_PREPSKILL_SUBMENU_END,
	LABEL_PREPSKILL_SUBLIST,
	
	LABEL_PREPSKILL_END,
};



// ========================================
// ======= There will added in cLib =======
// ========================================

extern void NewFadeIn(int step);
extern int FadeInExists();

// For StatScreen
extern void sub_809B4C0(ProcPtr);
extern void sub_809B014(ProcPtr);
extern void sub_809B504(ProcPtr);
extern void sub_809B520(ProcPtr);


// OAM Misc
static void (*PrepDrawHand)(int x, int y, int, int) = (const void*) 0x80AD51D;
extern void ResetPrepScreenHandCursor(ProcPtr);
static void (*PrepScreen_DrawHandGfxMaybe)(int, int) = (const void*) 0x80AD4A1;
static void (*UpdateHandObjAt)(int px) = (const void*) 0x80AD4E5;

// BG Scroll
extern int NewFadeOut(ProcPtr);
static void (*PrepStartScroll)(ProcPtr, int, int, int, int) = (const void*) 0x8097749;
extern void RestartScreenMenuScrollingBg();
// static void (*PrepMenu_UpdateTsaScroll)(int) = (const void*) 0x809A645;


// Parallel Worker
static void (*StartParallerWorkerWithParam)( void* func, int param, ProcPtr) = (const void*) 0x80ACE21; // func(ProcPtr,int param)
extern void DeleteEach6CDifferedLoop();



// ========================================
// ======= Static Func Definitions ========
// ========================================

// static void * (struct Proc_PrepUnit* proc);
const static struct ProcCmd gProc_PrepSkillScreen[];
static void PrepSkill_OnEnd (struct Proc_PrepUnit* proc);
static void PrepSkill_InitScreen (struct Proc_PrepUnit* proc);
static void PrepSkill_UnitSelectLoop (struct Proc_PrepUnit* proc);
static void PrepSkill_PreSubMenu (struct Proc_PrepUnit* proc);
static void PrepSkill_StartSubMenu (struct Proc_PrepUnit* proc);
static void PrepSkill_PostSubMenu (struct Proc_PrepUnit* proc);
static void PrepSkill_PreSubList(struct Proc_PrepUnit* proc);
static void PrepSkill_StartSubList(struct Proc_PrepUnit* proc);
static void PrepSkill_PostSubList(struct Proc_PrepUnit* proc);


// SubMenu
static void PrepSkillSubMenu_OnPickSkills(struct Proc_PrepUnit* proc);
static void PrepSkillSubMenu_OnPickCombatArts(struct Proc_PrepUnit* proc);
// static void PrepSkillSubMenu_OnPickBattalions(struct Proc_PrepUnit* proc);
static int PrepSkillSubMenu_Bpressed (struct Proc_PrepUnit* proc);


// On Draw
static void (*PrepUnit_DrawLeftUnitName)(struct Unit*) = (const void*) 0x809A931;
static void PrepSkill_InitTexts();


// Parallel
static void PrepSkill_UpdateSMSsAndObjs(struct Proc_PrepUnit* proc);
static void PrepSkill_UpdateUnitMenuTexts(struct Proc_PrepUnit* proc);










// ========================================
// ================ Main ==================
// ========================================

const static struct ProcCmd gProc_PrepSkillScreen[] = {
	
	PROC_NAME	("PREP_SKILLSCREEN"),
	
	PROC_SET_END_CB (PrepSkill_OnEnd),

// Init
PROC_LABEL (LABEL_PREPSKILL_INIT),
	PROC_YIELD,
	PROC_CALL	(PrepSkill_InitScreen),
	PROC_SLEEP	(2),
	PROC_CALL_ARG (NewFadeIn, 0x8),
	PROC_WHILE	(FadeInExists),

// Main Loop
PROC_LABEL (LABEL_PREPSKILL_UNITLOOP),
	PROC_REPEAT	(PrepSkill_UnitSelectLoop),
	

// Sub menu
PROC_LABEL (LABEL_PREPSKILL_SUBMENU),
	PROC_YIELD,
	PROC_CALL	(PrepSkill_PreSubMenu),
	PROC_YIELD,
	PROC_CALL	(PrepSkill_StartSubMenu),
	PROC_YIELD,
	PROC_CALL	(EnablePrepScreenMenu),
	PROC_SLEEP	(2),
	PROC_WHILE	(PrepScreenMenuExists),	// But PrepScreenMenu will never end itself
// Submenu End
PROC_LABEL (LABEL_PREPSKILL_SUBMENU_END),	
	PROC_YIELD,
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),
	PROC_CALL	(PrepSkill_PostSubMenu),
	PROC_GOTO	(LABEL_PREPSKILL_INIT),
	

// Stat Screen
PROC_LABEL (LABEL_PREPSKILL_STATSCREEN),
	PROC_CALL	(sub_809B4C0),
	PROC_SLEEP	(2),
	PROC_CALL	(sub_809B014),
	PROC_CALL	(sub_809B504), // Here Start StatScreen
	PROC_YIELD,
	PROC_CALL	(sub_809B520),
	PROC_GOTO	(LABEL_PREPSKILL_INIT),


// Sub List
PROC_LABEL (LABEL_PREPSKILL_SUBLIST),
	PROC_YIELD,
	// here will jump from post-submenu, where it has been faded out,
	// so here we don't need to fade out
	PROC_CALL	(PrepSkill_PreSubList),
	PROC_YIELD,
	PROC_CALL	(PrepSkill_StartSubList),
	PROC_YIELD,
	PROC_CALL	(PrepSkill_PostSubList),
	PROC_GOTO	(LABEL_PREPSKILL_INIT),



	

// End
PROC_LABEL	(LABEL_PREPSKILL_END),
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),
	PROC_CALL	(DeleteEach6CDifferedLoop),
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
	// static void (*PrepUnit_DrawUnitListNames)(struct Proc_PrepUnit*, int) = (const void*) 0x809A581;

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
	PrepSkill_DrawPickTotalBar(unit, ON_DRAW_CONFIG_INIT);
	PrepSkill_DrawLeftSkillsIcon(unit, ON_DRAW_CONFIG_INIT);
	// PrepSkill_DrawBattalionBar(unit, ON_DRAW_CONFIG_INIT);
	
	NewGreenTextColorManager((ProcPtr)proc);
	LoadDialogueBoxGfx(BG_SCREEN_ADDR(0x29), 5);
	RestartScreenMenuScrollingBg();
	
}






// Unit Select Loop
void PrepSkill_UnitSelectLoop (struct Proc_PrepUnit* proc){
	
	// This is a loop function!
	
	// static void (*PrepUnit_DrawUnitListNames)(struct Proc_PrepUnit*, int) = (const void*) 0x809A581;
	// static int (*ShouldPrepUnitMenuScroll)(struct Proc_PrepUnit*) = (const void*) 0x809AD91;
	static void (*PrepMenu_UpdateTsaScroll)(int) = (const void*) 0x809A645;
	extern void sub_809AE10(struct Proc_PrepUnit*);
	
	
	const u16 key_pre = gKeyStatusPtr->repeatedKeys;
	
	if( proc->list_num_cur != proc->list_num_pre )
		goto goto_MenuScroll;
	
	// If L pressed, menu scrolls faster (well...)
	proc->scroll_val = 
		0 == (L_BUTTON & gKeyStatusPtr->heldKeys)
			? 4
			: 8;
	
	
	
	// Handle normal button
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		Proc_Goto(proc, LABEL_PREPSKILL_END);
		return;
	} // B_BUTTON
	
	else if( R_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSKILL_STATSCREEN);
		return;
	} // R_BUTTON
	
	else if( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6A);
		
		Proc_Goto(proc, LABEL_PREPSKILL_SUBMENU);
		return;
	} // A_BUTTON
	
	
	// DPAD
	if( DPAD_LEFT & key_pre )
		if( 1 & proc->list_num_cur )
			proc->list_num_cur--;
	
	if( DPAD_RIGHT & key_pre )
		if( 0 == (1 & proc->list_num_cur) )
			if( (proc->list_num_cur + 1) < GetPrepScreenUnitListSize() )
				proc->list_num_cur++;
			
	if( DPAD_UP & key_pre )
		if( (proc->list_num_cur - 2) >= 0 )
			proc->list_num_cur -= 2;
	
	if( DPAD_DOWN & key_pre )
		if( (proc->list_num_cur + 2) < GetPrepScreenUnitListSize() )
			proc->list_num_cur += 2;
	
	if( proc->list_num_cur == proc->list_num_pre )
		return;
	
	// Draw Text
	// By introducing Parallel worker
	// it can effectively reduce operation delay!
	StartParallerWorkerWithParam(PrepSkill_UpdateUnitMenuTexts, 0, proc);
	
	// In fact there also need to update SMSs' position,
	// But it was set in function: PrepSkill_UpdateSMSsAndObjs 
	// by Parallel Worker init in function: PrepSkill_InitScreen
	
	// M4a
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x65);
	
	
	// ==========  Judge whether menu should scroll ==========
	if( 0 == ShouldPrepUnitMenuScroll(proc) )
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
		
		UpdateHandObjAt( (proc->list_num_pre % 2) * 56 + 0x70 );
	}
	
	
	if( proc->list_num_pre == proc->list_num_cur )
		return;
	
	
	
	// ========== On Menu scroll ==========
goto_MenuScroll:
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

}





// =======================================================
// ====================== SubMenu ========================
// =======================================================

void PrepSkill_PreSubMenu (struct Proc_PrepUnit* proc){
	
	extern u16 Tsa_PrepSkillScreenSubMenu[]; // tsa
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1, 0x5),
		0xA, 0xD, 0 );
	
	BG_Fill(gBG1TilemapBuffer, 0);
	CopyDataWithPossibleUncomp(Tsa_PrepSkillScreenSubMenu, gGenericBuffer);
	CallARM_FillTileRect(gBG1TilemapBuffer, gGenericBuffer, 0x1000);
	
	gLCDControlBuffer.bg0cnt.priority = 0b00;
	
	
}


void PrepSkill_StartSubMenu (struct Proc_PrepUnit* proc){
	
	
	// LoadDialogueBoxGfx(0, -1);
	// Font_InitForUIDefault();
	
	StartPrepScreenMenu(proc);
	
	SetPrepScreenMenuItem(
		MENUITEM_PREPSKILL_SKILL, 
		PrepSkillSubMenu_OnPickSkills, 
		TEXT_COLOR_NORMAL, 
		ENUM_msg_PrepSkillMenu_PickSkillName, 
		ENUM_msg_PrepSkillMenu_PickSkillDesc
	);
	
	SetPrepScreenMenuItem(
		MENUITEM_PREPSKILL_COMBAT, 
		PrepSkillSubMenu_OnPickCombatArts, 
		TEXT_COLOR_NORMAL, 
		ENUM_msg_PrepSkillMenu_PickCombatName, 
		ENUM_msg_PrepSkillMenu_PickCombatDesc
	);
	
/* 	SetPrepScreenMenuItem(
		MENUITEM_PREPSKILL_BATTALION, 
		PrepSkillSubMenu_OnPickBattalions, 
		TEXT_COLOR_NORMAL, 
		ENUM_msg_PrepSkillMenu_PickBattalionName, 
		ENUM_msg_PrepSkillMenu_PickBattalionDesc
	); */
	
	SetPrepScreenMenuOnBPress(PrepSkillSubMenu_Bpressed);
	
	
	SetPrepScreenMenuSelectedItem(0);
	DrawPrepScreenMenuFrameAt(0x2, 0x7);
	
}



// Some hack than vanilla At-menu:
// we will directly end the prep-menu when we press A,
// rather directly jump to block current proc.
// so we will also end into main loop, rather than sub-menu loop
// to identify whether we press A or B
// we take Proc_PrepUnit+0x37, proc->button_blank 
// to store current button when A pressed
// and if B pressed will store 0xFF

void PrepSkill_PostSubMenu (struct Proc_PrepUnit* proc){
	
	struct Proc* proc_PrepMenu = Proc_Find(gProc_PrepScreenMenu);
	
	if( NULL != proc_PrepMenu )
	{
		EndAllProcChildren(proc_PrepMenu);
		Proc_End(proc_PrepMenu);
	}
	
	gLCDControlBuffer.bg0cnt.priority = 0b10;
	
	
	if( MENUITEM_PREPSKILL_NULL != proc->button_blank )
		Proc_Goto(proc, LABEL_PREPSKILL_SUBLIST);
	
}




// Button pressed

int PrepSkillSubMenu_Bpressed(struct Proc_PrepUnit* proc) {
	
	Proc_Goto(proc, LABEL_PREPSKILL_SUBMENU_END);
	
	proc->button_blank = MENUITEM_PREPSKILL_NULL;
	return 1;
}


void PrepSkillSubMenu_OnPickSkills(struct Proc_PrepUnit* proc){
	
	Proc_Goto(proc, LABEL_PREPSKILL_SUBMENU_END);
	proc->button_blank = MENUITEM_PREPSKILL_SKILL;
	
}

void PrepSkillSubMenu_OnPickCombatArts(struct Proc_PrepUnit* proc){
	
	Proc_Goto(proc, LABEL_PREPSKILL_SUBMENU_END);
	proc->button_blank = MENUITEM_PREPSKILL_COMBAT;
	
}

/* void PrepSkillSubMenu_OnPickBattalions(struct Proc_PrepUnit* proc){
	
	Proc_Goto(proc, LABEL_PREPSKILL_SUBMENU_END);
	proc->button_blank = MENUITEM_PREPSKILL_BATTALION;
	
} */










// =======================================================
// ======================= On Draw =======================
// =======================================================


void PrepSkill_InitTexts(){
	
	// 0x809A815
	// gPrepUnitTexts = 2013598
	
	Font_InitForUIDefault();
	
	// 0x0 ~ 0xD: (total 14) unit name
	for( int i = 0; i < 0xE; i++ )
		Text_Init(&gPrepUnitTexts[i], 5);
	
	Text_Init(&gPrepUnitTexts[0xE], 9); 	// "Equippable Skills"
	Text_Init(&gPrepUnitTexts[0xF], 10);	// "Class & Unit Skills"
	Text_Init(&gPrepUnitTexts[0x10], 8);	// "Combat Arts"
	Text_Init(&gPrepUnitTexts[0x11], 6);	// "Battalion"
	Text_Init(&gPrepUnitTexts[0x12], 3);	// "none" for left RAM skills
	Text_Init(&gStatScreen.text[2], 3); 	// "none" for left ROM skills
	Text_Init(&gStatScreen.text[3], 3); 	// "none" for left CombatArts
	
	Text_Init(&gPrepUnitTexts[0x13], 7);
	Text_Init(&gPrepUnitTexts[0x14], 10);
	Text_Init(&gPrepUnitTexts[0x15], 15);
	
	// Borrow from StatScreen's TextHandle!
	
	// Two for right-upper bar
	Text_Init(&gStatScreen.text[0], 3); 	// "pick"
	Text_Init(&gStatScreen.text[1], 6); 	// "total skill"
}






// =======================================================
// ================== Parallel Worker ====================
// =======================================================
// inside Parallel worker
void PrepSkill_UpdateSMSsAndObjs(struct Proc_PrepUnit* proc){
	
	static void (*DrawUnitSMS)(int root_node, int xPos, int yPos, struct Unit* unit) = (const void*) 0x8027B61;
	
	for( int i = 0; i < GetPrepScreenUnitListSize(); i++ )
	{
		int yoff = (i >> 1) << 4;
		yoff -= proc->yDiff_cur;
		
		if( yoff < 0 )
			continue;
		
		if( yoff > 0x50 )
			continue;
		
		DrawUnitSMS(
			0, 
			(i & 1)* 56 + 0x70,
			yoff + 0x18,
			GetPrepScreenUnitListEntry(i) );
		
	} // for
	
	
	
	PutSprite(5, 
		0x90, 
		0x88,
		gObject_32x16, 
		OAM2_PAL(0x09) + 
			OAM2_LAYER(0b01) + 
			OAM2_CHR(0x160 / 0x20));
	
	PutSprite(5, 
		0xB0, 
		0x88,
		gObject_8x16, 
		OAM2_PAL(0x09) + 
			OAM2_LAYER(0b01) + 
			OAM2_CHR(0x1E0 / 0x20));
	
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


// Also inside Parallel worker
void PrepSkill_UpdateUnitMenuTexts(struct Proc_PrepUnit* proc){
	
	struct Unit* unit;
	
	unit = GetPrepScreenUnitListEntry(proc->list_num_cur);
	
	InitPrepSkillsList();
	MakeUnitPrepSkillsList(unit);
	
	PrepUnit_DrawLeftUnitName(unit);
	PrepSkill_DrawPickTotalBar(unit, ON_DRAW_CONFIG_UPDATE);
	PrepSkill_DrawLeftSkillsIcon(unit, ON_DRAW_CONFIG_UPDATE);
	// PrepSkill_DrawBattalionBar(unit, ON_DRAW_CONFIG_INIT);
}




















// =======================================================
// ===================== Sub List ========================
// =======================================================



void PrepSkill_PreSubList(struct Proc_PrepUnit* proc){
	extern void DeleteEach6CDifferedLoop();
	
	DeleteEach6CDifferedLoop();
}


void PrepSkill_StartSubList(struct Proc_PrepUnit* proc){
	
	// Judge for Submenu
	switch (proc->button_blank)
	{
		case MENUITEM_PREPSKILL_SKILL:
			PrepSkill_StartPickSkillScreen(proc);
			break;
		
		case MENUITEM_PREPSKILL_COMBAT:
			PrepSkill_StartPickCombatArtScreen(proc);
			break;
		
		case MENUITEM_PREPSKILL_BATTALION:
			break;
			
		default:
			break;
	
	} // switch
	
	
}
void PrepSkill_PostSubList(struct Proc_PrepUnit* proc){
	
	extern struct Unit* sub_8095394(); // maybe get leader?
	extern int sub_80958FC(struct Unit*); // Get index in Prep-Unit-List
	
	proc->list_num_cur = sub_80958FC( sub_8095394() );
	proc->list_num_pre = proc->list_num_cur;
	
	return;
}









// =======================================================
// ====================== GLOBAL =========================
// =======================================================
void StartPrepScreenSkillsMenu(struct Proc_AtMenu* proc){
	
	extern struct Unit* sub_8095394(); // maybe get leader?
	extern int sub_80958FC(struct Unit*); // Get index in Prep-Unit-List
	
	struct Proc_PrepUnit* child;
	
	child = (struct Proc_PrepUnit*)
		Proc_StartBlocking(gProc_PrepSkillScreen, proc);
	
	// Here, child proc should call for :
	// SetPrepScreenUnitListCharID(proc->unit->pCharacterData->number);
	// to make here, the parent proc can get the unit
	child->list_num_cur = sub_80958FC( sub_8095394() );
	
	child->list_num_pre = child->list_num_cur;
	child->max_counter = proc->max_counter;
	child->yDiff_cur = proc->yDiff;
	
	return;
	
}








