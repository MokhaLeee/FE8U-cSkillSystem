#include "gbafe.h"
#include "str-mag.h"


// need LoadUnitHook
void LoadUnit_Mag(struct Unit* unit){
	
	u8 char_id = unit->pCharacterData->number;
	u8 class_id= unit->pClassData->number;
	
	*GetMagAt(unit) = 
		UnitMagicTable[char_id].base +
		ClassMagicTable[class_id].base;
}