#include "gbafe-chax.h"
#include "CombatArt.h"


// ================================
//        Will add to C-Lib
// ================================

extern struct Struct0202BCB0 gGameState;

enum{
	// MenuItem Text Color
	MENU_COLOR_NORMAL = 0x0,
	MENU_COLOR_GRAY = 0x1,
	MENU_COLOR_BLUE = 0x2,
	MENU_COLOR_ORANGE = 0x3,
	MENU_COLOR_GREEN = 0x4,
	MENU_COLOR_BLACK = 0x5,
};


// ================================
//             Unit Menu
// ================================

int UMitem_CombatArt_Usability(const struct MenuItemDef* menu_item, int number){
	
	if( 1 == UnitHasCombatArt(gActiveUnit) )
		return MENU_ENABLED;
	
	else
		return MENU_DISABLED;
	
}


int UMitem_CombatArt_Effect(struct MenuProc* pmu, struct MenuItemProc* pcmd )
{
	extern void Text_ResetTileAllocation();
	
	struct MenuProc* pm_combat_art;
	
	// if unused
	if( MENU_ENABLED != pcmd->availability )
	{
		MenuFrozenHelpBox(pmu,msgAt_umCAGrayBox);
		return MENU_ITEM_NONE;
	}
	
	Text_ResetTileAllocation();	// This is reset font!
	ResetIconGraphics_();
	LoadIconPalettes(0x4);
	
	pm_combat_art = StartOrphanMenu(&Menu_CombatArtSelect);
	
	// Menu Panel
	// NewFace(0,GetUnitPortraitId(gActiveUnit),0xB0,0xC,0x2);
	// StartMenuPanel_CombatArt(pm_combat_art, gActiveUnit,0xF,0xB);
	
	return MENU_ACT_CLEAR | MENU_ACT_SND6A | MENU_ACT_END | MENU_ACT_SKIPCURSOR;
}






// ================================
//      CombatArt Select Menu
// ================================

static u8 CombatArtSelect_PressB(struct MenuProc*, struct MenuItemProc*);
static void CombatArtSelect_HelpBox(struct MenuProc*, struct MenuItemProc*);
static u8 CombatArtSelect_Usability(const struct MenuItemDef*, int number);
static int CombatArtSelect_DrawText(struct MenuProc*, struct MenuItemProc*);
static u8 CombatArtSelect_Effect(struct MenuProc*, struct MenuItemProc*);
static int CombatArtSelect_Hover(struct MenuProc*, struct MenuItemProc*);
static int CombatArtSelect_Unhover(struct MenuProc*, struct MenuItemProc*);


const struct MenuDef Menu_CombatArtSelect = {
	.rect 	= {1, 1, 0xE, 0},
	.style 	= 0,
	.menuItems = MenuItems_CombatArtSelect,
	.onInit = 0,
	.onEnd = 0,
	._u14 = 0,
	.onBPress = CombatArtSelect_PressB,
	.onRPress = MenuAutoHelpBoxSelect,
	.onHelpBox = CombatArtSelect_HelpBox,
};






const struct MenuItemDef MenuItems_CombatArtSelect[] = {
	
	[0] = {
		.name = 0,
		.nameMsgId = 0,
		.helpMsgId = 0,
		.color = MENU_COLOR_BLUE,
		.overrideId = 0x4E,
		.isAvailable = CombatArtSelect_Usability,
		.onDraw = CombatArtSelect_DrawText,
		.onSelected = CombatArtSelect_Effect,
		.onIdle = 0,
		.onSwitchIn = CombatArtSelect_Hover,
		.onSwitchOut = CombatArtSelect_Unhover,
	},
	
	[1] = {
		.name = 0,
		.nameMsgId = 0,
		.helpMsgId = 0,
		.color = MENU_COLOR_BLUE,
		.overrideId = 0x4E,
		.isAvailable = CombatArtSelect_Usability,
		.onDraw = CombatArtSelect_DrawText,
		.onSelected = CombatArtSelect_Effect,
		.onIdle = 0,
		.onSwitchIn = CombatArtSelect_Hover,
		.onSwitchOut = CombatArtSelect_Unhover,
	},
	
	[2] = {
		.name = 0,
		.nameMsgId = 0,
		.helpMsgId = 0,
		.color = MENU_COLOR_BLUE,
		.overrideId = 0x4E,
		.isAvailable = CombatArtSelect_Usability,
		.onDraw = CombatArtSelect_DrawText,
		.onSelected = CombatArtSelect_Effect,
		.onIdle = 0,
		.onSwitchIn = CombatArtSelect_Hover,
		.onSwitchOut = CombatArtSelect_Unhover,
	},
	
	[3] = {
		.name = 0,
		.nameMsgId = 0,
		.helpMsgId = 0,
		.color = MENU_COLOR_BLUE,
		.overrideId = 0x4E,
		.isAvailable = CombatArtSelect_Usability,
		.onDraw = CombatArtSelect_DrawText,
		.onSelected = CombatArtSelect_Effect,
		.onIdle = 0,
		.onSwitchIn = CombatArtSelect_Hover,
		.onSwitchOut = CombatArtSelect_Unhover,
	},
	
	[4] = {
		.name = 0,
		.nameMsgId = 0,
		.helpMsgId = 0,
		.color = MENU_COLOR_BLUE,
		.overrideId = 0x4E,
		.isAvailable = CombatArtSelect_Usability,
		.onDraw = CombatArtSelect_DrawText,
		.onSelected = CombatArtSelect_Effect,
		.onIdle = 0,
		.onSwitchIn = CombatArtSelect_Hover,
		.onSwitchOut = CombatArtSelect_Unhover,
	},
	[5] = {0}
};

