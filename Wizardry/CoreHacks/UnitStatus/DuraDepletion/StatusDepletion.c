#include "gbafe-chax.h"

struct Porc_StatusClear{
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 unk_29[0x4C - 0x29];
	/* 4C */ u16 tar_cur;
	/* 4E */ u8 unk_4E[0x58 - 0x4E];
	/* 58 */ u32 status_index;
};

// UnitStatusDepletionCore
void sub_80361AC(struct Porc_StatusClear *proc){
	
	extern void StartStatusClearFx(struct Unit*, ProcPtr);
	
	struct SelectTarget* tar = GetTarget(proc->tar_cur);
	struct Unit* unit = GetUnit(gActionData.subjectIndex);
	
	int status_index = GetUnitStatusIndex(unit);
	
	proc->status_index = status_index;
	
	SetUnitStatus(unit, 0);
	
	if( GetStatusInfo(status_index)->is_debuff )
		StartStatusClearFx( GetUnit(tar->uid), proc);

	
}



void TickActiveFactionTurn(void) {
	int displayMapChange = FALSE;

	InitTargets(0, 0);
	
	for (int i = gRAMChapterData.chapterPhaseIndex + 1; i < gRAMChapterData.chapterPhaseIndex + 0x40; ++i) {
		struct Unit* unit = GetUnit(i);

		if (!UNIT_IS_VALID(unit))
			continue;

		if (unit->state & (US_UNAVAILABLE | US_RESCUED))
			continue;

		if (unit->barrierDuration != 0)
			unit->barrierDuration--;

		if (unit->torchDuration != 0) {
			unit->torchDuration--;
			displayMapChange = TRUE;
		}
	
	}
	

	if (displayMapChange) {
		RenderBmMapOnBg2();
		RefreshEntityBmMaps();
		RenderBmMap();
		NewBMXFADE(TRUE);
		SMS_UpdateFromGameData();
	}
	
	
	/*
	 *
	 * new rule：
	 * if buff, clear it in own phase
	 * if debuff, clear in enimy's phase
	 *
	 */
	 
	 #define DEC_STATUS(i)											\
		struct Unit* unit = GetUnit(i);								\
		int status_index = GetUnitStatusIndex(unit);				\
																	\
		if( 0 != GetUnitStatusDura(unit) )							\
		{															\
			if( 1 == GetUnitStatusDura(unit) )						\
				AddTarget(unit->xPos, unit->yPos, unit->index, 0);	\
			else if( UNIT_STATUS_RECOVER != status_index )			\
				TryDecUnitStatusDura(unit);							\
		}															\
	
	if( FACTION_BLUE == gRAMChapterData.chapterPhaseIndex )
	{
		// non-debuff status
		for( int i = FACTION_BLUE + 1; i < FACTION_BLUE + 62; i++ )
		{	
			if( GetStatusInfo(GetUnitStatusIndex(GetUnit(i)))->is_debuff )
				continue;
			
			DEC_STATUS(i)
		}
		
		
		// debuff status
		for( int i = FACTION_RED + 1; i < FACTION_RED + 50; i++ )
		{
			if( !GetStatusInfo(GetUnitStatusIndex(GetUnit(i)))->is_debuff )
				continue;
			
			DEC_STATUS(i)
		}
	}
	
	else if( FACTION_RED == gRAMChapterData.chapterPhaseIndex )
	{
		// debuff status
		for( int i = FACTION_BLUE + 1; i < FACTION_BLUE + 62; i++ )
		{	
			if( !GetStatusInfo(GetUnitStatusIndex(GetUnit(i)))->is_debuff )
				continue;
			
			DEC_STATUS(i)
		}
		
		for( int i = FACTION_GREEN + 1; i < FACTION_GREEN + 20; i++ )
		{
			if( !GetStatusInfo(GetUnitStatusIndex(GetUnit(i)))->is_debuff )
				continue;
			
			DEC_STATUS(i)
		}
		
		// non-debuff status
		for( int i = FACTION_RED + 1; i < FACTION_RED + 50; i++ )
		{
			if( GetStatusInfo(GetUnitStatusIndex(GetUnit(i)))->is_debuff )
				continue;
			
			DEC_STATUS(i)
		}
	}
	
	else if( FACTION_GREEN == gRAMChapterData.chapterPhaseIndex )
	{
		for( int i = FACTION_GREEN + 1; i < FACTION_GREEN + 20; i++ )
		{
			if( GetStatusInfo(GetUnitStatusIndex(GetUnit(i)))->is_debuff )
				continue;
			
			DEC_STATUS(i)
		}
	}
	
	
	#undef DEC_STATUS
}



