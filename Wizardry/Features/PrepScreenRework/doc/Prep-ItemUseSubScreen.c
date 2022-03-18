// #include "prep-item.h"
#include "gbafe.h"

#define TH_PREP_ITEM gUnknown_02013498
extern struct TextHandle gUnknown_02013498[];






void PrepScreenItemUseScreen_OnUpdateSMS (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_OnInit (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_InitDisplay (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_OnIdle (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_AreUSureBoxInit (struct Proc_PrepItemUse*);
void PrepScreenItemUseScreen_AreUSureBoxLoop (struct Proc_PrepItemUse*);

void NewFadeIn (ProcPtr);
void NewFadeOut (ProcPtr);
int FadeOutExists (void);
int FadeInExists(void);
void WaitForFade (ProcPtr);
void StartFadeInBlackMedium (void);
void StartPrepScreenPromotion (struct Proc_PrepItemUse*);
static const uint32_t PrepScreenItemUseScreen_Promo_09CC9C = 0x809CC9C+1;
static const uint32_t PrepScreenItemUseScreen_Promo_09CC60 = 0x809CC60+1;
static const uint32_t PrepScreenItemUseScreen_Promo_002A6C = 0x8002A6C+1;
static const uint32_t PrepScreenItemUseScreen_OnEnd = 0x809C940+1;
static void (*ProcPrepItem_807EDF8)(int, int, int, ProcPtr) = (const void*) 0x807EDF9;
void DrawSpecialUiChar(u16* out, int color, int chr);
static const void (*PrepItemProc_HandleItemMsgPopUp)(int, int, int, int, int) = (const void*) 0x809A31D;
static void (*PrepScreenItemUseScreen_Init_ShowHand) (int, int, int, int) = (const void*) 0x80AD51D;
static void (*AP_80ACA84)(int) = (const void*) 0x80ACA85;
static void (*AP_807EE74)(void) = (const void*) 0x807EE75;


// Some funcs that maybe work on later
void DrawPrepScreenItemUseStatLabels(struct Unit*);
void DrawPrepScreenItemUseStatBars(struct Unit*, uint32_t mask);
void DrawPrepScreenItemUseStatValues(struct Unit*);
void DrawPrepScreenItemUseItemUseDesc(struct Unit*, int32_t);
static void (*DrawPrepScreenItemUseItems)(void*, struct TextHandle*, struct Unit*, int) = (const void*) 0x809B74C+1;

// Item Effect
void PrepScreenItemUseScreen_HandleItemEffect (struct Proc_PrepItemUse*); // 0x809CB39
extern const struct ProcCmd _gProc_StatScreenItemStatBoosterEffect[]; // 0x8A191A4
const struct ProcCmd _gProc_StatScreenItemJunaFruitEffect[]; // 0x8A191C4


// Booster effect proc
void PrepItemBooster_OnEnd(struct Proc_PrepItemBoost*);
void PrepItemBooster_OnInit(struct Proc_PrepItemBoost*);
void PrepItemBooster_OnIdle(struct Proc_PrepItemBoost*);

// Juna fruit effect proc
void PrepItemJuna_OnEnd(struct Proc_PrepItemJuna*); // 0x809D1C0
void PrepItemJuna_OnInit(struct Proc_PrepItemJuna*); // 0x809D0D4
void PrepItemJuna_OnIdle(struct Proc_PrepItemJuna*); // 0x809D17C
extern void sub_807EE74(ProcPtr); // end APs

// Item effect routines
static void (*PrepItemScreen_DrawStatUpAP)(int x, int y, int diff) = (const void*) 0x807EFF1;
void PrepItemBooster_DrawPopup(struct Proc_PrepItemBoost*, int, int, u16 msg_id, u16 item);// 0x809CD15
static void (*PrepItemJunaFruit_DrawPopup)(struct Proc_PrepItemJuna*, int, int, u16 msg_id, u16 item) = (const void*) 0x809D015;
u16 ApplyStatBoosterAndGetMessageId(struct Unit*, int item_slot); // 0x802F809
static u16 (*ApplyJunaFruitAndGetMessageId)(struct Unit*, int item_slot) = (const void*) 0x802F979;



/* enum{
	PROC_LABEL_PREPITEM_INIT = 0,
	PROC_LABEL_PREPITEM_IDLE = 1,
	PROC_LABEL_PREPITEM_CONFIRM = 2,
	PROC_LABEL_PREPITEM_EFFECT = 3,
	PROC_LABEL_PREPITEM_JUNAFRUIT = 4,
	PROC_LABEL_PREPITEM_PROMOTE = 5,
	PROC_LABEL_PREPITEM_PRE_END = 6,
	PROC_LABEL_PREPITEM_END = 7,
};
 */


// 8A19064
const struct ProcCmd _gProc_PrepScreenItemUseScreen[] = {
	
	PROC_YIELD,

// Label 0: init	
PROC_LABEL(PROC_LABEL_PREPITEM_INIT),	
	PROC_CALL (PrepScreenItemUseScreen_OnInit),
	PROC_CALL (PrepScreenItemUseScreen_InitDisplay),
	PROC_CALL_ARG (NewFadeIn, 0x10),
	PROC_WHILE (FadeInExists),

// Label 1: main Loop
PROC_LABEL(PROC_LABEL_PREPITEM_IDLE),	
	PROC_REPEAT (PrepScreenItemUseScreen_OnIdle),


// Label 2: "are you sure" text
PROC_LABEL(PROC_LABEL_PREPITEM_CONFIRM),	
	PROC_CALL (PrepScreenItemUseScreen_AreUSureBoxInit),
	PROC_REPEAT (PrepScreenItemUseScreen_AreUSureBoxLoop),
	PROC_GOTO(1),	// Back to main loop

	
// Label 3: handle item effect
PROC_LABEL(PROC_LABEL_PREPITEM_EFFECT),
	PROC_CALL ((void*)PrepScreenItemUseScreen_HandleItemEffect),
	PROC_START_CHILD_BLOCKING (_gProc_StatScreenItemStatBoosterEffect),
	PROC_GOTO(1),	// Back to main loop


// Label 4: juna fruit
PROC_LABEL(PROC_LABEL_PREPITEM_JUNAFRUIT),
	PROC_START_CHILD_BLOCKING ((void*)_gProc_StatScreenItemJunaFruitEffect),
	PROC_GOTO(1),	// Back to main loop


// Label 5: promote
PROC_LABEL(PROC_LABEL_PREPITEM_PROMOTE),
	PROC_CALL_ARG (NewFadeOut, 0x10),
	PROC_WHILE (FadeOutExists),
	PROC_CALL (StartFadeInBlackMedium),
	PROC_REPEAT (WaitForFade),
	PROC_CALL (StartPrepScreenPromotion),
	PROC_SLEEP(8),
	PROC_CALL ((void*)PrepScreenItemUseScreen_Promo_09CC9C),
	PROC_SLEEP (8),
	PROC_CALL ((void*)PrepScreenItemUseScreen_Promo_09CC60),
	PROC_CALL (PrepScreenItemUseScreen_InitDisplay),
	PROC_CALL_ARG (NewFadeIn, 8),
	PROC_WHILE (FadeInExists),
	PROC_WHILE ((void*)PrepScreenItemUseScreen_Promo_002A6C),
	PROC_GOTO(1),	// Back to main loop
	

// Label 6: fade out into end
PROC_LABEL(PROC_LABEL_PREPITEM_PRE_END),
	PROC_CALL_ARG (NewFadeOut, 0x10),
	PROC_WHILE (FadeOutExists),
	
// Label 7: end
PROC_LABEL(PROC_LABEL_PREPITEM_END),
	PROC_CALL ((void*)PrepScreenItemUseScreen_OnEnd),
	PROC_END,

};






// Start prep-item-use proc
void StartPrepScreenItemUseScreen (struct Unit* unit, ProcPtr parent) {
	
	struct Proc_PrepItemUse* child = 
		(struct Proc_PrepItemUse*)
		Proc_StartBlocking(_gProc_PrepScreenItemUseScreen, parent);
	
	child->unit = unit;
	
}







// ====================================================
// -------------- Inside Proc Funcs -------------------
// ====================================================

// 0x809C4E4
void PrepScreenItemUseScreen_InitDisplay (struct Proc_PrepItemUse* proc) {
	
	// Common defs
	extern const struct FaceVramEntry gFaceConfig_8205C70[];
	extern u16 gBgConfig_8A181E8[];
	void SetupFaceGfxData(const struct FaceVramEntry*);
	void RestartScreenMenuScrollingBg();
	void NewFace2(int, int, int, int, int);
	static void (*PrepScreenItemUseScreen_Init_DrawSomeGfx1)(int, int) = (const void*) 0x8098C3D;
	static void (*PrepScreenItemUseScreen_Init_DrawSomeGfx2)(int, int) = (const void*) 0x8098C8D;
	// extern u8 gGenericBuffer[0x200];
	int StartSmallBrownNameBoxes(int, int, int, int, int, ProcPtr);
	static void (*MaybeConfigSmallBrownNameBox)(int, int, int, int) = (const void*) 0x80ADBFD;
	extern const struct ProcCmd gProc_8A20B4C[];
	void ResetPrepScreenHandCursor(struct Proc_PrepItemUse*);
	static void (*PrepScreen_DrawHandGfxMaybe)(int, int) = (const void*) 0x80AD4A1;
	void Get6CDifferedLoop6C(void*, ProcPtr);
	void SetColorEffectsFirstTarget(int bg0, int bg1, int bg2, int bg3, int obj);
	static struct Proc* (*_StartHelpPromptSprite)(int x, int y, int palid, ProcPtr) = (const void*) 0x80894e1;
	void SMS_RegisterUsage(int);
	
	
	// Datas
	#define Gfx_PrepItemUseScreen gUnknown_08A1BAB8
	#define Tsa_PrepItemUseScreen gUnknown_08A1BAE4
	extern const u8 gUnknown_08A1BAB8[];
	extern const u8 gUnknown_08A1BAE4[];
	
	
	
	
	
	// begin
	char* str;
	
	gLCDControlBuffer.dispcnt.mode = 0;
	
	SetupBackgrounds(gBgConfig_8A181E8);
	SetupFaceGfxData(gFaceConfig_8205C70);
	
	proc->item34 = 0xFF;
	
	BG_Fill(BG_GetMapBuffer(0), 0);
	BG_Fill(BG_GetMapBuffer(1), 0);
	BG_Fill(BG_GetMapBuffer(2), 0);
	
	
	gLCDControlBuffer.bg0cnt.priority = 1;
	gLCDControlBuffer.bg1cnt.priority = 2;
	gLCDControlBuffer.bg2cnt.priority = 0;
	gLCDControlBuffer.bg3cnt.priority = 3;
	
	Font_InitForUIDefault();
	ResetIconGraphics_();
	LoadUiFrameGraphics();
	LoadObjUIGfx();
	SetupMapSpritesPalettes();
	
	BG_SetPosition(0, 0,0);
	BG_SetPosition(1, 0,0);
	BG_SetPosition(2, 0,0);
	
	LoadDialogueBoxGfx(BG_CHAR_ADDR(5), -1);
	LoadIconPalettes(4);
	RestartScreenMenuScrollingBg();
	
	for (int i = 0; i < 5; i++)
		Text_Allocate( &TH_PREP_ITEM[15+i], 7);
	
	
	for (int i = 0; i < 8; i++)
		Text_Init( &TH_PREP_ITEM[i], 3);
	
	Text_Init( &TH_PREP_ITEM[8], 8);
	Text_Init( &TH_PREP_ITEM[25], 15);
	Text_Init( &TH_PREP_ITEM[26], 15);
	Text_Init( &TH_PREP_ITEM[27], 14);
	Text_Init( &TH_PREP_ITEM[28], 8);
	Text_Init( &TH_PREP_ITEM[30], 15);
	
	DrawPrepScreenItemUseStatLabels(proc->unit);
	DrawPrepScreenItemUseStatValues(proc->unit);
	DrawPrepScreenItemUseStatBars(proc->unit,0);
		
	NewFace2(0, GetUnitPortraitId(proc->unit), 0x40, -4, 0x203);
	PrepScreenItemUseScreen_Init_DrawSomeGfx1( 0x6000, 5);
	PrepScreenItemUseScreen_Init_DrawSomeGfx2( 0x800, 10);
	
	CopyDataWithPossibleUncomp(
		Gfx_PrepItemUseScreen, 
		(void*) (BG_VRAM + 0x440)
	);
	
	CopyDataWithPossibleUncomp(
		Tsa_PrepItemUseScreen,
		gGenericBuffer
	);
	
	CallARM_FillTileRect(gBG1TilemapBuffer, gGenericBuffer, 0x1000);
	
	BG_EnableSyncByMask(0b111);
	
	// (int objNode, int tileOffset, int palIndex, int oam2base, int oam0base, ProcPtr parent);
	StartSmallBrownNameBoxes(0xD, 0xE00, 0xF, 0xC00, 0, proc);
	MaybeConfigSmallBrownNameBox(0, -0x28, -1, 1);
	
	str = GetStringFromIndex( proc->unit->pCharacterData->nameTextId );
	
	DrawTextInline(
		0, gBG0TilemapBuffer, 
		TEXT_COLOR_NORMAL, 
		(0x30 - GetStringTextWidth(str))/2,
		6, str
	);
	
	// sub_80AC9C0
	Proc_Start(gProc_8A20B4C, proc);
	
	ResetPrepScreenHandCursor(proc);
	PrepScreen_DrawHandGfxMaybe(0x600, 1);
	Get6CDifferedLoop6C(PrepScreenItemUseScreen_OnUpdateSMS, proc);
	
	
	gLCDControlBuffer.dispcnt.win0_on = 1;
	gLCDControlBuffer.dispcnt.win1_on = 0;
	gLCDControlBuffer.dispcnt.objWin_on = 0;
	
	gLCDControlBuffer.win0_top = 0x5E;
	gLCDControlBuffer.win0_bottom = 0x92;
	gLCDControlBuffer.win0_left = 0x68;
	gLCDControlBuffer.win0_right = 0xF0;
	
	gLCDControlBuffer.wincnt.win0_enableBg0 = 1;
	gLCDControlBuffer.wincnt.win0_enableBg1 = 1;
	gLCDControlBuffer.wincnt.win0_enableBg2 = 1;
	gLCDControlBuffer.wincnt.win0_enableBg3 = 1;
	gLCDControlBuffer.wincnt.win0_enableObj = 1;
	gLCDControlBuffer.wincnt.win0_enableBlend = 1;
	
	gLCDControlBuffer.wincnt.wout_enableBg0 = 1;
	gLCDControlBuffer.wincnt.wout_enableBg1 = 1;
	gLCDControlBuffer.wincnt.wout_enableBg2 = 1;
	gLCDControlBuffer.wincnt.wout_enableBg3 = 1;
	gLCDControlBuffer.wincnt.wout_enableObj = 1;
	gLCDControlBuffer.wincnt.wout_enableBlend = 0;
	
	
	
	SetSpecialColorEffectsParameters(3,0,0,8);
	SetColorEffectsFirstTarget(0,0,0,1,0);
	NewGreenTextColorManager((ProcPtr)proc);
	
	_StartHelpPromptSprite(0xC0, 0x90, 9, proc);
	DrawPrepScreenItemUseItemUseDesc(proc->unit, proc->item_slot);
	DrawPrepScreenItemUseItems(
		TILEMAP_LOCATED(gBG0TilemapBuffer, 2, 9),
		&TH_PREP_ITEM[15],
		proc->unit, 1
	);
	
	// x, y, ?, ?
	PrepScreenItemUseScreen_Init_ShowHand(0x10, (proc->item_slot & 0b111)*16+0x48, 0xB, 0x800);
	

	SMS_RegisterUsage(GetUnitSMSId(proc->unit));
	SMS_FlushIndirect();
	
	
	#undef Gfx_PrepItemUseScreen
	#undef Tsa_PrepItemUseScreen
}



// 0x809BF10
void DrawPrepScreenItemUseStatLabels(struct Unit* unit) {
	
	char* str;
	
	for( int i = 0; i < 8; i++ )
		Text_Clear( &TH_PREP_ITEM[i] );
	
	DrawTextInline(
		&TH_PREP_ITEM[0],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 3),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4E9 ) // HP
	);
	
	
	if ( 0 == UnitHasMagicRank(unit) )
		DrawTextInline(
			&TH_PREP_ITEM[1],
			TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 5),
			TEXT_COLOR_GOLD,
			0, 0, GetStringFromIndex( 0x4FE ) // Str
		);
	else
		DrawTextInline(
			&TH_PREP_ITEM[1],
			TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 5),
			TEXT_COLOR_GOLD,
			0, 0, GetStringFromIndex( 0x4FF ) // Mag
		);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[2],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 7),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4EC ) // Skill
	);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[3],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 16, 9),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4ED ) // Spd
	);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[4],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 23, 3),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4EE ) // Luck
	);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[5],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 23, 5),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4EF ) // Def
	);
	
	
	DrawTextInline(
		&TH_PREP_ITEM[6],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 23, 7),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4F0 ) // Res
	);
	
	DrawTextInline(
		&TH_PREP_ITEM[7],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 23, 9),
		TEXT_COLOR_GOLD,
		0, 0, GetStringFromIndex( 0x4F7 ) // Con
	);
	
	str = GetStringFromIndex( unit->pClassData->nameTextId );
	
	DrawTextInline(
		&TH_PREP_ITEM[8],
		TILEMAP_LOCATED(gBG2TilemapBuffer, 21, 1),
		TEXT_COLOR_NORMAL,
		GetStringTextCenteredPos(0x40, str), 
		0, 
		str // unit class
	);
	
	// "L" and "V"
	DrawSpecialUiChar( TILEMAP_LOCATED(gBG2TilemapBuffer, 17, 1), 3, 0x24);
	DrawSpecialUiChar( TILEMAP_LOCATED(gBG2TilemapBuffer, 18, 1), 3, 0x25);
	
}




