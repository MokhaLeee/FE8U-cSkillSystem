#include "gbafe.h"

extern void sub_806E444(ProcPtr); 		// Ekr Skill Proc Main Loop
static void EkrSkill_OnInit(ProcPtr);
static void EkrSkill_OnEnd(ProcPtr);
static void EkrSkillSub_Dummy(ProcPtr);


struct ProcEkrSkillSub{
	PROC_HEADER;
	u8 priority_bg1;
	u8 priority_bg2;
	u8 blendCoeffA;
	u8 blendCoeffB;
};

const struct ProcCmd gProcCmd_NewEkrSkill[] = {
	
	PROC_CALL( EkrSkill_OnInit ),
	PROC_REPEAT( sub_806E444 ),
	PROC_CALL( EkrSkill_OnEnd ),
	PROC_END,
};

static const struct ProcCmd gProcCmd_SubDummy[] = {
	
	PROC_REPEAT( EkrSkillSub_Dummy ),
	PROC_END,
};





void EkrSkillSub_Dummy(ProcPtr){ return; }


void EkrSkill_OnInit(ProcPtr proc){
	
	struct ProcEkrSkillSub* child = Proc_Start(gProcCmd_SubDummy, proc);
	
	child->priority_bg1 = gLCDControlBuffer.bg1cnt.priority;
	child->priority_bg2 = gLCDControlBuffer.bg2cnt.priority;
	child->blendCoeffA = gLCDControlBuffer.blendCoeffA;
	child->blendCoeffB = gLCDControlBuffer.blendCoeffB;
	
	
}



void EkrSkill_OnEnd(ProcPtr proc){
	
	struct ProcEkrSkillSub* child = Proc_Find(gProcCmd_SubDummy);
	
	gLCDControlBuffer.bg1cnt.priority = child->priority_bg1;
	gLCDControlBuffer.bg2cnt.priority = child->priority_bg2;
	gLCDControlBuffer.blendCoeffA = child->blendCoeffA;
	gLCDControlBuffer.blendCoeffB = child->blendCoeffB;
	
	Proc_End(child);
}











// With ASM
void EkrSkill_BgConfigHack(){
	
	extern void SpellFx_SetSomeColorEffect();
	
	SpellFx_SetSomeColorEffect();
	
	gLCDControlBuffer.bg1cnt.priority = 0b10;
	gLCDControlBuffer.blendCoeffA = 0x10;
	gLCDControlBuffer.blendCoeffB = 0x00;
	
}