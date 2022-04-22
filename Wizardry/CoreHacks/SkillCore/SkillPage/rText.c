#include "gbafe-chax.h"

extern struct HelpBoxInfo const HB_P0_Str, HB_P0_Res, HB_P0_Lck, HB_P0_HP, HB_P0_Stat;
static int (* const _TryRelocateHbUp)(struct HelpBoxProc* proc) = (void const*) 0x08089355;
static int (* const _TryRelocateHbDown)(struct HelpBoxProc* proc) = (void const*) 0x8089385;
static int (* const _TryRelocateHbLeft)(struct HelpBoxProc* proc) = (void const*) 0x80893b5;
static int (* const _TryRelocateHbRight)(struct HelpBoxProc* proc) = (void const*) 0x80893e5;

static void HbRedirect_Skill(struct HelpBoxProc* proc) {
	
	if ( proc->info->mid < GetOrMakeSklFastList(gStatScreen.unit)->cnt )
		return;
	
	switch ( proc->moveKey ) {
		
		case DPAD_LEFT:
			_TryRelocateHbLeft(proc);
			break;
		
		case DPAD_RIGHT:
			_TryRelocateHbRight(proc);
			break;
			
		case DPAD_DOWN:
			_TryRelocateHbDown(proc);
			break;
		
		case DPAD_UP:
		default:
			_TryRelocateHbUp(proc);
			break;
			
	} // switch
}

static void HbPopuplate_Skill(struct HelpBoxProc* proc){

	int skill_id = GetOrMakeSklFastList(gStatScreen.unit)->skills[proc->info->mid];
	
	proc->mid = GetSkillDescMsg(skill_id);

}



const struct HelpBoxInfo HB_P0_Skill0;
const struct HelpBoxInfo HB_P0_Skill1;
const struct HelpBoxInfo HB_P0_Skill2;
const struct HelpBoxInfo HB_P0_Skill3;
const struct HelpBoxInfo HB_P0_Skill4;
const struct HelpBoxInfo HB_P0_Skill5;
const struct HelpBoxInfo HB_P0_Skill6;

const struct HelpBoxInfo HB_P0_Skill0 =
{
	&HB_P0_Res, &HB_P0_Str, &HB_P0_HP, &HB_P0_Skill1,
	0x80, 0x88, 0, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P0_Skill1 =
{
	&HB_P0_Res, &HB_P0_Str, &HB_P0_Skill0, &HB_P0_Skill2,
	0x90, 0x88, 1, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P0_Skill2 =
{
	&HB_P0_Stat, &HB_P0_Lck, &HB_P0_Skill1, &HB_P0_Skill3,
	0xA0, 0x88, 2, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P0_Skill3 =
{
	&HB_P0_Stat, &HB_P0_Lck, &HB_P0_Skill2, &HB_P0_Skill4,
	0xB0, 0x88, 3, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P0_Skill4 =
{
    &HB_P0_Stat, &HB_P0_Lck, &HB_P0_Skill3, &HB_P0_Skill5,
    0xC0, 0x88, 4, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P0_Skill5 =
{
    &HB_P0_Stat, &HB_P0_Lck, &HB_P0_Skill4, &HB_P0_Skill6,
    0xD0, 0x88, 5, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P0_Skill6 =
{
    &HB_P0_Stat, &HB_P0_Lck, &HB_P0_Skill5, &HB_P0_HP,
    0xE0, 0x88, 6, HbRedirect_Skill, HbPopuplate_Skill,
};