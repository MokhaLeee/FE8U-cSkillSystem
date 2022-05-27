#include "gbafe-chax.h"

extern void ExecStandardHeal(ProcPtr);
extern void ExecFortify(ProcPtr);
extern void ExecRestore(ProcPtr);
extern void ExecStatusStaff(ProcPtr);
extern void ExecWarpStaff(ProcPtr);
extern void ExecRescueStaff(ProcPtr);
extern void ExecTorchStaff(ProcPtr);
extern void ExecHammerne(ProcPtr);
extern void ExecUnlock(ProcPtr);
static const uint32_t ExecBarrierStaff = 0x802EC8D;
void ExecStatBooster(ProcPtr);
extern void StartMapPromotion(ProcPtr);
static const uint32_t ActionDoorChest = 0x802F511;
extern void ExecSomeSelfHeal(ProcPtr, int heal_amount);
static const uint32_t ExecItemElixir = 0x802F3E5;
static const uint32_t ExecItemPureWater = 0x802F451;
static const uint32_t ExecItemAntitoxin = 0x802F4D1;
static const uint32_t ExecItemTorch = 0x802F48D;
extern void ExecItemMine(ProcPtr);
static const uint32_t ExecItemLightRune = 0x802FA91;
static const uint32_t ExecDanceRing = 0x802FBBD;
extern void ExecLatona(ProcPtr);
static const uint32_t ExecNightmareStaff = 0x802F1D9;
static const uint32_t ExecItemJunaFruit = 0x802F9E1;


static void ItemAct_Promotion(ProcPtr);
static void ItemAct_Vulnerary(ProcPtr);


typedef void (*ItemAct_t)(ProcPtr);

// On Modular
const ItemAct_t ItemActionEffectTable[0xFF] = {
	
	// Staves
	[ITEM_STAFF_HEAL] = ExecStandardHeal,
	[ITEM_STAFF_MEND] = ExecStandardHeal,
	[ITEM_STAFF_RECOVER] = ExecStandardHeal,
	[ITEM_STAFF_PHYSIC] = ExecStandardHeal,
	
	[ITEM_STAFF_FORTIFY] = ExecFortify,
	[ITEM_STAFF_RESTORE] = ExecRestore,
	
	[ITEM_STAFF_SILENCE] = ExecStatusStaff,
	[ITEM_STAFF_SLEEP] = ExecStatusStaff,
	[ITEM_STAFF_BERSERK] = ExecStatusStaff,
	
	[ITEM_STAFF_WARP] = ExecWarpStaff,
	[ITEM_STAFF_RESCUE] = ExecRescueStaff,
	[ITEM_STAFF_TORCH] = ExecTorchStaff,
	[ITEM_STAFF_REPAIR] = ExecHammerne,
	[ITEM_STAFF_UNLOCK] = ExecUnlock,
	[ITEM_STAFF_BARRIER] = (ItemAct_t) ExecBarrierStaff,
	
	// Stat boosters
	[ITEM_BOOSTER_HP] = ExecStatBooster,
	[ITEM_BOOSTER_POW] = ExecStatBooster,
	[ITEM_BOOSTER_SKL] = ExecStatBooster,
	[ITEM_BOOSTER_SPD] = ExecStatBooster,
	[ITEM_BOOSTER_LCK] = ExecStatBooster,
	[ITEM_BOOSTER_DEF] = ExecStatBooster,
	[ITEM_BOOSTER_RES] = ExecStatBooster,
	[ITEM_BOOSTER_MOV] = ExecStatBooster,
	[ITEM_BOOSTER_CON] = ExecStatBooster,
	
	// Promotion items
	[ITEM_HEROCREST] = ItemAct_Promotion,
	[ITEM_KNIGHTCREST] = ItemAct_Promotion,
	[ITEM_ORIONSBOLT] = ItemAct_Promotion,
	[ITEM_ELYSIANWHIP] = ItemAct_Promotion,
	[ITEM_GUIDINGRING] = ItemAct_Promotion,
	
	// items
	[ITEM_CHESTKEY] = (ItemAct_t) ActionDoorChest,
	[ITEM_DOORKEY] = (ItemAct_t) ActionDoorChest,
	[ITEM_LOCKPICK] = (ItemAct_t) ActionDoorChest,
	
	[ITEM_VULNERARY] = ItemAct_Vulnerary,
	[ITEM_ELIXIR] = (ItemAct_t) ExecItemElixir,
	[ITEM_PUREWATER] = (ItemAct_t) ExecItemPureWater,
	[ITEM_ANTITOXIN] = (ItemAct_t) ExecItemAntitoxin,
	[ITEM_TORCH] = (ItemAct_t) ExecItemTorch,
	
	[ITEM_CHESTKEY_BUNDLE] = (ItemAct_t) ActionDoorChest,
	[ITEM_MINE] = ExecItemMine,
	[ITEM_LIGHTRUNE] = (ItemAct_t) ExecItemLightRune,
	
	// Dance Ring
	[ITEM_FILLAS_MIGHT] = (ItemAct_t) ExecDanceRing,
	[ITEM_NINISS_GRACE] = (ItemAct_t) ExecDanceRing,
	[ITEM_THORS_IRE] = (ItemAct_t) ExecDanceRing,
	[ITEM_SETS_LITANY] = (ItemAct_t) ExecDanceRing,
	
	[ITEM_MASTERSEAL] = ItemAct_Promotion,
	[ITEM_METISSTOME] = ExecStatBooster,
	[ITEM_HEAVENSEAL] = ItemAct_Promotion,
	
	[ITEM_STAFF_LATONA] = ExecLatona,
	
	[ITEM_OCEANSEAL] = ItemAct_Promotion,
	[ITEM_LUNARBRACE] = ItemAct_Promotion,
	[ITEM_SOLARBRACE] = ItemAct_Promotion,
	
	[ITEM_VULNERARY_2] = ItemAct_Vulnerary,
	[ITEM_NIGHTMARE] = (ItemAct_t) ExecNightmareStaff,
	
	[ITEM_JUNAFRUIT] = (ItemAct_t) ExecItemJunaFruit,
	[ITEM_UNK_C1] = ItemAct_Promotion,
};

