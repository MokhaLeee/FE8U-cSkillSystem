#include "gbafe.h"

extern u8 *gpPortraitHeightList;

int new_ShouldPortraitBeSmol(const u8 portraitId){
	
	for(int i=0; gpPortraitHeightList[i]!=0; i++)
		if( portraitId == gpPortraitHeightList[i] )
			return TRUE;
	
	return FALSE;

}