// 0x809C254
void DrawPrepScreenItemUseStatValues(struct Unit* unit) {
	
	// HP
	DrawDecNumber( 
		TILEMAP_LOCATED(gBG2TilemapBuffer, 20, 3),
		(GetUnitCurrentHp(unit) == UNIT_MHP_MAX(unit)) 
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		GetUnitCurrentHp(unit)
	);
	
	
	// POW
	DrawDecNumber(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 20, 5),
		(GetUnitPower(unit) == UNIT_POW_MAX(unit)) 
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		GetUnitPower(unit)
	);
	
	
	// SKL
	DrawDecNumber(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 20, 7),
		(GetUnitSkill(unit) == UNIT_SKL_MAX(unit)) 
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		GetUnitSkill(unit)
	);
	
	
	// SPD
	DrawDecNumber(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 20, 9),
		(GetUnitSpeed(unit) == UNIT_SPD_MAX(unit)) 
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		GetUnitSpeed(unit)
	);
	
	
	// LCK
	DrawDecNumber(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 27, 3),
		(GetUnitLuck(unit) == UNIT_LCK_MAX(unit)) 
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		GetUnitLuck(unit)
	);
	
	
	// DEF
	DrawDecNumber(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 27, 5),
		(GetUnitDefense(unit) == UNIT_DEF_MAX(unit)) 
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		GetUnitDefense(unit)
	);
	
	
	// RES
	DrawDecNumber(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 27, 7),
		(GetUnitResistance(unit) == UNIT_RES_MAX(unit)) 
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		GetUnitResistance(unit)
	);
	
	
	// CON
	DrawDecNumber(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 27, 9),
		(UNIT_CON(unit) == UNIT_CON_MAX(unit)) 
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		UNIT_CON(unit)
	);
	
	
	TileMap_FillRect(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 19, 1),
		1, 1, 0
	);
	
	
	// LV
	DrawDecNumber(
		TILEMAP_LOCATED(gBG2TilemapBuffer, 20, 1),
		TEXT_COLOR_BLUE,
		unit->level
	);
	
	
	BG_EnableSyncByMask(0b100);
}




