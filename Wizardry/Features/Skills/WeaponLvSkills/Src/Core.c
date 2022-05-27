#include "gbafe-chax.h"

void BC_WeaponLvSkills(struct BattleUnit* actor, struct BattleUnit* target){
	
	struct Unit* unit_act = GetUnit(actor->unit.index);
	// struct Unit* unit_tar = GetUnit(target->unit.index);
	
	u16 weapon = GetUnitEquippedWeapon(unit_act);
	int wType = GetItemType(weapon);
	
	switch(wType){
		
		case ITYPE_SWORD:
			if( (*SkillTester)(unit_act, SID_SwordLv5) ){
				actor->battleAvoidRate += 15;
				actor->battleCritRate += 10;
				actor->battleSilencerRate += 10;
			}
			else if( (*SkillTester)(unit_act, SID_SwordLv4) ){
				actor->battleAvoidRate += 10;
				actor->battleCritRate += 10;
			}
			else if( (*SkillTester)(unit_act, SID_SwordLv3) ){
				actor->battleAvoidRate += 7;
				actor->battleCritRate += 7;
			}
			else if( (*SkillTester)(unit_act, SID_SwordLv2) ){
				actor->battleAvoidRate += 5;
				actor->battleCritRate += 5;
			}
			else if( (*SkillTester)(unit_act, SID_SwordLv1) ){
				actor->battleAvoidRate += 3;
				actor->battleCritRate += 3;
			}
			break;
		
		
		
		case ITYPE_LANCE:
			if( (*SkillTester)(unit_act, SID_LanceLv5) ){
				actor->battleHitRate += 20;
				actor->battleDefense += 5;
			}
			else if( (*SkillTester)(unit_act, SID_LanceLv4) ){
				actor->battleHitRate += 12;
				actor->battleDefense += 4;
			}
			else if( (*SkillTester)(unit_act, SID_LanceLv3) ){
				actor->battleHitRate += 9;
				actor->battleDefense += 3;
			}
			else if( (*SkillTester)(unit_act, SID_LanceLv2) ){
				actor->battleHitRate += 6;
				actor->battleDefense += 2;
			}
			else if( (*SkillTester)(unit_act, SID_LanceLv1) ){
				actor->battleHitRate += 3;
				actor->battleDefense += 1;
			}
			break;
		
		
		
		case ITYPE_AXE:
			if( (*SkillTester)(unit_act, SID_AxeLv5) ){
				actor->battleAttack += 5;
				actor->battleCritRate += 15;
			}
			else if( (*SkillTester)(unit_act, SID_AxeLv4) ){
				actor->battleAttack += 4;
				actor->battleCritRate += 8;
			}
			else if( (*SkillTester)(unit_act, SID_AxeLv3) ){
				actor->battleAttack += 3;
				actor->battleCritRate += 6;
			}
			else if( (*SkillTester)(unit_act, SID_AxeLv2) ){
				actor->battleAttack += 2;
				actor->battleCritRate += 4;
			}
			else if( (*SkillTester)(unit_act, SID_AxeLv1) ){
				actor->battleAttack += 1;
				actor->battleCritRate += 2;
			}
			break;
		
		
		
		case ITYPE_BOW:
			if( (*SkillTester)(unit_act, SID_BowLv5) ){
				actor->battleHitRate += 25;
			}
			else if( (*SkillTester)(unit_act, SID_BowLv4) ){
				actor->battleHitRate += 20;
			}
			else if( (*SkillTester)(unit_act, SID_BowLv3) ){
				actor->battleHitRate += 15;
			}
			else if( (*SkillTester)(unit_act, SID_BowLv2) ){
				actor->battleHitRate += 10;
			}
			else if( (*SkillTester)(unit_act, SID_BowLv1) ){
				actor->battleHitRate += 5;
			}
			break;
		
		
		case ITYPE_ANIMA:
		case ITYPE_LIGHT:
		case ITYPE_DARK:
			if( (*SkillTester)(unit_act, SID_BMagLv5) ){
				actor->battleAttack += 7;
				actor->battleHitRate += 15;
			}
			else if( (*SkillTester)(unit_act, SID_BMagLv4) ){
				actor->battleAttack += 4;
				actor->battleHitRate += 12;
			}
			else if( (*SkillTester)(unit_act, SID_BMagLv3) ){
				actor->battleAttack += 3;
				actor->battleHitRate += 9;
			}
			else if( (*SkillTester)(unit_act, SID_BMagLv2) ){
				actor->battleAttack += 2;
				actor->battleHitRate += 6;
			}
			else if( (*SkillTester)(unit_act, SID_BMagLv1) ){
				actor->battleAttack += 1;
				actor->battleHitRate += 3;
			}
			break;
		
		default:
			break;
	} // Switch

	for( int i = 0; i < UNIT_ITEM_COUNT; i++ )
		if( ITYPE_STAFF == GetItemType(unit_act->items[i]) ){
			
			if( (*SkillTester)(unit_act, SID_WMagLv5) ){
				actor->battleAvoidRate += 25;
			}
			else if( (*SkillTester)(unit_act, SID_WMagLv4) ){
				actor->battleAvoidRate += 20;
			}
			else if( (*SkillTester)(unit_act, SID_WMagLv3) ){
				actor->battleAvoidRate += 15;
			}
			else if( (*SkillTester)(unit_act, SID_WMagLv2) ){
				actor->battleAvoidRate += 10;
			}
			else if( (*SkillTester)(unit_act, SID_WMagLv1) ){
				actor->battleAvoidRate += 5;
			}
			break;
		}


}




int RangeGetter_WeaponLvSkills(struct Unit* unit, u16 item, int cur){
	
	const int wtype = GetItemType(item);
	
	switch( wtype ){
		
		case ITYPE_BOW:
			if( (*SkillTester)(unit, SID_BowLv5) )
				cur = cur + 1;
			
			break;
		
		
		case ITYPE_STAFF:
			if( (*SkillTester)(unit, SID_WMagLv5) )
				cur = cur + 5;
			
			break;
			
			
		default:
			break;
	}
	
	return cur;
}