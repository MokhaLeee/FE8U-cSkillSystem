// ==========================================================
//                   On Pick Combat Arts
// ==========================================================

static void PrepPickCombatArt_InitScreen (struct Proc_PrepPickSkill* proc);
static void PrepPickCombatArt_DrawLeftIcon(struct Unit*, int config);
static void PrepPickCombatArt_DrawRightBarTexts(struct Unit*, int config);
static void PrepPickCombatArt_DrawTotalSkill(struct Unit*);
static void PrepPickCombatArt_UpdateSkillDesc(struct Proc_PrepPickSkill*);




const static struct ProcCmd gProc_PrepSkillPickCombatArtList[] = {
	
	PROC_NAME	("PREP_SKILLSCREEN_PICK_COMBAT_ARTS"),
	PROC_SET_END_CB (PrepPickSkill_OnEnd),

// Init
PROC_LABEL (LABEL_PREPSLILLSLIST_INIT),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkill_InitSkillsList),
	PROC_CALL	(PrepPickCombatArt_InitScreen),
	PROC_SLEEP	(2),
	PROC_CALL_ARG (NewFadeIn, 0x4),
	PROC_WHILE	(FadeInExists),


// Main Loop
PROC_LABEL (LABEL_PREPSLILLSLIST_IDLE),	
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkill_MainLoop),
	

// Stat Screen
PROC_LABEL (LABEL_PREPSLILLSLIST_STATSCREEN),
	PROC_CALL	(EndProc_PrepSkillObj),
	PROC_CALL	(sub_809B4C0),
	PROC_SLEEP	(2),
	PROC_CALL	(sub_809B014),
	PROC_CALL	(PrepPickSkill_StartStatScreen), // Here Start StatScreen
	PROC_YIELD,
	PROC_CALL	(PrepPickSkill_PostStatScreen),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),
	

// When pick rom skill in right list
PROC_LABEL (LABEL_PREPSLILLSLIST_FAIL_REMOVE),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkill_FailAddSkillPre),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkill_FailAddSkillIdle),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_POST_CANCEL),


// When pick rom-equipped skill
PROC_LABEL (LABEL_PREPSLILLSLIST_REMOVE),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkil_PrepareRemoveSkillWindow),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkil_TryRemoveSkillIdle),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),


// When try to add skills
PROC_LABEL (LABEL_PREPSLILLSLIST_ADD),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkil_PrepareAddSkillWindow),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkil_TryAddSkillIdle),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),


// When try to replace skills
PROC_LABEL (LABEL_PREPSLILLSLIST_REPLACE),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkil_PickReplacedSkillIdle),

// After pick replacing skill
PROC_LABEL (LABEL_PREPSLILLSLIST_POST_REPLACE),
	PROC_YIELD,
	PROC_CALL	(PrepPickSkil_PrepareReplaceSkillWindow),
	PROC_YIELD,
	PROC_REPEAT	(PrepPickSkil_ConfirmReplaceSkillIdle),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_INIT),

// When fail or cancel to add & remove skill 
PROC_LABEL (LABEL_PREPSLILLSLIST_POST_CANCEL),
	PROC_CALL	(PrepPickSkil_CancelOnSkill),
	PROC_GOTO	(LABEL_PREPSLILLSLIST_IDLE),

// End
PROC_LABEL (LABEL_PREPSLILLSLIST_END),
	PROC_CALL	(DeleteEach6CDifferedLoop),
	PROC_CALL_ARG (NewFadeOut, 0x8),
	PROC_WHILE	(FadeOutExists),
	PROC_END,
};


