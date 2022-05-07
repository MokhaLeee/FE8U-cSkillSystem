#include "gbafe-chax.h"

static u16* const TM_PAGEFRAME = (u16*) 0x02003D2C;

void DrawSkillPage(void) {
	
	static const int X = 1;
	static const int Y = 15;
	
	struct TextHandle* text = &gStatScreen.text[STATSCREEN_TEXT_BWL];
	struct Unit* unit = gStatScreen.unit;
	struct SkillFastTesterList* list = GetOrMakeSklFastList(unit);
	
	Text_Clear(text);
	Text_SetColorId(text, TEXT_COLOR_GOLD);
	Text_AppendString(text, GetStringFromIndex(ENUM_msg_PrepSkillMenu_PickSkillName) );
	
	
	if ( list->cnt == 0 ) {
		
		Text_SetColorId(text, TEXT_COLOR_GRAY);
		Text_SetXCursor(text, 32);
		Text_AppendString(text, GetStringFromIndex(ENUM_msg_PrepPickSkill_None) );
		Text_Draw(text, TM_PAGEFRAME + TILEMAP_INDEX(X, Y));
		return;
	
	} // if
	
	
	Text_Draw(text, TM_PAGEFRAME + TILEMAP_INDEX(X, Y));
	
	for( int i = 0; i < list->cnt; i++ ) 
	{
		DrawIcon(
			TM_PAGEFRAME + TILEMAP_INDEX(X + 3 + 2*i, Y), 
			SKILL_ICON(list->skills[i]), 
			TILEREF(0, STATSCREEN_BGPAL_ITEMICONS)
		);
		
		if( i > 5 )
			break;
	}
}

