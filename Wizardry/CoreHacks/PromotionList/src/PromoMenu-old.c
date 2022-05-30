#include "gbafe.h"
#include "Promotion.h"
#include "promo-rework.h"

// =========================================================
//                             Menu
// =========================================================

static u8 NewPromoCmd_Usability(const struct MenuItemDef*, int number);
static int NewPromoCmd_DrawText(struct MenuProc*, struct MenuItemProc*);
static u8 NewPromoCmd_Effect(struct MenuProc*, struct MenuItemProc*);
static int NewPromoCmd_Hover(struct MenuProc*, struct MenuItemProc*);

const struct MenuItemDef MenuItems_NewPromotion[] = {
	
	#define PROMO_SELECT_ITEM(i) { \
		.name = 0, \
		.nameMsgId = 0, \
		.helpMsgId = 0, \
		.color = TEXT_COLOR_NORMAL, \
		.overrideId = i, \
		.isAvailable = NewPromoCmd_Usability, \
		.onDraw = NewPromoCmd_DrawText, \
		.onSelected = NewPromoCmd_Effect, \
		.onIdle = 0, \
		.onSwitchIn = NewPromoCmd_Hover, \
	}
	
	[0] = PROMO_SELECT_ITEM(0),
	[1] = PROMO_SELECT_ITEM(1),
	[2] = PROMO_SELECT_ITEM(2),
	[3] = PROMO_SELECT_ITEM(3),
	[4] = PROMO_SELECT_ITEM(4),
	[5] = {0}
	
	#undef PROMO_SELECT_ITEM
};


u8 NewPromoCmd_Usability(const struct MenuItemDef*, int number){
	
	return number < 2 ? MENU_ENABLED : MENU_NOTSHOWN;
}


int NewPromoCmd_DrawText(struct MenuProc* menu, struct MenuItemProc* menu_item){
	
	static void (*DrawClassNamePromoMenuItem)(struct MenuProc*, struct MenuItemProc*, char* str) = (const void*)0x80CDC49;
	
	struct Proc_PromoMenuSelect* parent = menu->proc_parent;
	struct Proc_PromoDisp* GrandFa = parent->proc_parent;
	u16 classId = GrandFa->promotedClassIds[menu_item->itemNumber];
	const struct ClassData *class = GetClassData(classId);
	
	DrawClassNamePromoMenuItem(
		menu,
		menu_item,
		GetStringFromIndex( class->nameTextId )
	);
	
	return 0;
}



u8 NewPromoCmd_Effect(struct MenuProc* menu, struct MenuItemProc* menu_item){
	
	struct Proc_PromoMenuSelect* parent = menu->proc_parent;
	struct Proc_PromoDisp* procDisp = parent->proc_parent;
	struct Proc_PromoMain* procMain = procDisp->proc_parent;
	
	if( 0 != procDisp->state )
		return 0;
	
	struct Unit* unit = GetUnitFromCharId(procDisp->charId);
	procMain->promoClass = procDisp->promotedClassIds[menu_item->itemNumber];
	
	switch(procMain->promoClass){
		case CLASS_RANGER:
		case CLASS_RANGER_F:
			TryRemoveUnitFromBallista(unit);
			break;
			
		default:
			break;
	}
	
	EndMenu(menu);
	
	extern void EndAllProcChildren(ProcPtr);
	extern void sub_80CCBD4();
	
	EndAllProcChildren(procMain);
	sub_80CCBD4();
	
	Proc_Goto(procMain, 0x5);
	return MENU_ACT_SKIPCURSOR | MENU_ACT_END | MENU_ACT_SND6A;
}



int NewPromoCmd_Hover(struct MenuProc* menu, struct MenuItemProc* menu_item){
	struct Proc_PromoMenuSelect* parent = menu->proc_parent;
	struct Proc_PromoDisp* procDisp = parent->proc_parent;
	extern void ChangePromotionClassDescText(u16 msg);
	extern void Dialogue_SetCharacterDisplayDelay(int time);
	
	procDisp->state = 1;
	procDisp->selectedOptionIndex = menu_item->itemNumber;
	ChangePromotionClassDescText( procDisp->promotedClassDescIds[menu_item->itemNumber] );
	Dialogue_SetCharacterDisplayDelay(-1);
	return 0;
}