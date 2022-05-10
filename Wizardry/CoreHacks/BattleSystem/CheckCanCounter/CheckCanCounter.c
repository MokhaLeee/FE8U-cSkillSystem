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
		if( 0 != (*it++)() )
		{
			gBattleTarget.weapon = 0;
			gBattleTarget.canCounter = 0;
			return;
		}
}




// For Modular Check Loop

int BNC_CheckEgg(){
	
	// Target cannot counter if it is a gorgon egg
	return UNIT_IS_GORGON_EGG(&gBattleTarget.unit);
}


int BNC_WpnAttr(){
	
	// Target cannot counter if either units are using "uncounterable" weapons
	u32 attr = gBattleActor.weaponAttributes | gBattleTarget.weaponAttributes;
	
	return 0 != (attr & IA_UNCOUNTERABLE);

}


int BNC_UnitStat(){
	
	struct BattleUnit* bu = &gBattleTarget;
	
	switch (bu->unit.statusIndex) 
	{

		case UNIT_STATUS_SLEEP:
		case UNIT_STATUS_PETRIFY:
		case UNIT_STATUS_13:
			return 1;

		
		case UNIT_STATUS_BERSERK:
			
			// Target cannot counter if a berserked player unit is attacking another player unit
			
			if( UNIT_FACTION(&gBattleActor.unit) == FACTION_BLUE )
				if( UNIT_FACTION(&gBattleTarget.unit) == FACTION_BLUE )
					return 1;

		
		default:
			return 0;

	} // switch (bu->unit.statusIndex)
	
	
}


int BNC_CheckRange(){
	
	struct BattleUnit* bu = &gBattleTarget;
	
	if( !IsItemCoveringRange(bu->weapon, gBattleStats.range) )
		return 1;
	
	if( bu->weaponSlotIndex == 0xFF )
		return 1;
	
	return 0;
}


