#pragma once

enum{
	
	// Size of each unit-ext data
	UNIT_EXPA_SIZE = 0x10,
	
	// number of unit-ext data
	UNIT_EXPA_MAX = 0x46,
	
	
};



struct UnitExpa{
	
	/* 00 */ u8 MasterClassList[0xA];	// in ClassRank
	/* 0A */ u8 pad_0A[0x10 - 0x0A];
};

extern struct UnitExpa *gpUnitExpaData;



int UnitHasExpaData(struct Unit*);
struct UnitExpa* GetUnitExpa(struct Unit*);




// Rom Data Expa


struct UnitRomDataExpa{
	u8 rank_ride;
	u8 rank_fly;
	u8 rank_heavy;

};


struct ClassRomDataExpa{
	u8 rank_ride;
	u8 rank_fly;
	u8 rank_heavy;
	u8 RankExp;		// lower class will gain more bonus
};


const struct UnitRomDataExpa *GetUnitRomDataExpa(u8 char_id);
const struct ClassRomDataExpa *GetClassRomDataExpa(u8 class_id);
