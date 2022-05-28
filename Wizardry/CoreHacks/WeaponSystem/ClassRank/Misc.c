#include "gbafe-chax.h"

// For Unit WType Growth
u8 GetClassRankExpGain(u8 class_id){
	
	u8 rank_exp = GetClassRomDataExpa(class_id)->RankExp;
	
	if( rank_exp > 0 )
		return rank_exp;
	
	if( CA_PROMOTED & gClassData[class_id].attributes )
		return 4;
	else
		return 0x10;
}



// For B2U Hook
void B2U_ClassRank(struct Unit* unit, struct BattleUnit* bu){
	
	int newWExp = NewGetBattleUnitUpdatedWeaponExp(bu, ITYPE_CLASS);
	
	if( newWExp > 0 )
		SetWExp(unit, ITYPE_CLASS, newWExp);
	
	if( newWExp >= WPN_EXP_S )
		SetUnitMasterClass(unit, unit->pClassData->number);
}