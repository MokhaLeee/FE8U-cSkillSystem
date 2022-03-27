#include "gbafe-chax.h"

extern void NewFadeIn(int step);
extern int FadeInExists();

// OAM Misc
static void (*PrepDrawHand)(int x, int y, int, int) = (const void*) 0x80AD51D;
extern void ResetPrepScreenHandCursor(ProcPtr);
static void (*PrepScreen_DrawHandGfxMaybe)(int, int) = (const void*) 0x80AD4A1;
extern void sub_80AD4E4(int); // also update hand

// BG Scroll
static void (*PrepStartScroll)(ProcPtr, int, int, int, int) = (const void*) 0x8097749;
extern void RestartScreenMenuScrollingBg();
// static void (*PrepMenu_UpdateTsaScroll)(int) = (const void*) 0x809A645;



// static void * (struct Proc_PrepUnit* proc);
static void PrepSkill_OnInit (struct Proc_PrepUnit* proc);
static void PrepSkill_OnEnd (struct Proc_PrepUnit* proc);
static void PrepSkill_InitScreen (struct Proc_PrepUnit* proc);
static void PrepSkill_UnitSelectLoop (struct Proc_PrepUnit* proc);


// On Draw
static void PrepSkill_InitTexts();
static void PrepSkill_DrawPickTotalBar(struct Unit* unit, int config); // config: 0->init, 1->update
static void PrepSkill_DrawRightSkillWindow(struct Unit* unit);









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
	PROC_CALL	(PrepSkill_OnInit),
	PROC_CALL	(PrepSkill_InitScreen),
	PROC_YIELD,
	
	PROC_CALL_ARG (NewFadeIn, 0x10),
	PROC_WHILE	(FadeInExists),
	
	
	
	
PROC_LABEL (LABEL_PREPSKILL_UNITLOOP),
	
	PROC_REPEAT	(PrepSkill_UnitSelectLoop),




PROC_LABEL	(LABEL_PREPSKILL_END),
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


void PrepSkill_OnInit (struct Proc_PrepUnit* proc){
	
	extern struct Unit* sub_8095394(); // maybe get leader?
	extern int sub_80958FC(struct Unit*); // Get index in Prep-Unit-List
	
	struct Proc_AtMenu* parent;
	parent = (struct Proc_AtMenu*)proc->proc_parent;
	
	proc->list_num_cur = sub_80958FC( sub_8095394() );
	proc->list_num_pre = proc->list_num_cur;
	
	proc->max_counter = parent->max_counter;
	proc->yDiff_cur = parent->yDiff;
}








void PrepSkill_InitScreen (struct Proc_PrepUnit* proc){

	static void (*PrepUnit_InitGfx)(void) = (const void*) 0x809A875;
	static void (*PrepUnit_InitSMS)(ProcPtr) = (const void*) 0x809A8F9;
	static void (*PrepUnit_DrawLeftUnitName)(struct Unit*) = (const void*) 0x809A931;
	static void (*PrepUnit_DrawUnitListNames)(struct Proc_PrepUnit*, int) = (const void*) 0x809A581;
	//static void (*PrepUnit_DrawText_Pick_Left)(struct Proc_PrepUnit*,int) = (const void*) 0x809AAF1;
	extern void Get6CDifferedLoop6C(void* func, ProcPtr);
	extern void sub_809A66C(struct Proc_PrepUnit*); // Called on SMS proc on-end
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
	PrepUnit_InitGfx();
	
	BG_EnableSyncByMask(0b1111);
	SetDefaultColorEffects();
	
	// Init SMS
	PrepUnit_InitSMS(proc);
	Get6CDifferedLoop6C(sub_809A66C, proc);
	
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
	StartHelpPromptSprite(0x20, 0x8F, 9, (ProcPtr)proc);
	
	
	// Draw Texts
	for( int i = 0; i < 6; i++)
		PrepUnit_DrawUnitListNames(proc, proc->yDiff_cur / 16 + i);
	
	PrepUnit_DrawLeftUnitName(unit);
	PrepSkill_DrawPickTotalBar(unit, 0);
	PrepSkill_DrawRightSkillWindow(unit);
	
	
	NewGreenTextColorManager((ProcPtr)proc);
	LoadDialogueBoxGfx(BG_SCREEN_ADDR(0x29), 5);
	RestartScreenMenuScrollingBg();
	
}











// Unit Select Loop
void PrepSkill_UnitSelectLoop (struct Proc_PrepUnit* proc){
	
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
		Text_Init(&gPrepUnitTexts[i + 0xE], 7);
	
	Text_Init(&gPrepUnitTexts[0x13], 7);
	Text_Init(&gPrepUnitTexts[0x14], 10);
	Text_Init(&gPrepUnitTexts[0x15], 15);
	
}




void PrepSkill_DrawPickTotalBar(struct Unit* unit, int config){
	
	// 0x809AAF1
	// config: 0->init, 1->update
	
	if( 0 == config )
	{
		Text_Clear(&gPrepUnitTexts[0x15]);
		
		DrawTextInline(
			&gPrepUnitTexts[0x15],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xD, 0x1),
			TEXT_COLOR_NORMAL, 6, 0,
			"Pick" );
		
		DrawTextInline(
			&gPrepUnitTexts[0x15],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xD, 0x1),
			TEXT_COLOR_NORMAL, 0x35, 0,
			"Total Skills" );
		
	} // if config
	
	
	// W.I.P.
	// Draw Numbers
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x10, 0x1),
		1, 1, 0 );
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1A, 0x1),
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


void PrepSkill_DrawRightSkillWindow(struct Unit* unit){
	
	struct SkillFastTesterList* list;
	
	
	ResetIconGraphics_();
	
	for( int i = 0; i < 3; i++ )
		Text_Clear(&gPrepUnitTexts[i + 0xE]);
	
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
		"Skill List");
	
	DrawTextInline(
		&gPrepUnitTexts[0xF],
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 9),
		TEXT_COLOR_GOLD,
		0, 0, 
		"Class & Unit");
	
	DrawTextInline(
		&gPrepUnitTexts[0x10],
		TILEMAP_LOCATED( gBG0TilemapBuffer, 8, 9),
		TEXT_COLOR_GOLD,
		0, 0, 
		"Skills");
	
	
	
	
	// Draw Handleable Skills' Icon
	list = GetOrMakeSklFastList(unit);
	
	if ( list->cnt == 0 ) 
	{
		DrawTextInline(
			&gPrepUnitTexts[0x11],
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
}






// =======================================================
// ====================== GLOBAL =========================
// =======================================================
void StartPrepScreenSkillsMenu(struct Proc_AtMenu* proc){
	
	Proc_StartBlocking(ProcCmd_PrepSkillScreen, proc);
	return;
	
}