// 0x809C0B4
void DrawPrepScreenItemUseStatBars(struct Unit* unit, uint32_t mask) {
	
	static void (*UnpackUiBarPalette)(int) = (const void*) 0x804E138+1;
	static void (*DrawPrepScreenItemUseStatBars_Core)(int, int, void*, int, int, int, int) = (const void*) 0x8086B2C+1;
	
	enum{
		STAT_PACK_HP  = 0,
		STAT_PACK_POW = 1,
		STAT_PACK_SKL = 2,
		STAT_PACK_SPD = 3,
		
		STAT_PACK_LCK = 4,
		STAT_PACK_DEF = 5,
		STAT_PACK_RES = 6,
		STAT_PACK_CON = 7,
	};
	
	
	
	int stat_pack[8];
	
	UnpackUiBarPalette(2);
	
	stat_pack[STAT_PACK_HP]  = GetUnitCurrentHp(unit) * 24 / UNIT_MHP_MAX(unit);
	stat_pack[STAT_PACK_POW] = GetUnitPower(unit) * 24 / UNIT_POW_MAX(unit);
	stat_pack[STAT_PACK_SKL] = GetUnitSkill(unit) * 24 / UNIT_SKL_MAX(unit);
	stat_pack[STAT_PACK_SPD] = GetUnitSpeed(unit) * 24 / UNIT_SPD_MAX(unit);
	
	stat_pack[STAT_PACK_LCK] = GetUnitLuck(unit) * 24 / UNIT_LCK_MAX(unit);
	stat_pack[STAT_PACK_DEF] = GetUnitDefense(unit) * 24 / UNIT_DEF_MAX(unit);
	stat_pack[STAT_PACK_RES] = GetUnitResistance(unit) * 24 / UNIT_RES_MAX(unit);
	stat_pack[STAT_PACK_CON] = UNIT_CON(unit) * 24 / UNIT_CON_MAX(unit);
	
	
	// 王德发
	// nmd总共就七个值,你不搞个switch, 搁这整活？？
	for( int i = 0; i < 7; i++ )
		DrawPrepScreenItemUseStatBars_Core(
				0x380 + 8 * i, 4, 
				
				TILEMAP_LOCATED(gBG0TilemapBuffer, (i>>2)*7 +18, (i&0b11)*2 + 4),
				0 == ((mask >> i) & 1)
					? 0x2000
					: 0x3000,
					
				0x18, stat_pack[i], 
				
				0 == ((mask >> i) & 1)
					? 0
					: stat_pack[i]
			);

	
	
	BG_EnableSyncByMask(0b1);
}




