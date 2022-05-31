#include "gbafe-chax.h"
#include "PrepSkill.h"

static void (*PrepDrawHand)(int x, int y, int, int) = (const void*) 0x80AD51D;

static void PrepSkillObj_OnInit(ProcPtr proc);
static void PrepSkillObj_OnUpdate(void);
static void PrepCombatArtObj_OnUpdate(void);

// Sub Update Skill
static void PrepSkillObj_PrepareTotalListIcons(struct Proc_PrepPickSkill*);
static void PrepSkillObj_DrawTotalListIcons(struct Proc_PrepPickSkill*);
static void PrepSkillObj_ScrollTotalListIcons(struct Proc_PrepPickSkill*);
static void PrepSkillObj_UpdateLabel(struct Unit*, struct PrepSkillsList*, struct Proc_PrepPickSkill*);

static void PrepCombatArtObj_PrepareTotalListIcons(struct Proc_PrepPickSkill*);
static void PrepCombatArtObj_UpdateLabel(struct Unit*, struct PrepSkillsList*, struct Proc_PrepPickSkill*);

// ========================================
// ================ Main ==================
// ========================================



const static struct ProcCmd gProc_PrepSkillPutObj[] = {
	
	PROC_NAME	("PREPSKILL_OBJ"),
	
	PROC_CALL	(PrepSkillObj_OnInit),
	PROC_REPEAT	(PrepSkillObj_OnUpdate),
	
	PROC_END,
	
};


