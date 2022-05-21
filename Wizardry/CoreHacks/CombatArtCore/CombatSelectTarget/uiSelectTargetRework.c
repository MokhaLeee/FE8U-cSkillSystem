#include "gbafe-chax.h"
#include <string.h>






static void CTS_HandleMoveInput(struct SelectTargetProc* proc){
	
	struct SelectTarget* current = proc->currentTarget;

	// Vanilla
	
	if ( (DPAD_UP & gKeyStatusPtr->repeatedKeys) && (current->next) )
		proc->currentTarget = current->next;
	
	else if ( (DPAD_DOWN & gKeyStatusPtr->repeatedKeys) && (proc->currentTarget->prev) ) 
		proc->currentTarget = current->prev;

	if (proc->currentTarget != current)
	{
		if( proc->selectRoutines->onSwitchOut )
			proc->selectRoutines->onSwitchOut(proc, current);
	
		if( proc->selectRoutines->onSwitchIn )
			proc->selectRoutines->onSwitchIn(proc, proc->currentTarget);
	
		PlaySoundEffect(0x67);
		
		return;
	}
	
	
	// Judge for combat art
	// static void (*BkSel_ExternUpdate)() = (const void*) 0x803738D;
	static void (*BattleTargetSelect_OnSwitchIn)(ProcPtr, struct SelectTarget*) = (const void*) 0x8022E8D;
	extern int* gpCommonSpace;
	extern struct Vec2 sSelectTargetRoot;
	extern struct SelectTarget sSelectTargetList[MAX_TARGET_LIST_COUNT];
	extern int sSelectTargetCount;
	
	int total = 0;
	int cur = 0;
	const s8 current_uid = current->uid;
	const int combatArt_old = gpBattleFlagExt->combatArt_id;
	const struct CombatArtInfo *old_info = GetCombatArtInfo(combatArt_old);
	const struct CombatArtInfo *new_info;
	u8 tmp_list[5] = {0};
	u8* ca_list = GetCombatArtList(gActiveUnit);
	u16 weapon = gBattleActor.weapon;
	
	// build tmp list and total
	for( int i = 0; i < 5; i++ )
		if( CanUnitWithWeaponUseCombatArt( gActiveUnit, weapon, ca_list[i]) )
			tmp_list[ total++ ] = ca_list[i];
	
	// get cur
	if( (0 == gpBattleFlagExt->isCombat) || !SKILL_VALID(gpBattleFlagExt->combatArt_id) || (gActiveUnit->index != gpBattleFlagExt->combat_unit) )
		cur = 0;
	else
	{
		for( int i = 0; i < total; i++)
			if( gpBattleFlagExt->combatArt_id == tmp_list[i] )
				cur = i + 1;
	}
	
	
	// Handle right/left key
	if( DPAD_RIGHT & gKeyStatusPtr->repeatedKeys )
		cur++;
	
	else if ( DPAD_LEFT & gKeyStatusPtr->repeatedKeys )
		cur--;
	
	else
		return;
	

	
	// if zero, consider button as normal change target
	if( 0 == total )
	{
		if ( (DPAD_LEFT & gKeyStatusPtr->repeatedKeys) && (current->next) )
			proc->currentTarget = current->next;
	
		else if ( (DPAD_RIGHT & gKeyStatusPtr->repeatedKeys) && (proc->currentTarget->prev) ) 
			proc->currentTarget = current->prev;
		
		if (proc->currentTarget != current)
		{
			if( proc->selectRoutines->onSwitchOut )
				proc->selectRoutines->onSwitchOut(proc, current);
		
			if( proc->selectRoutines->onSwitchIn )
				proc->selectRoutines->onSwitchIn(proc, proc->currentTarget);
		
			PlaySoundEffect(0x67);
		}
		
		return;
	}
		
	
	// if not zero, continue judge combat-art skill
	if( cur < 0 )
		cur = total;
	
	else if( cur > total )
		cur = 0;
	
	if( 0 == cur )
	{
		gpBattleFlagExt->isCombat = 0;
		gpBattleFlagExt->combatArt_id = 0;
		gpBattleFlagExt->combat_unit = 0;
	}
	else
	{
		gpBattleFlagExt->isCombat = 1;
		gpBattleFlagExt->combatArt_id = tmp_list[cur - 1];
		gpBattleFlagExt->combat_unit = gActiveUnit->index;
	}
	
	
	new_info = GetCombatArtInfo( gpBattleFlagExt->combatArt_id );
	
	
	// judge for range
	if( old_info->range_bouns == new_info->range_bouns )
		goto goto_sucess;
		
	

	// reserve
	memcpy(gGenericBuffer, sSelectTargetList, MAX_TARGET_LIST_COUNT * sizeof(struct SelectTarget));
	gpCommonSpace[0] = sSelectTargetRoot.x;
	gpCommonSpace[1] = sSelectTargetRoot.y;
	gpCommonSpace[2] = sSelectTargetCount;
		
	ClearBg0Bg1();
	MakeTargetListForWeapon(gActiveUnit, weapon);
	
	struct SelectTarget* tar = GetFirstTargetPointer();

	for( int i = 0; i < GetSelectTargetCount(); i++ )
	{
		tar = tar->next;
		
		if( current_uid == tar->uid )
			break;
	}
	
	if( current_uid == tar->uid )
	{
		proc->currentTarget = tar;
		goto goto_sucess;
	}
	else
	{
		memcpy(sSelectTargetList, gGenericBuffer, MAX_TARGET_LIST_COUNT * sizeof(struct SelectTarget));
		sSelectTargetRoot.x = gpCommonSpace[0];
		sSelectTargetRoot.y = gpCommonSpace[1];
		sSelectTargetCount = gpCommonSpace[2];
		goto goto_failure;
		
	}

goto_failure:
	PlaySoundEffect(0x6C);
	
	if( 0 == combatArt_old )
	{
		gpBattleFlagExt->isCombat = 0;
		gpBattleFlagExt->combatArt_id = 0;
		gpBattleFlagExt->combat_unit = 0;
	}
	
	else
	{
		gpBattleFlagExt->isCombat = 1;
		gpBattleFlagExt->combatArt_id = combatArt_old;
		gpBattleFlagExt->combat_unit = gActiveUnit->index;
	}
	
	BattleTargetSelect_OnSwitchIn(proc, proc->currentTarget );
	return;

goto_sucess:
	BattleTargetSelect_OnSwitchIn(proc, proc->currentTarget);
	PlaySoundEffect(0x67);
	
	// Fill map
	BmMapFill(gBmMapRange, NU_RANGE_MAP);
	GenerateUnitStandingReachRange(gActiveUnit, ItemRange2Mask(weapon, gActiveUnit));
	DisplayMoveRangeGraphics(RNG_RED);
	return;
}






