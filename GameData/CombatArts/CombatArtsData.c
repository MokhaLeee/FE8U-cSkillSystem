#include "gbafe-chax.h"

const struct CombatArtsROMList CharCombatArtsRomList[0x100] = {
	
	[CHARACTER_EIRIKA] = {
		
		.default_art[0]	= CA_HazeSlice,
		.default_art[1]	= CA_Hexblade,
		.default_art[2]	= CA_Windsweep,
		.default_art[3]	= CA_Assassinate,
		
		.master_art[0]	= 0,
		.master_art[1]	= 0,
		.master_art[2]	= 0,
		.master_art[3]	= 0,
	},
	
	
	[CHARACTER_EIRIKA] = {
		
		.default_art[0]	= CA_HazeSlice,
		.default_art[1]	= CA_Hexblade,
		.default_art[2]	= CA_Windsweep,
		.default_art[3]	= CA_Assassinate,
		
		.master_art[0]	= 0,
		.master_art[1]	= 0,
		.master_art[2]	= 0,
		.master_art[3]	= 0,
	},
	
	
	[CHARACTER_INNES] = {
		.default_art[0]	= CA_HeavyDraw,
		.default_art[1]	= CA_GravityShoot,
		.default_art[2]	= 0,
		.default_art[3]	= 0,
		
		.master_art[0]	= 0,
		.master_art[1]	= 0,
		.master_art[2]	= 0,
		.master_art[3]	= 0,
	},
};



const struct CombatArtsROMList ClassCombatArtsRomList[0x100] = {
	
	[CLASS_PALADIN] = {
		.default_art[0]	= CA_HeavyDraw,
		.default_art[1]	= CA_GravityShoot,
		.default_art[2]	= CA_TempestLance,
		.default_art[3]	= CA_Knightkneeler,
		
		.master_art[0]	= 0,
		.master_art[1]	= 0,
		.master_art[2]	= 0,
		.master_art[3]	= 0,
	},
};
