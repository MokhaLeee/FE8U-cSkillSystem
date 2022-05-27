#include "gbafe-chax.h"

static void (*DrawPrepScreenItemUseItems)(void*, struct TextHandle*, struct Unit*, int) = (const void*) 0x809B74C+1;
static void (*PrepScreenItemUseScreen_Init_ShowHand) (int, int, int, int) = (const void*) 0x80AD51D;
extern void sub_807EE74(ProcPtr); // end APs
static const void (*PrepItemProc_HandleItemMsgPopUp)(int, int, int, int, int) = (const void*) 0x809A31D;
static void (*ProcPrepItem_807EDF8)(int, int, int, ProcPtr) = (const void*) 0x807EDF9;
static void (*AP_80ACA84)(int) = (const void*) 0x80ACA85;
static void (*AP_807EE74)(void) = (const void*) 0x807EE75;


static void PrepSimpleItemProc_OnEnd(struct Proc_ItemSimple*);
static void PrepSimpleItemProc_OnInit(struct Proc_ItemSimple*);
static void PrepSimpleItemProc_OnIdle(struct Proc_ItemSimple*);
static void ActionSimpleItemProc_ExecEffect(struct Proc_ItemSimple*);

// ========================================
// 					Lib Func
// ========================================
int IsItemEffectSimple(void* func){
	
	const u32 raw = (u32)(func);
	return (raw >> 28) ? 1 : 0;
	
}


const void* ItemSimpleEffectFilter(void* func){
	
	const u32 raw = (u32)(func);
	const void* result = (const void*)(raw & 0xFFFFFFF);

	return result;
	
}














// ========================================
// 				Prep Proc
// ========================================
const struct ProcCmd gProc_PrepItemSimpleEffect[] = {
	
	PROC_SET_END_CB(PrepSimpleItemProc_OnEnd),
	PROC_YIELD,
	PROC_CALL(PrepSimpleItemProc_OnInit),
	PROC_YIELD,
	PROC_REPEAT(PrepSimpleItemProc_OnIdle),
	PROC_YIELD,
	PROC_END,
	
};




static void PrepSimpleItemProc_OnInit(struct Proc_ItemSimple* proc){
	
	char* str;
	struct TextHandle* th;
	struct Proc_PrepItemUse* parent;
	int icon_id;
	
	const int x = 0xE;
	const int y = 0xF;
	
	parent = (struct Proc_PrepItemUse*) proc->proc_parent;
	
	ProcPrepItem_807EDF8(0x1C0,3,0,parent);
	
	if ( _IsPointer((u32)proc->effect) )
		proc->effect(proc->unit, proc->item);
	
	UnitUpdateUsedItem(proc->unit, parent->item_slot);
	
	str = (NULL == proc->str)
		? GetStringFromIndex(ENUM_msg_ItemEffectApplied)
		: proc->str;
	
	icon_id = GetItemIconId(proc->item);
	
	if ( 0 != icon_id )
		DrawIcon(
			TILEMAP_LOCATED(gBG2TilemapBuffer, x, y),
			GetItemIconId(proc->item), 0x4000);
			
	th = &gStatScreen.text[4];
	
	Text_Clear(th);
	
	DrawTextInline(
		th, TILEMAP_LOCATED(gBG2TilemapBuffer, (0 == icon_id)?0:2 + x, y ),
		TEXT_COLOR_NORMAL, 0, 0, str);
	
	proc->x = x * 8 - 4;
	proc->y = y * 8 - 4;
	proc->height = 2;
	proc->width = 
		(GetStringTextWidth(str) + ((0 == icon_id)?0:3) ) / 8 + 2;
	
	BG_EnableSyncByMask(0b100);
	proc->timer = 0x78;
	
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x5A);
}


static void PrepSimpleItemProc_OnIdle(struct Proc_ItemSimple* proc) {
	
	PrepItemProc_HandleItemMsgPopUp(
		proc->x,
		proc->y,
		proc->width,
		proc->height,
		0xA440
	);
	
	if ( 0 != (--proc->timer) )
		if ( 0 == ((A_BUTTON + B_BUTTON) & gKeyStatusPtr->newKeys) )
			return;
	
	Proc_Break(proc);
}


static void PrepSimpleItemProc_OnEnd(struct Proc_ItemSimple* proc) {
	
	struct Proc_PrepItemUse* parent;
	int item_count;
	
	parent = (struct Proc_PrepItemUse*) proc->proc_parent;
	item_count = GetUnitItemCount( parent->unit );
	
	TileMap_FillRect( TILEMAP_LOCATED(gBG2TilemapBuffer, 14, 15), 14, 1, 0);
	
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
	AP_807EE74();
	
	BG_EnableSyncByMask(0b101);
	LoadDialogueBoxGfx(BG_CHAR_ADDR(5), -1);
}














// ========================================
// 				Action Effect
// ========================================

const struct ProcCmd gProc_ActionItemSimpleEffect[] = {
	PROC_YIELD,
	PROC_CALL (ActionSimpleItemProc_ExecEffect),
	PROC_YIELD,
	PROC_END,
	
};

static void ActionSimpleItemProc_ExecEffect(struct Proc_ItemSimple* proc){
	
	static void (*DrawMapItemEffectPopUp)(ProcPtr, u16 icon_id, char* str) = (const void*)0x801F9FD;
	struct Proc_PrepItemUse* parent;
	
	
	// Exec effect
	if ( _IsPointer((u32)proc->effect) )
		proc->effect(proc->unit, proc->item);
	
	parent = (struct Proc_PrepItemUse*) proc->proc_parent;
	
	UnitUpdateUsedItem(
		proc->unit, 
		parent->item_slot);
	
	
	// Play sound
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x5A);
	
	
	// Put Popup
	DrawMapItemEffectPopUp(
		proc,
		GetItemIconId(proc->item),
		(0 == proc->str)
			? GetStringFromIndex(ENUM_msg_ItemEffectApplied)
			: proc->str
	);
	
}
