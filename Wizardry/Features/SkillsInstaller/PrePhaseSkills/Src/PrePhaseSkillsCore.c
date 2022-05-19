#include "gbafe-chax.h"

void JudgePrePhaseRenewal(struct Unit* unit, u8 terrain){
	
	// org 8025948
	
	int heal_amount = 0;
	
	if( HpMaxGetter(unit) <= HpCurGetter(unit) )
		return;
	
	heal_amount += GetTerrainHealAmount(terrain);
	
	if( (*SkillTester)(unit, SID_Renewal) )
		heal_amount += _lib_div( HpMaxGetter(unit) * 3, 10);
	
	
	if( 0 == heal_amount )
		return;
	
	AddTarget(unit->xPos, unit->yPos, unit->index, heal_amount);
	

	// return 802598E
	return;
}