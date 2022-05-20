#include "gbafe-chax.h"


// For Modular Range Getter
int RangeMaxGetter_CombatArtBonus(struct Unit* unit, u16 item, int cur){
	
	const struct CombatArtInfo *info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	// sine the flag is set for both attacker and defender
	if( !IsFlagCombatArt(unit, 0) )
		return cur;
	
	return cur + info->range_bouns;

}

int RangeMaxGetter_CombatArtFix(struct Unit* unit, u16 item, int cur){
	
	const struct CombatArtInfo *info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	// sine the flag is set for both attacker and defender
	if( !IsFlagCombatArt(unit, 0) )
		return cur;
	
	if( !info->unnormal_range )
		return cur;
	
	switch( gpBattleFlagExt->combatArt_id )
	{
		case CA_PointBlankVolley:
			cur = 1;
			break;
			
		default:
			break;
	}

	
	return cur;
}


int RangeMinGetter_CombatArtBonus(struct Unit* unit, u16 item, int cur){
		
	return cur;
}


int RangeMinGetter_CombatArtFix(struct Unit* unit, u16 item, int cur){
	
	const struct CombatArtInfo *info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	// sine the flag is set for both attacker and defender
	if( !IsFlagCombatArt(unit, 0) )
		return cur;
	
	if( !info->unnormal_range )
		return cur;
	
	switch( gpBattleFlagExt->combatArt_id )
	{
		case CA_PointBlankVolley:
			cur = 1;
			break;
			
		default:
			break;
	}

	
	return cur;
}



// For Load Unit Hook
void LoadUnit_CombatArt(struct Unit* unit){
	
	struct NewBwlData* bwl;
	const u8 char_id = unit->pCharacterData->number;
	int count = 0;
	const struct CombatArtsROMList *list_char = &CharCombatArtsRomList[unit->pCharacterData->number];
	const struct CombatArtsROMList *list_class = &ClassCombatArtsRomList[unit->pClassData->number];
	
	
	// we use bwl table!
	if( !NBwl_HasBwl(char_id) )
		return;
	
	bwl = NBwl_GetBwlData(char_id);
	
	for( int i = 0; i < 5; i++ )
		bwl->combatArts[i] = 0;
	
	for( int i = 0; i < 4; i++ )
	{
		if( count > 4 )
			break;
		
		if( SKILL_VALID(list_char->default_art[i]) )
			bwl->combatArts[count++] = list_char->default_art[i];
		
		if( count > 4 )
			break;
		
		if( SKILL_VALID(list_class->default_art[i]) )
			bwl->combatArts[count++] = list_class->default_art[i];
	}
	
	if( unit->level < 10 )
		return;
	
	
	for( int i = 0; i < 4; i++ )
	{	
		if( count > 4 )
			break;
		
		if( SKILL_VALID(list_char->master_art[i]) )
			bwl->combatArts[count++] = list_char->master_art[i];
		
		if( count > 4 )
			break;
		
		if( SKILL_VALID(list_class->master_art[i]) )
			bwl->combatArts[count++] = list_class->master_art[i];
	}
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
			// Sword
			
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
				attacker->battleSilencerRate += 50;
				break;
				
			case CA_RupturedHeaven:
			case CA_SublimeHeaven:
			case CA_HeavensFall:
				attacker->battleAttack += MagGetter(unit_act);
				break;
			
			
			// Lance
			case CA_FrozenLance:
				attacker->battleAttack += SklGetter(unit_act);
				break;
			
			case CA_GlowingEmber:
				attacker->battleAttack += DefGetter(unit_act);
				break;
			
			case CA_Vengeance:
				attacker->battleAttack += 
					HpMaxGetter(unit_act) - HpCurGetter(unit_act);
				break;
				
			case CA_LanceJab:
				attacker->battleAttack += SpdGetter(unit_act);
				break;
			
			
			// Axe
			case CA_LightningAxe:
				attacker->battleAttack += ResGetter(unit_act);
				break;
			
			case CA_ArmoredStrike:
				attacker->battleAttack += DefGetter(unit_act);
				break;
			
			
			
			default:
				break;
		}
	
	return;
	
}


// For Check Can Counter
int BCanCounter_CombatArt(){
	
	if( gBattleActor.unit.index != gpBattleFlagExt->combat_unit )
		return NORMAL_COUNTER;
	
	const struct CombatArtInfo *info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	if( 0 == info )
		return NORMAL_COUNTER;
	
	if( 0 == info->special_eff )
		return NORMAL_COUNTER;
	
	// Check Combat Art
	switch(gpBattleFlagExt->combatArt_id)
	{
		case CA_Windsweep:
			return NULL_COUNTER;
		
		
		default:
			return NORMAL_COUNTER;
	}
		

}



