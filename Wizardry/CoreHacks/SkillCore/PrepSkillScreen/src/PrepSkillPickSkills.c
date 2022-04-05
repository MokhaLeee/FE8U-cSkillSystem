#include "gbafe-chax.h"
#include "PrepSkill.h"


enum{
	// Proc: Proc_PrepPickSkill's label
	LABEL_PREPSLILLSLIST_INIT = 0,
	LABEL_PREPSLILLSLIST_IDLE,
	LABEL_PREPSLILLSLIST_FAIL_REMOVE,
	LABEL_PREPSLILLSLIST_REMOVE,
	LABEL_PREPSLILLSLIST_ADD,
	LABEL_PREPSLILLSLIST_REPLACE,
	LABEL_PREPSLILLSLIST_POST_REPLACE,
	LABEL_PREPSLILLSLIST_POST_CANCEL,
	LABEL_PREPSLILLSLIST_STATSCREEN,
	
	LABEL_PREPSLILLSLIST_END,
	

	
	// state for Proc_PrepPickSkill + 0x29
	STATE_PREPSUB_NORMAL,
	STATE_PREPSUB_REPLACE_INRIGHT,
	STATE_PREPSUB_REPLACE_INLEFT,
};


extern u16 msgAt_PrepPickSkill_FailAddSkill;
extern u16 msgAt_PrepPickSkill_TryRemoveSkill;
extern u16 msgAt_PrepPickSkill_TryAddSkill;
extern u16 msgAt_PrepPickSkill_TryReplaceSkill;

// ========================================
// ======= There will added in cLib =======
// ========================================
static void (*PrepUnit_DrawLeftUnitName)(struct Unit*) = (const void*) 0x809A931;
extern void NewFadeIn(int step);
extern int FadeInExists();

// OAM Misc
static void (*PrepDrawHand)(int x, int y, int, int) = (const void*) 0x80AD51D;
extern void HidePrepScreenHandCursor();
extern void ResetPrepScreenHandCursor(ProcPtr);
static void (*PrepScreen_DrawHandGfxMaybe)(int, int) = (const void*) 0x80AD4A1;
static void (*PutObjWindow)(int x, int y, int length, int height, int oam2) = (const void*) 0x809A31D;

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
static void PrepPickSkill_InitTexts();
static void PrepPickSkill_DrawWindowGfx(void);
static void PrepPickSkill_DrawRightBarTexts(struct Unit*, int config);
static void PrepPickSkill_DrawTotalSkill(struct Unit*);
static void PrepPickSkill_UpdateSkillDesc(struct Proc_PrepPickSkill* proc);

static void PrepPickSkill_OnEnd(struct Proc_PrepPickSkill* proc);
static void PrepPickSkill_InitSkillsList (struct Proc_PrepPickSkill* proc);
static void PrepPickSkill_InitScreen (struct Proc_PrepPickSkill* proc);
static void PrepPickSkill_MainLoop(struct Proc_PrepPickSkill* proc);

static void PrepPickSkill_StartStatScreen(struct Proc_PrepPickSkill* proc);
static void PrepPickSkill_PostStatScreen(struct Proc_PrepPickSkill* proc);
static void PrepPickSkill_FailAddSkillPre(struct Proc_PrepPickSkill* proc);
static void PrepPickSkill_FailAddSkillIdle(struct Proc_PrepPickSkill* proc);
static void PrepPickSkil_PrepareRemoveSkillWindow(struct Proc_PrepPickSkill* proc);
static void PrepPickSkil_TryRemoveSkillIdle(struct Proc_PrepPickSkill* proc);
static void PrepPickSkil_PrepareAddSkillWindow(struct Proc_PrepPickSkill* proc);
static void PrepPickSkil_TryAddSkillIdle(struct Proc_PrepPickSkill* proc);
static void PrepPickSkil_PickReplacedSkillIdle(struct Proc_PrepPickSkill* proc);
static void PrepPickSkil_PrepareReplaceSkillWindow(struct Proc_PrepPickSkill* proc);
static void PrepPickSkil_ConfirmReplaceSkillIdle(struct Proc_PrepPickSkill* proc);
static void PrepPickSkil_CancelOnSkill(struct Proc_PrepPickSkill* proc);

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
	PROC_CALL_ARG (NewFadeIn, 0x4),
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
	PROC_CALL	(PrepPickSkill_StartStatScreen), // Here Start StatScreen
	PROC_YIELD,
	PROC_CALL	(PrepPickSkill_PostStatScreen),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),
	

