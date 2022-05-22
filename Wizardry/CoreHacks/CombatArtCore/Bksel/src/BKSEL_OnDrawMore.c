#include "gbafe-chax.h"

enum{
	
	// Real VRAM Offset to uncompress: OBJ_VRAM0 + OBJ_MOKHA_VRAMOFF
	OBJ_ARROW_VRAMOFF = 0x5320, 
	
	// Real Palette index: OBJ_ARROW_PAL + 0x10
	OBJ_ARROW_PAL = 0x3,
	
	
	// Obj config
	OBJ_ARROW_L_XPOS = -1,
	OBJ_ARROW_R_XPOS = 0x4B,
	OBJ_ARROW_YPOS = 0x16A,
};


static void BkselObj_UpdateArrow(struct Proc_BKSEL *proc){
	
	
	if ( (GetGameClock() & 0b111) == 0)
		proc->obj_arrow_timer = _lib_mod( proc->obj_arrow_timer + 1, 6);
	
	int vram_off = (OBJ_ARROW_VRAMOFF / 0x20) + 1 + proc->obj_arrow_timer;
	
	int xOff = (-1 == proc->pos) ? 0 : 0x9F;
	int yOff = (1 == proc->mode) ? 0 : 0x20;
	
	// Ensure we are using attack target-select
	extern const struct ProcCmd ProcCmd_CombatTargetSelection[];
	
	if( 0 == Proc_Find(ProcCmd_CombatTargetSelection) )
		return;
	
	PutSprite(
		0,
		OBJ_ARROW_L_XPOS + xOff,
		OBJ_ARROW_YPOS + yOff,
		gObject_8x16, 
		OAM2_PAL(OBJ_ARROW_PAL) + OAM2_LAYER(0b00) + OAM2_CHR(vram_off)
	);

	PutSprite(
		0,
		OBJ_ARROW_R_XPOS + xOff,
		OBJ_ARROW_YPOS + yOff,
		gObject_8x16_HFlipped, 
		OAM2_PAL(OBJ_ARROW_PAL) + OAM2_LAYER(0b00) + OAM2_CHR(vram_off)
	);
	
	
	// Check for AOE combat
	if( gpBattleFlagExt->isCombat )
	{
		const struct CombatArtInfo* info = 
			GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
			
		if( !info->AOE_Debuff )
			return;
		
		// Display object offsets
		const u8 Y_OFFs[6] = {0, 1, 2, 3, 2, 1};
		
		// 5 display at
		const s8 X_Real_disp[5] = {-0x10, 0, 0, 0, 0x10};
		const s8 Y_Real_disp[5] = {0, 0x10, 0, -0x10, 0};
		
		const int xTar = gBattleTarget.unit.xPos * 16 - gGameState.camera.x;
		const int yTar = gBattleTarget.unit.yPos * 16 - gGameState.camera.y;
		
		for( int i = 0; i < 5; i++ )
		{
			int xReal = xTar + X_Real_disp[i];
			int yReal = yTar + Y_Real_disp[i];
			
			if( xReal > 0xF0 )
				continue;
		
			if( yReal > 0xA0 )
				continue;
			
			xReal = (xReal + 0x204) & 0x1FF;
			yReal = (yReal + 0x103 + Y_OFFs[proc->obj_arrow_timer]) & 0xFF;
			
			PutSprite(
				0,
				xReal,
				yReal,
				gObject_8x8, 
				OAM2_PAL(OBJ_ARROW_PAL) + OAM2_LAYER(0b00) + OAM2_CHR(OBJ_ARROW_VRAMOFF / 0x20)
			);
		}

		
		
	}
}



void Bksel_InitMore(struct Proc_BKSEL *proc){
	
	extern u16 gGfx_BkselObjArrow[], gPal_BkselObjArrow[];
	extern void StartParallelWorker(void* func, ProcPtr);
	extern void BKSEL_InitGfx(ProcPtr);
	
	int count = 0;
	u8 *unit_combatarts = GetCombatArtList(gActiveUnit);
	u16 weapon = gBattleActor.weaponBefore;
	
	// Vanilla
	BKSEL_InitGfx(proc);
	
	for( int i = 0; i < 5; i++ )
		if( CanUnitWithWeaponUseCombatArt(gActiveUnit, weapon, unit_combatarts[i]) )
			count++;
	
	if( 0 == count )
		return;
	
	
	// Gfx
	CopyDataWithPossibleUncomp(gGfx_BkselObjArrow, gGenericBuffer);
	CopyTileGfxForObj(gGenericBuffer, OBJ_VRAM0 + OBJ_ARROW_VRAMOFF, 7, 2);
	
	
	// Pal
	ApplyPalettes(gPal_BkselObjArrow, OBJ_ARROW_PAL + 0x10, 1);
	
	// Init obj timer
	proc->obj_arrow_timer = 0;
	
	// Parallel worker
	StartParallelWorker(BkselObj_UpdateArrow, proc);
}






void cBksel_DrawMore(struct Proc_BKSEL *proc){
	
	u8 *unit_combatarts = GetCombatArtList(gActiveUnit);
	u16 weapon = gBattleActor.weaponBefore;
	int count = 0;
	
	if( 1 == proc->mode )
		proc->caIcon_yPos = 0x0D;		// Standard
	else
		proc->caIcon_yPos = 0x11;		// Detailed
	
	for( int i = 0; i < 5; i++ )
		if( CanUnitWithWeaponUseCombatArt(gActiveUnit, weapon, unit_combatarts[i]) )
			count++;
	
	Text_Clear(&proc->texts[2]);
	
	if( 0 == count )
		DrawTextInline(
			&proc->texts[2],
			TILEMAP_LOCATED( gBmFrameTmap0, 0x1, proc->caIcon_yPos),
			TEXT_COLOR_GRAY,
			GetStringTextCenteredPos( 0x40, GetStringFromIndex(ENUM_msg_Bksel_NoCAWarning) ),
			0,
			GetStringFromIndex(ENUM_msg_Bksel_NoCAWarning) 
		);
		
	
	else if( !gpBattleFlagExt->isCombat )
		DrawTextInline(
			&proc->texts[2],
			TILEMAP_LOCATED( gBmFrameTmap0, 0x1, proc->caIcon_yPos),
			TEXT_COLOR_NORMAL,
			GetStringTextCenteredPos( 0x40, GetStringFromIndex(ENUM_msg_Bksel_NotUseCA) ),
			0,
			GetStringFromIndex(ENUM_msg_Bksel_NotUseCA) );
	else
	{
		const struct CombatArtInfo* info = GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
		DrawTextInline(
			&proc->texts[2],
			TILEMAP_LOCATED( gBmFrameTmap0, 0x1, proc->caIcon_yPos),
			TEXT_COLOR_GREEN,
			GetStringTextCenteredPos( 0x40, GetStringFromIndex(info->msg_name) ),
			0,
			GetStringFromIndex(info->msg_name) );
	}
	// <!> look at gProcScr_SSPageNumCtrl->PageNumCtrl_UpdateArrows
}