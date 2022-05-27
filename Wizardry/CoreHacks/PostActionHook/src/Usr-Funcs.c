#include "gbafe-chax.h"

// ====================================================
//               Vanilla Exec Traps
// ====================================================

void PostAction_VanillaExecTrap(ProcPtr proc){
	
	extern int GetPickTrapType(struct Unit*);
	extern void ExecTrap(ProcPtr, struct Unit*, int);
	
	if( 0 == GetUnitCurrentHp(gActiveUnit) )
		return;
	
	if( (*SkillTester)(gActiveUnit, SID_Canto) )
		if( !(US_CANTOING & gActiveUnit->state) )
			if( 0x01 != gActionData.unitActionType ) // wait
				return;
	
	// Exec Trap
	if( 0 == GetPickTrapType(gActiveUnit) )
		return;
	
	gActionData.suspendPointType = 1;
	gActionData.unitActionType = 1; // wait
	
	SaveSuspendedGame(3);
	
	if( 1 == GetBattleAnimType() )
		SMS_UpdateFromGameData();
	
	ExecTrap(proc, gActiveUnit, 0);
}



// ==============================================
//                  Self Hurt
// ==============================================

extern const struct ProcCmd gProc_89A3288[];
extern void ExecSelfDamage(struct Unit*, int dmg);

struct ProcPostActionSelfHurt{
	PROC_HEADER;
	struct Unit* unit;
	int dmg;
};

static int DummyWaitSelfHurt();
static void SetSelfHurtResult(struct ProcPostActionSelfHurt*);

static const struct ProcCmd ProcCmd_WaitSelfHurt[] = {
	PROC_SLEEP(4),
	PROC_WHILE( DummyWaitSelfHurt ),
	PROC_SLEEP(4),
	PROC_CALL( SetSelfHurtResult ),
	PROC_END,
};

int DummyWaitSelfHurt(){
	extern int GetThread2SkipStack();
	return GetThread2SkipStack();
}

void SetSelfHurtResult(struct ProcPostActionSelfHurt* proc){
	AddUnitHp(proc->unit, -proc->dmg);
}


void PostAction_DmgAct(ProcPtr proc){
	
	struct Unit* unit = gActiveUnit;
	int dmg = 0;
	
	switch(gActionData.unitActionType){
		case 0x2:	// combat
			
			// Fury
			
			if( (*SkillTester)(unit, SID_Fury) )
				dmg += 6;
			
			if( (*SkillTester)(unit, SID_FuryPlus) )
				dmg += 8;
			
			// DoubleLion
			if( (*SkillTester)(unit, SID_DoubleLion) )
				if( gpBattleFlagExt->doubleLion_activited )
					dmg += 1;
			break;
		
		default:
			return;
	}

	if( dmg <= 0 )
		return;
	
	dmg = dmg >= GetUnitCurrentHp(unit)
		? GetUnitCurrentHp(unit) - 1
		: dmg;
	
	MU_EndAll();
	SMS_UpdateFromGameData();
	HideUnitSMS(unit);
	ExecSelfDamage(unit, dmg);
	
	struct ProcPostActionSelfHurt *child = 
		Proc_StartBlocking(ProcCmd_WaitSelfHurt, proc);
	
	child->unit = unit;
	child->dmg = dmg;
}


void PostAction_DmgTar(ProcPtr proc){
	
	struct Unit* unit = GetUnit(gActionData.targetIndex);
	int dmg = 0;
	
	// Fury
	switch(gActionData.unitActionType){
		case 0x2:	// combat
			
			if( (*SkillTester)(unit, SID_Fury) )
				dmg += 6;
			
			if( (*SkillTester)(unit, SID_FuryPlus) )
				dmg += 8;
			break;
		
		default:
			return;
	}
	
	if( dmg <= 0 )
		return;
	
	dmg = dmg >= GetUnitCurrentHp(unit)
		? GetUnitCurrentHp(unit) - 1
		: dmg;
	
	MU_EndAll();
	SMS_UpdateFromGameData();
	HideUnitSMS(unit);
	ExecSelfDamage(unit, dmg);
	
	struct ProcPostActionSelfHurt *child = 
		Proc_StartBlocking(ProcCmd_WaitSelfHurt, proc);
	
	child->unit = unit;
	child->dmg = dmg;
}