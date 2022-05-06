#include "gbafe-chax.h"

// ===================================================
//             Static Function Declaration
// ===================================================

int CheckCanDouble(struct BattleUnit* actor, struct BattleUnit* target);
static int CheckNormalDouble(struct BattleUnit* actor, struct BattleUnit* target);
static int CheckDoubleLoop(struct BattleUnit* actor, struct BattleUnit* target);
static int CheckNullDoubleLoop(struct BattleUnit* actor, struct BattleUnit* target);
static int CheckVantage(void);
static int CheckDesperation(void);


static int JudgeQuickRiposte(struct BattleUnit* bu);





// ===================================================
//                        Data
// ===================================================

enum{
	NOP_ATTACK = 0,
	ACT_ATTACK = 1,
	TAR_ATTACK = 2,
};

enum{
	UNWIND_VANTAGE = 1<<0,
	UNWIND_DESPERA = 1<<1,
	UNWIND_DOUBLE_ACT = 1<<2,
	UNWIND_DOUBLE_TAR = 1<<3,
};


static const uint8_t RoundArr[56] = {
	ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, NOP_ATTACK,	// 0:default
	TAR_ATTACK, ACT_ATTACK, NOP_ATTACK, NOP_ATTACK,	// 1	= 1
	ACT_ATTACK, ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, // 2	= 2	
	
	TAR_ATTACK, ACT_ATTACK, ACT_ATTACK, NOP_ATTACK, // 12	= 3
	ACT_ATTACK, TAR_ATTACK, ACT_ATTACK, NOP_ATTACK, // 3	= 4
	TAR_ATTACK, ACT_ATTACK, ACT_ATTACK, NOP_ATTACK, // 13	= 5
	ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, NOP_ATTACK,	// 0:default
	ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, NOP_ATTACK,	// 0:default
	ACT_ATTACK, TAR_ATTACK, TAR_ATTACK, NOP_ATTACK, // 4	= 8
	TAR_ATTACK, ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, // 14	= 9
	ACT_ATTACK, ACT_ATTACK, TAR_ATTACK, TAR_ATTACK, // 24	= 10
	
	
	TAR_ATTACK, ACT_ATTACK, ACT_ATTACK, TAR_ATTACK, // 124	= 11
	ACT_ATTACK, TAR_ATTACK, ACT_ATTACK, TAR_ATTACK, // 34	= 12
	TAR_ATTACK, ACT_ATTACK, TAR_ATTACK, ACT_ATTACK  // 134	= 13
};



// ===================================================
//             Core Function Definitions
// ===================================================