// 802FC49
void ActionStaffDoorChestUseItem(ProcPtr proc) {
	extern struct ProcCmd CONST_DATA sProcScr_ExecNightmareStaff[], sProcScr_SetTargetStatus[];
	
	ItemAct_t it;
	
	uint16_t  item = 
		GetUnit(gActionData.subjectIndex)->items[gActionData.itemSlotIndex];
	
	it = ItemActionEffectTable[ITEM_ID(item)];
	
	if( NULL == it )
		goto goto_return;
	
	// if is not pointer, then it should be msg_id, then start simple effect
	if ( IsItemEffectSimple(it) ) {
		
		struct Proc_ItemSimple* child 
			= (struct Proc_ItemSimple*)Proc_StartBlocking(gProc_ActionItemSimpleEffect, proc);
		
		child->effect = ItemSimpleEffectFilter(it);
		child->str = GetStringFromIndex((u32)ItemMenuEffectTable[ITEM_ID(item)]);
		child->item = item;
		child->unit = GetUnit(gActionData.subjectIndex);
		
		goto goto_return;
	}
	else
		it(proc);
	
goto_return:
	// fking nightmare ...
	if ( ITEM_NIGHTMARE == ITEM_ID(item) )
		Proc_StartBlocking(sProcScr_ExecNightmareStaff, proc);
	
	else if ( !(gBattleTarget.statusOut & (1 << 7)) ) // todo
		Proc_StartBlocking(sProcScr_SetTargetStatus, proc);
	
}






// 
void ExecStatBooster(ProcPtr proc) {
	
	static void (*DrawMapItemEffectPopUp)(ProcPtr, u16 icon_id, char* str) = (const void*)0x801F9FD;
	extern u16 ApplyStatBoosterAndGetMessageId(struct Unit*, int item_slot); // 0x802F809
	
	struct Unit* unit = GetUnit(gActionData.subjectIndex);
	u16 item = unit->items[gActionData.itemSlotIndex];
	
	gBattleTarget.statusOut = -1;
	ApplyStatBoosterAndGetMessageId(unit, gActionData.itemSlotIndex);
	
	// Play sound
	if( 0 == gRAMChapterData.unk41_8)
		m4aSongNumStart(0x5A);
	
	// Put Popup
	DrawMapItemEffectPopUp( proc, GetItemIconId(item), GetStringFromIndex(ENUM_msg_ItemUnitStatusUp));
	
}



// 0x802F809
u16 ApplyStatBoosterAndGetMessageId(struct Unit* unit, int item_slot){
	
	u16 item;
	const struct ItemStatBonuses* it;

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
	
	// For Magic
	*GetMagAt(unit) += ((s8*)it)[9];
	
	UnitCheckStatCaps(unit);
	UnitUpdateUsedItem(unit, item_slot);
	
	// Now we don't rely on this message id
	return 0;
}




static void ItemAct_Promotion(ProcPtr proc) { 
	
	// 0x802FEEC
	uint16_t item, *tmp;
	struct Unit* unit;
	
	
	unit = GetUnit(gActionData.subjectIndex);
	
	item = unit->items[gActionData.itemSlotIndex];
	gBattleTarget.weaponBefore = item;
	gBattleActor.weaponBefore = item;
	
	item = GetUnitEquippedWeapon(unit);
	gBattleTarget.weapon = item;
	gBattleActor.weapon = item;
	
	// // last item id = -1
	tmp = &gBattleTarget.unit.items[UNIT_ITEM_COUNT];
	*( (s8*)tmp - 1) = -1;
	
	StartMapPromotion(proc);
}

static void ItemAct_Vulnerary(ProcPtr proc){
	
	// 0x802FEC4
	ExecSomeSelfHeal(proc, 10);
}
