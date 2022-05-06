#include "gbafe-chax.h"


// For Modular Range Getter
int GetCombatArt_WeaponRangeMaxBonus(struct Unit* unit, u16 item){
	
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
	bwl->combatArts[0] = CA_CurvedShot;
	bwl->combatArts[1] = CA_HeavyDraw;
	bwl->combatArts[2] = CA_WrathStrike;
	bwl->combatArts[3] = CA_TempestLance;
	
}


// For Pre-Battle Calc
void BC_CombatArtBonus(struct BattleUnit* attacker, struct BattleUnit* defender){
	
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
	
}
