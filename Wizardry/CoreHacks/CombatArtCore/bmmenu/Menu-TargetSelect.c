#include "gbafe-chax.h"


// ================================
//           Definitions
// ================================

enum{
	// MenuItem Text Color
	MENU_COLOR_NORMAL = 0x0,
	MENU_COLOR_GRAY = 0x1,
	MENU_COLOR_BLUE = 0x2,
	MENU_COLOR_ORANGE = 0x3,
	MENU_COLOR_GREEN = 0x4,
	MENU_COLOR_BLACK = 0x5,
};

extern struct Struct0202BCB0 gGameState;
extern void Text_ResetTileAllocation();



// Menu & Menu Items & Target-Select definitions
const struct MenuDef Menu_CombatArtSelect;
const struct MenuItemDef MenuItems_CombatArtSelect[];
const struct MenuDef Menu_CombatArt_WeaponSelect;
const struct MenuItemDef MenuItems_CombatArt_WeaponSelect[];
const struct SelectInfo TargetSelectInfo_CombatArt;
const struct ProcCmd ProcCmd_CombatArt_PostTargetSelect[];





// ================================
//             Unit Menu
// ================================

int UMitem_CombatArt_Usability(const struct MenuItemDef* menu_item, int number){
	
	extern void ForEachUnitInRange(void*);
	extern void TryAddTrapsToTargetList();
	
	// if canto, return false
	if( US_CANTOING & gActiveUnit->state  )
		return MENU_NOTSHOWN;
	
	if( 0 == UnitHasCombatArt(gActiveUnit) )
		return MENU_NOTSHOWN;
	
	u8 *list = GetCombatArtList(gActiveUnit);
	
	if( NULL == list )
		return MENU_NOTSHOWN;
	
	for( int i = 0; i < 5; i++ ){
		if( 0 == CanUnitUseCombatArt(gActiveUnit, list[i]) )
			continue;
		
		const struct CombatArtInfo* info = GetCombatArtInfo(list[i]);
		u32 range_mask = 0;
		
		if( NULL == info )
			continue;

		// Temperory Set CombatArt flag to make mask
		EnableCombatArtFlag(gActiveUnit, list[i]);
		
		// Make mask
		for( int j = 0; j < UNIT_ITEM_COUNT; j++ )
		{
			u16 item = gActiveUnit->items[j];
			
			if( 0 == (IA_WEAPON & GetItemAttributes(item)) )
				continue;
					
			if( info->weapon_type != GetItemType(item) )
				continue;
					
			if( ITEM_USES(item) < info->cost )
				continue;
			
			range_mask |= ItemRange2Mask(item, gActiveUnit);
		}
		
		
		
		
		// Fill Map
		BmMapFill(gBmMapMovement, NU_MOVE_MAP);
		BmMapFill(gBmMapRange, NU_RANGE_MAP);
		GenerateUnitStandingReachRange(gActiveUnit, range_mask);
		
		// Make Target List
		InitTargets(gActiveUnit->xPos, gActiveUnit->yPos);
		ForEachUnitInRange(AddUnitToTargetListIfNotAllied);
		TryAddTrapsToTargetList();
		
		
		// Temperory Clear CombatArt flag after make mask
		// DisableCombatArtFlag();
		gpBattleFlagExt->isCombat = 0;
		
		if( 0 != GetSelectTargetCount() )
			return MENU_ENABLED;
		
	}
	
	return MENU_NOTSHOWN;
		
	
}


int UMitem_CombatArt_Effect(struct MenuProc* menu, struct MenuItemProc* menu_item ){
	
	struct MenuProc* sub_menu;
	u8 *list = GetCombatArtList(gActiveUnit);
	
	// if unused
	if( (MENU_ENABLED != menu_item->availability) || (NULL == list) )
	{
		MenuFrozenHelpBox(menu, ENUM_msg_umCAGrayBox);
		return MENU_ITEM_NONE;
	}
	
	// set flag
	gpBattleFlagExt->isCombat = 1;
	gpBattleFlagExt->combatArt_id = list[0];
	gpBattleFlagExt->combat_unit = gActiveUnit->index;
	
	// reset Texts & icons
	Text_ResetTileAllocation();	
	ResetIconGraphics_();
	LoadIconPalettes(0x4);
	
	sub_menu = StartOrphanMenu(&Menu_CombatArtSelect);
	
	// Menu Panel
	NewFace(0,GetUnitPortraitId(gActiveUnit),0xB0,0xC,0x2);
	StartMenuPanel_CombatArt(sub_menu, gActiveUnit,0xF,0xB);
	
	return MENU_ACT_CLEAR | MENU_ACT_SND6A | MENU_ACT_END | MENU_ACT_SKIPCURSOR;
}


