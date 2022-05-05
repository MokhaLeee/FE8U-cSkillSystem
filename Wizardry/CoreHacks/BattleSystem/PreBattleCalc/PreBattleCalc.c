#include "gbafe-chax.h"

// ===========================================================
//                         Judgement
// ===========================================================

int CheckMagAttack(struct BattleUnit* bu){
	
	return 0 != ((IA_MAGICDAMAGE | IA_MAGIC) & bu->weaponAttributes);
	
}



// ===========================================================
//                           Extern
// ===========================================================

void ComputeBattleUnitStats(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	typedef void (*BC_Fun) (struct BattleUnit*, struct BattleUnit*);
	extern BC_Fun PreBattleCalcLoopTable[];
	
	BC_Fun *it = &PreBattleCalcLoopTable[0];
	
	while( *it )
		(*it++)(attacker, defender);
	
}



void BC_Init(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	attacker->battleAttack = 0;
	attacker->battleDefense = 0;
	attacker->battleSpeed = 0;
	attacker->battleHitRate = 0;
	attacker->battleAvoidRate = 0;
	attacker->battleCritRate = 0;
	attacker->battleDodgeRate = 0;
}


void BC_Atk(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	attacker->battleAttack += GetItemMight(attacker->weapon) + attacker->wTriangleDmgBonus;

	if (IsItemEffectiveAgainst(attacker->weapon, &defender->unit) == TRUE) 
		attacker->battleAttack *= 3;
	
	// Check Magic
	if( CheckMagAttack(attacker) )
		attacker->battleAttack += *GetMagAt(&attacker->unit);

	else
		attacker->battleAttack += attacker->unit.pow;
	
	// Minus zero
	if( attacker->battleAttack < 0 )
		attacker->battleAttack = 0;
}


void BC_AS(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	s16 power = CheckMagAttack(attacker)
		? attacker->unit.pow
		: *GetMagAt(&attacker->unit);

	attacker->battleSpeed += attacker->unit.spd;
	
	if( GetItemWeight(attacker->weaponBefore) > _lib_div(power, 5) )
		attacker->battleSpeed -=  GetItemWeight(attacker->weaponBefore) - _lib_div(power, 5);
	
	
	// Minus zero
	if( attacker->battleSpeed < 0 )
		attacker->battleSpeed = 0;
}



void BC_DefRes(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	// Check Luna
	if( IA_NEGATE_DEFENSE & defender->weaponAttributes )
		attacker->battleDefense += 0;
		
	// Check Magic
	else if ( CheckMagAttack(defender) )
		attacker->battleDefense += attacker->terrainResistance + attacker->unit.res;

	else
		attacker->battleDefense += attacker->terrainDefense + attacker->unit.def;
	
	// Minus zero
	if( attacker->battleDefense < 0 )
		attacker->battleDefense = 0;
}


void BC_Hit(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	if( CheckMagAttack(attacker) )
		attacker->battleHitRate += (attacker->unit.skl + attacker->unit.lck) / 2;
	else
		attacker->battleHitRate += attacker->unit.skl;
	
	attacker->battleHitRate += GetItemHit(attacker->weapon) + attacker->wTriangleHitBonus;

	
	// Minus zero
	if( attacker->battleHitRate < 0 )
		attacker->battleHitRate = 0;
}


// Avo = unit.spd - [weight - floor(unit.pow/5)] + fix
void BC_Avo(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	s16 power = CheckMagAttack(attacker)
		? attacker->unit.pow
		: *GetMagAt(&attacker->unit);
	
	attacker->battleAvoidRate += attacker->unit.spd + attacker->unit.lck + attacker->terrainAvoid;
	
	if( GetItemWeight(attacker->weaponBefore) > _lib_div(power, 5) )
		attacker->battleAvoidRate -=  GetItemWeight(attacker->weaponBefore) - _lib_div(power, 5);
	
	if (attacker->battleAvoidRate < 0)
		attacker->battleAvoidRate = 0;
	
}


void BC_Crit(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	attacker->battleCritRate += 
		GetItemCrit(attacker->weapon) + 
		(attacker->unit.skl + attacker->unit.lck) / 2;
	
	if (attacker->battleCritRate < 0)
		attacker->battleCritRate = 0;
}


void BC_Dodge(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	attacker->battleDodgeRate += attacker->unit.lck;
	
	if (attacker->battleDodgeRate < 0)
		attacker->battleDodgeRate = 0;
	
}
