#include "gbafe.h"

// (802BD50) ApplyUnitPromotion
void MLU_PromoGain_Vanilla(struct Unit* unit, u8 classId) {
    const struct ClassData* promotedClass = GetClassData(classId);

    int baseClassId = unit->pClassData->number;
    int promClassId = promotedClass->number;

    int i;

    // Apply stat ups

    unit->maxHP += promotedClass->promotionHp;

    if (unit->maxHP > promotedClass->maxHP)
        unit->maxHP = promotedClass->maxHP;

    unit->pow += promotedClass->promotionPow;

    if (unit->pow > promotedClass->maxPow)
        unit->pow = promotedClass->maxPow;

    unit->skl += promotedClass->promotionSkl;

    if (unit->skl > promotedClass->maxSkl)
        unit->skl = promotedClass->maxSkl;

    unit->spd += promotedClass->promotionSpd;

    if (unit->spd > promotedClass->maxSpd)
        unit->spd = promotedClass->maxSpd;

    unit->def += promotedClass->promotionDef;

    if (unit->def > promotedClass->maxDef)
        unit->def = promotedClass->maxDef;

    unit->res += promotedClass->promotionRes;

    if (unit->res > promotedClass->maxRes)
        unit->res = promotedClass->maxRes;

    // Remove base class' base wexp from unit wexp
    for (i = 0; i < 8; ++i)
        unit->ranks[i] -= unit->pClassData->baseRanks[i];

    // Update unit class
    unit->pClassData = promotedClass;

    // Add promoted class' base wexp to unit wexp
    for (i = 0; i < 8; ++i) {
        int wexp = unit->ranks[i];

        wexp += unit->pClassData->baseRanks[i];

        if (wexp > WPN_EXP_S)
            wexp = WPN_EXP_S;

        unit->ranks[i] = wexp;
    }

    // If Pupil -> Shaman promotion, set Anima rank to 0
    if (baseClassId == CLASS_PUPIL && promClassId == CLASS_SHAMAN)
        unit->ranks[ITYPE_ANIMA] = 0;

    unit->level = 1;
    unit->exp   = 0;

    unit->curHP += promotedClass->promotionHp;

    if (unit->curHP > GetUnitMaxHp(unit))
        unit->curHP = GetUnitMaxHp(unit);
}


// GenerateBattleUnitStatGainsComparatively
void MLU_PromoDiff_Vanilla(struct BattleUnit* bu, struct Unit* unit) {
    bu->changeHP  = bu->unit.maxHP - unit->maxHP;
    bu->changePow = bu->unit.pow   - unit->pow;
    bu->changeSkl = bu->unit.skl   - unit->skl;
    bu->changeSpd = bu->unit.spd   - unit->spd;
    bu->changeDef = bu->unit.def   - unit->def;
    bu->changeRes = bu->unit.res   - unit->res;
    bu->changeLck = bu->unit.lck   - unit->lck;

    if (bu->unit.conBonus != unit->conBonus)
        bu->changeCon = bu->unit.conBonus - unit->conBonus;
    else {
        bu->changeCon = 0;
        bu->unit.conBonus = unit->conBonus;
    }
}