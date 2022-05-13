#include "gbafe-chax.h"

static void PostAction_OnInit(){
	
	if( gRAMChapterData.chapterVisionRange ) // Fog
	{
		RenderBmMapOnBg2();
		MoveActiveUnit(gActionData.xMove, gActionData.yMove);
		RefreshEntityBmMaps();
		RenderBmMap();
		NewBMXFADE(0);
		SMS_UpdateFromGameData();
	}
	else
	{
		MoveActiveUnit(gActionData.xMove, gActionData.yMove);
		RefreshEntityBmMaps();
		RenderBmMap();
	}
	
	SetCursorMapPosition(gActiveUnit->xPos, gActiveUnit->yPos);
	
	gGameState.cameraPrevious = gGameState.playerCursor;

}


int PostActionLoop(ProcPtr proc){
	
	typedef int (*PAL_Fun) (ProcPtr);
	extern PAL_Fun PostActionLoopTable[];
	
	PAL_Fun *it = &PostActionLoopTable[0];
	
	PostAction_OnInit();
	
	while( *it )
		if( 1 == (*it++)(proc) )
		{
			HideUnitSMS(gActiveUnit);
			return 0;
		}
	
	return 0;
	
}













