#include "gbafe-chax.h"
#include "PrepSkill.h"


void PrepSkill_DrawWindowGfx(void){
	
	// 0x809A874
	extern u16 Gfx_PrepSkillScreen[]; // gfx
	extern u16 Gfx_PrepSkillScreen2[]; // gfx2
	extern u16 Pal_PrepSkillScreen[]; // pal
	extern u16 Tsa_PrepSkillScreen[]; // tsa
	
	ResetIconGraphics_();
	LoadUiFrameGraphics();
	LoadObjUIGfx();
	
	LoadIconPalettes(4); // item icon
	
	CopyDataWithPossibleUncomp(Gfx_PrepSkillScreen2, (void*)0x06006000);
	CopyDataWithPossibleUncomp(Gfx_PrepSkillScreen, (void*)0x06000440);
	
	CopyDataWithPossibleUncomp(Tsa_PrepSkillScreen, gGenericBuffer);
	CallARM_FillTileRect(gBG1TilemapBuffer, gGenericBuffer, 0x1000);
	
	CopyToPaletteBuffer(Pal_PrepSkillScreen, 0x1E0, 0x20);
	CopyToPaletteBuffer(Pal_PrepSkillScreen, 0x320, 0x20);
	EnablePaletteSync();
	
}




void PrepSkill_DrawPickTotalBar(struct Unit* unit, int config){
	
	// 0x809AAF1
	// config: 0->init, 1->update
	
	if( ON_DRAW_CONFIG_INIT == config )
	{
		Text_Clear(&gStatScreen.text[0]);
		Text_Clear(&gStatScreen.text[1]);
		
		DrawTextInline(
			&gStatScreen.text[0],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xE, 0x1),
			TEXT_COLOR_NORMAL, 0, 0,
			"Pick" );
		
		DrawTextInline(
			&gStatScreen.text[1],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0x14, 0x1),
			TEXT_COLOR_NORMAL, 0, 0,
			"Total Skill" );
		
	} // if config
	
	
	// W.I.P.
	// Draw Numbers
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x12, 0x1),
		1, 1, 0 );
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1B, 0x1),
		1, 1, 0 );
	
	DrawDecNumber(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x12, 0x1),
		TEXT_COLOR_BLUE,
		unit->index );
	
	DrawDecNumber(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1B, 0x1),
		TEXT_COLOR_BLUE,
		unit->index );
		
	
	// On End
	BG_EnableSyncByMask(0b01);
}


void PrepSkill_DrawLeftSkillsIcon(struct Unit* unit, int config){
	
	struct PrepSkillsList* list;
	
	if( ON_DRAW_CONFIG_INIT == config )
	{
		// Clear TextHandle
		Text_Clear( &gPrepUnitTexts[0xE] );
		Text_Clear( &gPrepUnitTexts[0xF] );
		Text_Clear( &gPrepUnitTexts[0x10] );
		
		
		// TileMap_FillRect(u16 *dest, int width, int height, int fillValue)
		TileMap_FillRect(
			TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 5),
			0xB, 0x2, 0);
		
		TileMap_FillRect(
			TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 9),
			0xB, 0x2, 0);
			
		TileMap_FillRect(
			TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 0xF),
			0xB, 0x2, 0);
		
		TileMap_FillRect(
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xF, 0x11),
			0x6, 0x2, 0);
		
		// Draw Text
		DrawTextInline(
			&gPrepUnitTexts[0xE],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 5),
			TEXT_COLOR_GOLD,
			0, 0, 
			"Equippable Skills");
	
		DrawTextInline(
			&gPrepUnitTexts[0xF],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 9),
			TEXT_COLOR_GOLD,
			0, 0, 
			"Class & Unit Skills");
		
		DrawTextInline(
			&gPrepUnitTexts[0x10],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 0xF),
			TEXT_COLOR_GOLD,
			0, 0, 
			"Combat Arts");
		
	} // ON_DRAW_CONFIG_INIT
	
	
	// Clear Icons
	ResetIconGraphics_();
	
	
	// Clear Text
	Text_Clear( &gPrepUnitTexts[0x12] );
	
	
	// Clear Screen
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 7),
		0xB, 0x1, 0);
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 11),
		0xB, 0x3, 0);
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 17),
		0xB, 0x1, 0);
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x16, 0x11),
		0x2, 0x1, 0);
	
	
	
	list = GetUnitPrepSkillsList(unit);
	
	// RAM Skills
	if( 0 == list->total[PREP_SKLSUB_LEFT_RAM] )
		DrawTextInline(
			&gPrepUnitTexts[0x12],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 2, 7),
			TEXT_COLOR_GRAY,
			0, 0, 
			"None");
	else
		for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_RAM]; i++ )
			DrawIcon(
				TILEMAP_LOCATED( gBG0TilemapBuffer, 2 + i * 2, 7 ),
				SKILL_ICON(list->skills_ram[i]), 
				TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	
	
	// ROM Skills
	if( 0 == list->total[PREP_SKLSUB_LEFT_ROM] )
		DrawTextInline(
			&gPrepUnitTexts[0x12],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 2, 11),
			TEXT_COLOR_GRAY,
			0, 0, 
			"None");
	else
		for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_ROM]; i++ )
			DrawIcon(
				TILEMAP_LOCATED( gBG0TilemapBuffer, 2 + i * 2, 11 ),
				SKILL_ICON(list->skills_rom[i]), 
				TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	
	// Combat Arts
	// W.I.P.
	if( 0 == list->total[PREP_SKLSUB_LEFT_CA] )
		DrawTextInline(
			&gPrepUnitTexts[0x12],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 2, 17),
			TEXT_COLOR_GRAY,
			0, 0, 
			"None");
	else
		for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_CA]; i++ )
			DrawIcon(
				TILEMAP_LOCATED( gBG0TilemapBuffer, 2 + i * 2, 17 ),
				MASTERY_ICON(list->skills_CombatArt[i]), 
				TILEREF(0, STATSCREEN_BGPAL_EXTICONS) );
	


	
}


