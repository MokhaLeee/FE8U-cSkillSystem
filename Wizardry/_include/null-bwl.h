
#pragma once

#include "gbafe.h"

enum
{
	MAX_BWL_CHAR = 0x46,
};

struct NewBwlData
{
	/* 00 */ uint8_t supports[0x8];
	/* 08 */ uint8_t combatArts[0x5];
	/* 0D */ uint8_t pad_00[0x10 - 0xD];
};

extern struct NewBwlData gBWLDataStorage[]; // 0x203E894

/**
 * Gets Bwl entry for given character
 * 
 * @param charId character id
 * @return address of Bwl entry
 */
struct NewBwlData* NBwl_GetBwlData(unsigned charId);

/**
 * Returns non-zero if given character has a Bwl entry
 * 
 * @param charId character id
 * @return non-zero if character has Bwl entry
 */
int NBwl_HasBwl(unsigned charId);
