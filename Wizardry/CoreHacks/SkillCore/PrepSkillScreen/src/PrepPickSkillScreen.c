#include "gbafe-chax.h"
#include "PrepSkill.h"



// ========================================
// ======= There will added in cLib =======
// ========================================
static void (*PrepUnit_DrawLeftUnitName)(struct Unit*) = (const void*) 0x809A931;
extern void NewFadeIn(int step);
extern int FadeInExists();

// OAM Misc
static void (*PrepDrawHand)(int x, int y, int, int) = (const void*) 0x80AD51D;
extern void ResetPrepScreenHandCursor(ProcPtr);
static void (*PrepScreen_DrawHandGfxMaybe)(int, int) = (const void*) 0x80AD4A1;

// BG Scroll
extern int NewFadeOut(ProcPtr);
static void (*PrepStartScroll)(ProcPtr, int, int, int, int) = (const void*) 0x8097749;
extern void RestartScreenMenuScrollingBg();

// Parallel Worker
static void (*StartParallerWorkerWithParam)( void* func, int param, ProcPtr) = (const void*) 0x80ACE21; // func(ProcPtr,int param)
extern void DeleteEach6CDifferedLoop();




// ========================================
// ======= Static Func Definitions ========
// ========================================
static void PrepPickSkillList_InitTexts();
static void PrepPickSkillList_DrawWindowGfx(void);
static void PrepPickSkillList_DrawRightBarTexts(struct Unit*, int config);
static void PrepPickSkillList_DrawTotalSkill(struct Unit*);
static void PrepPickSkillList_UpdateSkillDesc(struct Proc_PrepSkillSubList* proc);

static void PrepPickSkill_InitSkillsList (struct Proc_PrepSkillSubList* proc);
static void PrepPickSkill_InitScreen (struct Proc_PrepSkillSubList* proc);
static void PrepPickSkill_MainLoop(struct Proc_PrepSkillSubList* proc);







// ========================================
// ================= Core =================
// ========================================

const static struct ProcCmd gProc_PrepSkillPickSkillList[] = {
	
	PROC_NAME	("PREP_SKILLSCREEN_PICKSKILLS"),

// Init
PROC_LABEL (LABEL_PREPSLILLSLIST_INIT),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkill_InitSkillsList),
	PROC_CALL	(PrepPickSkill_InitScreen),
	PROC_SLEEP	(2),
	PROC_CALL_ARG (NewFadeIn, 0x8),
	PROC_WHILE	(FadeInExists),


// Main Loop
PROC_LABEL (LABEL_PREPSLILLSLIST_IDLE),	
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkill_MainLoop),
	
	

PROC_LABEL (LABEL_PREPSLILLSLIST_END),
	PROC_CALL	(DeleteEach6CDifferedLoop),
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),
	PROC_END,
};





void PrepPickSkill_InitSkillsList (struct Proc_PrepSkillSubList* proc){
	
	
	InitPrepSkillsList();
	MakeUnitPrepSkillsList(proc->unit);
	
	proc->state = STATE_PREPSUB_NORMAL;
	proc->list_index = 0;
	proc->list_index_pre = 0;
	proc->list_type = PREP_SKLSUB_RIGHT;
	proc->list_type_pre = PREP_SKLSUB_RIGHT;
	proc->skill_id_pre = 0; // update on desc
}




void PrepPickSkill_InitScreen (struct Proc_PrepSkillSubList* proc){
	
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
	
	//sub_809ADC8(proc); 
	
	BG_Fill(gBG0TilemapBuffer, 0);
	BG_Fill(gBG1TilemapBuffer, 0);
	BG_Fill(gBG2TilemapBuffer, 0);
	
	gLCDControlBuffer.bg0cnt.priority = 0b10;
	gLCDControlBuffer.bg1cnt.priority = 0b10;
	gLCDControlBuffer.bg2cnt.priority = 0b01;
	gLCDControlBuffer.bg3cnt.priority = 0b11;
	
	BG_SetPosition( 0, 0, 0);
	BG_SetPosition( 1, 0, 0);
	BG_SetPosition( 2, 0, 0);
	BG_SetPosition( 3, 0, 0);
	
	PrepPickSkillList_InitTexts();
	PrepPickSkillList_DrawWindowGfx();
	
	
	BG_EnableSyncByMask(0b1111);
	SetDefaultColorEffects();
	
	// Commom space
	ResetCommonSpace();
	
	// Hand
	ResetPrepScreenHandCursor(proc);
	PrepScreen_DrawHandGfxMaybe(0x600, 0x1);
	PrepDrawHand( 0x78, 0x28, 0, 0x800);
	
	
	// BG Scroll
	PrepStartScroll(proc, 0xE0, 0x20, 0x200, 2);
	
	// Draw Text Icons
	PrepUnit_DrawLeftUnitName(proc->unit);
	PrepSkill_DrawLeftSkillsIcon(proc->unit, ON_DRAW_CONFIG_INIT);
	PrepPickSkillList_DrawRightBarTexts(proc->unit, ON_DRAW_CONFIG_INIT);
	PrepPickSkillList_DrawTotalSkill(proc->unit);
	
	// Parallel to update skill-desc
	StartParallerWorkerWithParam(PrepPickSkillList_UpdateSkillDesc, 0, proc);
	
	NewGreenTextColorManager((ProcPtr)proc);
	LoadDialogueBoxGfx(BG_SCREEN_ADDR(0x29), 5);
	RestartScreenMenuScrollingBg();
}





