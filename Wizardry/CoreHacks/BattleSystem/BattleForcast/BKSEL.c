#include "gbafe-chax.h"


// Judge for double attack and weapon use
void AddWeaponStatsAfterRound(struct BattleUnit* bu, u8 *hit, int *item_use){
	
	int GetBattleUnitHitCount(struct BattleUnit* actor);

	const struct CombatArtInfo* info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	const int item_cost = IsFlagCombatArt(&bu->unit, 0)
		? info->cost
		: 1;
		
	struct BattleUnit* tar = (&gBattleActor == bu)
		? &gBattleTarget
		: &gBattleActor;
	
	const int round_count = 
		(1 + CheckCanDouble(bu, tar)) *
		GetBattleUnitHitCount(bu);
	
	for( int i = 0; i < round_count; i++ ){
		
		*item_use -= item_cost;
		
		if( *item_use <= 0 )
			break;
		
		(*hit)++;
		
	}
	
	
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
		
		if( 0 != IsUnitEffectiveAgainst(&gBattleTarget.unit, &gBattleActor.unit) )
			proc->tar_eff = 1;
		
		if( 0 != IsItemEffectiveAgainst(gBattleTarget.weaponBefore, &gBattleActor.unit) )
			proc->tar_eff = 1;
		
		if( (gBattleTarget.wTriangleHitBonus > 0) && (IA_REVERTTRIANGLE & gBattleTarget.weaponAttributes) )
			proc->tar_eff = 1;
	}
	
	
	// For Object x2x4
	extern const u8 Gfx_BkSel[11][0x40];
	
	switch(proc->act_hit){
		case 0:
		case 1:
			CopyTileGfxForObj(Gfx_BkSel[0], OBJ_VRAM0 + 0x5D00, 1, 2);
			CopyTileGfxForObj(Gfx_BkSel[0], OBJ_VRAM0 + 0x5D20, 1, 2);
			break;
		
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			CopyTileGfxForObj(Gfx_BkSel[1], OBJ_VRAM0 + 0x5D00, 1, 2);
			CopyTileGfxForObj(Gfx_BkSel[proc->act_hit], OBJ_VRAM0 + 0x5D20, 1, 2);
			break;
		
		default:
			CopyTileGfxForObj(Gfx_BkSel[1], OBJ_VRAM0 + 0x5D00, 1, 2);
			CopyTileGfxForObj(Gfx_BkSel[10], OBJ_VRAM0 + 0x5D20, 1, 2);
			break;
	};
	
	switch(proc->tar_hit){
		case 0:
		case 1:
			CopyTileGfxForObj(Gfx_BkSel[0], OBJ_VRAM0 + 0x5D40, 1, 2);
			CopyTileGfxForObj(Gfx_BkSel[0], OBJ_VRAM0 + 0x5D60, 1, 2);
			break;
		
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			CopyTileGfxForObj(Gfx_BkSel[1], OBJ_VRAM0 + 0x5D40, 1, 2);
			CopyTileGfxForObj(Gfx_BkSel[proc->tar_hit], OBJ_VRAM0 + 0x5D60, 1, 2);
			break;
		
		default:
			CopyTileGfxForObj(Gfx_BkSel[1], OBJ_VRAM0 + 0x5D40, 1, 2);
			CopyTileGfxForObj(Gfx_BkSel[10], OBJ_VRAM0 + 0x5D60, 1, 2);
			break;
	};
}





