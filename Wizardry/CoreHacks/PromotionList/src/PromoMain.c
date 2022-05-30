#include "gbafe-chax.h"
#include "Promotion.h"

// ProcPromo_CheckBranches
void sub_80CC5B4(struct Proc_PromoMain* proc){
	struct Proc_PromoInit* parent = proc->proc_parent;
	
	switch( parent->promContextId ){
		
		case PROMO_INIT_CONTEXT_PREP:
		case PROMO_INIT_CONTEXT_BMMAP:
			
			if( 0 == parent->unk34 ){
				proc->promoClass = parent->unk35;
				Proc_Goto(proc, 5);
			}
			else
				Proc_Goto(proc, 4);
			
			break;
			
		// no trainee
		case PROMO_INIT_CONTEXT_TRAINEE:
		default:
			break;
	}
}