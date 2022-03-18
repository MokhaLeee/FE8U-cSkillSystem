#include "gbafe.h"
#include "common.h"
#include "level-up.h"
#include "level-up-rework.h"
#include "str-mag.h"

extern struct BattleUnit* gpUnitLeft_BattleStruct[];
extern struct BattleUnit* gpUnitRight_BattleStruct[];

// stat name tables
#define BU_PRE (*gpSomeBuStruct)
#define BU_AFT (*gpSomeUnitStruct2)

static struct BattleUnit** gpSomeBuStruct = (struct BattleUnit**)0x2020108;
static struct BattleUnit** gpSomeUnitStruct2 = (struct BattleUnit**)0x202010C;

extern const u16 LU_PosTable[];
extern const u16 LU_NameTable[];




static void EkrPutText_SetStatusNonePromo(void){
	gLevelUpStatsBase.stat_up[LU_HP]  = BU_PRE->changeHP;
	gLevelUpStatsBase.stat_up[LU_STR] = BU_PRE->changePow;
	gLevelUpStatsBase.stat_up[LU_MAG] = *GetBu_ChangeMagAt(BU_PRE);
	gLevelUpStatsBase.stat_up[LU_SKL] = BU_PRE->changeSkl;
	gLevelUpStatsBase.stat_up[LU_SPD] = BU_PRE->changeSpd;
	
	gLevelUpStatsBase.stat_up[LU_LCK] = BU_PRE->changeLck;
	gLevelUpStatsBase.stat_up[LU_DEF] = BU_PRE->changeDef;
	gLevelUpStatsBase.stat_up[LU_RES] = BU_PRE->changeRes;
	gLevelUpStatsBase.stat_up[LU_CON] = 0;
	gLevelUpStatsBase.stat_up[LU_MOV] = 0;
}



static void EkrPutText_SetStatusPromo(void)
{
	gLevelUpStatsBase.stat_up[LU_HP]  = BU_AFT->unit.pClassData->promotionHp;
	gLevelUpStatsBase.stat_up[LU_STR] = BU_AFT->unit.pClassData->promotionPow;
	gLevelUpStatsBase.stat_up[LU_MAG] = GetClassPromoBonusMag(BU_AFT->unit.pClassData->number);
	gLevelUpStatsBase.stat_up[LU_SKL] = BU_AFT->unit.pClassData->promotionSkl;
	gLevelUpStatsBase.stat_up[LU_SPD] = BU_AFT->unit.pClassData->promotionSpd;
	
	gLevelUpStatsBase.stat_up[LU_LCK] = 0;
	gLevelUpStatsBase.stat_up[LU_DEF] = BU_AFT->unit.pClassData->promotionDef;
	gLevelUpStatsBase.stat_up[LU_RES] = BU_AFT->unit.pClassData->promotionRes;
	gLevelUpStatsBase.stat_up[LU_CON] = 
		BU_AFT->unit.pClassData->baseCon - BU_PRE->unit.pClassData->baseCon;
	gLevelUpStatsBase.stat_up[LU_MOV] = 
		BU_AFT->unit.pClassData->baseMov - BU_PRE->unit.pClassData->baseMov;
}


