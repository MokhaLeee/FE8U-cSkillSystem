#include "gbafe-chax.h"

void SetBattleUnitWeapon(struct BattleUnit* bu, int itemSlot) {
	if (itemSlot == BU_ISLOT_AUTO)
		itemSlot = GetUnitEquippedWeaponSlot(&bu->unit);

	if (bu->unit.state & US_IN_BALLISTA)
		itemSlot = BU_ISLOT_BALLISTA;

	bu->canCounter = TRUE;

	switch (itemSlot) {

	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
        // regular item slots

		bu->weaponSlotIndex = itemSlot;
		bu->weapon = bu->unit.items[bu->weaponSlotIndex];

		break;

	case BU_ISLOT_5:
		// borrowed item?

		bu->weaponSlotIndex = 0xFF;
		bu->weapon = gUnknown_0202BCB0.itemUnk2C;

		break;

	case BU_ISLOT_ARENA_PLAYER:
		// arena player weapon

		bu->weaponSlotIndex = 0;

		bu->weapon = gUnknown_0203A8F0.playerWeapon;
		bu->canCounter = FALSE;

		break;

	case BU_ISLOT_ARENA_OPPONENT:
		// arena opponent weapon

		bu->weaponSlotIndex = 0;

		bu->weapon = gUnknown_0203A8F0.opponentWeapon;
		bu->canCounter = FALSE;

		break;

	case BU_ISLOT_BALLISTA:
		// riding ballista

		bu->weaponSlotIndex = 0xFF;

		bu->weapon = GetBallistaItemAt(bu->unit.xPos, bu->unit.yPos);
		bu->canCounter = FALSE;

		break;

	default:
		bu->weaponSlotIndex = 0xFF;

		bu->weapon = 0;
		bu->canCounter = FALSE;

		break;

	} // switch (itemSlot)

	bu->weaponBefore = bu->weapon;
	bu->weaponAttributes = GetItemAttributes(bu->weapon);
	bu->weaponType = GetItemType(bu->weapon);

	if (!(gBattleStats.config & BATTLE_CONFIG_BIT2)) 
	{
		if (bu->weaponAttributes & IA_MAGICDAMAGE) 
		{
			switch (GetItemIndex(bu->weapon)) 
			{

			case ITEM_SWORD_WINDSWORD:
				bu->weaponType = ITYPE_ANIMA;
				break;

			case ITEM_SWORD_LIGHTBRAND:
				bu->weaponType = ITYPE_LIGHT;
				break;

			case ITEM_SWORD_RUNESWORD:
				bu->weaponType = ITYPE_DARK;
				break;

			} // switch (GetItemIndex(bu->weapon))
		} // if (bu->weaponAttributes & IA_MAGICDAMAGE)

	}
	
}

