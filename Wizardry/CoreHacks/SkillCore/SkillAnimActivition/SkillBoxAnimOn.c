#include "gbafe-chax.h"
#include "SkillAnim.h"


// ===================================================
//                     Structs & Misc
// ===================================================

struct Proc_SkillBoxControler{
	
	/* 00 */ PROC_HEADER;
	
	u8 skills_atk[3];
	u8 skills_def[3];
	
};

struct Proc_SkillBoxItem{
	
	/* 00 */ PROC_HEADER;
	
	u8 skill_id;
	u8 timer;
	u8 xPos;
	u8 yPos;
	
};





// ===================================================
//                   Upper controler
// ===================================================

static void StartSkillBoxes(struct Proc_SkillBoxControler);
static int SkillBoxesExits(struct Proc_SkillBoxControler);

static const struct ProcCmd gProc_SkillBoxControler[] = {
	
	PROC_NAME("Skill_Activation_Box_Proc_Controller"),
	PROC_CALL(StartSkillBoxes),
	PROC_WHILE(SkillBoxesExits),
	PROC_END,
};

void StartSkillBoxes(struct Proc_SkillBoxControler){
	return;
}

int SkillBoxesExits(struct Proc_SkillBoxControler){
	return 0;
}




// ===================================================
//                     extern
// ===================================================

void StartSkillBoxControler(struct Anim* anim){
	
	extern const struct ProcCmd gProc_ekrGauge[];
	
	struct Proc* parent;
	struct Proc_SkillBoxControler* proc;
	struct BattleHitExt *bh_ext;
	
	bh_ext = &BattleHitExtArray[anim->nextRoundId - 1];
	parent = Proc_Find(gProc_ekrGauge);

	if( NULL == parent )
		return;
	
	proc = Proc_Start(gProc_SkillBoxControler, parent);
	
	
	for( int i = 0; i < 3; i++ )
	{
		proc->skills_atk[i] = bh_ext->atk_skills[i];
		proc->skills_def[i] = bh_ext->def_skills[i];
	}
}