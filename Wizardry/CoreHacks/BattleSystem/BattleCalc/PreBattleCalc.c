#include "gbafe-chax.h"



void ComputeBattleUnitStats(struct BattleUnit* actor, struct BattleUnit* target){
	
	typedef void (*BC_Fun) (struct BattleUnit*, struct BattleUnit*);
	extern BC_Fun PreBattleCalcLoopTable[];
	
	BC_Fun *it = &PreBattleCalcLoopTable[0];
	
	while( *it )
		(*it++)(actor, target);
	
}



void BC_Init(struct BattleUnit* actor, struct BattleUnit* target){
	
	actor->battleAttack = 0;
	actor->battleDefense = 0;
	actor->battleSpeed = 0;
	actor->battleHitRate = 0;
	actor->battleAvoidRate = 0;
	actor->battleCritRate = 0;
	actor->battleDodgeRate = 0;
	actor->battleSilencerRate = 0;
}


void BC_Lethality(struct BattleUnit* actor, struct BattleUnit* target){
	
	// BOSS
	if( UNIT_IS_VALID(&target->unit) & (NULL != &target->unit) )
		if ( 0 != (UNIT_CATTRIBUTES(&target->unit) & CA_BOSS) )
			actor->battleSilencerRate -= 30;
	
	
	// Asigned
	if( actor->battleSilencerRate < 0 )
		actor->battleSilencerRate  = 0;
	
	if( actor->battleSilencerRate > 100 )
		actor->battleSilencerRate = 100;
}


void BC_Atk(struct BattleUnit* actor, struct BattleUnit* target){
	
	actor->battleAttack += GetItemMight(actor->weapon); // + actor->wTriangleDmgBonus;

	if (IsItemEffectiveAgainst(actor->weapon, &target->unit) == TRUE) 
		actor->battleAttack *= 3;
	
	// Check Magic
	if( CheckMagAttack(actor) )
		actor->battleAttack += *GetMagAt(&actor->unit);

	else
		actor->battleAttack += actor->unit.pow;
	
	// Minus zero
	if( actor->battleAttack < 0 )
		actor->battleAttack = 0;
}


void BC_AS(struct BattleUnit* actor, struct BattleUnit* target){
	
	s16 power = CheckMagAttack(actor)
		? actor->unit.pow
		: *GetMagAt(&actor->unit);

	actor->battleSpeed += actor->unit.spd;
	
	if( GetItemWeight(actor->weaponBefore) > _lib_div(power, 5) )
		actor->battleSpeed -=  GetItemWeight(actor->weaponBefore) - _lib_div(power, 5);
	
	
	// Minus zero
	if( actor->battleSpeed < 0 )
		actor->battleSpeed = 0;
}



void BC_DefRes(struct BattleUnit* actor, struct BattleUnit* target){

	// Check Luna
	if( IA_NEGATE_DEFENSE & target->weaponAttributes )
		actor->battleDefense += 0;
	
	// Check SorceryBlade
	else if( (*SkillTester)(&actor->unit, SID_SorceryBlade) )
		actor->battleDefense += 
			actor->unit.res < actor->unit.def
			? actor->terrainResistance + actor->unit.res
			: actor->terrainDefense + actor->unit.def;
	
	// Check Magic
	else if ( CheckMagAttack(target) )
		actor->battleDefense += actor->terrainResistance + actor->unit.res;

	else
		actor->battleDefense += actor->terrainDefense + actor->unit.def;
	
	// Minus zero
	if( actor->battleDefense < 0 )
		actor->battleDefense = 0;
}


void BC_Hit(struct BattleUnit* actor, struct BattleUnit* target){

	int distance = UNIT_IS_VALID(&target->unit) & (NULL != &target->unit)
		? RECT_DISTANCE(actor->unit.xPos, actor->unit.yPos, target->unit.xPos, target->unit.yPos)
		: 0;
	
	if( CheckMagAttack(actor) )
		actor->battleHitRate += (actor->unit.skl + actor->unit.lck) / 2;
	else
		actor->battleHitRate += actor->unit.skl;
	
	actor->battleHitRate += GetItemHit(actor->weapon); // + actor->wTriangleHitBonus;

	if( distance > 2 )
		actor->battleHitRate -= 20 * (distance - 2);
	
	// Minus zero
	if( actor->battleHitRate < 0 )
		actor->battleHitRate = 0;
}


// Avo = unit.spd - [weight - floor(unit.pow/5)] + fix
void BC_Avo(struct BattleUnit* actor, struct BattleUnit* target){
		
	if( CheckMagAttack(actor) )
		actor->battleAvoidRate += (actor->unit.spd + actor->unit.lck) / 2;
	else
		actor->battleAvoidRate += actor->unit.spd;
	
	actor->battleAvoidRate += actor->terrainAvoid;

	
	if (actor->battleAvoidRate < 0)
		actor->battleAvoidRate = 0;
	
}


void BC_Crit(struct BattleUnit* actor, struct BattleUnit* target){
	
	actor->battleCritRate += 
		GetItemCrit(actor->weapon) + 
		(actor->unit.skl + actor->unit.lck) / 2;
	
	// To do
	if( (*SkillTester)(&actor->unit, SID_RuinedBladePlus) )
		actor->battleCritRate = 0;
	
	if (actor->battleCritRate < 0)
		actor->battleCritRate = 0;
}


void BC_Dodge(struct BattleUnit* actor, struct BattleUnit* target){
	
	actor->battleDodgeRate += actor->unit.lck;
	
	if (actor->battleDodgeRate < 0)
		actor->battleDodgeRate = 0;
	
}
