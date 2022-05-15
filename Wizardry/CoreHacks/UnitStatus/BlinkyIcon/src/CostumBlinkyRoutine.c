#include "gbafe-chax.h"


extern const struct ObjData *gUnknown_0859A530[], *gUnknown_0859A53C[];


void PutUnitStatusBuffIcon(struct Unit* unit){
	
	const u16 Obj_BuffArrow1[] = {
		1, 0x8000, 0x00, OAM2_CHR(0x4C) + OAM2_LAYER(0x2),
	};

	const u16 Obj_BuffArrow2[] = {
		1, 0x8000, 0x00, OAM2_CHR(0x4D) + OAM2_LAYER(0x2),
	};

	const u16 Obj_BuffArrow3[] = {
		1, 0x80FF, 0x00, OAM2_CHR(0x4D) + OAM2_LAYER(0x2),
	};
	
	u16 const * const Obj_BuffArrows[3] = {
		Obj_BuffArrow1, Obj_BuffArrow2, Obj_BuffArrow3
	};
	
	const u16 *obj_cur = Obj_BuffArrows[(GetGameClock()/8) % 3];
	
	int xPos = unit->xPos * 16 - gGameState.camera.x;
	int yPos = unit->yPos * 16 - gGameState.camera.y;
	
	if( xPos > 0xF0 )
		return;
	
	if( yPos > 0xA0 )
		return;
	
	xPos = (xPos + 0x1FF) & 0x1FF;
	yPos = (yPos + 0x100) & 0xFF;
	
	CallARM_PushToSecondaryOAM(xPos, yPos, obj_cur, 0);
}

void PutUnitStatusDeBuffIcon(struct Unit* unit){
	
	const u16 Obj_DeBuffArrow1[] = {
		1, 0x8000, 0x00, OAM2_CHR(0x4E) + OAM2_LAYER(0x2),
	};

	const u16 Obj_DeBuffArrow2[] = {
		1, 0x8000, 0x00, OAM2_CHR(0x4F) + OAM2_LAYER(0x2),
	};

	const u16 Obj_DeBuffArrow3[] = {
		1, 0x80FF, 0x00, OAM2_CHR(0x4F) + OAM2_LAYER(0x2),
	};
	
	u16 const * const Obj_DeBuffArrows[3] = {
		Obj_DeBuffArrow1, Obj_DeBuffArrow2, Obj_DeBuffArrow3
	};
	
	const u16 *obj_cur = Obj_DeBuffArrows[(GetGameClock()/8) % 3];
	
	int xPos = unit->xPos * 16 - gGameState.camera.x;
	int yPos = unit->yPos * 16 - gGameState.camera.y;
	
	if( xPos > 0xF0 )
		return;
	
	if( yPos > 0xA0 )
		return;
	
	xPos = (xPos + 0x1FF) & 0x1FF;
	yPos = (yPos + 0x100) & 0xFF;
	
	CallARM_PushToSecondaryOAM(xPos, yPos, (void*)obj_cur, 0);
}