#pragma once

// ====================================================

// C-Lib version: FE-CLib-Mokha
// https://github.com/MokhaLeee/FE-CLib-Mokha.git

#include "gbafe.h"
#include "prep-screen.h"
// ====================================================



struct newProc_PrepMain {
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 cur_cmd;
	/* 2A */ u8 pad_2A[0x2C - 0x2A];
	/* 2C */
	
};


struct newProc_PrepMapView {
	
	/* 00 */ PROC_HEADER;
	/* 29 */ u8 cur_cmd;
	/* 2A */ u8 pad_2A[0x3C - 0x2A];
	/* 3C */ u32 yDiff; // y Pos offset of Unit SMS
	/* 40 */ u32 xDiff;
	/* 44 */ u8 pad_44[0x4A - 0x44];
	/* 4A */ u16 unk_4A;
	/* 4C */ u8 pad_4C[0x54 - 0x4C];
	/* 54 */ void* maybe_ap;
	
};


enum{
	// PrepMenu command index
	CMD_PREPMENU_PICKUNIT = 0,
	CMD_PREPMENU_ITEM = 1,
	CMD_PREPMENU_SAVE = 2,
	CMD_PREPMENU_SUPPORT = 3,
	CMD_PREPMENU_OPTION = 4,
	CMD_PREPMENU_VIEWMAP = 5,
	CMD_PREPMENU_FORMATION = 6,
	
};

extern const struct ProcCmd newProcCmd_PrepMain[];

void StartNewPrepAtMenu(struct newProc_PrepMain*);
void StartNewPrepMapView(struct newProc_PrepMain*);