// 0x807352C
void EkrLevelUp_InitStatsAndPutText(Proc_EkrLevelUp_t *proc){
	
	struct BattleUnit *bu1, *bu2;
	
	
	if ( proc->gAISMain ){
		bu1 = *gpUnitRight_BattleStruct;
		bu2 = *gpUnitLeft_BattleStruct;
	}
	else{
		bu1 = *gpUnitLeft_BattleStruct;
		bu2 = *gpUnitRight_BattleStruct;
	}
	
	BU_PRE = bu1;
	BU_AFT = bu2;
	
	// Set Status buffer
	gLevelUpStatsBase.bu = bu1;
	
	if( FALSE == proc->promo )
		EkrPutText_SetStatusNonePromo();
	else
		EkrPutText_SetStatusPromo();
	
	// Draw texts
	Font_InitForUI(&gSomeFontStruct, (void*) 0x60028C0, 0x146, 0);
	
	// Draw Status Text
	for(int i = 0; i < LU_STAT_MAX; i++ )
	{
		struct TextHandle* th = LU_text(LUTEXT_STR_HP + i);
		char* stat_name = GetStringFromIndex(TABLE_ON[i].text_id);
		int x = TABLE_ON[i].x;
		int y = TABLE_ON[i].y;
		
		Text_Init(th, 3);
		Text_SetXCursor(th, 0);
		Text_SetColorId(th, TEXT_COLOR_GOLD);
		Text_AppendString(th, stat_name);
		Text_Draw(th, TILEMAP_LOCATED(gBG2TilemapBuffer,x,y) );
	}
		

	// Draw Status Number
	for(int i = 0; i < LU_STAT_MAX; i++ )
	{
		struct TextHandle* th = LU_text(LUTEXT_NUM_HP + i);
		int num = TABLE_ON[i].Get_Base(bu1);
		
		int x = 3 + TABLE_ON[i].x;
		int y = TABLE_ON[i].y;
		
		Text_Init(th, 2);
		Text_SetXCursor(th, 8);
		Text_SetColorId(th, TEXT_COLOR_BLUE);
		Text_AppendDecNumber(th, num);
		Text_Draw(th, TILEMAP_LOCATED(gBG2TilemapBuffer,x,y) );
	}

		
	// class name
	Text_Init(LU_text(LUTEXT_STR_CLASS), 8);
	
	Text_AppendString(
		LU_text(LUTEXT_STR_CLASS), 
		GetStringFromIndex(bu1->unit.pClassData->nameTextId) );
		
	Text_Draw(
		LU_text(LUTEXT_STR_CLASS), 
		TILEMAP_LOCATED(gBG2TilemapBuffer,3,5) );


		
	// "lv"
	Text_Init(LU_text(LUTEXT_STR_LEVEL), 8);
	
	Text_AppendString(
		LU_text(LUTEXT_STR_LEVEL), 
		GetStringFromIndex(0x4E7) );
		
	Text_Draw(
		LU_text(LUTEXT_STR_LEVEL), 
		TILEMAP_LOCATED(gBG2TilemapBuffer,11,5) );
		
	
	// level-pre
	Text_Init(LU_text(LUTEXT_NUM_LEVEL), 2);
	Text_SetXCursor(LU_text(LUTEXT_NUM_LEVEL), 8);
	Text_SetColorId(LU_text(LUTEXT_NUM_LEVEL), TEXT_COLOR_BLUE);
	Text_AppendDecNumber(LU_text(LUTEXT_NUM_LEVEL), bu1->levelPrevious);
	Text_Draw(
		LU_text(LUTEXT_NUM_LEVEL), 
		TILEMAP_LOCATED(gBG2TilemapBuffer, 13, 5) );
}





// 0x8074041
void EkrLevelUpProc_Promo_DrawNewClassNameLv(Proc_EkrLevelUp_t* proc){	
	static u16 *ekrlu_class_window_offset = (u16*) 0x2020134;
	static int (*Ekr_Calc)(int,int,int,int,int) = (const void*)0x8012DCD;
	
	if ( !proc->promo )
		goto GOTO_break_and_return;
	
	// Ekr_CommonCalc
	*ekrlu_class_window_offset = 
		Ekr_Calc(1, 0, 0x1000, proc->cnt, proc->stat_id);
	
	if( ++proc->cnt <= proc->stat_id )
		return;
	
	
	// draw class name
	BU_PRE = BU_AFT;
	
	struct TextHandle* th = LU_text(LUTEXT_STR_CLASS);
	const char *str = GetStringFromIndex(BU_AFT->unit.pClassData->nameTextId);
	
	Text_Clear(th);
	Text_AppendString(th, str);
	Text_Draw(th, TILEMAP_LOCATED(gBG2TilemapBuffer,3,5) );
	
	// draw class level
	th = LU_text(LUTEXT_NUM_LEVEL);
	Text_Clear(th);
	Text_SetXCursor(th, 8);
	Text_SetColorId(th, TEXT_COLOR_BLUE);
	Text_AppendDecNumber(th, 1);
	Text_Draw(th, TILEMAP_LOCATED(gBG2TilemapBuffer, 13, 5) );
	
	proc->cnt = 0;
	proc->stat_id = 8;
	
GOTO_break_and_return:
	Proc_Break(proc);
	return;

}