static void CTS_MainLoop(struct SelectTargetProc* proc){
	
	int x, y;

	if ( 0x40 & proc->unk_34 ) {
		TargetSelection_GetRealCursorPosition(proc, &x, &y);
		DisplayCursor(x, y, 4);
		return;
	}
	
	
	// reworked here
	
	CTS_HandleMoveInput(proc);
	
	// actually this is judging for return routine
	
	const int ctrl_key = TargetSelection_HandleSelectInput(proc);
	
	if( TSE_END & ctrl_key )
		EndTargetSelection(proc);
	
	if( TSE_PLAY_BEEP & ctrl_key )
		PlaySoundEffect(0x6A);
	
	if( TSE_PLAY_BOOP & ctrl_key )
		PlaySoundEffect(0x6B);
	
	if( TSE_CLEAR_GFX & ctrl_key )
		ClearBg0Bg1();
	
	if( TSE_END_FACE0 & ctrl_key )
		DeleteFaceByIndex(0);
	
	if( !(TSE_DISABLE & ctrl_key) )
	{
		TargetSelection_GetRealCursorPosition(proc, &x, &y);
		
		if( !EnsureCameraOntoPosition( proc, x / 0x10, y / 0x10) )
			DisplayCursor(x, y, 2);
	}
	
}

















const struct ProcCmd ProcCmd_CombatTargetSelection[] = {
	
	PROC_NAME("NEW_PROC_COMBAT_TARGETSELECTION"),
	
PROC_LABEL(0),
	PROC_REPEAT(CTS_MainLoop),
	PROC_SLEEP(1),

	PROC_CALL(RefreshBMapGraphics),
	PROC_GOTO(0),

	PROC_END,
};


ProcPtr StartCombatTargetSelection(const struct SelectInfo* selectInfo){
	
	struct SelectTargetProc* proc;

	AddSkipThread2();
	proc = Proc_Start(ProcCmd_CombatTargetSelection, PROC_TREE_3);

	proc->unk_34 = 1;
	proc->selectRoutines = selectInfo;
	proc->currentTarget = GetFirstTargetPointer();
	proc->onAPress = 0;

	if (proc->selectRoutines->onInit) {
		proc->selectRoutines->onInit(proc);
	}

	if (proc->selectRoutines->onUnk08) {
		proc->selectRoutines->onUnk08(proc);
	}

	if (proc->selectRoutines->onSwitchIn) {
		proc->selectRoutines->onSwitchIn(proc, proc->currentTarget);
	}

	gKeyStatusPtr->newKeys = 0;

	return proc;
	
}




// =====================================================
//        Hack on Vanilla attack target-select
// =====================================================

// sub-attack effect
u8 UnknownMenu_Selected(struct MenuProc* menu, struct MenuItemProc* menu_item){
	
	extern const struct SelectInfo gUnknown_0859D3F8;
	
	u16 weapon = gActiveUnit->items[menu_item->itemNumber];
	
	EquipUnitItemSlot(gActiveUnit, menu_item->itemNumber);
	ClearBg0Bg1();
	MakeTargetListForWeapon(gActiveUnit, weapon);
	
	// reworked a new CTS
	StartCombatTargetSelection(&gUnknown_0859D3F8);
	
	return MENU_ACT_ENDFACE | MENU_ACT_CLEAR | MENU_ACT_SND6A | MENU_ACT_END | MENU_ACT_SKIPCURSOR;
}
