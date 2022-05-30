#include "gbafe-chax.h"

static const u8 *BuildVanillaPromoList(u8 charId, u8 classId, u8 itemId);
static int CanUnitUsePromoItemVanilla(u8 charId, u8 classId, u8 itemId);


const u8 *GetUnitPromoList(u8 charId, u8 classId, u8 itemId){

	return BuildVanillaPromoList(charId, classId, itemId);
}



const u8 *BuildVanillaPromoList(u8 charId, u8 classId, u8 itemId){
	
	struct UnitPromoTable{
		u8 promoClass[2];
	};

	extern const struct UnitPromoTable gPromotionTable[];
	extern u8* gpRamPromoTmpList;
	
	for(int i = 0; i < PROMO_CLASS_LIST_MAX; i++)
		gpRamPromoTmpList[i] = 0;

	if( !CanUnitUsePromoItemVanilla(charId, classId, itemId) )
		return gpRamPromoTmpList;

	gpRamPromoTmpList[0] = gPromotionTable[classId].promoClass[0];
	gpRamPromoTmpList[1] = gPromotionTable[classId].promoClass[1];
	gpRamPromoTmpList[2] = 0;
	
	return gpRamPromoTmpList;
}

int CanUnitUsePromoItemVanilla(u8 charId, u8 classId, u8 itemId){
	
		#define CHECK_LIST(it)                       \
		while (*it)                              \
		{                                        \
			if (classId == *it) \
				return TRUE;                     \
			it++;                                \
        }                                        \

	const u8* classList = NULL;
	struct Unit* unit = GetUnitFromCharId(charId);
	
	if (charId == CHARACTER_EIRIKA || charId == CHARACTER_EPHRAIM)
	{
		switch (itemId)
		{

		case ITEM_LUNARBRACE:
			classList = gUnknown_088ADFA4;
			break;

		case ITEM_SOLARBRACE:
			classList = gUnknown_088ADFA6;
			break;
		default:
			break;
		} // switch (GetItemIndex(item))

		if (classList)
			CHECK_LIST(classList);
	}

	if (unit->level < 10)
		return FALSE;

	switch (itemId)
	{

	case ITEM_HEROCREST:
		classList = gUnknown_088ADF57;
		break;

	case ITEM_KNIGHTCREST:
		classList = gUnknown_088ADF5E;
		break;

	case ITEM_ORIONSBOLT:
		classList = gUnknown_088ADF64;
		break;

	case ITEM_ELYSIANWHIP:
		classList = gUnknown_088ADF67;
		break;

	case ITEM_GUIDINGRING:
		classList = gUnknown_088ADF6B;
		break;

	case ITEM_MASTERSEAL:
		classList = gUnknown_088ADF76;
		break;

	case ITEM_LUNARBRACE:
		classList = gUnknown_088ADFA4;
		break;

	case ITEM_SOLARBRACE:
		classList = gUnknown_088ADFA6;
		break;

	case ITEM_HEAVENSEAL:
		classList = gUnknown_088ADF96;
		break;

	case ITEM_UNK_C1:
		classList = gUnknown_088ADFA3;
		break;

	case ITEM_OCEANSEAL:
		classList = gUnknown_088ADF9E;
		break;
	default:
			break;
	} // switch (GetItemIndex(item))

	CHECK_LIST(classList);

	return FALSE;
}