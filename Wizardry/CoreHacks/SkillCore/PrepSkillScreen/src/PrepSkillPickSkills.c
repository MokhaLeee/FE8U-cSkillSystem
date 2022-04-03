#include "gbafe-chax.h"
#include "PrepSkill.h"


enum{
	// Proc: Proc_PrepSkillSubList's label
	LABEL_PREPSLILLSLIST_INIT = 0,
	LABEL_PREPSLILLSLIST_IDLE,
	LABEL_PREPSLILLSLIST_REMOVE,
	LABEL_PREPSLILLSLIST_POST_REMOVE,
	LABEL_PREPSLILLSLIST_ADD,
	LABEL_PREPSLILLSLIST_POST_ADD,
	LABEL_PREPSLILLSLIST_STATSCREEN,
	LABEL_PREPSLILLSLIST_END,
	

	
	// state for Proc_PrepSkillSubList + 0x29
	STATE_PREPSUB_NORMAL,
	STATE_PREPSUB_REPLACE_INRIGHT,
	STATE_PREPSUB_REPLACE_INLEFT,
};


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

// For StatScreen
extern void sub_809B4C0(ProcPtr);
extern void sub_809B014(ProcPtr);



// ========================================
// ======= Static Func Definitions ========
// ========================================
static void PrepPickSkillList_InitTexts();
static void PrepPickSkillList_DrawWindowGfx(void);
static void PrepPickSkillList_DrawRightBarTexts(struct Unit*, int config);
static void PrepPickSkillList_DrawTotalSkill(struct Unit*);
static void PrepPickSkillList_UpdateSkillDesc(struct Proc_PrepSkillSubList* proc);

static void PrepPickSkill_OnEnd(struct Proc_PrepSkillSubList* proc);
static void PrepPickSkill_InitSkillsList (struct Proc_PrepSkillSubList* proc);
static void PrepPickSkill_InitScreen (struct Proc_PrepSkillSubList* proc);
static void PrepPickSkill_MainLoop(struct Proc_PrepSkillSubList* proc);

static void PrepPickSkillList_StartStatScreen(struct Proc_PrepSkillSubList* proc);
static void PrepPickSkillList_PostStatScreen(struct Proc_PrepSkillSubList* proc);





// ========================================
// ================= Core =================
// ========================================

const static struct ProcCmd gProc_PrepSkillPickSkillList[] = {
	
	PROC_NAME	("PREP_SKILLSCREEN_PICKSKILLS"),
	PROC_SET_END_CB (PrepPickSkill_OnEnd),

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
	

// Stat Screen
PROC_LABEL (LABEL_PREPSLILLSLIST_STATSCREEN),
	PROC_CALL	(EndProc_PrepSkillObj),
	PROC_CALL	(sub_809B4C0),
	PROC_SLEEP	(2),
	PROC_CALL	(sub_809B014),
	PROC_CALL	(PrepPickSkillList_StartStatScreen), // Here Start StatScreen
	PROC_YIELD,
	PROC_CALL	(PrepPickSkillList_PostStatScreen),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),
	

// End
PROC_LABEL (LABEL_PREPSLILLSLIST_END),
	PROC_CALL	(DeleteEach6CDifferedLoop),
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),
	PROC_END,
};


void PrepPickSkill_OnEnd(struct Proc_PrepSkillSubList* proc){
	
	static void (*SetPrepScreenUnitListCharID)(int index) = (const void*) 0x80953C1;
	
	SetPrepScreenUnitListCharID(proc->unit->pCharacterData->number);
	
}




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
	
	gLCDControlBuffer.bg0cnt.priority = 0b00;
	gLCDControlBuffer.bg1cnt.priority = 0b10;
	gLCDControlBuffer.bg2cnt.priority = 0b01;
	gLCDControlBuffer.bg3cnt.priority = 0b11;
	
	BG_SetPosition( 0, 0, 0);
	BG_SetPosition( 1, 0, 0);
	BG_SetPosition( 2, 0, 0);
	BG_SetPosition( 3, 0, 0);
	
	EndGreenTextColorManager();
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
	
	// Skill Obj misc
	StartProc_PrepSkillObj(proc);
	
	// BG Scroll
	PrepStartScroll(proc, 0xE0, 0x20, 0x200, 2);
	
	// Draw Text Icons
	PrepUnit_DrawLeftUnitName(proc->unit);
	PrepSkill_DrawLeftSkillsIcon(proc->unit, ON_DRAW_CONFIG_INIT);
	PrepPickSkillList_DrawRightBarTexts(proc->unit, ON_DRAW_CONFIG_INIT);
	PrepPickSkillList_DrawTotalSkill(proc->unit);
	
	// Parallel to update skill-desc
	StartParallerWorkerWithParam(PrepPickSkillList_UpdateSkillDesc, 0, proc);

	LoadDialogueBoxGfx(BG_SCREEN_ADDR(0x29), 5);
	RestartScreenMenuScrollingBg();
}