// 0x809C3EC
void DrawPrepScreenItemUseItemUseDesc(struct Unit* unit, int32_t slot) {
	
	static void (*DrawPrepItemScreenItemDesc_Core)(struct TextHandle* list[], char*, void* map, int lines) = (const void*) 0x8008A3C+1;
	
	uint16_t msg_desc, item;
	int color;
	
	Text_Clear( &TH_PREP_ITEM[25] );
	Text_Clear( &TH_PREP_ITEM[26] );
	Text_Clear( &TH_PREP_ITEM[30] );
	
	if ( slot == -1 )
		return;
	
	item = unit->items[slot];
	msg_desc = GetItemUseDescId(item);
	
	
	// ??? wtf
	struct TextHandle* th_list[3] = {
		&TH_PREP_ITEM[25],
		&TH_PREP_ITEM[26],
		&TH_PREP_ITEM[30],
	};
	
	
	
	color = CanUnitUseItemPrepScreen(unit, item)
		? TEXT_COLOR_NORMAL
		: TEXT_COLOR_GRAY;
		
	
	Text_SetColorId( th_list[0], color );
	Text_SetColorId( th_list[1], color );
	Text_SetColorId( th_list[2], color );
	
	
	DrawPrepItemScreenItemDesc_Core(
		th_list,
		GetStringFromIndex(msg_desc),
		TILEMAP_LOCATED(gBG0TilemapBuffer, 15, 12),
		3
	);
	
	BG_EnableSyncByMask(0b1);
}






