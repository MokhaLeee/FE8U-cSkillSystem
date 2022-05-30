#include "gbafe-chax.h"

extern unsigned GetTargetListSize(void);

extern void MakeTargetListForAdjacentHeal(struct Unit*);
extern void MakeTargetListForRangedHeal(struct Unit*);
extern void MakeTargetListForRestore(struct Unit*);
extern void MakeTargetListForRescueStaff(struct Unit*);
extern void MakeTargetListForBarrier(struct Unit*);
extern void MakeTargetListForSilence(struct Unit*);
extern void MakeTargetListForSleep(struct Unit*);
extern void MakeTargetListForBerserk(struct Unit*);
extern void MakeTargetListForWarp(struct Unit*);
extern void MakeTargetListForHammerne(struct Unit*);
extern void MakeTargetListForUnlock(struct Unit*);
extern void MakeTargetListForLatona(struct Unit*);
extern void MakeTargetListForMine(struct Unit*);
extern void MakeTargetListForLightRune(struct Unit*);
extern void MakeTargetListForDanceRing(struct Unit*);
extern void MakeTargetListForDoorAndBridges(struct Unit*, int terrain);

static int NormalJudge_Heal(struct Unit*, uint16_t item);
static int NormalJudge_Physic(struct Unit*, uint16_t item);
static int NormalJudge_Restore(struct Unit*, uint16_t item);
static int NormalJudge_Rescue(struct Unit*, uint16_t item);
static int NormalJudge_Barrier(struct Unit*, uint16_t item);
static int NormalJudge_Silence(struct Unit*, uint16_t item);
static int NormalJudge_Sleep(struct Unit*, uint16_t item);
static int NormalJudge_Berserk(struct Unit*, uint16_t item);
static int NormalJudge_Warp(struct Unit*, uint16_t item);
static int NormalJudge_Repair(struct Unit*, uint16_t item);
static int NormalJudge_Unlock(struct Unit*, uint16_t item);
static int NormalJudge_Latona(struct Unit*, uint16_t item);
static int NormalJudge_Mine(struct Unit*, uint16_t item);
static int NormalJudge_LightRune(struct Unit*, uint16_t item);
static int NormalJudge_StaffTorch(struct Unit*, uint16_t item);
static int NormalJudge_DanceRing(struct Unit*, uint16_t item);
static int NormalJudge_MetisStome(struct Unit*, uint16_t item);


// Normal Judgement
typedef int (*JudgFunc_t)(struct Unit*, uint16_t item);

const JudgFunc_t ItemMenuUsabilityTable[0xFF] = {
	
	[ITEM_STAFF_HEAL] = NormalJudge_Heal,
	[ITEM_STAFF_MEND] = NormalJudge_Heal,
	[ITEM_STAFF_RECOVER] = NormalJudge_Heal,
	[ITEM_STAFF_PHYSIC] = NormalJudge_Physic,
	[ITEM_STAFF_FORTIFY] = NormalJudge_Physic,
	[ITEM_STAFF_RESTORE] = NormalJudge_Restore,
	[ITEM_STAFF_RESCUE] = NormalJudge_Rescue,
	[ITEM_STAFF_BARRIER] = NormalJudge_Barrier,
	[ITEM_STAFF_SILENCE] = NormalJudge_Silence,
	[ITEM_STAFF_SLEEP] = NormalJudge_Sleep,
	[ITEM_STAFF_BERSERK] = NormalJudge_Berserk,
	[ITEM_STAFF_WARP] = NormalJudge_Warp,
	[ITEM_STAFF_REPAIR] = NormalJudge_Repair,
	[ITEM_STAFF_UNLOCK] = NormalJudge_Unlock,
	
	[ITEM_BOOSTER_HP] =(JudgFunc_t) CanUnitUseStatGainItem,
	[ITEM_BOOSTER_POW] =(JudgFunc_t) CanUnitUseStatGainItem,
	[ITEM_BOOSTER_SKL] =(JudgFunc_t) CanUnitUseStatGainItem,
	[ITEM_BOOSTER_SPD] =(JudgFunc_t) CanUnitUseStatGainItem,
	[ITEM_BOOSTER_LCK] =(JudgFunc_t) CanUnitUseStatGainItem,
	[ITEM_BOOSTER_DEF] =(JudgFunc_t) CanUnitUseStatGainItem,
	[ITEM_BOOSTER_RES] =(JudgFunc_t) CanUnitUseStatGainItem,
	[ITEM_BOOSTER_MOV] =(JudgFunc_t) CanUnitUseStatGainItem,
	[ITEM_BOOSTER_CON] =(JudgFunc_t) CanUnitUseStatGainItem,
	
	[ITEM_HEROCREST] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_KNIGHTCREST] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_ORIONSBOLT] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_ELYSIANWHIP] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_GUIDINGRING] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_MASTERSEAL] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_HEAVENSEAL] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_OCEANSEAL] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_LUNARBRACE] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_SOLARBRACE] =(JudgFunc_t) CanUnitUsePromotionItem,
	[ITEM_UNK_C1] =(JudgFunc_t) CanUnitUsePromotionItem,
	
	[ITEM_VULNERARY] =(JudgFunc_t) CanUnitUseHealItem,
	[ITEM_ELIXIR] =(JudgFunc_t) CanUnitUseHealItem,
	[ITEM_VULNERARY_2] =(JudgFunc_t) CanUnitUseHealItem,
	
	[ITEM_PUREWATER] =(JudgFunc_t) CanUnitUsePureWaterItem,
	[ITEM_TORCH] =(JudgFunc_t) CanUnitUseTorchItem,
	[ITEM_ANTITOXIN] =(JudgFunc_t) CanUnitUseAntitoxinItem,
	
	[ITEM_CHESTKEY] =(JudgFunc_t) CanUnitUseChestKeyItem,
	[ITEM_CHESTKEY_BUNDLE] =(JudgFunc_t) CanUnitUseChestKeyItem,
	[ITEM_DOORKEY] =(JudgFunc_t) CanUnitUseDoorKeyItem,
	[ITEM_LOCKPICK] =(JudgFunc_t) CanUnitUseLockpickItem,
	
	[ITEM_STAFF_LATONA] = NormalJudge_Latona,
	[ITEM_MINE] = NormalJudge_Mine,
	[ITEM_LIGHTRUNE] = NormalJudge_LightRune,
	[ITEM_STAFF_TORCH] = NormalJudge_StaffTorch,
	
	[ITEM_FILLAS_MIGHT] = NormalJudge_DanceRing,
	[ITEM_NINISS_GRACE] = NormalJudge_DanceRing,
	[ITEM_THORS_IRE] = NormalJudge_DanceRing,
	[ITEM_SETS_LITANY] = NormalJudge_DanceRing,
	
	[ITEM_METISSTOME] = NormalJudge_MetisStome,
	[ITEM_JUNAFRUIT] =(JudgFunc_t) CanUnitUseFruitItem,
};