void PrepPickSkill_MainLoop(struct Proc_PrepSkillSubList* proc){
	
	struct PrepSkillsList* list;
	int xHand, yHand;
	
	list = GetUnitPrepSkillsList(proc->unit);
	
	// Handle normal button
	
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_END);
		return;
		
	} // B_BUTTON
	
	if( R_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_STATSCREEN);
		return;
		
	} // R_BUTTON
	
	

	
	
	// W.I,P.
	// DPAD
	switch (gKeyStatusPtr->repeatedKeys)
	{
		case DPAD_LEFT:
			if( 0 != proc->list_index )
				proc->list_index--;
			else if( PREP_SKLSUB_RIGHT == proc->list_type )
				proc->list_type = PREP_SKLSUB_LEFT_RAM;
			break;
		
		case DPAD_RIGHT:
			if( proc->list_index < (list->total[proc->list_type]-1) )
				proc->list_index++;
			else if( PREP_SKLSUB_RIGHT != proc->list_type )
			{
				proc->list_type = PREP_SKLSUB_RIGHT;
				proc->list_index = 0;
			}
			break;
		
		case DPAD_UP:
			switch( proc->list_type )
			{
				case PREP_SKLSUB_RIGHT:
					if( proc->list_index >= 6 )
						proc->list_index -= 6;
					break;
				
				case PREP_SKLSUB_LEFT_RAM:
					proc->list_type = PREP_SKLSUB_RIGHT;
					proc->list_index = 0;
					break;
				
				case PREP_SKLSUB_LEFT_ROM:
					proc->list_type = PREP_SKLSUB_LEFT_RAM;
					proc->list_index = 0;
					break;
					
				default:
					break;	
			}
			break;
		
		case DPAD_DOWN:
			switch( proc->list_type )
			{
				case PREP_SKLSUB_RIGHT:
					if( (proc->list_index+6) < list->total[proc->list_type] )
						proc->list_index += 6;
					else
					{
						proc->list_type = PREP_SKLSUB_LEFT_RAM;
						proc->list_index = 0;
					}	
					break;
				
				case PREP_SKLSUB_LEFT_RAM:
					proc->list_type = PREP_SKLSUB_LEFT_ROM;
					proc->list_index = 0;
					break;
				
				case PREP_SKLSUB_LEFT_ROM:
					break;
				
				default:
					break;
					
			}
			break;
		
		default:
			break;
	}
	// DPAD End
	
	
	if( 
		(proc->list_type_pre == proc->list_type) && 
		(proc->list_index_pre == proc->list_index) )
		goto goto_fail;
	
	// W.I.P.
	proc->list_type_pre = proc->list_type;
	proc->list_index_pre = proc->list_index;
	
	// Parallel to update skill-desc
	StartParallerWorkerWithParam(PrepPickSkillList_UpdateSkillDesc, 0, proc);
	
	// M4a
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x65);
	
	
	// Draw Hand
	switch ( proc->list_type )
	{
		
		case PREP_SKLSUB_LEFT_RAM:
			xHand = 0x10 + 0x10 * proc->list_index;
			yHand = 0x38;
			break;
		
		case PREP_SKLSUB_LEFT_ROM:
			xHand = 0x10 + 0x10 * _lib_mod(proc->list_index, 5);
			yHand = 0x58 + 0x10 * _lib_div(proc->list_index, 5);
			break;
			
			
		case PREP_SKLSUB_RIGHT:
		default:
			xHand = 0x78 + 0x10 * _lib_mod(proc->list_index, 6);
			yHand = 0x28 + 0x10 * _lib_div(proc->list_index, 6);
			break;
	}
	
	PrepDrawHand( xHand, yHand, 0, 0x800);
	
goto_fail:
	return;
}

 



// Stat Screen

void PrepPickSkillList_StartStatScreen(struct Proc_PrepSkillSubList* proc){
	
	// refer to 809B504
	
	SetStatScreenConfig(0x11);
	
	StartStatScreen(proc->unit, (ProcPtr)proc);
	
}

void PrepPickSkillList_PostStatScreen(struct Proc_PrepSkillSubList* proc){
	
	// refer to 809B520
	
	static int (*GetNewPrepUnitListIndexAfterStatScreen)() = (const void*) 0x8095675;
	
	InitPrepScreenUnitList();
	proc->unit = GetPrepScreenUnitListEntry( GetNewPrepUnitListIndexAfterStatScreen() );
	
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
	Text_Init(&gStatScreen.text[6], 0x11); 
	Text_Init(&gStatScreen.text[7], 0x11);
	Text_Init(&gStatScreen.text[8], 0x11);
	
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
			TILEMAP_LOCATED( gBG2TilemapBuffer, 0xF, 0x5),
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
				TILEMAP_LOCATED( gBG2TilemapBuffer, xPos, yPos),
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
		return;
	
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
		
		
		
		// w.i.p. for chinese
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