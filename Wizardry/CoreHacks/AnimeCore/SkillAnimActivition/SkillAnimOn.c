#include "gbafe-chax.h"

// =====================================================
//                     add for c-lib
// =====================================================

// right unit = 0; left = 1;
int GetAISSubjectId(struct Anim* anim);

int GetAISLayerId(struct Anim*);

// offensive: 0x806E310
// defensive: 0x806E58C


// =====================================================
//                 function declearation
// =====================================================

struct SPD_ProcStateMain {
  
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 skill;
	/* 2A */ u8 right;
	/* 2B */ u8 timer;
	/* 2C */ u16 depth;
	/* 2E */ u16 msg_name;
	/* 30 */ const void* icon;
	/* 30 */ struct TextHandle textHandle;
  
};

extern const struct ProcCmd SPD_main_Proc[];
extern const struct ProcCmd gProc_ekrGauge[];



typedef void (*AnimFunc) (struct Anim*);

extern AnimFunc SkillAnimationTable[0x100], CombatArtAnimationTable[0x100];

static u8 SortAnimActSkill(u8 skills[], const int max_num);



// =====================================================
//                 function definition
// =====================================================
int cSkillActivationAnims(struct Anim* anim){
	
	struct BattleHitExt *bh_ext_cur;
	int attr_ext;
	u8 skill_act = 0;
	AnimFunc anim_func = 0;
	u16 msg_name;
	const void* icon;
	
	enum{
		// return value
		ACTANIM_END = 0,
		ACTANIM_NOANIM = 1,
		ACTANIM_NOANIM2 = 2,
	};
	
	bh_ext_cur = &BattleHitExtArray[anim->nextRoundId - 1];
	attr_ext = bh_ext_cur->attr;
	
	
	
	if( ATTR_HITEXT_COMBAT_ART & attr_ext )
	{
		// Combat Art
		
		skill_act = gpBattleFlagExt->combatArt_id;
		
		const struct CombatArtInfo *info = GetCombatArtInfo(skill_act);
		
		if( 0 == info )
			return ACTANIM_NOANIM;
		
		anim_func = 
			(0 == CombatArtAnimationTable[skill_act])
			? CombatArtAnimationTable[0]
			: CombatArtAnimationTable[skill_act];
		
		msg_name = info->msg_name;
		
		icon = GetIconGfx( COMBAT_ART_ICON(skill_act) );
	}
	else
	{
		// Skills
		if( ATTR_HITEXT_SKILLACT_ATK & attr_ext )
			skill_act = SortAnimActSkill(bh_ext_cur->atk_skills, 3);
		
		if( ATTR_HITEXT_SKILLACT_DEF & attr_ext )
			skill_act = SortAnimActSkill(bh_ext_cur->def_skills, 3);
		
		
		// Check if we're front AIS layer.
		if( 0 != GetAISLayerId(anim) )
			return ACTANIM_NOANIM;
		
		
		// make skill activation
		if( !SKILL_VALID(skill_act) )
			return ACTANIM_NOANIM;
		
		anim_func = SkillAnimationTable[skill_act];
		msg_name = GetSkillNameMsg(skill_act);
		icon = GetIconGfx( SKILL_ICON(skill_act) );
	}
	
	if( 0 == anim_func )
		anim_func = SkillAnimationTable[0];

	// maybe set as activating skill
	anim->state3 |= 0x20;	
	anim_func(anim);

	
	
	// =====================================================
	//            Copy from skill-system fe8
	// =====================================================
	
	
	
	struct SPD_ProcStateMain* proc;
	struct Proc* parent = Proc_Find(gProc_ekrGauge);
	
	if( NULL == parent )
		return ACTANIM_END;
	
	proc = Proc_Start(SPD_main_Proc, parent);
	proc->msg_name = msg_name;
	proc->icon = icon;
	proc->right = GetAISSubjectId(anim); // currently only offensive skill
	proc->timer = anim->drawLayerPriority + 1;
	
	return ACTANIM_END;
}





// =====================================================
//                  Static function
// =====================================================

u8 SortAnimActSkill(u8 skills[], const int max_num){
	
	for( int i = 0; i < max_num; i++ )
		if( SKILL_VALID(skills[i]) )
			return skills[i];
	
	return 0;
}








