#include "gbafe.h"

int ShouldSkipGameStartIntro(){
	
	// extern u8 gUnknown_0300001A[];
	extern const u8 * GameIntroSkip_RomJudgeByte;
	
	if( 0 == *GameIntroSkip_RomJudgeByte )
		return 1;
	
	return gUnknown_0300001A;
}