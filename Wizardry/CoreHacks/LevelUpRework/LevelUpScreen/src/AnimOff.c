#include "gbafe.h"
#include "common.h"
#include "level-up.h"
#include "level-up-rework.h"

#include "status-getter.h"
#include "str-mag.h"

extern const u8 gGfx_LevelUpBoxFrame[]; // 0x88035B0
extern const u8 gMap_LevelUpBoxFrame[]; // 0x88039E8
extern const u8 gPal_LevelUpBoxFrame[]; // 0x8803B10


static void EkrPutText_SetStatusNonePromo(struct BattleUnit* bu){
	gLevelUpStatsBase.stat_up[LU_HP]  = bu->changeHP;
	gLevelUpStatsBase.stat_up[LU_STR] = bu->changePow;
	gLevelUpStatsBase.stat_up[LU_MAG] = *GetBu_ChangeMagAt(bu);
	gLevelUpStatsBase.stat_up[LU_SKL] = bu->changeSkl;
	gLevelUpStatsBase.stat_up[LU_SPD] = bu->changeSpd;
	
	gLevelUpStatsBase.stat_up[LU_LCK] = bu->changeLck;
	gLevelUpStatsBase.stat_up[LU_DEF] = bu->changeDef;
	gLevelUpStatsBase.stat_up[LU_RES] = bu->changeRes;
	gLevelUpStatsBase.stat_up[LU_CON] = 0;
	gLevelUpStatsBase.stat_up[LU_MOV] = 0;
}


// 0x807EA99
void MapAnimLevelUp_InitLevelUpBox(s16 actor_id, u8 x, u8 y){

	struct BattleUnit* bu;
	
	BG_Fill(gBG1TilemapBuffer,0);
	
	CopyDataWithPossibleUncomp( // Decompress
		gGfx_LevelUpBoxFrame, 
		BG_CHAR_ADDR(BG1) + GetBackgroundTileDataOffset(BG1) );
	
	CopyDataWithPossibleUncomp(
		LU_table_TSA,
		gGenericBuffer );
	
	sub_80149F0(gGenericBuffer, gBG1TilemapBuffer, 0x3F0, 0x5200);
	ApplyPalettes(gPal_LevelUpBoxFrame, 5, 1); // (aSrc, aPalId, aPalCount)
	
	bu = gMapAnimData.actors[actor_id].pBattleUnit;
	
	// add to status table
	EkrPutText_SetStatusNonePromo(bu);
	
	SomeDrawTextInlineAutoWidth(
		TILEMAP_LOCATED(gBG0TilemapBuffer, x+2, y), 
		TEXT_COLOR_NORMAL,
		GetStringFromIndex(bu->unit.pClassData->nameTextId) );
	
	for(int i=0; i < LU_STAT_MAX+1; i++) // with a lv
		SomeDrawTextCentered(
			TILEMAP_LOCATED(gBG0TilemapBuffer, x+TABLE_OFF[i].x, y+TABLE_OFF[i].y),
			TEXT_COLOR_GOLD,
			3,
			GetStringFromIndex(TABLE_OFF[i].text_id) );

	
	BG_EnableSyncByMask(0b11);
}





// 0x807F1AD
void MapAnimLevelUpProc_InitLevelUpBox(Proc_MapAnimLevelUp_t* proc){
	
	extern void MapAnimLevelUp_DrawActorStat(int actor_id, int base_x, int base_y,int stat_id_p1,int BoolUp);
	extern void sub_807EDF8(u16, u16, u16, Proc_MapAnimLevelUp_t*);
	
	Text_ResetTileAllocation();
	BG_Fill(gBG0TilemapBuffer,0);

	MapAnimLevelUp_InitLevelUpBox(proc->actor_id, 1,1);
	
	for(int stat_id = 0; stat_id < LU_STAT_MAX+1; stat_id++)
		// (int actor_id, int base_x, int base_y,int stat_id,int BoolUp)
		MapAnimLevelUp_DrawActorStat(proc->actor_id, 1, 1, stat_id, FALSE);

	BG_EnableSyncByMask(0b01);
	
	proc->stat_cur = 0;
	proc->time_delay = 0;
	proc->yPos = 0xFF80;
	
	gLCDControlBuffer.bg0cnt.priority = 0;
	gLCDControlBuffer.bg1cnt.priority = 1;
	gLCDControlBuffer.bg2cnt.priority = 1;
	gLCDControlBuffer.bg3cnt.priority = 2;
	
	SetDefaultColorEffects();
	
	gLCDControlBuffer.dispcnt.win0_on = 0;
	gLCDControlBuffer.dispcnt.win1_on = 0;
	gLCDControlBuffer.dispcnt.objWin_on = 0;
	
	BG_SetPosition(BG0, 0, proc->yPos);
	BG_SetPosition(BG1, 0, proc->yPos);
	
	struct BattleUnit* bu = gMapAnimData.actors[proc->actor_id].pBattleUnit;
	
	// (int faceSlot, int portraitId, int x, int y, int displayType);
	NewFace(
		0,
		bu->unit.pCharacterData->portraitId,
		0xB8,
		0x30 - (s16)proc->yPos,
		0x1042 );
	
	gpFaceProcs->yPosition = 0x20 - proc->yPos;
	sub_807EDF8(0x200, 3, 1, proc);
	
	// add for level-up-rework Get funcs
	gLevelUpStatsBase.bu = bu;
}







