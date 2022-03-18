#include "prep-screen.h"

extern void EndBG3Slider_();
extern void Get6CDifferedLoop6C(void* func, ProcPtr);
extern struct Unit* sub_8095394(); // maybe get leader?
extern int sub_80958FC(struct Unit*); // Get index in Prep-Unit-List
static void (*SetPrepScreenUnitListCharID)(int index) = (const void*) 0x80953C1;

// OAM Misc
static void (*PrepDrawHand)(int x, int y, int, int) = (const void*) 0x80AD51D;
extern void ResetPrepScreenHandCursor(ProcPtr);
static void (*PrepScreen_DrawHandGfxMaybe)(int, int) = (const void*) 0x80AD4A1;
extern void sub_80AD4E4(int); // also update hand


// BG Scroll
static void (*PrepStartScroll)(ProcPtr, int, int, int, int) = (const void*) 0x8097749;
extern void RestartScreenMenuScrollingBg();
static void (*PrepMenu_UpdateTsaScroll)(int) = (const void*) 0x809A645;
// static void (*HandleMenuScroll)(int,int,int,int) = (const void*) 0x80976CD;

// On Draw
static void (*PrepUnit_InitTexts)(void) = (const void*) 0x809A815;
static void (*PrepUnit_InitGfx)(void) = (const void*) 0x809A875;
static void (*PrepUnit_InitSMS)(struct Proc_PrepUnit*) = (const void*) 0x809A8F9;
static void (*PrepUnit_DrawLeftWindow)(struct Unit*) = (const void*) 0x809A9F9;
static void (*PrepUnit_DrawLeftText)(struct Unit*) = (const void*) 0x809A931;
static void (*PrepUnit_DrawTextInternal)(struct Proc_PrepUnit*, int) = (const void*) 0x809A581;
static void (*PrepUnit_DrawText_Pick_Left)(struct Proc_PrepUnit*,int) = (const void*) 0x809AAF1;


// 809B40C
void ProcPrepUnit_OnEnd(struct Proc_PrepUnit* proc){
	
	struct Proc_AtMenu* parent;
	
	parent = (struct Proc_AtMenu*)proc->proc_parent;
	
	parent->yDiff = proc->yDiff_cur;
	parent->cur_counter = proc->cur_counter;
	
	SetPrepScreenUnitListCharID(
		GetPrepScreenUnitListEntry(proc->list_num_cur)->pCharacterData->number);
	
	EndBG3Slider_();
}


// 809AE3C
void ProcPrepUnit_OnInit(struct Proc_PrepUnit* proc){
	
	struct Proc_AtMenu* parent;
	
	proc->list_num_cur = sub_80958FC( sub_8095394() );
	
	parent = (struct Proc_AtMenu*)proc->proc_parent;
	
	proc->max_counter = parent->max_counter;
	proc->cur_counter = parent->cur_counter;
	proc->yDiff_cur = parent->yDiff;
 	proc->list_num_pre = proc->list_num_cur;
	proc->unk_37 = 0;
}


// 809AE7C
void ProcPrepUnit_InitScreen(struct Proc_PrepUnit* proc){
	
	extern u16 gUnknown_08A181E8[];
	extern void sub_809ADC8(struct Proc_PrepUnit*);
	
	extern void sub_809A874();
	extern void sub_809A66C(struct Proc_PrepUnit*);
	extern void sub_80976CC(int, int, u16, int);
	extern void sub_80894E0();
	
	
	
	SetupBackgrounds(gUnknown_08A181E8);
	
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
	
	// <!> Init TextHandle
	PrepUnit_InitTexts();
	
	// <!> Init BG Gfx
	PrepUnit_InitGfx();
	
	BG_EnableSyncByMask(0b1111);
	SetDefaultColorEffects();
	
	// <!> Init SMS
	PrepUnit_InitSMS(proc);
	
	// <!> Also set SMS
	Get6CDifferedLoop6C(sub_809A66C, proc);
	
	ResetPrepScreenHandCursor(proc);
	PrepScreen_DrawHandGfxMaybe(0x600, 0x1);
	PrepDrawHand(
		(proc->list_num_cur % 2) * 56 + 0x70,
		(proc->list_num_cur / 2) * 16 - proc->yDiff_cur + 0x18,
		0x7, 0x800);
		
	PrepStartScroll(proc, 0xE0, 0x20, 0x200, 2);
	
	// Menu scroll bar (right var)
	sub_80976CC(0xA, proc->yDiff_cur,0,6);
	
	// OAM: [R]:info
	StartHelpPromptSprite(0x20, 0x8F, 9, (ProcPtr)proc);
	
	// Draw Texts
	PrepUnit_DrawLeftWindow( GetPrepScreenUnitListEntry(proc->list_num_cur) );
	PrepUnit_DrawLeftText( GetPrepScreenUnitListEntry(proc->list_num_cur) );
	
	for( int i = 0; i < 6; i++)
		PrepUnit_DrawTextInternal(proc, proc->yDiff_cur / 16 + i);
	
	PrepUnit_DrawText_Pick_Left(proc, 0);
	NewGreenTextColorManager((ProcPtr)proc);
	LoadDialogueBoxGfx(BG_SCREEN_ADDR(0x29), 5);
	RestartScreenMenuScrollingBg();
}