int UMitem_CombatArt_Hover(struct MenuProc*, struct MenuItemProc*){
	
	u8 *list = GetCombatArtList(gActiveUnit);
	
	if( NULL == list )
		return 0;
	
	// Set CombatArt flag
	EnableCombatArtFlag(gActiveUnit, list[0]);
	
	
	return 0;
}

int UMitem_CombatArt_Unhover(struct MenuProc*, struct MenuItemProc*){
	
	// Clear CombatArt flag
	gpBattleFlagExt->isCombat = 0;
	gpBattleFlagExt->combatArt_id = 0;
	gpBattleFlagExt->combat_unit = 0;
	
	return 0;

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
	
	#define COMBATART_SELECT_ITEM { \
		.name = 0, \
		.nameMsgId = 0, \
		.helpMsgId = 0, \
		.color = MENU_COLOR_BLUE, \
		.overrideId = 0x4E, \
		.isAvailable = CombatArtSelect_Usability, \
		.onDraw = CombatArtSelect_DrawText, \
		.onSelected = CombatArtSelect_Effect, \
		.onIdle = 0, \
		.onSwitchIn = CombatArtSelect_Hover, \
		.onSwitchOut = CombatArtSelect_Unhover, \
	}
	
	[0] = COMBATART_SELECT_ITEM,
	[1] = COMBATART_SELECT_ITEM,
	[2] = COMBATART_SELECT_ITEM,
	[3] = COMBATART_SELECT_ITEM,
	[4] = COMBATART_SELECT_ITEM,
	[5] = {0}
	
	#undef COMBATART_SELECT_ITEM
};

