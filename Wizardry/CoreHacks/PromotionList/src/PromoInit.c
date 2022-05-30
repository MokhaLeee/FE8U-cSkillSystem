#include "gbafe-chax.h"
#include "Promotion.h"

// Promo Init core
int sub_80CC6D4(struct Proc_PromoInit* proc){
	
	struct Unit* unit = GetUnitFromCharId(proc->charId);
	
	proc->item = unit->items[proc->promotionItemSlot];
	proc->classOld = unit->pClassData->number;
	
	const u8* class_list = GetUnitPromoList(proc->charId, unit->pClassData->number, proc->item);
	u8 sorted_list[7] = {0};
	
	proc->count = 0;
	
	for( int i = 0; i < PROMO_CLASS_LIST_MAX; i++ )
		if( class_list[i] != 0 )
			sorted_list[ proc->count++ ] = class_list[i];
	
	if( 0 == proc->count ){
		if( PROMO_INIT_CONTEXT_BMMAP == proc->promContextId ){
			BMapDispResume();
			RefreshBMapGraphics();
		}
		return 2;
	}
	else if( 1 == proc->count ){
		proc->unk35 = sorted_list[0];
		proc->unk34 = 0;
	}
	else{
		proc->unk35 = sorted_list[0];
		proc->unk34 = 1;
	}
	// Here we will not consider trainee


	extern void MakePromotionScreen(struct Proc_PromoInit*, u8 charId, u8 mode);
	
	MakePromotionScreen(proc, proc->charId, 1);
	return 1;

}