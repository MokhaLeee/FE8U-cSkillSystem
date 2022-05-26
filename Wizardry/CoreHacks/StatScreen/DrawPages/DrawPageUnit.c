#include "gbafe.h"
#include "gbafe-chax.h"

typedef struct Unit Unit;


extern void DrawStatScreenBar(u16 BarId, u8 x, u8 y, s8 ValueBase, s8 ValueReal, s8 MaxValue); // 0x80870BC
extern void DrawUiSmallNumber(u16* a, int b, int c);
extern u16 gBmFrameTmap0[0x280];


static void DrawPage1_Texts();
static void DrawPage1_NumBar(struct Unit*);

// ORG 0x8087184
void DisplayPage0(void){
	struct Unit* unit = gStatScreen.unit;
	
	PrepareForMoreTextColor();
	DrawPage1_Texts();
	DrawPage1_NumBar(unit);
	
	// DisplayBwl();
}



// ==========================================
// =============== Internal =================
// ==========================================

static void DrawPage1_Texts(){
	
	struct Unit* unit = gStatScreen.unit;
	
	// Draw Text
	NewDrawTextInline(		// Str
		&gStatScreen.text[STATSCREEN_TEXT_POWLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 1),
		FACTION_BLUE == UNIT_FACTION(unit)
			? GetNewTextColorByGrowth( PowGrowthGetter(unit) )
			: TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4FE));
		
	NewDrawTextInline(		// Mag
		&gStatScreen.text[STATSCREEN_TEXT_AFFINLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 3),
		FACTION_BLUE == UNIT_FACTION(unit)
			? GetNewTextColorByGrowth( MagGrowthGetter(unit) )
			: TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4FF));
	
	NewDrawTextInline(		// Skl
		&gStatScreen.text[STATSCREEN_TEXT_SKLLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 5),
		FACTION_BLUE == UNIT_FACTION(unit)
			? GetNewTextColorByGrowth( SklGrowthGetter(unit) )
			: TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4EC));

	NewDrawTextInline(		// Spd
		&gStatScreen.text[STATSCREEN_TEXT_SPDLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 7),
		FACTION_BLUE == UNIT_FACTION(unit)
			? GetNewTextColorByGrowth( SpdGrowthGetter(unit) )
			: TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4ED));
		
	NewDrawTextInline(		// Def
		&gStatScreen.text[STATSCREEN_TEXT_DEFLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 9),
		FACTION_BLUE == UNIT_FACTION(unit)
			? GetNewTextColorByGrowth( DefGrowthGetter(unit) )
			: TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4EF));
		
	NewDrawTextInline(		// Res
		&gStatScreen.text[STATSCREEN_TEXT_RESLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(1, 11),
		FACTION_BLUE == UNIT_FACTION(unit)
			? GetNewTextColorByGrowth( ResGrowthGetter(unit) )
			: TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4F0));
		
	NewDrawTextInline(		// Lck
		&gStatScreen.text[STATSCREEN_TEXT_LCKLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 1),
		FACTION_BLUE == UNIT_FACTION(unit)
			? GetNewTextColorByGrowth( LckGrowthGetter(unit) )
			: TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4EE));
		
	// Below will not show for growth text
	ResetTextPalInfo();
	
	NewDrawTextInline(		// Mov
		&gStatScreen.text[STATSCREEN_TEXT_MOVLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 3),
		TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4F6));
		
	NewDrawTextInline(		// Con
		&gStatScreen.text[STATSCREEN_TEXT_CONLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 5),
		TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4F7));
	
	
	NewDrawTextInline(		// Aid
		&gStatScreen.text[STATSCREEN_TEXT_AIDLABEL],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 7),
		TEXT_COLOR_GOLD, 
		0, 0,
		GetStringFromIndex(0x4F8));
	
	NewDrawTextInline(		// Trv
		&gStatScreen.text[STATSCREEN_TEXT_RESCUENAME],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 9),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4F9));
	
	// displaying unit rescue name
	Text_InsertString(
		&gStatScreen.text[STATSCREEN_TEXT_RESCUENAME],
		24, TEXT_COLOR_BLUE,
		GetUnitRescueName(gStatScreen.unit));
	
	
	NewDrawTextInline(		// Status
		&gStatScreen.text[STATSCREEN_TEXT_STATUS],
		gBmFrameTmap0 + TILEMAP_INDEX(9, 11),
		TEXT_COLOR_GOLD, 0, 0,
		GetStringFromIndex(0x4FA));
	
	// displaying unit status name and turns

	if (GetUnitStatusIndex(gStatScreen.unit) != UNIT_STATUS_RECOVER)
	{
		// display name

		if (GetUnitStatusIndex(gStatScreen.unit) == UNIT_STATUS_NONE)
		{
			Text_InsertString(
				&gStatScreen.text[STATSCREEN_TEXT_STATUS],
				24, TEXT_COLOR_BLUE,
				GetUnitStatusName(gStatScreen.unit));
		}
		else
		{
			Text_InsertString(
				&gStatScreen.text[STATSCREEN_TEXT_STATUS],
                22, TEXT_COLOR_BLUE,
				GetUnitStatusName(gStatScreen.unit));
		}

		// display turns

		if( UNIT_STATUS_NONE != GetUnitStatusIndex(gStatScreen.unit) )
		{
			DrawUiSmallNumber(
				gBmFrameTmap0 + TILEMAP_INDEX(16, 11),
				0, 
				GetUnitStatusDura(gStatScreen.unit)
				);
		}
	}
	else
	{
		// I do not understand what this is for

		struct Unit tmp = *gStatScreen.unit;

		tmp.statusIndex = 0;

		if (GetUnitStatusIndex(gStatScreen.unit) == UNIT_STATUS_NONE)
		{
			Text_InsertString(
				&gStatScreen.text[STATSCREEN_TEXT_STATUS],
				24, TEXT_COLOR_BLUE,
				GetUnitStatusName(&tmp));
		}
		else
		{
			Text_InsertString(
				&gStatScreen.text[STATSCREEN_TEXT_STATUS],
				22, TEXT_COLOR_BLUE,
				GetUnitStatusName(&tmp));
		}
	}
}




