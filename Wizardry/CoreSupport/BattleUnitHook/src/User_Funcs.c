
#include "gbafe-chax.h"

// (802A584) InitBattleUnit
void U2B_Vanilla(struct BattleUnit* bu, struct Unit* unit){
	if (!unit)
        return;

    bu->unit = *unit;

    bu->unit.maxHP = GetUnitMaxHp(unit);
    bu->unit.pow = GetUnitPower(unit);
    bu->unit.skl = GetUnitSkill(unit);
    bu->unit.spd = GetUnitSpeed(unit);
    bu->unit.def = GetUnitDefense(unit);
    bu->unit.lck = GetUnitLuck(unit);
    bu->unit.res = GetUnitResistance(unit);
    
	// bu->unit.conBonus = UNIT_CON(unit);
    // bu->unit.movBonus = UNIT_MOV(unit);
	
	bu->unit.conBonus = ConGetter(unit);
	bu->unit.movBonus = MovGetter(unit);

    bu->levelPrevious = bu->unit.level;
    bu->expPrevious = bu->unit.exp;

    bu->hpInitial = bu->unit.curHP;
    bu->statusOut = 0xFF;

    bu->changeHP = 0;
    bu->changePow = 0;
    bu->changeSkl = 0;
    bu->changeSpd = 0;
    bu->changeDef = 0;
    bu->changeRes = 0;
    bu->changeLck = 0;
    bu->changeCon = 0;

    gBattleActor.wexpMultiplier = 0;
    gBattleTarget.wexpMultiplier = 0;

    bu->wTriangleHitBonus = 0;
    bu->wTriangleDmgBonus = 0;

    bu->nonZeroDamage = FALSE;

    gBattleActor.weaponBroke = FALSE;
    gBattleTarget.weaponBroke = FALSE;

    gBattleActor.expGain = 0;
    gBattleTarget.expGain = 0;
}

// (802C1EC) UpdateUnitFromBattle
void B2U_Vanilla(struct Unit* unit, struct BattleUnit* bu){

    unit->level = bu->unit.level;
    unit->exp   = bu->unit.exp;
    unit->curHP = bu->unit.curHP;
    unit->state = bu->unit.state;

    gUnknown_03003060 = UNIT_ARENA_LEVEL(unit);

    if (bu->statusOut >= 0)
        SetUnitStatus(unit, bu->statusOut);

    unit->maxHP += bu->changeHP;
    unit->pow   += bu->changePow;
    unit->skl   += bu->changeSkl;
    unit->spd   += bu->changeSpd;
    unit->def   += bu->changeDef;
    unit->res   += bu->changeRes;
    unit->lck   += bu->changeLck;

    UnitCheckStatCaps(unit);

/* 	This has been worked in WeaponSystem

	extern int GetBattleUnitUpdatedWeaponExp(struct BattleUnit*);
	
    int tmp = GetBattleUnitUpdatedWeaponExp(bu);

    if (tmp > 0)
        unit->ranks[bu->weaponType] = tmp; */

    for (int i = 0; i < UNIT_ITEM_COUNT; ++i)
        unit->items[i] = bu->unit.items[i]; 

    UnitRemoveInvalidItems(unit);

    if (bu->expGain)
        BWL_AddExpGained(unit->pCharacterData->number, bu->expGain);
}