s8 CanUnitUseItem(struct Unit* unit, int item){
	
	JudgFunc_t it;
	
	if ((GetItemAttributes(item) & IA_STAFF) && !CanUnitUseStaff(unit, item))
		return FALSE;
	
	it = ItemMenuUsabilityTable[ITEM_ID(item)];
	
	if ( NULL == it	)
		return 0;
	else
		return it(unit, item);
}



int GetItemUseEffect(int item) {
	JudgFunc_t it;
	
	it = ItemMenuUsabilityTable[ITEM_ID(item)];
	
	return (NULL != it);
}


// Static functions
static int NormalJudge_Heal(struct Unit* unit, uint16_t item){
	MakeTargetListForAdjacentHeal(unit);
	return GetTargetListSize() != 0;
}


static int NormalJudge_Physic(struct Unit* unit, uint16_t item){
	MakeTargetListForRangedHeal(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Restore(struct Unit* unit, uint16_t item){
	MakeTargetListForRestore(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Rescue(struct Unit* unit, uint16_t item){
	MakeTargetListForRescueStaff(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Barrier(struct Unit* unit, uint16_t item){
	MakeTargetListForBarrier(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Silence(struct Unit* unit, uint16_t item){
	MakeTargetListForSilence(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Sleep(struct Unit* unit, uint16_t item){
	MakeTargetListForSleep(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Berserk(struct Unit* unit, uint16_t item){
	MakeTargetListForBerserk(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Warp(struct Unit* unit, uint16_t item){
	MakeTargetListForWarp(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Repair(struct Unit* unit, uint16_t item){
	MakeTargetListForHammerne(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Unlock(struct Unit* unit, uint16_t item){
	MakeTargetListForUnlock(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Latona(struct Unit* unit, uint16_t item){
	MakeTargetListForLatona(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_Mine(struct Unit* unit, uint16_t item){
	MakeTargetListForMine(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_LightRune(struct Unit* unit, uint16_t item){
	MakeTargetListForLightRune(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_StaffTorch(struct Unit* unit, uint16_t item){
	return gRAMChapterData.chapterVisionRange != 0;
}

static int NormalJudge_DanceRing(struct Unit* unit, uint16_t item){
	MakeTargetListForDanceRing(unit);
	return GetTargetListSize() != 0;
}

static int NormalJudge_MetisStome(struct Unit* unit, uint16_t item){
	return !(unit->state && US_GROWTH_BOOST);
}





//  Now in PromotionList
/* 
s8 CanUnitUsePromotionItem(struct Unit* unit, int item)
{
	#define CHECK_LIST(it)                       \
		while (*it)                              \
		{                                        \
			if (unit->pClassData->number == *it) \
				return TRUE;                     \
			it++;                                \
        }                                        \

	const u8* classList = NULL;

	if (unit->pCharacterData->number == CHARACTER_EIRIKA || unit->pCharacterData->number == CHARACTER_EPHRAIM)
	{
		switch (GetItemIndex(item))
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

	switch (GetItemIndex(item))
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

	#undef CHECK_LIST
} */


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
		*GetMagAt(unit) + ((u8*)bonuses)[9];
	
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





s8 CanUnitUseFruitItem(struct Unit* unit)
{
	return (unit->level >= 10)
		? TRUE
		: FALSE;
}