void PrepPickSkill_MainLoop(struct Proc_PrepSkillSubList* proc){
	
	struct PrepSkillsList* list;
	const u16 key_pre = gKeyStatusPtr->repeatedKeys;
	
	list = GetUnitPrepSkillsList(proc->unit);
	
	// Handle normal button
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_END);
		return;
	} // B_BUTTON
	
	
	
	// W.I,P.
	// DPAD
	if( DPAD_LEFT & key_pre ){
		if( 0 == proc->list_index )
			goto goto_fail;
		else
			proc->list_index--;
	} // DPAD_LEFT
	
	if( DPAD_RIGHT & key_pre ){
		if( list->total[proc->list_type] < proc->list_index )
			goto goto_fail;
		else
			proc->list_index++;
			
	} // DPAD_LEFT

	
	if( (proc->list_type_pre == proc->list_type) && (proc->list_index_pre == proc->list_index) )
		goto goto_fail;
	
	// W.I.P.
	proc->list_type_pre = proc->list_type;
	proc->list_index_pre = proc->list_index;
	
	// M4a
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x65);
	
	PrepDrawHand(
		0x78 + 0x10 * proc->list_index,
		0x28,
		0, 0x800);
	
goto_fail:
	return;
}





// =======================================================
// ====================== On Draw ========================
// =======================================================

void PrepPickSkillList_DrawWindowGfx(void){
	
	// 0x809A874
	extern u16 Gfx_PrepPickSkillScreen[]; // gfx
	extern u16 Gfx_PrepSkillScreen2[]; // gfx2
	extern u16 Pal_PrepSkillScreen[]; // pal
	extern u16 Tsa_PrepSubPickSkillScreen[]; // tsa
	
	ResetIconGraphics_();
	LoadUiFrameGraphics();
	LoadObjUIGfx();
	
	LoadIconPalettes(4); // item icon
	
	CopyDataWithPossibleUncomp(Gfx_PrepSkillScreen2, (void*)0x06006000);
	CopyDataWithPossibleUncomp(Gfx_PrepPickSkillScreen, (void*)0x06000440);
	
	CopyDataWithPossibleUncomp(Tsa_PrepSubPickSkillScreen, gGenericBuffer);
	CallARM_FillTileRect(gBG1TilemapBuffer, gGenericBuffer, 0x1000);
	
	CopyToPaletteBuffer(Pal_PrepSkillScreen, 0x1E0, 0x20);
	CopyToPaletteBuffer(Pal_PrepSkillScreen, 0x320, 0x20);
	EnablePaletteSync();
	
}


void PrepPickSkillList_InitTexts(){
	
	Font_InitForUIDefault();
	
	Text_Init(&gPrepUnitTexts[0xE], 9); 	// "Equippable Skills"
	Text_Init(&gPrepUnitTexts[0xF], 10);	// "Class & Unit Skills"
	Text_Init(&gPrepUnitTexts[0x10], 8);	// "Combat Arts"
	// Text_Init(&gPrepUnitTexts[0x11], 6);	// "Battalion"
	Text_Init(&gPrepUnitTexts[0x12], 3);	// "none" for left RAM skills
	Text_Init(&gStatScreen.text[2], 3); 	// "none" for left ROM skills
	Text_Init(&gStatScreen.text[3], 3); 	// "none" for left CombatArts
	
	// Two for right-upper bar
	Text_Init(&gStatScreen.text[0], 3); 	// "pick"
	Text_Init(&gStatScreen.text[1], 6); 	// "total skill"
	
	// Two for Right skill list
	Text_Init(&gStatScreen.text[4], 4); 	// "Skills"
	Text_Init(&gStatScreen.text[5], 3); 	// "none"
	
	// For skill desc
	Text_Init(&gStatScreen.text[6], 0x10); 
	Text_Init(&gStatScreen.text[7], 0x10);
	Text_Init(&gStatScreen.text[8], 0x10);
	
}


