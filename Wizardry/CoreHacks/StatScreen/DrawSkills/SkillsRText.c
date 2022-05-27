#include "gbafe-chax.h"

extern struct HelpBoxInfo const HB_P2_BMag, HB_P2_ClassR, HB_P2_Sword, HB_P2_WMag, HB_P2_Exp, HB_P2_Level, HB_P2_HP;

const struct HelpBoxInfo HB_P2_Skill0;
const struct HelpBoxInfo HB_P2_Skill1;
const struct HelpBoxInfo HB_P2_Skill2;
const struct HelpBoxInfo HB_P2_Skill3;
const struct HelpBoxInfo HB_P2_Skill4;
const struct HelpBoxInfo HB_P2_Skill5;
const struct HelpBoxInfo HB_P2_Skill6;
const struct HelpBoxInfo HB_P2_Skill7;
const struct HelpBoxInfo HB_P2_Skill8;
const struct HelpBoxInfo HB_P2_Skill9;

const struct HelpBoxInfo HB_P2_Art0;
const struct HelpBoxInfo HB_P2_Art1;
const struct HelpBoxInfo HB_P2_Art2;
const struct HelpBoxInfo HB_P2_Art3;
const struct HelpBoxInfo HB_P2_Art4;



// Skills

static void HbRedirect_Skill(struct HelpBoxProc* proc) {
	
	if ( proc->info->mid < GetOrMakeSklFastList(gStatScreen.unit)->cnt )
		return;
	
	switch ( proc->moveKey ) {
		
		case DPAD_LEFT:
			TryRelocateHbLeft(proc);
			break;
		
		case DPAD_RIGHT:
			TryRelocateHbRight(proc);
			break;
			
		case DPAD_DOWN:
			TryRelocateHbDown(proc);
			break;
		
		case DPAD_UP:
		default:
			TryRelocateHbUp(proc);
			break;
			
	} // switch
}

static void HbPopuplate_Skill(struct HelpBoxProc* proc){

	int skill_id = GetOrMakeSklFastList(gStatScreen.unit)->skills[proc->info->mid];
	
	proc->mid = GetSkillDescMsg(skill_id);

}




const struct HelpBoxInfo HB_P2_Skill0 =
{
	&HB_P2_BMag, &HB_P2_Skill5, &HB_P2_Exp, &HB_P2_Skill1,
	0x80, 0x70, 0, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P2_Skill1 =
{
	&HB_P2_BMag, &HB_P2_Skill6, &HB_P2_Skill0, &HB_P2_Skill2,
	0x90, 0x70, 1, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P2_Skill2 =
{
	&HB_P2_ClassR, &HB_P2_Skill7, &HB_P2_Skill1, &HB_P2_Skill3,
	0xA0, 0x70, 2, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P2_Skill3 =
{
	&HB_P2_ClassR, &HB_P2_Skill8, &HB_P2_Skill2, &HB_P2_Skill4,
	0xB0, 0x70, 3, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P2_Skill4 =
{
    &HB_P2_ClassR, &HB_P2_Skill9, &HB_P2_Skill3, &HB_P2_Skill5,
    0xC0, 0x70, 4, HbRedirect_Skill, HbPopuplate_Skill,
};




// Line 2
const struct HelpBoxInfo HB_P2_Skill5 =
{
    &HB_P2_Skill0, &HB_P2_Art0, &HB_P2_Exp, &HB_P2_Skill6,
    0x80, 0x80, 5, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P2_Skill6 =
{
    &HB_P2_Skill1, &HB_P2_Art0, &HB_P2_Skill5, &HB_P2_Skill7,
    0x90, 0x80, 6, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P2_Skill7 =
{
    &HB_P2_Skill2, &HB_P2_Art0, &HB_P2_Skill6, &HB_P2_Skill8,
    0xA0, 0x80, 7, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P2_Skill8 =
{
    &HB_P2_Skill3, &HB_P2_Art0, &HB_P2_Skill7, &HB_P2_Skill9,
    0xB0, 0x80, 8, HbRedirect_Skill, HbPopuplate_Skill,
};

const struct HelpBoxInfo HB_P2_Skill9 =
{
    &HB_P2_Skill4, &HB_P2_Art0, &HB_P2_Skill8, &HB_P2_Level,
    0xC0, 0x80, 9, HbRedirect_Skill, HbPopuplate_Skill,
};




// Combat Arts
static int GetCurrentArtIndex(int mid){
	
	u8 *art_list = GetCombatArtList(gStatScreen.unit);
	
	for(int i = 0; i < 5; i++)
		if( SKILL_VALID(art_list[i]) )
		{
			if( mid > 0 )
				mid--;
			else
				return art_list[i];
		}
	
	return 0;
}

static void HbRedirect_Art(struct HelpBoxProc* proc) {
	
	if ( SKILL_VALID(GetCurrentArtIndex(proc->info->mid)) )
		return;
	
	switch ( proc->moveKey ) {
		
		case DPAD_LEFT:
			TryRelocateHbLeft(proc);
			break;
		
		case DPAD_RIGHT:
			TryRelocateHbRight(proc);
			break;
			
		case DPAD_DOWN:
			TryRelocateHbDown(proc);
			break;
		
		case DPAD_UP:
		default:
			TryRelocateHbUp(proc);
			break;
			
	} // switch
}

static void HbPopuplate_Art(struct HelpBoxProc* proc){

	int art_id = GetCurrentArtIndex(proc->info->mid);
	
	proc->mid = GetCombatArtInfo(art_id)->msg_desc;

}



const struct HelpBoxInfo HB_P2_Art0 =
{
	&HB_P2_Skill5, &HB_P2_Sword, &HB_P2_Exp, &HB_P2_Art1,
	0x80, 0x90, 0, HbRedirect_Art, HbPopuplate_Art,
};

const struct HelpBoxInfo HB_P2_Art1 =
{
	&HB_P2_Skill5, &HB_P2_Sword, &HB_P2_Art0, &HB_P2_Art2,
	0x90, 0x90, 1, HbRedirect_Art, HbPopuplate_Art,
};

const struct HelpBoxInfo HB_P2_Art2 =
{
	&HB_P2_Skill5, &HB_P2_WMag, &HB_P2_Art1, &HB_P2_Art3,
	0xA0, 0x90, 2, HbRedirect_Art, HbPopuplate_Art,
};

const struct HelpBoxInfo HB_P2_Art3 =
{
	&HB_P2_Skill5, &HB_P2_WMag, &HB_P2_Art2, &HB_P2_Art4,
	0xB0, 0x90, 3, HbRedirect_Art, HbPopuplate_Art,
};

const struct HelpBoxInfo HB_P2_Art4 =
{
    &HB_P2_Skill5, &HB_P2_WMag, &HB_P2_Art3, &HB_P2_HP,
    0xC0, 0x90, 4, HbRedirect_Art, HbPopuplate_Art,
};