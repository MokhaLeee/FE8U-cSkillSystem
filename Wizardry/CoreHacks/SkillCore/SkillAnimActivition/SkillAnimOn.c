#include "gbafe-chax.h"
#include "SkillAnim.h"

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

typedef void (*AnimFunc) (struct Anim*);

extern AnimFunc SkillAnimationTable[0x100];

static u8 SortAnimActSkill(u8 skills[], const int max_num);



// =====================================================
//                 function definition
// =====================================================
int cSkillActivationAnims(struct Anim* anim){
	
	struct BattleHitExt *bh_ext_cur;
	int attr_ext;
	u8 skill_act = 0;
	AnimFunc anim_func = 0;
	
	enum{
		// return value
		ACTANIM_END = 0,
		ACTANIM_NOANIM = 1,
		ACTANIM_NOANIM2 = 2,
	};
	
	bh_ext_cur = &BattleHitExtArray[anim->nextRoundId - 1];
	attr_ext = bh_ext_cur->attr;
	
	
	if( ATTR_HITEXT_SKILLACT_ATK & attr_ext )
		skill_act = SortAnimActSkill(bh_ext_cur->atk_skills, 3);
	
	if( ATTR_HITEXT_SKILLACT_DEF & attr_ext )
		skill_act = SortAnimActSkill(bh_ext_cur->def_skills, 3);
	
	
	// Check if we're front AIS layer.
	if( 0 != GetAISLayerId(anim) )
		return ACTANIM_NOANIM;
	
	
	// make skill activation
	if( SKILL_VALID(skill_act) )
		anim_func = SkillAnimationTable[skill_act];
	
	if( 0 != anim_func )
	{
		// maybe set as activating skill
		anim->state3 |= 0x20;
		
		anim_func(anim);
	}
	
	StartSkillBoxControler(anim);
	
	return ACTANIM_END;
}





// =====================================================
//                  Static function
// =====================================================

u8 SortAnimActSkill(u8 skills[], const int max_num){
	
	for( int i = 0; i < max_num; i++ )
		if( 0 != SkillAnimationTable[skills[i]] )
			return skills[i];
	
	return 0;
}