const static struct ProcCmd gProc_PrepCombatArtObj[] = {
	
	PROC_NAME	("PREP_COMBAT_ART_OBJ"),
	
	PROC_CALL	(PrepSkillObj_OnInit),
	PROC_REPEAT	(PrepCombatArtObj_OnUpdate),
	
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








void PrepSkillObj_OnUpdate(void){
	
	
	
	// Skill tips
	if( !IsPrepSkillListValid() )
		return;
	
	// On Init
	struct PrepSkillsList* list = gpPrepSkillList;
	struct Unit* unit = GetUnit(list->unit_index);
	struct Proc_PrepPickSkill* proc = Proc_Find(gProc_PrepSkillPickSkillList);
	
	// Check Scrolling
	if( PREP_SCROLL_NOPE != proc->scroll_type ){
		PrepSkillObj_ScrollTotalListIcons(proc);
		return;
	}
	
	
	if( proc->right_disp_reset )
		PrepSkillObj_PrepareTotalListIcons(proc);
	
	
	PrepSkillObj_DrawTotalListIcons(proc);
	
	if( GetGameClock() & (1 << 5) )
		PrepSkillObj_UpdateLabel(unit, list, proc);

}

inline int OBJ_DEST(int i){
		return VOBJ_SKILL_ICONS + 0x40 * i;
}

void PrepSkillObj_PrepareTotalListIcons(struct Proc_PrepPickSkill* proc){
	
	struct PrepSkillsList* list = gpPrepSkillList;
	
	u8 count = 0;
	
	for( int i = proc->head_line * 6; i < list->total[PREP_SKLSUB_RIGHT]; i++ ){
		
		u8 skill_id = list->skills_all[i];
		
		if( !SKILL_VALID(skill_id) )
			continue;
		
		void *dest = count < 0x10
			? OBJ_VRAM0 + OBJ_DEST(count)
			: OBJ_VRAM0 + OBJ_DEST(count + 0x10);
		
		CopyTileGfxForObj( GetSkillIconGfx(skill_id), dest, 2, 2);
		
		count++;
		
		if( count >= 18 )
			break;
	}
	
	proc->displaying_count = count;
	proc->right_disp_reset = 0;
}

void PrepSkillObj_DrawTotalListIcons(struct Proc_PrepPickSkill* proc){

	
	if( 0 == proc->displaying_count )
		return;
	
	// Put Objs
	int count = 0;
	
	for( int i = 0; i < 18; i++ ){
		
		void* src = i < 0x10
			? OBJ_VRAM0 + OBJ_DEST(count)
			: OBJ_VRAM0 + OBJ_DEST(count + 0x10);
		
		PutSprite(5, 
			0x78 + 0x10 * _lib_mod(i, 6), 
			0x28 + 0x10 * _lib_div(i, 6),
			gObject_16x16, 
			OAM2_PAL(SKILLOBJ_PAL) + 
				OAM2_LAYER(0b01) + 
				OAM2_CHR((u32)src / 0x20));
		
		count++;
		
		if( count >= proc->displaying_count )
			break;
	}
	

}


void PrepSkillObj_ScrollTotalListIcons(struct Proc_PrepPickSkill* proc){
	
	if( proc->scroll_diffCur > 0xF ){
		
		proc->head_line = PREP_SCROLL_UP == proc->scroll_type
			? proc->head_line - 1
			: proc->head_line + 1;
			
		proc->scroll_diffCur = 0;
		proc->scroll_type = PREP_SCROLL_NOPE;
		proc->right_disp_reset = 1;
		
		// I have no idea why failed on update hand
		PrepDrawHand( 
			0x78 + 0x10 * _lib_mod(proc->list_index, 6), 
			0x28 + 0x10 * (_lib_div(proc->list_index, 6) - proc->head_line), 
			0, 0x800);
		return;
	}
	
	proc->scroll_diffCur += proc->scroll_step;
	
	if( PREP_SCROLL_DOWN == proc->scroll_type ){
		
		for( int i = 6; i < 18; i++ ){
			
			void* src = i < 0x10
				? OBJ_VRAM0 + OBJ_DEST(i)
				: OBJ_VRAM0 + OBJ_DEST(i + 0x10);
			
			PutSprite(5, 
				0x78 + 0x10 * _lib_mod(i, 6), 
				0x28 + 0x10 * _lib_div(i, 6) - proc->scroll_diffCur,
				gObject_16x16, 
				OAM2_PAL(SKILLOBJ_PAL) + 
					OAM2_LAYER(0b01) + 
					OAM2_CHR((u32)src / 0x20));
			
			
			if( i >= proc->displaying_count )
				break;
		}
	}
	
	else if( PREP_SCROLL_UP == proc->scroll_type ){
		
		for( int i = 0; i < 12; i++ ){
			
			void* src = i < 0x10
				? OBJ_VRAM0 + OBJ_DEST(i)
				: OBJ_VRAM0 + OBJ_DEST(i + 0x10);
			
			PutSprite(5, 
				0x78 + 0x10 * _lib_mod(i, 6), 
				0x28 + 0x10 * _lib_div(i, 6) + proc->scroll_diffCur,
				gObject_16x16, 
				OAM2_PAL(SKILLOBJ_PAL) + 
					OAM2_LAYER(0b01) + 
					OAM2_CHR((u32)src / 0x20));
			
			
			if( i >= proc->displaying_count )
				break;
		}
	}

}



void PrepSkillObj_UpdateLabel(struct Unit* unit, struct PrepSkillsList* list, struct Proc_PrepPickSkill* proc){
	
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
			0x48 + 0x10 * _lib_div(i, 5),
			gObject_8x16, 
			OAM2_PAL(SKILLOBJ_PAL) + 
				OAM2_LAYER(0b00) + 
				OAM2_CHR(SKILLOBJ_VOBJ / 0x20 + 1));
	
	
	// Right
	for( int i = 0; i < proc->displaying_count; i++ )
	{
		u8 num = i + 6 * proc->head_line;
		u8 skill_id = list->skills_all[num];
		
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
//                      Combat Art
// =======================================================


void PrepCombatArtObj_OnUpdate(){
	
	// Skill tips
	if( !IsPrepSkillListValid() )
		return;
	
	// On Init
	struct PrepSkillsList* list = gpPrepSkillList;
	struct Unit* unit = GetUnit(list->unit_index);
	struct Proc_PrepPickSkill* proc = Proc_Find(gProc_PrepSkillPickCombatArtList);
	
	
	// Check Scrolling
	if( PREP_SCROLL_NOPE != proc->scroll_type ){
		PrepSkillObj_ScrollTotalListIcons(proc);
		return;
	}
	
	
	if( proc->right_disp_reset )
		PrepCombatArtObj_PrepareTotalListIcons(proc);
	
	
	PrepSkillObj_DrawTotalListIcons(proc);
	
	
	if( GetGameClock() & (1 << 5) )
		PrepCombatArtObj_UpdateLabel(unit, list, proc);
	
}


void PrepCombatArtObj_PrepareTotalListIcons(struct Proc_PrepPickSkill* proc){
	
	struct PrepSkillsList* list = gpPrepSkillList;
	
	u8 count = 0;
	
	for( int i = proc->head_line * 6; i < list->total[PREP_SKLSUB_RIGHT]; i++ ){
		
		u8 index = list->skills_all[i];
		
		if( !SKILL_VALID(index) )
			continue;
		
		
		void *dest = count < 0x10
			? OBJ_VRAM0 + OBJ_DEST(count)
			: OBJ_VRAM0 + OBJ_DEST(count + 0x10);
		
		CopyTileGfxForObj( GetCombatArtIconGfx(index), dest, 2, 2);
		
		count++;
		
		if( count >= 18 )
			break;
	}
	
	proc->displaying_count = count;
	proc->right_disp_reset = 0;
	
}






void PrepCombatArtObj_UpdateLabel(struct Unit* unit, struct PrepSkillsList* list, struct Proc_PrepPickSkill* proc){
	
	// Right
	for( int i = 0; i < proc->displaying_count; i++ )
	{
		u8 num = i + 6 * proc->head_line;
		u8 skill_id = list->skills_all[num];
				
		if( isPrepCombatArtRAM(unit, skill_id) )
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



void StartProc_PrepCombatArtObj(ProcPtr parent){
	
	Proc_EndEach(gProc_PrepCombatArtObj);

	Proc_Start(gProc_PrepCombatArtObj, parent);
	
}

void EndProc_PrepCombatArtObj(){
	
	Proc_EndEach(gProc_PrepCombatArtObj);
	
}