u8 CombatArtSelect_PressB(struct MenuProc* mu, struct MenuItemProc* cmd){

	extern const struct MenuDef gUnitActionMenuDef[];
	
	// clear battle flag
	gpBattleFlagExt->isCombat = 0;
	gpBattleFlagExt->combatArt_id = 0;
	gpBattleFlagExt->combat_unit = 0;
	
	// Menu Panel
	EndMenuPanel_CombatArt();
	
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


void CombatArtSelect_HelpBox(struct MenuProc*, struct MenuItemProc* menu_item){
	
	u8* list = GetCombatArtList(gActiveUnit);
	const struct CombatArtInfo* info = GetCombatArtInfo(list[menu_item->itemNumber]);
	
	if( (NULL == info) || (NULL == list) )
		return;
	
	StartHelpBox(8 * menu_item->xTile, 8 * menu_item->yTile, info->msg_desc);
	
	return;
}



u8 CombatArtSelect_Usability(const struct MenuItemDef*, int number){
	
	extern void ForEachUnitInRange(void*);
	extern void TryAddTrapsToTargetList();
	
	u32 range_mask = 0;
	
	if( NULL == GetCombatArtList(gActiveUnit) )
		return MENU_NOTSHOWN;
	
	u8 ca_index = GetCombatArtList(gActiveUnit)[number];
	
	if( 0 == ca_index )
		return MENU_NOTSHOWN;
	
	const struct CombatArtInfo* info = GetCombatArtInfo(ca_index);
	
	if( NULL == info )
		return 0;
	
	if( 0 == CanUnitUseCombatArt(gActiveUnit, ca_index) )
		return MENU_DISABLED;

	// Temperory Set CombatArt flag to make mask
	EnableCombatArtFlag(gActiveUnit, ca_index);
	
	// Make mask
	for( int i = 0; i < UNIT_ITEM_COUNT; i++ )
	{
		u16 item = gActiveUnit->items[i];
		
		if( 0 == (IA_WEAPON & GetItemAttributes(item)) )
			continue;
				
		if( info->weapon_type != GetItemType(item) )
			continue;
				
		if( ITEM_USES(item) < info->cost )
			continue;
		
		range_mask |= ItemRange2Mask(item, gActiveUnit);
	}
	
	
	
	
	// Fill Map
	BmMapFill(gBmMapMovement, NU_MOVE_MAP);
	BmMapFill(gBmMapRange, NU_RANGE_MAP);
	GenerateUnitStandingReachRange(gActiveUnit, range_mask);
	
	// Make Target List
	InitTargets(gActiveUnit->xPos, gActiveUnit->yPos);
	ForEachUnitInRange(AddUnitToTargetListIfNotAllied);
	TryAddTrapsToTargetList();
	
	
	// Temperory Clear CombatArt flag after make mask
	// DisableCombatArtFlag();
	gpBattleFlagExt->isCombat = 0;
	
	if( 0 == GetSelectTargetCount() )
		return MENU_DISABLED;
	
	return MENU_ENABLED;

}

int CombatArtSelect_DrawText(struct MenuProc* menu, struct MenuItemProc* menu_item){
	
	u8* list = GetCombatArtList(gActiveUnit);
	
	if( NULL == list )
		return 0;
	
	const struct CombatArtInfo* info = GetCombatArtInfo(list[menu_item->itemNumber]);
	
	if( NULL == info )
		return 0;
	
	Text_SetColorId( 
		&menu_item->text, 
		MENU_ENABLED == menu_item->availability
			? MENU_COLOR_NORMAL
			: MENU_COLOR_GRAY );
	
	Text_AppendString(&menu_item->text, GetStringFromIndex(info->msg_name));
	
	Text_Draw(
		&menu_item->text, 
		TILEMAP_LOCATED(gBG0TilemapBuffer, menu_item->xTile + 2, menu_item->yTile) );
	
	DrawIcon(
		TILEMAP_LOCATED(gBG0TilemapBuffer, menu_item->xTile, menu_item->yTile), 
		COMBAT_ART_ICON(list[menu_item->itemNumber]),
		TILEREF(0, 4)
	);
	
	DrawDecNumber(
		TILEMAP_LOCATED(gBG0TilemapBuffer, menu_item->xTile + 0xB, menu_item->yTile),
		MENU_ENABLED == menu_item->availability
			? MENU_COLOR_NORMAL
			: MENU_COLOR_GRAY,
		info->cost
	);
	
	return 0;
}

u8 CombatArtSelect_Effect(struct MenuProc* menu, struct MenuItemProc* menu_item){
	
	struct MenuProc* sub_menu;
	
	// if unused
	if( MENU_ENABLED != menu_item->availability )
	{
		MenuFrozenHelpBox(menu, ENUM_msg_umCAselectGrayBox);
		return MENU_ITEM_NONE;
	}
	
	// reset Texts & icons
	Text_ResetTileAllocation();	
	ResetIconGraphics_();
	LoadIconPalettes(0x4);
	
	// Start new menu
	sub_menu = StartOrphanMenu(&Menu_CombatArt_WeaponSelect);
	
	// Menu Panel
	EndMenuPanel_CombatArt();
	NewFace(0,GetUnitPortraitId(gActiveUnit), 0xB0, 0xC, 0x2);
	ForceMenuItemPanel(sub_menu, gActiveUnit, 0xF, 0xB);
	
	return MENU_ACT_CLEAR | MENU_ACT_SND6A | MENU_ACT_END | MENU_ACT_SKIPCURSOR;
}

int CombatArtSelect_Hover(struct MenuProc* menu, struct MenuItemProc* menu_item){
	
	u8* list = GetCombatArtList(gActiveUnit);
	u32 range_mask = 0;
	
	if( NULL == list )
		return 0;
	
	u8 combatArt_index = list[menu_item->itemNumber];
	const struct CombatArtInfo *info = GetCombatArtInfo(combatArt_index);
	
	if( NULL == info )
		return 0;
	

	// set flag
	EnableCombatArtFlag(gActiveUnit, combatArt_index);
	
	// Make mask
	for( int i = 0; i < UNIT_ITEM_COUNT; i++ )
	{
		u16 item = gActiveUnit->items[i];
		
		if( 0 == (IA_WEAPON & GetItemAttributes(item)) )
			continue;
				
		if( info->weapon_type != GetItemType(item) )
			continue;
				
		if( ITEM_USES(item) < info->cost )
			continue;
		
		range_mask |= ItemRange2Mask(item, gActiveUnit);
	}
	
	
	// Fill Map
	BmMapFill(gBmMapMovement, NU_MOVE_MAP);
	BmMapFill(gBmMapRange, NU_RANGE_MAP);
	GenerateUnitStandingReachRange(gActiveUnit, range_mask);
	DisplayMoveRangeGraphics(RNG_RED);
	
	
	// Menu Panel
	if( NULL == Proc_Find(gProc_MenuItemPanel) )
	{
		NewFace(0,GetUnitPortraitId(gActiveUnit), 0xB0, 0xC, 0x2);
		StartMenuPanel_CombatArt(menu, gActiveUnit, 0xF, 0xB);
	}
	
	UpdateMenuPanel_CombatArt(info);
	
	return 0;
}



int CombatArtSelect_Unhover(struct MenuProc*, struct MenuItemProc*){
	
	// Fill Map
	BmMapFill(gBmMapMovement, NU_MOVE_MAP);
	BmMapFill(gBmMapRange, NU_RANGE_MAP);
	
	return 0;
}






// ================================
//   CombatArt Weapon Select Menu
// ================================

static u8 CombatArt_WeaponSelect_PressB(struct MenuProc*, struct MenuItemProc*);
static u8 CombatArtWeaponSelect_Usability(const struct MenuItemDef*, int number);
static u8 CombatArtWeaponSelect_Effect(struct MenuProc*, struct MenuItemProc*);


const struct MenuDef Menu_CombatArt_WeaponSelect = {
	.rect 	= {1, 1, 0xE, 0},
	.style 	= 0,
	.menuItems = MenuItems_CombatArt_WeaponSelect,
	.onInit = 0,
	.onEnd = 0,
	._u14 = 0,
	.onBPress = CombatArt_WeaponSelect_PressB,
	.onRPress = MenuAutoHelpBoxSelect,
	.onHelpBox = ConvoyMenu_HelpBox,
};






const struct MenuItemDef MenuItems_CombatArt_WeaponSelect[] = {
	
	#define COMBATART_WEAPONSELECT_ITEM { 					\
		.name = 0, 											\
		.nameMsgId = 0, 									\
		.helpMsgId = 0, 									\
		.color = MENU_COLOR_NORMAL, 						\
		.overrideId = 0x49, 								\
		.isAvailable = CombatArtWeaponSelect_Usability, 	\
		.onDraw = UnknownMenu_Draw, 						\
		.onSelected = CombatArtWeaponSelect_Effect, 		\
		.onIdle = 0, 										\
		.onSwitchIn = UnknownMenu_SwitchIn, 				\
		.onSwitchOut = BallistaRangeMenu_SwitchOut, 		\
	}
	
	[0] = COMBATART_WEAPONSELECT_ITEM,
	[1] = COMBATART_WEAPONSELECT_ITEM,
	[2] = COMBATART_WEAPONSELECT_ITEM,
	[3] = COMBATART_WEAPONSELECT_ITEM,
	[4] = COMBATART_WEAPONSELECT_ITEM,
	[5] = {0}
	
	#undef COMBATART_WEAPONSELECT_ITEM
};


