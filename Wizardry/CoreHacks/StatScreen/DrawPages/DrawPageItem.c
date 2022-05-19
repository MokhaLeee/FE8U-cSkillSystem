#include "gbafe-chax.h"

void DisplayTexts(const struct SSTextDispInfo* infos);

static const unsigned Mid_Silencer = ENUM_msg_Silencer;
static const unsigned Mid_Rng = 0x500; // Rng
static const unsigned Mid_Atk = 0x4F3; // Atk
static const unsigned Mid_Hit = 0x4F4; // Hit
static const unsigned Mid_Crt = 0x501; // Crit
static const unsigned Mid_Avo = 0x4F5; // Avoid

struct SSTextDispInfo const sNewPage1TextInfo[] ={
	
	// New "Silencer"
	{ 
		gStatScreen.text + STATSCREEN_TEXT_BWL, 
		gBmFrameTmap0 + TILEMAP_INDEX(2, 11), 
		TEXT_COLOR_GOLD, 
		6, 
		&Mid_Silencer
	},
	
	{ 
		gStatScreen.text + STATSCREEN_TEXT_BSATKLABEL, 
		gBmFrameTmap0 + TILEMAP_INDEX(2, 13), 
		TEXT_COLOR_GOLD, 
		6, 
		&Mid_Atk 
	},
	
	{ 
		gStatScreen.text + STATSCREEN_TEXT_BSHITLABEL, 
		gBmFrameTmap0 + TILEMAP_INDEX(2, 15), 
		TEXT_COLOR_GOLD, 
		6, 
		&Mid_Hit 
	},
	
	{ 
		gStatScreen.text + STATSCREEN_TEXT_BSRANGE,    
		gBmFrameTmap0 + TILEMAP_INDEX(9, 11), 
		TEXT_COLOR_GOLD, 
		6, 
		&Mid_Rng 
	},
	
	{ 
		gStatScreen.text + STATSCREEN_TEXT_BSCRTLABEL, 
		gBmFrameTmap0 + TILEMAP_INDEX(9, 13), 
		TEXT_COLOR_GOLD, 
		5, 
		&Mid_Crt 
	},
	
	{ 
		gStatScreen.text + STATSCREEN_TEXT_BSAVOLABEL, 
		gBmFrameTmap0 + TILEMAP_INDEX(9, 15), 
		TEXT_COLOR_GOLD, 
		6, 
		&Mid_Avo 
	},

	{ }, // end
}; 


void DisplayPage1(void)
{
	extern const u16 Page2SubWindow[];
	
	int i, item;
	const char* str;
	
	// Set BWL Table as Text "Silencer"
	Text_Clear(gStatScreen.text + STATSCREEN_TEXT_BWL);
	
	CopyDataWithPossibleUncomp(
		Page2SubWindow,
		gGenericBuffer);
	
	CallARM_FillTileRect(
		gBmFrameTmap1 + TILEMAP_INDEX(1, 11),
		gGenericBuffer, TILEREF(0x40, STATSCREEN_BGPAL_3));

	DisplayTexts(sNewPage1TextInfo);

	if (!UNIT_IS_GORGON_EGG(gStatScreen.unit))
	{
		for (i = 0; (i < UNIT_ITEM_COUNT) && (item = gStatScreen.unit->items[i]); ++i)
		{
			int color;

			if ((gStatScreen.unit->state & US_DROP_ITEM) && (i == GetUnitItemCount(gStatScreen.unit) - 1))
				color = TEXT_COLOR_GREEN;
			else
				color = IsItemDisplayUsable(gStatScreen.unit, item)
					? TEXT_COLOR_NORMAL
					: TEXT_COLOR_GRAY;

			DrawItemStatScreenLine(
				&gStatScreen.text[STATSCREEN_TEXT_ITEM0 + i],
				item, color,
				gBmFrameTmap0 + TILEMAP_INDEX(1, 1 + i*2));
		}
	}

	i = GetUnitEquippedWeaponSlot(gStatScreen.unit);
	item = 0;

	if (gStatScreen.unit->pClassData->number != CLASS_GORGONEGG)
	{
		if ((gStatScreen.unit->pClassData->number != CLASS_GORGONEGG2) && (i >= 0))
		{
			sub_8004B0C(
				gBmFrameTmap0 + TILEMAP_INDEX(16, 1 + i*2),
				0, 0x35);

			CallARM_FillTileRect(
				gBmFrameTmap1 + TILEMAP_INDEX(1, 2 + i*2),
				gUnknown_08A02250, TILEREF(0x40, STATSCREEN_BGPAL_3));

			item = gStatScreen.unit->items[i];
		}
	}

	if (!UNIT_IS_GORGON_EGG(gStatScreen.unit))
	{
		// for Silencer
		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(8,  11),
			TEXT_COLOR_BLUE, gBattleActor.battleSilencerRate);
		
		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(8,  13),
			TEXT_COLOR_BLUE, gBattleActor.battleAttack);

		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(8,  15),
			TEXT_COLOR_BLUE, gBattleActor.battleHitRate);

		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(15, 13),
			TEXT_COLOR_BLUE, gBattleActor.battleCritRate);

		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(15, 15),
			TEXT_COLOR_BLUE, gBattleActor.battleAvoidRate);
	}
	else
	{
		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(8,  13),
			TEXT_COLOR_BLUE, 0xFF);

		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(8,  15),
			TEXT_COLOR_BLUE, 0xFF);

		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(15, 13),
			TEXT_COLOR_BLUE, 0xFF);

		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(15, 15),
			TEXT_COLOR_BLUE, gBattleActor.battleAvoidRate);

		item = 0;
	}

    // TODO: macro, maybe?

	str = _GetUnitRangeString(&gBattleActor.unit);
	
	if( '\0' != *str )
		Text_InsertString(
			&gStatScreen.text[STATSCREEN_TEXT_BSRANGE],
			55 - GetStringTextWidth(str),
			TEXT_COLOR_BLUE, str);
	else
		DrawDecNumber(
			gBmFrameTmap0 + TILEMAP_INDEX(15, 11),
			TEXT_COLOR_BLUE, 0xFF);
	
	// null the gfx: "Equipment"
/* 	for (i = 0; i < 8; ++i)
	{
		gBmFrameTmap0[TILEMAP_INDEX(1 + i, 11)] = TILEREF(0x60 + i, STATSCREEN_BGPAL_7);
		gBmFrameTmap0[TILEMAP_INDEX(1 + i, 12)] = TILEREF(0x68 + i, STATSCREEN_BGPAL_7);
	} */
}