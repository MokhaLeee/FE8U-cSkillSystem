#include "gbafe-chax.h"

void EventCh0_DebugAllies(void){
	
	struct Unit*  unit;
	
	#define DEBUG_UNIT_SKILLS(charId) \
		unit = GetUnitFromCharId(charId); \
		\
		for( int i = 0; i < 0x50; i++ ) \
			SetUnitMasterClass(unit, i); \
		\
		SetWExp(unit, ITYPE_SWORD, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_LANCE, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_AXE, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_BOW, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_BMAG, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_WMAG, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_RIDE, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_FLY, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_HEAVY, WPN_EXP_S);	\
		SetWExp(unit, ITYPE_CLASS, WPN_EXP_S);
	
	DEBUG_UNIT_SKILLS(CHARACTER_EIRIKA);
	DEBUG_UNIT_SKILLS(CHARACTER_SETH);
	DEBUG_UNIT_SKILLS(CHARACTER_INNES);
	DEBUG_UNIT_SKILLS(CHARACTER_LUTE);
	DEBUG_UNIT_SKILLS(CHARACTER_KYLE);
	
	#undef DEBUG_UNIT_SKILLS
}