// For Post-Action Hook
void PostAction_CombatArtDebuff(ProcPtr proc){
	
	extern void ForEachUnitInRange(void*);
	
	if( !gpBattleFlagExt->isCombat )
		return;
	
	if( !gpBattleFlagExt->combatArt_hitted )
		return;
	
	struct Unit* unit_tar = GetUnit(gActionData.targetIndex);
	const struct CombatArtInfo* info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
	
	BmMapFill(gBmMapMovement, NU_MOVE_MAP);
	BmMapFill(gBmMapRange, NU_RANGE_MAP);
	GenerateUnitStandingReachRange(unit_tar, 0b11);
	InitTargets(gActiveUnit->xPos, gActiveUnit->yPos);
	ForEachUnitInRange(AddUnitToTargetListIfNotAllied);
	
	if( info->is_gravity )
	{
		MU_EndAll();
		SMS_UpdateFromGameData();
		
		if( !info->AOE_Debuff )
		{
			StartMapAnim_Gravity(unit_tar, proc);
			SetUnitStatus(unit_tar, UNIT_NEW_STATUS_GRAVITY);
		}
		
		else
			for( int i = 0; i < GetSelectTargetCount(); i++ )
			{
				struct Unit* unit_tmp = GetUnit( GetTarget(i)->uid );
			
				StartMapAnim_Gravity(unit_tmp, proc);
				SetUnitStatus(unit_tmp, UNIT_NEW_STATUS_GRAVITY);
			}
		return;
	}
	
	
	else if( info->debuff_atk )
	{
		MU_EndAll();
		SMS_UpdateFromGameData();
		
		if( !info->AOE_Debuff ){
			StartMapAnim_Gravity(unit_tar, proc);
			SetUnitStatus(unit_tar, UNIT_NEW_STATUS_Weaken);
		}
		else{
			for( int i = 0; i < GetSelectTargetCount(); i++ )
			{
				struct Unit* unit_tmp = GetUnit( GetTarget(i)->uid );
			
				StartMapAnim_Gravity(unit_tmp, proc);
				SetUnitStatus(unit_tmp, UNIT_NEW_STATUS_Weaken);
			}
		}
		return;
	}
	
	
	else if( info->debuff_def )
	{
		MU_EndAll();
		SMS_UpdateFromGameData();
		
		if( !info->AOE_Debuff ){
			StartMapAnim_Gravity(unit_tar, proc);
			SetUnitStatus(unit_tar, UNIT_NEW_STATUS_ExposeDef);
		}
		else{
			for( int i = 0; i < GetSelectTargetCount(); i++ )
			{
				struct Unit* unit_tmp = GetUnit( GetTarget(i)->uid );
				
				StartMapAnim_Gravity(unit_tmp, proc);
				SetUnitStatus(unit_tmp, UNIT_NEW_STATUS_ExposeDef);
			}
		}
		return;
	}
	
	else if( info->debuff_res )
	{
		MU_EndAll();
		SMS_UpdateFromGameData();
		
		if( !info->AOE_Debuff ){
			StartMapAnim_Gravity(unit_tar, proc);
			SetUnitStatus(unit_tar, UNIT_NEW_STATUS_ExposeRes);
		}
		else{
			for( int i = 0; i < GetSelectTargetCount(); i++ )
			{
				struct Unit* unit_tmp = GetUnit( GetTarget(i)->uid );
				
				StartMapAnim_Gravity(unit_tmp, proc);
				SetUnitStatus(unit_tmp, UNIT_NEW_STATUS_ExposeRes);
			}
		}
		return;
	}
	
	else if( info->debuff_Silence )
	{
		MU_EndAll();
		SMS_UpdateFromGameData();
		
		if( !info->AOE_Debuff ){
			StartMapAnim_Gravity(unit_tar, proc);
			SetUnitStatusExt(unit_tar, UNIT_STATUS_SILENCED, 1);
		}
		else{
			for( int i = 0; i < GetSelectTargetCount(); i++ )
			{
				struct Unit* unit_tmp = GetUnit( GetTarget(i)->uid );
				
				StartMapAnim_Gravity(unit_tmp, proc);
				SetUnitStatusExt(unit_tar, UNIT_STATUS_SILENCED, 1);
			}
		}
		return;
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