// When pick rom skill in right list
PROC_LABEL (LABEL_PREPSLILLSLIST_FAIL_REMOVE),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkill_FailAddSkillPre),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkill_FailAddSkillIdle),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_POST_CANCEL),


// When pick rom-equipped skill
PROC_LABEL (LABEL_PREPSLILLSLIST_REMOVE),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkil_PrepareRemoveSkillWindow),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkil_TryRemoveSkillIdle),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),


// When try to add skills
PROC_LABEL (LABEL_PREPSLILLSLIST_ADD),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkil_PrepareAddSkillWindow),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkil_TryAddSkillIdle),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),


// When try to replace skills
PROC_LABEL (LABEL_PREPSLILLSLIST_REPLACE),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkil_PickReplacedSkillIdle),

// After pick replacing skill
PROC_LABEL (LABEL_PREPSLILLSLIST_POST_REPLACE),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkil_PrepareReplaceSkillWindow),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkil_ConfirmReplaceSkillIdle),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),

// When fail or cancel to add & remove skill 
PROC_LABEL (LABEL_PREPSLILLSLIST_POST_CANCEL),
	PROC_CALL	(PrepPickSkil_CancelOnSkill),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_IDLE),

// End
PROC_LABEL (LABEL_PREPSLILLSLIST_END),
	PROC_CALL	(DeleteEach6CDifferedLoop),
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),
	PROC_END,
};


void PrepPickSkill_OnEnd(struct Proc_PrepPickSkill* proc){
	
	static void (*SetPrepScreenUnitListCharID)(int index) = (const void*) 0x80953C1;
	
	SetPrepScreenUnitListCharID(proc->unit->pCharacterData->number);
	
}




void PrepPickSkill_InitSkillsList (struct Proc_PrepPickSkill* proc){
	
	// Commom space
	InitPrepSkillsList();
	ResetSkillFastList();
	
	GetOrMakeSklFastList(proc->unit);
	MakeUnitPrepSkillsList(proc->unit);
	
	proc->state = STATE_PREPSUB_NORMAL;
	proc->list_type = PREP_SKLSUB_RIGHT;
	proc->list_type_pre = PREP_SKLSUB_RIGHT;
	
	proc->list_index = 0;
	proc->list_index_pre = 0;
	proc->skill_id_pre = 0; // update on desc
}




void PrepPickSkill_InitScreen (struct Proc_PrepPickSkill* proc){
	
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
	PrepPickSkill_InitTexts();
	PrepPickSkill_DrawWindowGfx();
	
	
	BG_EnableSyncByMask(0b1111);
	SetDefaultColorEffects();
	
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
	PrepPickSkill_DrawRightBarTexts(proc->unit, ON_DRAW_CONFIG_INIT);
	PrepPickSkill_DrawTotalSkill(proc->unit);
	
	// Parallel to update skill-desc
	StartParallerWorkerWithParam(PrepPickSkill_UpdateSkillDesc, 0, proc);

	LoadDialogueBoxGfx(BG_SCREEN_ADDR(0x29), 5);
	RestartScreenMenuScrollingBg();
}