// Put Window Routinue
// sub_807F30C
void MapAnimLevelUp_PutWindowOnScreen(Proc_MapAnimLevelUp_t* proc){
	
	proc->yPos += 8;
	BG_SetPosition(BG0, 0, proc->yPos);
	BG_SetPosition(BG1, 0, proc->yPos);
	
	if( proc->yPos <= 0xFFD0 )
		gpFaceProcs->yPosition = 0x20 - proc->yPos;
	
	if( proc->yPos >= 0xFFF0 )	
		Proc_Break((struct Proc*)proc);
	
}

// sub_807F354
void MapAnimLevelUp_PutWindowOffScreen(Proc_MapAnimLevelUp_t* proc){
	
	proc->yPos -= 8;
	BG_SetPosition(BG0, 0, proc->yPos);
	BG_SetPosition(BG1, 0, proc->yPos);
	
	if( proc->yPos >= 0xFF70 && proc->yPos <= 0xFFD0 )
		gpFaceProcs->yPosition = 0x20 - proc->yPos;
	
	if( proc->yPos <= 0xFF80 )
		Proc_Break((struct Proc*)proc);
}





// Main Anim
// sub_807F39C
void MapAnimLevelUp_MainAnime(Proc_MapAnimLevelUp_t* proc){
	extern void MapAnimLevelUp_DrawActorStat(int actor_id, int base_x, int base_y,int stat_id_p1,int BoolUp);
	extern s8 MapAnimLevelUp_GetActorStatUp(s16 actor_id, int stat_id_p1);
	extern void sub_807EE84(s16 x, s16 y,int stat_id_p1,s8 stat_up); // Draw AP
	
	int stat_id_p1;
	
	if( 0 != proc->time_delay )
	{
		proc->time_delay--;
		return;
	}
		
	
	
	for(stat_id_p1 = proc->stat_cur; 1; stat_id_p1++)
	{
		if( stat_id_p1 > LU_STAT_MAX )
		{
			Proc_Break((struct Proc*)proc);
			return;
		}
		
		if( 0 != MapAnimLevelUp_GetActorStatUp(proc->actor_id, stat_id_p1) )
			break;
	}
	
		
	MapAnimLevelUp_DrawActorStat(proc->actor_id,1,1,stat_id_p1,1);
	BG_EnableSyncByMask(0b01);
	
	// Here Draw some APs, which maybe we can ignore
	sub_807EE84(
		TABLE_OFF[stat_id_p1].x * 8 + 0x3E,
		TABLE_OFF[stat_id_p1].y * 8 - (proc->yPos-0x17),
		stat_id_p1,
		MapAnimLevelUp_GetActorStatUp(proc->actor_id, stat_id_p1) );
	
	if( !gChapterData.unk41_1 ){
		if( 0 == stat_id_p1 )
			m4aSongNumStart(0x2CD);
		else
			m4aSongNumStart(0x76);
	}
	
	proc->stat_cur = stat_id_p1+1;
	proc->time_delay = 0x14;
	return;

}





// Internal

// 0x807ED31
s8 MapAnimLevelUp_GetActorStatBase(s16 actor_id, int stat_id_p1){
	
	if( stat_id_p1 > LU_STAT_MAX )
		return 0;
	else
		return TABLE_OFF[stat_id_p1].Get_Base(
			gMapAnimData.actors[actor_id].pBattleUnit);
}


// 0x807EC09
s8 MapAnimLevelUp_GetActorStatUp(s16 actor_id, int stat_id_p1){
	
	if( stat_id_p1 > LU_STAT_MAX )
		return 0;
	else if( 0 == stat_id_p1 ) // lv
		return 1;
	else
		return gLevelUpStatsBase.stat_up[stat_id_p1-1];
}



// 0x807EBA5
// MapAnimLevelUp_DrawActorStat(proc->actor_id,1,1,stat_id,1);
void MapAnimLevelUp_DrawActorStat(int actor_id, int base_x, int base_y,int stat_id_p1,int BoolUp){
	
	u16* tm_loc = TILEMAP_LOCATED(
		gBG0TilemapBuffer, 
		base_x + TABLE_OFF[stat_id_p1].x + 4,
		base_y + TABLE_OFF[stat_id_p1].y );
	
	s8 stat = MapAnimLevelUp_GetActorStatBase(actor_id, stat_id_p1);
	
	if( BoolUp )
		stat += MapAnimLevelUp_GetActorStatUp(actor_id, stat_id_p1);
	
	DrawDecNumber(tm_loc, 2, stat);
}