// ========================================
// 				Juna Fruit
// ========================================

// already inside bmitemuse.c
int8_t CanUnitUseItemPrepScreen(struct Unit* unit, int item)
{
	if (GetItemAttributes(item) & IA_STAFF)
		return FALSE;

	switch (GetItemIndex(item))
	{

	case ITEM_BOOSTER_HP:
	case ITEM_BOOSTER_POW:
	case ITEM_BOOSTER_SKL:
	case ITEM_BOOSTER_SPD:
	case ITEM_BOOSTER_LCK:
	case ITEM_BOOSTER_DEF:
	case ITEM_BOOSTER_RES:
	case ITEM_BOOSTER_MOV:
	case ITEM_BOOSTER_CON:
		return CanUnitUseStatGainItem(unit, item);

	case ITEM_HEROCREST:
	case ITEM_KNIGHTCREST:
	case ITEM_ORIONSBOLT:
	case ITEM_ELYSIANWHIP:
	case ITEM_GUIDINGRING:
	case ITEM_MASTERSEAL:
	case ITEM_HEAVENSEAL:
	case ITEM_OCEANSEAL:
	case ITEM_LUNARBRACE:
	case ITEM_SOLARBRACE:
	case ITEM_UNK_C1:
		return CanUnitUsePromotionItem(unit, item);

	case ITEM_METISSTOME:
		if (unit->state & US_GROWTH_BOOST)
			return FALSE;

		return TRUE;

	case ITEM_JUNAFRUIT:
		return CanUnitUseFruitItem(unit);

	default:
		return FALSE;

	}
}




