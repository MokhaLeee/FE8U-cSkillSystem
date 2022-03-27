#include "gbafe.h"
#include "gbafe-chax.h"

const void* GetSkillIconGfx(u8 skill_id){
	
	if( (0 == skill_id) || (0xFF == skill_id) || (NULL == SkillInfoTable[skill_id]) )
		return 0;
	else
		return SkillInfoTable[skill_id]->icon;
	
}


int GetSkillDescMsg(u8 skill_id){
	
	return SkillInfoTable[skill_id]->msg_desc;
	
}