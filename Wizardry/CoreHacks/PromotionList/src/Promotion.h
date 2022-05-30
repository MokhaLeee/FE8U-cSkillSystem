#pragma once

#include "gbafe.h"
enum{
	
	// Proc_PromoInit->promContextId
	PROMO_INIT_CONTEXT_TRAINEE = 0,
	PROMO_INIT_CONTEXT_PREP = 1,
	PROMO_INIT_CONTEXT_BMMAP = 2,
};

struct Proc_PromoInit {
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 pad_29[0x2C - 0x29];
	/* 2C */ void* ccramifyParent;
	/* 30 */ u8 StateIndex;
	/* 31 */ u8 promContextId;
	/* 32 */ u8 unk_32;
	/* 33 */ u8 charId;
	/* 34 */ u8 unk34;		// a config(0 will directly promote, 1 will start menu)
	/* 35 */ u8 unk35;		// class index to promote
	/* 36 */ u8 unk_36[0x38 - 0x36];
	/* 38 */ struct Unit* unit;
	/* 3C */ u32 promotionItemSlot;
	
	// new here
	/* 40 */ u8 pad_40[0x64 - 0x40];
	/* 64 */ u16 item;
	/* 66 */ u8 count;
	/* 67 */ u8 classOld;
};

extern const struct ProcCmd gProc_PromotionInit[];

struct Proc_PromoMain {
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 unk_29;
	/* 2A */ u8 pad_2A[0x34 - 0x2A];
	/* 34 */ ProcPtr pPromotionSub6C;
	/* 38 */ u8 charId;
	/* 39 */ u8 modeId;
	/* 3A */ u8 unk3A;
	/* 3B */ u8 promoClass;				// class index that will promote to
	
};


struct Proc_PromoDisp {
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 pad_29[0x2C - 0x29];
	/* 2C */ u16 promotedClassIds[3];
	/* 32 */ u16 promotedClassAnimIds[3];
	/* 38 */ u16 promotedClassDescIds[3];
	/* 3E */ u8 pad_3E[0x40 - 0x3E];
	
	// a timer when change class: 0->1->2, 1=remove, 2=intro
	/* 40 */ u8 state;							
	
	// Current index in proc class list(0,1,2)
	/* 41 */ u8 selectedOptionIndex;			
	/* 42 */ u16 charId;
	/* 44 */ u8 pad_44[0x48 - 0x44];
	/* 48 */ u16 displayedWeapon;
	/* 4A */ u16 promotedClassHasAnim[3];
	/* 4D */ u8 pad_4C[0x50 - 0x4D];
	/* 50 */ u32 unk_50;
	/* 54 */ struct MenuProc* pMenuSelectProc;
};


struct Proc_PromoMenuSelect{
	/* 00 */ PROC_HEADER;
	/* 29 */
};


// const struct ProcCmd NewProc_PromotionDisplay[] = {};


struct UnitPromoTable{
	u8 promoClass[2];
};

extern const struct UnitPromoTable gPromotionTable[];