// static const uint32_t PrepScreenItemUseScreen_HandleItemEffect = 0x809CB39;
void PrepScreenItemUseScreen_HandleItemEffect (struct Proc_PrepItemUse* proc) {
	
	switch ( GetItemIndex (proc->unit->items[proc->item_slot]) ) 
	{
		case ITEM_HEROCREST:
		case ITEM_KNIGHTCREST:
		case ITEM_ORIONSBOLT:
		case ITEM_ELYSIANWHIP:
		case ITEM_GUIDINGRING:
		case ITEM_MASTERSEAL:
		case ITEM_HEAVENSEAL:
		case ITEM_OCEANSEAL:
		case ITEM_LUNARBRACE:
		case ITEM_SOLARBRACE:
		case ITEM_UNK_C1:
			// case promotion:
			if( 0 == gRAMChapterData.unk41_8)
				m4aSongNumStart(0x6A);
			Proc_Goto(proc, PROC_LABEL_PREPITEM_PROMOTE);
			break;
			
		case ITEM_JUNAFRUIT:
			Proc_Goto(proc, PROC_LABEL_PREPITEM_JUNAFRUIT);
			break;
		
		default:
			break;
	} // switch
	
	
}

















// ========================================
// 					Booster
// ========================================






// 0x8A191C4
const struct ProcCmd _gProc_StatScreenItemStatBoosterEffect[] = {
	
	PROC_SET_END_CB (PrepItemBooster_OnEnd),
	PROC_CALL (PrepItemBooster_OnInit),
	PROC_REPEAT (PrepItemBooster_OnIdle),
	PROC_END,
};





// 0x809CDD4
void PrepItemBooster_OnInit(struct Proc_PrepItemBoost* child) {
	
	struct Proc_PrepItemUse* parent;
	u16 item, msg_message;
	
	parent = (struct Proc_PrepItemUse*) child->proc_parent;
	ProcPrepItem_807EDF8(0x1C0,3,0,parent);
	
	child->pre_stat[0] = GetUnitCurrentHp(parent->unit);
	child->pre_stat[1] = GetUnitPower(parent->unit);
	child->pre_stat[2] = GetUnitSkill(parent->unit);
	child->pre_stat[3] = GetUnitSpeed(parent->unit);
	child->pre_stat[4] = GetUnitLuck(parent->unit);
	child->pre_stat[5] = GetUnitDefense(parent->unit);
	child->pre_stat[6] = GetUnitResistance(parent->unit);
	child->pre_stat[7] = UNIT_CON(parent->unit);
	
	item = parent->unit->items[parent->item_slot];
	msg_message = ApplyStatBoosterAndGetMessageId( parent->unit, parent->item_slot);
	
	DrawPrepScreenItemUseStatBars(parent->unit, 0);
	DrawPrepScreenItemUseStatValues(parent->unit);
	
	child->new_stat[0]  = GetUnitCurrentHp(parent->unit);
	child->new_stat[1] = GetUnitPower(parent->unit);
	child->new_stat[2] = GetUnitSkill(parent->unit);
	child->new_stat[3] = GetUnitSpeed(parent->unit);
	child->new_stat[4] = GetUnitLuck(parent->unit);
	child->new_stat[5] = GetUnitDefense(parent->unit);
	child->new_stat[6] = GetUnitResistance(parent->unit);
	child->new_stat[7] = UNIT_CON(parent->unit);
	
	PrepItemBooster_DrawPopup(child, 0xE, 0xE, msg_message, item);
	
	for( int i = 0; i < 8; i++ )
		if ( child->new_stat[i] != child->pre_stat[i] )
			PrepItemScreen_DrawStatUpAP(
				(i > 3 ? 1 : 0) * 7 * 8 + 0xB0,	// x?
				(i > 3 ? 0 : 1) * 16 + 0x2A,	// y?
				child->new_stat[i] - child->pre_stat[i]
			);

	
	child->timer = 0x78;
	
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x5A);
	
}



