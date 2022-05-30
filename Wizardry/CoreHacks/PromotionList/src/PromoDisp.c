#include "gbafe-chax.h"
#include "Promotion.h"



// Vanilla rework
void PromotionDisplay_Init(struct Proc_PromoDisp* proc){
	
	struct Proc_PromoMain* parent = proc->proc_parent;
	struct Proc_PromoInit* proc_init = Proc_Find(gProc_PromotionInit);
	
	parent->unk_29 = 2;
	proc->charId = parent->charId;
	proc->unk_50 = 9;
	const u8 *class_list = GetUnitPromoList(proc->charId, proc_init->classOld, proc_init->item);
	
	BG_Fill(gBG0TilemapBuffer, 0);
	BG_Fill(gBG1TilemapBuffer, 0);
	BG_Fill(gBG2TilemapBuffer, 0);
	
	LoadUiFrameGraphics();
	LoadObjUIGfx();
	
	// Maybe relate to Ekr Anim
	extern void sub_80CD47C(int, int, int, int, int);
	sub_80CD47C(0, -1, 0x1F6, 0x58, 0x6);
	
	// Maybe uncompress some gfx
	extern void sub_80CCBF4();
	extern void sub_80CD408(int, int, int);
	sub_80CCBF4();
	sub_80CD408(proc->unk_50, 0x118, 0x68);
	
	
	proc->promotedClassAnimIds[0] = 0;
	proc->promotedClassAnimIds[1] = 0;
	proc->promotedClassAnimIds[2] = 0;
	
	// In vanilla, these two value is not init
	// I think it is a bug!
	u8 class_id = 0;
	u16 weapon = 0;
	
	for( int i = 1; i < FACTION_GREEN; i++ ){
		
		struct Unit* unit = GetUnit(i);
		
		if( UNIT_IS_VALID(unit) && (unit->pCharacterData->number == proc->charId) ){
			
			class_id = unit->pClassData->number;
			weapon = GetUnitEquippedWeapon(unit);
			// class_id = 0x13;

			for(int i = 0; i <= 1; i++){
				proc->promotedClassIds[i] = class_list[i];
				
				extern u8 GetClassAnimationIdForWeapon(u16* AnimIdAt, u8 classId, u16 weapon);
				proc->promotedClassHasAnim[i] = 
					GetClassAnimationIdForWeapon(&proc->promotedClassAnimIds[i], class_id, weapon);
				
				proc->promotedClassDescIds[i] = 
					GetClassData(class_list[i])->descTextId;
				
			}
			
			proc->displayedWeapon = weapon;
			
			// Check some Trainee
			
			break;
		}
	}

	
	proc->state = 1;
	proc->selectedOptionIndex = 0;
	
	// This should be class UI name
	extern void PromotionDisplay_InitClassName(struct Proc_PromoDisp*, u8 classId);
	extern void PromotionDisplay_DrawClassName(struct Proc_PromoDisp*);
	extern struct MenuProc* Make6C_PromotionMenuSelect(struct Proc_PromoDisp*);
	
	PromotionDisplay_InitClassName(proc, class_id);
	PromotionDisplay_DrawClassName(proc);
	LoadObjUIGfx();
	proc->pMenuSelectProc = Make6C_PromotionMenuSelect(proc);
	
	struct Proc_PromoInit* GrandFather = parent->proc_parent;
	
	if( 1 == GrandFather->promContextId ){
		
		extern void RestartScreenMenuScrollingBg();
		RestartScreenMenuScrollingBg();
		BG_EnableSyncByMask(0b1111);
	}
}






u16 PromoDispMainLoopHackCore(struct Proc_PromoDisp* proc){
	
	// Hack from 80CD0A8, return at 0x80CD105
	// return value: GetBattleAnimationId
	
	u32 wType;
	u16 charId = proc->charId;
	struct Proc_PromoInit* proc_init = Proc_Find(gProc_PromotionInit);
	const u8 *class_list = GetUnitPromoList(proc->charId, proc_init->classOld, proc_init->item);
	u16 classId = class_list[proc->selectedOptionIndex];
	struct Unit *unit = GetUnitFromCharId(charId);
	const struct ClassData *class_promo = GetClassData(classId);
	const u8 *AnimDef = class_promo->pBattleAnimDef;
	
	// GetBattleAnimationId
	extern u16 GetBattleAnimationId(struct Unit*, const void* pBattleAnimDef, u16 weapon, u32 *R3);
	
	u16 anime_id = GetBattleAnimationId(
		unit, 
		AnimDef, 
		GetUnitEquippedWeapon(unit), 
		&wType);
	
	if( 0xFFFF == anime_id )
		if( 0 != AnimDef[2] )
		{
			anime_id = AnimDef[2];
			wType = AnimDef[3];
		}
	
	// Find a Displayed weapon
	for( int i = 1; i < 0xFF; i++ )
		if( GetItemType(i) == wType )
		{
			proc->displayedWeapon = i;
			break;
		}
	
	// to transmit values to asm
	gGenericBuffer[0] = charId - 1;
	gGenericBuffer[1] = classId;
	
	return anime_id;
	
}