u8 CombatArt_WeaponSelect_PressB(struct MenuProc*, struct MenuItemProc*){
	
	// Reset Text & Dsiplay
	Text_ResetTileAllocation();
	BG_Fill(gBG2TilemapBuffer, 0);
	BG_EnableSyncByMask(0b100);
	ResetIconGraphics_();
	LoadIconPalettes(0x4);
	
	// Reset Menu
	StartOrphanMenu(&Menu_CombatArtSelect);
	
	// Reset map works
	HideMoveRangeGraphics();
	
	return MENU_ACT_ENDFACE | MENU_ACT_CLEAR | MENU_ACT_SND6B | MENU_ACT_END | MENU_ACT_SKIPCURSOR;
	
}
u8 CombatArtWeaponSelect_Usability(const struct MenuItemDef*, int number){
	
	u16 item = gActiveUnit->items[number];

	const struct CombatArtInfo *info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	if( 0 == ITEM_USES(item) )
		return MENU_NOTSHOWN;
	
	if( (info->weapon_type != GetItemType(item)) || (0 == (IA_WEAPON & GetItemAttributes(item))) )
		return MENU_NOTSHOWN;
	
	if( ITEM_USES(item) < info->cost )
		return MENU_DISABLED;
	
	if( 0 == CanUnitUseWeapon(gActiveUnit, item) )
		return MENU_DISABLED;

	MakeTargetListForWeapon(gActiveUnit, item);
			
	if( 0 != GetSelectTargetCount() )
		return MENU_ENABLED;
	else
		return MENU_DISABLED;
	
}




