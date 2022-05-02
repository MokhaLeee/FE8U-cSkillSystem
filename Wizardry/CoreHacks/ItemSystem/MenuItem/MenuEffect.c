#include "gbafe-chax.h"

extern void NewBottomHelpText(ProcPtr parent, const char* string);
extern ProcPtr NewTargetSelection(const struct SelectInfo* selectInfo);
extern struct ProcCmd CONST_DATA gProcScr_SquareSelectWarp[];
extern struct ProcCmd CONST_DATA gProcScr_SquareSelectTorch[];

extern struct SelectInfo CONST_DATA gSelectInfo_OffensiveStaff;
extern struct SelectInfo CONST_DATA gSelectInfo_Barrier;
extern struct SelectInfo CONST_DATA gSelectInfo_Restore;
extern struct SelectInfo CONST_DATA gSelectInfo_Heal;
extern struct SelectInfo CONST_DATA gSelectInfo_PutTrap;
extern struct SelectInfo CONST_DATA gSelectInfo_0859D2F8;
extern struct SelectInfo CONST_DATA gSelectInfo_Repair;

extern void MakeTargetListForAdjacentHeal(struct Unit*);
extern void MakeTargetListForRangedHeal(struct Unit*);
extern void MakeTargetListForRestore(struct Unit*);
extern void MakeTargetListForRescueStaff(struct Unit*);
extern void MakeTargetListForBarrier(struct Unit*);
extern void MakeTargetListForSilence(struct Unit*);
extern void MakeTargetListForSleep(struct Unit*);
extern void MakeTargetListForBerserk(struct Unit*);
extern void MakeTargetListForWarp(struct Unit*);
extern void MakeTargetListForHammerne(struct Unit*);
extern void MakeTargetListForUnlock(struct Unit*);
extern void MakeTargetListForLatona(struct Unit*);
extern void MakeTargetListForMine(struct Unit*);
extern void MakeTargetListForLightRune(struct Unit*);
extern void MakeTargetListForDanceRing(struct Unit*);
extern void MakeTargetListForDoorAndBridges(struct Unit*, int terrain);

static void SetItemUseAction(struct Unit* unit);
static void SetStaffUseAction(struct Unit* unit);

static void DoEff_Heal(struct Unit*, uint16_t item);
static void DoEff_Physic(struct Unit*, uint16_t item);
static void DoEff_Restore(struct Unit*, uint16_t item);
static void DoEff_Rescue(struct Unit*, uint16_t item);
static void DoEff_Barrier(struct Unit*, uint16_t item);
static void DoEff_Silence(struct Unit*, uint16_t item);
static void DoEff_Sleep(struct Unit*, uint16_t item);
static void DoEff_Berserk(struct Unit*, uint16_t item);
static void DoEff_Warp(struct Unit*, uint16_t item);
static void DoEff_Repair(struct Unit*, uint16_t item);
static void DoEff_Unlock(struct Unit*, uint16_t item);
static void DoEff_Mine(struct Unit*, uint16_t item);
static void DoEff_LightRune(struct Unit*, uint16_t item);
static void DoEff_StaffTorch(struct Unit*, uint16_t item);
static void DoEff_DanceRing(struct Unit*, uint16_t item);


typedef void (*EffFunc_t)(struct Unit*, uint16_t item);

const EffFunc_t ItemMenuEffectTable[0xFF] = {
	
	[ITEM_STAFF_HEAL] = DoEff_Heal,
	[ITEM_STAFF_MEND] = DoEff_Heal,
	[ITEM_STAFF_RECOVER] = DoEff_Heal,
	[ITEM_STAFF_PHYSIC] = DoEff_Physic,
	[ITEM_STAFF_FORTIFY] = (EffFunc_t) SetStaffUseAction,
	[ITEM_STAFF_RESTORE] = DoEff_Restore,
	[ITEM_STAFF_RESCUE] = DoEff_Rescue,
	[ITEM_STAFF_BARRIER] = DoEff_Barrier,
	[ITEM_STAFF_SILENCE] = DoEff_Silence,
	[ITEM_STAFF_SLEEP] = DoEff_Sleep,
	[ITEM_STAFF_BERSERK] = DoEff_Berserk,
	[ITEM_STAFF_WARP] = DoEff_Warp,
	[ITEM_STAFF_REPAIR] = DoEff_Repair,
	[ITEM_STAFF_UNLOCK] = DoEff_Unlock,
	
	[ITEM_STAFF_LATONA] =(EffFunc_t) SetStaffUseAction,
	[ITEM_MINE] = DoEff_Mine,
	[ITEM_LIGHTRUNE] = DoEff_LightRune,
	[ITEM_STAFF_TORCH] = DoEff_StaffTorch,
	
	[ITEM_FILLAS_MIGHT] = DoEff_DanceRing,
	[ITEM_NINISS_GRACE] = DoEff_DanceRing,
	[ITEM_THORS_IRE] = DoEff_DanceRing,
	[ITEM_SETS_LITANY] = DoEff_DanceRing,
	
};

// core
void DoItemUse(struct Unit* unit, int item) {
	
	EffFunc_t it;
	
	ClearBg0Bg1();
	DeleteFaceByIndex(0);
	
	it = ItemMenuEffectTable[ITEM_ID(item)];
	
	if ( _IsPointer((u32)it) )	// if simple item, here, it = msg_id
		it(unit, item);
	else
		SetItemUseAction(unit);
	

}



// misc func
static void SetItemUseAction(struct Unit* unit){
	gActionData.unitActionType = UNIT_ACTION_USE_ITEM;
}

static void SetStaffUseAction(struct Unit* unit)
{
	HideMoveRangeGraphics();

	BG_Fill(gBG2TilemapBuffer, 0);
	BG_EnableSyncByMask(BG2_SYNC_BIT);

	gActionData.unitActionType = UNIT_ACTION_STAFF;
}

