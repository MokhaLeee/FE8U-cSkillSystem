#include "gbafe-chax.h"

static u16* const TM_PAGEFRAME = (u16*) 0x02003D2C;

void DrawSkillPage(void) {
	
	static const int X = 1;
	static const int Y = 12;
	
	struct TextHandle* text;
	struct Unit* unit = gStatScreen.unit;
	
	// Skills
	
	text = &gStatScreen.text[STATSCREEN_TEXT_BWL];
	Text_Clear(text);
	Text_SetColorId(text, TEXT_COLOR_GOLD);
	Text_AppendString(text, GetStringFromIndex(ENUM_msg_PrepSkillMenu_PickSkillName) );
	
	struct SkillFastTesterList* list = GetOrMakeSklFastList(unit);
	
	if ( list->cnt == 0 ) {
		
		Text_SetColorId(text, TEXT_COLOR_GRAY);
		Text_SetXCursor(text, 32);
		Text_AppendString(text, GetStringFromIndex(ENUM_msg_PrepPickSkill_None) );
		Text_Draw(text, TM_PAGEFRAME + TILEMAP_INDEX(X, Y));
	
	}
	else{
		Text_Draw(text, TM_PAGEFRAME + TILEMAP_INDEX(X, Y));
	
		for( int i = 0; i < list->cnt; i++ ) {
			DrawIcon(
				TM_PAGEFRAME + TILEMAP_INDEX(
					X + 2 * _lib_mod(i, 5) + 3, 
					Y + 2 * _lib_div(i, 5) ), 
				SKILL_ICON(list->skills[i]), 
				TILEREF(0, STATSCREEN_BGPAL_ITEMICONS)
			);
		}
	}
	
	
	
	
	
	
	// Combat Arts
	
	text = &gStatScreen.text[STATSCREEN_TEXT_SUPPORT0];
	Text_Clear(text);
	Text_SetColorId(text, TEXT_COLOR_GOLD);
	Text_AppendString(text, GetStringFromIndex(ENUM_msg_mssCAname) );
	
	u8* arts_list = GetCombatArtList(unit);
	
	if( !UnitHasCombatArt(unit) ){
		
		Text_SetColorId(text, TEXT_COLOR_GRAY);
		Text_SetXCursor(text, 32);
		Text_AppendString(text, GetStringFromIndex(ENUM_msg_PrepPickSkill_None) );
		Text_Draw(text, TM_PAGEFRAME + TILEMAP_INDEX(X, Y + 4));
	
	}
	else{
		Text_Draw(text, TM_PAGEFRAME + TILEMAP_INDEX(X, Y + 4));
		
		int count = 0;
		
		for( int i = 0; i < 5; i++ ) {
			
			if( !SKILL_VALID(arts_list[i]) )
				continue;
			
			DrawIcon(
				TM_PAGEFRAME + TILEMAP_INDEX(X + 3 + 2 * count, Y + 4), 
				COMBAT_ART_ICON(arts_list[i]), 
				TILEREF(0, STATSCREEN_BGPAL_ITEMICONS)
			);
			
			count++;
		}
	}
	
}

