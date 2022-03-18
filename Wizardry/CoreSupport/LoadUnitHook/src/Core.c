#include "gbafe.h"

typedef void (*HookFunc)(struct Unit* unit);
extern HookFunc OnLoadUnitFuncList[];

struct Unit* LoadUnit(const struct UnitDefinition* uDef) {
	struct UnitDefinition buf;

	struct Unit* unit = NULL;

	if (uDef->genMonster) {
		u32 packedItems;
		u16 item1, item2;

		u16 monsterClass = GenerateMonsterClass(uDef->classIndex);

		buf = *uDef;

		buf.autolevel = TRUE;
		buf.classIndex = monsterClass;
		buf.level = GenerateMonsterLevel(uDef->level);

		packedItems = GenerateMonsterItems(monsterClass);

        // ew
		item1 = packedItems >> 16;
		item2 = packedItems & 0xFFFF;

		buf.items[0] = item1;
		buf.items[1] = item2;
		buf.items[2] = 0;
		buf.items[3] = 0;

		if ((GetItemWeaponEffect(item1) == 1) || !item2)
			buf.itemDrop = FALSE;
		else
			buf.itemDrop = TRUE;

		if (item1 == ITEM_MONSTER_SHADOWSHT || item1 == ITEM_MONSTER_STONE) {
			// Add another weapon item if weapon is either Shadowshot or Stone

			buf.items[2] = buf.items[1];

			switch (monsterClass) {

			case CLASS_MOGALL:
				buf.items[1] = ITEM_MONSTER_EVILEYE;
				break;

			case CLASS_ARCH_MOGALL:
				buf.items[1] = ITEM_MONSTER_CRIMSNEYE;
				break;

			case CLASS_GORGON:
				buf.items[1] = ITEM_MONSTER_DEMONSURG;

			} // switch (monsterClass)
		}

		if (CanClassWieldWeaponType(monsterClass, ITYPE_BOW) == TRUE) {
			// TODO: AI BIT DEFINITIONS
			buf.ai.ai3 = buf.ai.ai3 & (1 | 2 | 4);
			buf.ai.ai3 = buf.ai.ai3 | (8 | 32);
		}

		uDef = &buf;
	} // (uDef->genMonster)

	switch (uDef->allegiance) {

		// TODO: unit definition faction constants

	case 0:
		unit = GetFreeBlueUnit(uDef);
		break;

	case 2:
		unit = GetFreeUnit(FACTION_RED);
		break;

	case 1:
		unit = GetFreeUnit(FACTION_GREEN);
		break;

	} // switch (uDef->allegiance)

	if (!unit)
		return NULL;

	ClearUnit(unit);

	UnitInitFromDefinition(unit, uDef);
	UnitLoadStatsFromChracter(unit, unit->pCharacterData);
	UnitHideIfUnderRoof(unit);

	if (UNIT_IS_GORGON_EGG(unit))
		SetUnitStatus(unit, UNIT_STATUS_RECOVER);
	
	// <!>
	// Load Unit Hook here!
	// since we will auto-level unit's magic
	// so load unit magic should before auto-level
	HookFunc *it = &OnLoadUnitFuncList[0];
	while( *it )
		(*it++)(unit);
	
	
	if (uDef->autolevel) {
		if (UNIT_FACTION(unit) == FACTION_BLUE) {
			UnitAutolevelRealistic(unit);
			UnitAutolevelWExp(unit, uDef);
		} else {
			if ((UNIT_CATTRIBUTES(unit) & CA_BOSS) || (unit->pCharacterData->number < 0x40)) {
				struct Unit* unit2 = GetFreeUnit(0);

				CopyUnit(unit, unit2);

				unit2->exp = 0;
				UnitAutolevelRealistic(unit2);

				ClearUnit(unit);
				CopyUnit(unit2, unit);

				ClearUnit(unit2);

				unit->exp   = UNIT_EXP_DISABLED;
				unit->level = uDef->level;
			} else
				UnitAutolevel(unit);

			UnitAutolevelWExp(unit, uDef);
			SetUnitLeaderCharId(unit, uDef->leaderCharIndex);
		}

		if (UNIT_IS_GORGON_EGG(unit))
			unit->maxHP = (unit->level + 1) * 5;
	} // if (uDef->autolevel)

	FixROMUnitStructPtr(unit);
	UnitLoadSupports(unit);

	if (uDef->itemDrop)
		unit->state |= US_DROP_ITEM;

	UnitCheckStatCaps(unit);

	unit->curHP = GetUnitMaxHp(unit);

	if (UNIT_IS_GORGON_EGG(unit))
		SetUnitHp(unit, 5);
	
	
	return unit;
}
