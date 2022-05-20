#include "gbafe-chax.h"


// ====================================================
//                   Static Declearation
// ====================================================

enum{
	
	// Real VRAM Offset to uncompress: OBJ_VRAM0 + OBJ_MOKHA_VRAMOFF
	OBJ_VRAMOFF = 0x53C0, 
	

};

struct Proc_Gravity{
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 timer;
	/* 2C */ struct Unit* unit;

};

struct Proc_SubGravity{
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 xPos;
	/* 2A */ u8 yPos;
	/* 2B */ u8 timer;
	/* 2C */ u8 xReal;
	/* 2D */ u8 yReal;
};

static void ProcGravity_OnInit(struct Proc_Gravity*);
static int ProcGravity_MoveCamera(struct Proc_Gravity*);
static void ProcGravity_StartSubAnim(struct Proc_Gravity*);
static void ProcGravity_SubAnimExist(struct Proc_Gravity*);

static const struct ProcCmd ProcCmd_MapAnimGravity[] = {
	
	PROC_CALL( ProcGravity_OnInit ),
	// PROC_CALL_2( ProcGravity_MoveCamera ),
	PROC_REPEAT( ProcGravity_StartSubAnim ),
	PROC_YIELD,
	PROC_REPEAT( ProcGravity_SubAnimExist ),
	PROC_END,
};


static void ProcSubGravity_OnInit(struct Proc_SubGravity*);
static void ProcSubGravity_UpdateAnim(struct Proc_SubGravity*);

static const struct ProcCmd ProcCmd_GravitySubAnim[] = {
	
	PROC_YIELD,
	PROC_CALL( ProcSubGravity_OnInit ),
	PROC_REPEAT( ProcSubGravity_UpdateAnim ),
	PROC_END,
};



// ====================================================
//               Function Definition
// ====================================================

void ProcGravity_OnInit(struct Proc_Gravity* proc){
	
	extern u16 Gfx_Gravity[];
	
	// Gfx
	CopyDataWithPossibleUncomp( Gfx_Gravity, OBJ_VRAM0 + OBJ_VRAMOFF ); 
	
	// Init timer
	proc->timer = 0;
	
	// M4A
	PlaySoundEffect(0x86);
	
	
}

int ProcGravity_MoveCamera(struct Proc_Gravity* proc){
	
	return EnsureCameraOntoPosition(proc, proc->unit->xPos, proc->unit->yPos);
}


void ProcGravity_StartSubAnim(struct Proc_Gravity* proc){
	
	proc->timer++;
	
	if( 0 == proc->timer % 10 )
	{
		struct Proc_SubGravity* child = 
			Proc_Start(ProcCmd_GravitySubAnim, PROC_TREE_3);
		
		child->xPos = proc->unit->xPos * 16 - gGameState.camera.x;
		child->yPos = proc->unit->yPos * 16 - gGameState.camera.y;
	}
	
	if( 3 < proc->timer / 10 )
		Proc_Break(proc);
}



void ProcGravity_SubAnimExist(struct Proc_Gravity* proc){
	
	if( !Proc_Find(ProcCmd_GravitySubAnim) )
		Proc_Break(proc);
		
}



// Sub Proc
void ProcSubGravity_OnInit(struct Proc_SubGravity* proc){
	
	if( (proc->xPos > 0xF0) || (proc->yPos > 0xA0) )
	{
		Proc_End(proc);
		return;
	}
	
	proc->xReal = (proc->xPos + 0x200) & 0x1FF;
	proc->yReal = (proc->yPos + 0xFD) & 0xFF;
	proc->timer = 0;
}


void ProcSubGravity_UpdateAnim(struct Proc_SubGravity* proc){
	
	
	PutSprite(
		1, 
		proc->xReal, 
		proc->yReal,
		gObject_16x8, 
		OAM2_PAL(0) + OAM2_CHR(OBJ_VRAMOFF / 0x20) + OAM2_LAYER(0x1));
	
	proc->yReal++;
	
	if( ++proc->timer > 0xF )
		Proc_Break(proc);
}





// ====================================================
//                      External
// ====================================================

void StartMapAnim_Gravity(struct Unit* unit, ProcPtr proc){
	
	struct Proc_Gravity* child = 
		Proc_StartBlocking(ProcCmd_MapAnimGravity, proc);
	
	child->unit = unit;
}