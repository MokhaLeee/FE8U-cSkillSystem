#include "gbafe-chax.h"

void ComputeBattleUnitStats(struct BattleUnit* attacker, struct BattleUnit* defender);

void BattleGenerateUiStats(struct Unit* unit, s8 itemSlot) {
	gBattleStats.config = BATTLE_CONFIG_BIT2;

	gBattleTarget.weapon = 0;
	gBattleTarget.weaponAttributes = IA_NONE;
	gBattleTarget.weaponType = 0xFF;

	gBattleTarget.unit.pClassData = NULL;

	gBattleActor.wTriangleHitBonus = 0;
	gBattleActor.wTriangleDmgBonus = 0;

	if ((itemSlot >= 0) && (itemSlot < UNIT_ITEM_COUNT)) {
		struct Unit tmpUnit = *unit;

		EquipUnitItemSlot(&tmpUnit, itemSlot);
		itemSlot = 0;

		InitBattleUnit(&gBattleActor, &tmpUnit);
	} else
		InitBattleUnit(&gBattleActor, unit);

	if (gUnknown_03005280.state & GMAP_STATE_BIT0)
		SetBattleUnitTerrainBonuses(&gBattleActor, 0); // TODO: TERRAIN ID DEFINITIONS
	else
		SetBattleUnitTerrainBonusesAuto(&gBattleActor);

	SetBattleUnitWeapon(&gBattleActor, itemSlot);
	ComputeBattleUnitStats(&gBattleActor, &gBattleTarget);

/* 	if (GetItemIndex(gBattleActor.weapon) == ITEM_SWORD_RUNESWORD) {
		gBattleActor.battleAttack -= gBattleActor.unit.pow / 2;

		gBattleActor.battleCritRate = 0;
		gBattleActor.battleEffectiveCritRate = 0;
	} */

	if (!gBattleActor.weapon) {
		gBattleActor.battleAttack = 0xFF;
		gBattleActor.battleHitRate = 0xFF;
		gBattleActor.battleCritRate = 0xFF;
		gBattleActor.battleSilencerRate = 0xFF;
	}

	if (GetItemWeaponEffect(gBattleActor.weapon) == WPN_EFFECT_HPHALVE)
		gBattleActor.battleAttack = 0xFF;

	if (GetItemIndex(gBattleActor.weapon) == ITEM_MONSTER_STONE) {
		gBattleActor.battleAttack = 0xFF;
		gBattleActor.battleCritRate = 0xFF;
	}
}