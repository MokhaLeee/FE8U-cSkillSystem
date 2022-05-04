#include "gbafe-chax.h"

/*
 * 判定规则：
 * 建一个以武器为index的列表，每个武器对应几个combat-art
 * 还需要对应角色，也即还需要有角色对应的技能清单，与熟练度绑定
 * 职业的清单与职业等级绑定
 * 另外每个类型的武器还有一个通用的战技效果
 * 最后是圣遗物战技：必须只有武器+人物均存在的情况下才行
 * 基于此，我们有必要也为战技构建一个fast-list
 */


/*
 * Build List
 */
struct CombatArtList* BuildCombatArtList(struct Unit* unit){
	
	extern void *gpCommonSpace;
	struct CombatArtList* list = gpCommonSpace;
	
	list->unit_id = unit->index;
	list->count = 0;
	
	// Judge for each weapon
	for( int i = 0; i < UNIT_ITEM_COUNT; i++ )
	{
		
		u8 item_id = ITEM_INDEX(unit->items[i]);
		
		if( (0 != item_id) && (0 != (IA_WEAPON & GetItemAttributes(item_id))) )
			for( int j = 0; j < 3; j++ )
			{
				u8 ca_index = WeaponCombatArtList[item_id].ca[j];
				
				if( 0 != ca_index )
				{
					
					list->list[list->count] = ca_index ;
					
					list->count++;
					if( list->count >= COMBATART_LIST_MAXNUM )
						goto goto_end;
				}
			}
	}
	
	
goto_end:	
	// sort array
	
	for( int i = 0; i < list->count; i++ ){
		
		u8 j;
		u8 tmp = list->list[i];
		
		for( j = i; j > 0; j-- )
			if( list->list[j-1] < tmp )
				list->list[j] = list->list[j-1];
			
		list->list[j] = tmp;
	}
		
	if( list->count > 0xA )
		list->count = 0xA;
	
	return list;
}


struct CombatArtList* GetCombatArtList(struct Unit* unit){
	
	extern void *gpCommonSpace;
	struct CombatArtList* list = gpCommonSpace;
	
	if( list->unit_id == unit->index )
		return list;
	
	else
		return BuildCombatArtList(unit);
	
}



int UnitHasCombatArt(struct Unit* unit){
	
	struct CombatArtList* list = GetCombatArtList(unit);
	
	return (0 != list->count);
	
}

int CanUnitUseCombatArt(struct Unit* unit, u8 index){
	
	struct CombatArtList* list = GetCombatArtList(unit);
	
	for( int i = 0; i < list->count; i++ )
		if( index == list->list[i] )
			return 1;
	
	return 0;
}

const struct CombatArtInfo* GetCombatArtInfo(u8 index){
	
	return CombatArtInfoTable[index];
	
};