#pragma once

enum{
	
	// Size of each unit-ext data
	UNIT_EXT_SIZE = 0x10,
	
	// number of unit-ext data
	UNIT_EXT_MAX = 0x46,
	
	
};



struct UnitExt{
	
	/* 00 */ u8 pad_00[0x10 - 0x00];
};

extern struct UnitExt *gpUnitExtData;


int UnitHasExtData(struct Unit*);
struct UnitExt* GetUnitExt(struct Unit*);