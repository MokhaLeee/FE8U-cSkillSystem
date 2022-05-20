#include "gbafe-chax.h"

/*
 *
 * Firstly null the check can-counter calc in function: SetBattleUnitWeapon
 * This has been set inside "WeaponEquip.c"
 * Then we shall rework on function: BattleInitTargetCanCounter
 * 
 */


void BattleInitTargetCanCounter(void) {
	
	// Here we shall make a modular Check function
	typedef int (*BNC_Fun) ();
	extern BNC_Fun BattleCheckNullCounterLoop[];
	
	BNC_Fun *it = &BattleCheckNullCounterLoop[0];
	
	while( *it )
	{
		int can_counter = (*it++)();
		
		if( NULL_COUNTER == can_counter ){
			gBattleTarget.weapon = 0;
			gBattleTarget.canCounter = 0;
			return;
		}
		else if( FORCE_COUNTER == can_counter )
			return;
	}
}




// For Modular Check Loop

int BCanCounter_CheckEgg(){
	
	// Target cannot counter if it is a gorgon egg
	return UNIT_IS_GORGON_EGG(&gBattleTarget.unit);
}


int BCanCounter_WpnAttr(){
	
	// Target cannot counter if either units are using "uncounterable" weapons
	u32 attr = gBattleActor.weaponAttributes | gBattleTarget.weaponAttributes;
	
	if( 0 == (attr & IA_UNCOUNTERABLE) )
		return NORMAL_COUNTER;
	else
		return NULL_COUNTER;

}


int BCanCounter_UnitStat(){
	
	struct BattleUnit* bu = &gBattleTarget;
	
	switch (bu->unit.statusIndex) 
	{

		case UNIT_STATUS_SLEEP:
		case UNIT_STATUS_PETRIFY:
		case UNIT_STATUS_13:
			return NULL_COUNTER;

		
		case UNIT_STATUS_BERSERK:
			
			// Target cannot counter if a berserked player unit is attacking another player unit
			
			if( UNIT_FACTION(&gBattleActor.unit) == FACTION_BLUE )
				if( UNIT_FACTION(&gBattleTarget.unit) == FACTION_BLUE )
					return NULL_COUNTER;

		
		default:
			return NORMAL_COUNTER;

	} // switch (bu->unit.statusIndex)
	
	
}


int BCanCounter_CheckRange(){
	
	struct BattleUnit* bu = &gBattleTarget;
	struct Unit* unit_tar = GetUnit(gBattleTarget.unit.index);
	
	if( !new_IsItemCoveringRange(bu->weapon, gBattleStats.range, unit_tar) )
		return NULL_COUNTER;
	
	if( bu->weaponSlotIndex == 0xFF )
		return NULL_COUNTER;
	
	return NORMAL_COUNTER;
}


