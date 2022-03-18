#include "gbafe-chax.h"

void DoPrepEff_Booster(struct Proc_PrepItemUse*, uint16_t item);
static void DoPrepEff_Promote(struct Proc_PrepItemUse* proc, uint16_t item);
static void DoPrepEff_JunaFruit(struct Proc_PrepItemUse* proc, uint16_t item);

static int PrepUsa_MetiStome(struct Unit* unit, uint16_t item);



typedef int (*PrepUsaFunc_t)(struct Unit*, uint16_t item);

const PrepUsaFunc_t ItemPrepUsabilityTable[0xFF] = {
	[ITEM_BOOSTER_HP] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	[ITEM_BOOSTER_POW] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	[ITEM_BOOSTER_SKL] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	[ITEM_BOOSTER_SPD] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	[ITEM_BOOSTER_LCK] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	[ITEM_BOOSTER_DEF] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	[ITEM_BOOSTER_RES] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	[ITEM_BOOSTER_MOV] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	[ITEM_BOOSTER_CON] = (PrepUsaFunc_t)CanUnitUseStatGainItem,
	
	[ITEM_HEROCREST] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_KNIGHTCREST] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_ORIONSBOLT] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_ELYSIANWHIP] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_GUIDINGRING] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_MASTERSEAL] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_HEAVENSEAL] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_OCEANSEAL] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_LUNARBRACE] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_SOLARBRACE] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	[ITEM_UNK_C1] = (PrepUsaFunc_t)CanUnitUsePromotionItem,
	
	[ITEM_METISSTOME] = PrepUsa_MetiStome,
	[ITEM_JUNAFRUIT] = (PrepUsaFunc_t)CanUnitUseFruitItem,
	
};
	

int8_t CanUnitUseItemPrepScreen(struct Unit* unit, int item)
{
	PrepUsaFunc_t it = ItemPrepUsabilityTable[ITEM_ID(item)];
	
	if ( NULL == it )
		return 0;

	return it(unit, item);
}


static int PrepUsa_MetiStome(struct Unit* unit, uint16_t item) {
	
	return !(unit->state & US_GROWTH_BOOST);
}







typedef void (*PrepEffFunc_t)(struct Proc_PrepItemUse*, uint16_t item);

const PrepEffFunc_t ItemPrepEffectTable[0xFF] = {
	
	[ITEM_BOOSTER_HP] = DoPrepEff_Booster,
	[ITEM_BOOSTER_POW] = DoPrepEff_Booster,
	[ITEM_BOOSTER_SKL] = DoPrepEff_Booster,
	[ITEM_BOOSTER_SPD] = DoPrepEff_Booster,
	[ITEM_BOOSTER_LCK] = DoPrepEff_Booster,
	[ITEM_BOOSTER_DEF] = DoPrepEff_Booster,
	[ITEM_BOOSTER_RES] = DoPrepEff_Booster,
	[ITEM_BOOSTER_MOV] = DoPrepEff_Booster,
	[ITEM_BOOSTER_CON] = DoPrepEff_Booster,
	
	[ITEM_HEROCREST] = DoPrepEff_Promote,
	[ITEM_KNIGHTCREST] = DoPrepEff_Promote,
	[ITEM_ORIONSBOLT] = DoPrepEff_Promote,
	[ITEM_ELYSIANWHIP] = DoPrepEff_Promote,
	[ITEM_GUIDINGRING] = DoPrepEff_Promote,
	[ITEM_MASTERSEAL] = DoPrepEff_Promote,
	[ITEM_HEAVENSEAL] = DoPrepEff_Promote,
	[ITEM_OCEANSEAL] = DoPrepEff_Promote,
	[ITEM_LUNARBRACE] = DoPrepEff_Promote,
	[ITEM_SOLARBRACE] = DoPrepEff_Promote,
	[ITEM_UNK_C1] = DoPrepEff_Promote,
	
	[ITEM_METISSTOME] = DoPrepEff_Booster,
	[ITEM_JUNAFRUIT] = DoPrepEff_JunaFruit,
};


// static const uint32_t PrepScreenItemUseScreen_HandleItemEffect = 0x809CB39;
void PrepScreenItemUseScreen_HandleItemEffect (struct Proc_PrepItemUse* proc) {
	
	uint16_t item = proc->unit->items[proc->item_slot];
	
	PrepEffFunc_t it = ItemPrepEffectTable[ITEM_ID(item)];
	
	if ( NULL == it )
		return;
	
	
	// if is not pointer, then it should be msg_id, then start simple effect
	
	if ( IsItemEffectSimple(it) ) {
		
		struct Proc_ItemSimple* child 
			= (struct Proc_ItemSimple*)Proc_StartBlocking(gProc_PrepItemSimpleEffect, proc);
		
		child->effect = ItemSimpleEffectFilter(it);
		child->str = GetStringFromIndex((u32)ItemMenuEffectTable[ITEM_ID(item)]);
		child->item = item;
		child->unit = proc->unit;
		return;
	}
		
	
	it(proc, item);
}



void DoPrepEff_Booster(struct Proc_PrepItemUse* proc, uint16_t item) {
	
	extern const struct ProcCmd _gProc_StatScreenItemStatBoosterEffect[]; // 0x8A191A4
	
	if ( GetItemStatBonuses(item) )
		Proc_StartBlocking(_gProc_StatScreenItemStatBoosterEffect, proc);
	
}


void DoPrepEff_Promote(struct Proc_PrepItemUse* proc, uint16_t item) {
	
	if ( CanUnitUsePromotionItem(proc->unit, item) ) {
		
		// case promotion:
		if( 0 == gRAMChapterData.unk41_8)
			m4aSongNumStart(0x6A);
		
		Proc_Goto(proc, PROC_LABEL_PREPITEM_PROMOTE);
	}
	
}


static void DoPrepEff_JunaFruit(struct Proc_PrepItemUse* proc, uint16_t item) {
	
	extern const struct ProcCmd _gProc_StatScreenItemJunaFruitEffect[]; // 0x8A191C4
	
	Proc_StartBlocking(_gProc_StatScreenItemJunaFruitEffect, proc);
	
}
