#include "gbafe.h"
#include "gbafe-chax.h"

const void* GetSkillIconGfx(u8 skill_id){
	
	return SkillInfoTable[skill_id]->icon;
	
}


int GetSkillDescMsg(u8 skill_id){
	
	return SkillInfoTable[skill_id]->msg_desc;
	
}