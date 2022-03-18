#pragma once

// ====================================================

// C-Lib version: FE-CLib-Mokha
// https://github.com/MokhaLeee/FE-CLib-Mokha.git

#include "gbafe.h"
// ====================================================




struct Proc_PrepItemUse
{
	/* 00 */ PROC_HEADER;
	/* 2C */ struct Unit* unit;
	/* 30 */ uint32_t item_slot;
	/* 34 */ uint32_t item34;
	/* 38 */ uint32_t item38_rText;
};


struct Proc_PrepItemBoost
{
	/* 00 */ PROC_HEADER;
	/* 2C */ u32 timer;
	
	/* 30 */ u8 pre_stat[8];
//	/* 30 */ u8 hp;
//	/* 31 */ u8 pow;
//	/* 32 */ u8 skl;
//	/* 33 */ u8 spd;
//	/* 34 */ u8 lck;
//	/* 35 */ u8 def;
//	/* 36 */ u8 res;
//	/* 37 */ u8 con;
	
	/* 38 */ u8 new_stat[8];
//	/* 38 */ u8 new_hp;
//	/* 39 */ u8 new_pow;
//	/* 3A */ u8 new_skl;
//	/* 3B */ u8 new_spd;
//	/* 3C */ u8 new_lck;
//	/* 3D */ u8 new_def;
//	/* 3E */ u8 new_res;
//	/* 3F */ u8 new_con;
	
	/* 40 */ u32 popup_x;
	/* 44 */ u32 popup_y;
	/* 48 */ u32 popup_width;
	/* 4C */ u32 popup_height;
};



struct Proc_PrepItemJuna
{
	/* 00 */ PROC_HEADER;
	/* 2C */ u32 timer;
	/* 30 */ s8 pre_lv;
	/* 31 */ s8 new_lv;
	/* 32 */ u8 pad_32[0x34 - 0x32];
	/* 34 */ u32 popup_x;
	/* 38 */ u32 popup_y;
	/* 3C */ u32 popup_width;
	/* 40 */ u32 popup_height;
};