// 2AED0
void BattleUnwind(){
	
	// Function declear
	int BattleGenerateRoundHits(struct BattleUnit*, struct BattleUnit*);
	
	uint8_t round[4] = {0};
	uint8_t roundInfo = 0;
	
	if(  1 == CheckVantage() )
		roundInfo |= UNWIND_VANTAGE;

	if( 1 == CheckCanDouble(&gBattleActor, &gBattleTarget) )
	{
		// 此处我们让 UNWIND_DOUBLE_ACT 与 UNWIND_DESPERA 成为互不影响
		if( CheckDesperation() )
			roundInfo |= UNWIND_DESPERA;
		else
			roundInfo |= UNWIND_DOUBLE_ACT;	
	}
	if( CheckCanDouble(&gBattleTarget, &gBattleActor) )
		roundInfo |= UNWIND_DOUBLE_TAR;
	
	for( int i=0; i<4; i++)
		round[i] = RoundArr[i+roundInfo*4];
	
	
	// Make Battle Real
	ClearBattleHits();
	gBattleHitIterator->info |= BATTLE_HIT_INFO_BEGIN;
	
	// a counter for how bu attcks(for anim activation)
	int attacker_attack_counter = 0;
	int defender_attack_counter = 0;
	
	// 1st
	for( int i=0; i<4; i++)
	{
		if( NOP_ATTACK == round[i] )
			break;
		
		// later we will make gBattleHitIterator--, here to judge whether BattleGenerateRoundHits applied
		struct BattleHit* hit_cur = gBattleHitIterator;
		
		// Check Hit Core
		if( (ACT_ATTACK == round[i]) )
		{
			if( BattleGenerateRoundHits(&gBattleActor, &gBattleTarget) )
				break;
			else
				attacker_attack_counter++;
		}
			
		if( (TAR_ATTACK == round[i]) )
		{
			if( BattleGenerateRoundHits(&gBattleTarget, &gBattleActor) )
				break;
			else
				defender_attack_counter++;
		}
		
		// hit real
		gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_RETALIATE;
		
		// follow up
		if( round[i] == round[i+1] )
			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_FOLLOWUP;
		
		
		// to judge is battle-hits advanced
		if( hit_cur == gBattleHitIterator )
			continue;
		
		
		
		// Todo: Anim effect
		
		(*BattleHitExtCur)--;
		gBattleHitIterator--;
		
		
		// Combat Art Anim
		if( (gpBattleFlagExt->isCombat) && (gpBattleFlagExt->combat_unit == gBattleActor.unit.index) )
			if( (0 == i) && (ACT_ATTACK == round[i]) )
			{
				gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SURESHOT;
				BattleHitExt_SetAttr(ATTR_HITEXT_COMBAT_ART);
			}
		
		// vantage anim
		if( UNWIND_VANTAGE & roundInfo )
			if( 0 == i )
			{
				// Add skill to BattleHitExt
				if ( (*SkillTester)(&gBattleTarget.unit, SID_VantageBat) )
						SetBattleHitExt_DefSkill(SID_VantageBat);
					else
						SetBattleHitExt_DefSkill(SID_Vantage);
				
				// just anim
				gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SURESHOT;
				BattleHitExt_SetAttr(ATTR_HITEXT_SKILLACT_DEF);
			}
			
		// desperation anim
		if( UNWIND_DESPERA & roundInfo )
			if( 2 == attacker_attack_counter )
				if( (ACT_ATTACK == round[i]) && (ACT_ATTACK == round[i-1]) && (TAR_ATTACK == round[i+1]) )
				{
					// Add skill to BattleHitExt
					if ( (*SkillTester)(&gBattleActor.unit, SID_DesperationBat) )
						SetBattleHitExt_AtkSkill(SID_DesperationBat);
					else
						SetBattleHitExt_AtkSkill(SID_Desperation);
					
					// just anim
					gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SURESHOT;
					BattleHitExt_SetAttr(ATTR_HITEXT_SKILLACT_ATK);
				}
		
		
		if( (i > 1) && (TAR_ATTACK == round[i]) && (0==CheckNormalDouble(&gBattleTarget, &gBattleActor)) )
			if( 2 == defender_attack_counter )
			{
				
				if( JudgeQuickRiposte(&gBattleTarget) )
					SetBattleHitExt_AtkSkill(SID_QuickRiposte);
						
				gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SURESHOT;
				BattleHitExt_SetAttr(ATTR_HITEXT_SKILLACT_ATK);
			}
		
		
		// end of anim set			
		(*BattleHitExtCur)++;
		gBattleHitIterator++;
	}
	
	gBattleHitIterator->info |= BATTLE_HIT_INFO_END;
}


// 0x802B018+1
// 角色的一轮攻击(勇者系武器的话同时判定两次)
int BattleGenerateRoundHits(struct BattleUnit* actor, struct BattleUnit* target) {
	
	// Function declear
	int GetBattleUnitHitCount(struct BattleUnit* actor);
	extern s8 BattleGenerateHit(struct BattleUnit* actor, struct BattleUnit* target);
	
	int i, count;
	u32 attrs;

	if (!actor->weapon)
		return FALSE;

	attrs = gBattleHitIterator->attributes;
	count = GetBattleUnitHitCount(actor);

	for (i = 0; i < count; ++i) 
	{
		gBattleHitIterator->attributes |= attrs;

		if (BattleGenerateHit(actor, target))
			return TRUE;
    }

	return FALSE;
}



