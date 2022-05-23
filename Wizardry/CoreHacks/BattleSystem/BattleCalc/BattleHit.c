#include "gbafe-chax.h"



void BattleGenerateHitAttributes(struct BattleUnit* actor, struct BattleUnit* target) {
	extern s8 BattleRoll2RN(u16 threshold, s8 simResult);
	extern s8 BattleRoll1RN(u16 threshold, s8 simResult);
	extern void BattleCheckPetrify(struct BattleUnit* actor, struct BattleUnit* target);
	
	short attack, defense;
	
	gBattleStats.damage = 0;

	// Miss
	if (!BattleRoll2RN(gBattleStats.hitRate, TRUE)) {
		gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_MISS;
		return;
	}
	
	// if combat-art set hitted bits in ext-flag
	// for post-action debuff
	if( gpBattleFlagExt->isCombat && actor->unit.index == gpBattleFlagExt->combat_unit )
		gpBattleFlagExt->combatArt_hitted = 1;

	attack = gBattleStats.attack;
	defense = gBattleStats.defense;

	gBattleStats.damage = attack - defense;
	
	// Minus zero
	if (gBattleStats.damage < 0)
		gBattleStats.damage = 0;
	
	if( (*SkillTester)(&actor->unit, SID_FlashingBladePlus) )
		gBattleStats.damage += 3;
	
	// 瞬杀	
	if (BattleRoll1RN(gBattleStats.critRate, FALSE) ) 
	{
		if ( BattleRoll1RN(gBattleStats.silencerRate, FALSE) )
		{
			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_SILENCER;
			gBattleStats.damage = BATTLE_MAX_DAMAGE;
		} 
		else 
		{
			gBattleHitIterator->attributes = gBattleHitIterator->attributes | BATTLE_HIT_ATTR_CRIT;
		
			gBattleStats.damage = (*SkillTester)(&actor->unit, SID_InfinityEdge)
				? gBattleStats.damage * 3
				: gBattleStats.damage * 2;
		}
	}
	
	
	// Apply damage
	
	
	// Todo: 破败之刃
	if( (*SkillTester)(&actor->unit, SID_RuinedBlade) )
		gBattleStats.damage = gBattleStats.damage + 5;
	
	if( (*SkillTester)(&actor->unit, SID_RuinedBladePlus) )
		gBattleStats.damage = gBattleStats.damage + 5;
	
	if (gBattleStats.damage > BATTLE_MAX_DAMAGE)
		gBattleStats.damage = BATTLE_MAX_DAMAGE;
	
	// 石化
	BattleCheckPetrify(actor, target);

	if (gBattleStats.damage != 0)
		actor->nonZeroDamage = TRUE;
	
}



void BattleGenerateHitEffects(struct BattleUnit* actor, struct BattleUnit* target) {
	actor->wexpMultiplier++;

	if (!(gBattleHitIterator->attributes & BATTLE_HIT_ATTR_MISS)) {
		switch (GetItemWeaponEffect(actor->weapon)) {

		case WPN_EFFECT_POISON:
			// Poison target
			target->statusOut = UNIT_STATUS_POISON;
			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_POISON;

			// "Ungray" target if it was petrified (as it won't be anymore)
			if (target->unit.statusIndex == UNIT_STATUS_PETRIFY || target->unit.statusIndex == UNIT_STATUS_13)
				target->unit.state = target->unit.state &~ US_UNSELECTABLE;

			break;

		case WPN_EFFECT_HPHALVE:
			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_HPHALVE;
			break;

            } // switch (GetItemWeaponEffect(actor->weapon))


		// Check for Combat-Art: CA_Subdue(手下留情)
		if( actor->unit.index == gpBattleFlagExt->combat_unit )
			if( CA_Subdue == gpBattleFlagExt->combatArt_id )
				if( gBattleStats.damage > (target->unit.curHP - 1) )
					gBattleStats.damage = target->unit.curHP - 1;


		if (gBattleStats.damage > target->unit.curHP)
			gBattleStats.damage = target->unit.curHP;
		
		target->unit.curHP -= gBattleStats.damage;

		if (target->unit.curHP < 0)
			target->unit.curHP = 0;


		if (GetItemWeaponEffect(actor->weapon) == WPN_EFFECT_HPDRAIN) 
		{
			if (actor->unit.maxHP < (actor->unit.curHP + gBattleStats.damage))
				actor->unit.curHP = actor->unit.maxHP;
			else
				actor->unit.curHP += gBattleStats.damage;

			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_HPSTEAL;
		}


		if (GetItemWeaponEffect(actor->weapon) == WPN_EFFECT_PETRIFY) {
			switch (gRAMChapterData.chapterPhaseIndex) {

			case FACTION_BLUE:
				if (UNIT_FACTION(&target->unit) == FACTION_BLUE)
					target->statusOut = UNIT_STATUS_13;
				else
					target->statusOut = UNIT_STATUS_PETRIFY;

				break;

			case FACTION_RED:
				if (UNIT_FACTION(&target->unit) == FACTION_RED)
					target->statusOut = UNIT_STATUS_13;
				else
					target->statusOut = UNIT_STATUS_PETRIFY;

				break;

			case FACTION_GREEN:
				if (UNIT_FACTION(&target->unit) == FACTION_GREEN)
					target->statusOut = UNIT_STATUS_13;
				else
					target->statusOut = UNIT_STATUS_PETRIFY;

				break;

			} // switch (gRAMChapterData.chapterPhaseIndex)

			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_PETRIFY;
		}

	}

	gBattleHitIterator->hpChange = gBattleStats.damage;

	if (!(gBattleHitIterator->attributes & BATTLE_HIT_ATTR_MISS) )
	{
		// For combat Art
		// actor->weapon = GetItemAfterUse(actor->weapon);
		u16 weapon = actor->weapon;
		
		if (0 == (GetItemAttributes(weapon) & IA_UNBREAKABLE) )
		{
			if( (&gBattleActor != actor) || !gpBattleFlagExt->isCombat )
				weapon -= (1 << 8);
			else
				weapon -= (GetCombatArtInfo(gpBattleFlagExt->combatArt_id)->cost << 8);
			
			s8 item_use = (s8)ITEM_USES(weapon);
			
			actor->weapon = item_use <= 0
				? 0
				: weapon;
		}
		
		
		

		if (!actor->weapon)
			actor->weaponBroke = TRUE;
	}
}




