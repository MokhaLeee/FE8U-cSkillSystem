#include "gbafe-chax.h"

extern const struct UnitRomDataExpa UnitRomDataExpaTable[0x100]; 
extern const struct ClassRomDataExpa ClassRomDataExpaTable[0x100]; 

const struct UnitRomDataExpa *GetUnitRomDataExpa(u8 char_id){
	return &UnitRomDataExpaTable[char_id];
}

const struct ClassRomDataExpa *GetClassRomDataExpa(u8 class_id){
	return &ClassRomDataExpaTable[class_id];
}