void PrepPickSkill_MainLoop(struct Proc_PrepPickSkill* proc){
	
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
	
	else if( R_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_STATSCREEN);
		return;
		
	} // R_BUTTON
	
	else if( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( IsPrepSkillRom(proc->unit, proc->skill_id_pre) )
		{
			// try pick rom skill
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_FAIL_REMOVE);
			
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6C);
			return;
		}
		
		else if ( isPrepSkillEquippedRAM(proc->unit, proc->skill_id_pre) )
		{
			// Remove ram skill
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_REMOVE);
			
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6A);
			return;
		}
		else if ( (PREP_SKLSUB_RIGHT == proc->list_type) )
		{
			if( GetUnitRamSkillCount(proc->unit) < UNIT_SKILL_COUNT )
			{
				// Add ram skill
				Proc_Goto(proc, LABEL_PREPSLILLSLIST_ADD);
				
				if( 0 == gRAMChapterData.unk41_8)
					m4aSongNumStart(0x6A);
				return;
			}
			else
			{
				// replace ram skill
				// for now preserve list-index
				proc->list_index_replace = proc->list_index;
				proc->list_index = 0;
				proc->list_type = PREP_SKLSUB_LEFT_RAM;
				
				if( 0 == gRAMChapterData.unk41_8)
					m4aSongNumStart(0x6A);
				
				StartParallerWorkerWithParam(PrepPickSkill_UpdateSkillDesc, 0, proc);
				PrepDrawHand( 0x10 + 0x10 * proc->list_index, 0x38, 0, 0x800);
				Proc_Goto(proc, LABEL_PREPSLILLSLIST_REPLACE);
				return;
			}
		}

		
	} // A_BUTTON

	
	
	// W.I,P.
	// DPAD
	switch (gKeyStatusPtr->repeatedKeys)
	{
		case DPAD_LEFT:
			if( PREP_SKLSUB_RIGHT == proc->list_type )
			{
				if( _lib_mod(proc->list_index, 6) == 0 )
				{
					if( _lib_div(proc->list_index, 6) < 2 )
						proc->list_type = PREP_SKLSUB_LEFT_RAM;

					else
						proc->list_type = PREP_SKLSUB_LEFT_ROM;
					
					proc->list_index = 0;
				}
				else
				{
					if( 0 != proc->list_index )
						proc->list_index--;
				}
			}
			else if( 0 != proc->list_index )
				proc->list_index--;
			
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
					if( (proc->list_index+6) < list->total[PREP_SKLSUB_RIGHT] )
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
					if( (proc->list_index+5) < list->total[PREP_SKLSUB_LEFT_ROM] )
						proc->list_index += 5;
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
	
	// m4a
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x65);
	
	// W.I.P.
	proc->list_type_pre = proc->list_type;
	proc->list_index_pre = proc->list_index;
	
	// Parallel to update skill-desc
	// StartParallerWorkerWithParam(PrepPickSkill_UpdateSkillDesc, 0, proc);
	PrepPickSkill_UpdateSkillDesc(proc);
	
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

void PrepPickSkill_StartStatScreen(struct Proc_PrepPickSkill* proc){
	
	// refer to 809B504
	
	SetStatScreenConfig(0x11);
	
	StartStatScreen(proc->unit, (ProcPtr)proc);
	
}

void PrepPickSkill_PostStatScreen(struct Proc_PrepPickSkill* proc){
	
	// refer to 809B520
	
	static int (*GetNewPrepUnitListIndexAfterStatScreen)() = (const void*) 0x8095675;
	
	InitPrepScreenUnitList();
	proc->unit = GetPrepScreenUnitListEntry( GetNewPrepUnitListIndexAfterStatScreen() );
	
}







// when try remove a rom skill

void PrepPickSkill_FailAddSkillPre(struct Proc_PrepPickSkill* proc){
	
	char* str;
	
	str = GetStringFromIndex( msgAt_PrepPickSkill_FailAddSkill );
	

	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0xD, 0x6),
		0x5, 0x1 , 0 );
	
	
	for( int line = 0; line < 2; line++ )
	{
		
		Text_Clear(&gStatScreen.text[0xB + line]);
		
		DrawTextInline(
			&gStatScreen.text[0xB + line],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xD, 0x6 + 2 * line),
			TEXT_COLOR_NORMAL, 0, 0,
			str );
		

		
		// w.i.p. for chinese
		while( 1 != *str++ ) // '\n'
			if( 0 == *str )
				goto goto_return;
	
	}

	
	
goto_return:
	HidePrepScreenHandCursor();
	BG_EnableSyncByMask(0b01);
}