void PrepPickCombatArt_InitScreen (struct Proc_PrepPickSkill* proc){
	
	u16 BgConfig[12] =
	{
		// tile offset	map offset	screen size
		0x0000,			0xE000,		0,			// BG 0
		0x0000,			0xE800,		0,			// BG 1
		0x0000,			0xF000,		0,			// BG 2
		0x8000,			0xF800,		0,			// BG 3
	};
	
	SetupBackgrounds(BgConfig);
	
	gLCDControlBuffer.dispcnt.bg0_on = 0;
	gLCDControlBuffer.dispcnt.bg1_on = 0;
	gLCDControlBuffer.dispcnt.bg2_on = 0;
	gLCDControlBuffer.dispcnt.bg3_on = 0;
	gLCDControlBuffer.dispcnt.obj_on = 0;
	
	//sub_809ADC8(proc); 
	
	BG_Fill(gBG0TilemapBuffer, 0);
	BG_Fill(gBG1TilemapBuffer, 0);
	BG_Fill(gBG2TilemapBuffer, 0);
	ResetIconGraphics();
	
	gLCDControlBuffer.bg0cnt.priority = 0b00;
	gLCDControlBuffer.bg1cnt.priority = 0b10;
	gLCDControlBuffer.bg2cnt.priority = 0b01;
	gLCDControlBuffer.bg3cnt.priority = 0b11;
	
	BG_SetPosition( 0, 0, 0);
	BG_SetPosition( 1, 0, 0);
	BG_SetPosition( 2, 0, 0);
	BG_SetPosition( 3, 0, 0);
	
	EndGreenTextColorManager();
	PrepPickSkill_InitTexts();
	PrepPickSkill_DrawWindowGfx();
	
	
	BG_EnableSyncByMask(0b1111);
	SetDefaultColorEffects();
	
	
	// Hand
	ResetPrepScreenHandCursor(proc);
	PrepScreen_DrawHandGfxMaybe(0x600, 0x1);
	PrepDrawHand( 0x78, 0x28, 0, 0x800);
	
	// Skill Obj misc
	StartProc_PrepCombatArtObj(proc);
	
	// BG Scroll
	PrepStartScroll(proc, 0xE0, 0x20, 0x200, 2);
	
	// Draw Text Icons
	PrepUnit_DrawLeftUnitName(proc->unit);
	PrepPickCombatArt_DrawLeftIcon(proc->unit, ON_DRAW_CONFIG_INIT);
	PrepPickCombatArt_DrawRightBarTexts(proc->unit, ON_DRAW_CONFIG_INIT);
	PrepPickCombatArt_DrawTotalSkill(proc->unit);
	
	
	// Parallel to update skill-desc
	StartParallerWorkerWithParam(PrepPickCombatArt_UpdateDesc, 0, proc);

	LoadDialogueBoxGfx(BG_SCREEN_ADDR(0x29), 5);
	RestartScreenMenuScrollingBg();
}







void PrepPickCombatArt_DrawLeftIcon(struct Unit*, int config){
	
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
			"Equipped:");
		
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
		TILEMAP_LOCATED( gBG0TilemapBuffer, 1, 9),
		0xB, 0x1, 0);
	
	
	
	list = GetUnitPrepSkillsList(unit);
	
	// RAM Skills
	if( 0 == list->total[PREP_SKLSUB_LEFT_CA] )
		DrawTextInline(
			&gPrepUnitTexts[0x12],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 2, 7),
			TEXT_COLOR_GRAY,
			0, 0, 
			"None");
	else
		for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_CA]; i++ )
			DrawIcon(
				TILEMAP_LOCATED( gBG0TilemapBuffer, 2 + i * 2, 7 ),
				COMBAT_ART_ICON(list->skills_CombatArt[i]), 
				TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) );
	
	
	
}




