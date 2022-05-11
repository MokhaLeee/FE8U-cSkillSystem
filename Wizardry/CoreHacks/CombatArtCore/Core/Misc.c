#include "gbafe-chax.h"


// For Modular Range Getter
int RangeGetter_CombatArtBonus(struct Unit* unit, u16 item){
	
	// sine the flag is set for both attacker and defender
	if( 1 == gpBattleFlagExt->isCombat )
		if( unit->index == gpBattleFlagExt->combat_unit )
			return GetCombatArtInfo(gpBattleFlagExt->combatArt_id)->range_bouns;

	
	return 0;
}



// For Load Unit Hook
void LoadUnit_CombatArt(struct Unit* unit){
	
	struct NewBwlData* bwl;
	u8 char_id = unit->pCharacterData->number;
	
	// we use bwl table!
	if( !NBwl_HasBwl(char_id) )
		return;
	
	bwl = NBwl_GetBwlData(char_id);
	
	// W.I.P.
	bwl->combatArts[0] = CA_HeavyDraw;
	bwl->combatArts[1] = CA_WrathStrike;
	bwl->combatArts[2] = CA_TempestLance;
	
}


// For Pre-Battle Calc
void BC_CombatArtBonus(struct BattleUnit* attacker, struct BattleUnit* defender){
	
	struct Unit* unit_act = GetUnit(attacker->unit.index);
	
	if( 0 == gpBattleFlagExt->isCombat )
		return;
	
	if( attacker->unit.index != gpBattleFlagExt->combat_unit )
		return;
	
	const struct CombatArtInfo *info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	if( 0 == info )
		return;
	
	attacker->battleAttack += info->mt;
	attacker->battleHitRate += info->hit;
	attacker->battleAvoidRate += info->avo;
	attacker->battleCritRate += info->crit;
	
	if( 1 == info->is_magic )
		attacker->weaponAttributes |= IA_MAGICDAMAGE;
	
	// Judge for atk_bonus
	if( 1 == info->atk_bonus )
		switch (gpBattleFlagExt->combatArt_id)
		{
			case CA_Soulblade:
				attacker->battleAttack += ResGetter(unit_act);
				break;
			
			case CA_FinesseBlade:
				attacker->battleAttack += SklGetter(unit_act);
				break;
				
			case CA_SwordDance:
				// W.I.P.
				break;
			
			case CA_Assassinate:
				attacker->battleSilencerRate += 
					GetUnitSkill(unit_act) + GetUnitLuck(unit_act);
				break;
				
			case CA_RupturedHeaven:
			case CA_SublimeHeaven:
				attacker->battleAttack += MagGetter(unit_act);
				break;
			
			default:
				break;
		}
	
	return;
	
}


// For Check Can Counter
int BNullCounter_CombatArt(){
	
	if( gBattleActor.unit.index != gpBattleFlagExt->combat_unit )
		return 0;
	
	const struct CombatArtInfo *info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	if( 0 == info )
		return 0;
	
	if( 0 == info->special_eff )
		return 0;
	
	// Check Combat Art
	switch(gpBattleFlagExt->combatArt_id)
	{
		case CA_Windsweep:
			return NORMAL_COUNTER;
		
		
		default:
			return NORMAL_COUNTER;
	}
		

}



// COMBAT_ART_ICON
// For Icon Display
const void* GetCombatArtIconGfx(int index){
	
	extern const void* GetFE16MasteryIconGfx(int index);
	
	if( !SKILL_VALID(index) )
		return 0;
	
	const struct CombatArtInfo *info = GetCombatArtInfo(index);
	
	if( 0 == info )
		return 0;
	
	if( 0 == info->icon )
		return GetFE16MasteryIconGfx(info->weapon_type);
	else
		return info->icon;
	
}

