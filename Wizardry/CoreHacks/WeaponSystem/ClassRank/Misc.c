#include "gbafe-chax.h"

// For Unit WType Growth
u8 GetClassRankExpGain(u8 class_id){
	
	u8 rank_exp = GetClassRomDataExpa(class_id)->RankExp;
	
	return rank_exp == 0
		? 0x20
		: rank_exp;

}



// For B2U Hook
void B2U_ClassRank(struct Unit* unit, struct BattleUnit* bu){
	
	int newWExp = NewGetBattleUnitUpdatedWeaponExp(bu, ITYPE_CLASS);
	
	if( newWExp > 0 )
		SetWExp(unit, ITYPE_CLASS, newWExp);
	
	if( newWExp >= WPN_EXP_S )
		SetUnitMasterClass(unit, unit->pClassData->number);
}