// 判定勇者系武器
int GetBattleUnitHitCount(struct BattleUnit* actor){
	
	// Target cannot double attack with brave weapon
	if( &gBattleActor != actor )
		return 1;
	
	if( !(actor->weaponAttributes & IA_BRAVE) )
		return 1;
	
	// attacker cannot use brave if use combat-art
	if( gpBattleFlagExt->isCombat )
		return 1;
	
	gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_BRAVE;
	return 2;
}




//  ORG $2AF90 (Check Doubling vanilla)
s8 BattleGetFollowUpOrder(struct BattleUnit** outAttacker, struct BattleUnit** outDefender) {
    
	

    if ( CheckCanDouble(&gBattleActor, &gBattleTarget) ) 
	{
        *outAttacker = &gBattleActor;
        *outDefender = &gBattleTarget;
    } 
	else if( CheckCanDouble( &gBattleTarget, &gBattleActor ) )
	{
        *outAttacker = &gBattleTarget;
        *outDefender = &gBattleActor;
    }
	else
		return FALSE;

    if (GetItemWeaponEffect((*outAttacker)->weaponBefore) == WPN_EFFECT_HPHALVE)
        return FALSE;

    if (GetItemIndex((*outAttacker)->weapon) == ITEM_MONSTER_STONE)
        return FALSE;

    return TRUE;
}




// ===================================================
//             Static Function Definitions
// ===================================================

// not static
int CheckCanDouble(struct BattleUnit* actor, struct BattleUnit* target){
	
	int can = CheckNormalDouble(actor, target) || CheckDoubleLoop(actor, target);

	return (!CheckNullDoubleLoop(actor,target)) && can;

}

// static
int CheckNormalDouble(struct BattleUnit* actor, struct BattleUnit* target){
	
	if( actor->battleSpeed < target->battleSpeed )
		return 0;
	
	else if( (actor->battleSpeed - target->battleSpeed) > BATTLE_FOLLOWUP_SPEED_THRESHOLD )
		return 1;
	else
		return 0;
}


// static 
int CheckDoubleLoop(struct BattleUnit* actor, struct BattleUnit* target){
	
	// Quick Riposte
	if( JudgeQuickRiposte(actor) )
		return 1;
	
	// default
	return 0;
}


// static 
int CheckNullDoubleLoop(struct BattleUnit* actor, struct BattleUnit* target){
	
	// if attacker use combat-art, cannot double attack
	if( &gBattleActor == actor )
		if( 1 == gpBattleFlagExt->isCombat )
			return 1;
	
	// default
	return 0;
}


// static 
int CheckVantage(void){
	
	struct Unit* target_unit = GetUnit(gBattleTarget.unit.index);
	
	// if inside combat-art, null vantage skills
	if( 1 == gpBattleFlagExt->isCombat )
		return 0;
	
	
	// Vantage:  HP <50%
	if( (*SkillTester)(target_unit, SID_Vantage) )
		if( target_unit->curHP < (target_unit->maxHP / 2) )
			return 1;
	
	
	// Todo
	// Vantage Battalion
	if( (*SkillTester)(target_unit, SID_VantageBat) )
		return 1;
	
	
	// default
	return 0;
}


// static 
int CheckDesperation(void){
	
	struct Unit* attacker_unit = GetUnit(gBattleActor.unit.index);
	
	// if inside combat-art, null desperation skills
	if( 1 == gpBattleFlagExt->isCombat )
		return 0;
	
	
	// Desperation:  HP <50%
	if( (*SkillTester)(attacker_unit, SID_Desperation) )
		if( attacker_unit->curHP < (attacker_unit->maxHP / 2) )
			return 1;
	
	
	// Todo
	// Desperation Battalion
	if( (*SkillTester)(attacker_unit, SID_DesperationBat) )
		return 1;
	
	
	// default
	return 0;
}



// ===================================================
//                    Skills misc
// ===================================================
int JudgeQuickRiposte(struct BattleUnit* bu){
	
	struct Unit* attacker_unit = GetUnit(bu->unit.index);
	
	// Quick Riposte:  HP >50% as defender
	if( &gBattleTarget == bu )
		if( (*SkillTester)(attacker_unit, SID_QuickRiposte) )
			if( attacker_unit->curHP > (attacker_unit->maxHP / 2) )
				return 1;
	
	return 0;
}

