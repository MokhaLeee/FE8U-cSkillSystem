
void PrepPickSkill_MainLoop(struct Proc_PrepPickSkill* proc){
	
	struct PrepSkillsList* list;
	int xHand, yHand;
	
	if( PREP_SCROLL_NOPE != proc->scroll_type )
		goto goto_scroll;
	
	// Check scroll speed
	proc->scroll_step = 0 == (L_BUTTON & gKeyStatusPtr->heldKeys)
		? 4 : 8;
	
	list = GetUnitPrepSkillsList(proc->unit);
	
	// Handle normal button
	
	if( B_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_END);
		PlaySoundEffect(0x6B);
		return;
		
	} // B_BUTTON
	
	else if( R_BUTTON & gKeyStatusPtr->newKeys )
	{
		Proc_Goto(proc, LABEL_PREPSLILLSLIST_STATSCREEN);
		return;
		
	} // R_BUTTON
	
	else if( A_BUTTON & gKeyStatusPtr->newKeys )
	{
		if( IsPrepSkillRom(proc->unit, proc->skill_id_pre) )
		{
			// try pick rom skill
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_FAIL_REMOVE);
			PlaySoundEffect(0x6C);
			return;
		}
		
		else if ( isPrepSkillEquippedRAM(proc->unit, proc->skill_id_pre) )
		{
			// Remove ram skill
			Proc_Goto(proc, LABEL_PREPSLILLSLIST_REMOVE);
			PlaySoundEffect(0x6A);
			return;
		}
		else if ( (PREP_SKLSUB_RIGHT == proc->list_type) )
		{
			if( GetUnitRamSkillCount(proc->unit) < UNIT_SKILL_COUNT )
			{
				// Add ram skill
				Proc_Goto(proc, LABEL_PREPSLILLSLIST_ADD);
				PlaySoundEffect(0x6A);
				return;
			}
			else
			{
				// replace ram skill
				// for now preserve list-index
				proc->list_index_replace = proc->list_index;
				proc->list_index = 0;
				proc->list_type = PREP_SKLSUB_LEFT_RAM;
				PlaySoundEffect(0x6A);
				
				StartParallerWorkerWithParam(PrepPickSkill_UpdateSkillDesc, 0, proc);
				PrepDrawHand( 0x10 + 0x10 * proc->list_index, 0x38, 0, 0x800);
				Proc_Goto(proc, LABEL_PREPSLILLSLIST_REPLACE);
				return;
			}
		}

		
	} // A_BUTTON

	
	
	// W.I,P.
	// DPAD
	switch (gKeyStatusPtr->repeatedKeys)
	{
		case DPAD_LEFT:
			if( PREP_SKLSUB_RIGHT == proc->list_type )
			{
				int line_cur = _lib_div(proc->list_index, 6) - proc->head_line;
				
				if( _lib_mod(proc->list_index, 6) == 0 )
				{
					if( line_cur < 2 )
						proc->list_type = PREP_SKLSUB_LEFT_RAM;

					else
						proc->list_type = PREP_SKLSUB_LEFT_ROM;
					
					proc->list_index = 
						0 == list->total[ proc->list_type ]
						? 0
						: list->total[ proc->list_type ] - 1;
				}
				else
				{
					if( 0 != proc->list_index )
						proc->list_index--;
				}
			}
			else if( 0 != proc->list_index )
				proc->list_index--;
			
			break;
		
		case DPAD_RIGHT:

			if( PREP_SKLSUB_RIGHT != proc->list_type ){
				if( proc->list_index < (list->total[proc->list_type]-1) )
					proc->list_index++;
				else{
					proc->list_type = PREP_SKLSUB_RIGHT;
					proc->list_index = 6 * proc->head_line;
				}
			}
			else{
				if( proc->list_index < (list->total[proc->list_type]-1) ){
					proc->list_index++;
					
					if( _lib_div(proc->list_index, 6) > (proc->head_line + 2) )
						proc->scroll_type = PREP_SCROLL_DOWN;
				}
			}

			break;
		
		case DPAD_UP:
			switch( proc->list_type )
			{
				case PREP_SKLSUB_RIGHT:
					if( proc->list_index >= 6 * (proc->head_line + 1) )
						proc->list_index -= 6;
					
					else if( proc->head_line != 0 ){
						proc->list_index -= 6;
						proc->scroll_type = PREP_SCROLL_UP;
					}
					
					break;
				
				case PREP_SKLSUB_LEFT_RAM:
					proc->list_type = PREP_SKLSUB_RIGHT;
					proc->list_index = 0;
					break;
				
				case PREP_SKLSUB_LEFT_ROM:
					proc->list_type = PREP_SKLSUB_LEFT_RAM;
					
					if( proc->list_index >= list->total[PREP_SKLSUB_LEFT_RAM] )
						proc->list_index = 
							0 == list->total[PREP_SKLSUB_LEFT_RAM]
								? 0
								: list->total[PREP_SKLSUB_LEFT_RAM] - 1;
					break;
					
				default:
					break;	
			}
			break;
		
		case DPAD_DOWN:
			switch( proc->list_type )
			{
				case PREP_SKLSUB_RIGHT:
					/*
					 * 1. 下一列不是末尾，直接 +6并进一步做判断：
					 * 		当前不位于底部则什么都不做
					 *		位于底部则补一个scrolling
					 *
					 * 2. 下一列是末尾，则首先加到末尾处在向上面那样做判断
					 * 3. 当前是末尾：什么都不做；
					 */
					 
					// end
					if( _lib_div(proc->list_index, 6) == _lib_div(list->total[PREP_SKLSUB_RIGHT] - 1, 6) )
						break;
					
					// judge for index
					if( (proc->list_index+6) < list->total[PREP_SKLSUB_RIGHT] )
						proc->list_index += 6;
					else
						proc->list_index = list->total[PREP_SKLSUB_RIGHT] - 1;

					// Judge for scrolling
					if( _lib_div(proc->list_index, 6) > (proc->head_line + 2) )
						proc->scroll_type = PREP_SCROLL_DOWN;
					
					break;
				
				case PREP_SKLSUB_LEFT_RAM:
					proc->list_type = PREP_SKLSUB_LEFT_ROM;
					
					if( proc->list_index >= list->total[PREP_SKLSUB_LEFT_ROM] )
						proc->list_index = 
							0 == list->total[PREP_SKLSUB_LEFT_ROM]
							? 0
							: list->total[PREP_SKLSUB_LEFT_ROM] - 1;
					break;
				
				case PREP_SKLSUB_LEFT_ROM:
					// now rom list is default < 5
					break;
				
				default:
					break;
					
			}
			break;
		
		default:
			break;
	}
	// DPAD End
	
	
	if( 
		(proc->list_type_pre == proc->list_type) && 
		(proc->list_index_pre == proc->list_index) )
		goto goto_fail;
	
	
	// W.I.P.
	proc->list_type_pre = proc->list_type;
	proc->list_index_pre = proc->list_index;
	
	// Parallel to update skill-desc
	StartParallerWorkerWithParam(PrepPickSkill_UpdateSkillDesc, 0, proc);
	
	// M4a
	PlaySoundEffect(0x65);
	
	
	// Draw Hand
	if( PREP_SCROLL_NOPE == proc->scroll_type ){
		switch ( proc->list_type )
		{
			
			case PREP_SKLSUB_LEFT_RAM:
				xHand = 0x10 + 0x10 * proc->list_index;
				yHand = 0x38;
				break;
			
			case PREP_SKLSUB_LEFT_ROM:
				xHand = 0x10 + 0x10 * _lib_mod(proc->list_index, 5);
				yHand = 0x48 + 0x10 * _lib_div(proc->list_index, 5);
				break;
				
				
			case PREP_SKLSUB_RIGHT:
			default:
				xHand = 0x78 + 0x10 * _lib_mod(proc->list_index, 6);
				yHand = 0x28 + 0x10 * (_lib_div(proc->list_index, 6) - proc->head_line);
				break;
		}
		
		PrepDrawHand( xHand, yHand, 0, 0x800);
	}
	
goto_fail:
	return;

goto_scroll:
	return;
}