static int StaffSelectOnSelect(ProcPtr proc, struct SelectTarget* target)
{
	gActionData.targetIndex = target->uid;
	SetStaffUseAction(NULL);

	return 0x17; // TODO: Select Return Constants
}

static int WarpOnSelectTarget(ProcPtr proc, struct SelectTarget* target)
{
	EndTargetSelection(proc);

	gActionData.targetIndex = target->uid;

	Proc_Start(gProcScr_SquareSelectWarp, PROC_TREE_3);

	return 4; // TODO: Map Select Return Constants
}

static int OnSelectPutTrap(ProcPtr proc, struct SelectTarget* target)
{
	gActionData.xOther = target->x;
	gActionData.yOther = target->y;

	SetStaffUseAction(NULL);

	return 0x17; // TODO: Map Select Return Constants
}



// Effect routine

static void DoEff_Heal(struct Unit* unit, uint16_t item) {
	MakeTargetListForAdjacentHeal(unit);
	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection(&gSelectInfo_Heal),
		GetStringFromIndex(0x874)
	); // TODO: msgid "Select a character to restore HP to."
}

static void DoEff_Physic(struct Unit* unit, uint16_t item) {
	MakeTargetListForRangedHeal(unit);
	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection(&gSelectInfo_Heal),
		GetStringFromIndex(0x874)
	); // TODO: msgid "Select a character to restore HP to."
}

static void DoEff_Restore(struct Unit* unit, uint16_t item) {
	MakeTargetListForRestore(unit);
	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection(&gSelectInfo_Restore),
		GetStringFromIndex(0x877)
	); // TODO: msgid "Select a character to restore to normal."
}

static void DoEff_Rescue(struct Unit* unit, uint16_t item){
	MakeTargetListForRescueStaff(unit);
	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection_Specialized(&gSelectInfo_0859D2F8, (void*)StaffSelectOnSelect),
		GetStringFromIndex(0x876)); // TODO: msgid "Select which character to bring next to you."
}

static void DoEff_Barrier(struct Unit* unit, uint16_t item){
	MakeTargetListForBarrier(unit);

	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection(&gSelectInfo_Barrier),
		GetStringFromIndex(0x879)
	); // TODO: msgid "Select a character to restore to normal."
}

static void DoEff_Silence(struct Unit* unit, uint16_t item){
	MakeTargetListForSilence(unit);
	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection(&gSelectInfo_OffensiveStaff),
		GetStringFromIndex(0x87B)
	); // TODO: msgid "Select a unit to use the staff on."
}

static void DoEff_Sleep(struct Unit* unit, uint16_t item){
	MakeTargetListForSleep(unit);
	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection(&gSelectInfo_OffensiveStaff),
		GetStringFromIndex(0x87B)
	); // TODO: msgid "Select a unit to use the staff on."
}

static void DoEff_Berserk(struct Unit* unit, uint16_t item){
	MakeTargetListForBerserk(unit);
	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection(&gSelectInfo_OffensiveStaff),
		GetStringFromIndex(0x87B)
	); // TODO: msgid "Select a unit to use the staff on."
}

static void DoEff_Warp(struct Unit* unit, uint16_t item){
	MakeTargetListForWarp(unit);

	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection_Specialized(&gSelectInfo_0859D2F8, (void*)WarpOnSelectTarget),
		GetStringFromIndex(0x875)
	); // TODO: msgid "Select character to warp."

	PlaySoundEffect(0x6A); // TODO: song ids
}

static void DoEff_Repair(struct Unit* unit, uint16_t item){
	MakeTargetListForHammerne(unit);

	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection(&gSelectInfo_Repair),
		GetStringFromIndex(0x878)
	); // TODO: msgid "Select the character whose weapon needs repair."

	PlaySoundEffect(0x6A); // TODO: song ids
}

static void DoEff_Unlock(struct Unit* unit, uint16_t item){
	MakeTargetListForUnlock(unit);

	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection_Specialized(&gSelectInfo_PutTrap, (void*)OnSelectPutTrap),
		GetStringFromIndex(0x87A)
	); // TODO: msgid "Select a door to open."

	PlaySoundEffect(0x6A); // TODO: song ids
}

static void DoEff_Mine(struct Unit* unit, uint16_t item){
	MakeTargetListForMine(unit);

	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection_Specialized(&gSelectInfo_PutTrap, (void*)OnSelectPutTrap),
		GetStringFromIndex(0x87D)
	); // TODO: msgid "Select an area to trap."

	PlaySoundEffect(0x6A); // TODO: song ids
}

static void DoEff_LightRune(struct Unit* unit, uint16_t item){
	MakeTargetListForLightRune(unit);

	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection_Specialized(&gSelectInfo_PutTrap, (void*)OnSelectPutTrap),
		GetStringFromIndex(0x87E)
	); // TODO: msgid "Select an area to trap."

	PlaySoundEffect(0x6A); // TODO: song ids
}

static void DoEff_StaffTorch(struct Unit* unit, uint16_t item){
	Proc_Start(gProcScr_SquareSelectTorch, PROC_TREE_3);
	PlaySoundEffect(0x6A); // TODO: song ids
}

static void DoEff_DanceRing(struct Unit* unit, uint16_t item){
	MakeTargetListForDanceRing(unit);

	BmMapFill(gBmMapMovement, -1);

	NewBottomHelpText(
		NewTargetSelection_Specialized(&gSelectInfo_0859D2F8, (void*)StaffSelectOnSelect),
		GetStringFromIndex(0x87F)
	); // TODO: msgid "Select a character to bless."
}