u8 CombatArtWeaponSelect_Effect(struct MenuProc* menu, struct MenuItemProc* menu_item){
	
	u16 weapon = gActiveUnit->items[menu_item->itemNumber];
	
	EquipUnitItemSlot(gActiveUnit, menu_item->itemNumber);
	ClearBg0Bg1();
	MakeTargetListForWeapon(gActiveUnit, weapon);
	
	// reworked a new CTS
	StartCombatTargetSelection(&TargetSelectInfo_CombatArt);
	
	return MENU_ACT_ENDFACE | MENU_ACT_CLEAR | MENU_ACT_SND6A | MENU_ACT_END | MENU_ACT_SKIPCURSOR;
}


// ================================
//     CombatArt target select
// ================================

extern void NewBattleForecast(ProcPtr proc);
extern void sub_8022F10(ProcPtr proc);
extern void sub_8022E8C(ProcPtr proc, struct SelectTarget* target);
extern u8 sub_8022DF0(ProcPtr proc, struct SelectTarget* target);
extern u8 sub_80373F0(ProcPtr proc, struct SelectTarget* target);

static u8 CombatArt_TargetSelect_OnCancel(ProcPtr proc, struct SelectTarget* target);

const struct SelectInfo TargetSelectInfo_CombatArt = {
	
	.onInit = NewBattleForecast,
	.onEnd = sub_8022F10,
	.onUnk08 = 0,
	.onSwitchIn = sub_8022E8C,
	.onSwitchOut = 0,
	.onSelect = sub_8022DF0,
	.onCancel = CombatArt_TargetSelect_OnCancel,
	.onHelp = sub_80373F0,
};

u8 CombatArt_TargetSelect_OnCancel(ProcPtr proc, struct SelectTarget* target){
	
	if( EventEngineExists() )
		return TSE_NONE;
	
	Proc_Start(ProcCmd_CombatArt_PostTargetSelect, PROC_TREE_3);
	return TSE_PLAY_BOOP | TSE_END | TSE_DISABLE;
}





// =================================
// CombatArt post target select proc
// =================================

extern void sub_8022E38();
extern struct ProcCmd gProc_BkSel[], gProc_CameraMovement[];
static void RebuildCombatArtWeaponSelectMenu(ProcPtr proc);

const struct ProcCmd ProcCmd_CombatArt_PostTargetSelect[] = {
	
	PROC_NAME			("PROC_COMBATART_POST_TARGETSELECT"),
	PROC_CALL			(AddSkipThread2),
	PROC_CALL			(sub_8022E38),
	PROC_WHILE_EXISTS 	(gProc_BkSel),
	PROC_WHILE_EXISTS 	(gProc_CameraMovement),
	PROC_YIELD,
	PROC_CALL			(RebuildCombatArtWeaponSelectMenu),
	PROC_YIELD,
	PROC_CALL			(SubSkipThread2),
	PROC_END,
};


void RebuildCombatArtWeaponSelectMenu(ProcPtr proc){
	
	extern const struct MenuDef gUnknownMenuDef; // sub-attack menu
	const struct MenuDef* mu_def;
	
	// Reset Text & Dsiplay
	Text_ResetTileAllocation();
	BG_Fill(gBG2TilemapBuffer, 0);
	BG_EnableSyncByMask(0b100);
	
	// Reset Menu
	if( (gpBattleFlagExt->isCombat) )
		mu_def = &Menu_CombatArt_WeaponSelect;
	else
		mu_def = &gUnknownMenuDef;
	
	struct MenuProc* menu = StartOrphanMenu(mu_def);
	
	// Reset map works
	HideMoveRangeGraphics();
	
	// Menu Panel
	NewFace(0,GetUnitPortraitId(gActiveUnit), 0xB0, 0xC, 0x2);
	ForceMenuItemPanel(menu, gActiveUnit, 0xF, 0xB);
}




