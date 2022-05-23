#include "gbafe-chax.h"



void BattleGenerateHitAttributes(struct BattleUnit* attacker, struct BattleUnit* defender) {
	extern s8 BattleRoll2RN(u16 threshold, s8 simResult);
	extern s8 BattleRoll1RN(u16 threshold, s8 simResult);
	extern void BattleCheckPetrify(struct BattleUnit* attacker, struct BattleUnit* defender);
	
	short attack, defense;
	
	gBattleStats.damage = 0;

	// Miss
	if (!BattleRoll2RN(gBattleStats.hitRate, TRUE)) {
		gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_MISS;
		return;
	}
	
	// if combat-art set hitted bits in ext-flag
	// for post-action debuff
	if( gpBattleFlagExt->isCombat && attacker->unit.index == gpBattleFlagExt->combat_unit )
		gpBattleFlagExt->combatArt_hitted = 1;

	attack = gBattleStats.attack;
	defense = gBattleStats.defense;

	gBattleStats.damage = attack - defense;
	
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
			gBattleStats.damage = gBattleStats.damage * 3;
		}
	}
	
	
	// Apply damage
	if (gBattleStats.damage < 0)
		gBattleStats.damage = 0;
	
	// Todo: 破败之刃
	// gBattleStats.damage = gBattleStats.damage + 1;
	
	
	if (gBattleStats.damage > BATTLE_MAX_DAMAGE)
		gBattleStats.damage = BATTLE_MAX_DAMAGE;
	
	// 石化
	BattleCheckPetrify(attacker, defender);

	if (gBattleStats.damage != 0)
		attacker->nonZeroDamage = TRUE;
	
}



void BattleGenerateHitEffects(struct BattleUnit* attacker, struct BattleUnit* defender) {
	attacker->wexpMultiplier++;

	if (!(gBattleHitIterator->attributes & BATTLE_HIT_ATTR_MISS)) {
		switch (GetItemWeaponEffect(attacker->weapon)) {

		case WPN_EFFECT_POISON:
			// Poison defender
			defender->statusOut = UNIT_STATUS_POISON;
			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_POISON;

			// "Ungray" defender if it was petrified (as it won't be anymore)
			if (defender->unit.statusIndex == UNIT_STATUS_PETRIFY || defender->unit.statusIndex == UNIT_STATUS_13)
				defender->unit.state = defender->unit.state &~ US_UNSELECTABLE;

			break;

		case WPN_EFFECT_HPHALVE:
			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_HPHALVE;
			break;

            } // switch (GetItemWeaponEffect(attacker->weapon))


		// Check for Combat-Art: CA_Subdue(手下留情)
		if( attacker->unit.index == gpBattleFlagExt->combat_unit )
			if( CA_Subdue == gpBattleFlagExt->combatArt_id )
				if( gBattleStats.damage > (defender->unit.curHP - 1) )
					gBattleStats.damage = defender->unit.curHP - 1;


		if (gBattleStats.damage > defender->unit.curHP)
			gBattleStats.damage = defender->unit.curHP;
		
		defender->unit.curHP -= gBattleStats.damage;

		if (defender->unit.curHP < 0)
			defender->unit.curHP = 0;


		if (GetItemWeaponEffect(attacker->weapon) == WPN_EFFECT_HPDRAIN) 
		{
			if (attacker->unit.maxHP < (attacker->unit.curHP + gBattleStats.damage))
				attacker->unit.curHP = attacker->unit.maxHP;
			else
				attacker->unit.curHP += gBattleStats.damage;

			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_HPSTEAL;
		}


		if (GetItemWeaponEffect(attacker->weapon) == WPN_EFFECT_PETRIFY) {
			switch (gRAMChapterData.chapterPhaseIndex) {

			case FACTION_BLUE:
				if (UNIT_FACTION(&defender->unit) == FACTION_BLUE)
					defender->statusOut = UNIT_STATUS_13;
				else
					defender->statusOut = UNIT_STATUS_PETRIFY;

				break;

			case FACTION_RED:
				if (UNIT_FACTION(&defender->unit) == FACTION_RED)
					defender->statusOut = UNIT_STATUS_13;
				else
					defender->statusOut = UNIT_STATUS_PETRIFY;

				break;

			case FACTION_GREEN:
				if (UNIT_FACTION(&defender->unit) == FACTION_GREEN)
					defender->statusOut = UNIT_STATUS_13;
				else
					defender->statusOut = UNIT_STATUS_PETRIFY;

				break;

			} // switch (gRAMChapterData.chapterPhaseIndex)

			gBattleHitIterator->attributes |= BATTLE_HIT_ATTR_PETRIFY;
		}

	}

	gBattleHitIterator->hpChange = gBattleStats.damage;

	if (!(gBattleHitIterator->attributes & BATTLE_HIT_ATTR_MISS) )
	{
		// For combat Art
		// attacker->weapon = GetItemAfterUse(attacker->weapon);
		u16 weapon = attacker->weapon;
		
		if (0 == (GetItemAttributes(weapon) & IA_UNBREAKABLE) )
		{
			if( (&gBattleActor != attacker) || !gpBattleFlagExt->isCombat )
				weapon -= (1 << 8);
			else
				weapon -= (GetCombatArtInfo(gpBattleFlagExt->combatArt_id)->cost << 8);
			
			s8 item_use = (s8)ITEM_USES(weapon);
			
			attacker->weapon = item_use <= 0
				? 0
				: weapon;
		}
		
		
		

		if (!attacker->weapon)
			attacker->weaponBroke = TRUE;
	}
}




