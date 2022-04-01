#include "gbafe-chax.h"
#include "PrepSkill.h"


// ========================================
// ======= Static Func Definitions ========
// ========================================

struct Proc_PrepSkillObj{
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 time;
	
};


static void PrepSkillObj_OnDraw(struct Proc_PrepSkillObj* proc);
static void PrepSkillObj_OnUpdate(struct Proc_PrepSkillObj* proc);


// ========================================
// ================ Main ==================
// ========================================




enum{
	SKILLOBJ_VRAMOFF = 0x2000,
	SKILLOBJ_PALID = 0x3,
};

const static struct ProcCmd gProc_PrepSkillPutObj[] = {
	
	PROC_NAME	("PREPSKILL_OBJ"),
	
	PROC_CALL	(PrepSkillObj_OnDraw),
	PROC_REPEAT	(PrepSkillObj_OnUpdate),
	
	PROC_END,
	
};



void PrepSkillObj_OnDraw(struct Proc_PrepSkillObj* proc){
	
	extern u16 Gfx_PrepPickSkillObjs[];
	extern u16 Pal_PrepPickSkillObjs[];
	
	// Gfx
	CopyDataWithPossibleUncomp( Gfx_PrepPickSkillObjs, OBJ_VRAM0 + SKILLOBJ_VRAMOFF ); 
	
	// Palette
	// (aSrc, aPalId, aPalCount)
	ApplyPalettes(Pal_PrepPickSkillObjs, SKILLOBJ_PALID + 0x10, 1);
	
	// timer
	proc->time = 0;
	
}



void PrepSkillObj_OnUpdate(struct Proc_PrepSkillObj* proc){
	
	proc->time++;
	
	if( (proc->time & 0x3F) < 0x20 )
		return;
	
	PutSprite(4, 0x10 * 0x8, 0x5 * 8, gObject_8x16, OAM2_PAL(SKILLOBJ_PALID) + SKILLOBJ_VRAMOFF / 0x20);
	PutSprite(4, 0x12 * 0x8, 0x5 * 8, gObject_8x16, OAM2_PAL(SKILLOBJ_PALID) + SKILLOBJ_VRAMOFF / 0x20 + 1);
	
	
}




// =======================================================
// ====================== GLOBAL =========================
// =======================================================
void StartProc_PrepSkillObj(ProcPtr parent){
	
	if( NULL == Proc_Find(gProc_PrepSkillPutObj) )
		Proc_Start(gProc_PrepSkillPutObj, parent);
	
}

void EndProc_PrepSkillObj(ProcPtr parent){
	
	Proc_EndEach(gProc_PrepSkillPutObj);
	
}