// 0x809CF48
void PrepItemBooster_OnIdle(struct Proc_PrepItemBoost* proc) {
	
	PrepItemProc_HandleItemMsgPopUp(
		proc->popup_x,
		proc->popup_y,
		proc->popup_width,
		proc->popup_height,
		0xA440
	);
	
	if ( 0 != (--proc->timer) )
		if ( 0 == ((A_BUTTON + B_BUTTON) & gKeyStatusPtr->newKeys) )
			return;
	
	Proc_Break(proc);
}




// 0x809CF8C
void PrepItemBooster_OnEnd(struct Proc_PrepItemBoost* child) {
	
	struct Proc_PrepItemUse* parent;
	int item_count;
	
	parent = (struct Proc_PrepItemUse*) child->proc_parent;
	item_count = GetUnitItemCount( parent->unit );
	
	TileMap_FillRect( TILEMAP_LOCATED(gBG2TilemapBuffer, 14, 14), 14, 1, 0);
	
	if ( 0 == item_count )
		Proc_Goto(parent, PROC_LABEL_PREPITEM_PRE_END);
	else {
		
		if ( item_count <= parent->item_slot )
			parent->item_slot--;
		
		PrepScreenItemUseScreen_Init_ShowHand(0x10, parent->item_slot*16 + 0x48, 0xB, 0x800);

	}// if & else
		
	
	
	DrawPrepScreenItemUseItems(
		TILEMAP_LOCATED(gBG0TilemapBuffer, 2, 9),
		&TH_PREP_ITEM[15],
		parent->unit, 1);
	
	DrawPrepScreenItemUseItemUseDesc(parent->unit, parent->item_slot);
	
	AP_80ACA84(0);
	AP_807EE74();
	
	BG_EnableSyncByMask(0b101);
	LoadDialogueBoxGfx(BG_CHAR_ADDR(5), -1);
}





// 0x802F809
u16 ApplyStatBoosterAndGetMessageId(struct Unit* unit, int item_slot){
	
	u16 item, msg_desc;
	const struct ItemStatBonuses* it;
	
	msg_desc = 0;
	item = unit->items[item_slot];
	
	if ( ITEM_METISSTOME == GetItemIndex(item) ) {
		
		unit->state |= US_GROWTH_BOOST;
		UnitUpdateUsedItem(unit, item_slot);
		
		return 0x1D; // msg: "Maturity increased"
	
	} // if
	
	
	it = GetItemStatBonuses(item);
	
	unit->maxHP += it->hpBonus;
	unit->curHP += it->hpBonus;
	unit->pow += it->powBonus;
	unit->skl += it->sklBonus;
	unit->spd += it->spdBonus;
	unit->def += it->defBonus;
	unit->res += it->resBonus;
	unit->lck += it->lckBonus;
	unit->movBonus += it->movBonus;
	unit->conBonus += it->conBonus;
	
	UnitCheckStatCaps(unit);
	UnitUpdateUsedItem(unit, item_slot);
	
	switch ( GetItemIndex(item) )
	{
		case ITEM_BOOSTER_SKL:
			msg_desc = 0x15;	// Skill increased.
			break;
		
		case ITEM_BOOSTER_LCK:
			msg_desc = 0x17;	// Luck increased.
			break;
		
		case ITEM_BOOSTER_HP:
			msg_desc = 0x1C;	// Max HP increased.
			break;
			
		case ITEM_BOOSTER_DEF:
			msg_desc = 0x18;	// Defense increased.
			break;
		
		case ITEM_BOOSTER_SPD:
			msg_desc = 0x16;	// Speed increased.
			break;
		
		case ITEM_BOOSTER_RES:
			msg_desc = 0x19; 	// Resistance increased.
			break;
		
		case ITEM_BOOSTER_MOV:
			msg_desc = 0x1A;	// Movement increased.
			break;
		
		case ITEM_BOOSTER_CON:
			msg_desc = 0x1B;	// Constitution increased.
			break;
		
		case ITEM_BOOSTER_POW:
			if ( !UnitHasMagicRank(unit) )
				msg_desc = 0x13;// Strength increased.
			else
				msg_desc = 0x13;// Magic increased.
			
		default:
			break;
	} // switch
	
	return msg_desc;
}


