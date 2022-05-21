#include "gbafe-chax.h"

static void MenuPanel_DrawCombatArt(const struct CombatArtInfo*);


void StartMenuPanel_CombatArt(struct MenuProc* menu, struct Unit* unit, u8 xPos, u8 yPos){
	ForceMenuItemPanel(menu, unit, xPos, yPos);
	
	
	gBattleActor.battleAttack = 0;
	gBattleActor.battleCritRate = 0;
	gBattleActor.battleHitRate = 0;
	gBattleActor.battleAvoidRate =0;
	
	gBattleTarget.battleAttack = 0;
	gBattleTarget.battleCritRate = 0;
	gBattleTarget.battleHitRate = 0;
	gBattleTarget.battleAvoidRate = 0;
	
	return;
}


void UpdateMenuPanel_CombatArt(const struct CombatArtInfo* info){	

	gBattleActor.battleAttack = info->mt;
	gBattleActor.battleHitRate = info->hit;
	gBattleActor.battleAvoidRate =info->avo;
	gBattleActor.battleCritRate = info->crit;
	
	MenuPanel_DrawCombatArt(info);
	return;
}


void EndMenuPanel_CombatArt(void){
	Proc_EndEach(gProc_MenuItemPanel);
}



void MenuPanel_DrawCombatArt(const struct CombatArtInfo* info){
	
	u8 color;
	struct PanelProc* panel = Proc_Find(gProc_MenuItemPanel);
	
	const int xPos = panel->xPos;
	const int yPos = panel->yPos;
	
	if( NULL == panel )
		return;
	
	// no arrow!
	panel->_unk64 = 0;
	
	
	Text_Clear(&panel->text[0]);
	Text_Clear(&panel->text[1]);
	Text_Clear(&panel->text[2]);
	
	
	// (int x, int y, int w, int h, int style)
	DrawUiFrame2( xPos, yPos, 0xE, 0x8, 0 );
	
	
	// Draw
	// Text_InsertString(struct TextHandle*, int xPos, int color, const char*)
	
	
	// "Afin"
	Text_InsertString(
		&panel->text[0],
		0x2,
		TEXT_COLOR_NORMAL,
		GetStringFromIndex(0x4F1) );
	
	if( 1 == info->is_magic )
		Text_InsertString(
			&panel->text[0],
			0x1A,
			TEXT_COLOR_GREEN,
			GetStringFromIndex(ENUM_msg_PrepPickSkill_Mag) );
	else
		Text_InsertString(
			&panel->text[0],
			0x1A,
			TEXT_COLOR_BLUE,
			GetStringFromIndex(ENUM_msg_PrepPickSkill_Phys) );
	
	
	// "Eff"
	Text_InsertString(
		&panel->text[0],
		0x32,
		TEXT_COLOR_NORMAL,
		GetStringFromIndex(ENUM_msg_PrepPickSkill_Eff) );
	
	if( !(info->eff_heavy | info->eff_ride | info->eff_dragon) )
		Text_InsertString(
			&panel->text[0],
			0x52,
			TEXT_COLOR_GRAY,
			GetStringFromIndex(ENUM_msg_PrepPickSkill_None) );
	
	Text_Draw(
		&panel->text[0],
		TILEMAP_LOCATED(gBG0TilemapBuffer, xPos + 1, yPos + 1) );
	
	// Draw Eff Icon
	if( info->eff_all )
		DrawIcon(
			TILEMAP_LOCATED( gBG0TilemapBuffer, xPos + 11, yPos + 1),
			MASTERY_ICON(MASTERY_ICON_STAR), 
			TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	else if( info->eff_heavy )
		DrawIcon(
			TILEMAP_LOCATED( gBG0TilemapBuffer, xPos + 11, yPos + 1),
			MASTERY_ICON(MASTERY_ICON_HEAVY), 
			TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	else if( info->eff_ride )
		DrawIcon(
			TILEMAP_LOCATED( gBG0TilemapBuffer, xPos + 11, yPos + 1),
			MASTERY_ICON(MASTERY_ICON_RIDE), 
			TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	else if( info->eff_dragon )
		DrawIcon(
			TILEMAP_LOCATED( gBG0TilemapBuffer, xPos + 11, yPos + 1),
			MASTERY_ICON(MASTERY_ICON_DRAGON), 
			TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	else if( info->eff_monster )
		DrawIcon(
			TILEMAP_LOCATED( gBG0TilemapBuffer, xPos + 11, yPos + 1),
			MASTERY_ICON(MASTERY_ICON_MONSTER), 
			TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	else if( info->eff_fly )
		DrawIcon(
			TILEMAP_LOCATED( gBG0TilemapBuffer, xPos + 11, yPos + 1),
			MASTERY_ICON(MASTERY_ICON_FLY), 
			TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
		
			
	
	
	
	// "Mt"
	Text_InsertString(
		&panel->text[1],
		0x2,
		TEXT_COLOR_NORMAL,
		GetStringFromIndex(0x503) );
	
	// "Hit"
	Text_InsertString(
		&panel->text[2],
		0x2,
		TEXT_COLOR_NORMAL,
		GetStringFromIndex(0x4F4) );
	
	// "Crit"
	Text_InsertString(
		&panel->text[1],
		0x32,
		TEXT_COLOR_NORMAL,
		GetStringFromIndex(0x501) );
	
	// "Avoid"
	Text_InsertString(
		&panel->text[2],
		0x32,
		TEXT_COLOR_NORMAL,
		GetStringFromIndex(0x4F5) );
		
	
	// judge for color
	if( gBattleActor.battleAttack > 0 )
		color = TEXT_COLOR_GREEN;
	else
		color = TEXT_COLOR_BLUE;
	
	
	// Bu.Atk
	Text_InsertNumberOr2Dashes(
		&panel->text[1],
		0x24,
		color,
		gBattleActor.battleAttack );
	
	
	// Bu.Hit
	if( gBattleActor.battleHitRate > 0 )
		color = TEXT_COLOR_GREEN;
	else
		color = TEXT_COLOR_BLUE;
	
	Text_InsertNumberOr2Dashes(
		&panel->text[2],
		0x24,
		color,
		gBattleActor.battleHitRate );
	
	
	// Bu.Crit
	if( gBattleActor.battleCritRate > 0 )
		color = TEXT_COLOR_GREEN;
	else
		color = TEXT_COLOR_BLUE;
	
	Text_InsertNumberOr2Dashes(
		&panel->text[1],
		0x54,
		color,
		gBattleActor.battleCritRate );
	
	
	// Bu.Avoid
	if( gBattleActor.battleAvoidRate > 0 )
		color = TEXT_COLOR_GREEN;
	else
		color = TEXT_COLOR_BLUE;
	
	Text_InsertNumberOr2Dashes(
		&panel->text[2],
		0x54,
		color,
		gBattleActor.battleAvoidRate );
		
	
	
	// Text_Display(struct TextHandle*, u16* bgMap)
	
	Text_Draw(
		&panel->text[1],
		TILEMAP_LOCATED(gBG0TilemapBuffer, xPos + 1, yPos + 3) );
	
	Text_Draw(
		&panel->text[2],
		TILEMAP_LOCATED(gBG0TilemapBuffer, xPos + 1, yPos + 5) );
		
	
	// End
	BG_EnableSyncByMask(0b01);
	
}