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
	
	if( NULL == panel )
		return;
	
	// no arrow!
	panel->_unk64 = 0;
	
	
	Text_Clear(&panel->text[0]);
	Text_Clear(&panel->text[1]);
	Text_Clear(&panel->text[2]);
	
	
	// (int x, int y, int w, int h, int style)
	DrawUiFrame2( panel->xPos, panel->yPos, 0xE, 0x8, 0 );
	
	
	// Draw
	// Text_InsertString(struct TextHandle*, int xPos, int color, const char*)
	// "Attack Def or Res"
	if( 1 == info->is_magic )
		Text_InsertString(
			&panel->text[0],
			0x1C,
			TEXT_COLOR_GREEN,
			GetStringFromIndex(ENUM_msg_CA_MagAtk) );
	else
		Text_InsertString(
			&panel->text[0],
			0x1C,
			TEXT_COLOR_NORMAL,
			GetStringFromIndex(ENUM_msg_CA_PhyAtk) );
	
	
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
		color = TEXT_COLOR_NORMAL;
	
	
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
		color = TEXT_COLOR_NORMAL;
	
	Text_InsertNumberOr2Dashes(
		&panel->text[2],
		0x24,
		color,
		gBattleActor.battleHitRate );
	
	
	// Bu.Crit
	if( gBattleActor.battleCritRate > 0 )
		color = TEXT_COLOR_GREEN;
	else
		color = TEXT_COLOR_NORMAL;
	
	Text_InsertNumberOr2Dashes(
		&panel->text[1],
		0x54,
		color,
		gBattleActor.battleCritRate );
	
	
	// Bu.Avoid
	if( gBattleActor.battleAvoidRate > 0 )
		color = TEXT_COLOR_GREEN;
	else
		color = TEXT_COLOR_NORMAL;
	
	Text_InsertNumberOr2Dashes(
		&panel->text[2],
		0x54,
		color,
		gBattleActor.battleAvoidRate );
		
	
	
	// Text_Display(struct TextHandle*, u16* bgMap)
	Text_Draw(
		&panel->text[0],
		TILEMAP_LOCATED(gBG0TilemapBuffer, panel->xPos+1, panel->yPos+1) );
	
	Text_Draw(
		&panel->text[1],
		TILEMAP_LOCATED(gBG0TilemapBuffer, panel->xPos+1, panel->yPos+3) );
	
	Text_Draw(
		&panel->text[2],
		TILEMAP_LOCATED(gBG0TilemapBuffer, panel->xPos+1, panel->yPos+5) );
		
	
	// End
	BG_EnableSyncByMask(0b01);
	
}