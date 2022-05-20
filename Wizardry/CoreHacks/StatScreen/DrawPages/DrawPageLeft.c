
#include "gbafe-chax.h"

typedef struct Unit Unit;
extern int GetStringTextCenteredPos(int x, const char* str);
extern void DrawSpecialUiChar(u16* out, int color, int chr);

// ORG 0x8086E44
void DisplayLeftPanel(void){
	Unit* unit = gStatScreen.unit;
	const char* namestr = GetStringFromIndex(unit->pCharacterData->nameTextId);
	unsigned namexoff = GetStringTextCenteredPos(0x30, namestr);
	
	// On init
	BG_Fill(gBG0TilemapBuffer,0);
	
	// Generate battle stats for unit for display later
	BattleGenerateUiStats(
		unit, 
		GetUnitEquippedWeaponSlot(unit)
		);
	
	
	// Display character name
	DrawTextInline(
		&gStatScreen.text[STATSCREEN_TEXT_CHARANAME],
		gBG0TilemapBuffer + TILEMAP_INDEX(3, 10),
		TEXT_COLOR_NORMAL,
		namexoff,
		0,
		namestr);
	
	// Display class name
	DrawTextInline(
		&gStatScreen.text[STATSCREEN_TEXT_CLASSNAME],
		gBG0TilemapBuffer + TILEMAP_INDEX(1, 13),
        TEXT_COLOR_NORMAL, 
		0, 0,
        GetStringFromIndex(gStatScreen.unit->pClassData->nameTextId) );

	
	// "LV"+"E"
	DrawSpecialUiChar(	// "L"
		gBG0TilemapBuffer + TILEMAP_INDEX(1, 15),
		TEXT_COLOR_GOLD,
		0x24);
		
	DrawSpecialUiChar(	// "V"
		gBG0TilemapBuffer + TILEMAP_INDEX(2, 15),
		TEXT_COLOR_GOLD,
		0x25);
		
	DrawSpecialUiChar(	// "E"
		gBG0TilemapBuffer + TILEMAP_INDEX(5, 15),
		TEXT_COLOR_GOLD,
		0x1D);		
	
	
	// "HP"+"/"
	DrawSpecialUiChar(	// "H"
		gBG0TilemapBuffer + TILEMAP_INDEX(1, 17),
		TEXT_COLOR_GOLD,
		0x22);
	
	DrawSpecialUiChar(	// "P"
		gBG0TilemapBuffer + TILEMAP_INDEX(2, 17),
		TEXT_COLOR_GOLD,
		0x23);
		
	DrawSpecialUiChar(	// "P"
		gBG0TilemapBuffer + TILEMAP_INDEX(5, 17),
		TEXT_COLOR_GOLD,
		0x16);
	
	// level + exp
	DrawDecNumber(	// Unit.level
		gBG0TilemapBuffer + TILEMAP_INDEX(4, 15),
		TEXT_COLOR_BLUE,
		unit->level);
	
	DrawDecNumber(	// // Unit.exp
		gBG0TilemapBuffer + TILEMAP_INDEX(7, 15),
		TEXT_COLOR_BLUE,
		unit->exp);	
	
	// Hp Cur+Max
	s8 sHpCur = GetUnitCurrentHp(unit);
	if( sHpCur<99 )
		DrawDecNumber(
			gBG0TilemapBuffer + TILEMAP_INDEX(4, 17),
			TEXT_COLOR_BLUE,
			sHpCur);
	else
	{
		DrawSpecialUiChar(
			gBG0TilemapBuffer + TILEMAP_INDEX(3, 17),
			TEXT_COLOR_BLUE,
			0x14);
			
		DrawSpecialUiChar(
			gBG0TilemapBuffer + TILEMAP_INDEX(4, 17),
			TEXT_COLOR_BLUE,
			0x14);
	}
	
	s8 sHpMax = GetUnitMaxHp(unit);
	if( sHpMax<99 )
		DrawDecNumber(
			gBG0TilemapBuffer + TILEMAP_INDEX(7, 17),
			TEXT_COLOR_BLUE,
			sHpMax);
	else
	{
		DrawSpecialUiChar(
			gBG0TilemapBuffer + TILEMAP_INDEX(6, 17),
			TEXT_COLOR_BLUE,
			0x14);
			
		DrawSpecialUiChar(
			gBG0TilemapBuffer + TILEMAP_INDEX(7, 17),
			TEXT_COLOR_BLUE,
			0x14);
	}

	/*=========================================================
	  ==========================  More ========================
	  ========================================================= */
	// display affininity icon
    DrawIcon(
		gBG0TilemapBuffer + TILEMAP_INDEX(9, 10),
		GetUnitAffinityIcon(unit),
		TILEREF(0, STATSCREEN_BGPAL_EXTICONS));
	
	return;
}