void PrepPickSkillList_DrawRightBarTexts(struct Unit* unit, int config){
	
	// config: 0->init, 1->update
	
	if( ON_DRAW_CONFIG_INIT == config )
	{
		Text_Clear(&gStatScreen.text[0]);
		Text_Clear(&gStatScreen.text[1]);
		Text_Clear(&gStatScreen.text[2]);
		
		DrawTextInline(
			&gStatScreen.text[0],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xE, 0x1),
			TEXT_COLOR_NORMAL, 0, 0,
			"Pick" );
		
		DrawTextInline(
			&gStatScreen.text[1],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0x14, 0x1),
			TEXT_COLOR_NORMAL, 0, 0,
			"Total Skill" );
		
		DrawTextInline(
			&gStatScreen.text[4],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xE, 0x3),
			TEXT_COLOR_NORMAL, 0, 0,
			"Skills" );
		
	} // if config
	
	
	// W.I.P.
	// Draw Numbers
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x12, 0x1),
		1, 1, 0 );
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1B, 0x1),
		1, 1, 0 );
	
	DrawDecNumber(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x12, 0x1),
		TEXT_COLOR_BLUE,
		unit->index );
	
	DrawDecNumber(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1B, 0x1),
		TEXT_COLOR_BLUE,
		unit->index );
		
	
	// On End
	BG_EnableSyncByMask(0b01);
	
}


void PrepPickSkillList_DrawTotalSkill(struct Unit* unit){
	
	struct PrepSkillsList* list;
	
	Text_Clear(&gStatScreen.text[3]);
	
	list = GetUnitPrepSkillsList(unit);
	

	if( 0 == list->total[PREP_SKLSUB_RIGHT] )
		DrawTextInline(
			&gStatScreen.text[3],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xF, 0x5),
			TEXT_COLOR_NORMAL, 0, 0,
			"None" );
	else		
		for( int i = 0; i < list->total[PREP_SKLSUB_RIGHT]; i++ )
		{
			int yOff = i / 6;
			int xOff = i - yOff * 6;
			
			int xPos = 0xF + 0x2 * xOff;
			int yPos = 0x5 + 0x2 * yOff;
			
			
			DrawIcon(
				TILEMAP_LOCATED( gBG0TilemapBuffer, xPos, yPos),
				SKILL_ICON(list->skills_all[i]), 
				TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) 
			);
		}
	

}















// =======================================================
// ================== Parallel Worker ====================
// =======================================================

void PrepPickSkillList_UpdateSkillDesc(struct Proc_PrepSkillSubList* proc){
	
	const int xStart = 0xD;
	const int yStart = 0xD;
	
	struct PrepSkillsList* list;
	int skill_id;
	char* str;
	
	list = GetUnitPrepSkillsList(proc->unit);
	
	switch( proc->list_type )
	{
		case PREP_SKLSUB_LEFT_RAM:
			skill_id = list->skills_ram[proc->list_index];
			break;
			
		case PREP_SKLSUB_LEFT_ROM:
			skill_id = list->skills_rom[proc->list_index];
			break;
		
		case PREP_SKLSUB_LEFT_CA:
			skill_id = list->skills_CombatArt[proc->list_index];
			break;
			
		case PREP_SKLSUB_RIGHT:
		default:
			skill_id = list->skills_all[proc->list_index];
			break;
	}
	
	if( skill_id == proc->skill_id_pre )
		// return;
	
	proc->skill_id_pre = skill_id;
	
	str = GetStringFromIndex(GetSkillDescMsg(skill_id));
	
	if( (0 == *str) || (0 == str) )
		return;
	
	
	
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, xStart, yStart),
		6, 0x10 , 0 );
	
	for( int line = 0; line < 3; line++ )
	{
		Text_Clear(&gStatScreen.text[6 + line]);
		
		DrawTextInline(
			&gStatScreen.text[6 + line],
			TILEMAP_LOCATED( gBG0TilemapBuffer, xStart, yStart + 2 * line),
			TEXT_COLOR_NORMAL, 0, 0,
			str );
		
		
		
		
		while( 1 != *str++ ) // '\n'
			if( 0 == *str )
				return;
	
	}
}







// =======================================================
// ====================== GLOBAL =========================
// =======================================================

void PrepSkill_StartPickSkillScreen(struct Proc_PrepUnit* proc){
	struct Proc_PrepSkillSubList* child;
	
	child = (struct Proc_PrepSkillSubList*) 
		Proc_StartBlocking(gProc_PrepSkillPickSkillList, proc);
	
	child->unit = GetPrepScreenUnitListEntry(proc->list_num_cur);
}