void PrepPickSkill_FailAddSkillIdle(struct Proc_PrepPickSkill* proc){
	
	enum{
		// Window
		OBJWINDOW0_XPOS = 0x60,
		OBJWINDOW0_YPOS = 0x2E,
		OBJWINDOW0_LENGTH = 0x11,
		OBJWINDOW0_HEIGHT = 4,
		
	};
	
	if( (A_BUTTON | B_BUTTON) & gKeyStatusPtr->newKeys )
	{
		Proc_Break(proc);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		return;
	} // A_BUTTON
	
	// Obj Window
	PutObjWindow(
		OBJWINDOW0_XPOS,
		OBJWINDOW0_YPOS,
		OBJWINDOW0_LENGTH,
		OBJWINDOW0_HEIGHT,
		OAM2_PAL(OBJWINDOW_PAL) +
			OAM2_LAYER(0b01) +
			OAM2_CHR(OBJWINDOW_VOBJ / 0x20) );
	
	
}





// On remove skill

void PrepPickSkil_PrepareRemoveSkillWindow(struct Proc_PrepPickSkill* proc){
	
	char* str;
	
	str = GetStringFromIndex( msgAt_PrepPickSkill_TryRemoveSkill );
	
	
	for( int line = 0; line < 2; line++ )
	{
		
		Text_Clear(&gStatScreen.text[0xB + line]);
		
		DrawTextInline(
			&gStatScreen.text[0xB + line],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xD, 0x6 + 2 * line),
			TEXT_COLOR_NORMAL, 0, 0,
			str );
		

		
		// w.i.p. for chinese
		while( 1 != *str++ ) // '\n'
			if( 0 == *str )
				goto goto_return;
	
	}
	
	
	
	
goto_return:
	proc->yeah = 1;
	// HidePrepScreenHandCursor();
	BG_EnableSyncByMask(0b01);
	
	// Icon
	DrawIcon(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x0F, 0x6 ),
		SKILL_ICON(proc->skill_id_pre), 
		TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
}



void PrepPickSkil_TryRemoveSkillIdle(struct Proc_PrepPickSkill* proc){
	
	enum{
		// Window
		OBJWINDOW0_XPOS = 0x73,
		OBJWINDOW0_YPOS = 0x29,
		OBJWINDOW0_LENGTH = 0xB,
		OBJWINDOW0_HEIGHT = 5,
		
		// Hand
		OBJHAND_XPOS_Y = 0x7C,
		OBJHAND_XPOS_N = 0xA0,
		OBJHAND_YPOS = 0x40,
	};
	
	
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_POST_CANCEL);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		return;
	} // B_BUTTON
	
	else if ( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( (proc->yeah & 1) == 0 )
		{
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_POST_CANCEL);
			
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6A);
			return;
		}
		else
		{
			RemoveSkill(proc->unit, proc->skill_id_pre);
			
			TileMap_FillRect(
				TILEMAP_LOCATED( gBG0TilemapBuffer, 0x0F, 0x06),
				0x2, 0x2 , 0 );
			BG_EnableSyncByMask(0b01);
			
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_INIT);
			
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6A);
			
			return;
		}
	
	} // A_BUTTON
	
	// DPAD
	if( (DPAD_LEFT ==  gKeyStatusPtr->repeatedKeys) || (DPAD_RIGHT == gKeyStatusPtr->repeatedKeys) )
	{
		proc->yeah = 1 & (~proc->yeah);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x65);
	}
	
	// Obj Window
	PutObjWindow(
		OBJWINDOW0_XPOS,
		OBJWINDOW0_YPOS,
		OBJWINDOW0_LENGTH,
		OBJWINDOW0_HEIGHT,
		OAM2_PAL(OBJWINDOW_PAL) +
			OAM2_LAYER(0b01) +
			OAM2_CHR(OBJWINDOW_VOBJ / 0x20) );
	
	// Hand
	PrepDrawHand( 
		1 & proc->yeah
			? OBJHAND_XPOS_Y
			: OBJHAND_XPOS_N,
		OBJHAND_YPOS, 0, 0x800);
}





