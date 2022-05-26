#include "gbafe-chax.h"


static void DisplayClassExp(int num, int x, int y, int wtype){
	
	extern void DrawSpecialUiChar(void *dest, int color, int);
	
	int wexp = GetWExp(gStatScreen.unit, wtype);
	
	int color = wexp >= WPN_EXP_S
		? TEXT_COLOR_GREEN
		: TEXT_COLOR_BLUE;
	
	// Display weapon type icon
	DrawIcon(gBmFrameTmap0 + TILEMAP_INDEX(x, y),
		GetWTypeMokhaIconIndex(wtype),
		TILEREF(0, STATSCREEN_BGPAL_ITEMICONS));


	// Display rank letter
	DrawSpecialUiChar(
		gBmFrameTmap0 + TILEMAP_INDEX(x + 4, y),
		color,
		GetDisplayRankStringFromExp(wexp < WPN_EXP_S ? WPN_EXP_A : WPN_EXP_S)
	);

	sub_8086B2C(
		0x401 + num*6, 
		5,
		gBmFrameTmap1 + TILEMAP_INDEX(x + 2, y + 1), 
		TILEREF(0, STATSCREEN_BGPAL_6),
		0x22, 
		_lib_div(wexp*34, WPN_EXP_S-1), 
		0);
}





void DisplayWeaponExp(int num, int x, int y, int wtype)
{
	extern void DrawSpecialUiChar(void *dest, int color, int);
	
	int progress, progressMax, color;

	int wexp = GetWExp(gStatScreen.unit, wtype);

	// Display weapon type icon
	DrawIcon(gBmFrameTmap0 + TILEMAP_INDEX(x, y),
		GetWTypeMokhaIconIndex(wtype),
		TILEREF(0, STATSCREEN_BGPAL_ITEMICONS));

	color = wexp >= WPN_EXP_S
		? TEXT_COLOR_GREEN
		: TEXT_COLOR_BLUE;

	// Display rank letter
	DrawSpecialUiChar(
		gBmFrameTmap0 + TILEMAP_INDEX(x + 4, y),
		color,
		GetDisplayRankStringFromExp(wexp)
	);

	GetWeaponExpProgressState(wexp, &progress, &progressMax);
	
	sub_8086B2C(
		0x401 + num*6, 
		5,
		gBmFrameTmap1 + TILEMAP_INDEX(x + 2, y + 1), 
		TILEREF(0, STATSCREEN_BGPAL_6),
		0x22, 
		_lib_div(progress*34, progressMax-1), 
		0);
}



void DisplayPage2(void)
{
	extern void DrawSkillPage(void);
	
	DisplayWeaponExp(0, 0x01, 0x01, ITYPE_SWORD);
	DisplayWeaponExp(1, 0x01, 0x03, ITYPE_LANCE);
	DisplayWeaponExp(2, 0x01, 0x05, ITYPE_AXE);
	DisplayWeaponExp(3, 0x01, 0x07, ITYPE_BOW);
	DisplayWeaponExp(4, 0x01, 0x09, ITYPE_BMAG);
	
	DisplayWeaponExp(5, 0x09, 0x01, ITYPE_WMAG);
	DisplayWeaponExp(6, 0x09, 0x03, ITYPE_RIDE);
	DisplayWeaponExp(7, 0x09, 0x05, ITYPE_FLY);
	DisplayWeaponExp(8, 0x09, 0x07, ITYPE_HEAVY);
	DisplayClassExp(9, 0x09, 0x09, ITYPE_CLASS);
	
	// DisplaySupportList();
	
	DrawSkillPage();
}
