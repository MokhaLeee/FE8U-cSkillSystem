
#include "gbafe-chax.h"
extern void** gpBWLSaveTarget; // 0x203E890

struct NewBwlData* NBwl_GetBwlData(unsigned charId)
{
	charId = charId - 1;
	return gBWLDataStorage + charId;
}

int NBwl_HasBwl(unsigned charId)
{
    return (charId < MAX_BWL_CHAR) && GetCharacterData(charId)->affinity;
}




// 0A4264
void NBwl_SaveBwl(void* target, unsigned size)
{
	const unsigned amt = size/0x10 > MAX_BWL_CHAR ? MAX_BWL_CHAR : size/0x10;
	uint32_t cur = 0;
	
	for (unsigned i = 0; i < amt; ++i){
		
		WriteAndVerifySramFast((const void*)&gBWLDataStorage[i], target + cur , 0x10);
		
		cur += 0x10;
		
		if ( cur > size )
			break;
	}
}

// 0A421C
void NBwl_LoadBwl(void* source, unsigned size)
{
	const unsigned amt = size/0x10 > MAX_BWL_CHAR ? MAX_BWL_CHAR : size/0x10;
	uint32_t cur = 0;
	
	for (unsigned i = 0; i < amt; ++i){
		
		(*ReadSramFast)(source, (void*)&gBWLDataStorage[i], 0x10);
		
		cur += 0x10;
		
		if ( cur > size )
			break;
	
	}
	
	gpBWLSaveTarget = source;
}

