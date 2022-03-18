#pragma once

enum{
	// for DisplayMoveRangeGraphics
	
	MOV_BLUE 	= 1 << 0,		// $1
	MOV_RED 	= 1 << 5, 		// $20
	MOV_GREEN 	= 1 << 6,		// $40
	
	RNG_RED		= 1 << 1,		// $2
	RNG_BLUE	= 1 << 4, 		// $10
	RNG_GREEN	= 1 << 2,		// $4
};


enum{
	// for FillMapByMask
	
	NU_RANGE_MAP = 0,
	ON_RANGE_MAP = 1,
	
	NU_MOVE_MAP = -1,
	ON_MOVE_MAP = 1,
	
	NU_MOVE2_MAP = 0,
	
	ON_UNIT_MAP = 0,
};