// On Add skill
void PrepPickSkil_PrepareAddSkillWindow(struct Proc_PrepPickSkill* proc){
	
	char* str;
	
	str = GetStringFromIndex( msgAt_PrepPickSkill_TryAddSkill );
	
	
	for( int line = 0; line < 2; line++ )
	{
		
		Text_Clear(&gStatScreen.text[0xB + line]);
		
		DrawTextInline(
			&gStatScreen.text[0xB + line],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xD, 0x6 + 2 * line),
			TEXT_COLOR_NORMAL, 0, 0,
			str );
		

		
		// w.i.p. for chinese
		while( 1 != *str++ ) // '\n'
			if( 0 == *str )
				goto goto_return;
	
	}
	
	
	
	
goto_return:
	proc->yeah = 1;
	// HidePrepScreenHandCursor();
	BG_EnableSyncByMask(0b01);
	
	// Icon
	DrawIcon(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x0F, 0x6 ),
		SKILL_ICON(proc->skill_id_pre), 
		TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
}

void PrepPickSkil_TryAddSkillIdle(struct Proc_PrepPickSkill* proc){
	
	enum{
		// Window
		OBJWINDOW0_XPOS = 0x73,
		OBJWINDOW0_YPOS = 0x29,
		OBJWINDOW0_LENGTH = 0x9,
		OBJWINDOW0_HEIGHT = 5,
		
		// Hand
		OBJHAND_XPOS_Y = 0x7C,
		OBJHAND_XPOS_N = 0xA0,
		OBJHAND_YPOS = 0x40,
	};
	
	
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_POST_CANCEL);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		return;
	} // B_BUTTON
	
	else if ( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( (proc->yeah & 1) == 0 )
		{
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_POST_CANCEL);
			
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6B);
			return;
		}
		else
		{
			AddSkill(proc->unit, proc->skill_id_pre);
			
			TileMap_FillRect(
				TILEMAP_LOCATED( gBG0TilemapBuffer, 0x0F, 0x06),
				0x2, 0x2 , 0 );
			BG_EnableSyncByMask(0b01);
			
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6A);
			
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_INIT);
			return;
		}
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6A);
	
	} // A_BUTTON
	
	// DPAD
	if( (DPAD_LEFT ==  gKeyStatusPtr->repeatedKeys) || (DPAD_RIGHT == gKeyStatusPtr->repeatedKeys) )
	{
		proc->yeah = 1 & (~proc->yeah);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x65);
	}
	
	// Obj Window
	PutObjWindow(
		OBJWINDOW0_XPOS,
		OBJWINDOW0_YPOS,
		OBJWINDOW0_LENGTH,
		OBJWINDOW0_HEIGHT,
		OAM2_PAL(OBJWINDOW_PAL) +
			OAM2_LAYER(0b01) +
			OAM2_CHR(OBJWINDOW_VOBJ / 0x20) );
	
	// Hand
	PrepDrawHand( 
		1 & proc->yeah
			? OBJHAND_XPOS_Y
			: OBJHAND_XPOS_N,
		OBJHAND_YPOS, 0, 0x800);
}





// choose replace skill idle
void PrepPickSkil_PickReplacedSkillIdle(struct Proc_PrepPickSkill* proc){
	
	struct PrepSkillsList* list;
	
	list = GetUnitPrepSkillsList(proc->unit);
	
	// Cursor
	DisplayCursor(
		0x78 + gGameState.camera.x + 0x10 * _lib_mod(proc->list_index_replace, 6),
		0x29 + gGameState.camera.y + 0x10 * _lib_div(proc->list_index_replace, 6),
		1);
	
	// Handle normal button
	
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_INIT);
		return;
		
	} // B_BUTTON
	
	
	if( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_POST_REPLACE);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6A);
	} // A_BUTTON
	
	
	// DPAD
	switch (gKeyStatusPtr->repeatedKeys)
	{
		case DPAD_LEFT:
			if( 0 != proc->list_index )
				proc->list_index--;

			break;
		
		case DPAD_RIGHT:
			if( proc->list_index < (list->total[proc->list_type]-1) )
				proc->list_index++;
			
			break;
		
		default:
			break;
		
	} // switch
	
	
	if( proc->list_index_pre == proc->list_index )
		goto goto_fail;

	
	proc->list_type_pre = proc->list_type;
	proc->list_index_pre = proc->list_index;
	
	// update skill-desc
	PrepPickSkill_UpdateSkillDesc(proc);
	
	// M4a
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x65);
	
	// Draw Hand
	PrepDrawHand( 0x10 + 0x10 * proc->list_index, 0x38, 0, 0x800);
	