u8 CombatArtSelect_PressB(struct MenuProc* mu, struct MenuItemProc* cmd){
	
	extern void Text_ResetTileAllocation();
	extern const struct MenuDef gUnitActionMenuDef[];
	
	// clear battle flag
	gpBattleFlagExt->isCombat = 0;
	
	// Menu Panel
	// EndMenuPanel_CombatArt();
	
	// Reset Text & Dsiplay
	Text_ResetTileAllocation();
	BG_Fill(gBG2TilemapBuffer, 0);
	BG_EnableSyncByMask(0b100);
	
	// Reset Menu
	StartSemiCenteredOrphanMenu(
		gUnitActionMenuDef,
		gGameState.unk1C.x - gGameState.camera.x,
		0x01, 0x14
	);
	
	// Reset map works
	HideMoveRangeGraphics();
	
	return MENU_ACT_ENDFACE | MENU_ACT_CLEAR | MENU_ACT_SND6B | MENU_ACT_END | MENU_ACT_SKIPCURSOR;
	
}


void CombatArtSelect_HelpBox(struct MenuProc*, struct MenuItemProc* item){
	
	StartHelpBox(8 * item->xTile, 8 * item->yTile, 0x212);
	
	return;
}



u8 CombatArtSelect_Usability(const struct MenuItemDef*, int number){
	
	// W.I.P.
	u8 index_combatArt = 1;
	
	if( 1 == CanUnitUseCombatArt(gActiveUnit, index_combatArt) )
		return MENU_ENABLED;
	
	else
		return MENU_DISABLED;
	
}

int CombatArtSelect_DrawText(struct MenuProc* menu, struct MenuItemProc* item){
	
	// W.I.P.
	// const u8 index_combatArt = 1;
	
	Text_SetColorId( 
		&item->text, 
		MENU_ENABLED == item->availability
			? MENU_COLOR_NORMAL
			: MENU_COLOR_GRAY );
	
	Text_AppendString(&item->text, "Hello World");
	
	Text_Draw(
		&item->text, 
		TILEMAP_LOCATED(gBG0TilemapBuffer, item->xTile + 2, item->yTile) );
	
	DrawIcon(
		TILEMAP_LOCATED(gBG0TilemapBuffer, item->xTile, item->yTile), 
		SKILL_ICON(0x21), 
		TILEREF(0, STATSCREEN_BGPAL_ITEMICONS)
	);
	
	DrawDecNumber(
		TILEMAP_LOCATED(gBG0TilemapBuffer, item->xTile + 0xB, item->yTile),
		MENU_ENABLED == item->availability
			? MENU_COLOR_NORMAL
			: MENU_COLOR_GRAY,
		1
	);
	
	return 0;
}

u8 CombatArtSelect_Effect(struct MenuProc*, struct MenuItemProc*){
	return MENU_ACT_CLEAR | MENU_ACT_SND6A | MENU_ACT_END | MENU_ACT_SKIPCURSOR;
}

int CombatArtSelect_Hover(struct MenuProc*, struct MenuItemProc*){
	return 0;
}

int CombatArtSelect_Unhover(struct MenuProc*, struct MenuItemProc*){
	return 0;
}