// 0x809CD15
void PrepItemBooster_DrawPopup(struct Proc_PrepItemBoost* proc, int x, int y, u16 msg_id, u16 item) {

	char* str;
	int icon_id, str_width;
	struct TextHandle* th;
	
	str = GetStringFromIndex(msg_id);
	icon_id = GetItemIconId(item);
	str_width = GetStringTextWidth(str);
	
	if ( 0 != icon_id )
		DrawIcon(
			TILEMAP_LOCATED(gBG2TilemapBuffer, x, y),
			GetItemIconId(item), 0x4000);
	
	th = &TH_PREP_ITEM[27];
	
	Text_Clear(th);
	
	DrawTextInline(
		th, TILEMAP_LOCATED(gBG2TilemapBuffer, (0 == icon_id)?0:2 + x, y ),
		TEXT_COLOR_NORMAL, 0, 0, str);
	
	BG_EnableSyncByMask(0b100);
	
	proc->popup_x = x * 8 - 4;
	proc->popup_y = y * 8 - 4;
	
	if ( str_width < 0 )
		str_width += 7;
	
	proc->popup_width = str_width / 8 + 1;
	
	if ( 0 != icon_id )
		proc->popup_width += 3;
	
	proc->popup_height = 2;
}







// ========================================
// 				Juna Fruit
// ========================================




// 0x8A191C4
const struct ProcCmd _gProc_StatScreenItemJunaFruitEffect[] = {
	
	PROC_SET_END_CB (PrepItemJuna_OnEnd),
	PROC_CALL (PrepItemJuna_OnInit),
	PROC_REPEAT (PrepItemJuna_OnIdle),
	PROC_CALL (sub_807EE74),
	PROC_END,
};


// 0x809D0D4
void PrepItemJuna_OnInit(struct Proc_PrepItemJuna* child) {
	
	struct Proc_PrepItemUse* parent;
	u16 item, msg_message;
	
	parent = (struct Proc_PrepItemUse*) child->proc_parent;
	ProcPrepItem_807EDF8(0x1C0,3,0,parent);
	
	child->pre_lv = parent->unit->level;
	
	item = parent->unit->items[parent->item_slot];
	msg_message = ApplyJunaFruitAndGetMessageId( parent->unit, parent->item_slot);
	
	DrawPrepScreenItemUseStatBars(parent->unit, 0b0);
	DrawPrepScreenItemUseStatValues(parent->unit);
	
	child->new_lv = parent->unit->level;
	
	
	PrepItemJunaFruit_DrawPopup(child, 0x11, 0xE, msg_message, item);
	
	if ( child->new_lv != child->pre_lv )
		PrepItemScreen_DrawStatUpAP(
			0xB0,	// x?
			0x1A,	// y?
			child->new_lv - child->pre_lv
		);

	
	child->timer = 0x78;
	
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x5A);
}





// 0x809D17C
void PrepItemJuna_OnIdle(struct Proc_PrepItemJuna* proc){
	
	PrepItemProc_HandleItemMsgPopUp(
		proc->popup_x,
		proc->popup_y,
		proc->popup_width,
		proc->popup_height,
		0xA440
	);
	
	if ( 0 != (--proc->timer) )
		if ( 0 == ((A_BUTTON + B_BUTTON) & gKeyStatusPtr->newKeys) )
			return;
	
	Proc_Break(proc);
	
}




// 0x809D1C0
void PrepItemJuna_OnEnd(struct Proc_PrepItemJuna* child) {
	
	struct Proc_PrepItemUse* parent;
	int item_count;
	
	parent = (struct Proc_PrepItemUse*) child->proc_parent;
	item_count = GetUnitItemCount( parent->unit );
	
	TileMap_FillRect( TILEMAP_LOCATED(gBG2TilemapBuffer, 17, 14), 12, 1, 0);
	
	if ( 0 == item_count )
		Proc_Goto(parent, PROC_LABEL_PREPITEM_PRE_END);
	else {
		
		if ( item_count <= parent->item_slot )
			parent->item_slot--;
		
		PrepScreenItemUseScreen_Init_ShowHand(0x10, parent->item_slot*16 + 0x48, 0xB, 0x800);

	}// if & else
		
	
	
	DrawPrepScreenItemUseItems(
		TILEMAP_LOCATED(gBG0TilemapBuffer, 2, 9),
		&TH_PREP_ITEM[15],
		parent->unit, 1
	);
	
	DrawPrepScreenItemUseItemUseDesc(parent->unit, parent->item_slot);
	
	AP_80ACA84(0);
	
	BG_EnableSyncByMask(0b101);
	LoadDialogueBoxGfx(BG_CHAR_ADDR(5), -1);
	
}













#undef TH_PREP_ITEM // $02013498
