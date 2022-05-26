#include "gbafe-chax.h"




void PostAction_Template(ProcPtr proc){
	
	// System Anim:
	// Status Cre
	extern void StartStatusClearFx(struct Unit*, ProcPtr);
	MU_EndAll();
	HideUnitSMS(gActiveUnit);
	StartStatusClearFx(gActiveUnit, proc);
	
	
	// Mokha Anim:
	// Gravity debuff
	SMS_UpdateFromGameData();
	StartMapAnim_Gravity(gActiveUnit, proc);

}

// ==============================================
//               Self Hurt
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
		case 0x3:	// staff
			
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
		case 0x3:	// staff
			
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
