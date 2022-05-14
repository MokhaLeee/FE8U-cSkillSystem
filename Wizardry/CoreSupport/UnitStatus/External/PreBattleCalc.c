#include "gbafe-chax.h"

void BC_UnitStatus (struct BattleUnit* bu, struct BattleUnit*){
	
	struct Unit* unit = GetUnit(bu->unit.index);
	const u8 index = GetUnitStatusIndex(unit);
	const struct UnitStatusInfo* info = GetStatusInfo(index);
	
	if( 1 == info->mag_atk )
		bu->weaponAttributes |= IA_MAGICDAMAGE;
	
	if( 1 == info->phys_atk )
		bu->weaponAttributes &= ~IA_MAGICDAMAGE;
	
	bu->battleAttack += info->dmg_bonus;
	bu->battleDefense += info->bu_def_bonus;
	bu->battleHitRate += info->hit_bonus;
	bu->battleAvoidRate += info->avo_bonus;
	bu->battleCritRate += info->crit_bonus;
	bu->battleSilencerRate += info->silencer_bonus;
	bu->battleDodgeRate += info->dodge_bonus;
}