goto_fail:	
	return;
}


void PrepPickSkil_PrepareReplaceSkillWindow(struct Proc_PrepPickSkill* proc){
	
	char* str;
	
	str = GetStringFromIndex( msgAt_PrepPickSkill_TryReplaceSkill );
	
	
	for( int line = 0; line < 2; line++ )
	{
		
		Text_Clear(&gStatScreen.text[0xB + line]);
		
		DrawTextInline(
			&gStatScreen.text[0xB + line],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xD, 0x6 + 2 * line),
			TEXT_COLOR_NORMAL, 0, 0,
			str );
		

		
		// w.i.p. for chinese
		while( 1 != *str++ ) // '\n'
			if( 0 == *str )
				goto goto_return;
	
	}
	
	
	
	
goto_return:
	proc->yeah = 1;
	// HidePrepScreenHandCursor();
	BG_EnableSyncByMask(0b01);
	
	// Icon
	DrawIcon(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x0F, 0x6 ),
		SKILL_ICON(GetUnitPrepSkillsList(proc->unit)->skills_all[proc->list_index_replace]), 
		TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
}


void PrepPickSkil_ConfirmReplaceSkillIdle(struct Proc_PrepPickSkill* proc){
	
	enum{
		// Window
		OBJWINDOW0_XPOS = 0x73,
		OBJWINDOW0_YPOS = 0x29,
		OBJWINDOW0_LENGTH = 0xB,
		OBJWINDOW0_HEIGHT = 5,
		
		// Hand
		OBJHAND_XPOS_Y = 0x7C,
		OBJHAND_XPOS_N = 0xA0,
		OBJHAND_YPOS = 0x40,
	};

	
	// Cursor
	DisplayCursor(
		0x10 + gGameState.camera.x + 0x10 + 0x10 * proc->list_index,
		0x3A + gGameState.camera.y,
		2);
	
	
	
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_POST_CANCEL);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		return;
	} // B_BUTTON
	
	else if ( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( (proc->yeah & 1) == 0 )
		{
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_POST_CANCEL);
			
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6B);
			return;
		}
		else
		{
			RemoveSkill(proc->unit, proc->skill_id_pre);
			AddSkill( proc->unit, GetUnitPrepSkillsList(proc->unit)->skills_all[proc->list_index_replace]);
			
			TileMap_FillRect(
				TILEMAP_LOCATED( gBG0TilemapBuffer, 0x0F, 0x06),
				0x2, 0x2 , 0 );
			BG_EnableSyncByMask(0b01);
			
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6A);
			
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_INIT);
			return;
		}
	
	} // A_BUTTON
	
	// DPAD
	if( (DPAD_LEFT ==  gKeyStatusPtr->repeatedKeys) || (DPAD_RIGHT == gKeyStatusPtr->repeatedKeys) )
	{
		proc->yeah = 1 & (~proc->yeah);
		
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x65);
	}
	
	// Obj Window
	PutObjWindow(
		OBJWINDOW0_XPOS,
		OBJWINDOW0_YPOS,
		OBJWINDOW0_LENGTH,
		OBJWINDOW0_HEIGHT,
		OAM2_PAL(OBJWINDOW_PAL) +
			OAM2_LAYER(0b01) +
			OAM2_CHR(OBJWINDOW_VOBJ / 0x20) );
	
	// Hand
	PrepDrawHand( 
		1 & proc->yeah
			? OBJHAND_XPOS_Y
			: OBJHAND_XPOS_N,
		OBJHAND_YPOS, 0, 0x800);
	
	return;
}