// 0x807411C
void EkrLevelUpProc_DrawNewLevel(Proc_EkrLevelUp_t* proc){
	extern void SomePlaySound_8071990(int ,int);
	static void (*sub_8071AB0)(int,int,int) = (const void*)0x8071AB1;
	static void (*EkrLevelUp_SomeAPs)(int,int,int,int,int,int) = (const void*)(0x8074D58+1);
	
	// extern struct TextHandle gUnknown_020176A0[];
	
	static ProcPtr* pproc_20200D8 = (ProcPtr*)0x20200D8;
	static ProcPtr (*StartProc_efxPartsofScroll)(void) = (const void*)0x8074581;
	
	if( FALSE == proc->promo ){
		proc->cnt = 0;
		EkrLevelUp_SomeAPs(0xA0, 1, 0x84, 0x3C, 0, 0);
		
		// Draw new Level
		struct TextHandle* th = LU_text(LUTEXT_NUM_LEVEL);
		
		Text_Clear(th);
		Text_SetXCursor(th, 8);
		Text_SetColorId(th, TEXT_COLOR_BLUE);
		Text_AppendDecNumber(th, BU_PRE->levelPrevious+1);
		Text_Draw(th, TILEMAP_LOCATED(gBG2TilemapBuffer, 13, 5) );
		
		SomePlaySound_8071990(0x2CD, 0x100);
		sub_8071AB0(0x2CD, 0x38, 0);
		Proc_Break(proc);
	}
	else{				
		Proc_End(*pproc_20200D8);
		*pproc_20200D8 = StartProc_efxPartsofScroll();
		
		proc->cnt = 0;
		proc->stat_id = 0;
		Proc_Break(proc);
	}
}



// 0x80741CC
void EkrLevelUpProc_MainAnime(Proc_EkrLevelUp_t* proc){
	extern void EkrLevelUp_DrawNewStat(Proc_EkrLevelUp_t*, s16);
	extern void SomePlaySound_8071990(int ,int);
	static void (*sub_8071AB0)(int,int,int) = (const void*)0x8071AB1;
	static void (*EkrLevelUp_SomeAPs)(int,int,int,int,int,int) = (const void*)(0x8074D58+1);
	static u16 *short_203E1B0 = (u16*)0x203E1B0;
	
	int stat_id;
	
	if( ++proc->cnt < 0x14 )
		return;
	
	
	// MOV!
	for( stat_id = proc->stat_id ; stat_id < LU_STAT_MAX; stat_id++ )		
		if( gLevelUpStatsBase.stat_up[stat_id] )
			break;

	
	
	proc->stat_id = stat_id+1;
	
	if( proc->stat_id > LU_STAT_MAX ){
		proc->cnt = 0;
		Proc_Break(proc);
		return;
	}
	

	// EkrLevelUp_DrawNewStat
	struct TextHandle* th = LU_text(stat_id + LU_STAT_MAX);

	int diff = gLevelUpStatsBase.stat_up[stat_id];
	int num = 
		TABLE_ON[stat_id].Get_Base(gLevelUpStatsBase.bu) +
		diff;
		
	int x = TABLE_ON[stat_id].x;
	int y = TABLE_ON[stat_id].y;
	
	Text_Clear(th);
	Text_SetXCursor(th, 8);
	Text_SetColorId(th, TEXT_COLOR_BLUE);
	Text_AppendDecNumber(th, num);
	Text_Draw(th, TILEMAP_LOCATED(gBG2TilemapBuffer, x+3, y) );
	
	// SomeSound
	SomePlaySound_8071990(0x76, 0x100);
	sub_8071AB0(0x76, 0x38, 0);
	
	// draw APs
	EkrLevelUp_SomeAPs(0xA0, 1, 
		0x35+x*8, 0x6+y*8, stat_id+1, diff);
	
	// HP Bar change
	if( LU_HP == stat_id ){
		short_203E1B0[1] = num;
		short_203E1B0[3] = 0xFFFF;
	}
	
	// reset counter
	proc->cnt = 0;
}




// HBlank
// 0x8074598
void EkrLevelUp_UpdateHBlankRule(void){
	
	static u16 *ekrlu_class_window_offset = (u16*) 0x2020134;
	static u16 *ekrlu_status_window_offset = (u16*) 0x2020136;

	extern u32 gUnknown_0201FDB8;
	extern u16 gUnknown_0201FB38[]; // maybe for class/lv windows
	extern u16 gUnknown_0201FC78[]; // maybe for status windows
	
	extern u16 gUnknown_0201FDC4[];
	extern u16 gUnknown_0201FF04[];
	
	u16 *_r1, *_r2;
	
	if( 0 != gUnknown_0201FDB8 ){
		_r2 = gUnknown_0201FB38;
		_r1 = gUnknown_0201FDC4;
	}
	else{
		_r2 = gUnknown_0201FC78;
		_r1 = gUnknown_0201FF04;
	}
	
	// core
	for(int i = 0; i < 0x9F; i++ )
	{
		if( i <= 0x17 ){
			*(_r2++) = 0;
			*(_r1++) = 0;
			continue;
		}
		
		else if( i <= 0x37 ){
			*(_r2++) = *ekrlu_class_window_offset;
			*(_r1++) = *ekrlu_class_window_offset;
		}
		
		else if( i < 0x9F ){
			*(_r2++) = *ekrlu_status_window_offset;
			*(_r1++) = *ekrlu_status_window_offset;
		}	
	}
}