void PrepSkill_DrawBattalionBar(struct Unit* unit, int config){
	
	if( ON_DRAW_CONFIG_INIT == config )
	{
		// Clear TextHandle
		Text_Clear( &gPrepUnitTexts[0x11] );
		
		
		// TileMap_FillRect(u16 *dest, int width, int height, int fillValue)
		TileMap_FillRect(
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xF, 0x11),
			0x6, 0x2, 0);
		
		// Draw Text
		DrawTextInline(
			&gPrepUnitTexts[0x11],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xF, 0x11),
			TEXT_COLOR_GOLD,
			0, 0, 
			"Battalion");
		
	} // ON_DRAW_CONFIG_INIT
	
	
	// Clear Icons
	// ResetIconGraphics_();
	
	
	
	// Battalion
	DrawIcon(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x16, 0x11 ),
		MASTERY_ICON(MASTERY_ICON_REASON), 
		TILEREF(0, STATSCREEN_BGPAL_EXTICONS) );
	
}











// 0x809AD91
int ShouldPrepUnitMenuScroll(struct Proc_PrepUnit* proc){
	
	/*
	yDiff_cur / 0x10	-> 	当前列表最上层的line
	list_num_cur 		->	鼠标指代的当前列表序号
	*/
	
	
	int line = proc->yDiff_cur / 0x10;
	int handLine = proc->list_num_cur / 2;
	int maxLine = GetPrepScreenUnitListSize() / 2;
	
	// Judge up
	// 1. handLine 位于 line 之上
	// 2. line 并非 line 0
	if( handLine < line )
		if( line > 0 )
			return 1;

	// Judge down
	// 1. handLine已经达到line+5
	// 2. handLine 并非最后一行
	if( handLine > (line + 4) )
		if( handLine < maxLine )
			return 1;
	
	return 0;

	
	
}







// 0x809A581
void PrepUnit_DrawUnitListNames(struct Proc_PrepUnit* proc, int line){
	
	extern int IsCharacterForceDeployed(int char_id);
	
	int list_index, text_index, newLine;
	struct Unit* unit;
	
	// it use 14 TextHandle to store 6 line of 12 Units;
	// then put them on BG2
	// then handle the bg-offset!
	
	// newLine = line % 7;
	
	newLine = line;
	
	while(newLine > 6)
		newLine = newLine - 7;
	
	
	// just add 2 units' name
	for( int i = 0; i < 2; i++ )
	{
		text_index = newLine * 2 + i;
		list_index = line * 2 + i;
		
		if( list_index >= GetPrepScreenUnitListSize() )
			continue;
		
		unit = GetPrepScreenUnitListEntry(list_index);
		
		
		Text_Clear( &gPrepUnitTexts[text_index] );
		
		DrawTextInline(
			&gPrepUnitTexts[text_index],
			TILEMAP_LOCATED( gBG2TilemapBuffer, 0x10 + i * 7 , line * 2 ),
			0 == (unit->state & US_NOT_DEPLOYED)
				? TEXT_COLOR_NORMAL
				: TEXT_COLOR_GRAY,
			0, 0,
			GetStringFromIndex(unit->pCharacterData->nameTextId) );
		
	} // for
	
	BG_EnableSyncByMask(0b100);
}






