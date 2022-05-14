#pragma once

enum{
	
	// Size of each unit-ext data
	UNIT_EXPA_SIZE = 0x10,
	
	// number of unit-ext data
	UNIT_EXPA_MAX = 0x46,
	
	
};



struct UnitExpa{
	
	/* 00 */ u8 pad_00[0x10 - 0x00];
};

extern struct UnitExpa *gpUnitExpaData;


int UnitHasExpaData(struct Unit*);
struct UnitExpa* GetUnitExpa(struct Unit*);