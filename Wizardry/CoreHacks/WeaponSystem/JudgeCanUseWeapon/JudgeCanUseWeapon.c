#include "gbafe-chax.h"



// Hack

s8 CanUnitUseWeapon(struct Unit* unit, int item) {
	if (item == 0)
		return FALSE;

	if (!(GetItemAttributes(item) & IA_WEAPON))
		return FALSE;

	if (GetItemAttributes(item) & IA_LOCK_ANY) {
		// Check for item locks

		if ((GetItemAttributes(item) & IA_LOCK_1) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_1))
			return FALSE;

		if ((GetItemAttributes(item) & IA_LOCK_4) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_4))
			return FALSE;

		if ((GetItemAttributes(item) & IA_LOCK_5) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_5))
			return FALSE;

		if ((GetItemAttributes(item) & IA_LOCK_6) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_6))
			return FALSE;

		if ((GetItemAttributes(item) & IA_LOCK_7) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_7))
			return FALSE;

		if ((GetItemAttributes(item) & IA_LOCK_2) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_2))
			return FALSE;

        // Monster lock is special
		if (GetItemAttributes(item) & IA_LOCK_3) {
			if (!(UNIT_CATTRIBUTES(unit) & CA_LOCK_3))
				return FALSE;

			return TRUE;
		}

		if (GetItemAttributes(item) & IA_UNUSABLE)
			if (!(IsItemUnsealedForUnit(unit, item)))
				return FALSE;
	}

	if (unit->statusIndex == UNIT_STATUS_SILENCED)
		if (GetItemAttributes(item) & IA_MAGIC)
			return FALSE;
	
	return GetWExp(unit, GetItemType(item)) >= GetItemRequiredExp(item);

}


s8 CanUnitUseStaff(struct Unit* unit, int item) {
	if (item == 0)
		return FALSE;

	if (!(GetItemAttributes(item) & IA_STAFF))
		return FALSE;

	if (unit->statusIndex == UNIT_STATUS_SLEEP)
		return FALSE;

	if (unit->statusIndex == UNIT_STATUS_BERSERK)
		return FALSE;

	if (unit->statusIndex == UNIT_STATUS_SILENCED)
		return FALSE;
	
	return GetWExp(unit, GetItemType(item)) >= GetItemRequiredExp(item);
	
}


int GetItemRequiredExp(int item) {
	
	int rank_exp = GetItemData(ITEM_INDEX(item))->weaponRank;
	
	if( 0 == gCanUnitUseAllTypeWeapon )
		return rank_exp;
	else
		return rank_exp < WPN_EXP_D ? 0 : rank_exp;

}
