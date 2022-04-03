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
	
	// 注意！
	// 在相同优先度的情况下，Obj在图层的上下顺序也与插入的顺序有关
	// 越后插入的图层优先级越高
	// 由于我们不得不将Window和Skill tips同时放置于0b01优先级
	// 因而二者必须放在同一个函数中，并将 PutObjWindow 放置于 skill-tips之后，以确保window能够将tips覆盖
	// 但是这样一来我们也不得不在这里配置窗口框
	
	static void (*PutObjWindow)(int x, int y, int length, int height, int oam2) = (const void*) 0x809A31D;
	
	
	// Cursor
	DisplayCursor(0x98 + gGameState.camera.x, 0x28 + 1 + gGameState.camera.y, 1);
	
	
	
	
	// Skill tips
	if( GetGameClock() & (1 << 5) )
	{
		PutSprite(4, 
			0x80, 
			0x28, 
			gObject_8x16, 
			OAM2_PAL(SKILLOBJ_PAL) + 
				OAM2_LAYER(0b01) + 
				OAM2_CHR(SKILLOBJ_VOBJ / 0x20));
		
		PutSprite( 4,
			0x90, 
			0x28, 
			gObject_8x16, 
			OAM2_PAL(SKILLOBJ_PAL) + 
				OAM2_LAYER(0b01) + 
				OAM2_CHR(SKILLOBJ_VOBJ / 0x20 + 1));
	}
	
	
	
	
	// Obj Window
	PutObjWindow(
		OBJWINDOW_XPOS,
		OBJWINDOW_YPOS,
		OBJWINDOW_LENGTH,
		OBJWINDOW_HEIGHT,
		OAM2_PAL(OBJWINDOW_PAL) +
			OAM2_LAYER(0b01) +
			OAM2_CHR(OBJWINDOW_VOBJ / 0x20) );
	
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