static void DrawPage1_NumBar(Unit* unit){
	
	DrawStatScreenBar(0,5,1,	// Pow
		unit->pow,
		PowGetter(unit),
		unit->pClassData->maxPow );
	
	DrawStatScreenBar(1,5,3,	// Mag
		*GetMagAt(unit),
		MagGetter(unit),
		GetClassMagCap(unit->pClassData->number) );
	
	// displaying skl stat value
    DrawStatScreenBar(2, 5, 5,
        gStatScreen.unit->state & US_RESCUING
            ? gStatScreen.unit->skl/2
            : gStatScreen.unit->skl,
        SklGetter(gStatScreen.unit),
		gStatScreen.unit->state & US_RESCUING
			? UNIT_SKL_MAX(gStatScreen.unit)/2
			: UNIT_SKL_MAX(gStatScreen.unit));

    // displaying spd stat value
	DrawStatScreenBar(3, 5, 7,
		gStatScreen.unit->state & US_RESCUING
			? gStatScreen.unit->spd/2
			:gStatScreen.unit->spd,
		SpdGetter(gStatScreen.unit),
		gStatScreen.unit->state & US_RESCUING
			? UNIT_SPD_MAX(gStatScreen.unit)/2
			: UNIT_SPD_MAX(gStatScreen.unit));
	
	
	DrawStatScreenBar(4,5,9,	// Def
		unit->def,
		DefGetter(unit),
		unit->pClassData->maxDef );
	
	DrawStatScreenBar(5,5,11,	// Res
		unit->res,
		ResGetter(unit),
		unit->pClassData->maxRes );
	
	DrawStatScreenBar(6,13,1,	// Lck
		unit->lck,
		LckGetter(unit),
		30 );
	
	DrawStatScreenBar(7,13,3,	// Mov
		unit->pClassData->baseMov,
		MovGetter(unit),
		0xF );
	
	DrawStatScreenBar(9,13,5,	// Con
		unit->pClassData->baseCon + unit->pCharacterData->baseCon,
		ConGetter(unit),
		unit->pClassData->maxCon );
	
	// displaying unit aid
	DrawDecNumber(gBmFrameTmap0 + TILEMAP_INDEX(13, 7), TEXT_COLOR_BLUE,
		GetUnitAid(gStatScreen.unit));

    // displaying unit aid icon
    DrawIcon(gBmFrameTmap0 + TILEMAP_INDEX(14, 7),
        GetUnitAidIconId(UNIT_CATTRIBUTES(gStatScreen.unit)),
        TILEREF(0, STATSCREEN_BGPAL_EXTICONS));
}