void PrepPickCombatArt_DrawRightBarTexts(struct Unit*, int config){
	
	// config: 0->init, 1->update
	
	struct PrepSkillsList* list = GetUnitPrepSkillsList(unit);
	
	if( ON_DRAW_CONFIG_INIT == config )
	{
		Text_Clear(&gStatScreen.text[0]);
		Text_Clear(&gStatScreen.text[1]);
		Text_Clear(&gStatScreen.text[2]);
		
		DrawTextInline(
			&gStatScreen.text[0],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xE, 0x1),
			TEXT_COLOR_NORMAL, 0, 0,
			"Pick" );
		
		DrawTextInline(
			&gStatScreen.text[1],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0x15, 0x1),
			TEXT_COLOR_NORMAL, 0, 0,
			"Total" );
		
		DrawTextInline(
			&gStatScreen.text[4],
			TILEMAP_LOCATED( gBG0TilemapBuffer, 0xE, 0x3),
			TEXT_COLOR_NORMAL, 0, 0,
			"Combat Arts:" );
		
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
		0 == (PREPSKILL_LISTLEN_CA - list->total[PREP_SKLSUB_LEFT_CA])
			? TEXT_COLOR_GRAY
			: TEXT_COLOR_BLUE,
		PREPSKILL_LISTLEN_CA - list->total[PREP_SKLSUB_LEFT_CA] );
	
	DrawDecNumber(
		TILEMAP_LOCATED( gBG0TilemapBuffer, 0x1B, 0x1),
		(PREPSKILL_LISTLEN_CA == list->total[PREP_SKLSUB_LEFT_CA])
			? TEXT_COLOR_GREEN
			: TEXT_COLOR_BLUE,
		list->total[PREP_SKLSUB_LEFT_CA] );
		
	
	// On End
	BG_EnableSyncByMask(0b01);
	
}



void PrepPickCombatArt_DrawTotalSkill(struct Unit*){
	
	struct PrepSkillsList* list;
	
	Text_Clear(&gStatScreen.text[3]);
	
	list = GetUnitPrepSkillsList(unit);
	

	if( 0 == list->total[PREP_SKLSUB_RIGHT] )
		DrawTextInline(
			&gStatScreen.text[3],
			TILEMAP_LOCATED( gBG2TilemapBuffer, 0xF, 0x5),
			TEXT_COLOR_NORMAL, 0, 0,
			"None" );
	else		
		for( int i = 0; i < list->total[PREP_SKLSUB_RIGHT]; i++ )
		{
			int yOff = i / 6;
			int xOff = i - yOff * 6;
			
			int xPos = 0xF + 0x2 * xOff;
			int yPos = 0x5 + 0x2 * yOff;
			
			
			DrawIcon(
				TILEMAP_LOCATED( gBG2TilemapBuffer, xPos, yPos),
				COMBAT_ART_ICON(list->skills_all[i]), 
				TILEREF(0, STATSCREEN_BGPAL_ITEMICONS) 
			);
		}
}


// ==========================================================
//                  Combat Arts: Parallel
// ==========================================================

void PrepPickCombatArt_UpdateSkillDesc(struct Proc_PrepPickSkill*){
	
	const int xStart = 0x5;
	const int yStart = 0xD;
	
	struct PrepSkillsList* list;
	int skill_id;
	char* str;
	
	list = GetUnitPrepSkillsList(proc->unit);
	
	switch( proc->list_type )
	{
		
		case PREP_SKLSUB_LEFT_CA:
			skill_id = list->skills_CombatArt[proc->list_index];
			break;
			
		case PREP_SKLSUB_RIGHT:
		default:
			skill_id = list->skills_all[proc->list_index];
			break;
	}
	
	if( skill_id == proc->skill_id_pre )
		return;
	
	TileMap_FillRect(
		TILEMAP_LOCATED( gBG0TilemapBuffer, xStart, yStart),
		0x10, 0x6 , 0 );
	
	proc->skill_id_pre = skill_id;
	
	const struct CombatArtInfo* info = CombatArtInfoTable(skill_id);
	
	str = GetStringFromIndex(info->msg_name);
	
	if( (0 == info) || (0 == str) )
		goto goto_end;
	
	
	
	for( int line = 0; line < 3; line++ )
	{
		Text_Clear(&gStatScreen.text[6 + line]);
		
		DrawTextInline(
			&gStatScreen.text[6 + line],
			TILEMAP_LOCATED( gBG0TilemapBuffer, xStart, yStart + 2 * line),
			TEXT_COLOR_NORMAL, 0, 0,
			str );
		
		
		
		// w.i.p. for chinese
		while( 1 != *str++ ) // '\n'
			if( 0 == *str )
				goto goto_end;
	
	}
	
goto_end:
	BG_EnableSyncByMask(0b01);
	
}

