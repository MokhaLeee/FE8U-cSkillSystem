#include "gbafe-chax.h"


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








// Item Menu
s8 CanUnitUseStatGainItem(struct Unit* unit, int item)
{
	extern struct Unit gStatGainSimUnit;
	
	s8 result;

	const struct ItemStatBonuses* bonuses = GetItemStatBonuses(item);

	ClearUnit(&gStatGainSimUnit);

	gStatGainSimUnit.pCharacterData = unit->pCharacterData;
	gStatGainSimUnit.pClassData     = unit->pClassData;

	gStatGainSimUnit.maxHP = unit->maxHP + bonuses->hpBonus;
	gStatGainSimUnit.pow = unit->pow + bonuses->powBonus;
	gStatGainSimUnit.skl = unit->skl + bonuses->sklBonus;
	gStatGainSimUnit.spd = unit->spd + bonuses->spdBonus;
	gStatGainSimUnit.def = unit->def + bonuses->defBonus;
	gStatGainSimUnit.res = unit->res + bonuses->resBonus;
	gStatGainSimUnit.lck = unit->lck + bonuses->lckBonus;
	gStatGainSimUnit.movBonus = unit->movBonus + bonuses->movBonus;
	gStatGainSimUnit.conBonus = unit->conBonus + bonuses->conBonus;
	
	*GetMagAt(&gStatGainSimUnit) = 
		*GetMagAt(&gStatGainSimUnit) + ((u8*)bonuses)[9];
	
	UnitCheckStatCaps(&gStatGainSimUnit);

	result = gStatGainSimUnit.maxHP != unit->maxHP;

	if (gStatGainSimUnit.pow != unit->pow)
		result = TRUE;

	if (gStatGainSimUnit.skl != unit->skl)
		result = TRUE;

	if (gStatGainSimUnit.spd != unit->spd)
		result = TRUE;

	if (gStatGainSimUnit.def != unit->def)
		result = TRUE;

	if (gStatGainSimUnit.res != unit->res)
		result = TRUE;

	if (gStatGainSimUnit.lck != unit->lck)
		result = TRUE;

	if (gStatGainSimUnit.movBonus != unit->movBonus)
		result = TRUE;

	if (gStatGainSimUnit.conBonus != unit->conBonus)
		result = TRUE;
	
	if (*GetMagAt(&gStatGainSimUnit) != *GetMagAt(unit))
		result = TRUE;

	return result;
}





















// prep
// in prep-item.c
