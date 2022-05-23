#include "gbafe-chax.h"

// ===================================================
//             Static Function Declaration
// ===================================================

int CheckCanDouble(struct BattleUnit* actor, struct BattleUnit* target);
static int CheckNormalDouble(struct BattleUnit* actor, struct BattleUnit* target);
static int CheckForceDouble(struct BattleUnit* actor, struct BattleUnit* target);
static int CheckNullDoubleLoop(struct BattleUnit* actor, struct BattleUnit* target);
static int CheckVantageBattle(void);
static int CheckDesperationBattle(void);



static int JudgeSkillQuickRiposte(struct BattleUnit* bu);
static int JudgeCombatArtDouble(struct BattleUnit* bu);
static int JudgeSkillDesperation(struct BattleUnit* bu);
static int JudgeSkillDesperationBat(struct BattleUnit* bu);



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
	
	if(  1 == CheckVantageBattle() )
		roundInfo |= UNWIND_VANTAGE;

	if( 1 == CheckCanDouble(&gBattleActor, &gBattleTarget) )
	{
		// 此处我们让 UNWIND_DOUBLE_ACT 与 UNWIND_DESPERA 成为互不影响
		if( CheckDesperationBattle() )
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
			
		else if( (TAR_ATTACK == round[i]) )
		{
			if( BattleGenerateRoundHits(&gBattleTarget, &gBattleActor) )
				break;
			else
				defender_attack_counter++;
		}
		else 
			break;
		
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
					if ( JudgeSkillDesperation(&gBattleActor) )
					{
						SetBattleHitExt_AtkSkill(SID_DesperationBat);
						
						gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SURESHOT;
						BattleHitExt_SetAttr(ATTR_HITEXT_SKILLACT_ATK);
					}
					else if( JudgeSkillDesperationBat(&gBattleActor) )
					{
						SetBattleHitExt_AtkSkill(SID_Desperation);
						
						gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SURESHOT;
						BattleHitExt_SetAttr(ATTR_HITEXT_SKILLACT_ATK);
					}
					
				}
		
		// Riposte anim
		if( (i > 1) && (TAR_ATTACK == round[i]) && (0==CheckNormalDouble(&gBattleTarget, &gBattleActor)) )
			if( 2 == defender_attack_counter )
			{
				if( JudgeSkillQuickRiposte(&gBattleTarget) )
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
	s8 BattleGenerateHit(struct BattleUnit* actor, struct BattleUnit* target);
	u8 *SortHitActivitionSkills(struct BattleUnit* actor, struct BattleUnit*, u8 arr[10]);
	
	int i, count;
	u32 attrs;

	if (!actor->weapon)
		return FALSE;

	attrs = gBattleHitIterator->attributes;
	count = GetBattleUnitHitCount(actor);
	
	// Sort for Skill Activition
	u8 ArrTmp[0x20] = {0};
	u8 *SkillActArr = SortHitActivitionSkills(actor, target, ArrTmp);
	
	for (i = 0; i < count; ++i) 
	{
		gBattleHitIterator->attributes |= attrs;
		
		if( SKILL_VALID(SkillActArr[i]) ){
			
			SetBattleHitExt_AtkSkill(SkillActArr[i]);	
			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SURESHOT;
			BattleHitExt_SetAttr(ATTR_HITEXT_SKILLACT_ATK);
		}
		

		if (BattleGenerateHit(actor, target))
			return TRUE;
    }

	return FALSE;
}



// 判定勇者系武器
int GetBattleUnitHitCount(struct BattleUnit* actor){
	
	typedef int(*HitCountCalc_Func)(struct BattleUnit* actor, int cur);
	
	extern const HitCountCalc_Func BattleHitsCountCalcLoop[];
	
	const HitCountCalc_Func *it = BattleHitsCountCalcLoop;
	
	int count = 1;
	
	while( *it ){
		count = (*it++)(actor, count);
		
		// -1 to force null brave effect
		if( -1 == count )
			break;
	}
	
	if( count > 1 )
		gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_BRAVE;
	
	if( count < 1 )
		count = 1;
	
	return count;
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

	if( CheckNullDoubleLoop(actor,target) )
		return 0;
	
	return CheckNormalDouble(actor, target) || CheckForceDouble(actor, target);


}

// static
int CheckNormalDouble(struct BattleUnit* actor, struct BattleUnit* target){
	
	if( actor->battleSpeed < target->battleSpeed )
		return 0;
	
	else if( (actor->battleSpeed - target->battleSpeed) > 4 )
		return 1;
	else
		return 0;
}


// static 
int CheckForceDouble(struct BattleUnit* actor, struct BattleUnit* target){
	
	// Combat Art
	if( JudgeCombatArtDouble(actor) )
		return 1;
	
	// Quick Riposte
	if( JudgeSkillQuickRiposte(actor) )
		return 1;
	
	// default
	return 0;
}


// static 
int CheckNullDoubleLoop(struct BattleUnit* actor, struct BattleUnit* target){
	
	struct Unit* target_unit = GetUnit(gBattleTarget.unit.index);
	
	// Combat Art
	if( 1 == gpBattleFlagExt->isCombat )
		if( &gBattleActor == actor )
			return !JudgeCombatArtDouble(actor);
	
	// WaryFighter
	if( 1 == (*SkillTester)(target_unit, SID_WaryFighter) )
		if( HpCurGetter(target_unit) > (HpMaxGetter(target_unit)/2) )
			return 1;
	
	// default
	return 0;
}


// static 
int CheckVantageBattle(void){
	
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
int CheckDesperationBattle(void){
	
	// Combat-art enjoys priority
	// if use double-attack combat-art, then will cause desperation
	if( 1 == gpBattleFlagExt->isCombat )
		return JudgeCombatArtDouble(&gBattleActor);
	
	
	
	if( 1 == JudgeSkillDesperation(&gBattleActor) )
		return 1;
	
	
	if( 1 == JudgeSkillDesperationBat(&gBattleActor) )
		return 1;
	
	// default
	return 0;
}



// ===================================================
//                    Skills misc
// ===================================================

int JudgeCombatArtDouble(struct BattleUnit* bu){
	
	if( &gBattleActor == bu )
		if( 1 == gpBattleFlagExt->isCombat )
		{
			// Check Combat-Art
			const struct CombatArtInfo* info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
			
			// if attacker use combat-art and without double attack
			if( 1 == info->double_attack )
				return 1;
			
		}
	
	return 0;
}


int JudgeSkillQuickRiposte(struct BattleUnit* bu){
	
	struct Unit* unit = GetUnit(bu->unit.index);
	
	if( &gBattleTarget != bu )
		return 0;
	
	// Quick Riposte:  HP >50% as defender
	
	if( (*SkillTester)(unit, SID_QuickRiposte) )
		if( GetUnitCurrentHp(unit) > (GetUnitMaxHp(unit) / 2) )
			return 1;
	
	return 0;
}


int JudgeSkillDesperation(struct BattleUnit* bu){
	
	struct Unit* unit = GetUnit(bu->unit.index);
	
	if( &gBattleActor != bu )
		return 0;
	
	// HP <50%
	if( (*SkillTester)(unit, SID_Desperation) )
		if( unit->curHP < (unit->maxHP / 2) )
			return 1;
	
	return 0;
}



int JudgeSkillDesperationBat(struct BattleUnit* bu){
	
	struct Unit* unit = GetUnit(bu->unit.index);
	
	if( &gBattleActor != bu )
		return 0;
	
	// Todo
	if( (*SkillTester)(unit, SID_DesperationBat) )
		return 1;
	
	return 0;
}