// Common cancel
void PrepPickSkil_CancelOnSkill(struct Proc_PrepPickSkill* proc){
	
	int xHand, yHand;
	
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
	
	// remove text
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0xD, 0x6),
		0x10, 0x5 , 0 );
		
	BG_EnableSyncByMask(0b01);
	
	return;
}





// =======================================================
// ====================== On Draw ========================
// =======================================================

void PrepPickSkill_DrawWindowGfx(void){
	
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


void PrepPickSkill_InitTexts(){
	
	Font_InitForUIDefault();
	
	Text_Init(&gPrepUnitTexts[0xE], 9); 	// "Equippable Skills"
	Text_Init(&gPrepUnitTexts[0xF], 10);	// "Class & Unit Skills"
	Text_Init(&gPrepUnitTexts[0x10], 8);	// "Combat Arts"
	// Text_Init(&gPrepUnitTexts[0x11], 6);	// "Battalion"
	Text_Init(&gPrepUnitTexts[0x12], 3);	// "none" for left RAM skills
	Text_Init(&gStatScreen.text[0x2], 3); 	// "none" for left ROM skills
	Text_Init(&gStatScreen.text[0x3], 3); 	// "none" for left CombatArts
	
	// Two for right-upper bar
	Text_Init(&gStatScreen.text[0x0], 3); 	// "pick"
	Text_Init(&gStatScreen.text[0x1], 6); 	// "total skill"
	
	// Two for Right skill list
	Text_Init(&gStatScreen.text[0x4], 4); 	// "Skills"
	Text_Init(&gStatScreen.text[0x5], 3); 	// "none"
	
	// For Obj-window text
	Text_Init(&gStatScreen.text[0xB], 0x12);
	Text_Init(&gStatScreen.text[0xC], 0x12);
	Text_Init(&gStatScreen.text[0xD], 0x12);
	
	// For Unit Name
	Text_Init(&gPrepUnitTexts[0x13], 7);
	Text_Init(&gPrepUnitTexts[0x14], 10);
	Text_Init(&gPrepUnitTexts[0x15], 15);
	
	// For skill desc
	Text_Init(&gStatScreen.text[0x6], 0x11); 
	Text_Init(&gStatScreen.text[0x7], 0x11);
	Text_Init(&gStatScreen.text[0x8], 0x11);
	
	
}


void PrepPickSkill_DrawRightBarTexts(struct Unit* unit, int config){
	
	// config: 0->init, 1->update
	
	struct PrepSkillsList* list = GetUnitPrepSkillsList(unit);
	
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
		0 == (5 - list->total[PREP_SKLSUB_LEFT_RAM])
			? TEXT_COLOR_GRAY
			: TEXT_COLOR_BLUE,
		5 - list->total[PREP_SKLSUB_LEFT_RAM] );
	
	DrawDecNumber(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1B, 0x1),
		(5 == list->total[PREP_SKLSUB_LEFT_RAM])
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		list->total[PREP_SKLSUB_LEFT_RAM] );
		
	
	// On End
	BG_EnableSyncByMask(0b01);
	
}


void PrepPickSkill_DrawTotalSkill(struct Unit* unit){
	
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

void PrepPickSkill_UpdateSkillDesc(struct Proc_PrepPickSkill* proc){
	
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
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, xStart, yStart),
		0x10, 0x6 , 0 );
	
	proc->skill_id_pre = skill_id;
	
	str = GetStringFromIndex(GetSkillDescMsg(skill_id));
	
	if( (0 == *str) || (0 == str) )
		goto goto_end;
	
	
	
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
				goto goto_end;
	
	}
	
goto_end:
	BG_EnableSyncByMask(0b01);
}







// =======================================================
// ====================== GLOBAL =========================
// =======================================================

void PrepSkill_StartPickSkillScreen(struct Proc_PrepUnit* proc){
	struct Proc_PrepPickSkill* child;
	
	child = (struct Proc_PrepPickSkill*) 
		Proc_StartBlocking(gProc_PrepSkillPickSkillList, proc);
	
	child->unit = GetPrepScreenUnitListEntry(proc->list_num_cur);
}
