#include "gbafe-chax.h"

extern const struct ItemStatBonuses Boost_Item_BC[];

const struct ItemData ItemBC = {
	.nameTextId = ENUM_msgItemName_MagBooster,
	.descTextId = ENUM_msgItemDesc_MagBooster,
	.useDescTextId = ENUM_msgItemUseDesc_MagBooster,
	.number = 0xBC,
	.weaponType = ITYPE_ITEM,
	.attributes = 0,
	.pStatBonuses = Boost_Item_BC,
	.maxUses = 1,
	.encodedRange = 0x11,
	.costPerUse = 8000,
	.iconId = 0xCA,
	
};