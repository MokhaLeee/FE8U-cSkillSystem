#include "gbafe-chax.h"


// Judge for double attack and weapon use
void AddWeaponStatsAfterRound(struct BattleUnit* bu, u8 *hit, int *item_use){
	
	if( *item_use <= 0 )
		return;

	// Combat Art
	if( (bu == &gBattleActor) && (gpBattleFlagExt->isCombat) )
		if(bu->unit.index == gpBattleFlagExt->combat_unit)
		{
			const struct CombatArtInfo* info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
			
			if( 0 != info )
			{
				(*hit)++;
				(*item_use) -= info->cost;
				return;
			}
		}
	
	// normal attack
	(*hit)++;
	(*item_use)--;
	
	
	if( 0 == (IA_BRAVE & bu->weaponAttributes) )
		return;
	
	
	(*hit)++;
	(*item_use)--;
	
}




// Judge for double attack
void BKSEL_SetupHitAndSuchStats(struct Proc_BKSEL *proc){
	
	int act_itemuse = GetItemUses(gBattleActor.weaponBefore);
	int tar_itemuse = GetItemUses(gBattleTarget.weaponBefore);
	
	
	// judge attacker
	
	proc->act_hit = 0;
	proc->act_eff = 0;
	
	if( 0 != gBattleActor.weapon )
	{
		AddWeaponStatsAfterRound(&gBattleActor, &proc->act_hit, &act_itemuse);
		
		if( CheckCanDouble(&gBattleActor, &gBattleTarget) )
			AddWeaponStatsAfterRound(&gBattleActor, &proc->act_hit, &act_itemuse);
		
		if( 0 != IsUnitEffectiveAgainst(&gBattleActor.unit, &gBattleTarget.unit) )
			proc->act_eff = 1;
		
		if( 0 != IsItemEffectiveAgainst(gBattleActor.weaponBefore, &gBattleTarget.unit) )
			proc->act_eff = 1;
		
		if( (gBattleActor.wTriangleHitBonus > 0) && (IA_REVERTTRIANGLE & gBattleActor.weaponAttributes) )
			proc->act_eff = 1;
	}
	
	// judge target
	
	proc->tar_hit = 0;
	proc->tar_eff = 0;
		
	if( 0 != gBattleTarget.weapon )
	{
		AddWeaponStatsAfterRound(&gBattleTarget, &proc->tar_hit, &tar_itemuse);
		
		if( CheckCanDouble(&gBattleTarget, &gBattleActor) )
			AddWeaponStatsAfterRound(&gBattleTarget, &proc->tar_hit, &tar_itemuse);
		
		if( 0 != IsUnitEffectiveAgainst(&gBattleTarget.unit, &gBattleActor.unit) )
			proc->tar_eff = 1;
		
		if( 0 != IsItemEffectiveAgainst(gBattleTarget.weaponBefore, &gBattleActor.unit) )
			proc->tar_eff = 1;
		
		if( (gBattleTarget.wTriangleHitBonus > 0) && (IA_REVERTTRIANGLE & gBattleTarget.weaponAttributes) )
			proc->tar_eff = 1;
	}
}





