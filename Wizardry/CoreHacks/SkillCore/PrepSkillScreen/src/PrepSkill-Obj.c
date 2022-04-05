#include "gbafe-chax.h"
#include "PrepSkill.h"



static void PrepSkillObj_OnInit(ProcPtr proc);
static void PrepSkillObj_OnUpdate(ProcPtr proc);


// ========================================
// ================ Main ==================
// ========================================



const static struct ProcCmd gProc_PrepSkillPutObj[] = {
	
	PROC_NAME	("PREPSKILL_OBJ"),
	
	PROC_CALL	(PrepSkillObj_OnInit),
	PROC_REPEAT	(PrepSkillObj_OnUpdate),
	
	PROC_END,
	
};




void PrepSkillObj_OnInit(ProcPtr proc){
	
	
	// Skill tips
	extern u16 Gfx_ObjSkill[];
	extern u16 Pal_ObjSkill[];
	
	CopyDataWithPossibleUncomp( Gfx_ObjSkill, OBJ_VRAM0 + SKILLOBJ_VOBJ ); 
	ApplyPalettes(Pal_ObjSkill, SKILLOBJ_PAL + 0x10, 1);
	
	
	// Window Obj
	extern u16 Gfx_ObjWindow[];
	extern u16 Pal_ObjWindow[];
	
	CopyDataWithPossibleUncomp(Gfx_ObjWindow, OBJ_VRAM0 + OBJWINDOW_VOBJ);
	ApplyPalettes(Pal_ObjWindow, OBJWINDOW_PAL + 0x10, 1);
	
}



void PrepSkillObj_OnUpdate(ProcPtr proc){
	
	struct Unit* unit;
	struct PrepSkillsList* list;
	
	// Skill tips
	if( !IsPrepSkillListValid() )
		return;
	
	// On Init
	list = gpCommonSpace;
	unit = GetUnit(list->unit_index);
	
	
	if( GetGameClock() & (1 << 5) )
		return;
	
	
	// RAM 
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_RAM]; i++ )
		PutSprite(5, 
			0x18 + 0x10 * i, 
			0x38, 
			gObject_8x16, 
			OAM2_PAL(SKILLOBJ_PAL) + 
				OAM2_LAYER(0b00) + 
				OAM2_CHR(SKILLOBJ_VOBJ / 0x20));
	
	
	
	// ROM 
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_ROM]; i++ )
		PutSprite(5, 
			0x18 + 0x10 * _lib_mod(i, 5), 
			0x58 + 0x10 * _lib_div(i, 5),
			gObject_8x16, 
			OAM2_PAL(SKILLOBJ_PAL) + 
				OAM2_LAYER(0b00) + 
				OAM2_CHR(SKILLOBJ_VOBJ / 0x20 + 1));
	
	
	// Right
	for( int i = 0; i < list->total[PREP_SKLSUB_RIGHT]; i++ )
	{
		u8 skill_id = list->skills_all[i];
		
		if( IsPrepSkillRom(unit, skill_id) )
			PutSprite(5, 
				0x80 + 0x10 * _lib_mod(i, 6), 
				0x28 + 0x10 * _lib_div(i, 6),
				gObject_8x16, 
				OAM2_PAL(SKILLOBJ_PAL) + 
					OAM2_LAYER(0b01) + 
					OAM2_CHR(SKILLOBJ_VOBJ / 0x20 + 1));
					
		else if( isPrepSkillEquippedRAM(unit, skill_id) )
			PutSprite(5, 
				0x80 + 0x10 * _lib_mod(i, 6), 
				0x28 + 0x10 * _lib_div(i, 6),
				gObject_8x16, 
				OAM2_PAL(SKILLOBJ_PAL) + 
					OAM2_LAYER(0b01) + 
					OAM2_CHR(SKILLOBJ_VOBJ / 0x20));
	}
				
	
	
	
	
}









// =======================================================
// ====================== GLOBAL =========================
// =======================================================
void StartProc_PrepSkillObj(ProcPtr parent){
	
	Proc_EndEach(gProc_PrepSkillPutObj);

	Proc_Start(gProc_PrepSkillPutObj, parent);
	
}

void EndProc_PrepSkillObj(){
	
	Proc_EndEach(gProc_PrepSkillPutObj);
	
}