// 0x809B038
void ProcPrepUnit_Idle(struct Proc_PrepUnit* proc){
	
	extern int sub_809ACB4(struct Proc_PrepUnit* proc);
	extern void sub_809A9E8(struct Proc_PrepUnit*);
	extern void sub_80ACE20(void*, int, ProcPtr);
	extern int sub_809AD90(struct Proc_PrepUnit*);
	extern void sub_809AE10(struct Proc_PrepUnit*);
	
	const u16 key_pre = gKeyStatusPtr->repeatedKeys;
	
	if( proc->list_num_cur != proc->list_num_pre )
		goto goto_MenuScroll;
	
	proc->scroll_val = 4;
	
	// If L pressed, menu scrolls faster (well...)
	if( L_BUTTON & gKeyStatusPtr->heldKeys )
		proc->scroll_val = 8;
	
	
	if( START_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == proc->cur_counter ){
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6C);
			return;
		}
		else{
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6A);
			Proc_Goto(proc, 0x63);
			return;
		}
	} // START_BUTTON
	
	else if( SELECT_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6A);
		
		Proc_Goto(proc, 0x3);
		return;
	} // SELECT_BUTTON
	
	else if( R_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, 0x4);
		return;
	} // R_BUTTON
	
	else if( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == sub_809ACB4(proc) )
			return;
		
		PrepUnit_DrawText_Pick_Left(proc, 1);
		return;
	} // A_BUTTON
	
	else if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6B);
		
		Proc_Goto(proc, 0xA);
		return;
	} // B_BUTTON


	// DPAD
	if( DPAD_LEFT & key_pre )
		if( 1 & proc->list_num_cur )
			proc->list_num_cur--;
	
	if( DPAD_RIGHT & key_pre )
		if( 0 == (1 & proc->list_num_cur) )
			if( proc->list_num_cur < GetPrepScreenUnitListSize() )
				proc->list_num_cur++;
			
	if( DPAD_UP & key_pre )
		if( (proc->list_num_cur - 2) >= 0 )
			proc->list_num_cur -= 2;
	
	if( DPAD_DOWN & key_pre )
		if( (proc->list_num_cur + 2) < GetPrepScreenUnitListSize() )
			proc->list_num_cur += 2;
	
	if( proc->list_num_cur == proc->list_num_pre )
		return;
	
	PrepUnit_DrawLeftWindow(GetPrepScreenUnitListEntry(proc->list_num_pre));
	
	// Draw Left Text
	sub_80ACE20(sub_809A9E8, 1, proc);
	
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x65);
	
	// 
	if( 0 == sub_809AD90(proc) )
	{
		proc->list_num_pre = proc->list_num_cur;
		
		PrepDrawHand(
			(proc->list_num_pre % 2) * 56 + 0x70,
			(proc->list_num_cur / 2) * 16 - proc->yDiff_cur + 0x18,
			0x7, 0x800);
			
	}
	else
	{
		if( proc->list_num_cur < proc->list_num_pre )
			PrepUnit_DrawTextInternal(proc, proc->yDiff_cur / 16 - 1);
		
		if( proc->list_num_cur > proc->list_num_pre )
			PrepUnit_DrawTextInternal(proc, proc->yDiff_cur / 16 + 6);
		
		sub_80AD4E4( (proc->list_num_pre % 2) * 56 + 0x70 );
	}
	
	if( proc->list_num_pre == proc->list_num_cur )
		return;
	
	goto goto_MenuScroll;
	
	
	
goto_MenuScroll:
	if( proc->list_num_cur < proc->list_num_pre )
		proc->yDiff_cur -= proc->scroll_val;
	
	if( proc->list_num_cur > proc->list_num_pre )
		proc->yDiff_cur += proc->scroll_val;
	
	if( 0 == (proc->yDiff_cur & 0xF) )
	{
		PrepMenu_UpdateTsaScroll( proc->yDiff_cur / 16 - 1 );
		PrepMenu_UpdateTsaScroll( proc->yDiff_cur / 16 + 6 );
		sub_809AE10(proc);
		proc->list_num_pre = proc->list_num_cur;
	}
	
	BG_SetPosition(2,0, proc->yDiff_cur - 0x18);
	
	return;
}


// Label 63
// 809B438
void ProcPrepUnit_OnGameStart(struct Proc_PrepUnit* proc){
	
	struct Proc_AtMenu* parent;
	
	parent = proc->proc_parent;
	parent->end_prep = 1;
	
	// Here goto AtMenu's label !!
	Proc_Goto(parent, 0x6); // AtMenu label 6: end
	
	proc->unk_37 = 1;
}

